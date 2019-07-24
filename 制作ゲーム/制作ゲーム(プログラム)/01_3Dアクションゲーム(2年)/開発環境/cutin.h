//=============================================================================
//
// �J�b�g�C������ [cutin.h]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#ifndef _CUTIN_H_
#define _CUTIN_H_

#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_CUTIN	(10)		//�w�i�̍ő吔
#define CUT_TEXTYPE_MAX	(3)	//�ǂݍ��ރe�N�X�`���̍ő吔

//=============================================================================
// �|���S���̎��
//=============================================================================
typedef enum
{
	CUTTYPE_KYARACTOR = 0,
	CUTTYPE_SKILL,
	CUTTYPE_MAX,
}CUTTYPE;

//�L�����N�^�[�̎��
typedef enum
{
	CHARATAYPE_HUMAN = 0,
	CHARATAYPE_TENGU,
	CHARATAYPE_KAPPA,
	CHARATAYPE_FOX,
	CHARATAYPE_ROBOT,
	CHARATAYPE_MAX,
}CHARATAYPE;

//�J�b�g�C���̏�Ԑݒ�
typedef enum
{
	CUTSTATE_NONE = 0,
	CUTSTATE_IN,
	CUTSTATE_OPEN,
	CUTSTATE_NOMAL,
	CUTSTATE_OUT,
}CUTSTATE;

//�J�b�g�C���̏�Ԑݒ�
typedef enum
{
	NAMESTATE_NONE = 0,
	NAMESTATE_IN,
	NAMESTATE_OUT,
}NAMESTATE;

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3		pos;			//���S���W
	D3DXVECTOR3		size;			//�T�C�Y
	D3DXVECTOR3		move;			//�ړ���
	float			cola;		
	int				nTexNum;		//�e�N�X�`���̔ԍ�
	CUTTYPE			type;			//�^�C�v
	CHARATAYPE		chara;			//�L�����N�^�[�̃^�C�v
	CUTSTATE		CutState;		//�J�b�g�C���̏�Ԑݒ�
	NAMESTATE		NameState;		//�����o���̏�Ԑݒ�
	bool			bUse;			//�g�p���Ă��邩�ǂ���
	bool			bMove;			//�ړ��ʂ̃��Z�b�g
}Cut;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitCut(void);
void UninitCut(void);
void UpdateCut(void);
void DrawCut(void);

int SetCut(int nTexNum, D3DXVECTOR3 pos, CHARATAYPE chara , CUTTYPE type);

void DeleteAllCut(void);
Cut * GetCut(void);
void SetCutState(CUTSTATE state);
#endif
