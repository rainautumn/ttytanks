/*
 * utils.c
 *
 *  Created on: Oct 29, 2015
 *      Author: rainautumn
 */

#include "utils.h"
#include <stdio.h>


void tank_reswap(short n, struct tank *t)
		{
		switch (n)
			{
			case 0:
				mvaddstr(LINES-1,0,"tank #0 reswap");


				t->live = 'Y';
				t->me_y = LINES-2;
				t->me_x = COLS/2;
				t->ort =  U_NORTH;
				t->ride = 'N';

			  break;
			case 1:
				mvaddstr(LINES-1,0,"tank #1 reswap");

				t->live = 'Y';
				t->me_y = LINES/2;
				t->me_x = 1;
				t->ort =  U_EAST;
				t->ride = 'N';

			  break;
			case 2:
				mvaddstr(LINES-1,0,"tank #2 reswap");


				t->live = 'Y';
				t->me_y = 1;
				t->me_x = COLS/2;
				t->ort =  U_SOUTH;
				t->ride = 'N';

			  break;
			case 3:
				mvaddstr(LINES-1,0,"tank #3 reswap");

				t->live = 'Y';
				t->me_y = LINES/2;
				t->me_x = COLS-2;
				t->ort =  U_WEST;
				t->ride = 'N';

			  break;
			default:
			  return;
			  break;
			}
		}

void tank_render(struct tank *t)
{
	char pixel = '#';
	if(t->live == 'Y')
	{
		switch (t->ort)
			{
		  case U_NORTH:
				if (t->ride == 'Y' && t->me_y > 1)
					t->me_y-=1;
				mvaddch(t->me_y, t->me_x,   pixel);
				mvaddch(t->me_y, t->me_x-1, pixel);
				mvaddch(t->me_y, t->me_x+1, pixel);
				mvaddch(t->me_y-1, t->me_x,   pixel);
				mvaddch(t->me_y+1, t->me_x-1, pixel);
				mvaddch(t->me_y+1, t->me_x+1, pixel);
			break;

		  case U_EAST:
				if (t->ride == 'Y' && t->me_x < COLS-2)
					t->me_x+=1;
				mvaddch(t->me_y,   t->me_x, pixel);
				mvaddch(t->me_y-1, t->me_x, pixel);
				mvaddch(t->me_y+1, t->me_x, pixel);
				mvaddch(t->me_y,   t->me_x+1, pixel);
				mvaddch(t->me_y-1, t->me_x-1, pixel);
				mvaddch(t->me_y+1, t->me_x-1, pixel);
			break;

		  case U_SOUTH:
				if (t->ride == 'Y' && t->me_y < LINES-2)
					t->me_y+=1;
				mvaddch(t->me_y, t->me_x,   pixel);
				mvaddch(t->me_y, t->me_x-1, pixel);
				mvaddch(t->me_y, t->me_x+1, pixel);
				mvaddch(t->me_y+1, t->me_x,   pixel);
				mvaddch(t->me_y-1, t->me_x-1, pixel);
				mvaddch(t->me_y-1, t->me_x+1, pixel);
			break;

		  case U_WEST:
				if (t->ride == 'Y'  && t->me_x > 1)
					t->me_x-=1;
				mvaddch(t->me_y,   t->me_x, pixel);
				mvaddch(t->me_y-1, t->me_x, pixel);
				mvaddch(t->me_y+1, t->me_x, pixel);
				mvaddch(t->me_y,   t->me_x-1, pixel);
				mvaddch(t->me_y-1, t->me_x+1, pixel);
				mvaddch(t->me_y+1, t->me_x+1, pixel);
			break;
			}
		t->ride='N';
		}
}

void boom_render(struct boom *b, struct tank *t1, struct tank *t2, struct tank *t3 , struct tank *t4)
{
	if(b->live == 'Y')
	{
		for(int k = 0; k < 4; k++)
		{
			if(abs(t1->me_x - b->me_x) <= 1 && abs(t1->me_y - b->me_y) <=1)
				t1->live = 'N';
			if(abs(t2->me_x - b->me_x) <= 1 && abs(t2->me_y - b->me_y) <=1)
				t2->live = 'N';
			if(abs(t3->me_x - b->me_x) <= 1 && abs(t3->me_y - b->me_y) <=1)
				t3->live = 'N';
			if(abs(t4->me_x - b->me_x) <= 1 && abs(t4->me_y - b->me_y) <=1)
				t4->live = 'N';
		}

	}
	if(b->live == 'Y' && (b->ort == U_NORTH || b->ort == U_SOUTH))
		mvaddch(b->me_y,   b->me_x, '#');

	if(b->live == 'Y' && (b->ort == U_WEST || b->ort == U_EAST))
		mvaddch(b->me_y,   b->me_x, '#');


	if(b->live == 'Y' && b->ort == U_NORTH)
	{
		b->me_y -= 1;
		if(b->me_y < 0)
		{
			b->live = 'N';
		}
	}

	if(b->live == 'Y' && b->ort == U_SOUTH)
	{
		b->me_y += 1;
		if(b->me_y > LINES)
		{
			b->live = 'N';
		}
	}

	if(b->live == 'Y' && b->ort == U_WEST)
	{
		b->me_x -= 1;
		if(b->me_x < 0)
		{
			b->live = 'N';
		}
	}

	if(b->live == 'Y' && b->ort == U_EAST)
	{
		b->me_x += 1;
		if(b->me_x > COLS)
		{
			b->live = 'N';
		}
	}
}
