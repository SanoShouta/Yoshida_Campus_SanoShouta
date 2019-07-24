//=============================================================================
//
// ポリゴン処理 [flontpolygon.h]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#ifndef _FLONTPOLYGON_H_
#define _FLONTPOLYGON_H_

#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_FLONTPOLYGON	(128)		//背景の最大数

//=============================================================================
// ポリゴンの種類
//=============================================================================
typedef enum
{
	FLONTTYPE_CHOTIN = 0,
	FLONTTYPE_CYARACTOR,
	FLONTTYPE_COMMENT,
	FLONTTYPE_READY,		// バトル開始準備完了
	FLONTTYPE_NOMAL,
	FLONTTYPE_UI,
	FLONTTYPE_FACE_HUMAN,
	FLONTTYPE_FACE_TENGU,
	FLONTTYPE_FACE_KAPPA,
	FLONTTYPE_FACE_FOX,
	FLONTTYPE_FACE_ROBOT,
	FLONTTYPE_NARRATION,
	FLONTTYPE_MAX
}FLONTTYPE;

//コメントの種類
typedef enum
{
	COMMENTTYPE_BTTLE = 0,
	COMMENTTYPE_QUESTION,
	COMMENTTYPE_TITLE,
	COMMENTTYPE_MAX
}COMMENTTYPE;
typedef enum
{
	FLONT_TEXTYPE_CHOTIN = 0,
	FLONT_TEXTYPE_CHARACTOR,
	FLONT_TEXTYPE_HUKIDASHI,
	FLONT_TEXTYPE_READY,
	FLONT_TEXTYPE_TITLE,
	FLONT_TEXTYPE_UI,
	FLONT_TEXTYPE_FASE,
	FLONT_TEXTYPE_SETTING,
	FLONT_TEXTYPE_START,
	FLONT_TEXTYPE_GAMEEND,
	FLONT_TEXTYPE_FG,
	FLONT_TEXTYPE_BG,
	FLONT_TEXTYPE_TIMEUP,
	FLONT_TEXTYPE_MAX
}FLONT_TEXTYPE;

//=============================================================================
// 構造体の定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3		pos;			//中心座標
	float			fWidth;			//幅
	float			fHight;			//高さ
	float			fUv;			//UV値
	int				nTexNum;		//テクスチャの番号
	FLONTTYPE		type;			//タイプ
	D3DXCOLOR		col;			//色
	bool			bUse;			//使用しているかどうか
}FlontPolygon;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitFlontPolygon(void);
void UninitFlontPolygon(void);
void UpdateFlontPolygon(void);
void DrawFlontPolygon(void);

int SetFlontPolygon(int nTexNum, D3DXVECTOR3 pos, float fWidth, float fHight, FLONTTYPE type);

void SetTexture(int nIdx, int nNumComment);
void ReleaseAllFlontPolygon();
void DeleteFlontPolygon(int nIdx);
FlontPolygon * GetFlontPolygon(void);
#endif