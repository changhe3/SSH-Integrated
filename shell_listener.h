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
#include <vector>
#include <string>

class shell_listener
{
public:
	typedef std::array<int, 3> std_fd;

	shell_listener();
	~shell_listener();

	std::string get_cmd_prompt();

	void init();

private:	

	std::vector<std_fd> fds;

	const char* get_env_value(const char* name);
};