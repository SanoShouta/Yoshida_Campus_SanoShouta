////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���b�V���Ǐ��� [meshwall.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "meshWall.h"
#include "line.h"
#include "event.h"
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define MAX_MESHWALL	(100)
#define MAX_MESHWALLTYPE	(24)
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice);
//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
MeshWall g_aMeshWall[MAX_MESHWALL];
MeshWallData g_aMeshWallData[MAX_MESHWALLTYPE];

//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		g_aMeshWall[nCntMeshWall].pVtxBuff = NULL;										// ���_�o�b�t�@�ւ̃|�C���^
		g_aMeshWall[nCntMeshWall].pIdxBuff = NULL;										// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
		g_aMeshWall[nCntMeshWall].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);			// �ʒu
		g_aMeshWall[nCntMeshWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
		g_aMeshWall[nCntMeshWall].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// �F
		g_aMeshWall[nCntMeshWall].fWidth = 0;		// ��
		g_aMeshWall[nCntMeshWall].fHeight = 0;	// ����
		g_aMeshWall[nCntMeshWall].nBlock_X = 1;	// �u���b�NX
		g_aMeshWall[nCntMeshWall].nBlock_Y = 1;	// �u���b�NY
		g_aMeshWall[nCntMeshWall].nType = 0;		// ���
		g_aMeshWall[nCntMeshWall].fMoveVtx = 0;										// ���_���Ƃ̍���
		g_aMeshWall[nCntMeshWall].fTexmoveMesh = 0;									// �e�N�X�`���̈ړ����x
		g_aMeshWall[nCntMeshWall].bCull = false;										// �J�����O���邩���Ȃ���
		g_aMeshWall[nCntMeshWall].bCollision = true;									// ���肠�邩�Ȃ���
		g_aMeshWall[nCntMeshWall].bUse = false;											// �g�p����Ă��邩�ǂ���

	}
}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitMeshWall(void)
{
	// �e�N�X�`���̔j��
	for (int nCntMeshWall = 0; nCntMeshWall < g_aMeshWallData[0].nNumTex; nCntMeshWall++)
	{
		if (g_aMeshWallData[nCntMeshWall].pTexture!= NULL)
		{
			g_aMeshWallData[nCntMeshWall].pTexture->Release();
			g_aMeshWallData[nCntMeshWall].pTexture = NULL;
		}
	}
	for (int nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		// ���_�o�b�t�@�̔j��
		if (g_aMeshWall[nCntMeshWall].pVtxBuff != NULL)
		{
			g_aMeshWall[nCntMeshWall].pVtxBuff->Release();
			g_aMeshWall[nCntMeshWall].pVtxBuff = NULL;
		}
		// �C���f�b�N�X�o�b�t�@�o�b�t�@�̔j��
		if (g_aMeshWall[nCntMeshWall].pIdxBuff != NULL)
		{
			g_aMeshWall[nCntMeshWall].pIdxBuff->Release();
			g_aMeshWall[nCntMeshWall].pIdxBuff = NULL;
		}
	}
}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateMeshWall(void)
{
	//VERTEX_3D *pVtx;	// ���_���̃|�C���^
	for (int nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		if (g_aMeshWall[nCntMeshWall].bUse == true)
		{
			g_aMeshWall[nCntMeshWall].col = GetEventColor();
			// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
		//	g_aMeshWall[nCntMeshWall].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			// �g�ł��i���ȂǂɎg�p����Ƃ��j
#if 0
		//�@�g�ł�
			g_aMeshWall[nCntMeshWall].fMoveVtx += 0.1f;
			for (int nCntZ = 0; nCntZ < BLOCK_Z + 1; nCntZ++)
			{
				for (int nCnt = 0; nCnt < BLOCK_X + 1; nCnt++)
				{// ���b�V��
					pVtx[0 + nCnt + nCntZ*(BLOCK_Z + 1)].pos.y = cosf(g_aMeshWall[nCntMeshWall].fMoveVtx + float(nCntZ) / 10.0f) * 10;
				}
			}
#endif
			// �e�N�X�`���ړ�(�C�Ȃǁj
#if 0
			g_aMeshWall[0].fTexmoveMesh -= 0.0003f;
			g_aMeshWall[1].fTexmoveMesh -= 0.0005f;
			if (g_aMeshWall[nCntMeshWall].fTexmoveMesh <= -0.5f)
			{
				g_aMeshWall[nCntMeshWall].fTexmoveMesh = 0.0f;
			}
			for (int nCntV = 0; nCntV < g_aMeshWall[nCntMeshWall].nBlock_Y + 1; nCntV++)
			{// �e�N�X�`���̐ݒ�
				for (int nCntH = 0; nCntH < g_aMeshWall[nCntMeshWall].nBlock_X + 1; nCntH++)
				{// "X"�͌��ɖ߂����灓�@"Z"�͌����܂��͑�����������̂Ł�
				 // �e�N�X�`���̐ݒ�
					pVtx[nCntH + (g_aMeshWall[nCntMeshWall].nBlock_X + 1)*nCntV].tex = D3DXVECTOR2(float(nCntH * 100 / g_aMeshWall[nCntMeshWall].nBlock_X) / 100.0f, float(nCntV * 100 / g_aMeshWall[nCntMeshWall].nBlock_Y) / 100.0f + g_aMeshWall[nCntMeshWall].fTexmoveMesh);
				}
			}
#endif
			// ���_�o�b�t�@���A�����b�N����
		//	g_aMeshWall[nCntMeshWall].pVtxBuff->Unlock();
		}
	}
}

