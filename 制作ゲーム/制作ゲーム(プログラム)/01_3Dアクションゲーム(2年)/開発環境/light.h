//=============================================================================
//
// ���C�g���� [light.h]
// Author : ��������
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef struct
{// ���C�g�̍\����
	D3DLIGHT9 Light;				// ���C�g�̏��
	bool bLight;					// ���C�g�̃I���I�t
	bool bUse;						// �g�p����Ă��邩�ǂ���
}Light;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitLight(void);
void UninitLight(void);
void UpdateLight(void);
int SetPointLight(D3DXVECTOR3 pos, D3DXCOLOR Diffuse, float Attenuation, float Range);		// �|�C���g���C�g�̐ݒu
int SetSpotLight(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR Diffuse);						// �X�|�b�g���C�g�̐ݒu
void SetPositionLight(int nIdxLight, D3DXVECTOR3 pos, D3DXVECTOR3 rot);						// ���C�g�̈ʒu,��],�X�V
void SwitchingLight(int nIdxLight);															// ���C�g�̃I���I�t��؂�ւ�


#endif
