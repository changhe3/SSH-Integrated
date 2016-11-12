# pragma once

#include <vector>
#include <string>
#include <array>
#include <sys/types.h>
#include <sys/wait.h>

class shell_listener
{
public:
	//typedef typename std::array<int, 3> std_fd;

	shell_listener();
	//~shell_listener();

	//initialize
	void init();


	void run();

private:	

	static shell_listener* singleton;

	std::vector<pid_t> pids;
	//fd_set write_fd;
};