#ifndef __MENU_H__
#define __MENU_H__

#include "game_thread.h"

// インクルードファイルで実態を定義すると、リンクエラーが発生する
extern const char* Item [ ITEM_NUM ];

E_SELECT_ITEM MenuWindow ( T_GAMEDATA* game_data, bool a_mode );

#endif // #ifndef __MENU_H__