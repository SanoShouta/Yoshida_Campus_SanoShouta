////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �K�[�h���� [guard.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GUARD_H_
#define _GUARD_H_

#include "main.h"
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef enum
{
	GUARDTYPE_0 = 0,
	GUARDTYPE_MAX
}GUARDTYPE;

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
	int nIdx;			// �ԍ�
	GUARDTYPE nType;	// ���
	bool bUse;			// �g�p����Ă��邩�ǂ���
}Guard;

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void InitGuard(void);
void UninitGuard(void);
void UpdateGuard(void);
void DrawGuard(void);
void SetGuard(int nIdx, D3DXVECTOR3 pos,float fLength);
void UnSetGuard(int nIdx, float fLength);
#endif
