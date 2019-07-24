////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �󏈗� [sky.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "sky.h"
#include "camera.h"
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define MAX_SKY	(1)
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
	SKYTYPE nType;		// ���
	float fWidth;				// ��
	float fHeight;				// ����
	float fDepth;				// ���s��
	float fLength;				// ���a
} SkyInfo;
typedef struct
{
	char *pFileName;
}SkyTexture;
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void MakeVertexSky(LPDIRECT3DDEVICE9 pDevice);

//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureSky[SKYTYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
Sky g_aSky[MAX_SKY];
float g_fTexmove;
SkyInfo g_aSkyInfo[] =
{// ���W	����	�^�C�v	��	����	���s��	���a
	{ D3DXVECTOR3(0.0f, 0.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SKYTYPE_0,  100.0f,100.0f, 0.0f,10000.0f },
};
SkyTexture g_aGuardTexInfo[SKYTYPE_MAX] =
{
	{ "data/TEXTURE/sky001.jpg" },
};
//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCnt = 0; nCnt < SKYTYPE_MAX; nCnt++)
	{// �e�N�X�`���̐ݒ�
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			g_aGuardTexInfo[nCnt].pFileName,	// �t�@�C���̖��O
			&g_apTextureSky[nCnt]);			// �e�N�X�`���ւ̃|�C���^
	}
	for (int nCnt = 0; nCnt < MAX_SKY; nCnt++)
	{
		g_aSky[nCnt].nNumVertex = (BLOCK_X + 1) * (BLOCK_Y + 1);					// ���_��
		g_aSky[nCnt].nNumIndex = 2 * (BLOCK_X*BLOCK_Y) + 4 * (BLOCK_Y - 1) + 2;	// �C���f�b�N�X��
		g_aSky[nCnt].nNumPolygon = 2 * (BLOCK_X*BLOCK_Y) + 4 * (BLOCK_Y - 1);	// �|���S����


		g_aSky[nCnt].pos = g_aSkyInfo[nCnt].pos;			// �ʒu
		g_aSky[nCnt].rot = g_aSkyInfo[nCnt].rot;			// ����
		g_aSky[nCnt].col = g_aSkyInfo[nCnt].col;			// �F
		g_aSky[nCnt].fWidth = g_aSkyInfo[nCnt].fWidth;	// ��
		g_aSky[nCnt].fHeight = g_aSkyInfo[nCnt].fHeight;	// ����
		g_aSky[nCnt].fDepth = g_aSkyInfo[nCnt].fDepth;	// ���s��
		g_aSky[nCnt].fLength = g_aSkyInfo[nCnt].fLength;	// ���a
		g_aSky[nCnt].nType = g_aSkyInfo[nCnt].nType;		// ���
		g_aSky[nCnt].bUse = true;										// �g�p����Ă��邩�ǂ���
	}
	g_fTexmove = 0;
	MakeVertexSky(pDevice);
}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitSky(void)
{
	// �e�N�X�`���̔j��
	for (int nCntGuard = 0; nCntGuard < SKYTYPE_MAX; nCntGuard++)
	{
		if (g_apTextureSky[nCntGuard] != NULL)
		{
			g_apTextureSky[nCntGuard]->Release();
			g_apTextureSky[nCntGuard] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_SKY; nCnt++)
	{
		// ���_�o�b�t�@�̔j��
		if (g_aSky[nCnt].pVtxBuff != NULL)
		{
			g_aSky[nCnt].pVtxBuff->Release();
			g_aSky[nCnt].pVtxBuff = NULL;
		}
		// �C���f�b�N�X�o�b�t�@�o�b�t�@�̔j��
		if (g_aSky[nCnt].pIdxBuff != NULL)
		{
			g_aSky[nCnt].pIdxBuff->Release();
			g_aSky[nCnt].pIdxBuff = NULL;
		}
	}
}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateSky(void)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^
	for (int nCnt = 0; nCnt < MAX_SKY; nCnt++)
	{
		if (g_aSky[nCnt].bUse)
		{
			// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
			g_aSky[nCnt].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			g_fTexmove += 0.0003f;
			if (g_fTexmove >= 0.5f)
			{
				g_fTexmove = 0.0f;
			}
			for (int nCntV = 0; nCntV < BLOCK_Y + 1; nCntV++)
			{// �e�N�X�`���̐ݒ�
				for (int nCntH = 0; nCntH < BLOCK_X + 1; nCntH++)
				{// "X"�͌��ɖ߂����灓�@"Z"�͌����܂��͑�����������̂Ł�
				 // �e�N�X�`���̐ݒ�
					pVtx[nCntH + (BLOCK_X + 1)*nCntV].tex = D3DXVECTOR2(float(nCntH * 100 / BLOCK_X) / 100.0f + g_fTexmove, float(nCntV * 100 / BLOCK_Y) / 100.0f);
				}
			}


			// ���_�o�b�t�@���A�����b�N����
			g_aSky[nCnt].pVtxBuff->Unlock();
		}
	}
}

