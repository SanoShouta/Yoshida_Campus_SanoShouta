////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���b�V�������� [meshField.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "meshField.h"
#include "input.h"
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define MAX_MESHFIELD		(100)
#define MAX_MESHFIELDTYPE	(24)
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);
//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
MeshField g_aMeshField[MAX_MESHFIELD];
MeshFieldData g_aMeshFieldData[MAX_MESHFIELDTYPE];
//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		g_aMeshField[nCntMeshField].pVtxBuff = NULL;									// ���_�o�b�t�@�ւ̃|�C���^
		g_aMeshField[nCntMeshField].pIdxBuff = NULL;									// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
		g_aMeshField[nCntMeshField].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);					// �ʒu
		g_aMeshField[nCntMeshField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
		g_aMeshField[nCntMeshField].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);				// �F
		g_aMeshField[nCntMeshField].fWidth = 0;											// ��
		g_aMeshField[nCntMeshField].fDepth = 0;											// ���s��
		g_aMeshField[nCntMeshField].nBlock_X = 0;										// �u���b�NX
		g_aMeshField[nCntMeshField].nBlock_Z = 0;										// �u���b�NZ
		g_aMeshField[nCntMeshField].fSlopeSin = 0;											// �΂�
		g_aMeshField[nCntMeshField].fSlopeSinMove = 0;										// �΂ߌv�Z
		g_aMeshField[nCntMeshField].fSlopeCos = 0;											// �΂�
		g_aMeshField[nCntMeshField].fSlopeCosMove = 0;										// �΂ߌv�Z
		g_aMeshField[nCntMeshField].nType = 0;		// ���
		g_aMeshField[nCntMeshField].fMoveVtx = 0;									// ���_���Ƃ̍���
		g_aMeshField[nCntMeshField].fTexmove = D3DXVECTOR2(0.0f,0.0f);									// �e�N�X�`���̈ړ����x
		g_aMeshField[nCntMeshField].fTexPos = D3DXVECTOR2(0.0f, 0.0f);								// �e�N�X�`���̈ړ�
		g_aMeshField[nCntMeshField].nNumVertex =(g_aMeshField[nCntMeshField].nBlock_X + 1)*(g_aMeshField[nCntMeshField].nBlock_Z + 1);// ���_��
		g_aMeshField[nCntMeshField].nNumIndex = 2*(g_aMeshField[nCntMeshField].nBlock_X*g_aMeshField[nCntMeshField].nBlock_Z)+4*(g_aMeshField[nCntMeshField].nBlock_Z - 1)+2;// �C���f�b�N�X��										//
		g_aMeshField[nCntMeshField].nNumPolygon = 2*(g_aMeshField[nCntMeshField].nBlock_X*g_aMeshField[nCntMeshField].nBlock_Z)+4*(g_aMeshField[nCntMeshField].nBlock_Z-1);	// �|���S����
		g_aMeshField[nCntMeshField].bCull = false;										// �J�����O
		g_aMeshField[nCntMeshField].bCollision = true;									// �����蔻��
		g_aMeshField[nCntMeshField].bUse = false;										// �g�p����Ă��邩�ǂ���
	}
}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitMeshField(void)
{
	// �e�N�X�`���̔j��
	for (int nCntMeshField = 0; nCntMeshField < g_aMeshFieldData[0].nNumTex; nCntMeshField++)
	{
		if (g_aMeshFieldData[nCntMeshField].pTexture != NULL)
		{
			g_aMeshFieldData[nCntMeshField].pTexture->Release();
			g_aMeshFieldData[nCntMeshField].pTexture = NULL;
		}
	}
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		// ���_�o�b�t�@�̔j��
		if (g_aMeshField[nCntMeshField].pVtxBuff != NULL)
		{
			g_aMeshField[nCntMeshField].pVtxBuff->Release();
			g_aMeshField[nCntMeshField].pVtxBuff = NULL;
		}
		// �C���f�b�N�X�o�b�t�@�o�b�t�@�̔j��
		if (g_aMeshField[nCntMeshField].pIdxBuff != NULL)
		{
			g_aMeshField[nCntMeshField].pIdxBuff->Release();
			g_aMeshField[nCntMeshField].pIdxBuff = NULL;
		}
	}
}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateMeshField(void)
{

	VERTEX_3D *pVtx;	// ���_���̃|�C���^
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		if (g_aMeshField[nCntMeshField].bUse == true)
		{
			// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
			g_aMeshField[nCntMeshField].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			// �g�ł��i���ȂǂɎg�p����Ƃ��j
#if 0
		//�@�g�ł�
			if (g_aMeshField[nCntMeshField].nType == 2|| g_aMeshField[nCntMeshField].nType == 1)
			{
				for (int nCntZ = 0; nCntZ < g_aMeshField[nCntMeshField].nBlock_Z + 1; nCntZ++)
				{
					g_aMeshField[nCntMeshField].fMoveVtx += 0.05f;
					for (int nCnt = 0; nCnt < g_aMeshField[nCntMeshField].nBlock_X + 1; nCnt++)
					{// ���b�V��
						pVtx[nCntZ*(g_aMeshField[nCntMeshField].nBlock_X + 1)].pos.y = cosf(g_aMeshField[nCntMeshField].fMoveVtx) * 50;
					}
				}
				//for (int nCntZ = 0; nCntZ < g_aMeshField[nCntMeshField].nBlock_Z + 1; nCntZ++)
				//{
				//	g_aMeshField[nCntMeshField].fSlopeSinMove += 0.001f;
				//	for (int nCnt = 0; nCnt < g_aMeshField[nCntMeshField].nBlock_X + 1; nCnt++)
				//	{// ���b�V��
				//		pVtx[nCntZ*(g_aMeshField[nCntMeshField].nBlock_X + 1) + nCnt].pos.y = cosf(g_aMeshField[nCntMeshField].fSlopeSinMove + float(nCntZ) / float(g_aMeshField[nCntMeshField].nBlock_Z)) * 10;
				//	}
				//}
			}

#endif

			// �e�N�X�`���ړ�(�C�Ȃǁj
#if 1
			g_aMeshField[nCntMeshField].fTexPos -= g_aMeshField[nCntMeshField].fTexmove;
			if (g_aMeshField[nCntMeshField].fTexPos.x <= -1.0f)
			{
				g_aMeshField[nCntMeshField].fTexPos.x = 0.0f;
			}
			if (g_aMeshField[nCntMeshField].fTexPos.y <= -1.0f)
			{
				g_aMeshField[nCntMeshField].fTexPos.y = 0.0f;
			}
			for (int nCntV = 0; nCntV < g_aMeshField[nCntMeshField].nBlock_Z + 1; nCntV++)
			{// �e�N�X�`���̐ݒ�
				for (int nCntH = 0; nCntH < g_aMeshField[nCntMeshField].nBlock_X + 1; nCntH++)
				{// "X"�͌��ɖ߂����灓�@"Z"�͌����܂��͑�����������̂Ł�
				 // �e�N�X�`���̐ݒ�
					pVtx[nCntH + (g_aMeshField[nCntMeshField].nBlock_X + 1)*nCntV].tex = D3DXVECTOR2(float(nCntH * 100 / g_aMeshField[nCntMeshField].nBlock_X) / 100.0f + g_aMeshField[nCntMeshField].fTexPos.x, float(nCntV * 100 / g_aMeshField[nCntMeshField].nBlock_Z) / 100.0f + g_aMeshField[nCntMeshField].fTexPos.y);
				}
			}

#endif
			// ���_�o�b�t�@���A�����b�N����
			g_aMeshField[nCntMeshField].pVtxBuff->Unlock();
		}
	}
}

