/*
 * utils.h
 *
 *   Created on: Oct 29, 2015
 *       Author: rainautumn
 * Contributors: DmitryHetman
 */

#ifndef UTILS_H_
#define UTILS_H_

#define U_NORTH 0
#define U_EAST 1
#define U_SOUTH 2
#define U_WEST 3

#include <ncurses.h>
//#include <math.h> //for abs(); no need in it.
#include <stdint.h>
uint_fast8_t frags; //fastest variable for this CPU, at least 8-bit (max value 255), just integer slow on amd64, long faster than int.

struct tank
{
    char *skin;
	uint_fast8_t me_x;
	uint_fast8_t me_y;
	uint_fast8_t ort; //U_NORTH, U_EAST, U_SOUTH, U_WEST will be here
	//1 and 0 used for boolean values, not true and false.
	bool ride; //make boolean value here, 0, false - deat, 1, true - live, if you want to check condition
                   //don't type if (me.ride = 1), just if (me.ride)
	bool live; //make boolean value here
};

struct boom
{
	uint_fast8_t me_x;
	uint_fast8_t me_y;
	uint_fast8_t ort;

	bool live; //make boolean value here 0 - dead, 1 - live
};


void tank_reswap(short n, struct tank *t);

void tank_render(struct tank *t);
//void tank_KILL(short n, struct tank *t); function not exist
void boom_render(struct boom *b_bot, struct boom *b_me, struct tank *t);
#endif /* UTILS_H_ */
