#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include "log.h"
#include "utility.h"

bool UpdataGame ( T_GAMESITUATION* game_situation )
{
	int32_t now_time, ball_diff_time;
	uint8_t x = 0, y = 0;

	if ( game_situation->before_ballupdate == 0 )
	{
		game_situation->before_ballupdate = GetMinutesMilli ();
	}
	else
	{
		now_time = GetMinutesMilli ();
		// 60分になると時間が繰り上がるので分が0分に戻り、計算結果が負になる場合があり、その場合は59分59秒999ミリ秒から前回時間を引いて現時点時間を足す
		ball_diff_time = ( now_time > game_situation->before_ballupdate )?( now_time - game_situation->before_ballupdate ):( ( 59*60*1000 + 59*1000 + 999 ) - game_situation->before_ballupdate + now_time );

		if ( ball_diff_time >= BALL_SPEED )
		{
			mvprintw ( game_situation->ball_y, game_situation->ball_x, " " );
			refresh ();
			switch ( game_situation->ball_direction )
			{
				case northwest:
					game_situation->ball_x -= 1;
					game_situation->ball_y -= 1;
				break;
				case north:
					game_situation->ball_y -= 1;
				break;
				case northeast:
					game_situation->ball_x += 1;
					game_situation->ball_y -= 1;
				break;
				case west:
					game_situation->ball_x -= 1;
				break;
				case east:
					game_situation->ball_x += 1;
				case southwest:
					game_situation->ball_x -= 1;
					game_situation->ball_y += 1;
				break;
				case south:
					game_situation->ball_y += 1;
				break;
				case southeast:
					game_situation->ball_x += 1;
					game_situation->ball_y += 1;
				break;
			}
			game_situation->before_ballupdate = GetMinutesMilli ();
		}

	}

	if ( game_situation->block_count == 0 )
	{
		clear ();
		getmaxyx ( stdscr, y, x );
		attrset ( COLOR_PAIR ( COLOR_YELLOW ) );
		mvprintw ( y / 2, ( x / 2 ) - 2, "CLEAR" );
		attrset ( COLOR_PAIR ( COLOR_WHITE ) );
		mvprintw ( MAX_HEIGHT - 2, MAX_WIDTH - 15, "qボタンで戻る" );
		refresh ();
		while ( GetCh ( 0 ) != 'q' );
		WriteLog ( false, "clear" );
		return false;
	}

	if ( game_situation->ball_y >= MAX_HEIGHT )
	{
		clear ();
		getmaxyx ( stdscr, y, x );
		attrset ( COLOR_PAIR ( COLOR_RED ) );
		mvprintw ( y / 2, ( x / 2 ) - 1, "OUT" );
		attrset ( COLOR_PAIR ( COLOR_WHITE) );
		mvprintw ( MAX_HEIGHT - 2, MAX_WIDTH - 15, "qボタンで戻る" );
		refresh ();
		while ( GetCh ( 0 ) != 'q' );
		WriteLog ( false, "field out" );
		return false;
	}

	return true;
}
