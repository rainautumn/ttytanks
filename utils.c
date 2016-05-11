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


int boom_render(struct boom *b_bot, struct boom *b_me, struct tank *t)
{
    for (unsigned char i = 0; i <= 254; i++)
        {
        //recalc position
        switch (b_bot[i].ort)
        {
        case U_NORTH:
            b_bot[i].me_y -= 1;
            break;
        case U_SOUTH:
            b_bot[i].me_y += 1;
            break;
        case U_WEST:
            b_bot[i].me_x -= 1;
            break;
        case U_EAST:
            b_bot[i].me_x += 1;
            break;
        default:
            break;
        }

        switch (b_me[i].ort)
        {
        case U_NORTH:
            b_me[i].me_y -= 1;
            break;
        case U_SOUTH:
            b_me[i].me_y += 1;
            break;
        case U_WEST:
            b_me[i].me_x -= 1;
            break;
        case U_EAST:
            b_me[i].me_x += 1;
            break;
        default:
            break;
        }
        //calc
            if(b_bot[i].live == 'Y' || b_me[i].live == 'Y' )
            {
                for(char k = 0; k < 4; k++)
                {
                    if(abs(t[k].me_x - b_bot[i].me_x) <= 1 && abs(t[k].me_y - b_bot[i].me_y) <=1 && t[k].live == 'Y' && b_bot[i].live == 'Y')
                    {
                        t[k].live = 'N';
                        b_bot[i].live = 'N';
                    }
                    if(abs(t[k].me_x - b_me[i].me_x) <= 1 && abs(t[k].me_y - b_me[i].me_y) <=1 && t[k].live == 'Y' && b_me[i].live == 'Y')
                    {
                        t[k].live = 'N';
                        b_me[i].live = 'N';
                        frags++;
                    }
                }
                for (unsigned char j = i; j <= 254; j++)
                    if(b_bot[i].me_x == b_bot[j].me_x && b_bot[i].me_y == b_bot[j].me_y)
                    {
                        if(i!=j)
                        {
                            b_bot[i].live = 'N';
                            b_bot[j].live = 'N';
                        }
                    }
                for (unsigned char j = 0; j <= 254; j++)
                    if(b_bot[i].me_x == b_me[j].me_x && b_bot[i].me_y == b_me[j].me_y)
                    {
                        b_bot[i].live = 'N';
                        b_me[j].live = 'N';
                    }
            }


            //render

            if(b_bot[i].live == 'Y')
                mvaddch(b_bot[i].me_y,   b_bot[i].me_x, '#');
            if(b_me[i].live == 'Y')
                mvaddch(b_me[i].me_y,   b_me[i].me_x, '#');

        }
}
