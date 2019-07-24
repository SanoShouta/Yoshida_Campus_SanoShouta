////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �O�Ղ̏��� [orbit.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "orbit.h"
#include "player.h"
#include "gamepad.h"
#include "input.h"
#include "game.h"
#include "player.h"

//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef struct
{
	char *pFileName;
}OrbitTexture;
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void MakeVertexOrbit(LPDIRECT3DDEVICE9 pDevice);

//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureOrbit[ORBITTYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff= NULL;	// ���_�o�b�t�@�ւ̃|�C���^

Orbit g_aOrbit[MAX_ORBIT];
OrbitTexture g_aOrbitTexInfo[ORBITTYPE_MAX] =
{
	{ "data/TEXTURE/orbit000.jpg" },
	{ "data/TEXTURE/orbit001.jpg" },
	{ "data/TEXTURE/orbit002.jpg" },
	{ "data/TEXTURE/orbit003.jpg" },
};
int g_nCntOrbit;
//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitOrbit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntOrbitTex = 0; nCntOrbitTex < ORBITTYPE_MAX; nCntOrbitTex++)
	{// �e�N�X�`���̐ݒ�
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			g_aOrbitTexInfo[nCntOrbitTex].pFileName,	// �t�@�C���̖��O
			&g_apTextureOrbit[nCntOrbitTex]);			// �e�N�X�`���ւ̃|�C���^
	}

	for (int nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{
		g_aOrbit[nCntOrbit].nType = ORBITTYPE_0;					// ���
		g_aOrbit[nCntOrbit].nMotionType = PLAYER_MOTION_TYPE_MAX;
		g_aOrbit[nCntOrbit].Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �n�_
		g_aOrbit[nCntOrbit].End = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_aOrbit[nCntOrbit].InitStart = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �n�_
		g_aOrbit[nCntOrbit].InitEnd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_aOrbit[nCntOrbit].nLength = MAX_ORBIT_LENGTH;				// ����
		g_aOrbit[nCntOrbit].nCntTrueTime = 0;						// ������܂ł̎���
		g_aOrbit[nCntOrbit].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
		g_aOrbit[nCntOrbit].bUse = false;							// �g�p����Ă��邩�ǂ���
	}
	MakeVertexOrbit(pDevice);

}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitOrbit(void)
{
	// �e�N�X�`���̔j��
	for (int nCntOrbit = 0; nCntOrbit < ORBITTYPE_MAX; nCntOrbit++)
	{
		if (g_apTextureOrbit[nCntOrbit] != NULL)
		{
			g_apTextureOrbit[nCntOrbit]->Release();
			g_apTextureOrbit[nCntOrbit] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuff != NULL)
	{
		g_pVtxBuff->Release();
		g_pVtxBuff = NULL;
	}

}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateOrbit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++,pVtx+=4)
	{
		if (g_aOrbit[nCntOrbit].bUse)
		{
			g_aOrbit[nCntOrbit].col.a -= 0.03f;
			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aOrbit[nCntOrbit].col;
			pVtx[1].col = g_aOrbit[nCntOrbit].col;
			pVtx[2].col = g_aOrbit[nCntOrbit].col;
			pVtx[3].col = g_aOrbit[nCntOrbit].col;
			if (g_aOrbit[nCntOrbit].col.a <= 0)
			{
				g_aOrbit[nCntOrbit].bUse = false;
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuff->Unlock();

}

//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawOrbit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxPlayerWorld;
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);					// Z�o�b�t�@�ւ̏�������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);						// ���C�g�e���󂯂Ȃ�
	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{
		mtxPlayerWorld = g_aOrbit[nCntOrbit].playerWorld;

		if (g_aOrbit[nCntOrbit].bUse == true)
		{
			// �O��̈ʒu���l��
			g_aOrbit[nCntOrbit].mtxStartOld = g_aOrbit[nCntOrbit].mtxStart;
			g_aOrbit[nCntOrbit].mtxEndOld = g_aOrbit[nCntOrbit].mtxEnd;

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aOrbit[nCntOrbit].mtxStart);
			D3DXMatrixTranslation(&g_aOrbit[nCntOrbit].mtxStart, g_aOrbit[nCntOrbit].Start.x, g_aOrbit[nCntOrbit].Start.y, g_aOrbit[nCntOrbit].Start.z);	// �X�^�[�g
			D3DXMatrixMultiply(&g_aOrbit[nCntOrbit].mtxStart, &g_aOrbit[nCntOrbit].mtxStart, &mtxPlayerWorld);	// [�n�_*�v���C���[]�̃}�g���b�N�X�v�Z
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aOrbit[nCntOrbit].mtxStart);

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aOrbit[nCntOrbit].mtxEnd);
			D3DXMatrixTranslation(&g_aOrbit[nCntOrbit].mtxEnd, g_aOrbit[nCntOrbit].End.x, g_aOrbit[nCntOrbit].End.y, g_aOrbit[nCntOrbit].End.z);	// �G���h
			D3DXMatrixMultiply(&g_aOrbit[nCntOrbit].mtxEnd, &g_aOrbit[nCntOrbit].mtxEnd, &mtxPlayerWorld);		// [�I�_*�v���C���[]�̃}�g���b�N�X�v�Z
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aOrbit[nCntOrbit].mtxEnd);

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aOrbit[nCntOrbit].mtxWorld);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aOrbit[nCntOrbit].mtxWorld);


			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuff, 0, sizeof(VERTEX_3D));
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureOrbit[g_aOrbit[nCntOrbit].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntOrbit * 4, 2);


		}
	}
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);					// Z�o�b�t�@�ւ̏�������
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ���C�g�e���󂯂Ȃ�
	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


}

