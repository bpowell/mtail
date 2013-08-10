#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define SHORTBY 5
#define HEIGHT LINES-SHORTBY
#define WIDTH COLS/2-SHORTBY

WINDOW *create_win(int height, int width, int starty, int startx);
size_t strcpy_range(char *dest, const char *src, size_t index, size_t endpos);
void *tail_thread(void *p);

struct tpackage{
	WINDOW *win;
	char filename[128];
};

typedef struct tpackage package;

int main(int argc, char* argv[])
{
	package win0;
	package win1;
	pthread_t threads[2];

	//ncurses setup
	initscr();
	cbreak();
	refresh();

	win0.win = create_win(HEIGHT,WIDTH,0,0);
	strcpy(win0.filename, "log0.txt");
	win1.win = create_win(HEIGHT,WIDTH,0,WIDTH+SHORTBY);
	strcpy(win1.filename, "log1.txt");

	int rc0 = pthread_create(&threads[0], NULL, tail_thread, &win0);
	if(rc0){exit(-1);}
	int rc1 = pthread_create(&threads[1], NULL, tail_thread, &win1);
	if(rc1){exit(-2);}

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

void *tail_thread(void *p)
{
	package *pkg = p;
	char cmd[256];
	char buffer[512];
	FILE *cmd_output;

	strcpy(cmd, "tail -f ");
	strcat(cmd, pkg->filename);

	cmd_output = popen(cmd, "r");
	while(fgets(buffer, 512, cmd_output)!=NULL){
		wprintw(pkg->win, buffer);
		wrefresh(pkg->win);
	}
}
