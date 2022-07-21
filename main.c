#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <signal.h>
#include <locale.h>
#include "analysis_option.h"
#include "game_thread.h"
#include "help.h"
#include "log.h"
#include "menu.h"
#include "save_game.h"
#include "utility.h"

int main ( int argc, char** argv )
{
	bool a_mode = false;		// aモード
	E_SELECT_ITEM item = map_1;	// 選択項目
	FILE* save_fp;				// セーブファイルポインタ
	T_GAMEDATA game_data;		// ゲームデータ

	if ( !OpenLog () )
	{
		fprintf ( stderr, "[WARNING] 書き込み権限がありません。\nlogフォルダがディレクトリに存在することを確認し\nカレントディレクトリのすべてのフォルダの権限が770(rwxrwx---)であることを確認し再度実行してください。\n");
		exit ( 1 );
	}

	WriteLog ( false, "== start main ==" );

	// 初期化
	signal ( SIGINT, signal_handler );
	setlocale(LC_ALL, ""); // 日本語に対応する
	initscr ();
	keypad ( stdscr, TRUE );
	start_color ();
	init_pair ( COLOR_RED, COLOR_RED, COLOR_BLACK );
	init_pair ( COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK );
	init_pair ( COLOR_GREEN, COLOR_GREEN, COLOR_BLACK );
	init_pair ( COLOR_WHITE, COLOR_WHITE, COLOR_BLACK );
	curs_set ( 0 );
	crmode ();
	noecho ();
	WriteLog ( false, "finish init setting" );

#ifdef DEBUG_MODE
	game_data.life_count	= 5;
	game_data.clear_count	= 6;
	game_data.fail_count	= 0;
	game_data.open_map		= 7;
	memset ( game_data.pass_data, '\0', PASS_SIZE );
	WriteLog ( false, "create init data ( DEBUG ) " );
#else
	// データ読み出し
	save_fp = fopen ( SAVEDATAFILE, "rb" );
	if ( save_fp != NULL )
	{
		fread ( &game_data, sizeof ( T_GAMEDATA ), 1, save_fp );
		WriteLog ( false, "load save data" );
	}
	else
	{
		game_data.life_count	= 3;
		game_data.clear_count	= 0;
		game_data.fail_count	= 0;
		game_data.open_map		= 1;
		memset ( game_data.pass_data, '\0', PASS_SIZE );
		WriteLog ( false, "create init data" );
	}
	fclose ( save_fp );
#endif

	a_mode = ( argc > 1 )?AnalysisOption ( argc, argv, game_data ):false;	// aモード
	WriteLog ( false, "strat main thread" );
	while ( !Sig_flag && item != exit_game )
	{
		item = MenuWindow ( &game_data, a_mode );
		if ( Sig_flag ) break;

		switch ( item )
		{
			case exit_game:
				WriteLog ( false, "select exit" );
			break;
			case help:
				WriteLog ( false, "select help" );
				DrawHelpWindow ();
			break;
			default:
				WriteLog ( false, "select map %d", item );
				GameThread ( item, &game_data, a_mode );
			break;
		}
	}

	SaveGame ( game_data );
	WriteLog ( false, "finish save game" );
	endwin ();
	WriteLog ( false, "close main window" );
	WriteLog ( false, "== end main ==" );
	CloseLog ();

	return 0;
}