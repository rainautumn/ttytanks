/* main.c
 *
 *   Created on: 2016/08/19
 *      Authors: rainautumn, DmitryHetman
 * Contributors:
 */
#include "core.h"
int main()
{
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
             case '2':
                //start_server();
                break;
            case '3':
				start_local_game();
				break;
			case '4':
				for(;;)
				{
					print_setting_main();
					char select = getch();
					if(select == '0')
						break;
					if(select == '1')
					{
						for(;;)
						{
							print_setting_castom();
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
                        case '5':
                               print_help();
                               for(;;)
                               {
                               char select=getch();
                               if(select== '0')
                               break;
                               }
                               break;
                        case '6':
                               print_about();
                               for(;;)
                               {
                               char select=getch();
                               if(select=='0')
                               break;
                               }
                               break;
			default:
				break;
		}
    }
//prepare terminal before exit
return 0;
}
