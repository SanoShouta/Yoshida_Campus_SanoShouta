////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �e�̏��� [shadow.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "shadow.h"
#include "meshField.h"
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define MAX_SHADOW	(1000)

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureShadow = NULL;	// �e�N�X�`���ւ̃|�C���^
Shadow g_aShadow[MAX_SHADOW];
//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/shadow000.jpg",	// �t�@�C���̖��O
		&g_pTextureShadow);				// �e�N�X�`���ւ̃|�C���^

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
		g_aShadow[nCntShadow].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
		g_aShadow[nCntShadow].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_aShadow[nCntShadow].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);	// �F
		g_aShadow[nCntShadow].fWidth = 0;							// ��
		g_aShadow[nCntShadow].fDepth = 0;							// ���s��
		g_aShadow[nCntShadow].bUse = false;							// �g�p����Ă��邩�ǂ���
	}

	MakeVertexShadow(pDevice);

}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitShadow(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateShadow(void)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^
	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pVtx += 4)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{
			g_aShadow[nCntShadow].posOld = g_aShadow[nCntShadow].pos;
			g_aShadow[nCntShadow].pos += g_aShadow[nCntShadow].move;
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-(g_aShadow[nCntShadow].fWidth / 2), 0.0f, (g_aShadow[nCntShadow].fDepth / 2));
			pVtx[1].pos = D3DXVECTOR3((g_aShadow[nCntShadow].fWidth / 2), 0.0f, (g_aShadow[nCntShadow].fDepth / 2));
			pVtx[2].pos = D3DXVECTOR3(-(g_aShadow[nCntShadow].fWidth / 2), 0.0f, -(g_aShadow[nCntShadow].fDepth / 2));
			pVtx[3].pos = D3DXVECTOR3((g_aShadow[nCntShadow].fWidth / 2), 0.0f, -(g_aShadow[nCntShadow].fDepth / 2));
			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aShadow[nCntShadow].col;
			pVtx[1].col = g_aShadow[nCntShadow].col;
			pVtx[2].col = g_aShadow[nCntShadow].col;
			pVtx[3].col = g_aShadow[nCntShadow].col;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X


	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// Z�o�b�t�@�ւ̏�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);
		}
	}
	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// Z�o�b�t�@�ւ̏������ݏI��
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

//==============================================================================================================================
// ���_���̍쐬
//==============================================================================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-(g_aShadow[nCntShadow].fWidth / 2), 0.0f, (g_aShadow[nCntShadow].fDepth / 2));
		pVtx[1].pos = D3DXVECTOR3((g_aShadow[nCntShadow].fWidth / 2), 0.0f, (g_aShadow[nCntShadow].fDepth / 2));
		pVtx[2].pos = D3DXVECTOR3(-(g_aShadow[nCntShadow].fWidth / 2), 0.0f, -(g_aShadow[nCntShadow].fDepth / 2));
		pVtx[3].pos = D3DXVECTOR3((g_aShadow[nCntShadow].fWidth / 2), 0.0f, -(g_aShadow[nCntShadow].fDepth / 2));
		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_aShadow[nCntShadow].col;
		pVtx[1].col = g_aShadow[nCntShadow].col;
		pVtx[2].col = g_aShadow[nCntShadow].col;
		pVtx[3].col = g_aShadow[nCntShadow].col;
		// �e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

}
//==============================================================================================================================
// �e�̐ݒ�
//==============================================================================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fDepth)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^
	int nCntShadow;
	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++,pVtx+= 4)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos +D3DXVECTOR3(0.0f,0.1f,0.0f);
			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].fWidth = fWidth;
 			g_aShadow[nCntShadow].fDepth = fDepth;
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-(g_aShadow[nCntShadow].fWidth / 2), 0.0f, (g_aShadow[nCntShadow].fDepth / 2));
			pVtx[1].pos = D3DXVECTOR3((g_aShadow[nCntShadow].fWidth / 2), 0.0f, (g_aShadow[nCntShadow].fDepth / 2));
			pVtx[2].pos = D3DXVECTOR3(-(g_aShadow[nCntShadow].fWidth / 2), 0.0f, -(g_aShadow[nCntShadow].fDepth / 2));
			pVtx[3].pos = D3DXVECTOR3((g_aShadow[nCntShadow].fWidth / 2), 0.0f, -(g_aShadow[nCntShadow].fDepth / 2));
			g_aShadow[nCntShadow].bUse = true;
			break;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;
}
//==============================================================================================================================
// �e�̈ʒu��ݒ�
//==============================================================================================================================
void SetPositionShadow(int nIdyShadow, D3DXVECTOR3 pos, D3DXVECTOR3 Initpos)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * nIdyShadow;
	if (g_aShadow[nIdyShadow].bUse == true)
	{
		g_aShadow[nIdyShadow].posOld = g_aShadow[nIdyShadow].pos;

		g_aShadow[nIdyShadow].pos.x = pos.x;
		g_aShadow[nIdyShadow].pos.z = pos.z;
		// �����ɂ���ĉe�̓����x�ύX
		g_aShadow[nIdyShadow].col.a -= (Initpos.y - pos.y)*0.005f;
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-(g_aShadow[nIdyShadow].fWidth / 2), 0.0f, (g_aShadow[nIdyShadow].fDepth / 2));
		pVtx[1].pos = D3DXVECTOR3((g_aShadow[nIdyShadow].fWidth / 2), 0.0f, (g_aShadow[nIdyShadow].fDepth / 2));
		pVtx[2].pos = D3DXVECTOR3(-(g_aShadow[nIdyShadow].fWidth / 2), 0.0f, -(g_aShadow[nIdyShadow].fDepth / 2));
		pVtx[3].pos = D3DXVECTOR3((g_aShadow[nIdyShadow].fWidth / 2), 0.0f, -(g_aShadow[nIdyShadow].fDepth / 2));
		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_aShadow[nIdyShadow].col;
		pVtx[1].col = g_aShadow[nIdyShadow].col;
		pVtx[2].col = g_aShadow[nIdyShadow].col;
		pVtx[3].col = g_aShadow[nIdyShadow].col;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

}
//==============================================================================================================================
// �e�̐F��ݒ�
//==============================================================================================================================
void SetColorShadow(int nIdyShadow, float fAlpha)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * nIdyShadow;
	if (g_aShadow[nIdyShadow].bUse == true)
	{
		g_aShadow[nIdyShadow].col.a = fAlpha;
		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_aShadow[nIdyShadow].col;
		pVtx[1].col = g_aShadow[nIdyShadow].col;
		pVtx[2].col = g_aShadow[nIdyShadow].col;
		pVtx[3].col = g_aShadow[nIdyShadow].col;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}
//==============================================================================================================================
// �e���폜
//==============================================================================================================================
void DeleteShadow(int nIdyShadow)
{
 	g_aShadow[nIdyShadow].bUse = false;
}
//==============================================================================================================================
// �e���擾
//==============================================================================================================================
Shadow *GetShadow(void)
{
	return &g_aShadow[0];
}