//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	//// ���u�����f�B���O�����Z�����ɐݒ�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);



	for (int nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		if (g_aMeshWall[nCntMeshWall].bUse == true)
		{
			if (g_aMeshWall[nCntMeshWall].nType == 4)
			{
				// Z�o�b�t�@�ւ̏�������
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			}
			if (g_aMeshWall[nCntMeshWall].bCull == true)
			{// �J�����O�I�t
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			}

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aMeshWall[nCntMeshWall].mtxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshWall[nCntMeshWall].rot.y, g_aMeshWall[nCntMeshWall].rot.x, g_aMeshWall[nCntMeshWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorld, &g_aMeshWall[nCntMeshWall].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aMeshWall[nCntMeshWall].pos.x, g_aMeshWall[nCntMeshWall].pos.y, g_aMeshWall[nCntMeshWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorld, &g_aMeshWall[nCntMeshWall].mtxWorld, &mtxTrans);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCntMeshWall].mtxWorld);
			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_aMeshWall[nCntMeshWall].pVtxBuff, 0, sizeof(VERTEX_3D));
			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_aMeshWall[nCntMeshWall].pIdxBuff);
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aMeshWallData[g_aMeshWall[nCntMeshWall].nType].pTexture);
			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aMeshWall[nCntMeshWall].nNumIndex, 0, g_aMeshWall[nCntMeshWall].nNumPolygon);
			if (g_aMeshWall[nCntMeshWall].bCull == true)
			{// �J�����O�I�t
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			}
			if (g_aMeshWall[nCntMeshWall].nType == 4)
			{
				// Z�o�b�t�@�ւ̏�������
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			}
		}
	}
	//// ���u�����f�B���O�����ɖ߂�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//==============================================================================================================================
