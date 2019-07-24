////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �n�ʃG�t�F�N�g���� [.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "effectUP.h"
#include "game.h"
#include "effect.h"
#include "player.h"
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define MAX_EFFECTUP	(2000)
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			// ���S���W
	D3DXVECTOR3 rot;			// ����
	EFFECTUPTYPE nType;			// ���
	float fWidth;				// ��
	float fDepth;				// ���s��
} EffectUPInfo;
typedef struct
{
	char *pFileName;
}EffectUPTexture;
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void MakeVertexEffectUP(LPDIRECT3DDEVICE9 pDevice);

//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffectUP = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_apTextureEffectUP[EFFECTUPTYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
EffectUP g_aEffectUP[MAX_EFFECTUP];
EffectUPTexture g_aEffectUPTexInfo[EFFECTUPTYPE_MAX] =
{
	{ "data/TEXTURE/LeafEffect.jpg" },
	{ "data/TEXTURE/.jpg" },
	{ "data/TEXTURE/GuardEffect.png" },
};
float fTexmove;
//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitEffectUP(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntEffectUPTex = 0; nCntEffectUPTex < EFFECTUPTYPE_MAX; nCntEffectUPTex++)
	{// �e�N�X�`���̐ݒ�
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			g_aEffectUPTexInfo[nCntEffectUPTex].pFileName,	// �t�@�C���̖��O
			&g_apTextureEffectUP[nCntEffectUPTex]);			// �e�N�X�`���ւ̃|�C���^
	}

	for (int nCntEffectUP = 0; nCntEffectUP < MAX_EFFECTUP; nCntEffectUP++)
	{
		g_aEffectUP[nCntEffectUP].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
		g_aEffectUP[nCntEffectUP].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffectUP[nCntEffectUP].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffectUP[nCntEffectUP].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_aEffectUP[nCntEffectUP].fRadius = 0;								// ���a
		g_aEffectUP[nCntEffectUP].bUse = false;							// �g�p����Ă��邩�ǂ���
		g_aEffectUP[nCntEffectUP].nIdy = 0;								// �ԍ�
		g_aEffectUP[nCntEffectUP].fAttackPower = 0;						// �_���[�W
		g_aEffectUP[nCntEffectUP].fDamageH = 0;							// ���������_���[�W
		g_aEffectUP[nCntEffectUP].fDamageV = 0;							// ���������_���[�W

	}
	fTexmove = 0;
	MakeVertexEffectUP(pDevice);
}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitEffectUP(void)
{
	// �e�N�X�`���̔j��
	for (int nCntEffectUP = 0; nCntEffectUP < EFFECTUPTYPE_MAX; nCntEffectUP++)
	{
		if (g_apTextureEffectUP[nCntEffectUP] != NULL)
		{
			g_apTextureEffectUP[nCntEffectUP]->Release();
			g_apTextureEffectUP[nCntEffectUP] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffectUP != NULL)
	{
		g_pVtxBuffEffectUP->Release();
		g_pVtxBuffEffectUP = NULL;
	}
}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateEffectUP(void)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

						// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffectUP->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffectUP = 0; nCntEffectUP < MAX_EFFECTUP; nCntEffectUP++, pVtx += 4)
	{
		if (g_aEffectUP[nCntEffectUP].bUse == true)
		{
			switch (g_aEffectUP[nCntEffectUP].nType)
			{
			case EFFECTUPTYPE_LEAF:
				//g_aEffectUP[nCntEffectUP].fRadius += 10;
				g_aEffectUP[nCntEffectUP].col.a += -0.02f;
				g_aEffectUP[nCntEffectUP].rot.y += 0.3f;
				if (g_aEffectUP[nCntEffectUP].col.a <= 0.0f)
				{
					g_aEffectUP[nCntEffectUP].bUse = false;
				}
				if ((rand() +1)%100==0&& g_aEffectUP[nCntEffectUP].col.a >= 0.3f)
				{
					SetEffect(g_aEffectUP[nCntEffectUP].pos + D3DXVECTOR3(sinf(SetRandomEffect()) * 10,
						cosf(SetRandomEffect()) * 10,
						 cosf(SetRandomEffect()) * 10)
						, D3DXVECTOR3(sinf(SetRandomEffect()) * 1, 0, cosf(SetRandomEffect()) * 1), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),float( rand()%30+10), 0, EFFECTTYPE_CARTOON_WIND);
				}
				break;
			case EFFECTUPTYPE_PAPER:
				g_aEffectUP[nCntEffectUP].rot.x += 0.01f;
				g_aEffectUP[nCntEffectUP].rot.y += 0.01f;
				g_aEffectUP[nCntEffectUP].rot.z += 0.01f;
				g_aEffectUP[nCntEffectUP].move.x += sinf(SetRandomEffect())*0.5f;
				g_aEffectUP[nCntEffectUP].move.z += sinf(SetRandomEffect())*0.5f;
				g_aEffectUP[nCntEffectUP].move.y -= sinf((rand()%314)/100.0f)*0.1f;
				if (g_aEffectUP[nCntEffectUP].pos.y <= 0.0f)
				{
					g_aEffectUP[nCntEffectUP].bUse = false;
				}
				break;
			case EFFECTUPTYPE_GUARD:
				g_aEffectUP[nCntEffectUP].move.x *=0.9f;
				g_aEffectUP[nCntEffectUP].move.z *=0.9f;
				g_aEffectUP[nCntEffectUP].move.y *=0.9f;
				if ((g_aEffectUP[nCntEffectUP].move.x <= 1.0f&&g_aEffectUP[nCntEffectUP].move.x >= -1.0f) &&
					(g_aEffectUP[nCntEffectUP].move.z <= 1.0f&&g_aEffectUP[nCntEffectUP].move.z >= -1.0f)&&
					(g_aEffectUP[nCntEffectUP].move.y <= 1.0f&&g_aEffectUP[nCntEffectUP].move.y >= -1.0f))
				{
					g_aEffectUP[nCntEffectUP].col.a += -0.02f;
					if (g_aEffectUP[nCntEffectUP].col.a <= 0.0f)
					{
						g_aEffectUP[nCntEffectUP].bUse = false;
					}
				}
				break;
			}
			g_aEffectUP[nCntEffectUP].pos += g_aEffectUP[nCntEffectUP].move;
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-(g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, (g_aEffectUP[nCntEffectUP].fRadius / 2));
			pVtx[1].pos = D3DXVECTOR3((g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, (g_aEffectUP[nCntEffectUP].fRadius / 2));
			pVtx[2].pos = D3DXVECTOR3(-(g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, -(g_aEffectUP[nCntEffectUP].fRadius / 2));
			pVtx[3].pos = D3DXVECTOR3((g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, -(g_aEffectUP[nCntEffectUP].fRadius / 2));
			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aEffectUP[nCntEffectUP].col;
			pVtx[1].col = g_aEffectUP[nCntEffectUP].col;
			pVtx[2].col = g_aEffectUP[nCntEffectUP].col;
			pVtx[3].col = g_aEffectUP[nCntEffectUP].col;


		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffectUP->Unlock();

}

//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawEffectUP(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	// ���e�X�g��ݒ�
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ���e�X�g��L����
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0);					// ���l��0
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ���傫��

	// ���C�g�e���󂯂Ȃ�
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// Z�o�b�t�@�ւ̏�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCntEffectUP = 0; nCntEffectUP < MAX_EFFECTUP; nCntEffectUP++)
	{
		if (g_aEffectUP[nCntEffectUP].bUse == true)
		{
			if (g_aEffectUP[nCntEffectUP].nType == EFFECTUPTYPE_LEAF)
			{
				// ���u�����f�B���O�����Z�����ɐݒ�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffectUP[nCntEffectUP].mtxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEffectUP[nCntEffectUP].rot.y, g_aEffectUP[nCntEffectUP].rot.x, g_aEffectUP[nCntEffectUP].rot.z);
			D3DXMatrixMultiply(&g_aEffectUP[nCntEffectUP].mtxWorld, &g_aEffectUP[nCntEffectUP].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffectUP[nCntEffectUP].pos.x, g_aEffectUP[nCntEffectUP].pos.y, g_aEffectUP[nCntEffectUP].pos.z);
			D3DXMatrixMultiply(&g_aEffectUP[nCntEffectUP].mtxWorld, &g_aEffectUP[nCntEffectUP].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffectUP[nCntEffectUP].mtxWorld);
			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffectUP, 0, sizeof(VERTEX_3D));
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEffectUP[g_aEffectUP[nCntEffectUP].nType]);
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffectUP * 4, 2);

			if (g_aEffectUP[nCntEffectUP].nType == EFFECTUPTYPE_LEAF)
			{
				// ���u�����f�B���O�����ɖ߂�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			}
			if (g_aEffectUP[nCntEffectUP].nType == EFFECTUPTYPE_LEAF)
			{// ���Ȃ画��
				if (g_aEffectUP[nCntEffectUP].col.a >= 0.3f)
				{// ����															// �ʒu�𔽉f
					if (CollisionPlayer(g_aEffectUP[nCntEffectUP].pos,
						D3DXVECTOR3(g_aEffectUP[nCntEffectUP].mtxWorld._41, g_aEffectUP[nCntEffectUP].mtxWorld._42, g_aEffectUP[nCntEffectUP].mtxWorld._43),
						g_aEffectUP[nCntEffectUP].fRadius / 2, g_aEffectUP[nCntEffectUP].fAttackPower,
						g_aEffectUP[nCntEffectUP].fDamageH,
						g_aEffectUP[nCntEffectUP].fDamageV, g_aEffectUP[nCntEffectUP].nIdy))
					{
					}
				}
			}
		}
	}
	// Z�\�[�X
	//	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// ���C�g�e���󂯂Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// Z�o�b�t�@�ւ̏�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���e�X�g�����ɖ߂�
	//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// ���e�X�g�𖳌���

}

//==============================================================================================================================
// ���_���̍쐬
//==============================================================================================================================
void MakeVertexEffectUP(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

						// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECTUP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffectUP,
		NULL);

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffectUP->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntEffectUP = 0; nCntEffectUP < MAX_EFFECTUP; nCntEffectUP++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-(g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, (g_aEffectUP[nCntEffectUP].fRadius / 2));
		pVtx[1].pos = D3DXVECTOR3((g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, (g_aEffectUP[nCntEffectUP].fRadius / 2));
		pVtx[2].pos = D3DXVECTOR3(-(g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, -(g_aEffectUP[nCntEffectUP].fRadius / 2));
		pVtx[3].pos = D3DXVECTOR3((g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, -(g_aEffectUP[nCntEffectUP].fRadius / 2));
		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
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
	g_pVtxBuffEffectUP->Unlock();

}
//==============================================================================================================================
// �|���S���̐ݒ�
//==============================================================================================================================
void SetEffectUP(int nIdy,D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, EFFECTUPTYPE nType, float fRadius)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

						// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffectUP->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffectUP = 0; nCntEffectUP < MAX_EFFECTUP; nCntEffectUP++, pVtx += 4)
	{
		if (g_aEffectUP[nCntEffectUP].bUse == false)
		{
			g_aEffectUP[nCntEffectUP].pos = pos;
			g_aEffectUP[nCntEffectUP].move = move;
			g_aEffectUP[nCntEffectUP].rot = rot;
			g_aEffectUP[nCntEffectUP].col = col;
			g_aEffectUP[nCntEffectUP].nIdy = nIdy;
			g_aEffectUP[nCntEffectUP].nType = nType;
			g_aEffectUP[nCntEffectUP].fRadius = fRadius;
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-(g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, (g_aEffectUP[nCntEffectUP].fRadius / 2));
			pVtx[1].pos = D3DXVECTOR3((g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, (g_aEffectUP[nCntEffectUP].fRadius / 2));
			pVtx[2].pos = D3DXVECTOR3(-(g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, -(g_aEffectUP[nCntEffectUP].fRadius / 2));
			pVtx[3].pos = D3DXVECTOR3((g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, -(g_aEffectUP[nCntEffectUP].fRadius / 2));
			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aEffectUP[nCntEffectUP].col;
			pVtx[1].col = g_aEffectUP[nCntEffectUP].col;
			pVtx[2].col = g_aEffectUP[nCntEffectUP].col;
			pVtx[3].col = g_aEffectUP[nCntEffectUP].col;
			g_aEffectUP[nCntEffectUP].bUse = true;
			// �ʒu�𔽉f
			D3DXMATRIX mtxTrans;				// �v�Z�p�}�g���b�N�X
			D3DXMatrixTranslation(&mtxTrans, g_aEffectUP[nCntEffectUP].pos.x, g_aEffectUP[nCntEffectUP].pos.y, g_aEffectUP[nCntEffectUP].pos.z);
			D3DXMatrixMultiply(&g_aEffectUP[nCntEffectUP].mtxWorld, &g_aEffectUP[nCntEffectUP].mtxWorld, &mtxTrans);

			break;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffectUP->Unlock();
}
void SetEffectUPDamage(int nIdy, float fAttackPower, float fDamageH, float fDamageV, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, EFFECTUPTYPE nType, float fRadius)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

						// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffectUP->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffectUP = 0; nCntEffectUP < MAX_EFFECTUP; nCntEffectUP++, pVtx += 4)
	{
		if (g_aEffectUP[nCntEffectUP].bUse == false)
		{
			g_aEffectUP[nCntEffectUP].pos = pos;
			g_aEffectUP[nCntEffectUP].move = move;
			g_aEffectUP[nCntEffectUP].rot = rot;
			g_aEffectUP[nCntEffectUP].col = col;
			g_aEffectUP[nCntEffectUP].nIdy = nIdy;
			g_aEffectUP[nCntEffectUP].nType = nType;
			g_aEffectUP[nCntEffectUP].fRadius = fRadius;
			g_aEffectUP[nCntEffectUP].nIdy = nIdy;								// �ԍ�
			g_aEffectUP[nCntEffectUP].fAttackPower = fAttackPower;						// �_���[�W
			g_aEffectUP[nCntEffectUP].fDamageH = fDamageH;							// ���������_���[�W
			g_aEffectUP[nCntEffectUP].fDamageV = fDamageV;							// ���������_���[�W

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-(g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, (g_aEffectUP[nCntEffectUP].fRadius / 2));
			pVtx[1].pos = D3DXVECTOR3((g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, (g_aEffectUP[nCntEffectUP].fRadius / 2));
			pVtx[2].pos = D3DXVECTOR3(-(g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, -(g_aEffectUP[nCntEffectUP].fRadius / 2));
			pVtx[3].pos = D3DXVECTOR3((g_aEffectUP[nCntEffectUP].fRadius / 2), 0.0f, -(g_aEffectUP[nCntEffectUP].fRadius / 2));
			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aEffectUP[nCntEffectUP].col;
			pVtx[1].col = g_aEffectUP[nCntEffectUP].col;
			pVtx[2].col = g_aEffectUP[nCntEffectUP].col;
			pVtx[3].col = g_aEffectUP[nCntEffectUP].col;
			g_aEffectUP[nCntEffectUP].bUse = true;
			// �ʒu�𔽉f
			D3DXMATRIX mtxTrans;				// �v�Z�p�}�g���b�N�X
			D3DXMatrixTranslation(&mtxTrans, g_aEffectUP[nCntEffectUP].pos.x, g_aEffectUP[nCntEffectUP].pos.y, g_aEffectUP[nCntEffectUP].pos.z);
			D3DXMatrixMultiply(&g_aEffectUP[nCntEffectUP].mtxWorld, &g_aEffectUP[nCntEffectUP].mtxWorld, &mtxTrans);

			break;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffectUP->Unlock();
}