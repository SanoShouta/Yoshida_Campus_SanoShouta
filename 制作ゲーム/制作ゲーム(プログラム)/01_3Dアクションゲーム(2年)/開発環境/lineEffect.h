//=============================================================================
//
// ラインエフェクト処理 [line.h]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#ifndef _LINEEFFECT_H_
#define _LINEEFFECT_H_

#include "main.h"

//=============================================================================
// エフェクトの種類
//=============================================================================
typedef enum
{
	LINETYPE_EFFECT_RAIN,
	LINETYPE_EFFECT_WINDY,
	LINETYPE_EFFECT_MAX,
}LINETYPEEFFECT;

//=============================================================================
// 構造体の定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3				pos;			//中心座標
	D3DXVECTOR3				move;			//中心座標
	D3DXVECTOR3				rot;			//向き
	D3DXMATRIX				mtxWorld;		//ワールドマトリックス
	D3DXCOLOR				color;			//色
	LINETYPEEFFECT			type;			//エフェクトの種類
	float					nLong;			//線の長さ
	bool					bUse;			//使用しているかどうか
}LineEffect;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitLineEffect(void);
void UninitLineEffect(void);
void UpdateLineEffect(void);
void DrawLineEffect(void);

void SetLineEffect(LINETYPEEFFECT type, bool bPlayEffect);
void CreateLineEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float nLong, LINETYPEEFFECT type);
#endif