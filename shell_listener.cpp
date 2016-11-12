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

extern "C" 
{
	#include <rote/rote.h>
	#include <ncurses.h>
}


shell_listener* shell_listener::singleton = NULL;

RoteTerm* rt;
char buf[BUFSIZ];
int screen_w, screen_h;

static unsigned char getout = 0;
void sigchld(int signo) { getout = 1; }

shell_listener::shell_listener() {
	if (singleton) {
		fprintf(stderr, "%s\n", "Only one instance is allowed");
	}
	singleton = this;
	init();
}

void shell_listener::init() {
	signal(SIGCHLD, sigchld);
	initscr();
    noecho();
    start_color();
    raw();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, screen_h, screen_w);
    
    mvwprintw(stdscr, 0, 27, " SSH Integrated ");
    wrefresh(stdscr);

	rt = rote_vt_create(screen_h - 1, screen_w);
	rote_vt_forkpty(rt, "/bin/bash --login");

}

void shell_listener::run() {
	int ch = 0;
	while (!getout) {
		rote_vt_draw(rt, stdscr, 1, 1, NULL);
		wrefresh(stdscr);

		ch = getch();
		if (ch != ERR) {
			rote_vt_keypress(rt, ch);
		}
		rote_vt_update(rt);
	}
	endwin();

}

