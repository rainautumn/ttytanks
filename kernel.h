/*
 * kernel.h
 *
 *  Created on: May 12, 2016
 *      Author: rainautumn
 */

#include <ncurses.h>

int left;
int top;

int client_id;

#define H_GAME 20
#define W_GAME 70

#define PORT 33123

void start_server();
void render_startpage();
char render_gamespace();
void render_setting_main();
void render_setting_castom();
