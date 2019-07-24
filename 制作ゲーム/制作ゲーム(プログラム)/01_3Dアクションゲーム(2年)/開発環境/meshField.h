////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���b�V�������� [meshField.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef enum
{
	MESHFIRLDTYPE_GREEN = 0,
	MESHFIRLDTYPE_BRIDGE,
	MESHFIRLDTYPE_SEAJPG,
	MESHFIRLDTYPE_SEAPNG,
	MESHFIRLDTYPE_RENGA,
	MESHFIRLDTYPE_STAIRS,
	MESHFIRLDTYPE_GREENPNG,
	MESHFIRLDTYPE_WALL,
	MESHFIRLDTYPE_BLACK,
	MESHFIRLDTYPE_MAX,
}MESHFIRLDTYPE;
typedef struct
{
	int nNumTex;
	LPDIRECT3DTEXTURE9	pTexture;	// �e�N�X�`���ւ̃|�C���^
	char *pFileName;	// �e�N�X�`���ւ̃|�C���^
}MeshFieldData;

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 rot;					// ����
	D3DXCOLOR col;						// �F
	D3DXMATRIX mtxWorld;				// ���[���h�}�g���b�N�X
	float fWidth;						// ��
	float fDepth;						// ���s��
	int nBlock_X;						// �u���b�NX
	int nBlock_Z;						// �u���b�NZ
	float fSlopeSin;					// �΂�
	float fSlopeSinMove;				// �΂߂̊p�x�v�Z
	float fSlopeCos;						// �΂�
	float fSlopeCosMove;					// �΂߂̊p�x�v�Z
	int nType;				// ���
	float fMoveVtx;					// ���_���Ƃ̍���
	D3DXVECTOR2 fTexmove;				// �e�N�X�`���̈ړ����x
	D3DXVECTOR2 fTexPos;				// �e�N�X�`���̈ړ����x
	int nNumVertex;						// ���_��
	int nNumIndex;						// �C���f�b�N�X��
	int nNumPolygon;					// �|���S����
	bool bCull;							// �J�����O���邩�ǂ���
	bool bCollision;							// �J�����O���邩�ǂ���
	bool bUse;							// �g�p����Ă��邩�ǂ���
}MeshField;

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);
bool CollisionMeshField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadiusWidth, float fRadiusHeight,MeshField **pMeshField);
void SetMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, int nBlock_X, int nBlock_Z, float fWidth, float fDepth,float fSlopeSin, bool bCull);
MeshField *GetMeshField(void);
MeshFieldData *GetMeshFieldData(void);
#endif
