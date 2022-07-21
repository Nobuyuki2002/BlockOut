#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "block.h"
#include "game_thread.h"
#include "game_utility.h"
#include "load_map_data.h"
#include "log.h"
#include "utility.h"

bool LoadMapData ( uint8_t map_no, T_GAMESITUATION* game_situation )
{
	WriteLog ( false, "== start LoadMapData ==" );
	uint8_t i = 0, j = 0;
	char line[ ( MAX_WIDTH / BLOCKSIZE_WIDTH ) + 1 ];
	char filename[ MAPFILE_LEN ];
	FILE* fp;
	game_situation->block_count = 0;

	if ( Demo_mode )
	{
		sprintf ( filename, "%s%d.dat", DEMOMAPFILE_BASE, map_no );
	}
	else
	{
		sprintf ( filename, "%s%d.dat", MAPFILE_BASE, map_no );
	}

	WriteLog ( false, "load map file < %s >", filename );
	if ( ( fp = fopen ( filename, "r" ) ) == NULL )
	{
		WriteLog ( true, "dosen't open file < %s >", filename );
		return false;
	}

	for ( i = 0; i < ( MAX_HEIGHT / BLOCKSIZE_HEIGHT ); i ++ )
	{
		/* fgets は size_t - 1だけ文字をとるので、改行文字まで考慮して +2する */
		if ( fgets ( line, ( MAX_WIDTH / BLOCKSIZE_WIDTH ) + 2, fp ) == NULL )
		{
			WriteLog ( true, "load null line" );
			return false;
		}

		line[ MAX_WIDTH / BLOCKSIZE_WIDTH ] = '\0';
		if ( strlen ( line ) != MAX_WIDTH / BLOCKSIZE_WIDTH  )
		{
			WriteLog ( true, "broken map data < %d line / %d word >", i, strlen ( line ) );
			return false;
		}

		for ( j = 0; ; j ++ )
		{
			game_situation->map[ i ][ j ] = line[ j ];
			if ( JugeMap ( game_situation->map[ i ][ j ] ) ) game_situation->block_count ++;
			if ( game_situation->map[ i ][ j ] == '\0' ) break;
		}

		WriteLog ( false, "< load : %d > %s, block : %d", i, &game_situation->map[i][0], game_situation->block_count );
	}

	WriteLog ( false, "== end LoadMapData ==" );
	return true;
}
