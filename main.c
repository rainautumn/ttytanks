/*
 * main.c
 *
 *  Created on: Oct 29, 2015
 *      Author: rainautumn
 */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include <math.h>


#define ME_TANK 0
#define BOT_TANK_1 1
#define BOT_TANK_2 2
#define BOT_TANK_3 3

#define SLEEP_BOTS_CONST 1000000

    unsigned char num_of_boom_bot = 0;
    unsigned char num_of_boom_me = 0;
	struct tank t[4];
    struct boom b_bot[256];
    struct boom b_me[256];


void render_all(void)
{

	erase();
	for(short k = 0; k < 4; k++ )
			tank_render(&t[k]);
    boom_render(&b_bot, &b_me, &t);
    mvaddstr(LINES-1,0,"frags : ");
    printw("%i", frags);
	return;
}

void start_game(void)
{
	for(short k = 0; k < 4; k++ )
		tank_reswap(k, &t[k]);
	render_all();
    return;
}

void *thread_BOTS(void *arg)
{
    for(;;)
    {
        for(int n = 1; n <4; n ++ )
        {
                t[n].ort = rand() % 4;

            unsigned char ridebot = rand() % 10;
            if (ridebot > 2)
                t[n].ride = 'Y';
            unsigned char boombot = rand() % 10;
            if (boombot > 2 && t[n].live == 'Y')
            {
                num_of_boom_bot += 1;
                b_bot[num_of_boom_bot].ort  = t[n].ort;
                b_bot[num_of_boom_bot].me_x = t[n].me_x;
                b_bot[num_of_boom_bot].me_y = t[n].me_y;
                b_bot[num_of_boom_bot].live = 'Y';

                switch (t[n].ort)
                {
                case U_NORTH:
                    b_bot[num_of_boom_bot].me_y -= 3;
                    break;
                case U_SOUTH:
                    b_bot[num_of_boom_bot].me_y += 3;
                    break;
                case U_WEST:
                    b_bot[num_of_boom_bot].me_x -= 3;
                    break;
                case U_EAST:
                    b_bot[num_of_boom_bot].me_x += 3;
                    break;
                default:
                    break;
                }
            }
        }
	int lvl_speed = SLEEP_BOTS_CONST/log(frags+ 2);
        usleep(lvl_speed);
	}

	return 0;
}
int main(void)
{
    frags = 0;

    initscr();

	mvaddstr(LINES/2-1,COLS/2 - 6,"PRESS ANY KEY");
	getch();
	halfdelay(1);
	erase();

    pthread_t bot1;
    int id1;
	int result;


	id1 = 1;
    result = pthread_create(&bot1, NULL, thread_BOTS, &id1);
	if (result != 0)
	{
		perror("Creating the first thread");
		return -1;
	}


    start_game();

	while(1)
	{
		char key = getch();
		if(key == 'w' || key == 'W')
		{
			t[ME_TANK].ride='Y';
			t[ME_TANK].ort=U_NORTH;
		}

		if(key == 'a' || key == 'A')
		{
			t[ME_TANK].ride='Y';
			t[ME_TANK].ort=U_WEST;
		}

		if(key == 's' || key == 'S')
		{
			t[ME_TANK].ride='Y';
			t[ME_TANK].ort=U_SOUTH;
		}

		if(key == 'd' || key == 'D')
		{
			t[ME_TANK].ride='Y';
			t[ME_TANK].ort=U_EAST;
		}
		if(key == ' ')
		{
            num_of_boom_me += 1;
            b_me[num_of_boom_me].ort=t[ME_TANK].ort;
            b_me[num_of_boom_me].me_x=t[ME_TANK].me_x;
            b_me[num_of_boom_me].me_y=t[ME_TANK].me_y;

            switch (t[ME_TANK].ort)
            {
            case U_NORTH:
                b_me[num_of_boom_me].me_y -= 3;
                break;
            case U_SOUTH:
                b_me[num_of_boom_me].me_y += 3;
                break;
            case U_WEST:
                b_me[num_of_boom_me].me_x -= 3;
                break;
            case U_EAST:
                b_me[num_of_boom_me].me_x += 3;
                break;
            default:
                break;
            }
            b_me[num_of_boom_me].live='Y';
            usleep(10000);
		}

			short kills = 0;

			if(t[0].live == 'N')
			{
				erase();
				cbreak();
                mvaddstr(LINES/2-2,COLS/2 - 4,  "GAME OVER");
				mvaddstr(LINES/2-1,COLS/2 - 6,"PRESS ANY KEY");
				getch();
				halfdelay(1);
                for(unsigned char i = 0; i <= 254; i++)
                {
                    b_me[i].live = 'N';
                    b_bot[i].live = 'N';
                }
				start_game();
                frags = 0;
			}
			for(int k = 0; k<4; k++)
				if (t[k].live == 'N')
					kills += 1;
			if(kills >= 3)
            {
                for(short k = 1; k < 4; k++ )
                    tank_reswap(k, &t[k]);
            }
			render_all();
	}
	exit(0);
}
