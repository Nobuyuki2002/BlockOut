#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "game_utility.h"
#include "log.h"
#include "utility.h"

void UpdateSaveData ( T_GAMEDATA* game_data, T_GAMESITUATION game_situation, uint8_t map_no, bool a_mode )
{
	WriteLog ( false, "== start UpdateSaveData ==" );
	if ( Sig_flag || a_mode )
	{
		WriteLog ( false, "don't update save data" );
		return;
	}

	game_data->life_count += game_situation.broken_lifeup_block;

	if ( game_situation.ball_y >= MAX_HEIGHT )
	{
		game_data->fail_count ++;
		game_data->life_count --;
		WriteLog ( false, "game fail" );

		if ( game_data->life_count <= 0 )
		{
			/* リセット */
			game_data->life_count	= 3;
			game_data->clear_count	= 0;
			game_data->fail_count	= 0;
			game_data->open_map		= 1;
			WriteLog ( false, "reset save data" );
		}
	}
	else
	{
		game_data->clear_count ++;
		WriteLog ( false, "game clear" );
		if ( map_no == ITEM_NUM - 2 && game_data->pass_data[ 0 ] == '\0' )
		{
			CreateClearPass ( game_data );
		}
		else if ( ( game_data->open_map < ITEM_NUM - 2 ) && ( game_data->open_map == map_no ) )
		{
			game_data->open_map ++;
			WriteLog ( false, "new open < %d >", game_data->open_map );
		}
	}

	WriteLog ( false, "update save data < life : %d | clear : %d | fail : %d | open : %d >", game_data->life_count, game_data->clear_count, game_data->fail_count, game_data->open_map );
	WriteLog ( false, "== end UpdateSaveData ==" );
	return;
}
