#include <ncurses.h>
#include <unistd.h>
#include "game_thread.h"

void DrawItems ( E_SELECT_ITEM select_item, uint8_t open_map, uint8_t x )
{
	int item_count = 1;

	/* 項目の描画 */
	for ( item_count = 1; item_count <= ITEM_NUM; item_count ++ )
	{
		if ( item_count == select_item )
		{
			attrset ( COLOR_PAIR ( COLOR_YELLOW ) );
		}

		switch ( item_count )
		{
			case ITEM_NUM - 1:
				mvprintw ( 24, ( x / 2 ) - 2, "HELP" );
			break;
			case ITEM_NUM:
				mvprintw ( 25, ( x / 2 ) - 2, "EXIT" );
			break;
			default:
				if ( item_count < open_map )
				{
					mvprintw ( 3 + item_count, 0, "map%d", item_count );
				}
				else if ( item_count == open_map )
				{
					mvprintw ( 3 + item_count, 0, "map%d", item_count );
					item_count = ITEM_NUM - 2;
				}
			break;
		}

		attrset ( COLOR_PAIR ( COLOR_WHITE ) );
	}
	refresh ();
}