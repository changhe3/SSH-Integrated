#include "shell_listener.h"
#include <sys/types.h>
#include <csignal>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <thread>
#include <cassert>
#include <cstring>
#include <mutex>
#include <stropts.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/mman.h>


#define CTRLD 	4

const int WIDTH_RATIO = 4;
int TERM_WIDTH = -1;

shell_listener* shell_listener::singleton = NULL;

RoteTerm* rt;
char buf[BUFSIZ];
size_t size = 0;
int screen_w, screen_h, i, j;
WINDOW* termwin, *menuwin;

//char* choices [] = {"local", "my cs241 VM", NULL};
RoteTerm* rts [5];
//size_t num_of_choices = 6;
ITEM** items;
MENU* menu;
WINDOW* control = NULL;
int active_panel_idx = 0;

static unsigned char getout = 0;
void sigchld(int signo) { getout = 1; }

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

shell_listener::shell_listener() : terminals(5, NULL), num_profiles(0) {
	if (singleton) {
		fprintf(stderr, "%s\n", "Only one instance is allowed");
	}
	singleton = this;
	create_profiles("profile.json");
	init();
}


void shell_listener::download(int index) {
	profile_info& info = profiles[choices[index]];
	char* cmd = NULL;
	struct stat st = {0};

	asprintf(&cmd, "/tmp/%s", info.remark.c_str());
	if (stat("/tmp/%s", &st) == -1) {
	    mkdir("/tmp/%s", 0700);
	}
	cmd = NULL;
	asprintf(&cmd, "sshpass -p \'%s\' scp -r %s@%s:%s/. /tmp/%s\n", info.password.c_str(), info.user.c_str(), info.server.c_str(), info.directory.c_str(), info.remark.c_str());
	//system(cmd);
	rote_vt_write(rts[0], cmd, strlen(cmd));
	free(cmd);
	cmd = NULL;
	asprintf(&cmd, "cd /tmp/%s\n", info.remark.c_str());
	rote_vt_write(rts[0], cmd, strlen(cmd));
	free(cmd);
}

void shell_listener::upload(int index) {
	profile_info& info = profiles[choices[index]];
	char* cmd = NULL;
	asprintf(&cmd, "sshpass -p \'%s\' scp -r /tmp/%s/. %s@%s:%s\n", info.password.c_str(), info.remark.c_str(), info.user.c_str(), info.server.c_str(), info.directory.c_str());
	//system(cmd);
	rote_vt_write(rts[0], cmd, strlen(cmd));
	free(cmd);
}

void shell_listener::create_profiles(const char* filename) {
	FILE* fp = fopen(filename, "a+");
	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	rewind(fp);
	char* json = (char*) mmap(NULL, size + 1, PROT_READ | PROT_WRITE, MAP_PRIVATE, fileno(fp), 0);
	json[size] = '\0';

	dom.Parse(json);
	if (!dom.IsObject()) return;
	if (!dom.HasMember("profiles")) return;
	auto& p = dom["profiles"];
	for (rapidjson::Value::ConstValueIterator i = p.Begin(); i != p.End(); ++i) {
		if (i->HasMember("user") && i->HasMember("password") && i->HasMember("server")) num_profiles++;
		else continue;
		std::string key;
		if (i->HasMember("remark")) key = (*i)["remark"].GetString();
		else key = (*i)["server"].GetString();
		profile_info& info = profiles[key];
		info.remark = (*i)["remark"].GetString();
		info.user = (*i)["user"].GetString();
		info.server = (*i)["server"].GetString();
		info.password = (*i)["password"].GetString();
		if (i->HasMember("port")) info.port = static_cast<unsigned int>((*i)["port"].GetInt());
		else info.port = 22;
		if (i->HasMember("directory")) info.directory = (*i)["directory"].GetString();
		else info.directory = "~";
	}

	choices = new const char*[num_profiles + 2];
	//sessions = new ssh_session[num_profiles + 1](); // initialize ssh pointers to NULL
	int i = 1;
	for (const auto& info : profiles) choices[i++] = info.first.c_str();
	choices[0] = "local";
	choices[num_profiles + 1] = NULL;
	munmap(json, size + 1);
	fclose(fp);
}

