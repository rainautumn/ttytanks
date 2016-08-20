/*
 *  multiplayer.h
 *
 *   Created on: May 12, 2016
 *       Author: rainautumn
 * Contributors: DmitryHetman
 */

#include "render.h"
uint_fast8_t client_id;
#define PORT 33123
//void start_server();
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
