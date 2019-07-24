//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : ��������
//
//=============================================================================
#include "light.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIGHT			(10)		// ���C�g�̍ő吔
#define LIGHT_MOVE_SPEED	(0.05f)		// ���C�g�̈ړ����x

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Light g_Light[MAX_LIGHT];				// ���C�g�̏��

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();					// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir;											// ���C�g�̊p�x������ϐ�

// -----���-----------------------
	// ���C�g���N���A����
	ZeroMemory(&g_Light[0], sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	g_Light[0].Light.Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	g_Light[0].Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// ���C�g�̐F��ݒ�
	// ���C�g�̎��͐F��ݒ�
	g_Light[0].Light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// ���C�g�̎��͐F��ݒ�
	// ���C�g�̋��ʐF��ݒ�
	g_Light[0].Light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// ���C�g�̋��ʐF��ݒ�

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.72f, -0.8f, 0.54f);
	D3DXVec3Normalize(&vecDir, &vecDir);								// ���K������
	g_Light[0].Light.Direction = vecDir;								// ���K�����ꂽ������������

	// ���C�g��ݒ肷��
	pDevice->SetLight(0, &g_Light[0].Light);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);

	// �g�p���Ă��邩�ǂ�����ݒ肷��
	g_Light[0].bLight = TRUE;											// �I��
	g_Light[0].bUse = TRUE;												// �g�p���Ă����Ԃɂ���


// ----���------------------------
	// ���C�g���N���A����
	ZeroMemory(&g_Light[1], sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	g_Light[1].Light.Type = D3DLIGHT_DIRECTIONAL;
	// ���C�g�̐F��ݒ�
	g_Light[1].Light.Diffuse  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ���C�g�̊g�U����ݒ�
	g_Light[1].Light.Ambient  = D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.6f);		// ���C�g�̎��͌���ݒ�
	g_Light[1].Light.Specular = D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.6f);		// ���C�g�̔��ˌ���ݒ�

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.88f, 0.88f, -0.94f);
	D3DXVec3Normalize(&vecDir, &vecDir);								// ���K������
	g_Light[1].Light.Direction = vecDir;								// ���K�����ꂽ������������

	// ���C�g��ݒ肷��
	pDevice->SetLight(1, &g_Light[1].Light);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(1, TRUE);

	// �g�p���Ă��邩�ǂ�����ݒ肷��
	g_Light[1].bLight = TRUE;											// �I��
	g_Light[1].bUse = TRUE;											// �g�p���Ă����Ԃɂ���


// ----�O��------------------------
	// ���C�g���N���A����
	ZeroMemory(&g_Light[2], sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	g_Light[2].Light.Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	g_Light[2].Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// ���C�g�̐F��ݒ�

	// ���C�g�͈̔͂�ݒ�
//	g_Light[2].Range = 70.75f;

	// ���C�g�̈ʒu��ݒ�
	g_Light[2].Light.Position = D3DXVECTOR3(0.0f, 50.0f, 0.0f);

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.89f, -0.1f, 0.94f);
	D3DXVec3Normalize(&vecDir, &vecDir);								// ���K������
	g_Light[2].Light.Direction = vecDir;								// ���K�����ꂽ������������

	// ���C�g��ݒ肷��
	pDevice->SetLight(2, &g_Light[2].Light);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(2, TRUE);

	// �g�p���Ă��邩�ǂ�����ݒ肷��
	g_Light[2].bLight = TRUE;											// �I��
	g_Light[2].bUse = TRUE;												// �g�p���Ă����Ԃɂ���
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{
}

//=============================================================================
// �|�C���g���C�g�̐ݒ�
//=============================================================================
int SetPointLight(D3DXVECTOR3 pos, D3DXCOLOR Diffuse,float Attenuation,float Range)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	int nCntLight = 0;							// ���C�g�̃J�E���g�ϐ�

	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{// ���C�g�̍ő吔�����[�v
		if (g_Light[nCntLight].bUse == false)
		{// ���C�g���g���Ă��Ȃ���ԂȂ�
			// ���C�g���N���A����
			ZeroMemory(&g_Light[nCntLight], sizeof(D3DLIGHT9));

			// ���C�g�̎�ނ�ݒ�
			g_Light[nCntLight].Light.Type = D3DLIGHT_POINT;

			// ���C�g�̈ʒu�̐ݒ�
			g_Light[nCntLight].Light.Position = pos;									// ���C�g�̈ʒu��ݒ�

			// ���C�g�̐F��ݒ�
			g_Light[nCntLight].Light.Diffuse  = Diffuse;								// ���C�g�̊g�U����ݒ�
			g_Light[nCntLight].Light.Ambient  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// ���C�g�̎��͐F��ݒ�
			g_Light[nCntLight].Light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// ���C�g�̋��ʐF��ݒ�

			// �����̐ݒ�
			g_Light[nCntLight].Light.Attenuation0 = Attenuation;						// ���`�����W��(��{�I�ɂ����ŕς��)
			g_Light[nCntLight].Light.Attenuation1 = 0.0f;								// 2�������W��(��{�I��0.0f�ő��v)
			g_Light[nCntLight].Light.Attenuation2 = 0.0f;								// �w�������W��(��{�I��0.0f�ő��v)

			// �����͈̔͂̐ݒ�
			g_Light[nCntLight].Light.Range = Range;										// �͈�

			// ���C�g��ݒ肷��
			pDevice->SetLight(nCntLight, &g_Light[nCntLight].Light);

			// ���C�g��L���ɂ���
			pDevice->LightEnable(nCntLight, TRUE);

			g_Light[nCntLight].bLight = true;											// ���C�g���I���ɂ���
			g_Light[nCntLight].bUse	  = true;											// ���C�g���g�p��Ԃɂ���

			break;
		}
	}
	return nCntLight;																	// ������ԍ��𑗂�
}

