#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "game_thread.h"

#define BLOCKSIZE_WIDTH 2
#define BLOCKSIZE_HEIGHT 2

void BrokenBlock ( T_GAMESITUATION* game_situation, uint8_t block_y, uint8_t block_x );
void ExplosionBlock ( T_GAMESITUATION* game_situation, uint8_t block_y, uint8_t block_x );

#endif // #ifndef __BLOCK_H__