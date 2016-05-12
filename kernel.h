/*
 * kernel.h
 *
 *  Created on: May 12, 2016
 *      Author: rainautumn
 */

#include <ncurses.h>
int left;
int top;

#define H_GAME 20
#define W_GAME 70

void render_startpage();
char render_gamespace();
