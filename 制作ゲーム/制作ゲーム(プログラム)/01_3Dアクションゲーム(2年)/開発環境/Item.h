//=============================================================================
//
// アイテム処理 [item.h]
// Author : 佐藤安純 Sato_Asumi
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "meshField.h"
#include "model.h"

//=============================================================================
// アイテムの種類
//=============================================================================
typedef enum
{
	ITEMTYPE_CHANDY = 0,	//綿あめ
	ITEMTYPE_OMIKUZI,		//おみくじ
	ITEMTYPE_TAKOYAKI,		//たこ焼き
	ITEMTYPE_CUCUMBER,		//きゅうり
	ITEMTYPE_FRIED_TOUHU,	//油揚げ
	ITEMTYPE_LEAF,			//葉っぱ
	ITEMTYPE_SCREW,			//ねじ
	ITEMTYPE_MAX,
}ITEMTYPE;

//=============================================================================
// アイテムの出現位置の種類
//=============================================================================
typedef enum
{
	ITEMPOS_00 = 0,
	ITEMPOS_01,
	ITEMPOS_02,
	ITEMPOS_03,
	ITEMPOS_04,
	ITEMPOS_05,
	ITEMPOS_06,
	ITEMPOS_MAX,
}ITEMPOS;

//=============================================================================
// 構造体の定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3		pos;				//中心座標
	D3DXVECTOR3		move;				//移動量
	D3DXVECTOR3		posOld;				//前回の位置
	D3DXMATRIX		mtxWorld;			//ワールドマトリックス
	int				nIdxshadow;			//影の番号
	MeshField *		pMeshFieldLand;		// どの床に乗っているか
	Model			*pModel;			// 当たったモデルの情報
	ITEMTYPE		type;				//アイテムのタイプ
	float			fAttack;			//攻撃力
	float			fHeal;				//回復力
	float			fSpeed;				//スピード
	int				nLife;				// ライフ
	bool			bUse;				//使用しているかどうか
}Item;

typedef struct
{
	ITEMTYPE		type;				//アイテムのタイプ
	float			fAttack;			//攻撃力
	float			fHeal;				//回復力
	float			fSpeed;				//スピード
	int				nCounter;			//確率カウンター
	int				nLowProbability;	//最低確立
	int				Probability;		//確立
}Data;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

void SetItem(ITEMTYPE type);
D3DXVECTOR3 SetPos(int nItemPos);
void SetTex(int nIndex, int nType);
bool CollsionItem(D3DXVECTOR3 pos, float fRadiusWidth, float fRadiusHeight,float *pLife, float *Attack, float *Speed);
void DeleteItem(int nCntItem);
Item * GetItem(void);
#endif