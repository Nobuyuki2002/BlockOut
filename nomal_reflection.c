#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "block.h"
#include "game_thread.h"
#include "game_utility.h"
#include "log.h"
#include "nomal_reflection.h"
#include "reflection_utility.h"

void HorizonReflection ( T_GAMESITUATION* game_situation )
{
	if ( game_situation->ball_direction >= west ) return;
	if ( game_situation->ball_y != 0 ) return;
	game_situation->ball_direction = GetHorizonReflectionDirection ( game_situation->ball_direction );
	return;
}

void VerticalReflection ( T_GAMESITUATION* game_situation )
{
	if ( ( game_situation->ball_direction == northwest || game_situation->ball_direction == west || game_situation->ball_direction == southwest ) && game_situation->ball_x == 0 )
		game_situation->ball_direction = GetVerticalReflectionDirection ( game_situation->ball_direction );
	if ( ( game_situation->ball_direction == northeast || game_situation->ball_direction == east || game_situation->ball_direction == southeast ) && game_situation->ball_x == MAX_WIDTH - 1 )
		game_situation->ball_direction = GetVerticalReflectionDirection ( game_situation->ball_direction );

	return;
}

bool BlockNormalReflection ( T_GAMESITUATION* game_situation )
{
	uint8_t ball_x = game_situation->ball_x;
	uint8_t ball_y = game_situation->ball_y;
	char broken_block = '0';

	if ( ( game_situation->ball_direction == north || game_situation->ball_direction == northwest || game_situation->ball_direction == northeast ) && JugeMap ( ( broken_block = game_situation->map[ ( ball_y - 1 ) / BLOCKSIZE_HEIGHT ][ ball_x / BLOCKSIZE_WIDTH ] ) ) )
	{
		if ( broken_block == '2' ) game_situation->broken_lifeup_block ++;
		if ( broken_block == '3' ) ExplosionBlock ( game_situation, ball_y - 1, ball_x );
		game_situation->ball_direction = GetHorizonReflectionDirection ( game_situation->ball_direction );
		BrokenBlock ( game_situation, ( ball_y - 1 ) / BLOCKSIZE_HEIGHT, ball_x / BLOCKSIZE_WIDTH );
		return true;
	}

	if ( ( game_situation->ball_direction == south || game_situation->ball_direction == southwest || game_situation->ball_direction == southeast ) && JugeMap ( ( broken_block = game_situation->map[ ( ball_y + 1 ) / BLOCKSIZE_HEIGHT ][ ball_x / BLOCKSIZE_WIDTH ] ) ) )
	{
		if ( broken_block == '2' ) game_situation->broken_lifeup_block ++;
		if ( broken_block == '3' ) ExplosionBlock ( game_situation, ball_y + 1, ball_x );
		game_situation->ball_direction = GetHorizonReflectionDirection ( game_situation->ball_direction );
		BrokenBlock ( game_situation, ( ball_y + 1 ) / BLOCKSIZE_HEIGHT, ball_x / BLOCKSIZE_WIDTH );
		return true;
	}

	if ( ( game_situation->ball_direction == west || game_situation->ball_direction == northwest || game_situation->ball_direction == southwest ) && JugeMap ( ( broken_block = game_situation->map[ ball_y / BLOCKSIZE_HEIGHT ][ ( ball_x - 1 ) /BLOCKSIZE_WIDTH ] ) ) )
	{
		if ( broken_block == '2' ) game_situation->broken_lifeup_block ++;
		if ( broken_block == '3' ) ExplosionBlock ( game_situation, ball_y, ball_x - 1 );
		if ( game_situation->ball_direction == northwest || game_situation->ball_direction == southwest )
		{
			game_situation->ball_direction = GetVerticalReflectionDirection ( game_situation->ball_direction );
		}
		else
		{
			game_situation->ball_direction = GetHorizonReflectionDirection ( game_situation->ball_direction );
		}

		BrokenBlock ( game_situation, ball_y / BLOCKSIZE_HEIGHT, ( ball_x - 1 ) / BLOCKSIZE_WIDTH );
		return true;
	}

	if ( ( game_situation->ball_direction == east || game_situation->ball_direction == northeast || game_situation->ball_direction == southeast ) && JugeMap ( ( broken_block = game_situation->map[ ball_y / BLOCKSIZE_HEIGHT ][ ( ball_x + 1 ) / BLOCKSIZE_WIDTH ] ) ) )
	{
		if ( broken_block == '2' ) game_situation->broken_lifeup_block ++;
		if ( broken_block == '3' ) ExplosionBlock ( game_situation, ball_y, ball_x + 1 );
		if ( game_situation->ball_direction == northeast || game_situation->ball_direction == southeast )
		{
			game_situation->ball_direction = GetVerticalReflectionDirection ( game_situation->ball_direction );
		}
		else
		{
			game_situation->ball_direction = GetHorizonReflectionDirection ( game_situation->ball_direction );
		}

		BrokenBlock ( game_situation, ball_y / BLOCKSIZE_HEIGHT, ( ball_x + 1 ) / BLOCKSIZE_WIDTH );
		return true;
	}

	return false;
}
