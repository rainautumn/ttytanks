/* main.c
 *
 *   Created on: 2016/08/19
 *      Authors: rainautumn, DmitryHetman
 * Contributors:
 */
#include "core.h"
int main()
{
/* You shoul use square bitmap fonts for this game
 * Use 8*8 16*16 etc. fonts from /usr/share/consolefonts, add selection of font in settings
 * Maybe you need to call external program 'setfont' for it
 * Seems like it's possilbe only in vt/tty/framebuffer, not in pty like graphic terminal or tmux
 */

    initscr();
    noecho();
    curs_set(0); // 0 is FALSE
	for(;;)
	{
print_canvas();
print_startpage();
		uint_fast8_t game_type = getch();
		if(game_type == '0')
			break;
		switch (game_type)
		{
                        case '1':
                                   //connect to server;
                                   break;
                        case '2':
                                  //start_server();
                                  break;
                        case '3':
				  start_local_game();
				  break;
                        case '4':
                                  print_setting_main();
				  break;
                        case '5':
                                  print_help();
                                  break;
                        case '6':
                                  print_about();
                                  break;
			default:
				  break;
		}
    }
//prepare terminal before exit, now better use CTRL+C
return 0;
}