void shell_listener::init() {
	signal(SIGCHLD, sigchld);
	initscr();
    noecho();
    start_color();
    raw();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    //getmaxyx(stdscr, screen_h, screen_w);
    screen_h = LINES;
    screen_w = COLS;
    screen_h -= 2;

    for (i = 0; i < 8; i++) for (j = 0; j < 8; j++)
      if (i != 7 || j != 0)
         init_pair(j*8+7-i, i, j);
    
    TERM_WIDTH = (screen_w * WIDTH_RATIO) / (WIDTH_RATIO + 1);
    termwin = create_newwin(screen_h, TERM_WIDTH, 0, 0);
    menuwin = create_newwin(screen_h, screen_w - TERM_WIDTH - 2, 0, TERM_WIDTH + 1);
    keypad(termwin, TRUE);
    nodelay(termwin, TRUE);
    keypad(menuwin, FALSE);

    // create menu
    items = (ITEM**) calloc(num_profiles + 2, sizeof(ITEM*));
    for (int i = 0; i < num_profiles + 2; ++i) items[i] = new_item(choices[i], choices[i]);
    menu = new_menu(items);
	set_menu_win(menu, menuwin);
	set_menu_sub(menu, menuwin);
	set_menu_mark(menu, " * ");

	post_menu(menu);
	refresh();
	wrefresh(menuwin);

    rt = rote_vt_create(screen_h - 1, TERM_WIDTH);
  	rote_vt_forkpty(rt, "/bin/bash --login");
  	rts[0] = rt;
  	control = termwin;

  	//curs_set(0);

  	terminals[0] = new_panel(termwin);
  	show_panel(terminals[0]);
  	update_panels();

}

WINDOW* shell_listener::populate_panel(int index, int height, int width, int starty, int startx) {
	if (terminals.size() < index + 1) {
		terminals.resize(index + 1);
	}
	auto& val = terminals[index];
	assert(!val);
	WINDOW* win = create_newwin(height, width, starty, startx);
    keypad(win, TRUE);
    nodelay(win, TRUE);
	rts[index] = rote_vt_create(screen_h - 1, TERM_WIDTH);

	std::string key(choices[index]);
	profile_info& info = profiles[key];
	char* cmd = NULL;
	asprintf(&cmd, "ssh %s@%s", info.user.c_str(), info.server.c_str());
	rote_vt_forkpty(rts[index], cmd);
	rote_vt_draw(rts[index], win, 1, 0, NULL);
	//mvwprintw(win, 0, 0, "Panel %d", index);
	//wrefresh(win);
	val = new_panel(win);
	hide_panel(val);
	update_panels();

	free(cmd);
	return win;
}

void shell_listener::run() {
	int ch = 0;
	while (!getout) {
		//rote_vt_draw(rt, termwin, 1, 0, NULL);

		for (int i = 0; i < 5; ++i) {
			if (!terminals[i]) continue;
			rote_vt_draw(rts[i], panel_window(terminals[i]), 1, 0, NULL);
			//wrefresh(panel_window(terminals[i]));
		}
		wrefresh(panel_window(terminals[active_panel_idx]));
		
		//ch = wgetch(termwin);
		ch = wgetch(panel_window(terminals[active_panel_idx]));
		if (ch == KEY_F(1)) control = menuwin;
		else if (control == menuwin) {
			wrefresh(menuwin);
			//mvwprintw(termwin, 0, 0, "Connection #%d activated", 0);
			if (ch == KEY_DOWN) menu_driver(menu, REQ_DOWN_ITEM);
			else if (ch == KEY_UP) menu_driver(menu, REQ_UP_ITEM);
			else if (ch == '\n') {
				int index = item_index(current_item(menu));
				if (index >= terminals.size() || !terminals[index]) {
					populate_panel(index, screen_h, TERM_WIDTH, 0, 0);
				}
				show_panel(terminals[index]);
				hide_panel(terminals[active_panel_idx]);
				update_panels();
				doupdate();
				active_panel_idx = index;
				control = panel_window(terminals[active_panel_idx]);
			}
		} else if (ch == KEY_F(2) && control != menuwin && control != termwin) download(active_panel_idx);
		else if (ch == KEY_F(3) && control != menuwin && control != termwin) upload(active_panel_idx);
		else if (ch != ERR) rote_vt_keypress(rts[active_panel_idx], ch);
		//rote_vt_update(rt);

	}
	destroy_win(termwin);
	destroy_win(menuwin);
	endwin();

}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
    //wborder(local_win, 0, 0, 0, 0, 0, 0, 0, 0);
	//box(local_win, 0 , 0);		
					/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	refresh();
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void destroy_win(WINDOW *local_win)
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}

