#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include "block.h"
#include "game_thread.h"
#include "game_utility.h"
#include "nomal_reflection.h"

void BlockDiagonalReflection ( T_GAMESITUATION* game_situation )
{
	uint8_t ball_x = game_situation->ball_x;
	uint8_t ball_y = game_situation->ball_y;
	char broken_block = '0';

	switch ( game_situation->ball_direction )
	{
		case northwest :
			if ( BlockNormalReflection ( game_situation ) ) break;
			if ( JugeMap ( ( broken_block = game_situation->map[ ( ball_y - 1 ) / BLOCKSIZE_HEIGHT ][ ( ball_x - 1 ) / BLOCKSIZE_WIDTH ] ) ) )
			{
				if ( broken_block == '2' ) game_situation->broken_lifeup_block ++;
				if ( broken_block == '3' ) ExplosionBlock ( game_situation, ball_y - 1, ball_x - 1 );
				game_situation->ball_direction = southeast;
				BrokenBlock ( game_situation, ( ball_y - 1 ) / BLOCKSIZE_HEIGHT, ( ball_x - 1 ) / BLOCKSIZE_WIDTH );
			}
		break;
		case north :
			BlockNormalReflection ( game_situation );
		break;
		case northeast :
			if ( BlockNormalReflection ( game_situation ) ) break;
			if ( JugeMap ( ( broken_block = game_situation->map[ ( ball_y - 1 ) / BLOCKSIZE_HEIGHT ][ ( ball_x + 1 ) / BLOCKSIZE_WIDTH ] ) ) )
			{
				if ( broken_block == '2' ) game_situation->broken_lifeup_block ++;
				if ( broken_block == '3' ) ExplosionBlock ( game_situation, ball_y - 1, ball_x + 1 );
				game_situation->ball_direction = southwest;
				BrokenBlock ( game_situation, ( ball_y - 1 ) / BLOCKSIZE_HEIGHT, ( ball_x + 1 ) / BLOCKSIZE_WIDTH );
			}
		break;
		case west :
		case east :
			BlockNormalReflection ( game_situation );
		break;
		case southwest :
			if ( BlockNormalReflection ( game_situation ) );
			if ( JugeMap ( ( broken_block = game_situation->map[ ( ball_y + 1 ) / BLOCKSIZE_HEIGHT ][ ( ball_x - 1 ) / BLOCKSIZE_WIDTH ] ) ) )
			{
				if ( broken_block == '2' ) game_situation->broken_lifeup_block ++;
				if ( broken_block == '3' ) ExplosionBlock ( game_situation, ball_y + 1, ball_x - 1 );
				game_situation->ball_direction = northeast;
				BrokenBlock ( game_situation, ( ball_y + 1 ) / BLOCKSIZE_HEIGHT, ( ball_x - 1 ) / BLOCKSIZE_WIDTH );
			}
		break;
		case south :
			BlockNormalReflection ( game_situation );
		break;
		case southeast :
			if ( BlockNormalReflection ( game_situation ) ) break;
			if ( JugeMap ( ( broken_block = game_situation->map[ ( ball_y + 1 ) / BLOCKSIZE_HEIGHT ][( ball_x + 1 ) / BLOCKSIZE_WIDTH ] ) ) )
			{
				if ( broken_block == '2' ) game_situation->broken_lifeup_block ++;
				if ( broken_block == '3' ) ExplosionBlock ( game_situation, ball_y + 1, ball_x + 1 );
				game_situation->ball_direction = northwest;
				BrokenBlock ( game_situation, ( ball_y + 1 ) / BLOCKSIZE_HEIGHT, ( ball_x + 1 ) / BLOCKSIZE_WIDTH );
			}
		break;
	}

	refresh ();
	return;
}
