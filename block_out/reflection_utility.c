#include <stdio.h>
#include <stdbool.h>
#include "game_thread.h"
#include "reflection_utility.h"

E_DIRECTION GetBaseReflectionDirection ( E_DIRECTION direction )
{
	switch ( direction )
	{
		case north :
			return south;
		case south :
			return north;
		case west :
			return east;
		case east :
			return west;
		default :
			return direction;
	}
}

E_DIRECTION GetHorizonReflectionDirection ( E_DIRECTION direction )
{
	switch ( direction )
	{
		case northwest :
			return southwest;
		case northeast :
			return southeast;
		case southwest :
			return northwest;
		case southeast :
			return northeast;
		default :
			return GetBaseReflectionDirection ( direction );
	}
}

E_DIRECTION GetVerticalReflectionDirection ( E_DIRECTION direction )
{
	switch ( direction )
	{
		case northwest :
			return northeast;
		case northeast :
			return northwest;
		case southwest :
			return southeast;
		case southeast :
			return southwest;
		default :
			return GetBaseReflectionDirection ( direction );
	}
}
