////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �^�C������ [time.cpp]
// Author : RyotaKinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "time.h"
#include "fade.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "flontpolygon.h"
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TIME_POS_X	(45)	// �^�C���̉���
#define TIME_POS_Y	(70)	// �^�C���̏c��
#define TIME_PLACE	(D3DXVECTOR3(SCREEN_WIDTH/2-10,80,0.0f))// �^�C���̏ꏊ
#define TIME_REN	(3)	// �^�C���̌���
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int						g_nTime;					// �^�C��
int						g_nFrameCount ;				// �b�����Z
int						g_nFrameTimeCount;			// �b�����Z�i�I������p�j
bool					g_bUse[TIME_REN];						// �g�p���Ă��邩�ǂ���
bool					g_bStop;						// �^�C�����~�܂��Ă��邩�ǂ���
//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nTime = GAME_TIME;
	g_nFrameCount = 0;
	g_nFrameTimeCount = GAME_TIME;
	g_bStop = false;
	g_bUse[0] = true;
	g_bUse[1] = true;
	g_bUse[2] = true;
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,		// �t�@�C���̖��O
								&g_pTextureTime);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexTime(pDevice);
}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitTime(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateTime(void)
{
	if (g_bStop == false&&GetCamera()[0].nState == CAMERASTATE_NONE)
	{
		g_nFrameCount++;

		if (g_nFrameCount % 60 == 0)
		{
			AddTime(-1);
		}
	}

	if (g_nTime >= 0)
	{
		g_bUse[0] = true;
		g_bUse[1] = false;
		g_bUse[2] = false;

	}
	if (g_nTime >= 10)
	{
		g_bUse[0] = true;
		g_bUse[1] = true;
		g_bUse[2] = false;

	}
	if (g_nTime >= 100)
	{
		g_bUse[0] = true;
		g_bUse[1] = true;
		g_bUse[2] = true;
	}

}

//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	// �|���S���̕`��
	for (int nCnt = 0; nCnt < TIME_REN; nCnt++)
	{
		if (g_bUse[nCnt] == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCnt,
				2);
		}
	}
}

//==============================================================================================================================
// ���_���̍쐬
//==============================================================================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D*pVtx;		// ���_���ւ̃|�C���^
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TIME_REN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < TIME_REN; nCnt++, pVtx += 4)
	{

		// ���_����ݒ�
		pVtx[0].pos = D3DXVECTOR3(float(TIME_POS_X * -nCnt - (TIME_POS_X / 2) + TIME_POS_X) + 10, -(TIME_POS_Y / 2), 0.0f) + TIME_PLACE;
		pVtx[1].pos = D3DXVECTOR3(float(TIME_POS_X * -nCnt + (TIME_POS_X / 2) + TIME_POS_X) + 10, -(TIME_POS_Y / 2), 0.0f) + TIME_PLACE;
		pVtx[2].pos = D3DXVECTOR3(float(TIME_POS_X * -nCnt - (TIME_POS_X / 2) + TIME_POS_X) + 10, (TIME_POS_Y / 2), 0.0f) + TIME_PLACE;
		pVtx[3].pos = D3DXVECTOR3(float(TIME_POS_X * -nCnt + (TIME_POS_X / 2) + TIME_POS_X) + 10, (TIME_POS_Y / 2), 0.0f) + TIME_PLACE;

		int nData = int(powf(10,float(nCnt)));

		pVtx[0].tex = D3DXVECTOR2((g_nTime % (10 * nData) / nData) * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_nTime % (10 * nData) / nData)* 0.1f + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((g_nTime % (10 * nData) / nData)* 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((g_nTime % (10 * nData) / nData)* 0.1f + 0.1f, 1.0f);

		// rhw�̐ݒ�
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].rhw = 1.0f;
		}
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//==============================================================================================================================
// �^�C���̉��Z
//==============================================================================================================================
void AddTime(int nTime)
{
	VERTEX_2D*pVtx;		// ���_���ւ̃|�C���^
	g_nTime += nTime;
	if (g_nTime <= 0)
	{
		g_nTime = 0;
		if (GetGameState() != GAMESTATE_END)
		{
			SetFlontPolygon(FLONT_TEXTYPE_TIMEUP, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 +100, 0.0f),
				SCREEN_WIDTH / 1.5f, 200, FLONTTYPE_NARRATION);
			PlaySound(SOUND_LABEL_TIMEUP000);
			SetGameState(GAMESTATE_END);
		}
	}
	else if (g_nTime <= 15)
	{
		PlaySound(SOUND_TIMELIMIT);
	}
	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	for (int nCnt = 0; nCnt < TIME_REN; nCnt++, pVtx += 4)
	{
		int nData = 1;

		for (int nCnt2 = nCnt; nCnt2 != 0; nCnt2--)
		{
			nData *= 10;
		}

		pVtx[0].tex = D3DXVECTOR2((g_nTime % (10 * nData) / nData) * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_nTime % (10 * nData) / nData)* 0.1f + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((g_nTime % (10 * nData) / nData)* 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((g_nTime % (10 * nData) / nData)* 0.1f + 0.1f, 1.0f);
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//==============================================================================================================================
// �^�C���̒�~
//==============================================================================================================================
void StopTime(void)
{
	g_bStop = true;
}