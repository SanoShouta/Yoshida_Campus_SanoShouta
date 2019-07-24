////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ������G�t�F�N�g���� [effectUP.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _EFFECTUP_H_
#define _EFFECTUP_H_

#include "main.h"
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef enum
{
	EFFECTUPTYPE_LEAF = 0,
	EFFECTUPTYPE_PAPER,
	EFFECTUPTYPE_GUARD,
	EFFECTUPTYPE_MAX
}EFFECTUPTYPE;

typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ���
	D3DXCOLOR col;	// �F
	D3DXVECTOR3 rot;	// ����
	D3DXMATRIX mtxWorld;// ���[���h�}�g���b�N�X
	float fRadius;		// ��
	EFFECTUPTYPE nType;	// ���
	int nIdy;			// �ԍ�
	bool bUse;			// �g�p����Ă��邩�ǂ���
	float fAttackPower; // �U����
	float fDamageH;		// ���������
	float fDamageV;		// �c�������

}EffectUP;

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void InitEffectUP(void);
void UninitEffectUP(void);
void UpdateEffectUP(void);
void DrawEffectUP(void);
void SetEffectUP(int nIdy,D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, EFFECTUPTYPE nType, float fRadius);
void SetEffectUPDamage(int nIdy, float fAttackPower, float fDamageH, float fDamageV, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, EFFECTUPTYPE nType, float fRadius);

#endif
