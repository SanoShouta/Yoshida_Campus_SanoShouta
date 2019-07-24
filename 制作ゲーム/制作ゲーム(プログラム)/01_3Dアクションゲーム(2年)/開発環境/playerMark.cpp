//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �v���C���[�ԍ��̕\���̏��� [playerMark.cpp]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "playerMark.h"
#include "player.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �v���g�^�C�v�錾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MakeVertexPlayerMark(LPDIRECT3DDEVICE9 pDevice);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �O���[�o���ϐ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
LPDIRECT3DTEXTURE9		g_pTexturePlayerMark[PLAYERMARK_MAX] = {};			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerMark = NULL;							//���_�o�b�t�@�ւ̃|�C���^
PlayerMark			g_aPlayerMark[PLAYERMARK_MAX];

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ����������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitPlayerMark(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntPlayerMark = 0; nCntPlayerMark < PLAYERMARK_MAX; nCntPlayerMark++)
	{
		g_aPlayerMark[nCntPlayerMark].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayerMark[nCntPlayerMark].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayerMark[nCntPlayerMark].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPlayerMark[nCntPlayerMark].nCntSwitch = 0;
		g_aPlayerMark[nCntPlayerMark].fWidth = PLAYERMARK_WIDTH;
		g_aPlayerMark[nCntPlayerMark].fHeight = PLAYERMARK_HEIGHT;
		g_aPlayerMark[nCntPlayerMark].bUse = true;
	}
	// ���_���̍쐬
	MakeVertexPlayerMark(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerMark(void)
{
	// �e�N�X�`���̊J��
	for (int nCntPlayerMark = 0; nCntPlayerMark < PLAYERMARK_MAX; nCntPlayerMark++)
	{
		if (g_pTexturePlayerMark[nCntPlayerMark] != NULL)
		{
			g_pTexturePlayerMark[nCntPlayerMark]->Release();
			g_pTexturePlayerMark[nCntPlayerMark] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayerMark != NULL)
	{
		g_pVtxBuffPlayerMark->Release();
		g_pVtxBuffPlayerMark = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerMark(void)
{
	Player *pPlayer = GetPlayer();
	for (int nCntPlayerMark = 0; nCntPlayerMark < PLAYERMARK_MAX; nCntPlayerMark++)
	{
		if (pPlayer[nCntPlayerMark].typeInfo != PLAYERTYPE_MAX)
		{
			if (g_aPlayerMark[nCntPlayerMark].bUse == true)
			{// �\�����Ă��鎞
				Player *pPlayer = GetPlayer();
				if (pPlayer[nCntPlayerMark].bUse == true)
				{
					if (g_aPlayerMark[nCntPlayerMark].bUse == true)
					{
						g_aPlayerMark[nCntPlayerMark].pos = D3DXVECTOR3(pPlayer[nCntPlayerMark].aModel[3].mtxWorld._41, pPlayer[nCntPlayerMark].aModel[3].mtxWorld._42 + 50.0f, pPlayer[nCntPlayerMark].aModel[3].mtxWorld._43);
						g_aPlayerMark[nCntPlayerMark].nCntSwitch++;
						if (g_aPlayerMark[nCntPlayerMark].nCntSwitch >= PLAYERMARK_COUNTSPEED)
						{// ��莞�Ԍo�����Ƃ�
							g_aPlayerMark[nCntPlayerMark].bUse = false;
							g_aPlayerMark[nCntPlayerMark].nCntSwitch = 0;
						}
					}
					else
					{
						g_aPlayerMark[nCntPlayerMark].bUse = false;
					}
				}

			}
			else if (g_aPlayerMark[nCntPlayerMark].bUse == false)
			{// �\�����ĂȂ���
				g_aPlayerMark[nCntPlayerMark].nCntSwitch++;
				if (g_aPlayerMark[nCntPlayerMark].nCntSwitch >= PLAYERMARK_COUNTSPEED)
				{// ��莞�Ԍo�����Ƃ�
					g_aPlayerMark[nCntPlayerMark].bUse = true;
					g_aPlayerMark[nCntPlayerMark].nCntSwitch = 0;
				}
			}
		}
		else
		{
			g_aPlayerMark[nCntPlayerMark].bUse = false;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerMark(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxView, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//Z�o�b�t�@��L��
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 10);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	for (int nCntPlayerMark = 0; nCntPlayerMark < PLAYERMARK_MAX; nCntPlayerMark++)
	{
		if (g_aPlayerMark[nCntPlayerMark].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�t�s���ݒ�
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._11 = mtxView._11;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._12 = mtxView._21;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._13 = mtxView._31;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._21 = mtxView._12;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._22 = mtxView._22;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._23 = mtxView._32;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._31 = mtxView._13;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._32 = mtxView._23;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_aPlayerMark[nCntPlayerMark].pos.x, g_aPlayerMark[nCntPlayerMark].pos.y, g_aPlayerMark[nCntPlayerMark].pos.z);

			D3DXMatrixMultiply(&g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark, &g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0,
				g_pVtxBuffPlayerMark,
				0,
				sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePlayerMark[nCntPlayerMark]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntPlayerMark * 4,
				2);
		}
	}

	//Z�o�b�t�@�𖳌�
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPlayerMark(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		PLAYERMARK_TEXTURE_0,
		&g_pTexturePlayerMark[0]);
	D3DXCreateTextureFromFile(pDevice,
		PLAYERMARK_TEXTURE_1,
		&g_pTexturePlayerMark[1]);
	D3DXCreateTextureFromFile(pDevice,
		PLAYERMARK_TEXTURE_2,
		&g_pTexturePlayerMark[2]);
	D3DXCreateTextureFromFile(pDevice,
		PLAYERMARK_TEXTURE_3,
		&g_pTexturePlayerMark[3]);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * PLAYERMARK_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerMark,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayerMark->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPlayerMark = 0; nCntPlayerMark < PLAYERMARK_MAX; nCntPlayerMark++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aPlayerMark[nCntPlayerMark].fWidth, g_aPlayerMark[nCntPlayerMark].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPlayerMark[nCntPlayerMark].fWidth, g_aPlayerMark[nCntPlayerMark].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aPlayerMark[nCntPlayerMark].fWidth, -g_aPlayerMark[nCntPlayerMark].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPlayerMark[nCntPlayerMark].fWidth, -g_aPlayerMark[nCntPlayerMark].fHeight, 0.0f);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[1].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[2].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[3].nor = D3DXVECTOR3(0.0, 0.0, -1.0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayerMark->Unlock();

}
