////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ����p���C���̏��� [libe.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "line.h"

//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define MAX_LINE	(40000)
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			// ���S���W
	D3DXVECTOR3 rot;			// ����
	LINETYPE nType;				// ���
	float fWidth;				// ��
	float fHeight;				// ����
} LineInfo;
typedef struct
{
	char *pFileName;
}LineTexture;
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void MakeVertexLine(LPDIRECT3DDEVICE9 pDevice);

//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLine = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_apTextureLine[LINETYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
Line g_aLine[MAX_LINE];
//BulletInfo g_aBulletInfo[] =
//{
//	{D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER, 30.0f, 30.0f},
//};
//LineTexture g_aLineTexInfo[LINETYPE_MAX] =
//{
//	{ "data/TEXTURE/bullet000.png" },
//};
int g_nIdyLine;
//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	//for (int nCntLineTex = 0; nCntLineTex < LINETYPE_MAX; nCntLineTex++)
	//{// �e�N�X�`���̐ݒ�
	//	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
	//		g_aLineTexInfo[nCntLineTex].pFileName,		// �t�@�C���̖��O
	//		&g_apTextureLine[nCntLineTex]);				// �e�N�X�`���ւ̃|�C���^
	//}
	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		g_aLine[nCntLine].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
		g_aLine[nCntLine].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �O��̈ʒu
		g_aLine[nCntLine].posStart = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ŏ��̈ʒu
		g_aLine[nCntLine].posEnd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �Ō�̈ʒu
		g_aLine[nCntLine].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);	// �F
		g_aLine[nCntLine].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
		g_aLine[nCntLine].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
		g_aLine[nCntLine].nType = LINETYPE_MAX;						// ���
		g_aLine[nCntLine].bUse = false;								// �g�p����Ă��邩�ǂ���
	}
	g_nIdyLine = 0;
	MakeVertexLine(pDevice);


}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitLine(void)
{
	// �e�N�X�`���̔j��
	for (int nCntLine = 0; nCntLine < LINETYPE_MAX; nCntLine++)
	{
		if (g_apTextureLine[nCntLine] != NULL)
		{
			g_apTextureLine[nCntLine]->Release();
			g_apTextureLine[nCntLine] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffLine != NULL)
	{
		g_pVtxBuffLine->Release();
		g_pVtxBuffLine = NULL;
	}
}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateLine(void)
{

}

//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;							// �r���{�[�h�p�}�g���b�N�X

	// ���C�g�e���󂯂Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		if (g_aLine[nCntLine].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aLine[nCntLine].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aLine[nCntLine].rot.y, g_aLine[nCntLine].rot.x, g_aLine[nCntLine].rot.z);
			D3DXMatrixMultiply(&g_aLine[nCntLine].mtxWorld, &g_aLine[nCntLine].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aLine[nCntLine].pos.x, g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z);
			D3DXMatrixMultiply(&g_aLine[nCntLine].mtxWorld, &g_aLine[nCntLine].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aLine[nCntLine].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, 0);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_LINELIST, nCntLine * 2, 1);
		}
	}
	// ���C�g�e���󂯂Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//==============================================================================================================================
