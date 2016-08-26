/*
 * core.c
 *
 *   Created on: 2016/08/19
 *      Authors: rainautumn, DmitryHetman
 */
#include "core.h"

void render_all()
 //better move all related to rendering in rener.c
{
	for(uint_fast8_t k = 0; k < 4; k++ )
			tank_render(&t[k]);
    boom_render(b_bot, b_me, t); //&b_bot, &b_me, &t was here
//H_GAME+2 22
//create function that returns number of frags;
   mvaddstr(22,8,""); //move it to print_canvas;
    printw("%i",frags);
}

void *thread_fpc()
{
    for(;t[0].live;)
    {
        usleep(SLEEP_BOTS_CONST);
        render_all();
       refresh();
    }
//should be better move it to canvas.c: print_game_over;
     mvaddstr(8,1,"                                                  ");
     mvaddstr(9,1,"                       GAME OVER                  ");
    mvaddstr(10,1,"                     PRESS ANY KEY                ");
    mvaddstr(11,1,"                   YOUR FRAGS : ");
     printw("%i%s", frags,"                       "); //string for clearing artefacts, remove it later, after fix;
    mvaddstr(12,1,"                                             ");
        refresh(); //what is refresh? called two times after death
return 0;
}

void *thread_BOTS()
{
    for(;;)
    {
        for(uint_fast8_t n = 1; n <4; n ++ )
        {
                t[n].ort = rand() % 4;

            uint_fast8_t ridebot = rand() % 10;
            if (ridebot > 2)
                t[n].ride = 1;
            uint_fast8_t boombot = rand() % 10;
            if (boombot > 2 && t[n].live)
            {
                num_of_boom_bot += 1;
                b_bot[num_of_boom_bot].ort  = t[n].ort;
                b_bot[num_of_boom_bot].me_x = t[n].me_x;
                b_bot[num_of_boom_bot].me_y = t[n].me_y;
                b_bot[num_of_boom_bot].live = 1;

                switch (t[n].ort)
                {
                case U_NORTH:
                    b_bot[num_of_boom_bot].me_y -= 2; //start of boolet for bots
                    break;
                case U_SOUTH:
                    b_bot[num_of_boom_bot].me_y += 2;
                    break;
                case U_WEST:
                    b_bot[num_of_boom_bot].me_x -= 2;
                    break;
                case U_EAST:
                    b_bot[num_of_boom_bot].me_x += 2;
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

void start_local_game()
{
print_canvas(); //print canvas before start game
frags = 0;
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
    if (result2 != 0)
    {
        perror("Creating the 3 thread");
        return;
    }

	for(uint_fast8_t k = 0; k < 4; k++ )
		tank_reswap(k, &t[k]);


	for(;;)
	{
        uint_fast16_t key;
            keypad(stdscr,1); //bf=TRUE, read man keypad, man ncurses
            key = wgetch(stdscr); //read man wgetch
//HOW USE KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT fron getch(), read man getch
//NUMPAD support
                 if (key==KEY_UP|| key == 'w'||key=='8') //not call has_key everytime;
                  {
                  t[ME_TANK].ride=1;
                  t[ME_TANK].ort=U_NORTH;
                            fpc_sleep = 1;
                   }
                 else if (key==KEY_LEFT || key == 'a'||key=='4')
                    {
                    t[ME_TANK].ride=1;
                    t[ME_TANK].ort=U_WEST;
                            fpc_sleep = 1;
                     }

                else if (key==KEY_DOWN||key=='s'||key=='2')
                    {
                    t[ME_TANK].ride=1;
                    t[ME_TANK].ort=U_SOUTH;
                            fpc_sleep = 1;
                    }
                else if (key==KEY_RIGHT||key=='d'||key=='6')
                    {
                    t[ME_TANK].ride=1;
                    t[ME_TANK].ort=U_EAST;
                            fpc_sleep = 1;
                    }
	        //better read this separate from arrow keys
               else if (key==' '||key=='5'||key=='0') //KEY_ENTER not works;
                                                    //you can't ride and shoot at the same time yet :( ;
               {
                num_of_boom_me++;
                b_me[num_of_boom_me].ort=t[ME_TANK].ort;
                b_me[num_of_boom_me].me_x=t[ME_TANK].me_x;
                b_me[num_of_boom_me].me_y=t[ME_TANK].me_y;

                   switch (t[ME_TANK].ort)
                   {
                    case U_NORTH:
                     b_me[num_of_boom_me].me_y -= 2; //start of boolet for user
                    break;
                    case U_SOUTH:
                     b_me[num_of_boom_me].me_y += 2;
                    break;
                    case U_WEST:
                     b_me[num_of_boom_me].me_x -= 2;
                    break;
                    case U_EAST:
                     b_me[num_of_boom_me].me_x += 2;
                    break;
                    default:
                    break;
                  }
                b_me[num_of_boom_me].live=1;
                            fpc_sleep = 1;
                   }
                   //how to exit?
            key = '\0';

			uint_fast8_t kills = 0;

			if(! t[0].live)
			{
//should be better move it to canvas.c : print_game_over();
                cbreak();
				getch();

                mvaddstr(12,1,"                     TO RESPAWN 2                 ");
                refresh();
                sleep(1);
                mvaddstr(12,1,"                     TO RESPAWN 1                 ");
                refresh();
                sleep(1);
                print_canvas(); //print canvas before respawn

                for(uint_fast8_t i = 0; i <= 254; i++) //what is 254?
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
