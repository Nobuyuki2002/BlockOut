#ifndef __GAME_THREAD_H__
#define __GAME_THREAD_H__

/*****************************************************
 *                      定数定義                      *
******************************************************/
#define MAX_WIDTH 100
#define MAX_HEIGHT 30
#define PASS_SIZE 14
#define PADDLE_Y 26 // パドルの中心のy座標
#define INIT_BALL_X 50
#define INIT_BALL_Y 22
#define INIT_PADDLE_SIZE 7 // 1以上,増分2ずつ
#define INIT_PADDLE_X 50 // パドルの中心のy座標
#define ITEM_NUM 9 // 選択項目数
#define BALL_SPEED 80
#define PADDLE_SENSIVE 0.67

/*****************************************************
 *                    列挙型定義                      *
******************************************************/
/* メニュー項目 */
typedef enum SELECT_ITEM
{
	map_1 = 0x01,
	map_2,
	map_3,
	map_4,
	map_5,
	map_6,
	map_7,
	help,
	exit_game,
} E_SELECT_ITEM;

/* 方角 */
typedef enum DIRECTION
{
	northwest = 0x01,
	north,
	northeast,
	west,
	east,
	southwest,
	south,
	southeast,
} E_DIRECTION;

/*****************************************************
 *                    構造体定義                      *
******************************************************/
/* ゲームセーブデータ */
#pragma pack(push,1)
typedef struct S_GAMEDATA
{
	uint8_t		life_count;				// 残り残基
	uint16_t	clear_count;			// クリア回数
	uint16_t	fail_count;				// 失敗回数
	uint8_t		open_map;				// 解放済みマップ番号
	char		pass_data[ PASS_SIZE ];	// 合言葉データ
} T_GAMEDATA;
#pragma pack(pop)

/* ゲーム状況データ */
typedef struct S_GAMESITUATION
{
	uint8_t		ball_x;								// ボールのx座標
	uint8_t		ball_y;								// ボールのy座標
	uint8_t		ball_direction;						// ボールの進行方向 ( 1 ~ 8 )
	uint8_t		paddle_x;							// パドルの中心のx座標
	uint8_t		paddle_size;						// パドルサイズ
	bool		paddle_size_inde;					// パドルサイズ増減(true:増, false:減)
	E_DIRECTION broken_lifeup_block;				// 破壊したライフアップブロックの数
	int32_t		before_ballupdate;					// 前回のボールのアップデート時間
	char		map[ MAX_HEIGHT ][ MAX_WIDTH + 1 ];	// マップデータ
	uint16_t	block_count;						// 残りブロック数
} T_GAMESITUATION;

/*****************************************************
 *                    関数原型宣言                    *
******************************************************/
void GameThread ( E_SELECT_ITEM select_map, T_GAMEDATA* game_data, bool a_mode );

#endif //#ifndef __GAME_THREAD_H__
