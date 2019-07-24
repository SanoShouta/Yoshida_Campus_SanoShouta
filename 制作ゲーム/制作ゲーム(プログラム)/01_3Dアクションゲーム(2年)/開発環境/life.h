////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���C�t���� [life.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef enum
{
	LIFETEX_BG =0,
	LIFETEX_BG2,
	LIFETEX_GAGERED,
	LIFETEX_GAGE,
	LIFETEX_MAX
}LIFETEX;

typedef struct
{
	LPDIRECT3DTEXTURE9	pTexture;	// �e�N�X�`���ւ̃|�C���^
	char	*pFileName;	// �e�N�X�`���ւ̃|�C���^
}LifeData;

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
	int nNumVertex;						// ���_��
	int nNumIndex;						// �C���f�b�N�X��
	int nNumPolygon;					// �|���S����
	int nPatternAnim;					// �p�^�[��
	int nCounterAnim;					// �J�E���^�[
	bool bUse;							// �g�p����Ă��邩�ǂ���
	bool bUseDown;
	int nDrawDown;						// �����p
	bool bDownRed;						// �Ԃ����C�t
	int nDownRedCounter;				// �Ԃ����C�t�����Ԋu�ۊ�
}Life;
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
void SetLife(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nType, int nBlock_X, int nBlock_Y, float fWidth, float fHeight,bool bUseDown);
Life *GetLife(void);
LifeData *GetLifeData(void);
void SetPlayerLife(int nLife, int nIdy);
void GetPlayerLife(int nLife, int nIdy);
#endif
