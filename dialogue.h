#ifndef  DIALOGUE_H
#define  DIALOGUE_H

/***************************************************************/
/*                  CURSES ....                                */
/***************************************************************/
#include <curses.h>
#include <stdarg.h>

struct  chatScreen {

 WINDOW *wInTittle; 
 WINDOW *wIn; 
 WINDOW *wSep;
 WINDOW *wOutTittle; 
 WINDOW *wOut;
};

extern void beginChatScreen(struct  chatScreen *screen);

extern void endChatScreen(struct chatScreen *screen);

extern void putstrInWindow(WINDOW *win, char *str);

extern void vprintInWindow(WINDOW *win,const char *format,va_list ap);

extern void printInWindow(WINDOW *win,const char *format,...);

#endif /* DIALOGUE_H */
