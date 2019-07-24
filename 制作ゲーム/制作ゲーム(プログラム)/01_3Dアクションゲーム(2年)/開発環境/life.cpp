////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���C�t���� [life.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "life.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "player.h"
#include "flontpolygon.h"
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define MAX_LIFE_NUM	(16)
#define MAX_LIFE		(100)
#define LIFE_WHIDTH		(145)
#define ANIM			(0.3333f)

//UI�l
#define UI_Y			(73)
#define UI_WHITH		(250)
#define UI_HIGHT		(115)

//�A�C�R��
#define ICON_Y			(63)
#define ICON_WHITH		(100)
#define ICON_HIGHT		(85)
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);
//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
Life g_aLife[MAX_LIFE_NUM];
LifeData g_aLifeData[LIFETEX_MAX] =
{
	{ NULL,"data/TEXTURE/.jpg" },
	{ NULL,"data/TEXTURE/.jpg" },
	{ NULL,"data/TEXTURE/.jpg" },
	{ NULL,"data/TEXTURE/orbit003.jpg" },
};
int g_nLife[MAX_PLAYER];
bool g_bDown[MAX_PLAYER];
bool g_bUp[MAX_PLAYER];
//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	Player *pPlayer = GetPlayer();

	for (int nCntLife = 0; nCntLife < MAX_LIFE_NUM; nCntLife++)
	{
		g_aLife[nCntLife].pVtxBuff = NULL;										// ���_�o�b�t�@�ւ̃|�C���^
		g_aLife[nCntLife].pIdxBuff = NULL;										// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
		g_aLife[nCntLife].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);					// �ʒu
		g_aLife[nCntLife].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����
		g_aLife[nCntLife].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);				// �F
		g_aLife[nCntLife].fWidth = 0;											// ��
		g_aLife[nCntLife].fHeight = 0;											// ����
		g_aLife[nCntLife].nBlock_X = 0;											// �u���b�NX
		g_aLife[nCntLife].nBlock_Y = 0;											// �u���b�NY
		g_aLife[nCntLife].nPatternAnim = 0;										// �p�^�[��
		g_aLife[nCntLife].nCounterAnim = 0;										// �J�E���^�[
		g_aLife[nCntLife].nType = 0;											// ���
		g_aLife[nCntLife].bUse = false;											// �g�p����Ă��邩�ǂ���
		g_aLife[nCntLife].bUseDown = false;										// �_�E�������ǂ���
		g_aLife[nCntLife].bDownRed = false;									// �w�i�̐Ԃ����C�t�p
		g_aLife[nCntLife].nDownRedCounter = 0;								// �w�i�̐Ԃ����C�t�p����
		g_aLife[nCntLife].nDrawDown = 0;									// �|���S�����Z�p
	}
	for (int nCntTex = 0; nCntTex < LIFETEX_MAX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			g_aLifeData[nCntTex].pFileName,						// �t�@�C���̖��O
			&g_aLifeData[nCntTex].pTexture);						// �e�N�X�`���ւ̃|�C���^
	}
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		g_nLife[nCnt] = MAX_LIFE;
		g_bDown[nCnt] = false;
		g_bUp[nCnt] = false;
	}

	int nNum = 0;
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (pPlayer[nCnt].typeInfo != PLAYERTYPE_MAX)
		{
			nNum++;
		}
	}
	if (nNum == 2)
	{// 2�l�Ȃ�
		//////if (pPlayer[0].typeInfo != PLAYERTYPE_MAX)
		//////{// �I������Ă�����
		////// // ���𒆐S�Ƃ��Ă̏������W�E��]�E�e�N�X�`���E���C�t�������E������Ȃ��E�������E�c
		//////	SetFlontPolygon(5, D3DXVECTOR3(170, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
		//////	SetFlontPolygon(6, D3DXVECTOR3(250, ICON_Y, 0), ICON_WHITH, ICON_HIGHT, FLONTTYPE(FLONTTYPE_UI + (int)pPlayer[0].typeInfo + 1));
		//////	SetLife(D3DXVECTOR3(45, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH*3 + 5, 35, false);
		//////	SetLife(D3DXVECTOR3(50, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH*3, 30, false);
		//////	SetLife(D3DXVECTOR3(50, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH*3, 30, true);
		//////	SetLife(D3DXVECTOR3(50, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH*3, 30, true);
		//////}
		//////if (pPlayer[1].typeInfo != PLAYERTYPE_MAX)
		//////{// �I������Ă�����
		//////	SetFlontPolygon(5, D3DXVECTOR3(770, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
		//////	SetFlontPolygon(6, D3DXVECTOR3(860, ICON_Y, 0), ICON_WHITH, ICON_HIGHT, FLONTTYPE(FLONTTYPE_UI + (int)pPlayer[1].typeInfo + 1));
		//////	SetLife(D3DXVECTOR3(675, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH*3 + 5, 35, false);
		//////	SetLife(D3DXVECTOR3(680, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH*3, 30, false);
		//////	SetLife(D3DXVECTOR3(680, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH*3, 30, true);
		//////	SetLife(D3DXVECTOR3(680, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH*3, 30, true);
		//////}
		if (pPlayer[0].typeInfo != PLAYERTYPE_MAX)
		{// �I������Ă�����
		 // ���𒆐S�Ƃ��Ă̏������W�E��]�E�e�N�X�`���E���C�t�������E������Ȃ��E�������E�c
			SetFlontPolygon(5, D3DXVECTOR3(170, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
			SetFlontPolygon(6, D3DXVECTOR3(245, ICON_Y, 0), ICON_WHITH, ICON_HIGHT, (FLONTTYPE)(FLONTTYPE_UI + (int)pPlayer[0].typeInfo + 1));
			SetLife(D3DXVECTOR3(52.5f, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH + 5, 35, false);
			SetLife(D3DXVECTOR3(55, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH, 30, false);
			SetLife(D3DXVECTOR3(55, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH, 30, true);
			SetLife(D3DXVECTOR3(55, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH, 30, true);
		}
		if (pPlayer[1].typeInfo != PLAYERTYPE_MAX)
		{// �I������Ă�����
			SetFlontPolygon(5, D3DXVECTOR3(440, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
			SetFlontPolygon(6, D3DXVECTOR3(515, ICON_Y, 0), ICON_WHITH, ICON_HIGHT, (FLONTTYPE)(FLONTTYPE_UI + (int)pPlayer[1].typeInfo + 1));
			SetLife(D3DXVECTOR3(322.5f, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH + 5, 35, false);
			SetLife(D3DXVECTOR3(325, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH, 30, false);
			SetLife(D3DXVECTOR3(325, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH, 30, true);
			SetLife(D3DXVECTOR3(325, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH, 30, true);
		}
	}
	else
	{
		if (pPlayer[0].typeInfo != PLAYERTYPE_MAX)
		{// �I������Ă�����
			// ���𒆐S�Ƃ��Ă̏������W�E��]�E�e�N�X�`���E���C�t�������E������Ȃ��E�������E�c
			SetFlontPolygon(5, D3DXVECTOR3(170, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
			SetFlontPolygon(6, D3DXVECTOR3(245, ICON_Y, 0), ICON_WHITH, ICON_HIGHT, (FLONTTYPE)(FLONTTYPE_UI + (int)pPlayer[0].typeInfo + 1));
			SetLife(D3DXVECTOR3(52.5f, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH + 5, 35, false);
			SetLife(D3DXVECTOR3(55, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH, 30, false);
			SetLife(D3DXVECTOR3(55, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH, 30, true);
			SetLife(D3DXVECTOR3(55, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH, 30, true);
		}
		if (pPlayer[1].typeInfo != PLAYERTYPE_MAX)
		{// �I������Ă�����
			SetFlontPolygon(5, D3DXVECTOR3(440, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
			SetFlontPolygon(6, D3DXVECTOR3(515, ICON_Y, 0), ICON_WHITH, ICON_HIGHT, (FLONTTYPE)(FLONTTYPE_UI + (int)pPlayer[1].typeInfo + 1));
			SetLife(D3DXVECTOR3(322.5f, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH + 5, 35, false);
			SetLife(D3DXVECTOR3(325, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH, 30, false);
			SetLife(D3DXVECTOR3(325, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH, 30, true);
			SetLife(D3DXVECTOR3(325, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH, 30, true);
		}
		if (pPlayer[2].typeInfo != PLAYERTYPE_MAX)
		{// �I������Ă�����
			SetFlontPolygon(5, D3DXVECTOR3(830, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
			SetFlontPolygon(6, D3DXVECTOR3(905, ICON_Y, 0), ICON_WHITH, ICON_HIGHT, (FLONTTYPE)(FLONTTYPE_UI + (int)pPlayer[2].typeInfo + 1));
			SetLife(D3DXVECTOR3(712.5f, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH + 5, 35, false);
			SetLife(D3DXVECTOR3(715, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH, 30, false);
			SetLife(D3DXVECTOR3(715, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH, 30, true);
			SetLife(D3DXVECTOR3(715, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH, 30, true);
		}
		if (pPlayer[3].typeInfo != PLAYERTYPE_MAX)
		{
			// �I������Ă�����
			SetFlontPolygon(5, D3DXVECTOR3(1100, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
			SetFlontPolygon(6, D3DXVECTOR3(1175, ICON_Y, 0), ICON_WHITH, ICON_HIGHT,(FLONTTYPE)(FLONTTYPE_UI + (int)pPlayer[3].typeInfo + 1));
			SetLife(D3DXVECTOR3(982.5f, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH + 5, 35, false);
			SetLife(D3DXVECTOR3(985, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH, 30, false);
			SetLife(D3DXVECTOR3(985, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH, 30, true);
			SetLife(D3DXVECTOR3(985, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH, 30, true);
		}
	}
}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitLife(void)
{
	// �e�N�X�`���̔j��
	for (int nCntLife = 0; nCntLife <LIFETEX_MAX; nCntLife++)
	{
		if (g_aLifeData[nCntLife].pTexture!= NULL)
		{
			g_aLifeData[nCntLife].pTexture->Release();
			g_aLifeData[nCntLife].pTexture = NULL;
		}
	}
	for (int nCntLife = 0; nCntLife < MAX_LIFE_NUM; nCntLife++)
	{
		// ���_�o�b�t�@�̔j��
		if (g_aLife[nCntLife].pVtxBuff != NULL)
		{
			g_aLife[nCntLife].pVtxBuff->Release();
			g_aLife[nCntLife].pVtxBuff = NULL;
		}
		// �C���f�b�N�X�o�b�t�@�o�b�t�@�̔j��
		if (g_aLife[nCntLife].pIdxBuff != NULL)
		{
			g_aLife[nCntLife].pIdxBuff->Release();
			g_aLife[nCntLife].pIdxBuff = NULL;
		}
	}
}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();				// �f�o�C�X�̎擾
	VERTEX_2D *pVtx;	// ���_���̃|�C���^

	int nCnt = 0;
	for (int nCntL = 0; nCntL < MAX_LIFE_NUM; nCntL++)
	{
		nCnt = nCntL / LIFETEX_MAX;
		if (g_aLife[nCntL].bUse == true)
		{
			// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
			g_aLife[nCntL].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			if (g_aLife[nCntL].bUseDown == true)
			{
				if (g_aLife[nCntL].nType == LIFETEX_GAGE)
				{
					if (g_bDown[nCnt])
					{// ������
						g_aLife[nCntL].nDrawDown++;
						if (g_aLife[nCntL].nDrawDown >= 100 - ((float)g_nLife[nCnt] / MAX_LIFE) * 100)
						{// 100%�� X%�������Ƃ��܂Ō��炷
							g_bDown[nCnt] = false;
							g_aLife[nCntL - 1].bDownRed = true;		// ���C�t�̑O���ԃ��C�t�Ȃ�-1
							g_aLife[nCntL - 1].nDownRedCounter = 60; // �ԃ��C�t�����Ԋu�ۊ�
							if (g_nLife[nCnt] <= 0)
							{// ���񂾂�ۊǂȂ�
								g_aLife[nCntL - 1].nDownRedCounter = 0;
							}
						}
					}
				}
				if (g_aLife[nCntL].nType == LIFETEX_GAGERED)
				{
					if (g_aLife[nCntL].bDownRed)
					{
						g_aLife[nCntL].nDownRedCounter--;
						if (g_aLife[nCntL].nDownRedCounter <= 0)
						{
							g_aLife[nCntL].nDownRedCounter = 0;
							g_aLife[nCntL].nDrawDown++;
							if (g_aLife[nCntL].nDrawDown >= 100 - ((float)g_nLife[nCnt] / MAX_LIFE) * 100)
							{// 100%�� X%�������Ƃ��܂Ō��炷
								g_aLife[nCntL].bDownRed = false;
							}
						}
					}
				}
				if (g_bUp[nCnt])
				{
					if (g_aLife[nCntL].nType == LIFETEX_GAGE)
					{
						g_aLife[nCntL].nDrawDown--;
						if (g_aLife[nCntL].nDrawDown <= 100 - ((float)g_nLife[nCnt] / MAX_LIFE) * 100)
						{// 100%�� X%�������Ƃ��܂ő��₷
							g_bUp[nCnt] = false;
						}
					}
					if (g_aLife[nCntL].nType == LIFETEX_GAGERED)
					{
						g_aLife[nCntL].nDrawDown--;
						if (g_aLife[nCntL].nDrawDown <= 100 - ((float)g_nLife[nCnt] / MAX_LIFE) * 100)
						{// 100%�� X%�������Ƃ��܂ő��₷
						}
					}
				}

			}
		}
	}
}

//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	// ���C���[�t���[��
//	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	for (int nCntLife = 0; nCntLife < MAX_LIFE_NUM; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aLife[nCntLife].mtxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aLife[nCntLife].rot.y, g_aLife[nCntLife].rot.x, g_aLife[nCntLife].rot.z);
			D3DXMatrixMultiply(&g_aLife[nCntLife].mtxWorld, &g_aLife[nCntLife].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aLife[nCntLife].pos.x, g_aLife[nCntLife].pos.y, g_aLife[nCntLife].pos.z);
			D3DXMatrixMultiply(&g_aLife[nCntLife].mtxWorld, &g_aLife[nCntLife].mtxWorld, &mtxTrans);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_aLife[nCntLife].pVtxBuff, 0, sizeof(VERTEX_2D));
			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_aLife[nCntLife].pIdxBuff);
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aLifeData[g_aLife[nCntLife].nType].pTexture);
			if (g_aLife[nCntLife].bUseDown == true)
			{
				// �|���S���̕`��
				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aLife[nCntLife].nNumIndex, 0, g_aLife[nCntLife].nNumPolygon - g_aLife[nCntLife].nDrawDown * 2);
			}
			else
			{
				// �|���S���̕`��
				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aLife[nCntLife].nNumIndex, 0, g_aLife[nCntLife].nNumPolygon );

			}
		}
	}

}

//==============================================================================================================================
// ���_���̍쐬
//==============================================================================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;	// ���_���̃|�C���^
	for (int nCntLife = 0; nCntLife < MAX_LIFE_NUM; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == false)
		{
			// ���_���̍쐬
			pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * g_aLife[nCntLife].nNumVertex,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_2D,
				D3DPOOL_MANAGED,
				&g_aLife[nCntLife].pVtxBuff,
				NULL);


			// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾

			g_aLife[nCntLife].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			// ���_���W�̐ݒ�

			for (int nCnt = 0; nCnt < g_aLife[nCntLife].nNumVertex; nCnt++)
			{// "X"�͌��ɖ߂����灓�@"Z"�͌����܂��͑�����������̂Ł�
				pVtx[nCnt].pos = D3DXVECTOR3( (g_aLife[nCntLife].fWidth / g_aLife[nCntLife].nBlock_X)*(nCnt % (g_aLife[nCntLife].nBlock_X + 1)),
					+(g_aLife[nCntLife].fHeight)*(nCnt / (g_aLife[nCntLife].nBlock_X + 1)), 0.0f) + g_aLife[nCntLife].pos;

			}
			// rhw�̐ݒ�
			for (int nCnt = 0; nCnt < g_aLife[nCntLife].nNumVertex; nCnt++)
			{
				pVtx[nCnt].rhw = 1.0f;
			}
			// ���_�J���[�̐ݒ�
			for (int nCnt = 0; nCnt < g_aLife[nCntLife].nNumVertex; nCnt++)
			{
				pVtx[nCnt].col = g_aLife[nCntLife].col;
			}

			// �S�̃e�N�X�`��
			for (int nCntV = 0; nCntV < g_aLife[nCntLife].nBlock_Y + 1; nCntV++)
			{// �e�N�X�`���̐ݒ�
				for (int nCntH = 0; nCntH < g_aLife[nCntLife].nBlock_X + 1; nCntH++)
				{// "X"�͌��ɖ߂����灓�@"Z"�͌����܂��͑�����������̂Ł�
				 // �e�N�X�`���̐ݒ�
					pVtx[nCntH + (g_aLife[nCntLife].nBlock_X + 1)*nCntV].tex = D3DXVECTOR2(float(nCntH * 100 / g_aLife[nCntLife].nBlock_X) / 100.0f , float(nCntV * 100 / g_aLife[nCntLife].nBlock_Y) / 100.0f);
				}
			}
			// ���_�o�b�t�@���A�����b�N����
			g_aLife[nCntLife].pVtxBuff->Unlock();
			WORD *pIdx;	// �C���f�b�N�X�f�[�^�ւ̃|�C���^

				// �C���f�b�N�X�o�b�t�@�̍쐬
			pDevice->CreateIndexBuffer(sizeof(WORD)*g_aLife[nCntLife].nNumIndex,
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,
				D3DPOOL_MANAGED,
				&g_aLife[nCntLife].pIdxBuff,
				NULL);

			// �C���f�b�N�X�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
			g_aLife[nCntLife].pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);


			// �C���f�b�N�X�̐ݒ�
			for (int nCntIdx = 0, nCntPos = 0; nCntIdx < g_aLife[nCntLife].nNumIndex; nCntIdx += 2)
			{
				if ((nCntIdx / 2) % (g_aLife[nCntLife].nBlock_X + 2) == g_aLife[nCntLife].nBlock_X + 1)
				{
					pIdx[nCntIdx] = nCntPos - 1;
					pIdx[nCntIdx + 1] = nCntPos + g_aLife[nCntLife].nBlock_X + 1;
				}
				else
				{
					pIdx[nCntIdx] = nCntPos + g_aLife[nCntLife].nBlock_X + 1;
					pIdx[nCntIdx + 1] = nCntPos;

					nCntPos++;
				}
			}
			// ���_�o�b�t�@���A�����b�N����
			g_aLife[nCntLife].pIdxBuff->Unlock();
			break;
		}
	}
}
//==============================================================================================================================
// ���b�V���̐ݒ�
//==============================================================================================================================
void SetLife(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXCOLOR col, int nType, int nBlock_X, int nBlock_Y, float fWidth, float fHeight,bool bUseDown)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntLife = 0; nCntLife < MAX_LIFE_NUM; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == false)
		{
			g_aLife[nCntLife].pos = pos;				// �ʒu
			g_aLife[nCntLife].rot = rot;				// ����
			g_aLife[nCntLife].col = col;				// �F
			g_aLife[nCntLife].fWidth = fWidth;			// ��
			g_aLife[nCntLife].fHeight = fHeight;		// ���s��
			g_aLife[nCntLife].nBlock_X = nBlock_X;		// �u���b�NX
			g_aLife[nCntLife].nBlock_Y = nBlock_Y;		// �u���b�NZ
			g_aLife[nCntLife].nType = nType;			// ���
			g_aLife[nCntLife].bUseDown = bUseDown;
			g_aLife[nCntLife].nNumVertex = (g_aLife[nCntLife].nBlock_X + 1)*(g_aLife[nCntLife].nBlock_Y + 1);											// ���_��
			g_aLife[nCntLife].nNumIndex = 2 * (g_aLife[nCntLife].nBlock_X*g_aLife[nCntLife].nBlock_Y) + 4 * (g_aLife[nCntLife].nBlock_Y - 1) + 2;	// �C���f�b�N�X��										//
			g_aLife[nCntLife].nNumPolygon = 2 * (g_aLife[nCntLife].nBlock_X*g_aLife[nCntLife].nBlock_Y) + 4 * (g_aLife[nCntLife].nBlock_Y - 1);	// �|���S����

			MakeVertexLife(pDevice);
			g_aLife[nCntLife].bUse = true;										// �g�p����Ă��邩�ǂ���
			break;
		}
	}
}
//==============================================================================================================================
// ���C�t�̊l��
//==============================================================================================================================
Life *GetLife(void)
{
	return &g_aLife[0];
}
LifeData *GetLifeData(void)
{
	return &g_aLifeData[0];
}
//==============================================================================================================================
// ���C�t�̏����ݒ�
//==============================================================================================================================
void SetPlayerLife(int nLife,int nIdy)
{
	g_nLife[nIdy] = nLife;
}
//==============================================================================================================================
// ���C�t�̕ύX
//==============================================================================================================================
void GetPlayerLife(int nLife, int nIdy)
{
	if (g_nLife[nIdy] < nLife)
	{
		g_nLife[nIdy] = nLife;
		g_bUp[nIdy] = true;
	}
	else if (g_nLife[nIdy] != nLife)
	{
		g_nLife[nIdy] = nLife;
		g_bDown[nIdy] = true;
	}

}