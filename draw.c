#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include "block.h"
#include "game_thread.h"

void DrawBlock ( T_GAMESITUATION game_situation )
{
	uint8_t x = 0, y = 0;

	/* ブロックの描画 */
	while ( y < MAX_HEIGHT )
	{
		while ( x < MAX_WIDTH )
		{
			if ( game_situation.map [ y / BLOCKSIZE_HEIGHT ][ x / BLOCKSIZE_WIDTH ] == '1' ) attrset ( COLOR_PAIR ( COLOR_WHITE ) );
			if ( game_situation.map [ y / BLOCKSIZE_HEIGHT ][ x / BLOCKSIZE_WIDTH ] == '2' ) attrset ( COLOR_PAIR ( COLOR_GREEN ) );
			if ( game_situation.map [ y / BLOCKSIZE_HEIGHT ][ x / BLOCKSIZE_WIDTH ] == '3' ) attrset ( COLOR_PAIR ( COLOR_RED ) );
			if ( game_situation.map [ y / BLOCKSIZE_HEIGHT ][ x / BLOCKSIZE_WIDTH ] == '0' )
			{
				x ++;
				continue;
			}

			mvprintw ( y, x, "#" );
			attrset ( COLOR_PAIR ( COLOR_WHITE ) );
			x ++;
		}
		x = 0;
		y ++;
	}

	refresh ();
}

void DrawGameWindow ( T_GAMESITUATION game_situation )
{
	uint8_t i = 0;

	move ( ( MAX_HEIGHT / 2 ) + 2, 0 );
	clrtobot ();

	/* パドルの描画 */
	for ( i = ( game_situation.paddle_size / 2 ); i > 0; i -- )
	{
		mvprintw ( PADDLE_Y, ( game_situation.paddle_x - i ) , "=" );
	}
	for ( i = 0; i <= ( game_situation.paddle_size / 2 ); i ++ )
	{
		mvprintw ( PADDLE_Y, ( game_situation.paddle_x + i ) , "=" );
	}

	/* ボールの描画 */
	mvprintw ( game_situation.ball_y, game_situation.ball_x, "@" );
	refresh ();
	return;
}