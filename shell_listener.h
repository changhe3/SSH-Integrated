#include <vector>
#include <string>
#include <array>

class shell_listener
{
public:
	typedef std::array<int, 3> std_fd;

	shell_listener();
	~shell_listener();

	std::string get_cmd_prompt();

	//initialize
	void init();

	//create a shell subprocess and setup pipes
	void create_shell_process();

	void run();

private:	

	static shell_listener* singleton = NULL;

	std::vector<pid> pids;
	std::vector<std_fd> fds;
	//fd_set read_fd;
	//fd_set write_fd;

	static void read_and_write();

	const char* get_env_value(const char* name);
};