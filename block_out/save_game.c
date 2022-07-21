#include <stdio.h>
#include <stdbool.h>
#include "log.h"
#include "save_game.h"

void SaveGame ( T_GAMEDATA game_data )
{
	FILE* save_fp;

	save_fp = fopen ( SAVEDATAFILE, "wb" );
	if ( save_fp == NULL )
	{
		WriteLog ( true, "couldn't SaveGame" );
		return;
	}

	fwrite ( &game_data, sizeof ( T_GAMEDATA ), 1, save_fp );

	fclose ( save_fp );

	return;
}
