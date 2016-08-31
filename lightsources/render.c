/*
 * render.c
 *
 *  Created on: Oct 29, 2015
 *      Authors: rainautumn
 * Contributors: DmitryHetman
 */

#include "render.h"

void tank_reswap(uint_fast8_t n, struct tank *t)
		{
		switch (n)
			{
			case 0: //my tank

//orientation works only for my tank and for left tank
				t->live = 1;
                                        //H_GAME-1, 19 now
				t->me_y = 18; // y position
				t->me_x = 30; // x postiion
				t->ort =  U_SOUTH;
				t->ride = 0;

			  break;
			case 1:  //left tank

				t->live = 1;
				t->me_y = 10;
				t->me_x = 4;
				t->ort  = U_WEST;
				t->ride = 0;

			  break;
			case 2:  //top tank


				t->live = 1;
				t->me_y = 3;
				t->me_x = 35;
				t->ort  = U_EAST; //U_NORTH not works
				t->ride = 0;

			  break;
			case 3:  //right tank

				t->live = 1;
				t->me_y = 10;
                                          //W_GAME-2 was here, 69 now
				t->me_x = 68;
				t->ort =  U_EAST;
				t->ride = 0;

			  break;
			default:
		  break;
			}
		}

void tank_render(struct tank *t)
{
	if(t->live)
	{
		switch (t->ort)
			{
		  case U_NORTH:    //if w pressed
				if (t->ride  && t->me_y > 2 ) //last digit is border
					t->me_y--; //move tank up
//render tank
//better do it with strings, only 3-4 commands need if use strings.
//use only mvadaddstr
uint_fast8_t x=t->me_x-1; //calculate x position one time
                mvaddstr(t->me_y-1,x," # ");
                mvaddstr(t->me_y  ,x,"###");
		mvaddstr(t->me_y+1,x,"# #");
                mvaddstr(t->me_y+2,x,"   "); //clear space after tank
			break;

		  case U_EAST:                                 //W_GAME
		         if (t->ride && t->me_x < 69) //last digit is border for tanks
		         t->me_x++; //move right
                //render tank turned to right
                x=t->me_x-2;
                mvaddstr(t->me_y-1,x," ## ");
                mvaddstr(t->me_y  ,x,"  ##");
                mvaddstr(t->me_y+1,x," ## ");
			break;

		  case U_SOUTH:
		       if (t->ride && t->me_y < 19) //last digit is border for tanks
		       t->me_y++;   //move down
                //render tank:
                x=t->me_x-1;
                mvaddstr(t->me_y-2,x,"   ");
                mvaddstr(t->me_y-1,x,"# #");
                mvaddstr(t->me_y  ,x,"###");
                mvaddstr(t->me_y+1,x," # ");
	        break;

		  case U_WEST:
				//if tank rides and not reach a border
				if (t->ride  && t->me_x > 2) //border for game
				t->me_x--; //move tank left
                //render tank
		x=t->me_x-1;
                mvaddstr(t->me_y-1,x," ## ");
                mvaddstr(t->me_y  ,x,"##  ");
                mvaddstr(t->me_y+1,x," ## ");
			break;
			}
		t->ride=0;
		}
}


