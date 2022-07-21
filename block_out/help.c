#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include "game_thread.h"
#include "help.h"
#include "log.h"
#include "utility.h"

void DrawHelpWindow ()
{
	WriteLog ( false, "== start DrawHelpWindow ==" );
	int ch;
	uint8_t line_count = 0;
	FILE* fp;
	char help_line[ LINE_MAXLEN ];

	fp = fopen ( HELPDATAFILE, "r" );
	if ( fp == NULL )
	{
		WriteLog ( true, "fail open help file" );
		return;
	}

	/* ヘルプを出力する */
	clear ();
	while ( fgets ( help_line, LINE_MAXLEN, fp ) != NULL )
	{
		mvprintw ( line_count, 0, help_line );
		memset ( help_line, '\0', LINE_MAXLEN );
		WriteLog ( false, "load line %d", line_count ++ );
	}
	fclose ( fp );
	mvprintw ( MAX_HEIGHT - 2, MAX_WIDTH - 15, "qボタンで戻る" );
	refresh ();

	while ( ch != 'q' && !Sig_flag ) ch = GetCh ( 500 );
	WriteLog ( false, "== end DrawHelpWindow ==" );
	return;
}