//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	// ���e�X�g��ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);					// ���l��0
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ���傫��

	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		if (g_aMeshField[nCntMeshField].bUse == true)
		{
			if (g_aMeshField[nCntMeshField].nType == MESHFIRLDTYPE_SEAPNG)
			{
				// Z�o�b�t�@�ւ̏�������
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			}
			if (g_aMeshField[nCntMeshField].bCull == true)
			{// �J�����O�I�t
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			}
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aMeshField[nCntMeshField].mtxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshField[nCntMeshField].rot.y, g_aMeshField[nCntMeshField].rot.x, g_aMeshField[nCntMeshField].rot.z);
			D3DXMatrixMultiply(&g_aMeshField[nCntMeshField].mtxWorld, &g_aMeshField[nCntMeshField].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aMeshField[nCntMeshField].pos.x, g_aMeshField[nCntMeshField].pos.y, g_aMeshField[nCntMeshField].pos.z);
			D3DXMatrixMultiply(&g_aMeshField[nCntMeshField].mtxWorld, &g_aMeshField[nCntMeshField].mtxWorld, &mtxTrans);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshField[nCntMeshField].mtxWorld);
			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_aMeshField[nCntMeshField].pVtxBuff, 0, sizeof(VERTEX_3D));
			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_aMeshField[nCntMeshField].pIdxBuff);
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aMeshFieldData[g_aMeshField[nCntMeshField].nType].pTexture);
			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aMeshField[nCntMeshField].nNumIndex, 0, g_aMeshField[nCntMeshField].nNumPolygon);
			if (g_aMeshField[nCntMeshField].bCull == true)
			{// �J�����O�I�t
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			}
			if (g_aMeshField[nCntMeshField].nType == MESHFIRLDTYPE_SEAPNG)
			{
				// Z�o�b�t�@�ւ̏�������
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			}
		}
	}
	// ���e�X�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// ���e�X�g�𖳌���

}

