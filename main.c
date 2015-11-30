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


#define ME_TANK 0
#define BOT_TANK_1 1
#define BOT_TANK_2 2
#define BOT_TANK_3 3

	unsigned char num_of_boom = 0;
	struct tank t[4];
	struct boom b[256];


void render_all(void)
{

	erase();
	for(short k = 0; k < 4; k++ )
			tank_render(&t[k]);
	for(short k = 0; k < 256; k++ )
			boom_render(&b[k], &t[0], &t[1], &t[2], &t[3]);
	mvaddch(LINES-1,0, ' ');
	return;
}

void start_game(void)
{
	for(short k = 0; k < 4; k++ )
		tank_reswap(k, &t[k]);
	render_all();
	return;
}

void *thread_BOT1(void *arg)
{
	int loc_id = * (int *) arg;
	while(true)
	{
		unsigned char ortbot = rand() % 4;
		if(ortbot == 0)
			t[BOT_TANK_1].ort=U_NORTH;

		if(ortbot == 1)
			t[BOT_TANK_1].ort=U_WEST;

		if(ortbot == 2)
			t[BOT_TANK_1].ort=U_SOUTH;

		if(ortbot == 3)
			t[BOT_TANK_1].ort=U_EAST;

		unsigned char ridebot = rand() % 10;
		if (ridebot > 2)
			t[BOT_TANK_1].ride = 'Y';
		unsigned char boombot = rand() % 10;
		if (boombot > 5 && t[BOT_TANK_1].live == 'Y')
		{
			num_of_boom += 1;
			b[num_of_boom].ort=t[BOT_TANK_1].ort;
			b[num_of_boom].me_x=t[BOT_TANK_1].me_x;
			b[num_of_boom].me_y=t[BOT_TANK_1].me_y;

			if (t[BOT_TANK_1].ort == U_NORTH)
				b[num_of_boom].me_y -= 3;

			if (t[BOT_TANK_1].ort == U_SOUTH)
				b[num_of_boom].me_y += 3;

			if (t[BOT_TANK_1].ort == U_WEST)
				b[num_of_boom].me_x -= 3;

			if (t[BOT_TANK_1].ort == U_EAST)
				b[num_of_boom].me_x += 3;

			b[num_of_boom].live='Y';
		}

		sleep(1);
	}
	return 0;
}

void *thread_BOT2(void *arg)
{
	int loc_id = * (int *) arg;
	for(;;)
	{
		unsigned char ortbot = rand() % 4;
		if(ortbot == 0)
			t[BOT_TANK_2].ort=U_NORTH;

		if(ortbot == 1)
			t[BOT_TANK_2].ort=U_WEST;

		if(ortbot == 2)
			t[BOT_TANK_2].ort=U_SOUTH;

		if(ortbot == 3)
			t[BOT_TANK_2].ort=U_EAST;

		unsigned char ridebot = rand() % 10;
		if (ridebot > 0)
			t[BOT_TANK_2].ride = 'Y';
		unsigned char boombot = rand() % 10;
		if (boombot > 6 && t[BOT_TANK_2].live == 'Y')
		{
			num_of_boom += 1;
			b[num_of_boom].ort=t[BOT_TANK_2].ort;
			b[num_of_boom].me_x=t[BOT_TANK_2].me_x;
			b[num_of_boom].me_y=t[BOT_TANK_2].me_y;

			if (t[BOT_TANK_2].ort == U_NORTH)
				b[num_of_boom].me_y -= 3;

			if (t[BOT_TANK_2].ort == U_SOUTH)
				b[num_of_boom].me_y += 3;

			if (t[BOT_TANK_2].ort == U_WEST)
				b[num_of_boom].me_x -= 3;

			if (t[BOT_TANK_2].ort == U_EAST)
				b[num_of_boom].me_x += 3;

			b[num_of_boom].live='Y';
		}


		sleep(1);
	}
	return 0;
}

void *thread_BOT3(void *arg)
{
	int loc_id = * (int *) arg;
	for(;;)
	{
		unsigned char ortbot = rand() % 4;
		if(ortbot == 0)
			t[BOT_TANK_3].ort=U_NORTH;

		if(ortbot == 1)
			t[BOT_TANK_3].ort=U_WEST;

		if(ortbot == 2)
			t[BOT_TANK_3].ort=U_SOUTH;

		if(ortbot == 3)
			t[BOT_TANK_3].ort=U_EAST;

		unsigned char ridebot = rand() % 10;
		if (ridebot > 3)
			t[BOT_TANK_3].ride = 'Y';

		unsigned char boombot = rand() % 10;
		if (boombot > 6 && t[BOT_TANK_3].live == 'Y')
		{
			num_of_boom += 1;
			b[num_of_boom].ort=t[BOT_TANK_3].ort;
			b[num_of_boom].me_x=t[BOT_TANK_3].me_x;
			b[num_of_boom].me_y=t[BOT_TANK_3].me_y;

			if (t[BOT_TANK_3].ort == U_NORTH)
				b[num_of_boom].me_y -= 3;

			if (t[BOT_TANK_3].ort == U_SOUTH)
				b[num_of_boom].me_y += 3;

			if (t[BOT_TANK_3].ort == U_WEST)
				b[num_of_boom].me_x -= 3;

			if (t[BOT_TANK_3].ort == U_EAST)
				b[num_of_boom].me_x += 3;

			b[num_of_boom].live='Y';
		}
		sleep(1);
	}
	return 0;

}

int main(void)
{

	initscr();

	mvaddstr(LINES/2-1,COLS/2 - 6,"PRESS ANY KEY");
	getch();
	halfdelay(1);
	erase();

	pthread_t bot1, bot2, bot3;
	int id1, id2, id3;
	int result;


	id1 = 1;
	result = pthread_create(&bot1, NULL, thread_BOT1, &id1);
	if (result != 0)
	{
		perror("Creating the first thread");
		return -1;
	}


	id2 = 2;
	result = pthread_create(&bot2, NULL, thread_BOT2, &id2);
	if (result != 0)
	{
		perror("Creating the first thread");
		return -1;
	}

	id3 = 3;
	result = pthread_create(&bot3, NULL, thread_BOT3, &id3);
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
			num_of_boom += 1;
			b[num_of_boom].ort=t[ME_TANK].ort;
			b[num_of_boom].me_x=t[ME_TANK].me_x;
			b[num_of_boom].me_y=t[ME_TANK].me_y;

			if (t[ME_TANK].ort == U_NORTH)
				b[num_of_boom].me_y -= 3;

			if (t[ME_TANK].ort == U_SOUTH)
				b[num_of_boom].me_y += 3;

			if (t[ME_TANK].ort == U_WEST)
				b[num_of_boom].me_x -= 3;

			if (t[ME_TANK].ort == U_EAST)
				b[num_of_boom].me_x += 3;

			b[num_of_boom].live='Y';
			usleep(1);
		}

			short kills = 0;

			if(t[0].live == 'N')
			{
				erase();
				cbreak();
				mvaddstr(LINES/2-2,COLS/2 - 4,  "GAME OWER");
				mvaddstr(LINES/2-1,COLS/2 - 6,"PRESS ANY KEY");
				getch();
				halfdelay(1);
				start_game();
			}
			for(int k = 0; k<4; k++)
				if (t[k].live == 'N')
					kills += 1;
			if(kills >= 3)
				start_game();

			render_all();
	}
	exit(0);
}
