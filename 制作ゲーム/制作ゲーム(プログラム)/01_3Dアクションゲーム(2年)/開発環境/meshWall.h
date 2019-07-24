////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���b�V���Ǐ��� [meshWall.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef struct
{
	int nNumTex;
	LPDIRECT3DTEXTURE9	pTexture;	// �e�N�X�`���ւ̃|�C���^
	char	*pFileName;	// �e�N�X�`���ւ̃|�C���^
}MeshWallData;

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 rot;					// ����
	D3DXCOLOR col;						// �F
	D3DXMATRIX mtxWorld;				// ���[���h�}�g���b�N�X
	float fWidth;						// ��
	float fHeight;						// ����
	int nBlock_X;						// �u���b�NX
	int nBlock_Y;						// �u���b�NY
	int nType;					// ���
	float fMoveVtx;						// ���_���Ƃ̓���
	float fTexmoveMesh;					// �e�N�X�`���̈ړ����x
	int nNumVertex;						// ���_��
	int nNumIndex;						// �C���f�b�N�X��
	int nNumPolygon;					// �|���S����
	bool bCull;							// �J�����O���邩���Ȃ���
	bool bCollision;					// ���肠�邩�Ȃ���
	bool bUse;							// �g�p����Ă��邩�ǂ���
}MeshWall;

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
bool CollisionMeshWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadiusWidth, float fRadiusHeight);
bool CollisionVecMeshWall(D3DXVECTOR3 pPos, D3DXVECTOR3 posOld, D3DXVECTOR3 *pMove, float fRadiusWidth, float fRadiusHeight);
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, int nBlock_X, int nBlock_Y, float fWidth, float fHeight, bool bCull);
MeshWall *GetMeshWall(void);
MeshWallData *GetMeshWallData(void);

#endif
