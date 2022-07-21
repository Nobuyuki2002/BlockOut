#ifndef __LOAD_MAP_DATA_H__
#define __LOAD_MAP_DATA_H__

#include "game_thread.h"

#define MAPFILE_LEN 32
#define MAPFILE_BASE "./maps/map"
#define DEMOMAPFILE_BASE "./demo_maps/map"

/*****************************************************
 *                    関数原型宣言                    *
******************************************************/
bool LoadMapData ( uint8_t map_no, T_GAMESITUATION* game_situation );

#endif // #ifndef __LOAD_MAP_DATA_H__