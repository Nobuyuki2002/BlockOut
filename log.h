#ifndef __LOG_H__
#define __LOG_H__

#include "game_thread.h"

/*****************************************************
 *                      定数定義                      *
******************************************************/
#define LOGROOT "./log"
#define LOGBASENAME "sys_log"
#define LOGNAMEMAX 128

/*****************************************************
 *                      大域変数                      *
******************************************************/
extern FILE* Log_fp;

/*****************************************************
 *                    関数原型宣言                    *
******************************************************/
bool OpenLog ();
void WriteLog ( bool eflag, char* format, ... );
void CloseLog ();

#endif // #ifndef __LOG_H__