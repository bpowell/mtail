#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define SHORTBY 5
#define HEIGHT LINES-SHORTBY
#define WIDTH COLS/2-SHORTBY

WINDOW *create_win(int height, int width, int starty, int startx);

struct tpackage{
	WINDOW *win;
	char filename[128];
};

typedef struct tpackage package;

int main(int argc, char* argv[])
{
	//ncurses setup
	initscr();
	cbreak();
	refresh();

	package win1;
	win1.win = create_win(HEIGHT,WIDTH,0,0);

	package win2;
	win2.win = create_win(HEIGHT,WIDTH,0,WIDTH+SHORTBY);

	while(true){}

	//teardown ncurses
	endwin();
	return 0;
}

WINDOW *create_win(int height, int width, int starty, int startx)
{
	WINDOW *win;
	win = newwin(height, width, starty, startx);
	box(win, 0, 0);

	wrefresh(win);
	return win;
}
