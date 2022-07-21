#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include "log.h"
#include "menu.h"
#include "draw_items.h"
#include "utility.h"

const char* Item [ ITEM_NUM ] = { "map_1", "map_2", "map_3", "map_4", "map_5", "map_6", "map_7", "help", "exit_game" }; // 実態を定義

E_SELECT_ITEM MenuWindow ( T_GAMEDATA* game_data, bool a_mode )
{
	WriteLog ( false, "== start MenuWindow ==" );
	int ch = 0;
	uint8_t open_map = 0;
	uint8_t x = 0, y = 0;
	E_SELECT_ITEM select_item = map_1;

	if ( a_mode )
	{
		open_map = 7;
	}
	else
	{
		open_map = game_data->open_map;
	}

	/* 画面を更新する */
	/* space または enterで決定 */
	do
	{
		clear ();
		mvprintw ( 0, 0, "BLOCK+++++" );
		mvprintw ( 1, 0, "BRAKE+++++" );
		getmaxyx ( stdscr, y, x );
		WriteLog ( false, "window size < x:%d, y:%d >", x, y );

		/* ステータス描画 */
		if ( a_mode )
		{
			mvprintw ( 1, ( x > 70 )?( x - 14 ):70, "ALL OPEN MODE" );
		}
		else
		{
			mvprintw ( 0, ( x > 70 )?( x - 10 ):70, "LIFE  : %d", game_data->life_count );
			mvprintw ( 1, ( x > 70 )?( x - 10 ):70, "CLEAR : %d", game_data->clear_count );
			mvprintw ( 2, ( x > 70 )?( x - 10 ):70, "FAIL  : %d", game_data->fail_count );
		}

		mvhline ( 3, 0, '=', x );
		if ( !a_mode && game_data->open_map == ITEM_NUM - 2 && game_data->pass_data[ 0 ] != '\0' )
		{
			mvprintw ( 19, 0, "ALL OPEN MODE PASS : %s", game_data->pass_data );
		}
		mvhline ( 20, 0, '=', x );
		WriteLog ( false, "draw status" );
		getmaxyx ( stdscr, y, x );
		if ( x != MAX_WIDTH || y != MAX_HEIGHT )
		{
			WriteLog ( false, "error window size" );
			attrset ( COLOR_PAIR ( COLOR_RED ) );
			mvprintw ( 2, 0, "画面サイズを100×30に調整してください(現在%3d×%3d)", x, y );
			attrset ( COLOR_PAIR ( COLOR_WHITE ) );
		}

		DrawItems ( select_item, open_map, x );
		WriteLog ( false, "draw items" );
		switch ( ( ch = GetCh ( 500 ) ) )
		{
			// 選択項目を上へ
			case KEY_UP:
				if ( select_item > 1 )
				{
					if ( select_item == ITEM_NUM - 1 )
					{
						select_item = open_map;
					}
					else
					{
						select_item --;
					}
				}
			break;
			// 選択項目を下へ
			case KEY_DOWN:
				if ( select_item < ITEM_NUM )
				{
					if ( select_item == open_map )
					{
						select_item = ITEM_NUM - 1;
					}
					else
					{
						select_item ++;
					}
				}
			break;
		}
		WriteLog ( false, "select item select_item < %s >", Item [ select_item -1 ] );
	} while ( ch != ' ' && ch != '\n' && !Sig_flag );

	WriteLog ( false, "== end MenuWindow ==" );
	return select_item;
}