// ���_���̍쐬
//==============================================================================================================================
void MakeVertexLine(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * MAX_LINE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLine,
		NULL);

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++, pVtx += 2)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_aLine[nCntLine].col;
		pVtx[1].col = g_aLine[nCntLine].col;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLine->Unlock();

}
//==============================================================================================================================
// ���C���̐ݒ�
//==============================================================================================================================
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 posStart, D3DXVECTOR3 posEnd, D3DXCOLOR col, LINETYPE nType)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++, pVtx += 2)
	{
		if (g_aLine[nCntLine].bUse == false)
		{
			g_aLine[nCntLine].pos = pos;
			g_aLine[nCntLine].posOld = pos;
			g_aLine[nCntLine].posStart = posStart;
			g_aLine[nCntLine].posEnd = posEnd;
			g_aLine[nCntLine].col = col;
			g_aLine[nCntLine].nType = nType;
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aLine[nCntLine].posStart.x, g_aLine[nCntLine].posStart.y, g_aLine[nCntLine].posStart.z);
			pVtx[1].pos = D3DXVECTOR3(g_aLine[nCntLine].posEnd.x, g_aLine[nCntLine].posEnd.y, g_aLine[nCntLine].posEnd.z);
			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aLine[nCntLine].col;
			pVtx[1].col = g_aLine[nCntLine].col;

			g_aLine[nCntLine].bUse = true;
			break;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLine->Unlock();
}
//==============================================================================================================================
// ���C���̏��擾
//==============================================================================================================================
int CollisionLine(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, LINETYPE nType)
{

	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMin.y, vtxMin.z), D3DXVECTOR3(vtxMin.x, vtxMax.y, vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), nType);
	SetLine(pos, D3DXVECTOR3(vtxMax.x, vtxMin.y, vtxMin.z), D3DXVECTOR3(vtxMax.x, vtxMax.y, vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), nType);
	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMin.y, vtxMax.z), D3DXVECTOR3(vtxMin.x, vtxMax.y, vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), nType);
	SetLine(pos, D3DXVECTOR3(vtxMax.x, vtxMin.y, vtxMax.z), D3DXVECTOR3(vtxMax.x, vtxMax.y, vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), nType);

	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMin.y, vtxMin.z), D3DXVECTOR3(vtxMax.x, vtxMin.y, vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), nType);
	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMin.y, vtxMin.z), D3DXVECTOR3(vtxMin.x, vtxMin.y, vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), nType);
	SetLine(pos, D3DXVECTOR3(vtxMax.x, vtxMin.y, vtxMin.z), D3DXVECTOR3(vtxMax.x, vtxMin.y, vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), nType);
	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMin.y, vtxMax.z), D3DXVECTOR3(vtxMax.x, vtxMin.y, vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), nType);

	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMax.y, vtxMin.z), D3DXVECTOR3(vtxMax.x, vtxMax.y, vtxMin.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), nType);
	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMax.y, vtxMin.z), D3DXVECTOR3(vtxMin.x, vtxMax.y, vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), nType);
	SetLine(pos, D3DXVECTOR3(vtxMax.x, vtxMax.y, vtxMin.z), D3DXVECTOR3(vtxMax.x, vtxMax.y, vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), nType);
	SetLine(pos, D3DXVECTOR3(vtxMin.x, vtxMax.y, vtxMax.z), D3DXVECTOR3(vtxMax.x, vtxMax.y, vtxMax.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), nType);
	g_nIdyLine++;
	if (!g_aLine[(g_nIdyLine-1) * 12 + 0].bUse)
	{
		return 0;
	}
	return g_nIdyLine - 1;
}
void SetPositionLine(int nIdyLine, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	g_aLine[nIdyLine * 12 + 0].pos = pos;
	g_aLine[nIdyLine * 12 + 1].pos = pos;
	g_aLine[nIdyLine * 12 + 2].pos = pos;
	g_aLine[nIdyLine * 12 + 3].pos = pos;
	g_aLine[nIdyLine * 12 + 4].pos = pos;
	g_aLine[nIdyLine * 12 + 5].pos = pos;
	g_aLine[nIdyLine * 12 + 6].pos = pos;
	g_aLine[nIdyLine * 12 + 7].pos = pos;
	g_aLine[nIdyLine * 12 + 8].pos = pos;
	g_aLine[nIdyLine * 12 + 9].pos = pos;
	g_aLine[nIdyLine * 12 + 10].pos = pos;
	g_aLine[nIdyLine * 12 + 11].pos = pos;

	g_aLine[nIdyLine * 12 + 0].rot = rot;
	g_aLine[nIdyLine * 12 + 1].rot = rot;
	g_aLine[nIdyLine * 12 + 2].rot = rot;
	g_aLine[nIdyLine * 12 + 3].rot = rot;
	g_aLine[nIdyLine * 12 + 4].rot = rot;
	g_aLine[nIdyLine * 12 + 5].rot = rot;
	g_aLine[nIdyLine * 12 + 6].rot = rot;
	g_aLine[nIdyLine * 12 + 7].rot = rot;
	g_aLine[nIdyLine * 12 + 8].rot = rot;
	g_aLine[nIdyLine * 12 + 9].rot = rot;
	g_aLine[nIdyLine * 12 + 10].rot = rot;
	g_aLine[nIdyLine * 12 + 11].rot = rot;
}
void DeleteLine(LINETYPE nType)
{
	for (int nCntLine = 0; nCntLine < MAX_LINE; nCntLine++)
	{
		if (g_aLine[nCntLine].nType == nType)
		{
			if (g_aLine[nCntLine].bUse == true)
			{
				g_aLine[nCntLine].bUse = false;
				if (nCntLine % 12 == 0)
				{
					g_nIdyLine--;
				}
			}
		}
	}


}