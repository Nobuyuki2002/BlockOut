#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include "block.h"
#include "game_thread.h"
#include "game_utility.h"

void BrokenBlock ( T_GAMESITUATION* game_situation, uint8_t block_y, uint8_t block_x )
{
	uint8_t i = 0, j = 0;

	game_situation->map[ block_y ][ block_x ] = '0';
	game_situation->block_count --;
	for ( i = 0; i < BLOCKSIZE_HEIGHT; i ++ )
	{
		for ( j = 0; j < BLOCKSIZE_WIDTH; j ++ )
		{
			mvprintw ( ( block_y * BLOCKSIZE_HEIGHT ) + i, ( block_x * BLOCKSIZE_WIDTH ) + j, " " );
		}
	}

	refresh ();
	return;
}

void ExplosionBlock ( T_GAMESITUATION* game_situation, uint8_t block_y, uint8_t block_x )
{
	block_y /= BLOCKSIZE_HEIGHT;
	block_x /= BLOCKSIZE_WIDTH;

	if ( JugeMap ( game_situation->map[ block_y - 1 ][ block_x - 1 ] ) )
	{
		if ( game_situation->map[ block_y - 1 ][ block_x - 1 ] == '2' ) game_situation->broken_lifeup_block ++;
		BrokenBlock ( game_situation, block_y - 1, block_x - 1 );
	}

	if ( JugeMap ( game_situation->map[ block_y - 1 ][ block_x ] ) )
	{
		if ( game_situation->map[ block_y - 1 ][ block_x ] == '2' ) game_situation->broken_lifeup_block ++;
		BrokenBlock ( game_situation, block_y - 1, block_x );
	}

	if ( JugeMap ( game_situation->map[ block_y - 1 ][ block_x + 1 ] ) )
	{
		if ( game_situation->map[ block_y - 1 ][ block_x + 1 ] == '2' ) game_situation->broken_lifeup_block ++;
		BrokenBlock ( game_situation, block_y - 1, block_x + 1 );
	}

	if ( JugeMap ( game_situation->map[ block_y ][ block_x - 1 ] ) )
	{
		if ( game_situation->map[ block_y ][ block_x - 1 ] == '2' ) game_situation->broken_lifeup_block ++;
		BrokenBlock ( game_situation, block_y, block_x - 1 );
	}

	if ( JugeMap ( game_situation->map[ block_y ][ block_x + 1 ] ) )
	{
		if ( game_situation->map[ block_y ][ block_x + 1 ] == '2' ) game_situation->broken_lifeup_block ++;
		BrokenBlock ( game_situation, block_y , block_x + 1 );
	}

	if ( JugeMap ( game_situation->map[ block_y + 1 ][ block_x - 1 ] ) )
	{
		if ( game_situation->map[ block_y + 1 ][ block_x - 1  ] == '2' ) game_situation->broken_lifeup_block ++;
		BrokenBlock ( game_situation, block_y + 1 , block_x - 1 );
	}

	if ( JugeMap ( game_situation->map[ block_y + 1 ][ block_x ] ) )
	{
		if ( game_situation->map[ block_y + 1 ][ block_x ] == '2' ) game_situation->broken_lifeup_block ++;
		BrokenBlock ( game_situation, block_y + 1, block_x );
	}

	if ( JugeMap ( game_situation->map[ block_y + 1 ][ block_x + 1 ] ) )
	{
		if ( game_situation->map[ block_y + 1 ][ block_x + 1 ] == '2' ) game_situation->broken_lifeup_block ++;
		BrokenBlock ( game_situation, block_y + 1, block_x + 1 );
	}

	refresh ();
	return;
}
