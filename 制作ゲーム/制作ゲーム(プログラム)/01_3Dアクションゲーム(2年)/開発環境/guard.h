////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ガード処理 [guard.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GUARD_H_
#define _GUARD_H_

#include "main.h"
//******************************************************************************************************************************
// 構造体定義
//******************************************************************************************************************************
typedef enum
{
	GUARDTYPE_0 = 0,
	GUARDTYPE_MAX
}GUARDTYPE;

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = NULL;						// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 pIdxBuff = NULL;						// インデックスバッファへのポインタ
	int nNumVertex;	// 頂点数
	int nNumIndex;	// インデックス数
	int nNumPolygon;	// ポリゴン数

	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 rot;	// 向き
	D3DXCOLOR col;		// 色
	D3DXMATRIX mtxWorld;// ワールドマトリックス
	float fWidth;		// 幅
	float fHeight;		// 高さ
	float fDepth;		// 奥行き
	float fLength;		// 半径
	int nIdx;			// 番号
	GUARDTYPE nType;	// 種類
	bool bUse;			// 使用されているかどうか
}Guard;

//******************************************************************************************************************************
// プロトタイプ宣言
//******************************************************************************************************************************
void InitGuard(void);
void UninitGuard(void);
void UpdateGuard(void);
void DrawGuard(void);
void SetGuard(int nIdx, D3DXVECTOR3 pos,float fLength);
void UnSetGuard(int nIdx, float fLength);
#endif
