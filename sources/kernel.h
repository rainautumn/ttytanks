/*
 * kernel.h
 *
 *   Created on: May 12, 2016
 *       Author: rainautumn
 * Contributors: DmitryHetman
 */

#include <ncurses.h>
#include <stdint.h>

uint_fast8_t left;
uint_fast8_t top;

uint_fast8_t client_id;

#define H_GAME 20
#define W_GAME 70

#define PORT 33123

void start_server();
void render_startpage();
void render_gamespace();
void render_setting_main();
void render_setting_castom();
