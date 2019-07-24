//=============================================================================
//
// 選択画面処理 [select.h]
// Author : 佐藤安純　Sato_Aumi
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

#include "main.h"

//=============================================================================
// ポーズの状態の種類
//=============================================================================
typedef enum
{//ポーズの状態
	SELECTSTATE_START = 0,
	SELECTSTATE_QUESTION,
	SELECTSTATE_TITLE,
	SELECTSTATE_MAX,
}SELECTSTATE;

typedef enum
{//ボタンの状態
	BOTTUNSTATE_NOMAL = 0,
	BOTTUNSTATE_SELECT,
	BOTTUNSTATE_NONE,
	BOTTUNSTATE_MAX,
}BOTTUNSTATE;

//=============================================================================
// ポーズの構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3		Pos;		//中心座標
	D3DXVECTOR3		PosHold;	//中人座標の保存用
	D3DXVECTOR3		Size;		//ポリゴンのサイズ
	float			fChange;	//変化
	int				nTex;		//テクスチャの番号
	BOTTUNSTATE		state;		//状態設定
}Select;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitSelect(void);
void UninitSelect(void);
void UpdateSelect(void);
void DrawSelect(void);

void Input(void);
#endif