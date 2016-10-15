#include <iostream>
#include <unistd.h>
#include <istream>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <thread>
#include <cassert>

//sending input and output to a bash terminal

// istream& posix_wrapper(FILE* fp) {
// 	__gnu_cxx::stdio_filebuf<char> filebuf(posix_handle, std::ios::in);
// 	istream& ret = *new is(&filebuf);
// 	return ret;
// }

void read_and_write(int fd) {
	char* buffer = NULL;
	size_t size = 0;
	FILE* fp = fdopen(fd, "r");
	assert(fp);

	loop:
	//printf("writing thread open\n");
	while (getline(&buffer, &size, fp) != -1) {
		//printf("writing\n");
		printf("%s", buffer);
	}
	//printf("done_printing\n");
	goto loop;

	// buffer = (char*) malloc(20);
	// ssize_t res = read(fd, buffer, 20);
	// printf("%zd bytes read\n", res);
	// printf("%s", buffer);
	// if (res == -1) perror("read failed");

	free(buffer);
}

int main(int argc, char const *argv[])
{
	std::string user_in;

	int stderr_pipe[2];
	int stdout_pipe[2];
	int stdin_pipe[2];

	pipe(stderr_pipe);
	pipe(stdout_pipe);
	pipe(stdin_pipe);

	pid_t bash = fork();
	if (bash == -1) {
		perror("fork failed");
		goto cleanup;
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
		goto cleanup;
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

		std::thread t(read_and_write, stdout_pipe[0]);
		t.detach();

		while (std::getline(std::cin, user_in)) {
			//fprintf(stderr, "%s\n", "reading ");
			ssize_t bytes = write(stdin_pipe[1], user_in.c_str(), user_in.size());
            write(stdin_pipe[1], "\n", 1);
			//printf("%zd bytes written\n", bytes);
		}

		int status;
		waitpid(bash, &status, 0);
		return 0;
	}

	cleanup:	
	return 1;

	return 0;
}

