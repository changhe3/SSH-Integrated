#include "shell_listener.h"
#include <sys/types.h>
#include <signal.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <istream>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <thread>
#include <cassert>

shell_listener::shell_listener() {
	if (singleton) {
		fprintf(stderr, "%s\n", "Only one instance is allowed");
	}
	singleton = this;
	init();
}

std::string shell_listener::get_cmd_prompt() {
	const char* user = get_env_value("USER");
	char hostname[1024];
	hostname[1023] = '\0';
	gethostname(hostname, 1023);
	char* cwd = get_current_dir_name(); // DYNAMIC MEMORY ALLOCATED

	std::stringstream ss;
	ss << '[' << user << '@' << hostname << ' ' << cwd << ']' << std::endl;
	return ss.str();
}

void shell_listener::init() {
	// create pipes
	create_shell_process();
	std::thread reader(shell_listener::read_and_write);
	reader.detach();
}

size_t shell_listener::create_shell_process() {
	size_t index = fds.size();

	int stderr_pipe[2];
	int stdout_pipe[2];
	int stdin_pipe[2];

	pipe(stderr_pipe);
	pipe(stdout_pipe);
	pipe(stdin_pipe);

	pid_t bash = fork();
	if (bash == -1) {
		perror("fork failed");
		abort();
	} else if (bash == 0) {
		close(stdin_pipe[1]);
		close(STDIN_FILENO);
		dup2(stdin_pipe[0], STDIN_FILENO);

		close(stdout_pipe[0]);
		close(STDOUT_FILENO);
		dup2(stdout_pipe[1], STDOUT_FILENO);

		close(stderr_pipe[0]);
		close(STDERR_FILENO);
		dup2(stderr_pipe[1], STDERR_FILENO);

		//printf("starting shell\n");
		execlp("bash", "bash", NULL);
		perror("exec failed");
		kill(getppid(), SIGTERM);
		abort();
	} else {
		char* stdout_buffer = NULL;
		char* stderr_buffer = NULL;
		size_t stderr_size = 0;
		size_t stdout_size = 0;
		size_t bytesread_stderr = 0;
		size_t bytesread_stdout = 0;

		close(stdin_pipe[0]);
		close(stdout_pipe[1]);
		close(stderr_pipe[1]);

		fds.emplace_back(stdin_pipe[1], stderr_pipe[0], stdout_pipe[0]);
		pids.push_back(bash);
	}
}

void shell_listener::run() {
	std::string input;
	while(std::getline(std::cin, input)) {
		ssize_t bytes = write(fds[0][STDIN_FILENO], user_in.c_str(), user_in.size());
        write(fds[0][STDIN_FILENO], "\n", 1);
	}
}

const char* shell_listener::get_env_value(const char* name) {
	char* result = secure_getenv(name);
	if (!result) return result;
	return std::strchr(result) + 1;
}

static void shell_listener::read_and_write() {
	int fd = singleton->fds[0][STDOUT_FILENO];

	char* buffer = NULL;
	size_t size = 0;
	FILE* fp = fdopen(fd, "r");
	assert(fp);

	loop:
	while (getline(&buffer, &size, fp) != -1) {
		printf("%s", buffer);
	}
	goto loop;
}