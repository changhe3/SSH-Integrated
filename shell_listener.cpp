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
#include <mutex>
#include <csignal>
#include <pty.h>

shell_listener* shell_listener::singleton = NULL;
int master;

shell_listener::shell_listener() {
	if (singleton) {
		fprintf(stderr, "%s\n", "Only one instance is allowed");
	}
	singleton = this;
	init();
}

void sig_catch(int signal) {
	assert(signal == SIGUSR1);
}

template <typename T>
void println(T t) {
	static std::mutex mtx;
	mtx.lock();
	std::cout << t;
	mtx.unlock();
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
	//std::thread reader((shell_listener::read_stderr));
	std::thread reader2((shell_listener::read_stdout));
	//reader.detach();
	reader2.detach();
}

size_t shell_listener::create_shell_process() {
	char* args[] = {"/bin/bash", "-i", NULL};
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	int pid = forkpty(&master, NULL, NULL, &w);
	if (pid == 0) execve(args[0], args, NULL);

	return 0;
}

void shell_listener::run() {
	std::string input;
	std::string prompt;
	signal(SIGUSR1, sig_catch);

	while(1) {
		//prompt = get_cmd_prompt();
		//std::cout << prompt;
		if (!std::getline(std::cin, input)) break;
		ssize_t bytes = write(master, input.c_str(), input.size());
        write(master, "\n", 1);
        //std::string trigger("kill -SIGUSR1 $(ps -o ppid= $$) \n");
        //write(master, trigger.c_str(), trigger.size());
        //pause();
	}
}

const char* shell_listener::get_env_value(const char* name) {
	char* result = secure_getenv(name);
	if (!result) return result;
	return std::strchr(result, '=') + 1;
}

void shell_listener::read_stdout() {
	//printf("writing thread ready\n");
	int fd = master;

	char* buffer = NULL;
	size_t size = 0;
	FILE* fp = fdopen(fd, "r");
	assert(fp);

	loop:
	while (getline(&buffer, &size, fp) != -1) {
		println(buffer);
	}
	goto loop;
	free(buffer);	
}

void shell_listener::read_stderr() {
	//printf("writing thread ready\n");
	int fd = singleton->fds[0][1];

	char* buffer = NULL;
	size_t size = 0;
	FILE* fp = fdopen(fd, "r");
	assert(fp);

	loop:
	while (getline(&buffer, &size, fp) != -1) {
		println(buffer);
	}
	goto loop;
	free(buffer);	
}