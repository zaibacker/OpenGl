/***************************************************************/
/*                  CURSES ....                                */
/***************************************************************/

#include <string.h>
#include "dialogue.h"

#define SIZE 256

void beginChatScreen(struct  chatScreen *screen)
{
 char    str[SIZE];
 int     i;

 int posInTittle,heightInTittle,
     posWIn,heightWIn,
     poswSep,heightSep,
     posOutTittle,heightOutTittle,
     posWOut,heightWOut;


 initscr();

 /* initialisation des fenetres */

    /* Positions et hauteurs ... */

 posInTittle  = 0;                             heightInTittle  = 1;

 posWIn       = posInTittle+heightInTittle;    heightWIn       = (LINES-3)/2;
                                               /* -3 : nb lignes "occupees" */

 poswSep      = posWIn+heightWIn;              heightSep       = 1;

 posOutTittle = poswSep+heightSep;             heightOutTittle = 1;

 posWOut      = posOutTittle+heightOutTittle;  heightWOut      = LINES-posWOut;

    /* creation des fenetres ... */

 screen->wInTittle  = newwin(heightInTittle,COLS,posInTittle,0);

 screen->wIn        = newwin(heightWIn,COLS,posWIn,0); 

 screen->wSep       = newwin(heightSep,COLS,poswSep,0);

 screen->wOutTittle = newwin(heightOutTittle,COLS,posOutTittle,0);

 screen->wOut       = newwin(heightWOut,COLS,posWOut,0);

    /* Affichage des titres, ... */

      /* Un message dans la fenetre wInTittle         */
 wattron(screen->wInTittle,A_REVERSE);
 strcpy(str,"Vous");
 mvwaddstr(screen->wInTittle,0,(COLS-strlen(str))/2,str);
 wattron(screen->wInTittle,A_NORMAL);

      /* Une ligne dans wSep                          */
 for(i=0;i<COLS && i<SIZE-1;i++) str[i]='-';
 str[i]='\0';

 waddstr(screen->wSep,str);

      /* Un message dans la fenetre wOutTittle        */
 wattron(screen->wOutTittle,A_REVERSE);
 strcpy(str,"Et les autres...");
 mvwaddstr(screen->wOutTittle,0,(COLS-strlen(str))/2,str);
 wattron(screen->wOutTittle,A_NORMAL);

 refresh();

 wrefresh(screen->wInTittle);
 wrefresh(screen->wIn);
 wrefresh(screen->wSep);
 wrefresh(screen->wOutTittle);
 wrefresh(screen->wOut);

 /* mise en place du scroll */

 scrollok(screen->wIn,TRUE);
 scrollok(screen->wOut,TRUE);
 
}

void endChatScreen(struct chatScreen *screen)
{
 endwin();
 
 delwin(screen->wInTittle);
 delwin(screen->wIn);
 delwin(screen->wSep);
 delwin(screen->wOutTittle);
 delwin(screen->wOut);
}

void putstrInWindow(WINDOW *win, char *str)
{
 waddstr(win,str);

 wrefresh(win);
}

void vprintInWindow(WINDOW *win,const char *format,va_list ap)
{
 char    line[SIZE];

 vsnprintf(line,SIZE,format,ap);
 line[SIZE-1]='\0';

 putstrInWindow(win,line);
}

void printInWindow(WINDOW *win,const char *format, ...)
{
 va_list ap;

 va_start(ap,format);
   vprintInWindow(win,format,ap);
 va_end(ap);
}
