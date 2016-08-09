/*
 * kernel.c
 *
 *  Created on: May 12, 2016
 *      Author: rainautumn
 */

#include "kernel.h"
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>


void handle_error(char* err_fun) {
unsigned short lin = LINES;
  mvaddstr(lin-2,0,"error!!!");
  exit(1);
}

void child_proc(int sock) {
  size_t name_len;
  char msg[] = "TTY tanks\n";
  char name_buff[256];
  char format_buff[256];
  write(sock, msg, sizeof(msg));
  name_len = read(sock, name_buff, sizeof(name_buff));
/*
ALWAYS FALSE
name_len IS UNSIGNED INTEGER
  if(-1 == name_len) {
    handle_error("read");
  }
*/
  while(name_len > 0 &&
      ( '\n' == name_buff[name_len-1]  ||
        '\r' == name_buff[name_len-1])) {
    name_len--;
  }
  name_buff[name_len] = 0;
  sprintf(format_buff, "Hello, %s!\n", name_buff);
  write(sock, format_buff, strlen(format_buff));
  close(sock);
  exit(0);
}

void *server_thread()
{
    struct sockaddr_in addr;
    int accepted_socket;
    int fork_pid;
    int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == listen_socket) {
      handle_error("socket");
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    if(-1 == bind(listen_socket, (struct sockaddr*)&addr, sizeof(addr))){
      handle_error("bind");
    }

    if(-1 == listen(listen_socket, 100)) {
      handle_error("listen");
    }

    for(;;) {
      accepted_socket = accept(listen_socket, 0, 0);
      if(-1 == accepted_socket) {
        handle_error("accept");
      }

      fork_pid = fork();
      if(-1 == fork_pid) {
        handle_error("fork");
      } else if(0 == fork_pid) {
        close(listen_socket);
        child_proc(accepted_socket);
      } else {
        close(accepted_socket);
      }
    }
//    return;
}

void start_server()
{
    pthread_t net;
    int id2;
    int result;

    id2 = 2;
    result = pthread_create(&net, NULL, server_thread, &id2);
    if (result != 0)
    {
        perror("Creating the 2 thread");
        return;
    }
}
void render_startpage()
{
unsigned short lin=LINES;
	mvaddstr(top + H_GAME/2-6, left + W_GAME/2 -6 ,"TTY TANKS");
	mvaddstr(top + H_GAME/2-2, left + 5 ,"1 connect to server");
	mvaddstr(top + H_GAME/2-1, left + 5 ,"2 create server");
	mvaddstr(top + H_GAME/2-0, left + 5 ,"3 game with bots");
	mvaddstr(top + H_GAME/2+1, left + 5 ,"4 settings");
	mvaddstr(top + H_GAME/2+2, left + 5 ,"5 about this game");
	mvaddstr(top + H_GAME/2+3, left + 5 ,"0 exit");

	mvaddstr(top + H_GAME/2-8, left + 50 ,"  ##  ");
	mvaddstr(top + H_GAME/2-7, left + 50 ,"  ##  ");
	mvaddstr(top + H_GAME/2-1, left + 50 ,"  ##  ");
	mvaddstr(top + H_GAME/2  , left + 50 ,"  ##  ");
	mvaddstr(top + H_GAME/2+1, left + 50 ,"######");
	mvaddstr(top + H_GAME/2+2, left + 50 ,"######");
	mvaddstr(top + H_GAME/2+3, left + 50 ,"##  ##");
	mvaddstr(top + H_GAME/2+4, left + 50 ,"##  ##");
	mvaddstr(lin-2,0,"#");
}

char render_gamespace()
{
//may be better col = COLS-1; etc../
unsigned short col = COLS;
unsigned short lin = LINES;
//why query to environment variables all the time? better do it ONE TIME IN WHOLE PROGRAM.
//	erase(); //delete this//

        left = col - W_GAME - 1;
	if(left < 1)
		return 'E';
//	for(int i = left-1; i < left; i++)
//j=0
//make loop shorter
unsigned short i = left-1;
 top = lin - H_GAME -3;
unsigned short row = col-1;
unsigned short cot = lin-3;
//left and right line loop>>
		for(int j=top; j < cot; j++)
                 {
			mvaddstr(j,i,"#");
			mvaddstr(j,row,"#");
                 }
//	int right = COLS - 1;
//j=0
//make loop smaller
//		for(int j = LINES -1; j < LINES; j++)
//cut off loop, do it one time
//			mvaddstr(LINES-1,right, "#");
//no need for it at all


	if(top < 1)
		return 'E';
//	for(int i = 0; i < top; i++)
//remove loop, render only one top line

//			for(int j = COLS-72; j < COLS; j++)
//				mvaddstr(top-1,j, "#");
//This loop moved to the next one

//	for(int i = 0; i < COLS; i++)
//i
//		mvaddstr(LINES-1,LINES-2, "#");

//or COLS-W_GAME+2

//top and bottom !loop>>
//	for(int i = col-72; i < col; i++)
//	   {
i=col-72;
mvaddstr(top-1,i,"########################################################################");
mvaddstr(cot,i,"########################################################################");
//           }

}

void render_setting_main()
{
unsigned short lin = LINES;
	mvaddstr(top + H_GAME/2-1, left + 5 ,"1 network game");
	mvaddstr(top + H_GAME/2+0, left + 5 ,"0 return");
	mvaddstr(lin-2,0,"#");
}

void render_setting_castom()
{
	mvaddstr(top + H_GAME/2-1, left + 5 ,"1 server port");
	mvaddstr(top + H_GAME/2+0, left + 5 ,"0 return");
}
