#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include "game_thread.h"
#include "log.h"

bool JugeMap ( char map )
{
	switch ( map )
	{
		case '1' :
		case '2' :
		case '3' :
			return true;
	}
	return false;
}

void CreateClearPass ( T_GAMEDATA* game_data )
{
	uint8_t i = 0;
	uint8_t pivot;
	srand ( ( unsigned int )time ( NULL ) );

	while ( i < PASS_SIZE - 1 )
	{
		pivot = rand () % 100;

		if ( pivot < 30 )
		{
			game_data->pass_data[ i ++ ] = '0' + rand () % ( ( '9' - '0' ) + 1 );
		}
		else if ( pivot < 75 )
		{
			game_data->pass_data[ i ++ ] = 'a' + rand () % ( ( 'z' - 'a' ) + 1 );
		}
		else if ( pivot < 100 )
		{
			game_data->pass_data[ i ++ ] = 'A' + rand () % ( ( 'Z' - 'A' ) + 1 );
		}
	}

	game_data->pass_data[ i ] = '\0';
	WriteLog ( false, "create pass data < %s >", game_data->pass_data );
	return;
}