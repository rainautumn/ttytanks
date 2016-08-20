/*
 * multiplayer.c
 *
 *  Created on: May 12, 2016
 *      Author: rainautumn
 * Contibutors: DmitryHetman
 */

#include "multiplayer.h"



void child_proc(int sock) {
/*
  size_t name_len;
  char msg[] = "TTY tanks\n";
  char name_buff[256];
  char format_buff[256];
  write(sock, msg, sizeof(msg));
  name_len = read(sock, name_buff, sizeof(name_buff));


//ALWAYS FALSE
//name_len IS UNSIGNED INTEGER>>
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
*/
  close(sock);

  exit(0);
}

void *server_thread()
{
/*
    struct sockaddr_in addr;
    int accepted_socket;
    int fork_pid;
    int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
 implicit declaration of handle_error
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
*/
    return 0;
}

/*
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
