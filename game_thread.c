#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include "draw.h"
#include "game_thread.h"
#include "game_utility.h"
#include "load_map_data.h"
#include "log.h"
#include "reflection.h"
#include "update_game.h"
#include "update_savedata.h"
#include "utility.h"

void GameThread ( E_SELECT_ITEM select_map, T_GAMEDATA* game_data, bool a_mode )
{
	WriteLog ( false, "==== start GameThread ====" );

	int ch = 0;
	uint8_t x = 0, y = 0;
	bool error_flag = false;
	T_GAMESITUATION game_situation;

	clear ();
	getmaxyx ( stdscr, y, x );

	if ( !LoadMapData ( select_map, &game_situation ) )
	{
		WriteLog ( true, "broken map data" );
		mvprintw ( y/2, ( x/2 - 14 ), "マップデータが破損しています" );
		mvprintw ( MAX_HEIGHT - 2, MAX_WIDTH - 15, "qボタンで戻る" );
		refresh ();
		while ( GetCh ( 0 ) != 'q' );
		return;
	}

	WriteLog ( false, "start game init setting" );
	/* ゲーム状況初期化 */
	game_situation.ball_x = INIT_BALL_X;
	game_situation.ball_y = INIT_BALL_Y;
	game_situation.ball_direction = south;
	game_situation.paddle_x = INIT_PADDLE_X;
	game_situation.broken_lifeup_block = 0;
	game_situation.paddle_size = INIT_PADDLE_SIZE;
	game_situation.paddle_size_inde = false;

	/* ゲーム初期画面描画 */
	DrawBlock ( game_situation );
	DrawGameWindow ( game_situation );
	mvprintw ( INIT_BALL_Y + 2, INIT_BALL_X - 13, "スペースキーを押して下さい" );
	refresh ();

	while ( ch != ' ' && !Sig_flag ) ch = GetCh ( 500 );
	while ( !Sig_flag )
	{
		getmaxyx ( stdscr, y, x );
		if ( x != MAX_WIDTH || y != MAX_HEIGHT )
		{
			error_flag = true;
			clear ();
			mvprintw ( y/2, ( x/2 - 16 ), "画面サイズを100×30にしてください" );
			refresh ();
			WriteLog ( true, "window size error window" );
			sleep ( 2 );
			continue;
		}

		if ( error_flag )
		{
			error_flag = false;
			clear ();
			DrawBlock ( game_situation );
			DrawGameWindow ( game_situation );
		}

		ch = GetCh ( BALL_SPEED * PADDLE_SENSIVE );
		switch ( ch )
		{
			case KEY_LEFT :
				if ( game_situation.paddle_x != 0 )
				{
					game_situation.paddle_x --;
				}
			break;
			case KEY_RIGHT :
			if ( game_situation.paddle_x != MAX_WIDTH - 1 )
			{
				game_situation.paddle_x ++;
			}
			break;
		}

		Reflection ( &game_situation );
		if ( !UpdataGame ( &game_situation ) ) break;
		DrawGameWindow ( game_situation );
	}

	UpdateSaveData ( game_data, game_situation, select_map, a_mode );

	if ( game_data->life_count == 3 && game_data->clear_count == 0 && game_data->fail_count == 0 && game_data->open_map == 1 && !Sig_flag )
	{
		attrset ( COLOR_PAIR ( COLOR_RED ) );
		mvprintw ( y / 2, ( x / 2 ) - 4, "GAME OVER" );
		attrset ( COLOR_PAIR ( COLOR_WHITE) );
		mvprintw ( MAX_HEIGHT - 2, MAX_WIDTH - 15, "qボタンで戻る" );
		refresh ();
		while ( GetCh ( 0 ) != 'q' );
	}

	WriteLog ( false, "close game window" );
	Sig_flag = false;
	WriteLog ( false, "== end GameThread ==" );

	return;
}