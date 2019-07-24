//=============================================================================
//
// ���C���G�t�F�N�g���� [line.h]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#ifndef _LINEEFFECT_H_
#define _LINEEFFECT_H_

#include "main.h"

//=============================================================================
// �G�t�F�N�g�̎��
//=============================================================================
typedef enum
{
	LINETYPE_EFFECT_RAIN,
	LINETYPE_EFFECT_WINDY,
	LINETYPE_EFFECT_MAX,
}LINETYPEEFFECT;

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3				pos;			//���S���W
	D3DXVECTOR3				move;			//���S���W
	D3DXVECTOR3				rot;			//����
	D3DXMATRIX				mtxWorld;		//���[���h�}�g���b�N�X
	D3DXCOLOR				color;			//�F
	LINETYPEEFFECT			type;			//�G�t�F�N�g�̎��
	float					nLong;			//���̒���
	bool					bUse;			//�g�p���Ă��邩�ǂ���
}LineEffect;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitLineEffect(void);
void UninitLineEffect(void);
void UpdateLineEffect(void);
void DrawLineEffect(void);

void SetLineEffect(LINETYPEEFFECT type, bool bPlayEffect);
void CreateLineEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float nLong, LINETYPEEFFECT type);
#endif