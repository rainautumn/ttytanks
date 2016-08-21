/*
 * main.c
 *
 *   Created on: Oct 29, 2015
 *       Author: rainautumn
 * Contributors: DmitryHetman
 */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include "kernel.h"
#include <math.h>
#include <stdint.h>

#define ME_TANK 0
#define BOT_TANK_1 1
#define BOT_TANK_2 2
#define BOT_TANK_3 3

#define SLEEP_BOTS_CONST 10000

    bool fpc_sleep = 0; //bool now
    uint_fast8_t num_of_boom_bot = 0;
    uint_fast8_t num_of_boom_me = 0;
	struct tank t[4];
    struct boom b_bot[256];
    struct boom b_me[256];

void render_all()
{
uint_fast8_t lin=LINES/2+10;
uint_fast8_t col=COLS/2-37;
	for(short k = 0; k < 4; k++ )
			tank_render(&t[k]);
    boom_render(&b_bot, &b_me, &t);
//
   mvaddstr(lin-2,col,"# frags : ");
    printw("%i", frags);
	return;
}

void *thread_fpc(void *arg)
{
uint_fast8_t lin=LINES;
uint_fast8_t col=COLS;
    for(;t[0].live;)
    {
        usleep(SLEEP_BOTS_CONST);
//     erase(); //delete this no need at all.
//     Is it possible ti fis terrible rendering in framebuffer?


//Remove this shit clear();
//Do a normal rendering
//       clear();
        render_gamespace(); //(better do it once)
        render_all();
       refresh();
    }
//Remove clear
//
        clear();
//      erase();
    mvaddstr(lin/2-5,col/2 - 4,  "GAME OVER");
    mvaddstr(lin/2-3,col/2 - 6,"PRESS ANY KEY");
    mvaddstr(lin/2-4,col/2 - 7,"YOUR FRAGS : ");
        printw("%i", frags);
        refresh();

        return 0;
}

void *thread_BOTS(void *arg)
{
    for(;;)
    {
        for(uint_fast8_t n = 1; n <4; n ++ )
        {
                t[n].ort = rand() % 4;

            uint_fast8_t ridebot = rand() % 10;
            if (ridebot > 2)
                t[n].ride = 1; //bool, true means to ride
            uint_fast8_t boombot = rand() % 10;
            if (boombot > 2 && t[n].live) //&& live == true (1)
            {
                num_of_boom_bot += 1;
                b_bot[num_of_boom_bot].ort  = t[n].ort;
                b_bot[num_of_boom_bot].me_x = t[n].me_x;
                b_bot[num_of_boom_bot].me_y = t[n].me_y;
                b_bot[num_of_boom_bot].live = 1;

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
   uint_fast16_t lvl_speed = SLEEP_BOTS_CONST*30/log(2+frags);
            usleep(lvl_speed);
	}

	return 0;
}

void start_local_game(void)
{
frags = 0;
t[ME_TANK].skin = '#';
for(int i = 1; i < 4; i++ )
t[i].skin = '8';
//    halfdelay(1); // /usr/lib/gcc/x86_64-pc-linux-gnu/5.3.0/../../../../x86_64-pc-linux-gnu/bin/ld: main.o: undefined reference to symbol 'halfdelay'
cbreak();

    pthread_t bot;
	uint_fast8_t id1;
        uint_fast8_t result;

       id1 = 1;
    result = pthread_create(&bot, NULL, thread_BOTS, &id1);
	if (result != 0)
	{
        perror("Creating the 1 thread");
		return;
	}

    pthread_t fpc;
    uint_fast8_t id3;
    uint_fast8_t result2;

    id3 = 3;
    result2 = pthread_create(&fpc, NULL, thread_fpc, &id3);
    if (result != 0)
    {
        perror("Creating the 3 thread");
        return;
    }

	for(uint_fast8_t k = 0; k < 4; k++ )
		tank_reswap(k, &t[k]);


	for(;;)
	{
        char key;
            key = getch();
//short delay, not works
//	    usleep(9999);
            if(key == 'w')
            {
                t[ME_TANK].ride=1;
                t[ME_TANK].ort=U_NORTH;
                            fpc_sleep = 1;
            }

            if(key == 'a')
            {
                t[ME_TANK].ride=1;
                t[ME_TANK].ort=U_WEST;
                            fpc_sleep = 1;
            }

            if(key == 's')
            {
                t[ME_TANK].ride=1;
                t[ME_TANK].ort=U_SOUTH;
                            fpc_sleep = 1;
            }

            if(key == 'd')
            {
                t[ME_TANK].ride=1;
                t[ME_TANK].ort=U_EAST;
                            fpc_sleep = 1;
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
                b_me[num_of_boom_me].live=1;
                            fpc_sleep =1;
//delay after shoot, not works
//		usleep(59999);
            }
            key = '\0';

			uint_fast8_t kills = 0;

			if(! t[0].live) //if .live = false
			{
                cbreak();
				getch();

                mvaddstr(LINES/2+2,COLS/2 - 5,"TO RESPAWN 2");
                refresh();
                sleep(1);
                mvaddstr(LINES/2+2,COLS/2 - 5,"TO RESPAWN 1");
                refresh();
                sleep(1);
//clear before respawn
		clear();
//				halfdelay(1);  ///usr/lib/gcc/x86_64-pc-linux-gnu/5.3.0/../../../../x86_64-pc-linux-gnu/bin/ld: main.o: undefined reference to symbol 'halfdelay'

                for(uint_fast8_t i = 0; i <= 254; i++)
                {
                    b_me[i].live = 0;
                    b_bot[i].live = 0;
                }
                frags = 0;
                for(uint_fast8_t k = 0; k < 4; k++ )
                    tank_reswap(k, &t[k]);
                result2 = pthread_create(&fpc, NULL, thread_fpc, &id3);
                if (result != 0)
                {
                    perror("Creating the 3 thread");
                    return;
                }
			}
			for(uint_fast8_t k = 0; k<4; k++)
				if (! t[k].live)
					kills += 1;
			if(kills >= 3)
            {
                for(uint_fast8_t k = 1; k < 4; k++ )
                    tank_reswap(k, &t[k]);
            }

        }

}
int main(void)
{
//unsigned short lin=LINES;
//unsigned short col=COLS;
//can't recieve value
    initscr();
    noecho();
    curs_set(FALSE);
render_gamespace();
render_startpage();
	for(;;)
	{
//removed from loop
//		render_gamespace();
//		render_startpage();
		char game_type = getch();
//		erase();    delete this
//		render_gamespace(); and this
		if(game_type == '0')
			break;
		switch (game_type)
		{
//            case '2':
//                start_server();
//                break;
            case '3':		clear();
				start_local_game();
				break;
			case '4':
				for(;;)
				{
					render_setting_main();
					char select = getch();
					if(select == '0')
						break;
					if(select == '1')
					{
						for(;;)
						{
							render_setting_castom();
							char select = getch();
							if(select == '0')
								break;
							if(select == '1')
							{
								//nope
							}
						}
					}
				}
				break;
			default:
				break;
		}
    }
return 0;
}
