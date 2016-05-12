/*
 * kernel.c
 *
 *  Created on: May 12, 2016
 *      Author: rainautumn
 */

#include "kernel.h"

void render_startpage()
{
	mvaddstr(top + H_GAME/2-1,left + W_GAME/2 - 6,"PRESS ANY KEY");
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
