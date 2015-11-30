/*
 * utils.h
 *
 *  Created on: Oct 29, 2015
 *      Author: rainautumn
 */

#ifndef UTILS_H_
#define UTILS_H_

#define U_NORTH 0
#define U_EAST 1
#define U_SOUTH 2
#define U_WEST 3 // направления взгляда танка

#include <ncurses.h>

struct tank
{
	unsigned short me_x;
	unsigned short me_y;

	unsigned short ort; // направлениe взгляда танка

	char ride;
	char live;
};

struct boom
{
	unsigned short me_x;
	unsigned short me_y;

	unsigned short ort; // направлениe полёта снаряда

	char live;
};


void tank_reswap(short n, struct tank *t);

void tank_render(struct tank *t);
void tank_KILL(short n, struct tank *t);

void boom_render(struct boom *b, struct tank *t1, struct tank *t2, struct tank *t3 , struct tank *t4);

#endif /* UTILS_H_ */
