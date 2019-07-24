////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �r���{�[�h�̏��� [billboard.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "billboard.h"
#include "shadow.h"

//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define MAX_BILLBOARD	(5)
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************

typedef struct
{
	char *pFileName;
}BillboardTexture;
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);

//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
Billboard g_aBillboard[MAX_BILLBOARD];
BillboardData g_aBillboardData[BILLBOARDTYPE_MAX];
BillboardTexture g_pFileName[BILLBOARDTYPE_MAX] =
{
	{ "data/TEXTURE/SystemIcon.png" },
	{ "data/TEXTURE/SystemIcon.png" },
	{ "data/TEXTURE/SystemIcon.png" },
	{"data/TEXTURE/Shop_Angry.png"},
};
//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_aBillboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
		g_aBillboard[nCntBillboard].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �O��̈ʒu
		g_aBillboard[nCntBillboard].Initpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// �����ʒu
		g_aBillboard[nCntBillboard].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_aBillboard[nCntBillboard].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_aBillboard[nCntBillboard].fWidth = 0;								// ��
		g_aBillboard[nCntBillboard].fHeight = 0;							// ����
		g_aBillboard[nCntBillboard].fDepth = 0;								// ���s��
		g_aBillboard[nCntBillboard].nType = BILLBOARDTYPE_EVENT;				// ���
		g_aBillboard[nCntBillboard].nIdyShadow = 0;							// �e��ID
		g_aBillboard[nCntBillboard].nCounter = 0;							// �J�E���^�[
		g_aBillboard[nCntBillboard].bUse = false;							// �g�p����Ă��邩�ǂ���
	}

	MakeVertexBillboard(pDevice);

}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitBillboard(void)
{
	// �e�N�X�`���̔j��
	for (int nCntBillboard = 0; nCntBillboard < BILLBOARDTYPE_MAX; nCntBillboard++)
	{
		if (g_aBillboardData[nCntBillboard].pTexture != NULL)
		{
			g_aBillboardData[nCntBillboard].pTexture->Release();
			g_aBillboardData[nCntBillboard].pTexture = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateBillboard(void)
{

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == true)
		{
			// �O��̈ʒu�̐ݒ�
			g_aBillboard[nCntBillboard].posOld = g_aBillboard[nCntBillboard].pos;
			// �ړ��ʉ��Z
			g_aBillboard[nCntBillboard].pos += g_aBillboard[nCntBillboard].move;
			g_aBillboard[nCntBillboard].nCounter++;
			switch (g_aBillboard[nCntBillboard].nType)
			{
			case BILLBOARDTYPE_SHOP:
				if (g_aBillboard[nCntBillboard].nCounter >= 180)
				{
					g_aBillboard[nCntBillboard].bUse = false;
				}
				break;
			}
//--------------------------/ �e���ړ����� /---------------------------------------------------------------------------------------//
		//	SetPositionShadow(g_aBillboard[nCntBillboard].nIdyShadow, g_aBillboard[nCntBillboard].pos, g_aBillboard[nCntBillboard].Initpos);
		}
	}

}

//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;							// �r���{�[�h�p�}�g���b�N�X

	// Z�o�b�t�@�ւ̏�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// ���C�g�e���󂯂Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBillboard[nCntBillboard].mtxWorld);

			// �r���{�[�h�̐ݒ�
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			// �t�s��̐ݒ�
			g_aBillboard[nCntBillboard].mtxWorld._11 = mtxView._11;
			g_aBillboard[nCntBillboard].mtxWorld._12 = mtxView._21;
			g_aBillboard[nCntBillboard].mtxWorld._13 = mtxView._31;
			g_aBillboard[nCntBillboard].mtxWorld._21 = mtxView._12;
			g_aBillboard[nCntBillboard].mtxWorld._22 = mtxView._22;
			g_aBillboard[nCntBillboard].mtxWorld._23 = mtxView._32;
			g_aBillboard[nCntBillboard].mtxWorld._31 = mtxView._13;
			g_aBillboard[nCntBillboard].mtxWorld._32 = mtxView._23;
			g_aBillboard[nCntBillboard].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBillboard].pos.x, g_aBillboard[nCntBillboard].pos.y, g_aBillboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBillboard].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aBillboardData[g_aBillboard[nCntBillboard].nType].pTexture);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillboard * 4, 2);
		}
	}
	// Z�o�b�t�@�ւ̏�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	// ���C�g�e���󂯂Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==============================================================================================================================
// ���_���̍쐬
//==============================================================================================================================
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);
	// �e�N�X�`���̔j��
	for (int nCntBillboard = 0; nCntBillboard < BILLBOARDTYPE_MAX; nCntBillboard++)
	{

		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			g_pFileName[nCntBillboard].pFileName,		// �t�@�C���̖��O
			&g_aBillboardData[nCntBillboard].pTexture);		// �e�N�X�`���ւ̃|�C���^
	}
	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-(g_aBillboard[nCntBillboard].fWidth / 2), (g_aBillboard[nCntBillboard].fHeight), 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_aBillboard[nCntBillboard].fWidth / 2), (g_aBillboard[nCntBillboard].fHeight),0.0f);
		pVtx[2].pos = D3DXVECTOR3(-(g_aBillboard[nCntBillboard].fWidth / 2), 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_aBillboard[nCntBillboard].fWidth / 2), 0.0f, 0.0f);
		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// �e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBillboard->Unlock();

}
//==============================================================================================================================
// �r���{�[�h�̐ݒ�
//==============================================================================================================================
void SetBillboard(D3DXVECTOR3 pos,BILLBOARDTYPE nType, float fWidth, float fHeight)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++, pVtx += 4)
	{
		if (g_aBillboard[nCntBillboard].bUse == false)
		{
			g_aBillboard[nCntBillboard].pos = pos;
			g_aBillboard[nCntBillboard].Initpos = pos;
			g_aBillboard[nCntBillboard].nType = nType;
			g_aBillboard[nCntBillboard].fWidth = fWidth;
			g_aBillboard[nCntBillboard].fHeight = fHeight;
			g_aBillboard[nCntBillboard].nCounter = 0;
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-(g_aBillboard[nCntBillboard].fWidth / 2), (g_aBillboard[nCntBillboard].fHeight), 0.0f);
			pVtx[1].pos = D3DXVECTOR3((g_aBillboard[nCntBillboard].fWidth / 2), (g_aBillboard[nCntBillboard].fHeight), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-(g_aBillboard[nCntBillboard].fWidth / 2), 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((g_aBillboard[nCntBillboard].fWidth / 2), 0.0f, 0.0f);

			// �e�̐ݒ�
			//g_aBillboard[nCntBillboard].nIdyShadow = SetShadow(D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x, 0.1f, g_aBillboard[nCntBillboard].pos.z), g_aBillboard[nCntBillboard].rot,
			//	g_aBillboard[nCntBillboard].fWidth /2, g_aBillboard[nCntBillboard].fWidth /2);

			g_aBillboard[nCntBillboard].bUse = true;
			break;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBillboard->Unlock();
}
//==============================================================================================================================
// �r���{�[�h�̍폜
//==============================================================================================================================
void DeleteBillboard(BILLBOARDTYPE nType)
{
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].nType == nType)
		{
			g_aBillboard[nCntBillboard].bUse = false;
		}
	}
}
//==============================================================================================================================
// �r���{�[�h�̎擾
//==============================================================================================================================
Billboard *GetBillboard(void)
{
	return &g_aBillboard[0];
}
BillboardData *GetBillboardData(void)
{
	return &g_aBillboardData[0];
}
