#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>
#include "block_diagonal_reflection.h"
#include "game_thread.h"
#include "nomal_reflection.h"
#include "paddle_reflection.h"

void BlockReflection ( T_GAMESITUATION* game_situation )
{
	BlockNormalReflection ( game_situation );
	BlockDiagonalReflection ( game_situation );
}

void Reflection ( T_GAMESITUATION* game_situation )
{
	BlockReflection ( game_situation );
	HorizonReflection ( game_situation );
	VerticalReflection ( game_situation );
	PaddleReflection ( game_situation );
	return;
}