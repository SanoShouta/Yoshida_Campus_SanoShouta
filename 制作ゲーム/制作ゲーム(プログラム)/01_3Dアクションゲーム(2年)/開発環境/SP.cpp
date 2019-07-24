////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �K�E�Z���� [SP.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "SP.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "player.h"
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define MAX_SP_NUM	(12)
#define SP_WHIDTH		(20)
#define SP_HIGHT		(30)
#define ANIM			(0.3333f)
#define SP_Y			(90)
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void MakeVertexSp(LPDIRECT3DDEVICE9 pDevice);
//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
Sp g_aSp[MAX_SP_NUM];
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSP = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
SpData g_aSpData[SPTEX_MAX] =
{
	{ NULL,"data/TEXTURE/Attack_UI000.png" },
};
int g_nSetNum;		//���C�t�̃Z�b�g�J�E���^�[
int g_nCounter;
//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitSp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	Player *pPlayer = GetPlayer();

	//�\���̂̏�����

	for (int nCntSp = 0; nCntSp < MAX_SP_NUM; nCntSp++)
	{
		g_aSp[nCntSp].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
		g_aSp[nCntSp].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
		g_aSp[nCntSp].fWidth = 0;									// ��
		g_aSp[nCntSp].fHeight = 0;									// ����
		g_aSp[nCntSp].nPatternAnim = 0;								// �p�^�[��
		g_aSp[nCntSp].nCounterAnim = 0;								// �J�E���^�[
		g_aSp[nCntSp].nIdy = 0;										// �v���C���[�i���o�[
		g_aSp[nCntSp].nNumber = 0;									// ���i���o�[
		g_aSp[nCntSp].bUse = false;									// �g�p����Ă��邩�ǂ���
	}

	//�e�N�X�`���̓ǂݍ���
	for (int nCntTex = 0; nCntTex < SPTEX_MAX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			g_aSpData[nCntTex].pFileName,						// �t�@�C���̖��O
			&g_aSpData[nCntTex].pTexture);						// �e�N�X�`���ւ̃|�C���^
	}

	// ���_���̐ݒ�
	MakeVertexSp(pDevice);

	//�ϐ��̏�����
	int nNum = 0;
	g_nSetNum = 0;
	g_nCounter = 1;

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (pPlayer[nCnt].typeInfo != PLAYERTYPE_MAX)
		{
			nNum++;
		}
	}
	if (nNum == 2)
	{// 2�l�Ȃ�
		if (pPlayer[0].typeInfo != PLAYERTYPE_MAX)
		{// �I������Ă�����
		 // ���𒆐S�Ƃ��Ă̏������W�E��]�E�e�N�X�`���E���C�t�������E������Ȃ��E�������E�c
			SetSp(D3DXVECTOR3(155 + 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 0, 0);
			SetSp(D3DXVECTOR3(110 + 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 0, 1);
			SetSp(D3DXVECTOR3(65 + 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 0, 2);

		}
		if (pPlayer[1].typeInfo != PLAYERTYPE_MAX)
		{// �I������Ă�����
			SetSp(D3DXVECTOR3(455 - 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 1, 0);
			SetSp(D3DXVECTOR3(410 - 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 1, 1);
			SetSp(D3DXVECTOR3(365 - 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 1, 2);

		}
	}
	else
	{
		if (pPlayer[0].typeInfo != PLAYERTYPE_MAX)
		{// �I������Ă�����
			// ���𒆐S�Ƃ��Ă̏������W�E��]�E�e�N�X�`���E���C�t�������E������Ȃ��E�������E�c
			SetSp(D3DXVECTOR3(155 +15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 0, 0);
			SetSp(D3DXVECTOR3(110+15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 0, 1);
			SetSp(D3DXVECTOR3(65+15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 0, 2);

		}
		if (pPlayer[1].typeInfo != PLAYERTYPE_MAX)
		{// �I������Ă�����
			SetSp(D3DXVECTOR3(455-15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 1, 0);
			SetSp(D3DXVECTOR3(410 - 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 1, 1);
			SetSp(D3DXVECTOR3(365 - 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 1, 2);

		}
		if (pPlayer[2].typeInfo != PLAYERTYPE_MAX)
		{// �I������Ă�����
			SetSp(D3DXVECTOR3(755+70, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 2, 0);
			SetSp(D3DXVECTOR3(710 + 70, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 2, 1);
			SetSp(D3DXVECTOR3(665 + 70, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 2, 2);
		}
		if (pPlayer[3].typeInfo != PLAYERTYPE_MAX)
		{
			// �I������Ă�����
			SetSp(D3DXVECTOR3(1055+50, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 3, 0);
			SetSp(D3DXVECTOR3(1010+50, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 3, 1);
			SetSp(D3DXVECTOR3(965+50, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 3, 2);
		}
	}
}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitSp(void)
{
	// �e�N�X�`���̔j��
	for (int nCntSp = 0; nCntSp <SPTEX_MAX; nCntSp++)
	{
		if (g_aSpData[nCntSp].pTexture!= NULL)
		{
			g_aSpData[nCntSp].pTexture->Release();
			g_aSpData[nCntSp].pTexture = NULL;
		}
	}
	for (int nCntSp = 0; nCntSp < MAX_SP_NUM; nCntSp++)
	{
		for (int nCntSetSp = 0; nCntSetSp < MAX_SP; nCntSetSp++)
		{
			// ���_�o�b�t�@�̔j��
			if (g_pVtxBuffSP != NULL)
			{
				g_pVtxBuffSP->Release();
				g_pVtxBuffSP = NULL;
			}
		}
	}
}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateSp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();				// �f�o�C�X�̎擾
	//VERTEX_2D *pVtx;	// ���_���̃|�C���^
}

//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawSp(void)
{
	//�ϐ��錾
	int nCntDraw = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSP, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntSp = 0; nCntSp < MAX_SP_NUM; nCntSp++)
	{
		if (g_aSp[nCntSp].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aSpData[SPTEX_BG].pTexture);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,						//�v���~�e�B�u�̎��
				nCntSp * 4,									//�J�n���钸�_�̃C���f�b�N�X
				2);											//�v���~�e�B�u�̐�
		}
	}
}

//==============================================================================================================================
// ���_���̍쐬
//==============================================================================================================================
void MakeVertexSp(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;	// ���_���̃|�C���^

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SP_NUM * MAX_SP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSP,
		NULL);


	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSP->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSp = 0; nCntSp < MAX_SP_NUM; nCntSp++)
	{
		for (int nCntSetSp = 0; nCntSetSp < MAX_SP; nCntSetSp++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0, 0, 0);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0);
			pVtx[2].pos = D3DXVECTOR3(0, 0, 0);
			pVtx[3].pos = D3DXVECTOR3(0, 0, 0);

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0, 1.0f);

			pVtx += 4;		//���_�f�[�^�̃|�C���^���S���i�߂�
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSP->Unlock();
}

//==============================================================================================================================
// ���b�V���̐ݒ�
//==============================================================================================================================
void SetSp(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, int nIdy, int nNumber)
{
	//�ϐ��錾
	int nCounter = 1;
	VERTEX_2D *pVtx;	// ���_���̃|�C���^

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSP->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSp = 0; nCntSp < MAX_SP_NUM; nCntSp++)
	{
		if (g_aSp[nCntSp].bUse == false)
		{
			g_aSp[nCntSp].pos = pos;			// �ʒu
			g_aSp[nCntSp].rot = rot;			// ����
			g_aSp[nCntSp].fWidth = fWidth;		// ��
			g_aSp[nCntSp].fHeight = fHeight;	// ���s��
			g_aSp[nCntSp].nIdy = nIdy;			// �v���C���[�i���o�[
			g_aSp[nCntSp].nNumber = nNumber;	// ���i���o�[
			g_aSp[nCntSp].bUse = true;			// �g�p����Ă��邩�ǂ���

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aSp[nCntSp].pos.x - g_aSp[nCntSp].fWidth, g_aSp[nCntSp].pos.y - g_aSp[nCntSp].fHeight, g_aSp[nCntSp].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aSp[nCntSp].pos.x + g_aSp[nCntSp].fWidth, g_aSp[nCntSp].pos.y - g_aSp[nCntSp].fHeight, g_aSp[nCntSp].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aSp[nCntSp].pos.x - g_aSp[nCntSp].fWidth, g_aSp[nCntSp].pos.y + g_aSp[nCntSp].fHeight, g_aSp[nCntSp].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aSp[nCntSp].pos.x + g_aSp[nCntSp].fWidth, g_aSp[nCntSp].pos.y + g_aSp[nCntSp].fHeight, g_aSp[nCntSp].pos.z);
			break;
		}

		pVtx += 4;		//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSP->Unlock();
}
//==============================================================================================================================
// ���C�t�̊l��
//==============================================================================================================================
Sp *GetSp(void)
{
	return &g_aSp[0];
}
SpData *GetSpData(void)
{
	return &g_aSpData[0];
}
//==============================================================================================================================
// ���C�t�̏����ݒ�
//==============================================================================================================================
void SetPlayerSp(int nSp,int nIdy)
{
}
//==============================================================================================================================
// ���C�t�̕ύX
//==============================================================================================================================
void GetPlayerSp(int nSp, int nIdy)
{

}

//==============================================================================================================================
// �K�E�Z�̉񐔂����炷
//==============================================================================================================================
void DeleteSp(int nIdy)
{
	for (int nCntSp = 0; nCntSp < MAX_SP_NUM; nCntSp++)
	{
		if (g_aSp[nCntSp].nIdy == nIdy)
		{
			if (g_aSp[nCntSp].bUse == true)
			{
				if (g_aSp[nCntSp].nNumber == 2)
				{
					g_aSp[nCntSp].bUse = false;
					break;
				}
				else if (g_aSp[nCntSp].nNumber == 1)
				{
					g_aSp[nCntSp].bUse = false;
					break;
				}
				else
				{
					g_aSp[nCntSp].bUse = false;
					break;
				}
			}
		}
	}
}