////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���f������ [model.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define MAX_MODEL		(350)		// �ő吔
#define MAX_MODEL_TYPE	(40)		// ���f���̃^�C�v�̍ő吔
#define MAX_MODEL_COLLISION	(50)		// ���f���̔����
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef enum
{
	MODELTYPE_KINGYO = 0,
	MODELTYPE_TAKOYAKI,
	MODELTYPE_CHOKO,
	MODELTYPE_IKE,
	MODELTYPE_DAI,
	MODELTYPE_CHOTIN,
	MODELTYPE_TREE,
	MODELTYPE_STONE_1,
	MODELTYPE_STONE_2,
	MODELTYPE_STONE_3,
	MODELTYPE_STONE_4,
	MODELTYPE_STONE_5,
	MODELTYPE_POLE,
	MODELTYPE_JIMEN,
	MODELTYPE_ISH,
	MODELTYPE_TAIKO,
	MODELTYPE_CHOTIN2,
	MODELTYPE_TAKOYAKI_BALL,
	MODELTYPE_METEO,
	MODELTYPE_FISH,
	MODELTYPE_MAX,
}MODELTYPE;

typedef struct
{
	LPD3DXMESH pMesh;							// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;						// �}�e���A�����ւ̃|�C���^
	DWORD nNumMat;								// �}�e���A�����̐�
	LPDIRECT3DTEXTURE9 *pTextuer;			// �e�N�X�`��
	D3DXVECTOR3 CollisionPos[MAX_MODEL_COLLISION];
	float fWidthCollision[MAX_MODEL_COLLISION];
	float fDepthCollision[MAX_MODEL_COLLISION];
	float fHeightCollision[MAX_MODEL_COLLISION];
	float fRadiusCollision[MAX_MODEL_COLLISION];
	bool bCollison[MAX_MODEL_COLLISION];
	bool bCatch;
	bool bGetInfo;
	char *pFileName;
	int nNumModel;
}ModelData;
typedef struct
{
	LPD3DXBUFFER pBuffMat;				// �}�e���A�����ւ̃|�C���^
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 posOld;					// �O��̈ʒu
	D3DXVECTOR3 Initpos;				// �����ʒu
	D3DXVECTOR3 move;					// �ړ���
	D3DXCOLOR col;						// �J���[
	MODELTYPE nType;					// ���
	D3DXVECTOR3 Diffrot;				// �p�x�̍���
	D3DXVECTOR3 Destrot;				// �ړI�̊p�x
	D3DXVECTOR3 rot;					// �p�x
	D3DXMATRIX mtxWorld;				// ���[���h�}�g���b�N�X
	int nIdyShadow;						// �e�̔ԍ�
	int nIdyLine[MAX_MODEL_COLLISION];	// ���̔ԍ�
	int nIdy;							// �ԍ�
	bool bCollision;					// �����蔻��
	bool bUse;
	bool bDraw;
	bool bHit;
	bool bCatch;
	bool bFlag;
	int nCounter;
	float fCounter;
}Model;

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
int CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 rot, float fRadius);
int CollisionModelGetInfo(D3DXVECTOR3 *pPos, float fRadiusWidth, float fRadiusHeight, Model **pModel);
int CollisionModelMinMax(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadiusWidth, float fRadiusHeight, Model **pModel);
int SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE nType);
void SetCollisionModel(D3DXVECTOR3 pos, float fRadiusCollision,float fWidthCollision, float fDepthCollision,float fHeightCollision, MODELTYPE nType);
Model *GetModel(void);
ModelData *GetModelData(void);
#endif
