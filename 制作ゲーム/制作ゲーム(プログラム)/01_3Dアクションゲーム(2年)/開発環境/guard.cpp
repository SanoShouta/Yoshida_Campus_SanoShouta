////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ��i���́j���� [sky.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "guard.h"
#include "camera.h"
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define MAX_GUARD	(4)
#define BLOCK_X	(50)
#define BLOCK_Y	(30)
#define VERTEX_WIDTH	(2+2*BLOCK_X)
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			// ���S���W
	D3DXVECTOR3 rot;			// ����
	D3DXCOLOR col;			// �F
	GUARDTYPE nType;		// ���
	float fWidth;				// ��
	float fHeight;				// ����
	float fDepth;				// ���s��
	float fLength;				// ���a
} GuardInfo;
typedef struct
{
	char *pFileName;
}GuardTexture;
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void MakeVertexGuard(LPDIRECT3DDEVICE9 pDevice);

//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureGuard[GUARDTYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
Guard g_aGuard[MAX_GUARD];
GuardInfo g_aGuardInfo[] =
{// ���W	����	�^�C�v	��	����	���s��	���a
	{ D3DXVECTOR3(0.0f, 100.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(0.92f, 0.43f, 0.62f, 0.5f), GUARDTYPE_0, 10.0f,1.7f, 0.0f,50.0f },
	{ D3DXVECTOR3(0.0f, 100.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(0.55f, 0.78f, 1.0f,0.5f), GUARDTYPE_0, 10.0f,1.7f, 0.0f,50.0f },
	{ D3DXVECTOR3(0.0f, 100.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f, 1.0f, 0.1f, 0.5f), GUARDTYPE_0, 10.0f,1.7f, 0.0f,50.0f },
	{ D3DXVECTOR3(0.0f, 100.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(0.1f, 1.0f, 0.1f, 0.5f), GUARDTYPE_0, 10.0f,1.7f, 0.0f,50.0f },
};
GuardTexture g_aGuardTexInfo[GUARDTYPE_MAX] =
{
	{ "data/TEXTURE/Guard.jpg" },
};
//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitGuard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntGuardTex = 0; nCntGuardTex < GUARDTYPE_MAX; nCntGuardTex++)
	{// �e�N�X�`���̐ݒ�
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			g_aGuardTexInfo[nCntGuardTex].pFileName,	// �t�@�C���̖��O
			&g_apTextureGuard[nCntGuardTex]);			// �e�N�X�`���ւ̃|�C���^
	}
	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{
		g_aGuard[nCnt].nNumVertex = (BLOCK_X + 1) * (BLOCK_Y + 1);					// ���_��
		g_aGuard[nCnt].nNumIndex = 2 * (BLOCK_X*BLOCK_Y) + 4 * (BLOCK_Y - 1) + 2;	// �C���f�b�N�X��
		g_aGuard[nCnt].nNumPolygon = 2 * (BLOCK_X*BLOCK_Y) + 4 * (BLOCK_Y - 1);	// �|���S����


		g_aGuard[nCnt].pos = g_aGuardInfo[nCnt].pos;			// �ʒu
		g_aGuard[nCnt].rot = g_aGuardInfo[nCnt].rot;			// ����
		g_aGuard[nCnt].col = g_aGuardInfo[nCnt].col;			// �F
		g_aGuard[nCnt].fWidth = g_aGuardInfo[nCnt].fWidth;	// ��
		g_aGuard[nCnt].fHeight = g_aGuardInfo[nCnt].fHeight;	// ����
		g_aGuard[nCnt].fDepth = g_aGuardInfo[nCnt].fDepth;	// ���s��
		g_aGuard[nCnt].fLength = g_aGuardInfo[nCnt].fLength;	// ���a
		g_aGuard[nCnt].nIdx = nCnt;							// �ԍ�
		g_aGuard[nCnt].nType = g_aGuardInfo[nCnt].nType;		// ���
		g_aGuard[nCnt].bUse = false;										// �g�p����Ă��邩�ǂ���

	}
	MakeVertexGuard(pDevice);
}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitGuard(void)
{
	// �e�N�X�`���̔j��
	for (int nCntGuard = 0; nCntGuard < GUARDTYPE_MAX; nCntGuard++)
	{
		if (g_apTextureGuard[nCntGuard] != NULL)
		{
			g_apTextureGuard[nCntGuard]->Release();
			g_apTextureGuard[nCntGuard] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{
		// ���_�o�b�t�@�̔j��
		if (g_aGuard[nCnt].pVtxBuff != NULL)
		{
			g_aGuard[nCnt].pVtxBuff->Release();
			g_aGuard[nCnt].pVtxBuff = NULL;
		}
		// �C���f�b�N�X�o�b�t�@�o�b�t�@�̔j��
		if (g_aGuard[nCnt].pIdxBuff != NULL)
		{
			g_aGuard[nCnt].pIdxBuff->Release();
			g_aGuard[nCnt].pIdxBuff = NULL;
		}
	}
}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateGuard(void)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{
		// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
		g_aGuard[nCnt].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


		for (int nCntV = 0; nCntV < BLOCK_Y + 1; nCntV++)
		{
			for (int nCntH = 0; nCntH < BLOCK_X + 1; nCntH++)
			{// "X"�͌��ɖ߂����灓�@"Z"�͌����܂��͑�����������̂Ł�
			 // ���_���W�̐ݒ�
				pVtx[nCntH + (BLOCK_X + 1)*nCntV].pos = D3DXVECTOR3(sinf(0 + (-D3DX_PI * 2 / (BLOCK_X))* nCntH)*(sinf(D3DX_PI / BLOCK_Y*nCntV)*g_aGuard[nCnt].fLength),
					(cosf(0 + D3DX_PI / BLOCK_Y*nCntV)*g_aGuard[nCnt].fHeight*BLOCK_Y),
					cosf(0 + (-D3DX_PI * 2 / (BLOCK_X))* nCntH)*(sinf(0.1f + D3DX_PI / BLOCK_Y*nCntV)*g_aGuard[nCnt].fLength));
			}
		}
		// ���_�o�b�t�@���A�����b�N����
		g_aGuard[nCnt].pVtxBuff->Unlock();
	}
}

//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawGuard(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxProjection;				// �v�Z�p�}�g���b�N�X
	// ���C�g�e���󂯂Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);					// ���l��0
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ���傫��


	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{
		if (g_aGuard[nCnt].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aGuard[nCnt].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aGuard[nCnt].rot.y, g_aGuard[nCnt].rot.x, g_aGuard[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aGuard[nCnt].mtxWorld, &g_aGuard[nCnt].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aGuard[nCnt].pos.x, g_aGuard[nCnt].pos.y, g_aGuard[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aGuard[nCnt].mtxWorld, &g_aGuard[nCnt].mtxWorld, &mtxTrans);

			// �r���[�}�g���b�N�X��ݒ�
			D3DXMATRIX matrix = g_aGuard[nCnt].mtxWorld *GetCamera()[0].mtxView * GetCamera()[0].mtxProjection;

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aGuard[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_aGuard[nCnt].pVtxBuff, 0, sizeof(VERTEX_3D));

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_aGuard[nCnt].pIdxBuff);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureGuard[g_aGuard[nCnt].nType]);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aGuard[nCnt].nNumVertex, 0, g_aGuard[nCnt].nNumPolygon);

		}
	}

	// ���e�X�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// ���e�X�g�𖳌���
	// ���C�g�e���󂯂Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//==============================================================================================================================
