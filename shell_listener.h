#include <vector>
#include <string>
#include <array>
#include <sys/types.h>
#include <sys/wait.h>

class shell_listener
{
public:
	typedef typename std::array<int, 3> std_fd;

	shell_listener();
	//~shell_listener();

	std::string get_cmd_prompt();

	//initialize
	void init();

	//create a shell subprocess and setup pipes
	size_t create_shell_process();

	void run();

private:	

	static shell_listener* singleton;

	std::vector<pid_t> pids;
	std::vector<std_fd> fds;
	fd_set read_fd;
	//fd_set write_fd;

	static void read_stdout();
	static void read_stderr();

	const char* get_env_value(const char* name);
};