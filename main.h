#ifndef __MAIN_H__
#define __MAIN_H__

#include "game_thread.h"

/*****************************************************
 *                    マクロ定義                      *
******************************************************/
// #define DEBUG_MODE

#ifdef DEBUG_MODE
#define DEBUG(y,x,...) mvprintw(y,x,__VA_ARGS__);
#else
#define DEBUG(y,x,...)
#endif

#endif // #ifndef __MAIN_H__