//==============================================================================================================================
// ���_���̍쐬
//==============================================================================================================================
void MakeVertexOrbit(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

		// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ORBIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff,
		NULL);

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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


	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuff->Unlock();

}
//==============================================================================================================================
// �O�Ղ̐ݒ�
//==============================================================================================================================
void SetOrbit(D3DXMATRIX Idxmtx, D3DXMATRIX IdxmtxOld, int nLength, D3DXVECTOR3 Start, D3DXVECTOR3 End, ORBITTYPE nType, PlayerMotionType nMotionType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	VERTEX_3D *pVtx;	// ���_���̃|�C���^
	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_ORBIT; nCnt++,pVtx+=4)
	{
		if (g_aOrbit[nCnt].bUse == false)
		{
			g_aOrbit[nCnt].playerWorld = Idxmtx;
			g_aOrbit[nCnt].playerWorldOld = IdxmtxOld;
			g_aOrbit[nCnt].Start = Start;
			g_aOrbit[nCnt].End = End;
			g_aOrbit[nCnt].InitStart = Start;
			g_aOrbit[nCnt].InitEnd = End;
			g_aOrbit[nCnt].nType = nType;
			g_aOrbit[nCnt].nMotionType = nMotionType;
			g_aOrbit[nCnt].nLength = nLength;
			g_aOrbit[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (g_aOrbit[nCnt].nLength == 0)
			{
				break;
			}
			D3DXMATRIX mtxPlayerWorld,mtxPlayerWorldOld;

			mtxPlayerWorld = g_aOrbit[nCnt].playerWorld;
			mtxPlayerWorldOld = g_aOrbit[nCnt].playerWorldOld;

			// ���ݒn
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aOrbit[nCnt].mtxStart);
			D3DXMatrixTranslation(&g_aOrbit[nCnt].mtxStart, g_aOrbit[nCnt].Start.x, g_aOrbit[nCnt].Start.y, g_aOrbit[nCnt].Start.z);	// �X�^�[�g
			D3DXMatrixMultiply(&g_aOrbit[nCnt].mtxStart, &g_aOrbit[nCnt].mtxStart, &mtxPlayerWorld);	// [�n�_*�v���C���[]�̃}�g���b�N�X�v�Z																											// ���[���h�}�g���b�N�X�̐ݒ�
		//	pDevice->SetTransform(D3DTS_WORLD, &g_aOrbit[nCnt].mtxStart);

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aOrbit[nCnt].mtxEnd);
			D3DXMatrixTranslation(&g_aOrbit[nCnt].mtxEnd, g_aOrbit[nCnt].End.x, g_aOrbit[nCnt].End.y, g_aOrbit[nCnt].End.z);	// �G���h
			D3DXMatrixMultiply(&g_aOrbit[nCnt].mtxEnd, &g_aOrbit[nCnt].mtxEnd, &mtxPlayerWorld);		// [�I�_*�v���C���[]�̃}�g���b�N�X�v�Z																												// ���[���h�}�g���b�N�X�̐ݒ�
	//		pDevice->SetTransform(D3DTS_WORLD, &g_aOrbit[nCnt].mtxEnd);

			// �ߋ�
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aOrbit[nCnt].mtxStartOld);
			D3DXMatrixTranslation(&g_aOrbit[nCnt].mtxStartOld, g_aOrbit[nCnt].Start.x, g_aOrbit[nCnt].Start.y, g_aOrbit[nCnt].Start.z);	// �X�^�[�g
			D3DXMatrixMultiply(&g_aOrbit[nCnt].mtxStartOld, &g_aOrbit[nCnt].mtxStartOld, &mtxPlayerWorldOld);	// [�n�_*�v���C���[]�̃}�g���b�N�X�v�Z																											// ���[���h�}�g���b�N�X�̐ݒ�
		//	pDevice->SetTransform(D3DTS_WORLD, &g_aOrbit[nCnt].mtxStartOld);

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aOrbit[nCnt].mtxEndOld);
			D3DXMatrixTranslation(&g_aOrbit[nCnt].mtxEndOld, g_aOrbit[nCnt].End.x, g_aOrbit[nCnt].End.y, g_aOrbit[nCnt].End.z);	// �G���h
			D3DXMatrixMultiply(&g_aOrbit[nCnt].mtxEndOld, &g_aOrbit[nCnt].mtxEndOld, &mtxPlayerWorldOld);		// [�I�_*�v���C���[]�̃}�g���b�N�X�v�Z																												// ���[���h�}�g���b�N�X�̐ݒ�
		//	pDevice->SetTransform(D3DTS_WORLD, &g_aOrbit[nCnt].mtxEndOld);

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aOrbit[nCnt].mtxStart._41, g_aOrbit[nCnt].mtxStart._42, g_aOrbit[nCnt].mtxStart._43);
			pVtx[1].pos = D3DXVECTOR3(g_aOrbit[nCnt].mtxEnd._41, g_aOrbit[nCnt].mtxEnd._42, g_aOrbit[nCnt].mtxEnd._43);
			pVtx[2].pos = D3DXVECTOR3(g_aOrbit[nCnt].mtxStartOld._41, g_aOrbit[nCnt].mtxStartOld._42, g_aOrbit[nCnt].mtxStartOld._43);
			pVtx[3].pos = D3DXVECTOR3(g_aOrbit[nCnt].mtxEndOld._41, g_aOrbit[nCnt].mtxEndOld._42, g_aOrbit[nCnt].mtxEndOld._43);

			// �e�N�X�`���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


			g_aOrbit[nCnt].bUse = true;
			break;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuff->Unlock();

}
