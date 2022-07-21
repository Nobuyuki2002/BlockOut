#ifndef __NOMAL_REFLECTION_H__
#define __NOMAL_REFLECTION_H__

#include "game_thread.h"

void HorizonReflection ( T_GAMESITUATION* game_situation );
void VerticalReflection ( T_GAMESITUATION* game_situation );
bool BlockNormalReflection ( T_GAMESITUATION* game_situation );

#endif // #ifndef __NOMAL_REFLECTION_H__