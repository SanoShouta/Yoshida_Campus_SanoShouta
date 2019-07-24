//=============================================================================
//
// タイトル処理 [title.h]
// Author : 佐藤安純　Sato_Aumi
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

//=============================================================================
// 状態設定
//=============================================================================
typedef enum
{
	TITLETYPE_NONE = 0,
	TITLETYPE_LOGO,
	TITLETYPE_BOTTUN,
}TITLETYPE;

typedef enum
{
	LOGOSIZE_NONE = 0,
	LOGOSIZE_BIG,
	LOGOSIZE_SMALL,
}LOGOSIZE;

typedef enum
{
	BOTTNSTATE_NOMAL = 0,
	BOTTNSTATE_TRUE,
	BOTTNSTATE_FALSE,
}BOTTNSTATE;

//=============================================================================
// ポーズの構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3		Pos;		//中心座標
	D3DXVECTOR3		PosHold;	//中人座標の保存用
	D3DXVECTOR3		Size;		//ポリゴンのサイズ
	float			fCola;	//変化
	TITLETYPE		Type;		//タイプ
}Title;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif