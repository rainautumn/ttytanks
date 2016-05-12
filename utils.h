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
#define U_WEST 3

#include <ncurses.h>

int frags;

struct tank
{
	unsigned short me_x;
	unsigned short me_y;

	unsigned short ort;

	char ride;
	char live;
};

struct boom
{
	unsigned short me_x;
	unsigned short me_y;

	unsigned short ort;

	char live;
};


void tank_reswap(short n, struct tank *t);

void tank_render(struct tank *t);
void tank_KILL(short n, struct tank *t);
int boom_render(struct boom *b_bot, struct boom *b_me, struct tank *t);
#endif /* UTILS_H_ */
