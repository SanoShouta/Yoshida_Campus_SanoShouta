//=============================================================================
//
// �I����ʏ��� [select.h]
// Author : ���������@Sato_Aumi
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

#include "main.h"

//=============================================================================
// �|�[�Y�̏�Ԃ̎��
//=============================================================================
typedef enum
{//�|�[�Y�̏��
	SELECTSTATE_START = 0,
	SELECTSTATE_QUESTION,
	SELECTSTATE_TITLE,
	SELECTSTATE_MAX,
}SELECTSTATE;

typedef enum
{//�{�^���̏��
	BOTTUNSTATE_NOMAL = 0,
	BOTTUNSTATE_SELECT,
	BOTTUNSTATE_NONE,
	BOTTUNSTATE_MAX,
}BOTTUNSTATE;

//=============================================================================
// �|�[�Y�̍\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3		Pos;		//���S���W
	D3DXVECTOR3		PosHold;	//���l���W�̕ۑ��p
	D3DXVECTOR3		Size;		//�|���S���̃T�C�Y
	float			fChange;	//�ω�
	int				nTex;		//�e�N�X�`���̔ԍ�
	BOTTUNSTATE		state;		//��Ԑݒ�
}Select;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitSelect(void);
void UninitSelect(void);
void UpdateSelect(void);
void DrawSelect(void);

void Input(void);
#endif