//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawSky(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxProjection;				// �v�Z�p�}�g���b�N�X
															// ���C�g�e���󂯂Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);					// ���l��0
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ���傫��
	for (int nCnt = 0; nCnt < MAX_SKY; nCnt++)
	{
		if (g_aSky[nCnt].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aSky[nCnt].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aSky[nCnt].rot.y, g_aSky[nCnt].rot.x, g_aSky[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aSky[nCnt].mtxWorld, &g_aSky[nCnt].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aSky[nCnt].pos.x, g_aSky[nCnt].pos.y, g_aSky[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aSky[nCnt].mtxWorld, &g_aSky[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aSky[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_aSky[nCnt].pVtxBuff, 0, sizeof(VERTEX_3D));

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_aSky[nCnt].pIdxBuff);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureSky[g_aSky[nCnt].nType]);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aSky[nCnt].nNumVertex, 0, g_aSky[nCnt].nNumPolygon);

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
void MakeVertexSky(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^
	for (int nCnt = 0; nCnt < MAX_SKY; nCnt++)
	{

		// ���_���̍쐬
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aSky[nCnt].nNumVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_aSky[nCnt].pVtxBuff,
			NULL);
		// �C���f�b�N�X�o�b�t�@�̍쐬
		pDevice->CreateIndexBuffer(sizeof(WORD)*g_aSky[nCnt].nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_aSky[nCnt].pIdxBuff,
			NULL);

		// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
		g_aSky[nCnt].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


		for (int nCntV = 0; nCntV < BLOCK_Y + 1; nCntV++)
		{
			for (int nCntH = 0; nCntH < BLOCK_X + 1; nCntH++)
			{// "X"�͌��ɖ߂����灓�@"Z"�͌����܂��͑�����������̂Ł�
				// ���_���W�̐ݒ�
				pVtx[nCntH + (BLOCK_X + 1)*nCntV].pos =
					D3DXVECTOR3(sinf(0 + (D3DX_PI * 2 / (BLOCK_X))* nCntH)*(sinf(D3DX_PI / BLOCK_Y*nCntV)*g_aSky[nCnt].fLength),
					(cosf(0 + D3DX_PI / BLOCK_Y*nCntV)*g_aSky[nCnt].fHeight*BLOCK_Y),
					cosf(0 + (D3DX_PI * 2 / (BLOCK_X))* nCntH)*(sinf(0.1f + D3DX_PI / BLOCK_Y*nCntV)*g_aSky[nCnt].fLength));
			}
		}

		for (int nCntVtx = 0; nCntVtx < g_aSky[nCnt].nNumVertex; nCntVtx++)
		{
			// �@���̐ݒ�
			pVtx[nCntVtx].nor = pVtx[nCntVtx].pos / g_aSky[nCnt].fLength;
		}
		for (int nCntVtx = 0; nCntVtx < g_aSky[nCnt].nNumVertex; nCntVtx++)
		{
			// ���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = g_aSky[nCnt].col;
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
		g_aSky[nCnt].pVtxBuff->Unlock();
	}
	for (int nCntIdxGuard = 0; nCntIdxGuard < MAX_SKY; nCntIdxGuard++)
	{// �C���f�b�N�X�̐ݒ�
		int nCnt = 0;

		WORD *pIdx;	// �C���f�b�N�X�f�[�^�ւ̃|�C���^
		// �C���f�b�N�X�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
		g_aSky[nCntIdxGuard].pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
		// ���_���W�̐ݒ�
		for (int nCntX = 0; nCntX < g_aSky[nCntIdxGuard].nNumIndex; nCntX += 2)
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
		g_aSky[nCntIdxGuard].pIdxBuff->Unlock();
	}

}
//==============================================================================================================================
// �Z�b�g
//==============================================================================================================================
void SetSky(D3DXVECTOR3 pos, float fLength)
{
	for (int nCnt = 0; nCnt < MAX_SKY; nCnt++)
	{

		g_aSky[nCnt].bUse = true;
		g_aSky[nCnt].pos = pos;
		g_aSky[nCnt].fLength = fLength;
		g_aSky[nCnt].fHeight = g_aSkyInfo[nCnt].fHeight*fLength;
	}
}

