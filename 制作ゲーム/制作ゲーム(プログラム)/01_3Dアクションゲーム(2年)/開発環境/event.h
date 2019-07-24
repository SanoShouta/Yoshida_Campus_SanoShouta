//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// イベント処理 [event.h]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _EVENT_H_
#define _EVENT_H_		// 2重インクルード防止のマクロ定義

#include "main.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// マクロ定義
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define EVENT_TOPMAX		(4)		// 頂点数

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 列挙体の定義
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef enum
{// イベントの種類
	EVENTTYPE_NONE = 0,			// 何もない
	EVENTTYPE_WATER,			// 洪水
	EVENTTYPE_FIRE,				// 火事
	EVENTTYPE_FALLING_ROCK,		// 複数の落石
	EVENTTYPE_FALLING_BIGROCK,	// 大きい岩の落石
	EVENTTYPE_METEORSHOWER,		// 流星群
	EVENTTYPE_METEORITE,		// 隕石
	EVENTTYPE_RAIN,				// 雨で見えにくく
	EVENTTYPE_THUNDER,			// 雷
	EVENTTYPE_FALLING_CHOUTIN,	// 提灯落下
	EVENTTYPE_FALLING_BRANCH,	// 木の枝落下
	EVENTTYPE_LEEF,				// 葉っぱで見えにくく
	EVENTTYPE_GUST,				// 突風
	EVENTTYPE_MAX,				// 最大数
}EVENTTYPE;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// プロトタイプ宣言
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetEvent(EVENTTYPE eventType);
void InitEvent();
void UninitEvent();
void UpdateEvent();
D3DXCOLOR GetEventColor(void);
void SetEventColor(D3DXCOLOR col);
EVENTTYPE GetEventType(void);
#endif