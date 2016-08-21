 /*
 * utils.c
 *
 *   Created on: Oct 29, 2015
 *       Author: rainautumn
 * Contributors: DmitryHetman
 */

#include "utils.h"
//#include <stdio.h> //why??
//#include <stdint.h>
#include "kernel.h"


void tank_reswap(short n, struct tank *t)
		{
                uint_fast8_t lin=LINES/2+10;
		switch (n)
			{
			case 0:
//				mvaddstr(lin-1,0,"tank #0 reswap"); //not works


				t->live = 1; // = true
				t->me_y = lin-5;
				t->me_x = left + 30;
				t->ort =  U_NORTH;
				t->ride = 0; //bool, false

			  break;
			case 1:
//				mvaddstr(lin-1,0,"tank #1 reswap");

				t->live = 1;
				t->me_y = top + 10;
				t->me_x = left + 1;
				t->ort =  U_EAST;
				t->ride = 0;

			  break;
			case 2:
//				mvaddstr(lin-1,0,"tank #2 reswap");


				t->live = 1;
				t->me_y = top + 1;
				t->me_x = left + 40;
				t->ort =  U_SOUTH;
				t->ride = 0;

			  break;
			case 3:
//				mvaddstr(lin-1,0,"tank #3 reswap");

				t->live = 1;
				t->me_y = top + 10;
				t->me_x = left + W_GAME - 2;
				t->ort =  U_WEST;
				t->ride = 0;

			  break;
			default:
			  return;
		  break;
			}
		return;
		}

void tank_render(struct tank *t)
{
uint_fast8_t lin=LINES/2+10;
uint_fast8_t col=COLS/2+35;
//    char t->skin = '^';
	if(t->live) // t->live is bool
	{
		switch (t->ort)
			{
		  case U_NORTH:
				if (t->ride && t->me_y > 1 + top)
					t->me_y-=1;
//render tank
//better do it with strings, if use strings code will be very small, and fast
//use only mvaddstr, delete t->skin;?
//you need to fill front of tank with spaces, left and right from borell
                mvaddch(t->me_y, t->me_x,   t->skin);
                mvaddch(t->me_y, t->me_x-1, t->skin);
                mvaddch(t->me_y, t->me_x+1, t->skin);
                mvaddch(t->me_y-1, t->me_x,   t->skin);
                mvaddch(t->me_y+1, t->me_x-1, t->skin);
                mvaddch(t->me_y+1, t->me_x+1, t->skin);
//fill free area with spaces move it up better
		mvaddch(t->me_y+1,t->me_x,' ');
                mvaddstr(t->me_y+2,t->me_x-1,"   ");
			break;

		  case U_EAST:
				if (t->ride && t->me_x < col-3) //t->ride is bool
					t->me_x+=1;
                mvaddch(t->me_y,   t->me_x, t->skin);
                mvaddch(t->me_y-1, t->me_x, t->skin);
                mvaddch(t->me_y+1, t->me_x, t->skin);
                mvaddch(t->me_y,   t->me_x+1, t->skin);
                mvaddch(t->me_y-1, t->me_x-1, t->skin);
                mvaddch(t->me_y+1, t->me_x-1, t->skin);
//fill free area with spaces
uint_fast8_t x=t->me_x-2;
		mvaddch(t->me_y-1,x,' ');
		mvaddch(t->me_y+1,x,' ');
		mvaddstr(t->me_y,x,"  "); //center
			break;

		  case U_SOUTH:
				if (t->ride && t->me_y < lin-5)
					t->me_y+=1;
                mvaddch(t->me_y, t->me_x,   t->skin);
                mvaddch(t->me_y, t->me_x-1, t->skin);
                mvaddch(t->me_y, t->me_x+1, t->skin);
                mvaddch(t->me_y+1, t->me_x,   t->skin);
                mvaddch(t->me_y-1, t->me_x-1, t->skin);
                mvaddch(t->me_y-1, t->me_x+1, t->skin);
//fill free area with spaces
//better move it up
		mvaddch(t->me_y-1,t->me_x,' '); //center
		mvaddstr(t->me_y-2,t->me_x-1,"   "); //area after tank
			break;

		  case U_WEST:
				if (t->ride  && t->me_x > 1 + left)
					t->me_x-=1;
                mvaddch(t->me_y,   t->me_x, t->skin);
                mvaddch(t->me_y-1, t->me_x, t->skin);
                mvaddch(t->me_y+1, t->me_x, t->skin);
                mvaddch(t->me_y,   t->me_x-1, t->skin);
                mvaddch(t->me_y-1, t->me_x+1, t->skin);
                mvaddch(t->me_y+1, t->me_x+1, t->skin);
//fill free area with spaces
x=t->me_x+2;
                mvaddstr(t->me_y,x-1,"  "); //center
		mvaddch(t->me_y+1,x,' ');
		mvaddch(t->me_y-1,x,' ');
			break;
			}
		t->ride=0;
		}
}