void boom_render(struct boom *b_bot, struct boom *b_me, struct tank *t)
/* render player and bot boolets at the same time
 */
{
//fix this fucking bug!
//i - is not a distance for bullet to fly, it's number of bullets that you can shoot
//bullets fly endless
//make border for bullets, just like for tanks
    for ( uint_fast8_t i=0; i <= 253; i++) // i is number ob bullets that you can shoot, haha.
        {
        //recalc position
        switch (b_bot[i].ort) //bot tank shooting
        {
        case U_NORTH:           //shoot up
            if (b_bot[i].me_y>1)
                b_bot[i].me_y--; //change position of bullet, you need it only if b_bot[].me_y < H_GAME
            else
                 b_bot[i].live = 0;              //remove from gamespace;
            break;
        case U_SOUTH:   //shoot down
            if (b_bot[i].me_y<20)
                b_bot[i].me_y++;
            else
                b_bot[i].live = 0;
            break;
        case U_WEST: //shoot to left
            if (b_bot[i].me_x>1)
                b_bot[i].me_x--;
            else
                b_bot[i].live = 0;
            break;
        case U_EAST:
            if (b_bot[i].me_x<70)
                 b_bot[i].me_x++; //70 is barrier for bots
             else
                 b_bot[i].live =0;
            break;
        default:
            break;
        }

      switch (b_me[i].ort) //my tank shooting
      {
         case U_NORTH: //shoot up
           if (b_me[i].me_y>1)
               b_me[i].me_y--;
           else
               b_me[i].live = 0;
         break;
        case U_SOUTH:  //shoot down
            if (b_me[i].me_y < 20)
                b_me[i].me_y++; //shoot if boolet not reaches the border;
	    else
                b_me[i].live = 0;  //better remove this variable
         break;
        case U_WEST:
            if (b_me[i].me_x > 1)
                b_me[i].me_x--;
            else
                b_me[i].live = 0; //remove from gamespace, better delete it.
        break;
        case U_EAST:
            if (b_me[i].me_x < 70)
                b_me[i].me_x++;
            else
                b_me[i].live = 0; //remove from gamespace
        break;
        default:
        break;
     }
        //calc
            if (b_bot[i].live || b_me[i].live)
            {
                for(uint_fast8_t k = 0; k < 4; k++)
                {
                    //kill tank or bot? why abs() is used?
                    if(abs(t[k].me_x - b_bot[i].me_x) <= 1 && abs(t[k].me_y - b_bot[i].me_y) <=1 && t[k].live && b_bot[i].live)
                    {
                        t[k].live = 0;
                        b_bot[i].live = 0;
                    }
                    for(uint_fast8_t n = 0; n < 4; n++)
                    	if(abs(t[k].me_x - t[n].me_x) <= 1 &&
						   abs(t[k].me_y - t[n].me_y) <= 1 && //what is that?
						   t[k].live &&
						   t[n].live &&
						   k != n)
						{
							t[k].live = 0;
							t[n].live = 0;
						}

                    if(abs(t[k].me_x - b_me[i].me_x) <= 1 && abs(t[k].me_y - b_me[i].me_y) <=1 && t[k].live && b_me[i].live)
                    {
                        t[k].live = 0;
                        b_me[i].live = 0;
                        frags++;
                    }
                }
                for (uint_fast8_t j = i; j < 255; j++)
                    if(b_bot[i].me_x == b_bot[j].me_x && b_bot[i].me_y == b_bot[j].me_y && b_bot[i].live && b_bot[j].live )
                    {
                        if(i!=j)
                        {
                            b_bot[i].live = 0;
                            b_bot[j].live = 0;
                        }
                    }
                for (uint_fast8_t j = 0; j < 255; j++)
                    if(b_bot[i].me_x == b_me[j].me_x && b_bot[i].me_y == b_me[j].me_y && b_bot[i].live && b_me[j].live )
                    {
                        b_bot[i].live = 0; //kill
                        b_me[j].live = 0;
                    }
            }


            //render

            if(b_bot[i].live)
             //{//ugly boolet rendering and  if this curly braces here,
                //if remove it boolet will be rendered fine.
                mvaddch(b_bot[i].me_y,b_bot[i].me_x,'o');
		mvaddch(b_bot[i+1].me_y,b_bot[i+1].me_x,' ');
             //}
//fill area behind boolet with spaces
            if(b_me[i].live)
           //{// same shit with this  curly braces
	    mvaddch(b_me[i].me_y,b_me[i].me_x,'o');
            mvaddch(b_me[i+1].me_y,b_me[i+1].me_x,' ');
           //} //try to compile it with and without this braces;

        }
}
