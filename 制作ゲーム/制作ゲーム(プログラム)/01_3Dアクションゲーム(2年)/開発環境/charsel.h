//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// キャラクター選択処理 [charSel.h]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _CHARSEL_H_
#define _CHARSEL_H_		// 2重インクルード防止のマクロ定義

#include "main.h"
#include "player.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// マクロ定義
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define MAX_CHARSELTOP		(4)		// 頂点数
#define CHOTIN_HEIGHT		(150)	// 提灯の高さ
#define PICKUP_WIDTH		(340)	// キャラ表示ウィンドウの幅
#define PICKUP_HEIGHT		(310)	// キャラ表示ウィンドウの高さ
#define CHARWINDOW_WIDTH	(140)	// キャラウィンドウの幅
#define CHARWINDOW_HEIGHT	(140)	// キャラウィンドウの高さ
#define EXIT_WIDTH			(320)	// 戻るウィンドウの幅
#define EXIT_HEIGHT			(100)	// 戻るウィンドウの高さ

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 列挙体の定義
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef enum
{// 選択ウィンドウ種類
	CHARSELTYPE_BG = 0,			// 背景
	CHARSELTYPE_CHOUTINUP,		// 提灯(上)
	CHARSELTYPE_CHOUTINDOWN,	// 提灯(下)
	CHARSELTYPE_PLAYER1,		// 1Pの選択キャラクターウィンドウ
	CHARSELTYPE_PLAYER2,		// 2Pの選択キャラクターウィンドウ
	CHARSELTYPE_PLAYER3,		// 3Pの選択キャラクターウィンドウ
	CHARSELTYPE_PLAYER4,		// 4Pの選択キャラクターウィンドウ
	CHARSELTYPE_MATURI,			// まつり（女の子）
	CHARSELTYPE_AMANO,			// あまの（天狗）
	CHARSELTYPE_GOJOU,			// 悟浄（河童）
	CHARSELTYPE_MOMIJI,			// 紅葉（きつね）
	CHARSELTYPE_DONROID,		// ドンロイド（ロボット）
	CHARSELTYPE_RANDOM,			// ランダム
	CHARSELTYPE_EXIT,			// 戻る
	CHARSELTYPE_MAX,			// 総数
	CHARSELTYPE_NONE,			// どれでもない (総数に含まないため一番下に置いている)
}CHARSELTYPE;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 構造体の定義
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct
{// 選択するウィンドウ
	D3DXVECTOR3	pos;	// 位置
	float fWidth;		// 幅
	float fHeight;		// 高さ
	CHARSELTYPE type;	// 種類
	bool bUse;			// 使っているかどうか
	float moveTex;		// テクスチャの移動量
}Charsel;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// プロトタイプ宣言
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitCharsel(void);
void UninitCharsel(void);
void UpdateCharsel(void);
void DrawCharsel(void);
void MakeVertexCharsel(LPDIRECT3DDEVICE9 pDevice);
void SetCharsel(D3DXVECTOR3	pos, float fWidth, float fHeight, CHARSELTYPE type);
PLAYERTYPE CollisionCharsel(D3DXVECTOR3 pPos, float fWidth, float fHeight, PLAYERTYPE type);
#endif