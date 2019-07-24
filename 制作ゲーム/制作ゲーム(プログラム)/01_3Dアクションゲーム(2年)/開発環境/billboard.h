////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �r���{�[�h�̏��� [billboard.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef enum
{
	BILLBOARDTYPE_EVENT = 0,
	BILLBOARDTYPE_EVENT_1 ,
	BILLBOARDTYPE_EVENT_2 ,
	BILLBOARDTYPE_SHOP ,
	BILLBOARDTYPE_MAX
}BILLBOARDTYPE;
typedef struct
{
	int nNumTex;
	LPDIRECT3DTEXTURE9	pTexture;	// �e�N�X�`���ւ̃|�C���^
	char *pFileName;	// �e�N�X�`���ւ̃|�C���^
}BillboardData;

typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 posOld;	// �O��̈ʒu
	D3DXVECTOR3 Initpos;// �����ʒu
	D3DXVECTOR3 move;	// ����
	D3DXVECTOR3 rot;	// ����
	D3DXMATRIX mtxWorld;// ���[���h�}�g���b�N�X
	float fWidth;		// ��
	float fHeight;		// ����
	float fDepth;		// ���s��
	BILLBOARDTYPE nType;	// ���
	int nIdyShadow;		// �e��ID
	int nCounter;		// �J�E���^�[
	bool bUse;			// �g�p����Ă��邩�ǂ���
}Billboard;

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, BILLBOARDTYPE nType,float fWidth,float fHeight);
void DeleteBillboard(BILLBOARDTYPE nType);
Billboard *GetBillboard(void);
BillboardData *GetBillboardData(void);
#endif