// ���_���̍쐬
//==============================================================================================================================
void MakeVertexGuard(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^
	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{

		// ���_���̍쐬
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aGuard[nCnt].nNumVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_aGuard[nCnt].pVtxBuff,
			NULL);
		// �C���f�b�N�X�o�b�t�@�̍쐬
		pDevice->CreateIndexBuffer(sizeof(WORD)*g_aGuard[nCnt].nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_aGuard[nCnt].pIdxBuff,
			NULL);

		// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
		g_aGuard[nCnt].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


		for (int nCntV = 0; nCntV < BLOCK_Y + 1; nCntV++)
		{
			for (int nCntH = 0; nCntH < BLOCK_X + 1; nCntH++)
			{// "X"�͌��ɖ߂����灓�@"Z"�͌����܂��͑�����������̂Ł�
				// ���_���W�̐ݒ�
				pVtx[nCntH + (BLOCK_X + 1)*nCntV].pos = D3DXVECTOR3(sinf(0 + (-D3DX_PI * 2 / (BLOCK_X))* nCntH)*(sinf(D3DX_PI / BLOCK_Y*nCntV)*g_aGuard[nCnt].fLength),
					(cosf(0 + D3DX_PI / BLOCK_Y*nCntV)*g_aGuard[nCnt].fHeight*BLOCK_Y),
					cosf(0 + (-D3DX_PI * 2 / (BLOCK_X))* nCntH)*(sinf(0.1f + D3DX_PI / BLOCK_Y*nCntV)*g_aGuard[nCnt].fLength));
			}
		}

		for (int nCntVtx = 0; nCntVtx < g_aGuard[nCnt].nNumVertex; nCntVtx++)
		{
			// �@���̐ݒ�
			pVtx[nCntVtx].nor = pVtx[nCntVtx].pos / g_aGuard[nCnt].fLength;
		}
		for (int nCntVtx = 0; nCntVtx < g_aGuard[nCnt].nNumVertex; nCntVtx++)
		{
			// ���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = g_aGuard[nCnt].col;
		}
		for (int nCntV = 0; nCntV < BLOCK_Y + 1; nCntV++)
		{// �e�N�X�`���̐ݒ�
			for (int nCntH = 0; nCntH < BLOCK_X + 1; nCntH++)
			{// "X"�͌��ɖ߂����灓�@"Z"�͌����܂��͑�����������̂Ł�
			// �e�N�X�`���̐ݒ�
				pVtx[nCntH + (BLOCK_X + 1)*nCntV].tex = D3DXVECTOR2(float(nCntH * 100 / BLOCK_X) / 100.0f, float(nCntV * 100 / BLOCK_Y) / 100.0f);
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		g_aGuard[nCnt].pVtxBuff->Unlock();
	}
	for (int nCntIdxGuard = 0; nCntIdxGuard < MAX_GUARD; nCntIdxGuard++)
	{// �C���f�b�N�X�̐ݒ�
		int nCnt = 0;

		WORD *pIdx;	// �C���f�b�N�X�f�[�^�ւ̃|�C���^
		// �C���f�b�N�X�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
		g_aGuard[nCntIdxGuard].pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
		// ���_���W�̐ݒ�
		for (int nCntX = 0; nCntX < g_aGuard[nCntIdxGuard].nNumIndex; nCntX += 2)
		{
			if (BLOCK_Y > 1 && nCntX % (VERTEX_WIDTH + 2) == VERTEX_WIDTH)
			{// �d�Ȃ蕔��
				pIdx[nCntX] = pIdx[nCntX - 1];
				pIdx[nCntX + 1] = (BLOCK_X + 1) + int(nCnt / 2);
			}
			else
			{// �ʏ핔��
				pIdx[nCntX] = (BLOCK_X + 1) + int(nCnt / 2);
				pIdx[nCntX + 1] = int(nCnt / 2);
				nCnt += 2;
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		g_aGuard[nCntIdxGuard].pIdxBuff->Unlock();
	}

}
//==============================================================================================================================
// �K�[�h�Z�b�g
//==============================================================================================================================
void SetGuard(int nIdx, D3DXVECTOR3 pos, float fLength)
{
	g_aGuard[nIdx].bUse = true;
	g_aGuard[nIdx].pos = pos;
	g_aGuard[nIdx].fLength = g_aGuardInfo[nIdx].fLength*fLength;
	g_aGuard[nIdx].fHeight = g_aGuardInfo[nIdx].fHeight*fLength;
}
//==============================================================================================================================
// �K�[�h�폜
//==============================================================================================================================
void UnSetGuard(int nIdx, float fLength)
{
	g_aGuard[nIdx].bUse = false;
	g_aGuard[nIdx].fLength = g_aGuardInfo[nIdx].fLength*fLength;
	g_aGuard[nIdx].fHeight = g_aGuardInfo[nIdx].fHeight*fLength;

}
