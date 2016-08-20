/*
 * kernel.c
 *
 *   Created on: May 12, 2016
 *       Author: rainautumn
 * Contributors: DmitryHetman
 */

#include "kernel.h"
#include <pthread.h>

#include <sys/types.h>
//#include <sys/socket.h> not works yet
//#include <netinet/in.h>
//#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
//#include <stdio.h>
#include <unistd.h>
#include <errno.h>

//Predifined wariables:
//W_GAME -Game Width
//H_GAME - game height
//top - ?
//left - ?
/* Not works, commented
void handle_error(char* err_fun) {
uint_fast8_t lin = LINES;
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

ALWAYS FALSE
name_len IS UNSIGNED INTEGER
  if(-1 == name_len) {
    handle_error("read");
  }

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

 commented untill will work
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
*/
void render_startpage()
{
	uint_fast8_t lin=LINES;
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

void render_gamespace() //Deprecated and slowx, see print_canvas in lightsources/canvas.h
{
                       //W_GAME/2
uint_fast8_t col = COLS/2+35; //better declare it in program one time
uint_fast8_t lin = LINES/2+10; //

        left = col - W_GAME - 1; //left declared in kernel.h

uint_fast8_t i = left-1; // x position of left border

 top = lin - H_GAME -3;  //declared in kernel.h

uint_fast8_t row = col-1; // x position of right border
uint_fast8_t bottomend_y = lin-3; //end of gamespace y position

//left and right line loop>>
                 //reder left and right borders from top to bottom
		for(uint_fast8_t j=top; j < bottomend_y; j++)
                 {
			//j - y coordinate; i,row - x coordinate;
			mvaddch(j,i,'#');
			mvaddch(j,row,'#');
                 }

//top and bottom borders
i=col-72;  //x position to start draw top and bottom lines
mvaddstr(top-1,i,"########################################################################");
mvaddstr(bottomend_y,i,"########################################################################");
}


void render_setting_main()
{
uint_fast8_t lin = LINES;
	mvaddstr(top + H_GAME/2-1, left + 5 ,"1 network game");
	mvaddstr(top + H_GAME/2+0, left + 5 ,"0 return");
	mvaddstr(lin-2,0,"#");
}

void render_setting_castom()
{
	mvaddstr(top + H_GAME/2-1, left + 5 ,"1 server port");
	mvaddstr(top + H_GAME/2+0, left + 5 ,"0 return");
}
