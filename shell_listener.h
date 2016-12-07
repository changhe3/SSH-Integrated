# pragma once

#include <vector>
#include <string>
#include <array>
#include <sys/types.h>
#include <sys/wait.h>
#include <rapidjson/document.h>
#include <unordered_map>

extern "C" 
{
	#include <rote/rote.h>
	#include <ncurses.h>
	#include <menu.h>
	#include <panel.h>
	#include <sys/types.h>
	#include <sys/stat.h>
}

class shell_listener
{
public:
	//typedef typename std::array<int, 3> std_fd;

	struct profile_info {
		std::string remark, user, server, password, directory;
		unsigned int port;
	};

	shell_listener();

	void init();

	void create_profiles(const char*);

	void run();

	WINDOW* populate_panel(int index, int height, int width, int starty, int startx);

private:	

	static shell_listener* singleton;

	//std::vector<pid_t> pids;
	//fd_set write_fd;

	std::vector<PANEL*> terminals;

	rapidjson::Document dom;

	size_t num_profiles;

	std::unordered_map<std::string, profile_info> profiles;

	const char** choices;
	//ssh_session* sessions;
};