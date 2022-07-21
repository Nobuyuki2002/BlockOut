#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <stdbool.h>
#include <signal.h>
#include "game_thread.h"

extern volatile sig_atomic_t Sig_flag;
extern bool Demo_mode;

void signal_handler ( int signum );
int GetCh ( uint32_t limit );
uint32_t GetMinutesMilli ();

#endif // #ifndef __UTILITY_H__