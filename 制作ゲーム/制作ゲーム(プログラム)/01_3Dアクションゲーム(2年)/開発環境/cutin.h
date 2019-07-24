//=============================================================================
//
// カットイン処理 [cutin.h]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#ifndef _CUTIN_H_
#define _CUTIN_H_

#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_CUTIN	(10)		//背景の最大数
#define CUT_TEXTYPE_MAX	(3)	//読み込むテクスチャの最大数

//=============================================================================
// ポリゴンの種類
//=============================================================================
typedef enum
{
	CUTTYPE_KYARACTOR = 0,
	CUTTYPE_SKILL,
	CUTTYPE_MAX,
}CUTTYPE;

//キャラクターの種類
typedef enum
{
	CHARATAYPE_HUMAN = 0,
	CHARATAYPE_TENGU,
	CHARATAYPE_KAPPA,
	CHARATAYPE_FOX,
	CHARATAYPE_ROBOT,
	CHARATAYPE_MAX,
}CHARATAYPE;

//カットインの状態設定
typedef enum
{
	CUTSTATE_NONE = 0,
	CUTSTATE_IN,
	CUTSTATE_OPEN,
	CUTSTATE_NOMAL,
	CUTSTATE_OUT,
}CUTSTATE;

//カットインの状態設定
typedef enum
{
	NAMESTATE_NONE = 0,
	NAMESTATE_IN,
	NAMESTATE_OUT,
}NAMESTATE;

//=============================================================================
// 構造体の定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3		pos;			//中心座標
	D3DXVECTOR3		size;			//サイズ
	D3DXVECTOR3		move;			//移動量
	float			cola;		
	int				nTexNum;		//テクスチャの番号
	CUTTYPE			type;			//タイプ
	CHARATAYPE		chara;			//キャラクターのタイプ
	CUTSTATE		CutState;		//カットインの状態設定
	NAMESTATE		NameState;		//吹き出しの状態設定
	bool			bUse;			//使用しているかどうか
	bool			bMove;			//移動量のリセット
}Cut;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitCut(void);
void UninitCut(void);
void UpdateCut(void);
void DrawCut(void);

int SetCut(int nTexNum, D3DXVECTOR3 pos, CHARATAYPE chara , CUTTYPE type);

void DeleteAllCut(void);
Cut * GetCut(void);
void SetCutState(CUTSTATE state);
#endif
