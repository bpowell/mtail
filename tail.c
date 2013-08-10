#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define SHORTBY 5
#define HEIGHT LINES-SHORTBY
#define WIDTH COLS/2-SHORTBY

WINDOW *create_win(int height, int width, int starty, int startx);
size_t strcpy_range(char *dest, const char *src, size_t index, size_t endpos);

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

size_t strcpy_range(char *dest, const char *src, size_t index, size_t endpos)
{
	size_t start, pos;
	for(start=0, pos=index; start<endpos; start++, pos++)
	{
		dest[start] = src[pos];
	}
	dest[start] = '\0';

	return start;
}
