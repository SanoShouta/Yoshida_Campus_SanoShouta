////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �e���� [shadow.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 posOld;	// �ʒu
	D3DXVECTOR3 move;	// �ړ���
	D3DXVECTOR3 rot;	// ����
	D3DXCOLOR col;		// �F
	D3DXMATRIX mtxWorld;// ���[���h�}�g���b�N�X
	float fWidth;		// ��
	float fDepth;		// ���s��
	bool bUse;			// �g�p����Ă��邩�ǂ���
}Shadow;
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos,D3DXVECTOR3 rot,float fWidth,float fDepth);
void SetPositionShadow(int nIdyShadow, D3DXVECTOR3 pos, D3DXVECTOR3 posOld);
void SetColorShadow(int nIdyShadow, float fAlpha);
void DeleteShadow(int nIdyShadow);
Shadow *GetShadow(void);
#endif