//==============================================================================================================================
// ���_���̍쐬
//==============================================================================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		if (g_aMeshField[nCntMeshField].bUse == false)
		{

			// ���_���̍쐬
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aMeshField[nCntMeshField].nNumVertex,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_3D,
				D3DPOOL_MANAGED,
				&g_aMeshField[nCntMeshField].pVtxBuff,
				NULL);

			// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
			g_aMeshField[nCntMeshField].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			//float PosX = g_aMeshField[nCntMeshField].fWidth * (g_aMeshField[nCntMeshField].nBlock_X * -0.5f);
			//float PosZ = g_aMeshField[nCntMeshField].fDepth * (g_aMeshField[nCntMeshField].nBlock_Z * 0.5f);
			// ���_���W�̐ݒ�
			for (int nCnt = 0; nCnt < g_aMeshField[nCntMeshField].nNumVertex; nCnt++)
			{// "X"�͌��ɖ߂����灓�@"Z"�͌����܂��͑�����������̂Ł�
	/*			if (nCnt % (g_aMeshField[nCntMeshField].nBlock_X + 1) == 0)
				{
					PosX = g_aMeshField[nCntMeshField].fWidth *(g_aMeshField[nCntMeshField].nBlock_X * -0.5f);
					if (nCnt != 0)
					{
						PosZ -= g_aMeshField[nCntMeshField].fDepth;
					}
				}
				pVtx[nCnt].pos = D3DXVECTOR3(PosX, 0.0f, PosZ);
				PosX += g_aMeshField[nCntMeshField].fWidth;*/

				//pVtx[nCnt].pos = D3DXVECTOR3(-(g_aMeshField[nCntMeshField].fWidth  * float(g_aMeshField[nCntMeshField].nBlock_X/2) ) + (g_aMeshField[nCntMeshField].fWidth)*(nCnt % (g_aMeshField[nCntMeshField].nBlock_X + 1)),
				//	0.0f, (g_aMeshField[nCntMeshField].fDepth * g_aMeshField[nCntMeshField].nBlock_Z /2) - (g_aMeshField[nCntMeshField].fDepth)*(nCnt / (g_aMeshField[nCntMeshField].nBlock_Z + 1)));

				// ���_���̐ݒ�	���W�̒��ڎw��͂����ł͊�{�I�ɂ͂��Ȃ�(g_pos~~���𑫂������͂��Ȃ�D3DXMatrixTranslation�ł���Ă�
				for (int nCntPos = 0; nCntPos < g_aMeshField[nCntMeshField].nNumVertex; nCntPos++)
				{
					pVtx[nCntPos].pos = D3DXVECTOR3(float(-((g_aMeshField[nCntMeshField].nBlock_X * g_aMeshField[nCntMeshField].fWidth) / 2) + g_aMeshField[nCntMeshField].fWidth * (nCntPos % (g_aMeshField[nCntMeshField].nBlock_X + 1))),
						0.0f,
						float((g_aMeshField[nCntMeshField].nBlock_Z * g_aMeshField[nCntMeshField].fDepth) / 2 - g_aMeshField[nCntMeshField].fDepth * (nCntPos / (g_aMeshField[nCntMeshField].nBlock_X + 1))));
				}
			}
			// �@���̐ݒ�
			for (int nCnt = 0; nCnt < g_aMeshField[nCntMeshField].nNumVertex; nCnt++)
			{
				pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			}
			// ���_�J���[�̐ݒ�
			for (int nCnt = 0; nCnt < g_aMeshField[nCntMeshField].nNumVertex; nCnt++)
			{
				pVtx[nCnt].col = g_aMeshField[nCntMeshField].col;
			}
			//// �u���b�N���ƂɈꖇ�z�u����e�N�X�`��
			//for (int nCnt = 0; nCnt < g_aMeshField[nCntMeshField].nNumVertex; nCnt++)
			//{
			//	// �e�N�X�`���̐ݒ�
			//	pVtx[nCnt].tex = D3DXVECTOR2(0.0f + (nCnt%(g_aMeshField[nCntMeshField].nBlock_X+1)), 0.0f + (nCnt / (g_aMeshField[nCntMeshField].nBlock_X + 1)));
			//}

			if (g_aMeshField[nCntMeshField].fSlopeSin > 0 || g_aMeshField[nCntMeshField].fSlopeSin < 0)
			{
				for (int nCntZ = 0; nCntZ < g_aMeshField[nCntMeshField].nBlock_Z + 1; nCntZ++)
				{
					g_aMeshField[nCntMeshField].fSlopeSinMove += float(D3DX_PI / (g_aMeshField[nCntMeshField].nBlock_Z));
					for (int nCnt = 0; nCnt < g_aMeshField[nCntMeshField].nBlock_X + 1; nCnt++)
					{// ���b�V��
						pVtx[nCntZ*(g_aMeshField[nCntMeshField].nBlock_X + 1) + nCnt].pos.y = sinf(g_aMeshField[nCntMeshField].fSlopeSinMove) * g_aMeshField[nCntMeshField].fSlopeSin;
					}
				}
			}
			if (g_aMeshField[nCntMeshField].fSlopeCos > 0 || g_aMeshField[nCntMeshField].fSlopeCos < 0)
			{
				for (int nCntZ = 0; nCntZ < g_aMeshField[nCntMeshField].nBlock_Z + 1; nCntZ++)
				{
					g_aMeshField[nCntMeshField].fSlopeCosMove += float(D3DX_PI / (g_aMeshField[nCntMeshField].nBlock_Z));
					for (int nCnt = 0; nCnt < g_aMeshField[nCntMeshField].nBlock_X + 1; nCnt++)
					{// ���b�V��
						pVtx[nCntZ*(g_aMeshField[nCntMeshField].nBlock_X + 1) + nCnt].pos.y = cosf(g_aMeshField[nCntMeshField].fSlopeCosMove) * g_aMeshField[nCntMeshField].fSlopeCos;
					}
				}
			}
			for (int nCntV = 0; nCntV < g_aMeshField[nCntMeshField].nBlock_Z + 1; nCntV++)
			{// �e�N�X�`���̐ݒ�
				for (int nCntH = 0; nCntH < g_aMeshField[nCntMeshField].nBlock_X + 1; nCntH++)
				{// "X"�͌��ɖ߂����灓�@"Z"�͌����܂��͑�����������̂Ł�
				 // �e�N�X�`���̐ݒ�
					pVtx[nCntH + (g_aMeshField[nCntMeshField].nBlock_X + 1)*nCntV].tex = D3DXVECTOR2(float(nCntH * 100 / g_aMeshField[nCntMeshField].nBlock_X) / 100.0f + g_aMeshField[nCntMeshField].fTexPos.x, float(nCntV * 100 / g_aMeshField[nCntMeshField].nBlock_Z) / 100.0f + g_aMeshField[nCntMeshField].fTexPos.y);
				}
			}
			// ���_�o�b�t�@���A�����b�N����
			g_aMeshField[nCntMeshField].pVtxBuff->Unlock();


			WORD *pIdx;	// �C���f�b�N�X�f�[�^�ւ̃|�C���^

			// �C���f�b�N�X�o�b�t�@�̍쐬
			pDevice->CreateIndexBuffer(sizeof(WORD)*g_aMeshField[nCntMeshField].nNumIndex,
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,
				D3DPOOL_MANAGED,
				&g_aMeshField[nCntMeshField].pIdxBuff,
				NULL);

			// �C���f�b�N�X�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
			g_aMeshField[nCntMeshField].pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

			//int nCnt = 0;
			//// ���_���W�̐ݒ�
			//for (int nCntX = 0; nCntX < g_aMeshField[nCntMeshField].nNumIndex; nCntX += 2)
			//{
			//	if (g_aMeshField[nCntMeshField].nBlock_X > 1 && nCntX % ((2 + 2 * g_aMeshField[nCntMeshField].nBlock_X) + 2) == (2 + 2 * g_aMeshField[nCntMeshField].nBlock_X))
			//	{// �d�Ȃ蕔��
			//		pIdx[nCntX] = pIdx[nCntX - 1];
			//		pIdx[nCntX + 1] = (g_aMeshField[nCntMeshField].nBlock_X + 1) + int(nCnt / 2);
			//	}
			//	else
			//	{// �ʏ핔��
			//		pIdx[nCntX] = (g_aMeshField[nCntMeshField].nBlock_X + 1) + int(nCnt / 2);
			//		pIdx[nCntX + 1] = int(nCnt / 2);
			//		nCnt += 2;
			//	}
			//}

			//int nIdxX = g_aMeshField[nCntMeshField].nBlock_X + 1;
			//int nIdxZ = (g_aMeshField[nCntMeshField].nBlock_Z + 1) * 2;
			//for (int nCntMesh = 0; nCntMesh < g_aMeshField[nCntMeshField].nNumIndex; nCntMesh += 2)
			//{
			//	if (nCntMesh == nIdxZ)
			//	{
			//		pIdx[nCntMesh] = nIdxX - (g_aMeshField[nCntMeshField].nBlock_X + 2);
			//		pIdx[nCntMesh + 1] = nIdxX;
			//		nIdxZ += ((g_aMeshField[nCntMeshField].nBlock_X + 1) * 2) + 2;
			//	}
			//	else
			//	{
			//		pIdx[nCntMesh] = nIdxX;
			//		pIdx[nCntMesh + 1] = nIdxX - (g_aMeshField[nCntMeshField].nBlock_X + 1);
			//		nIdxX++;
			//	}
			//}

			// �C���f�b�N�X�̐ݒ�
			for (int nCntIdx = 0, nCntPos = 0; nCntIdx < g_aMeshField[nCntMeshField].nNumIndex; nCntIdx += 2)
			{
				if ((nCntIdx / 2) % (g_aMeshField[nCntMeshField].nBlock_X + 2) == g_aMeshField[nCntMeshField].nBlock_X + 1)
				{
					pIdx[nCntIdx] = nCntPos - 1;
					pIdx[nCntIdx + 1] = nCntPos + g_aMeshField[nCntMeshField].nBlock_X + 1;
				}
				else
				{
					pIdx[nCntIdx] = nCntPos + g_aMeshField[nCntMeshField].nBlock_X + 1;
					pIdx[nCntIdx + 1] = nCntPos;

					nCntPos++;
				}
			}
			// ���_�o�b�t�@���A�����b�N����
			g_aMeshField[nCntMeshField].pIdxBuff->Unlock();
			break;
		}
	}
}
//==============================================================================================================================
// �t�B�[���h�̂����蔻��
//==============================================================================================================================
bool CollisionMeshField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadiusWidth, float fRadiusHeight,MeshField **pMeshField)
{
	bool bLand = false;

// ���_�P�P�̂����蔻��
#if 1
	*pMeshField = NULL;
	VERTEX_3D *pVtx;	// ���_���̃|�C���^
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		if (g_aMeshField[nCntMeshField].bUse == true)
		{
			// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
			g_aMeshField[nCntMeshField].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			if (g_aMeshField[nCntMeshField].bCollision == true)
			{
				if (g_aMeshField[nCntMeshField].pos.x - g_aMeshField[nCntMeshField].fWidth  * g_aMeshField[nCntMeshField].nBlock_X / 2 < pPos->x + fRadiusWidth&&	// ��
					g_aMeshField[nCntMeshField].pos.x + g_aMeshField[nCntMeshField].fWidth  * g_aMeshField[nCntMeshField].nBlock_X / 2 > pPos->x - fRadiusWidth&&		// �E
					g_aMeshField[nCntMeshField].pos.z - g_aMeshField[nCntMeshField].fDepth  * g_aMeshField[nCntMeshField].nBlock_Z / 2 < pPos->z + fRadiusWidth&&	// ��O
					g_aMeshField[nCntMeshField].pos.z + g_aMeshField[nCntMeshField].fDepth  * g_aMeshField[nCntMeshField].nBlock_Z / 2 > pPos->z - fRadiusWidth)		// ��
				{// X Z ���͈͓�
					for (int nCnt = 0; nCnt < g_aMeshField[nCntMeshField].nNumVertex; nCnt++)
					{
						if (g_aMeshField[nCntMeshField].pos.x + pVtx[nCnt].pos.x - g_aMeshField[nCntMeshField].fWidth / 2 <= pPos->x + fRadiusWidth&&	// ��
							g_aMeshField[nCntMeshField].pos.x + pVtx[nCnt].pos.x + g_aMeshField[nCntMeshField].fWidth / 2 >= pPos->x - fRadiusWidth&&		// �E
							g_aMeshField[nCntMeshField].pos.z + pVtx[nCnt].pos.z - g_aMeshField[nCntMeshField].fDepth / 2 <= pPos->z + fRadiusWidth&&	// ��O
							g_aMeshField[nCntMeshField].pos.z + pVtx[nCnt].pos.z + g_aMeshField[nCntMeshField].fDepth / 2 >= pPos->z - fRadiusWidth)		// ��
						{
							if (g_aMeshField[nCntMeshField].rot.x == D3DX_PI)
							{// �V��Ȃ�t�����ɔ��˂���
								if (g_aMeshField[nCntMeshField].pos.y + pVtx[nCnt].pos.y <= pPos->y + fRadiusHeight&&
									g_aMeshField[nCntMeshField].pos.y + pVtx[nCnt].pos.y  > pPosOld->y + fRadiusHeight)
								{// ��
									pPos->y = g_aMeshField[nCntMeshField].pos.y + pVtx[nCnt].pos.y - fRadiusHeight;
									pMove->y = 0;
								}
							}
							else
							{
								if (g_aMeshField[nCntMeshField].bCull == true)
								{
									if (g_aMeshField[nCntMeshField].pos.y + pVtx[nCnt].pos.y <= pPos->y + fRadiusHeight&&
										g_aMeshField[nCntMeshField].pos.y + pVtx[nCnt].pos.y  > pPosOld->y + fRadiusHeight)
									{// ��
										pPos->y = g_aMeshField[nCntMeshField].pos.y + pVtx[nCnt].pos.y - fRadiusHeight;

										pMove->y = 0;
									}
								}
								if (g_aMeshField[nCntMeshField].pos.y + pVtx[nCnt].pos.y > pPos->y&&
									g_aMeshField[nCntMeshField].pos.y + pVtx[nCnt].pos.y - 10 < pPosOld->y)
								{// ��
									pPos->y = g_aMeshField[nCntMeshField].pos.y + pVtx[nCnt].pos.y;
									pMove->y = 0;
									bLand = true; // ��������
									*pMeshField = &g_aMeshField[nCntMeshField];
								}
							}
						}
					}
				}
			}
			// ���_�o�b�t�@���A�����b�N����
			g_aMeshField[nCntMeshField].pVtxBuff->Unlock();
		}
	}
