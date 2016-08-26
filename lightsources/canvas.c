/*
 * canvas.c
 *
 *  Created on:  2016/08/19
 *      Authors: rainautumn, DmitryHetman
 * Contributors:
 */

//PAGES AND BORDERS ARE RENDERED HERE
//ALL MULTIPLAYER STUFF MOVED TO multiplayer.c multiplayer.h

#include "canvas.h"

void print_startpage() //this is not rendered, just printed;
{
	       //mvaddstr(y,x,"string");
        mvaddstr( 3,1,"                                                        OO            ");
	mvaddstr( 4,1,"                               TTY TANKS                OO            ");

	mvaddstr( 8,1,"    1 Connect to server                                 ##            ");
	mvaddstr( 9,1,"    2 Create server                                     ##            ");
	mvaddstr(10,1,"    3 Game with bots                                  ######          ");
	mvaddstr(11,1,"    4 Settings                                        ######          ");
        mvaddstr(12,1,"    5 Help                                            ##  ##          ");
	mvaddstr(13,1,"    6 About this game                                 ##  ##          ");
	mvaddstr(14,1,"    0 Exit                                                            ");
}

void print_canvas() //USE THIS FUNCTION BEFORE EVERY GAME
{
//H_GAME was 20
//W_GAME was 70

//May be better remove top and left borders? Leave it for capability with main sources;

//canvas:
 mvaddstr(0,0,"________________________________________________________________________"); //top border
 mvaddstr(1,0,"|                                                                      |");
 mvaddstr(2,0,"|                                                                      |");
 mvaddstr(3,0,"|                                                                      |");
 mvaddstr(4,0,"|                                                                      |");
 mvaddstr(5,0,"|                                                                      |");
 mvaddstr(6,0,"|                                                                      |");
 mvaddstr(7,0,"|                                                                      |");
 mvaddstr(8,0,"|                                                                      |");
 mvaddstr(9,0,"|                                                                      |");
mvaddstr(10,0,"|                                                                      |");
mvaddstr(11,0,"|                                                                      |");
mvaddstr(12,0,"|                                                                      |");
mvaddstr(13,0,"|                                                                      |");
mvaddstr(14,0,"|                                                                      |");
mvaddstr(15,0,"|                                                                      |");
mvaddstr(16,0,"|                                                                      |");
mvaddstr(17,0,"|                                                                      |");
mvaddstr(18,0,"|                                                                      |");
mvaddstr(19,0,"|                                                                      |");
mvaddstr(20,0,"|                                                                      |");
mvaddstr(21,0,"|----------------------------------------------------------------------|"); //bottom border
mvaddstr(22,0,"|FRAGS:                                                                 ");
}
void print_help()
{
print_canvas();

 mvaddstr(3,1,"                            Help                          ");
 mvaddstr(5,1," Control:                                                 ");
 mvaddstr(6,1,"    wasd/arrow keys/8426 (numpad)  - Move                 ");
 mvaddstr(7,1,"    space/5/0                      - Fire                 ");
 mvaddstr(8,1,"    CTRL+C                         - Exit game            ");
mvaddstr(10,1," How to play:                                             ");
mvaddstr(11,1,"  For better user experience use square or almost squere  ");
mvaddstr(12,1," font in your terminal, in vt for example you need use    ");
mvaddstr(13,1," '$ setfont <font name>', list of fonts located in        ");
mvaddstr(14,1," /usr/share/consolefonts/, you can use same bitmap font in");
mvaddstr(15,1," your terminal emulator                                   ");
mvaddstr(19,1,"  Press any key to exit                                   ");

getch();
}
void print_about()
{
  print_canvas();

  mvaddstr(3,1,"                         About                           ");
  mvaddstr(5,1,"    Created on: 2015/10/29                               ");
  mvaddstr(6,1,"       Version: 1.1                                      ");
  mvaddstr(7,1,"        Author: rainautumn                               ");
  mvaddstr(8,1,"  Contributors: DmitryHetman                             ");
  mvaddstr(9,1,"  GitHub Pages:                                          ");
 mvaddstr(10,1,"          github.com/rainatumn/ttytanks                  ");
 mvaddstr(11,1,"          github.com/DmitryHetman/ttytanks               ");
 mvaddstr(19,1,"  Press any key to exit                                  ");

 getch();
}
void print_setting_main()
{
 for(;;)
    {
       print_canvas();
           mvaddstr( 9, 5 ,"1 network game");
           mvaddstr(10, 5 ,"0 return");

           uint_fast8_t select=getch();
           if (select=='0')
           break;
          if (select=='1')
             for(;;)
                {
                 print_canvas();
                 mvaddstr( 9,5,"1 server port");
                 mvaddstr(10,5,"0 return     ");
                 uint_fast8_t select=getch();
                   if (select=='0')
                    break;
                   if (select=='1')
                    break;  //nope
                }

    }

}
