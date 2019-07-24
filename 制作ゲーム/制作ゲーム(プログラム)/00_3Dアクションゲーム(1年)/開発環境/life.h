//=============================================================================
//
// ライフ処理 [life.h]
// Author : TEAM_Fascinator
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//****************************************************************************
#define MAX_LIFE (128)

//*****************************************************************************
// 構造体宣言
//****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//位置(中心座標)
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXVECTOR3 ParentPos;
	D3DXVECTOR3 ParentRot;
	D3DXCOLOR col;
	int nMaxLife;		//内部数値の最大値
	int nMaxLifeGuage; //見かけのHPの最大値
	bool bUse;
}LIFE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitLife(void);		//ライフ初期化
void UninitLife(void);		//ライフ終了
void UpdateLife(void);		//ライフ更新
void DrawLife(void);		//ライフ描画
void HitDamage(int nDamage);
void DecreaseMaxLife(int nLife);

#endif
