#ifndef __REFLECTION_UTILITY_H__
#define __REFLECTION_UTILITY_H__

#include "game_thread.h"

E_DIRECTION GetBaseReflectionDirection ( E_DIRECTION direction );
E_DIRECTION GetHorizonReflectionDirection ( E_DIRECTION direction );
E_DIRECTION GetVerticalReflectionDirection ( E_DIRECTION direction );

#endif // #ifndef __REFLECTION_UTILITY_H__