/* core.h
 *
 *   Created on: 2016/08/19
 *       Autors: rainautumn, DmitryHetman
 * Contributors:
 */

//#include <pthread.h> //already included in multiplayer.h, include it if multiplayer disabled;
#include <stdlib.h> //for rand();
#include "canvas.h"
#include "multiplayer.h" //Doesn't work yet
#define ME_TANK 0
#define BOT_TANK_1 1
#define BOT_TANK_2 2
#define BOT_TANK_3 3
#define SLEEP_BOTS_CONST 10000

bool fpc_sleep; // = 0; zero by default in all variables, assignment isn't necessary
uint_fast8_t num_of_boom_bot;
uint_fast8_t num_of_boom_me;

struct tank t[4];
struct boom b_bot[255];
struct boom b_me[255];

void render_all();
void *thread_fpc();
void *thread_BOTS();
void start_local_game();

