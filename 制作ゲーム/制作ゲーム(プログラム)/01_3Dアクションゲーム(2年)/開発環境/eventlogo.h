//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// イベントロゴ処理 [eventlogo.h]
// Author : suzuki
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _EVENTLOGO_H_
#define _EVENTLOGO_H_

#include "main.h"
#include "event.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// マクロ定義
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define EVENTLOGO_WIDTH			(130)										// 幅
#define EVENTLOGO_HEIGHT		(70)										// 高さ
#define EVENTLOGO_POS_X			(SCREEN_WIDTH - EVENTLOGO_WIDTH - 20.0f)	// X座標 (右端 - 幅 - 右端との隙間)
#define EVENTLOGO_POS_Y			(SCREEN_HEIGHT - EVENTLOGO_HEIGHT - 20.0f)	// Y座標 (下端 - 高さ - 下端との隙間)
#define EVENTLOGO_MAX			(4)											// 頂点数
#define EVENTLOGO_MOVESPEED		(5.0f)										// 動く速度
#define EVENTLOGO_NUMTIMES		(5)											// テロップを出す回数(周回)
#define EVENTLOGO_APPEARSPEED	(1.0f/ (60.0f * 0.5f))						// 演出スピード( Alphaの最大値 / (フレーム数 * 秒数))
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 列挙体の定義
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef enum
{// イベントの種類
	EVENTLOGOTEX_NONE = 0,			// 何もない
	EVENTLOGOTEX_WATER,				// 洪水
	EVENTLOGOTEX_FIRE,				// 火事
	EVENTLOGOTEX_FALLING_ROCK,		// 落石
	EVENTLOGOTEX_METEORITE,			// 隕石
	EVENTLOGOTEX_RAIN,				// 雨
	EVENTLOGOTEX_THUNDER,			// 雷
	EVENTLOGOTEX_FALLING_OBJECT,	// 落下
	EVENTLOGOTEX_GUST,				// 突風
	EVENTLOGOTEX_MAX,				// 最大数
}EVENTLOGOTEX;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 構造体の定義
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct
{// カーソル
	D3DXVECTOR3		pos;			// 現在の位置
	D3DXVECTOR3		posOld;			// 前回の位置
	D3DXVECTOR3		move;			// 移動量
	D3DXCOLOR		col;			// 色
	float			fWidth;			// 幅
	float			fHeight;		// 高さ
	int				nCountDiaplay;	// 表示中のカウント
	int				nNumTimes;		// ロゴを出した回数
	bool			bUse;			// 使っているかどうか
	bool			bAlpha;			// 透明かどうか
	EVENTTYPE		type;			// イベントの種類
	EVENTLOGOTEX	texType;		// テクスチャの種類
}EVENTLOGO;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// プロトタイプ宣言
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitEventlogo(void);
void UninitEventlogo(void);
void UpdateEventlogo(void);
void DrawEventlogo(void);
void SetEventlogo(D3DXVECTOR3 pos, float fWidth, float fHeight, EVENTTYPE type);
void DeleteEventLogo(void);
#endif