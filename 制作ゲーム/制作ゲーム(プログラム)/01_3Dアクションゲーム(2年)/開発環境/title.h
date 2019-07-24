//=============================================================================
//
// �^�C�g������ [title.h]
// Author : ���������@Sato_Aumi
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

//=============================================================================
// ��Ԑݒ�
//=============================================================================
typedef enum
{
	TITLETYPE_NONE = 0,
	TITLETYPE_LOGO,
	TITLETYPE_BOTTUN,
}TITLETYPE;

typedef enum
{
	LOGOSIZE_NONE = 0,
	LOGOSIZE_BIG,
	LOGOSIZE_SMALL,
}LOGOSIZE;

typedef enum
{
	BOTTNSTATE_NOMAL = 0,
	BOTTNSTATE_TRUE,
	BOTTNSTATE_FALSE,
}BOTTNSTATE;

//=============================================================================
// �|�[�Y�̍\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3		Pos;		//���S���W
	D3DXVECTOR3		PosHold;	//���l���W�̕ۑ��p
	D3DXVECTOR3		Size;		//�|���S���̃T�C�Y
	float			fCola;	//�ω�
	TITLETYPE		Type;		//�^�C�v
}Title;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif