#include <stdio.h>
#include <stdbool.h>
#include "game_thread.h"
#include "paddle_reflection.h"

void PaddleReflection ( T_GAMESITUATION* game_situation )
{
	// ボールの進行方向がパドルに向いていない場合は処理をしない
	if ( game_situation->ball_direction < southwest ) return;
	// ボールがパドル位置にいない場合は処理しない
	if ( game_situation->paddle_x - ( game_situation->paddle_size / 2 ) - 1 > game_situation->ball_x || game_situation->paddle_x + ( game_situation->paddle_size / 2 ) + 1 < game_situation->ball_x ) return;
	if ( game_situation->ball_y != PADDLE_Y - 1 ) return;

	if ( game_situation->paddle_x - ( game_situation->paddle_size / 2 ) - 1 <= game_situation->ball_x && game_situation->paddle_x > game_situation->ball_x )
	{
		if ( game_situation->ball_direction != southeast && ( game_situation->paddle_x - ( game_situation->paddle_size / 2 ) - 1 ) == game_situation->ball_x ) return;
		game_situation->ball_direction = northwest;
	}
	else if ( game_situation->paddle_x == game_situation->ball_x )
	{
		game_situation->ball_direction = north;
	}
	else if ( game_situation->paddle_x < game_situation->ball_x && game_situation->paddle_x + ( game_situation->paddle_size / 2 ) + 1 >= game_situation->ball_x )
	{
		if ( game_situation->ball_direction != southwest && game_situation->paddle_x + ( game_situation->paddle_size / 2 ) + 1 == game_situation->ball_x ) return;
		game_situation->ball_direction = northeast;
	}

	if ( game_situation->paddle_size_inde )
	{
		game_situation->paddle_size += PADDLE_INDE;
	}
	else
	{
		game_situation->paddle_size -= PADDLE_INDE;
	}

	if ( game_situation->paddle_size == PADDLE_MAXSIZE || game_situation->paddle_size == PADDLE_MINSIZE ) game_situation->paddle_size_inde = !game_situation->paddle_size_inde;

	return;
}