//=============================================================================
// �X�|�b�g���C�g�̐ݒ�
//=============================================================================
int SetSpotLight(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR Diffuse)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir;							// ���C�g�̊p�x������ϐ�
	int nCntLight = 0;							// ���C�g�̃J�E���g�ϐ�

	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{// ���C�g�̍ő吔�����[�v
		if (g_Light[nCntLight].bUse == false)
		{// ���C�g���g���Ă��Ȃ���ԂȂ�
		 // ���C�g���N���A����
			ZeroMemory(&g_Light[nCntLight], sizeof(D3DLIGHT9));

			// ���C�g�̎�ނ�ݒ�
			g_Light[nCntLight].Light.Type = D3DLIGHT_SPOT;

			// ���C�g�̈ʒu�̐ݒ�
			g_Light[nCntLight].Light.Position = pos;									// ���C�g�̈ʒu��ݒ�

			// ���C�g�̐F��ݒ�
			g_Light[nCntLight].Light.Diffuse  = Diffuse;								// ���C�g�̊g�U����ݒ�
			g_Light[nCntLight].Light.Ambient  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// ���C�g�̎��͐F��ݒ�
			g_Light[nCntLight].Light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// ���C�g�̋��ʐF��ݒ�

			// �����̐ݒ�
			g_Light[nCntLight].Light.Attenuation0 = 0.1f;								// ���`�����W��(��{�I��0.1f���炢�ő��v)
			g_Light[nCntLight].Light.Attenuation1 = 0.0f;								// 2�������W��(��{�I��0.0f�ő��v)
			g_Light[nCntLight].Light.Attenuation2 = 0.0f;								// �w�������W��(��{�I��0.0f�ő��v)

			// �����͈̔͂̐ݒ�
			g_Light[nCntLight].Light.Range = 220.0f;										// �͈�

			// �X�|�b�g���C�g�̃t�H�[���I�t�̐ݒ�
			g_Light[nCntLight].Light.Falloff = 1.0f;

			// �X�|�b�g���C�g�̓����R�[���̊p�x�̐ݒ�
			g_Light[nCntLight].Light.Theta = 0.5f;

			// �X�|�b�g���C�g�̊O���R�[���̊p�x�̐ݒ�
			g_Light[nCntLight].Light.Phi = D3DX_PI / 2;


			// ���C�g�̕����̐ݒ�
			vecDir = rot;														// ���C�g�̊p�x����
			D3DXVec3Normalize(&vecDir, &vecDir);								// ���C�g�̊p�x�𐳋K������
			g_Light[nCntLight].Light.Direction = vecDir;								// ���K�����ꂽ�����Ŋp�x��ݒ肷��

			// ���C�g��ݒ肷��
			pDevice->SetLight(nCntLight, &g_Light[nCntLight].Light);

			// ���C�g��L���ɂ���
			pDevice->LightEnable(nCntLight, TRUE);

			g_Light[nCntLight].bLight = true;											// ���C�g���I���ɂ���
			g_Light[nCntLight].bUse = true;												// ���C�g���g�p��Ԃɂ���

			break;
		}
	}
	return nCntLight;																	// ������ԍ��𑗂�
}

//=============================================================================
// ���C�g�̈ʒu�X�V
//=============================================================================
void SetPositionLight(int nIdxLight, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{

	if (nIdxLight != -1)
	{// -1�Ȃ珈�����Ȃ�
		LPDIRECT3DDEVICE9 pDevice = GetDevice();					// �f�o�C�X�̎擾
		D3DXVECTOR3 vecDir;											// ���C�g�̊p�x������ϐ�

		// ���C�g�̈ʒu��ݒ�
		g_Light[nIdxLight].Light.Position = pos;					// ���C�g�̈ʒu��ݒ�

		// ���C�g�̕����̐ݒ�
		vecDir = rot;												// ���C�g�̊p�x������
		D3DXVec3Normalize(&vecDir, &vecDir);						// ���K������
		g_Light[nIdxLight].Light.Direction = vecDir;				// ���K�����ꂽ������������

		// ���C�g��ݒ肷��
		pDevice->SetLight(nIdxLight, &g_Light[nIdxLight].Light);

	}
}

//=============================================================================
// ���C�g�̃I���I�t�؂�ւ�
//=============================================================================
void SwitchingLight(int nIdxLight)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// ���C�g�̃I���I�t��؂�ւ�
	g_Light[nIdxLight].bLight = g_Light[nIdxLight].bLight ? false : true;

	// ���C�g��L���ɂ���
	pDevice->LightEnable(nIdxLight, g_Light[nIdxLight].bLight);

}