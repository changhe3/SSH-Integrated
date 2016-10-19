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
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <signal.h>

shell_listener* shell_listener::singleton = NULL;

shell_listener::shell_listener() {
	if (singleton) {
		fprintf(stderr, "%s\n", "Only one instance is allowed");
	}
	singleton = this;
	init();
}

std::string shell_listener::get_cmd_prompt() {
	const char* user = cuserid(NULL);
	char hostname[1024];
	hostname[1023] = '\0';
	gethostname(hostname, 1023);
	char* cwd = get_current_dir_name(); // DYNAMIC MEMORY ALLOCATED

	std::stringstream ss;
	ss << '[' << user << '@' << hostname << ' ' << cwd << ']' << "$ ";
	free(cwd);
	return ss.str();
}

void shell_listener::init() {
	// create pipes
	create_shell_process();
	//std::thread reader(shell_listener::read_and_write);
	//reader.detach();
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
		close(stdin_pipe[0]);
		close(stdout_pipe[1]);
		close(stderr_pipe[1]);

		errno = 0;
		if (fcntl(stderr_pipe[0], F_SETFL, fcntl(stderr_pipe[0], F_GETFL) | O_NONBLOCK) == -1) {
			perror("Call to fcntl failed.\n"); exit(1);
		}

		errno = 0;
		if (fcntl(stdout_pipe[0], F_SETFL, fcntl(stdout_pipe[0], F_GETFL) | O_NONBLOCK) == -1) {
			perror("Call to fcntl failed.\n"); exit(1);
		}

		fds.push_back({{stdin_pipe[1], stderr_pipe[0], stdout_pipe[0]}});
		pids.push_back(bash);
	}

	return index;
}

void shell_listener::run() {
	std::string input;
	std::string prompt;
	pid_t pid = getpid();
	signal(SIGRTMIN, shell_listener::read_and_write);

	while(1) {
		prompt = get_cmd_prompt();
		std::cout << prompt;
		if (!std::getline(std::cin, input)) break;
		//printf("reading\n");
		//std::cout << input << std::endl;
		ssize_t bytes = write(fds[0][0], input.c_str(), input.size());
		//printf("%zd bytes written\n", bytes);
        write(fds[0][0], "\n", 1);
        std::string trigger("kill -SIGRTMIN $(ps -o ppid= $$) \n");
        write(fds[0][0], trigger.c_str(), trigger.size());
        pause();
        //read_and_write();
	}
}

const char* shell_listener::get_env_value(const char* name) {
	char* result = secure_getenv(name);
	if (!result) return result;
	return std::strchr(result, '=') + 1;
}

void shell_listener::read_and_write(int signal) {
	assert(signal == SIGRTMIN);
	//printf("writing thread ready\n");
	std_fd fd_arr = singleton->fds[0];
	char buffer[BUFSIZ];
	ssize_t result;
	ssize_t bytesread = 0;
	while (true) {
		errno = 0;
		result = read(fd_arr[1], buffer, BUFSIZ-1);
		int read_err = errno;

		if (result > 0) {
			buffer[result] = '\0';
			std::cout << buffer;
		}

		if (read_err == EAGAIN || read_err == EWOULDBLOCK) {
			break;
		}
	}

	while (true) {
		errno = 0;
		result = read(fd_arr[2], buffer, BUFSIZ-1);
		int read_err = errno;

		if (result > 0) {
			buffer[result] = '\0';
			std::cout << buffer;
		}

		if (read_err == EAGAIN || read_err == EWOULDBLOCK) {
			break;
		}
	}	
}