#endif
	return bLand;
}
//==============================================================================================================================
// ���b�V���̐ݒ�
//==============================================================================================================================
void SetMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType, int nBlock_X, int nBlock_Z, float fWidth, float fDepth,float fSlopeSin,bool bCull)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		if (g_aMeshField[nCntMeshField].bUse == false)
		{
			g_aMeshField[nCntMeshField].pos = pos;					// �ʒu
			g_aMeshField[nCntMeshField].rot = rot;				// ����
			g_aMeshField[nCntMeshField].fWidth = fWidth;											// ��
			g_aMeshField[nCntMeshField].fDepth = fDepth;											// ���s��
			g_aMeshField[nCntMeshField].nBlock_X = nBlock_X;										// �u���b�NX
			g_aMeshField[nCntMeshField].nBlock_Z = nBlock_Z;										// �u���b�NZ
			g_aMeshField[nCntMeshField].fSlopeSin = fSlopeSin;											// �΂�
			g_aMeshField[nCntMeshField].nType = nType;		// ���
			g_aMeshField[nCntMeshField].bCull = bCull;		// �J�����O
			g_aMeshField[nCntMeshField].nNumVertex = (g_aMeshField[nCntMeshField].nBlock_X + 1)*(g_aMeshField[nCntMeshField].nBlock_Z + 1);// ���_��
			g_aMeshField[nCntMeshField].nNumIndex = 2 * (g_aMeshField[nCntMeshField].nBlock_X*g_aMeshField[nCntMeshField].nBlock_Z) + 4 * (g_aMeshField[nCntMeshField].nBlock_Z - 1) + 2;// �C���f�b�N�X��										//
			g_aMeshField[nCntMeshField].nNumPolygon = 2 * (g_aMeshField[nCntMeshField].nBlock_X*g_aMeshField[nCntMeshField].nBlock_Z) + 4 * (g_aMeshField[nCntMeshField].nBlock_Z - 1);	// �|���S����

			MakeVertexMeshField(pDevice);
			g_aMeshField[nCntMeshField].bUse = true;										// �g�p����Ă��邩�ǂ���

			break;
		}
	}
}
//==============================================================================================================================
// ���b�V���̊l��
//==============================================================================================================================
MeshField *GetMeshField(void)
{
	return &g_aMeshField[0];
}
MeshFieldData *GetMeshFieldData(void)
{
	return &g_aMeshFieldData[0];
}
