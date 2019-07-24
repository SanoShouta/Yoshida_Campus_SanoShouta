//=============================================================================
//
// �A�C�e������ [item.h]
// Author : �������� Sato_Asumi
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "meshField.h"
#include "model.h"

//=============================================================================
// �A�C�e���̎��
//=============================================================================
typedef enum
{
	ITEMTYPE_CHANDY = 0,	//�Ȃ���
	ITEMTYPE_OMIKUZI,		//���݂���
	ITEMTYPE_TAKOYAKI,		//�����Ă�
	ITEMTYPE_CUCUMBER,		//���イ��
	ITEMTYPE_FRIED_TOUHU,	//���g��
	ITEMTYPE_LEAF,			//�t����
	ITEMTYPE_SCREW,			//�˂�
	ITEMTYPE_MAX,
}ITEMTYPE;

//=============================================================================
// �A�C�e���̏o���ʒu�̎��
//=============================================================================
typedef enum
{
	ITEMPOS_00 = 0,
	ITEMPOS_01,
	ITEMPOS_02,
	ITEMPOS_03,
	ITEMPOS_04,
	ITEMPOS_05,
	ITEMPOS_06,
	ITEMPOS_MAX,
}ITEMPOS;

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3		pos;				//���S���W
	D3DXVECTOR3		move;				//�ړ���
	D3DXVECTOR3		posOld;				//�O��̈ʒu
	D3DXMATRIX		mtxWorld;			//���[���h�}�g���b�N�X
	int				nIdxshadow;			//�e�̔ԍ�
	MeshField *		pMeshFieldLand;		// �ǂ̏��ɏ���Ă��邩
	Model			*pModel;			// �����������f���̏��
	ITEMTYPE		type;				//�A�C�e���̃^�C�v
	float			fAttack;			//�U����
	float			fHeal;				//�񕜗�
	float			fSpeed;				//�X�s�[�h
	int				nLife;				// ���C�t
	bool			bUse;				//�g�p���Ă��邩�ǂ���
}Item;

typedef struct
{
	ITEMTYPE		type;				//�A�C�e���̃^�C�v
	float			fAttack;			//�U����
	float			fHeal;				//�񕜗�
	float			fSpeed;				//�X�s�[�h
	int				nCounter;			//�m���J�E���^�[
	int				nLowProbability;	//�Œ�m��
	int				Probability;		//�m��
}Data;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

void SetItem(ITEMTYPE type);
D3DXVECTOR3 SetPos(int nItemPos);
void SetTex(int nIndex, int nType);
bool CollsionItem(D3DXVECTOR3 pos, float fRadiusWidth, float fRadiusHeight,float *pLife, float *Attack, float *Speed);
void DeleteItem(int nCntItem);
Item * GetItem(void);
#endif