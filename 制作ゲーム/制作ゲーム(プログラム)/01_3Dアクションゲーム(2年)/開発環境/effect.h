////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "model.h"


//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef enum
{
	EFFECTTYPE_SMOKE = 0,		// ��
	EFFECTTYPE_IMPACT,			// �Ռ���
	EFFECTTYPE_HITEXPLOSION,	// �q�b�g
	EFFECTTYPE_WATERFALL_0,		// ��
	EFFECTTYPE_WATERFALL_1,		// ��P
	EFFECTTYPE_STATE_UP,		// �X�e�[�^�X�A�b�v
	EFFECTTYPE_FIRE,			// ��
	EFFECTTYPE_WATER,			// ��
	EFFECTTYPE_POW_UP,			// �U��UP
	EFFECTTYPE_LIFE_UP,			// ���C�t��
	EFFECTTYPE_SPEED_UP,		// �X�s�[�hUP
	EFFECTTYPE_WALK,		// ����
	EFFECTTYPE_LASER,		// ���[�U�[
	EFFECTTYPE_BOMB,		// �{��
	EFFECTTYPE_DIRTY,		// �y
	EFFECTTYPE_SUNDER,		// ��
	EFFECTTYPE_CRASH,		// ����
	EFFECTTYPE_CARTOON_SLICE_0,		// �U�b
	EFFECTTYPE_CARTOON_FIRE,		// ��
	EFFECTTYPE_CARTOON_WIND,		// ��
	EFFECTTYPE_CARTOON_DON,		// �h��
	EFFECTTYPE_CARTOON_TA,		// ����
	EFFECTTYPE_MAX
}EFFECTTYPE;

typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 Destpos;// �ړI�̈ʒu
	D3DXVECTOR3 posOld;	// �O��̈ʒu
	D3DXVECTOR3 Initpos;// �����ʒu
	D3DXVECTOR3 move;	// ����
	D3DXVECTOR3 rot;	// ����
	float fAngle;		// �p�x
	float fLength;		// ����
	D3DXCOLOR col;		// �F
	D3DXMATRIX mtxWorld;// ���[���h�}�g���b�N�X
	float fWidth;		// ��
	float fHeight;		// ����
	float fDepth;		// ���s��
	float fRadius;		// ����
	int nLife;			// ����
	float fSinCosMove;	// ���
	EFFECTTYPE nType;// ���
	int nIdyShadow;		// �e��ID
	float fChangeRadius;// �g��k��
	int nCounterAnim;	// �A�j���[�V�����J�E���^�[
	int nPatternAnim;	// �A�j���[�V�����p�^�[��
	int nRandAnim;	// �����_���J�E���^�[
	bool bUse;			// �g�p����Ă��邩�ǂ���
	int nIdy;			// �ԍ�
	float fAttackPower; // �U����
	float fDamageH;		// ���������
	float fDamageV;		// �c�������
	Model *pModel;
}Effect;

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fRadius, int nLife, EFFECTTYPE nType);
void SetEffectDamage(int nIdy, float fAttackPower, float fDamageH, float fDamageV,D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fRadius, int nLife, EFFECTTYPE nType);
float SetRandomEffect(void);
Effect *GetEffect(void);

void HitEffect(D3DXVECTOR3 pos);
#endif