// int verify_knownhost(ssh_session session) {
//   int state;
//   char *hexa;
//   state = ssh_is_server_known(session);
//   char* temp_str = NULL;
//   switch (state)
//   {
//     case SSH_SERVER_KNOWN_OK:
//       break; /* ok */
//     case SSH_SERVER_KNOWN_CHANGED:
//       asprintf(&temp_str, "Host key for server changed!\n For security reasons, connection will be stopped!\n");
//       goto show_error;
//     case SSH_SERVER_FOUND_OTHER:
//       asprintf(&temp_str, "The host key for this server was not found but an other"
//         "type of key exists.\n An attacker might change the default server key to"
//         "confuse your client into thinking the key does not exist!\n");
//       goto show_error;
//     case SSH_SERVER_ERROR:
//       asprintf(&temp_str, "Error %s", ssh_get_error(session));
//       goto show_error;

//  	default: 
//  		abort();
//   }
//   return 0;

//   show_error: 
// 	rote_vt_inject(rts[active_panel_idx], temp_str, strlen(temp_str));
// 	free(temp_str);
// 	return -1;
// }

// ssh_session ssh_connect(int index) {
// 	profile_info& info = profiles[choices[index]];

//   	ssh_session my_ssh_session;
//   	int rc;
//   	char *password;
//   	char* temp_str = NULL;
//   	// Open session and set options
//   	my_ssh_session = ssh_new();
//   	if (my_ssh_session == NULL) exit(-1);
//   	ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, info.server.c_str());
//   	ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, info.port);
//   	ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, info.user.c_str());
//   	// Connect to server
//   	rc = ssh_connect(my_ssh_session);
//   	if (rc != SSH_OK)
//   	{
//   	  asprintf(&temp_str, "Error connecting to %s: %s\n", info.server.c_str(), ssh_get_error(my_ssh_session));
//   	  rote_vt_inject(rts[active_panel_idx], temp_str, strlen(temp_str));
//   	  free(temp_str);
//   	  ssh_free(my_ssh_session);
//   	  exit(-1);
//   	}
//   	// Verify the server's identity
//   	// For the source code of verify_knowhost(), check previous example
//   	if (verify_knownhost(my_ssh_session) < 0)
//   	{
//   	  ssh_disconnect(my_ssh_session);
//   	  ssh_free(my_ssh_session);
//   	  exit(-1);
//   	}
//   	// Authenticate ourselves
//   	password = info.password.c_str();
//   	rc = ssh_userauth_password(my_ssh_session, NULL, password);
//   	if (rc != SSH_AUTH_SUCCESS)
//   	{
//   	  asprintf(&temp_str, "Error authenticating with password: %s\n",
//   	          ssh_get_error(my_ssh_session));
//   	  rote_vt_inject(rts[active_panel_idx], temp_str, strlen(temp_str));
//   	  free(temp_str);
//   	  ssh_disconnect(my_ssh_session);
//   	  ssh_free(my_ssh_session);
//   	  exit(-1);
//   	}
//   	return my_ssh_session;
// }  

// int sftp_download(int index) {
// 	profile_info& info = profiles[choices[index]];

// 	//create directory in /tmp
// 	struct stat st;
// 	memset(&st, 0, sizeof(struct stat));
// 	char* path = NULL;
// 	asprintf(&path, "/tmp/%s", info.remark);
// 	if (stat(path, &st) == -1) {
//     	mkdir(path, 0700);
// 	}
// 	char* orig_path = get_current_dir_name();
// 	chdir(path);

// 	//connect sftp
// 	sftp_session sftp;
//     int rc;
//     sftp = sftp_new(session);
//     if (sftp == NULL) {
//     	rote_vt_inject(rts[active_panel_idx], "Error allocating SFTP session!\n");
//     	return SSH_ERROR;
//     }

//     int rc = sftp_init(sftp);
//     if (rc != SSH_OK) {
// 		rote_vt_inject(rts[active_panel_idx], "Error initializing SFTP session!\n");
// 		sftp_free(sftp);
// 		return rc;
// 	}

// 	//downloading

// }

// int sftp_download_dir(sftp_dir dir, sftp_session sftp, ssh_session ssh) {
// 	sftp_attributes chld_attr;
// 	while ((chld_attr = sftp_readdir(sftp, dir)) != NULL) {
// 		if (S_ISDIR(chld_attr->permissions)) {
// 			// open directory

// 		} else (S_ISREG(chld_attr->permissions)) {
// 			// open file
// 		} else (S_ISLNK(chld_attr->permissions)) {
// 			// open link
// 		}
// 	}
// }