// ���_���̍쐬
//==============================================================================================================================
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^
	for (int nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		if (g_aMeshWall[nCntMeshWall].bUse == false)
		{
			// ���_���̍쐬
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aMeshWall[nCntMeshWall].nNumVertex,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_3D,
				D3DPOOL_MANAGED,
				&g_aMeshWall[nCntMeshWall].pVtxBuff,
				NULL);

			// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
			g_aMeshWall[nCntMeshWall].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			// ���_���W�̐ݒ�
			for (int nCnt = 0; nCnt < g_aMeshWall[nCntMeshWall].nNumVertex; nCnt++)
			{// "X"�͌��ɖ߂����灓�@"Z"�͌����܂��͑�����������̂Ł�
				pVtx[nCnt].pos = D3DXVECTOR3(-(g_aMeshWall[nCntMeshWall].fWidth  * g_aMeshWall[nCntMeshWall].nBlock_X / 2) + (g_aMeshWall[nCntMeshWall].fWidth )*(nCnt % (g_aMeshWall[nCntMeshWall].nBlock_X + 1)),
					(g_aMeshWall[nCntMeshWall].fHeight * g_aMeshWall[nCntMeshWall].nBlock_Y) - (g_aMeshWall[nCntMeshWall].fHeight)*(nCnt / (g_aMeshWall[nCntMeshWall].nBlock_X + 1)), 0.0f);
			}

			// �@���̐ݒ�
			for (int nCnt = 0; nCnt < g_aMeshWall[nCntMeshWall].nNumVertex; nCnt++)
			{
				pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			}
			// ���_�J���[�̐ݒ�
			for (int nCnt = 0; nCnt < g_aMeshWall[nCntMeshWall].nNumVertex; nCnt++)
			{
				pVtx[nCnt].col = g_aMeshWall[nCntMeshWall].col;
			}
			// �u���b�N���ƂɈꖇ�z�u����e�N�X�`��
			for (int nCnt = 0; nCnt < g_aMeshWall[nCntMeshWall].nNumVertex; nCnt++)
			{
				// �e�N�X�`���̐ݒ�
				pVtx[nCnt].tex = D3DXVECTOR2(0.0f + (nCnt%(g_aMeshWall[nCntMeshWall].nBlock_X+1)), 0.0f + (nCnt / (g_aMeshWall[nCntMeshWall].nBlock_X + 1)));
			}

			//// �����e�N�X�`��
			//for (int nCntV = 0; nCntV < g_aMeshWall[nCntMeshWall].nBlock_Y + 1; nCntV++)
			//{// �e�N�X�`���̐ݒ�
			//	for (int nCntH = 0; nCntH < g_aMeshWall[nCntMeshWall].nBlock_X + 1; nCntH++)
			//	{// "X"�͌��ɖ߂����灓�@"Z"�͌����܂��͑�����������̂Ł�
			//	 // �e�N�X�`���̐ݒ�
			//		pVtx[nCntH + (g_aMeshWall[nCntMeshWall].nBlock_X + 1)*nCntV].tex = D3DXVECTOR2(float(nCntH * 100 / g_aMeshWall[nCntMeshWall].nBlock_X) / 100.0f + g_aMeshWall[nCntMeshWall].fTexmoveMesh, float(nCntV * 100 / g_aMeshWall[nCntMeshWall].nBlock_Y) / 100.0f);
			//	}
			//}
			// ���_�o�b�t�@���A�����b�N����
			g_aMeshWall[nCntMeshWall].pVtxBuff->Unlock();

			WORD *pIdx;	// �C���f�b�N�X�f�[�^�ւ̃|�C���^

				// �C���f�b�N�X�o�b�t�@�̍쐬
			pDevice->CreateIndexBuffer(sizeof(WORD)*g_aMeshWall[nCntMeshWall].nNumIndex,
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,
				D3DPOOL_MANAGED,
				&g_aMeshWall[nCntMeshWall].pIdxBuff,
				NULL);

			// �C���f�b�N�X�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
			g_aMeshWall[nCntMeshWall].pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

			// �C���f�b�N�X�̐ݒ�
			for (int nCntIdx = 0, nCntPos = 0; nCntIdx < g_aMeshWall[nCntMeshWall].nNumIndex; nCntIdx += 2)
			{
				if ((nCntIdx / 2) % (g_aMeshWall[nCntMeshWall].nBlock_X + 2) == g_aMeshWall[nCntMeshWall].nBlock_X + 1)
				{
					pIdx[nCntIdx] = nCntPos - 1;
					pIdx[nCntIdx + 1] = nCntPos + g_aMeshWall[nCntMeshWall].nBlock_X + 1;
				}
				else
				{
					pIdx[nCntIdx] = nCntPos + g_aMeshWall[nCntMeshWall].nBlock_X + 1;
					pIdx[nCntIdx + 1] = nCntPos;

					nCntPos++;
				}
			}
			// ���_�o�b�t�@���A�����b�N����
			g_aMeshWall[nCntMeshWall].pIdxBuff->Unlock();
			break;
		}
	}
}
//==============================================================================================================================
// �ǂ̂����蔻��
//==============================================================================================================================
bool CollisionMeshWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadiusWidth, float fRadiusHeight)
{
	bool bCollision = false;

	// �ʏ�̂����蔻��
	for (int nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		if (g_aMeshWall[nCntMeshWall].bUse == true)
		{
			if (g_aMeshWall[nCntMeshWall].bCollision == true)
			{
				if (g_aMeshWall[nCntMeshWall].rot.y == 0.0f || g_aMeshWall[nCntMeshWall].rot.y == D3DX_PI)
				{
					if (g_aMeshWall[nCntMeshWall].pos.x - g_aMeshWall[nCntMeshWall].fWidth * g_aMeshWall[nCntMeshWall].nBlock_X / 2 <= pPos->x + fRadiusWidth&&	// ��
						g_aMeshWall[nCntMeshWall].pos.x + g_aMeshWall[nCntMeshWall].fWidth * g_aMeshWall[nCntMeshWall].nBlock_X / 2 >= pPos->x - fRadiusWidth&&	// �E
						g_aMeshWall[nCntMeshWall].pos.y + g_aMeshWall[nCntMeshWall].fHeight * g_aMeshWall[nCntMeshWall].nBlock_Y > pPos->y&&// ��
						g_aMeshWall[nCntMeshWall].pos.y <= pPos->y + fRadiusHeight)	// ��
					{// X Y ���͈͓�
						if (g_aMeshWall[nCntMeshWall].rot.y == 0.0f)
						{
							if (g_aMeshWall[nCntMeshWall].pos.z < pPos->z + fRadiusWidth&&
								g_aMeshWall[nCntMeshWall].pos.z >= pPosOld->z + fRadiusWidth)
							{//	�O
								pPos->z = g_aMeshWall[nCntMeshWall].pos.z - fRadiusWidth;
								pMove->z = 0;
								bCollision = true; // ��������
							}
						}
						if (g_aMeshWall[nCntMeshWall].rot.y == D3DX_PI)
						{// 180�x��]������
							if (g_aMeshWall[nCntMeshWall].pos.z > pPos->z - fRadiusWidth&&
								g_aMeshWall[nCntMeshWall].pos.z <= pPosOld->z - fRadiusWidth)
							{//	���
								pPos->z = g_aMeshWall[nCntMeshWall].pos.z + fRadiusWidth;
								pMove->z = 0;
								bCollision = true; // ��������
							}
						}
					}
				}
				else
				{
					if (g_aMeshWall[nCntMeshWall].pos.z - g_aMeshWall[nCntMeshWall].fWidth * g_aMeshWall[nCntMeshWall].nBlock_X / 2 <= pPos->z + fRadiusWidth&&	// ��
						g_aMeshWall[nCntMeshWall].pos.z + g_aMeshWall[nCntMeshWall].fWidth * g_aMeshWall[nCntMeshWall].nBlock_X / 2 >= pPos->z - fRadiusWidth&&	// �E
						g_aMeshWall[nCntMeshWall].pos.y + g_aMeshWall[nCntMeshWall].fHeight * g_aMeshWall[nCntMeshWall].nBlock_Y > pPos->y&&// ��
						g_aMeshWall[nCntMeshWall].pos.y <= pPos->y + fRadiusHeight)	// ��
					{
						if (g_aMeshWall[nCntMeshWall].rot.y == D3DX_PI / 2)
						{// 90�x��]������
							if (g_aMeshWall[nCntMeshWall].pos.x < pPos->x + fRadiusWidth&&
								g_aMeshWall[nCntMeshWall].pos.x >= pPosOld->x + fRadiusWidth)
							{//	���
								pPos->x = g_aMeshWall[nCntMeshWall].pos.x - fRadiusWidth;
								pMove->x = 0;
								bCollision = true; // ��������
							}
						}
						if (g_aMeshWall[nCntMeshWall].rot.y == -D3DX_PI / 2)
						{// -90�x��]������
							if (g_aMeshWall[nCntMeshWall].pos.x > pPos->x - fRadiusWidth&&
								g_aMeshWall[nCntMeshWall].pos.x <= pPosOld->x - fRadiusWidth)
							{//	���
								pPos->x = g_aMeshWall[nCntMeshWall].pos.x + fRadiusWidth;
								pMove->x = 0;
								bCollision = true; // ��������
							}
						}
					}
				}
			}
		}
	}
	return bCollision;
}
bool CollisionVecMeshWall(D3DXVECTOR3 pPos, D3DXVECTOR3 posOld, D3DXVECTOR3 *pMove, float fRadiusWidth, float fRadiusHeight)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^
	bool bCollision = false;
	D3DXVECTOR3 MeshWallvec[4];
	D3DXVECTOR3 vec[4];
	D3DXVECTOR3 vecOld[4];

	D3DXVECTOR3 pos = pPos;
	D3DXVECTOR3 PosOld = posOld;
	D3DXVECTOR3 vecMove;
	D3DXVECTOR3 vecA;
	D3DXVECTOR3 vecB;
	float vecC;

	// �ʏ�̂����蔻��
	for (int nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		if (g_aMeshWall[nCntMeshWall].bUse == true)
		{
			// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
			g_aMeshWall[nCntMeshWall].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			if (g_aMeshWall[nCntMeshWall].pos.x - g_aMeshWall[nCntMeshWall].fWidth  * g_aMeshWall[nCntMeshWall].nBlock_X / 2 <= pPos.x + fRadiusWidth&&	// ��
				g_aMeshWall[nCntMeshWall].pos.x + g_aMeshWall[nCntMeshWall].fWidth  * g_aMeshWall[nCntMeshWall].nBlock_X / 2 >= pPos.x - fRadiusWidth&&	// �E
				g_aMeshWall[nCntMeshWall].pos.y + g_aMeshWall[nCntMeshWall].fHeight * g_aMeshWall[nCntMeshWall].nBlock_Y > pPos.y&&// ��
				g_aMeshWall[nCntMeshWall].pos.y <= pPos.y + fRadiusHeight)	// ��
			{// X Y ���͈͓�

				vecMove = D3DXVECTOR3((pos.x - PosOld.x), (pos.y - PosOld.y), pos.z - PosOld.z);
				vecA = D3DXVECTOR3(-(pos.x - PosOld.x), -(pos.y - PosOld.y), -(pos.z - PosOld.z));
				vecB = pVtx[0].nor;
				vecC = ((vecA.x *vecB.x) + (vecA.z *vecB.z));

				MeshWallvec[0] = ((pVtx[1].pos) - (pVtx[0].pos));
				vec[0] = pPos - (pVtx[0].pos + g_aMeshWall[nCntMeshWall].pos);
				vecOld[0] = posOld - (pVtx[0].pos + g_aMeshWall[nCntMeshWall].pos);
				if (g_aMeshWall[nCntMeshWall].rot.y == D3DX_PI)
				{
					vecB = -pVtx[0].nor;
					MeshWallvec[0] = ((pVtx[0].pos) - (pVtx[1].pos));
					vec[0] = pPos - (pVtx[1].pos + g_aMeshWall[nCntMeshWall].pos);
					vecOld[0] = posOld - (pVtx[1].pos + g_aMeshWall[nCntMeshWall].pos);
				}
				if ((MeshWallvec[0].z*vecOld[0].x) - (MeshWallvec[0].x*vecOld[0].z) > 0)
				{
					if (((MeshWallvec[0].z*vec[0].x) - (MeshWallvec[0].x*vec[0].z)) < 0)
					{
						pMove->x = (vecMove.x + (vecC*2.0f))*pVtx[0].nor.x;
						pMove->y = vecMove.y + (vecC*2.0f)*pVtx[0].nor.y;
						pMove->z = vecMove.z + (vecC*2.0f)*pVtx[0].nor.z;

						bCollision = true;
					}
				}
			}

			// ���_�o�b�t�@���A�����b�N����
			g_aMeshWall[nCntMeshWall].pVtxBuff->Unlock();
		}
	}
	return bCollision;

}
//==============================================================================================================================
// ���b�V���̐ݒ�
//==============================================================================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, int nBlock_X, int nBlock_Y, float fWidth, float fHeight, bool bCull)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntMeshWall = 0; nCntMeshWall < MAX_MESHWALL; nCntMeshWall++)
	{
		if (g_aMeshWall[nCntMeshWall].bUse == false)
		{
			g_aMeshWall[nCntMeshWall].pos = pos;					// �ʒu
			g_aMeshWall[nCntMeshWall].rot = rot;				// ����
			g_aMeshWall[nCntMeshWall].fWidth = fWidth;											// ��
			g_aMeshWall[nCntMeshWall].fHeight = fHeight;											// ���s��
			g_aMeshWall[nCntMeshWall].nBlock_X = nBlock_X;										// �u���b�NX
			g_aMeshWall[nCntMeshWall].nBlock_Y = nBlock_Y;										// �u���b�NZ
			g_aMeshWall[nCntMeshWall].nType = nType;		// ���
			g_aMeshWall[nCntMeshWall].bCull = bCull;		// �J�����O
			g_aMeshWall[nCntMeshWall].nNumVertex = (g_aMeshWall[nCntMeshWall].nBlock_X + 1)*(g_aMeshWall[nCntMeshWall].nBlock_Y + 1);											// ���_��
			g_aMeshWall[nCntMeshWall].nNumIndex = 2 * (g_aMeshWall[nCntMeshWall].nBlock_X*g_aMeshWall[nCntMeshWall].nBlock_Y) + 4 * (g_aMeshWall[nCntMeshWall].nBlock_Y - 1) + 2;	// �C���f�b�N�X��										//
			g_aMeshWall[nCntMeshWall].nNumPolygon = 2 * (g_aMeshWall[nCntMeshWall].nBlock_X*g_aMeshWall[nCntMeshWall].nBlock_Y) + 4 * (g_aMeshWall[nCntMeshWall].nBlock_Y - 1);	// �|���S����

			MakeVertexMeshWall(pDevice);
			g_aMeshWall[nCntMeshWall].bUse = true;										// �g�p����Ă��邩�ǂ���
			break;
		}
	}
}
//==============================================================================================================================
// ���b�V���̊l��
//==============================================================================================================================
MeshWall *GetMeshWall(void)
{
	return &g_aMeshWall[0];
}
MeshWallData *GetMeshWallData(void)
{
	return &g_aMeshWallData[0];
}