void boom_render(struct boom *b_bot, struct boom *b_me, struct tank *t)
{
//fix this fucking bug!
//i - is not a distance for bullet to fly, it's number of bullets that you can shoot
//bullets fly endless
    for ( uint_fast8_t i=0; i <= 233; i++)
        {
        //recalc position
        switch (b_bot[i].ort)
        {
        case U_NORTH:
//	if(b_bot[i].me_y > LINES/2+10)
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
        case U_NORTH: //shoot up
            if(b_me[i].me_y < LINES/2+3) //almost works
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
            if(b_bot[i].live || b_me[i].live ) //bool values
            {
                for(uint_fast8_t k = 0; k < 4; k++)
                {
                    if(abs(t[k].me_x - b_bot[i].me_x) <= 1 && abs(t[k].me_y - b_bot[i].me_y) <=1 && t[k].live && b_bot[i].live)
                    {
                        t[k].live = 0; //false
                        b_bot[i].live = 0;
                    }
                    for(uint_fast8_t n = 0; n < 4; n++)
                    	if(abs(t[k].me_x - t[n].me_x) <= 1 &&
						   abs(t[k].me_y - t[n].me_y) <= 1 &&
						   t[k].live &&
						   t[n].live &&
						   k != n)
						{
							t[k].live = 0; //false, dead
							t[n].live = 0;
						}

                    if(abs(t[k].me_x - b_me[i].me_x) <= 1 && abs(t[k].me_y - b_me[i].me_y) <=1 && t[k].live && b_me[i].live)
                    {
                        t[k].live = 0;
                        b_me[i].live = 0;
                        frags++;
                    }
                }
                for (uint_fast8_t j = i; j <= 254; j++)
                    if(b_bot[i].me_x == b_bot[j].me_x && b_bot[i].me_y == b_bot[j].me_y && b_bot[i].live && b_bot[j].live)
                    {
                        if(i!=j)
                        {
                            b_bot[i].live = 0;
                            b_bot[j].live = 0;
                        }
                    }
                for (uint_fast8_t j = 0; j <= 254; j++)
                    if(b_bot[i].me_x == b_me[j].me_x && b_bot[i].me_y == b_me[j].me_y && b_bot[i].live && b_me[j].live)
                      {
                        b_bot[i].live = 0;
                        b_me[j].live = 0;
                      }
            }


            //render

            if(b_bot[i].live) //bool
              {//fix bad boolet rendering, or fix bad game rendering when this curly braces commented.
                mvaddch(b_bot[i].me_y,b_bot[i].me_x,'o');
		mvaddch(b_bot[i+1].me_y,b_bot[i+1].me_x,' ');
              }
//fill area behind boolet with spaces
//it works!
//no need in clear(); for boolet rendering now
              if(b_me[i].live)//bool, so you don't need to compare
              {
	      mvaddch(b_me[i].me_y,b_me[i].me_x,'o');
              mvaddch(b_me[i+1].me_y,b_me[i+1].me_x,' ');
              }

        }
}
