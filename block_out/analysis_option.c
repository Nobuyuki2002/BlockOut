#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>
#include "log.h"
#include "utility.h"

bool AnalysisOption ( uint8_t argc, char** argv, T_GAMEDATA game_data )
{
	int opt;
	const char* optstring = "a:d";

	opterr = 0;

	while ( ( opt = getopt ( argc, argv, optstring ) ) != -1 )
	{
		WriteLog ( false, "loard option < %c >", opt );
		switch ( opt )
		{
			case 'a' :
				if ( strcmp ( optarg, game_data.pass_data ) == 0 )
				{
					WriteLog ( false, "match input pass" );
					return true;
				}
			break;
			case 'd' :
				Demo_mode = true;
			break;
		}
	}

	WriteLog ( true, "don't match input pass" );
	return false;
}