////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ��̏��� [sky.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SKY_H_
#define _SKY_H_

#include "main.h"
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef enum
{
	SKYTYPE_0 = 0,
	SKYTYPE_MAX
}SKYTYPE;

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuff = NULL;						// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	int nNumVertex;	// ���_��
	int nNumIndex;	// �C���f�b�N�X��
	int nNumPolygon;	// �|���S����

	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 rot;	// ����
	D3DXCOLOR col;		// �F
	D3DXMATRIX mtxWorld;// ���[���h�}�g���b�N�X
	float fWidth;		// ��
	float fHeight;		// ����
	float fDepth;		// ���s��
	float fLength;		// ���a
	SKYTYPE nType;	// ���
	bool bUse;			// �g�p����Ă��邩�ǂ���
}Sky;

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void InitSky(void);
void UninitSky(void);
void UpdateSky(void);
void DrawSky(void);
void SetSky(D3DXVECTOR3 pos,float fLength);
#endif
