/*
 * render.h
 *
 *   Created on: Oct 29, 2015
 *       Author: rainautumn
 * Contributros: DmitryHetman
 */

#ifndef RENDER_H_
#define RENDER_H_

#define U_NORTH 0
#define U_EAST 1
#define U_SOUTH 2
#define U_WEST 3

#include <ncurses.h>
#include <stdlib.h> //for math.h
#include <stdint.h>
#include <math.h> //better remove it if possible.
#include <unistd.h>
//#include <math.h> warning occur whatever i do with this lib
uint_fast8_t frags; //uint fastest value at least 0-255 (one byte), on amd64 fastest 8-bit value, that uses 8-bit registers.

struct tank
{
	uint_fast8_t me_x;
	uint_fast8_t me_y;
	uint_fast8_t ort;

	bool ride;  //mame booolean var here
	bool live;  //make boolean variable here
};

struct boom
{
	uint_fast8_t me_x;
	uint_fast8_t me_y;
	uint_fast8_t ort;

	bool live; //make boolean variable here
};


void tank_reswap(uint_fast8_t n, struct tank *t);

void tank_render(struct tank *t);
void boom_render(struct boom *b_bot, struct boom *b_me, struct tank *t);
#endif /* RENDER_H_ */
