//=============================================================================
//
// ���C���G�t�F�N�g���� [lineEffect.cpp]
// Author : �������� Sato_Asumi
//
//=============================================================================
#include "lineEffect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define LINE_EFFECT	(400)

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexLineEffect(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLineEffect = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LineEffect				g_LineEffect[LINE_EFFECT];
LINETYPEEFFECT			g_TypeEffect;					//�G�t�F�N�g�̎��
int						g_nCntTimeLine;					//���ԃJ�E���^�[
bool					g_bPlay;						//�g�p���Ă��邩�ǂ���

//=============================================================================
// ����������
//=============================================================================
void InitLineEffect(void)
{
	//�ϐ��錾
	int nCntLineEffect;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	//�ϐ��̏�����
	g_nCntTimeLine = 0;
	g_bPlay = false;
	for (nCntLineEffect = 0; nCntLineEffect < LINE_EFFECT; nCntLineEffect++)
	{
		g_LineEffect[nCntLineEffect].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		g_LineEffect[nCntLineEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_LineEffect[nCntLineEffect].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_LineEffect[nCntLineEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_LineEffect[nCntLineEffect].type = LINETYPE_EFFECT_MAX;
		g_LineEffect[nCntLineEffect].bUse = false;
	}

	// ���_���̍쐬
	MakeVertexLineEffect(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitLineEffect(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLineEffect != NULL)
	{
		g_pVtxBuffLineEffect->Release();
		g_pVtxBuffLineEffect = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLineEffect(void)
{
	//�ϐ��錾
	int nCntLineEffect;
	D3DXVECTOR3 Pos = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 Pos2 = D3DXVECTOR3(0, 0, 0);

	g_nCntTimeLine++;		//���Ԃ̉��Z

	if (g_bPlay == true)
	{
		if (g_TypeEffect == LINETYPE_EFFECT_RAIN)
		{
			for (int nCntRain = 0; nCntRain < 3; nCntRain++)
			{
				Pos.x = (float)-500 + rand() % 1200;
				Pos.z = (float)-100 + rand() % 600;

				CreateLineEffect(D3DXVECTOR3(Pos.x, 300, Pos.z), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(0.7f, 0.9f, 0.9f, 1.0f), 100.0f, LINETYPE_EFFECT_RAIN);
			}
		}
		else
		{

			if (g_nCntTimeLine % 10 == 0)
			{
				for (int nCntRain = 0; nCntRain < 2; nCntRain++)
				{
					Pos.y = (float)600 + rand() % 300;
					Pos.z = (float)-300 + rand() % 600;
					Pos2.y = (float)600 + rand() % 300;

					CreateLineEffect(D3DXVECTOR3(-600, Pos.y, Pos.z), D3DXVECTOR3(0, 0, D3DX_PI * 0.5f), D3DXCOLOR(0.5f, 0.9f, 0.6f, 0.5f), 100.0f, LINETYPE_EFFECT_WINDY);
					CreateLineEffect(D3DXVECTOR3(-600, Pos2.y, Pos2.z), D3DXVECTOR3(0, 0, D3DX_PI * 0.5f), D3DXCOLOR(0.4f, 0.5f, 0.4f, 0.5f), 100.0f, LINETYPE_EFFECT_WINDY);
				}
			}
		}
	}

	for (nCntLineEffect = 0; nCntLineEffect < LINE_EFFECT; nCntLineEffect++)
	{
		if (g_LineEffect[nCntLineEffect].bUse == true)
		{
			switch (g_LineEffect[nCntLineEffect].type)
			{
			case LINETYPE_EFFECT_RAIN:
				//�ʒu�X�V
				g_LineEffect[nCntLineEffect].move.y += -0.1f;
				g_LineEffect[nCntLineEffect].pos.y += g_LineEffect[nCntLineEffect].move.y;

				if (g_LineEffect[nCntLineEffect].pos.y < -350.0)
				{
					g_LineEffect[nCntLineEffect].bUse = false;
				}
				break;

			case LINETYPE_EFFECT_WINDY:
				//�ʒu�X�V
				g_LineEffect[nCntLineEffect].pos.x += 9.0f;

				if (g_LineEffect[nCntLineEffect].pos.x > 1600.0)
				{
					g_LineEffect[nCntLineEffect].bUse = false;
				}
				break;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLineEffect(void)
{
	//�ϐ��錾
	int nCntLineEffect;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX		  mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (nCntLineEffect = 0; nCntLineEffect < LINE_EFFECT; nCntLineEffect++)
	{
		if (g_LineEffect[nCntLineEffect].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_LineEffect[nCntLineEffect].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_LineEffect[nCntLineEffect].rot.y, g_LineEffect[nCntLineEffect].rot.x, g_LineEffect[nCntLineEffect].rot.z);
			D3DXMatrixMultiply(&g_LineEffect[nCntLineEffect].mtxWorld, &g_LineEffect[nCntLineEffect].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_LineEffect[nCntLineEffect].pos.x, g_LineEffect[nCntLineEffect].pos.y, g_LineEffect[nCntLineEffect].pos.z);
			D3DXMatrixMultiply(&g_LineEffect[nCntLineEffect].mtxWorld, &g_LineEffect[nCntLineEffect].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_LineEffect[nCntLineEffect].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffLineEffect, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_LINELIST, nCntLineEffect * 2, 1);
		}
	}

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexLineEffect(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	int nCntLineEffect;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * LINE_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLineEffect,
		NULL);

	VERTEX_3D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLineEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLineEffect = 0; nCntLineEffect < LINE_EFFECT; nCntLineEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

		pVtx += 2;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLineEffect->Unlock();
}

//=============================================================================
// ���C���̃^�C�v�ݒ�
//=============================================================================
void SetLineEffect(LINETYPEEFFECT type, bool bPlayEffect)
{
	g_TypeEffect = type;
	g_bPlay = bPlayEffect;
}

//=============================================================================
// ���C���̐ݒ�
//=============================================================================
void CreateLineEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float nLong, LINETYPEEFFECT type)
{
	//�ϐ��錾
	int nCntLineEffect;

	VERTEX_3D * pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLineEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLineEffect = 0; nCntLineEffect < LINE_EFFECT; nCntLineEffect++)
	{
		if (g_LineEffect[nCntLineEffect].bUse == false)
		{
			g_LineEffect[nCntLineEffect].pos = pos;
			g_LineEffect[nCntLineEffect].type = type;
			g_LineEffect[nCntLineEffect].rot = rot;
			g_LineEffect[nCntLineEffect].color = col;
			g_LineEffect[nCntLineEffect].nLong = nLong;
			g_LineEffect[nCntLineEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_LineEffect[nCntLineEffect].bUse = true;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y, pos.z);
			pVtx[1].pos = D3DXVECTOR3(pos.x, pos.y + nLong, pos.z);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			break;
		}

		pVtx += 2;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLineEffect->Unlock();
}