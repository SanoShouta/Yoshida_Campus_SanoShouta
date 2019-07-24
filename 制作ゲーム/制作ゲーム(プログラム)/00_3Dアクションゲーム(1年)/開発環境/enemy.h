//=============================================================================
//
// エネミー処理 [Enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_ENEMY (2)

//#define MAX_PARTS (15)
#define MAX_E_PARTS (17)
//*****************************************************************************
// エネミーの構造体
//*****************************************************************************
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture = NULL;		//テクスチャへのポインタ
	LPD3DXMESH pMesh = NULL;		//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMat = NULL;	//マテリアル情報へのポインタ
	DWORD nNumMat;			//マテリアル情報の数
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posold;	//位置
	D3DXVECTOR3 rot;	//向き
	D3DXVECTOR3 VtxMinModel = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	D3DXVECTOR3 VtxMaxModel = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	D3DXVECTOR3 VecShot;	//ショット用ベクトル
	float fDestAngle;		//目的の角度
	D3DXVECTOR3 fDestAngle_Axis;		//目的の角度
	D3DXVECTOR3 fAngle_Axis;		//目的の角度
	float fAngle;			//差分
	float nIdxModelParent = -1;	//親モデルのインデックス
	char FileName[256];
}PARTS_E;

typedef enum
{
	ENEMYSTATE_NONE = 0,
	ENEMYSTATE_BACKHOME,
	ENEMYSTATE_DISCOVERY,
	ENEMYSTATE_MAX
}ENEMYSTATE;

typedef enum
{
	ENEMYSTATE2_NORMAL = 0,
	ENEMYSTATE2_DAMAGE,
	ENEMYSTATE2_MAX
}ENEMYSTATE2;


typedef enum
{
	ENEMYSTATUS_NEUTRAL = 0,
	ENEMYSTATUS_MOVE,
	ENEMYSTATUS_ATTACK,
	ENEMYSTATUS_JUMP,
	ENEMYSTATUS_LANDING,
	ENEMYSTATUS_GUARD,
	ENEMYSTATUS_DAMAGE1,
	ENEMYSTATUS_MAX
}ENEMYSTATUS;

//------------------------------------------------------------------------
// 当たり判定の構造体													 |
//------------------------------------------------------------------------
typedef struct
{
	D3DXMATRIX mtxWorldCollision;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fRadius;
	int StartFlame;
	int EndFlame;
	bool bUse;
	int nCntMotion;
	int nIdxMotion;
	int nIdxParent;
}ENEMYCOLLISION;

typedef struct
{
	DWORD nNumMatEnemy = 0;	//マテリアルの情報の数
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posold;	//位置
	D3DXVECTOR3 move;	//向き
	D3DXVECTOR3 rot;	//向き
	D3DXVECTOR3 VtxMinEnemy = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	D3DXVECTOR3 VtxMaxEnemy = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	D3DXVECTOR3 HomePoint;
	float DestHome;
	ENEMYSTATE state;
	ENEMYSTATE2 state2;
	ENEMYSTATUS status;
	bool bUseJump;
	float fDestAngle;					//目的の角度
	float fAngle;						//差分
	float fLength;
	int nIndexShadow;					//影の番号
	int nIndexSencer;					//センサー(当たり判定用)の番号
	int nIndexSencerEnemy;				//センサー(AI用)の番号
	int nIndexSencerEnableAttack;		//センサー(攻撃可能距離)の番号
	int nLife;
	bool bUse;
	bool bHit;
	int nCntCoolDown ;
	int nCoolDown = 200;
	ENEMYCOLLISION Collision;
	PARTS_E aModel[MAX_E_PARTS];
}ENEMY;




//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

void HitEnemy(int nDamage, int nCntEnemy);

ENEMY *GetEnemy(void);
ENEMYSTATUS *GetEnemyStatus(void);

void HitEnemy(int nDamage, int nCntEnemy);

bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *VtxMax, D3DXVECTOR3 *VtxMin);
int SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
void SetEnemyStatus(ENEMYSTATUS status, int nCntEnemy);
void DeleteEnemy(int nCntEnemy);
#endif
