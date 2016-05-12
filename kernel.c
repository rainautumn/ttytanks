/*
 * kernel.c
 *
 *  Created on: May 12, 2016
 *      Author: rainautumn
 */

#include "kernel.h"

void render_startpage()
{
	mvaddstr(top + H_GAME/2-6, left + W_GAME/2 -6 ,"TTY TANKS");
	mvaddstr(top + H_GAME/2-2, left + 5 ,"1 connect to server");
	mvaddstr(top + H_GAME/2-1, left + 5 ,"2 create server");
	mvaddstr(top + H_GAME/2-0, left + 5 ,"3 game with bots");
	mvaddstr(top + H_GAME/2+1, left + 5 ,"4 settings");
	mvaddstr(top + H_GAME/2+2, left + 5 ,"5 about this game");
	mvaddstr(top + H_GAME/2+3, left + 5 ,"0 exit");

	mvaddstr(top + H_GAME/2-8, left + 50 ,"  ##  ");
	mvaddstr(top + H_GAME/2-7, left + 50 ,"  ##  ");
	mvaddstr(top + H_GAME/2-1, left + 50 ,"  ##  ");
	mvaddstr(top + H_GAME/2  , left + 50 ,"  ##  ");
	mvaddstr(top + H_GAME/2+1, left + 50 ,"######");
	mvaddstr(top + H_GAME/2+2, left + 50 ,"######");
	mvaddstr(top + H_GAME/2+3, left + 50 ,"##  ##");
	mvaddstr(top + H_GAME/2+4, left + 50 ,"##  ##");
	mvaddstr(LINES-2,0,"#");
}

char render_gamespace()
{
	erase();
	left = COLS - W_GAME - 1;
	if(left < 0)
		return 'E';
	for(int i = 0; i < left; i++)
		for(int j = 0; j < LINES-3; j++)
			mvaddstr(j,i, "#");

	int right = COLS - 1;
		for(int j = 0; j < LINES; j++)
			mvaddstr(j,right, "#");

	top = LINES - H_GAME - 3;
	if(top < 0)
		return 'E';
	for(int i = 0; i < top; i++)
			for(int j = 0; j < COLS; j++)
				mvaddstr(i,j, "#");

	for(int i = 0; i < COLS; i++)
		mvaddstr(LINES-1,i, "#");
	for(int i = 0; i < COLS; i++)
		mvaddstr(LINES-3,i, "#");
}

void render_setting_main()
{
	mvaddstr(top + H_GAME/2-1, left + 5 ,"1 network game");
	mvaddstr(top + H_GAME/2+0, left + 5 ,"0 return");
	mvaddstr(LINES-2,0,"#");
}

void render_setting_castom()
{
	mvaddstr(top + H_GAME/2-1, left + 5 ,"1 server port");
	mvaddstr(top + H_GAME/2+0, left + 5 ,"0 return");
}
