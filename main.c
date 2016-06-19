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
#include "kernel.h"
#include <math.h>


#define ME_TANK 0
#define BOT_TANK_1 1
#define BOT_TANK_2 2
#define BOT_TANK_3 3

#define SLEEP_BOTS_CONST 10000


    char fpc_sleep = 'N';
    unsigned char num_of_boom_bot = 0;
    unsigned char num_of_boom_me = 0;
	struct tank t[4];
    struct boom b_bot[256];
    struct boom b_me[256];


void render_all(void)
{

	for(short k = 0; k < 4; k++ )
			tank_render(&t[k]);
    boom_render(&b_bot, &b_me, &t);
    mvaddstr(LINES-2,0,"# frags : ");
    printw("%i", frags);
	return;
}

void *thread_fpc(void *arg)
{
    for(;t[0].live == 'Y';)
    {
        usleep(SLEEP_BOTS_CONST);
        erase();
        clear();
        render_gamespace();
        render_all();
        refresh();
    }
        clear();
        erase();
    mvaddstr(LINES/2-5,COLS/2 - 4,  "GAME OVER");
    mvaddstr(LINES/2-3,COLS/2 - 6,"PRESS ANY KEY");
    mvaddstr(LINES/2-4,COLS/2 - 7,"YOUR FRAGS : ");
        printw("%i", frags);
        refresh();

        return 0;
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
    int lvl_speed = SLEEP_BOTS_CONST*30/log(2+frags);
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
    halfdelay(1); // /usr/lib/gcc/x86_64-pc-linux-gnu/5.3.0/../../../../x86_64-pc-linux-gnu/bin/ld: main.o: undefined reference to symbol 'halfdelay'
    cbreak();

    pthread_t bot;
	int id1;
	int result;

	id1 = 1;
    result = pthread_create(&bot, NULL, thread_BOTS, &id1);
	if (result != 0)
	{
        perror("Creating the 1 thread");
		return;
	}

    pthread_t fpc;
    int id3;
    int result2;

    id3 = 3;
    result2 = pthread_create(&fpc, NULL, thread_fpc, &id3);
    if (result != 0)
    {
        perror("Creating the 3 thread");
        return;
    }

	for(short k = 0; k < 4; k++ )
		tank_reswap(k, &t[k]);


	for(;;)
	{
        char key;
            key = getch();
            if(key == 'w' || key == 'W')
            {
                t[ME_TANK].ride='Y';
                t[ME_TANK].ort=U_NORTH;
                            fpc_sleep = 'Y';
            }

            if(key == 'a' || key == 'A')
            {
                t[ME_TANK].ride='Y';
                t[ME_TANK].ort=U_WEST;
                            fpc_sleep = 'Y';
            }

            if(key == 's' || key == 'S')
            {
                t[ME_TANK].ride='Y';
                t[ME_TANK].ort=U_SOUTH;
                            fpc_sleep = 'Y';
            }

            if(key == 'd' || key == 'D')
            {
                t[ME_TANK].ride='Y';
                t[ME_TANK].ort=U_EAST;
                            fpc_sleep = 'Y';
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
                            fpc_sleep = 'Y';

            }
            key = '\0';

			short kills = 0;

			if(t[0].live == 'N')
			{
                cbreak();
				getch();

                mvaddstr(LINES/2+2,COLS/2 - 5,"TO RESPAWN 2");
                refresh();
                sleep(1);
                mvaddstr(LINES/2+2,COLS/2 - 5,"TO RESPAWN 1");
                refresh();
                sleep(1);
				halfdelay(1);  ///usr/lib/gcc/x86_64-pc-linux-gnu/5.3.0/../../../../x86_64-pc-linux-gnu/bin/ld: main.o: undefined reference to symbol 'halfdelay'

                for(unsigned char i = 0; i <= 254; i++)
                {
                    b_me[i].live = 'N';
                    b_bot[i].live = 'N';
                }
                frags = 0;
                for(short k = 0; k < 4; k++ )
                    tank_reswap(k, &t[k]);
                result2 = pthread_create(&fpc, NULL, thread_fpc, &id3);
                if (result != 0)
                {
                    perror("Creating the 3 thread");
                    return;
                }
			}
			for(int k = 0; k<4; k++)
				if (t[k].live == 'N')
					kills += 1;
			if(kills >= 3)
            {
                for(short k = 1; k < 4; k++ )
                    tank_reswap(k, &t[k]);
            }

        }

}
int main(void)
{
    initscr();
    noecho();
    curs_set(FALSE);
	for(;;)
	{
		render_gamespace();
		render_startpage();
		char game_type = getch();
		erase();
		render_gamespace();
		if(game_type == '0')
			break;
		switch (game_type)
		{
            case '2':
//                start_server();
                break;
            case '3':
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
	exit(0);
}
