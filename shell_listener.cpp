#include "shell_listener.h"

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
	int stderr_pipe[2];
	int stdout_pipe[2];
	int stdin_pipe[2];

	pipe(stderr_pipe);
	pipe(stdout_pipe);
	pipe(stdin_pipe);

	
}

const char* shell_listener::get_env_value(const char* name) {
	char* result = secure_getenv(name);
	if (!result) return result;
	return std::strchr(result) + 1;
}