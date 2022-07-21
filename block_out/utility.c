#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include "log.h"
#include "utility.h"

volatile sig_atomic_t Sig_flag = 0;
bool Demo_mode = false;

void signal_handler ( int signum )
{
	Sig_flag = 1;
	WriteLog ( false, "get stop signal" );
}

int GetCh ( uint32_t limit )
{
	int ch;

	if ( limit != 0 )
	{
		timeout ( limit );
	}

	ch = getch ();

	switch ( ch )
	{
		case KEY_UP:
			WriteLog ( false, "input key < KEY_UP >" );
		break;
		case KEY_DOWN:
			WriteLog ( false, "input key < KEY_DOWN >" );
		break;
		case KEY_LEFT:
			WriteLog ( false, "input key < KEY_LEFT >" );
		break;
		case KEY_RIGHT:
			WriteLog ( false, "input key < KEY_RIGHT >" );
		break;
		case '\n':
			WriteLog ( false, "input key < ENTER >" );
		break;
		case ' ':
			WriteLog ( false, "input key < SPACE >" );
		break;
		case -1:
			WriteLog ( false, "input time out" );
		break;
		default:
			WriteLog ( false, "input key < %c >", ch );
		break;
	}

	timeout ( -1 );
	return ch;
}

uint32_t GetMinutesMilli ()
{
	struct timespec tmspec;
	struct tm tm;

	uint32_t milli_time = 0;

	clock_gettime ( CLOCK_REALTIME, &tmspec );
	localtime_r ( &tmspec.tv_sec, &tm );

	milli_time = ( ( tm.tm_min * 60 ) * 1000 ) + ( tm.tm_sec * 1000 ) + ( tmspec.tv_nsec / 1000000 );
	return milli_time;
}