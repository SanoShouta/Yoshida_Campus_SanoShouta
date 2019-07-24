//=============================================================================
//
// �I����ʂ̏��� [select.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "select.h"
#include "main.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"
#include "game.h"
#include "fade.h"
#include "flontpolygon.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_POLYGON		(3)		//�|���S���̍ő吔
#define MAX_TEX			(2)		//�e�N�X�`���̍ő吔
#define CHANGE			(30.0f)	//�|���S���̕ω���
#define MOVE			(3.0f)	//�ω���
#define OVER_MOVE		(10.0f)	//�Y���L�[�������Ȃ��������̃|���S���̈ړ���

//�ǂ񂿂��o�g���{�^��
#define BATTLE_WHIDTH		(520)											//�w�i�̕�
#define BATTLE_HEIGHT		(280)											//�w�i�̍���
#define BATTLE_POS_X		((SCREEN_WIDTH / 2) - 570)						//�w�i�̍���X���W
#define BATTLE_POS_Y		(150)											//�w�i�̍���Y���W

//�H�H�H�{�^��
#define QUESTION_WHIDTH		(250)											//�w�i�̕�
#define QUESTION_HEIGHT		(250)											//�w�i�̍���
#define QUESTION_POS_X		((QUESTION_WHIDTH / 2) - 20)					//�w�i�̍���X���W
#define QUESTION_POS_Y		(460)											//�w�i�̍���Y���W

//�^�C�g���{�^��
#define TITLE_WHIDTH		(250)											//�w�i�̕�
#define TITLE_HEIGHT		(250)											//�w�i�̍���
#define TITLE_POS_X			((TITLE_WHIDTH / 2) + 350)						//�w�i�̍���X���W
#define TITLE_POS_Y			(460)											//�w�i�̍���Y���W

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureSelect[MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelect = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int g_SelectMode;										//�I������Ă��郂�[�h
Select					g_Select[MAX_POLYGON];			//���ݒ�
int						g_SelectTime;					//���ԃJ�E���^�[
int						g_CommentID;					//�R�����g�|���S���̎擾

//=============================================================================
// ����������
//=============================================================================
void InitSelect(void)
{
	//�ϐ��錾
	int		nCntTex;
	int		nCntSelect;
	char	cTexName[MAX_TEX][48];		//�t�@�C�������i�[����

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	g_Select[0].Pos = D3DXVECTOR3(BATTLE_POS_X, BATTLE_POS_Y, 0.0f);
	g_Select[1].Pos = D3DXVECTOR3(QUESTION_POS_X, QUESTION_POS_Y, 0.0f);
	g_Select[2].Pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);

	g_Select[0].PosHold = D3DXVECTOR3(BATTLE_POS_X, BATTLE_POS_Y, 0.0f);
	g_Select[1].PosHold = D3DXVECTOR3(QUESTION_POS_X, QUESTION_POS_Y, 0.0f);
	g_Select[2].PosHold = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);

	g_Select[0].Size = D3DXVECTOR3(BATTLE_WHIDTH, BATTLE_HEIGHT, 0.0f);
	g_Select[1].Size = D3DXVECTOR3(QUESTION_WHIDTH, QUESTION_HEIGHT, 0.0f);
	g_Select[2].Size = D3DXVECTOR3(TITLE_WHIDTH, TITLE_HEIGHT, 0.0f);

	g_Select[0].nTex = 0;
	g_Select[1].nTex = 1;
	g_Select[2].nTex = 1;

	g_Select[0].state = BOTTUNSTATE_SELECT;
	g_Select[1].state = BOTTUNSTATE_NOMAL;
	g_Select[2].state = BOTTUNSTATE_NOMAL;

	for (nCntSelect = 0; nCntSelect < MAX_POLYGON; nCntSelect++)
	{
		g_Select[nCntSelect].fChange = 0;
	}

	g_SelectMode = SELECTSTATE_START;			//�I����Ԃ̐ݒ�
	g_SelectTime = 0;							//���ԃJ�E���^�[
	g_CommentID = 0;							//�R�����g�|���S����ID

	//�e�N�X�`���t�@�C�������i�[����
	wsprintf(&cTexName[0][0], "data\\TEXTURE\\title_logo.png");		//�ǂ񂿂��o�g���{�^��
	wsprintf(&cTexName[1][0], "data\\TEXTURE\\select00.png");		//�^�C�g���A�H�H�H�{�^��

	//�e�N�X�`���̓ǂݍ���
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			&cTexName[nCntTex][0],
			&g_pTextureSelect[nCntTex]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelect,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	//�R���e�j���[�{�^��-----------------------------------------------------------

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(BATTLE_POS_X, BATTLE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BATTLE_POS_X + BATTLE_WHIDTH, BATTLE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BATTLE_POS_X, BATTLE_POS_Y + BATTLE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BATTLE_POS_X + BATTLE_WHIDTH, BATTLE_POS_Y + BATTLE_HEIGHT, 0.0f);

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
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���g���C�{�^��-----------------------------------------------------------

	//���_���W�̐ݒ�
	pVtx[4].pos = D3DXVECTOR3(QUESTION_POS_X, QUESTION_POS_Y, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(QUESTION_POS_X + QUESTION_WHIDTH, QUESTION_POS_Y, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(QUESTION_POS_X, QUESTION_POS_Y + QUESTION_HEIGHT, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(QUESTION_POS_X + QUESTION_WHIDTH, QUESTION_POS_Y + QUESTION_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�N�C�b�g�{�^��-----------------------------------------------------------

	//���_���W�̐ݒ�
	pVtx[8].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(TITLE_POS_X + TITLE_WHIDTH, TITLE_POS_Y, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y + TITLE_HEIGHT, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(TITLE_POS_X + TITLE_WHIDTH, TITLE_POS_Y + TITLE_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.5f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();

	//�t�����g�|���S��
	SetFlontPolygon(11, D3DXVECTOR3(640.0f, 360.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, FLONTTYPE_NOMAL);
	SetFlontPolygon(FLONT_TEXTYPE_CHARACTOR, D3DXVECTOR3(1120.0f, 500.0f, 0.0f), 380.0f, 880.0f, FLONTTYPE_CYARACTOR);
	SetFlontPolygon(10, D3DXVECTOR3(640.0f, 360.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, FLONTTYPE_NOMAL);
	g_CommentID = SetFlontPolygon(FLONT_TEXTYPE_HUKIDASHI, D3DXVECTOR3(875.0f, 350.0f, 0.0f), 350.0f, 500.0f, FLONTTYPE_COMMENT);
	SetFlontPolygon(FLONT_TEXTYPE_CHOTIN, D3DXVECTOR3(640.0f, 50.0f, 0.0f), 1340.0f, 140.0f, FLONTTYPE_CHOTIN);
	SetFlontPolygon(FLONT_TEXTYPE_CHOTIN, D3DXVECTOR3(640.0f, 670.0f, 0.0f), 1340.0f, 140.0f, FLONTTYPE_CHOTIN);

	SetTexture(g_CommentID, COMMENTTYPE_BTTLE);
}

//=============================================================================
// �I������
//=============================================================================
void UninitSelect(void)
{
	//�ϐ��錾
	int nCntTex;

	//�e�N�X�`���̔j��
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (g_pTextureSelect[nCntTex] != NULL)
		{
			g_pTextureSelect[nCntTex]->Release();
			g_pTextureSelect[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSelect != NULL)
	{
		g_pVtxBuffSelect->Release();
		g_pVtxBuffSelect = NULL;
	}

	//�t�����g�|���S���̊J��
	ReleaseAllFlontPolygon();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSelect(void)
{
	//�ϐ��錾
	int nCntSelect;

	//�t�F�[�h�����擾����
	FADE fade;
	fade = GetFade();

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���͏���
	Input();

	//�I������
	switch (g_SelectMode)
	{
	case SELECTSTATE_START:

		//�{�^���̏�Ԑݒ�
		g_Select[0].state = BOTTUNSTATE_SELECT;
		g_Select[1].state = BOTTUNSTATE_NOMAL;
		g_Select[2].state = BOTTUNSTATE_NOMAL;

		//����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_SelectMode = SELECTSTATE_MAX;
			g_Select[0].state = BOTTUNSTATE_MAX;

			if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
			{
				PlaySound(SOUND_DECISION_1);
				//�t�F�[�h���[�h�ݒ�
				SetFade(MODE_CHARACTER);
			}
		}
		else
		{
			//�Q�[���p�b�h�̓��͏���
			for (int nIdy = 0; nIdy < MAX_GAMEPAD; nIdy++)
			{
				if (GetGamePadPress(nIdy, BUTTON_A) == true || GetGamePadPress(nIdy, BUTTON_B))
				{
					g_SelectMode = SELECTSTATE_MAX;
					g_Select[0].state = BOTTUNSTATE_MAX;

					if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
					{
						PlaySound(SOUND_DECISION_1);
						//�t�F�[�h���[�h�ݒ�
						SetFade(MODE_CHARACTER);
					}
				}
			}
		}

		//�R�����g�e�N�X�`���̐ݒ�
		SetTexture(g_CommentID, COMMENTTYPE_BTTLE);
		break;

	case SELECTSTATE_QUESTION:
		//�{�^���̏�Ԑݒ�
		g_Select[0].state = BOTTUNSTATE_NOMAL;
		g_Select[1].state = BOTTUNSTATE_SELECT;
		g_Select[2].state = BOTTUNSTATE_NOMAL;

		//����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_SelectMode = SELECTSTATE_MAX;
			g_Select[1].state = BOTTUNSTATE_MAX;

			if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
			{
				PlaySound(SOUND_DECISION_1);
				//�t�F�[�h���[�h�ݒ�
				SetFade(MODE_STAFF);
			}
		}
		else
		{
			//�Q�[���p�b�h�̓��͏���
			for (int nIdy = 0; nIdy < MAX_GAMEPAD; nIdy++)
			{
				if (GetGamePadPress(nIdy, BUTTON_A) == true || GetGamePadPress(nIdy, BUTTON_B))
				{
					g_SelectMode = SELECTSTATE_MAX;
					g_Select[1].state = BOTTUNSTATE_MAX;

					if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
					{
						PlaySound(SOUND_DECISION_1);
						//�t�F�[�h���[�h�ݒ�
						SetFade(MODE_STAFF);
					}
				}
			}
		}

		//�R�����g�e�N�X�`���̐ݒ�
		SetTexture(g_CommentID, COMMENTTYPE_QUESTION);
		break;

	case SELECTSTATE_TITLE:

		//�{�^���̏�Ԑݒ�
		g_Select[0].state = BOTTUNSTATE_NOMAL;
		g_Select[1].state = BOTTUNSTATE_NOMAL;
		g_Select[2].state = BOTTUNSTATE_SELECT;

		//����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_SelectMode = SELECTSTATE_MAX;
			g_Select[2].state = BOTTUNSTATE_MAX;

			if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
			{
				PlaySound(SOUND_DECISION_1);
				//�t�F�[�h���[�h�ݒ�
				SetFade(MODE_TITLE);
			}
		}
		else
		{
			//�Q�[���p�b�h�̓��͏���
			for (int nIdy = 0; nIdy < MAX_GAMEPAD; nIdy++)
			{
				if (GetGamePadPress(nIdy, BUTTON_A) == true|| GetGamePadPress(nIdy, BUTTON_B))
				{
					g_SelectMode = SELECTSTATE_MAX;
					g_Select[2].state = BOTTUNSTATE_MAX;

					if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
					{
						PlaySound(SOUND_DECISION_1);
						//�t�F�[�h���[�h�ݒ�
						SetFade(MODE_TITLE);
					}
				}
			}
		}

		//�R�����g�e�N�X�`���̐ݒ�
		SetTexture(g_CommentID, COMMENTTYPE_TITLE);
		break;
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSelect = 0; nCntSelect < MAX_POLYGON; nCntSelect++)
	{
		switch (g_Select[nCntSelect].state)
		{
		case BOTTUNSTATE_NOMAL:

			g_Select[nCntSelect].fChange -= MOVE;

			if (g_Select[nCntSelect].fChange < 0)
			{
				g_Select[nCntSelect].fChange = 0;
			}

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x - g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y - g_Select[nCntSelect].fChange, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x + g_Select[nCntSelect].Size.x + g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y - g_Select[nCntSelect].fChange, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x - g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y + g_Select[nCntSelect].Size.y + g_Select[nCntSelect].fChange, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x + g_Select[nCntSelect].Size.x + g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y + g_Select[nCntSelect].Size.y + g_Select[nCntSelect].fChange, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			break;

		case BOTTUNSTATE_SELECT:

			//�ω���
			g_Select[nCntSelect].fChange += MOVE;

			if (g_Select[nCntSelect].fChange > CHANGE)
			{
				g_Select[nCntSelect].fChange = CHANGE;
			}

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x - g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y - g_Select[nCntSelect].fChange, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x + g_Select[nCntSelect].Size.x + g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y - g_Select[nCntSelect].fChange, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x - g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y + g_Select[nCntSelect].Size.y + g_Select[nCntSelect].fChange, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x + g_Select[nCntSelect].Size.x + g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y + g_Select[nCntSelect].Size.y + g_Select[nCntSelect].fChange, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;

		case BOTTUNSTATE_NONE:
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;

		case BOTTUNSTATE_MAX:
			static float fSelect = 1.0f;
			if (fSelect == 1.0f)
			{
				fSelect = 0.0f;
			}
			else
			{
				fSelect = 1.0f;
			}
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(fSelect, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(fSelect, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(fSelect, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(fSelect, 0.0f, 0.0f, 1.0f);
			break;
		}

		//���W��߂�
		if (g_Select[nCntSelect].Pos.x < g_Select[nCntSelect].PosHold.x)
		{//�l�����Z����
			g_Select[nCntSelect].Pos.x += 2.0f;

			if (g_Select[nCntSelect].Pos.x > g_Select[nCntSelect].PosHold.x)
			{//�l�̏C��
				g_Select[nCntSelect].Pos.x = g_Select[nCntSelect].PosHold.x;
			}
		}
		if (g_Select[nCntSelect].Pos.x > g_Select[nCntSelect].PosHold.x)
		{//�l�����Z����
			g_Select[nCntSelect].Pos.x -= 2.0f;

			if (g_Select[nCntSelect].Pos.x < g_Select[nCntSelect].PosHold.x)
			{//�l�̏C��
				g_Select[nCntSelect].Pos.x = g_Select[nCntSelect].PosHold.x;
			}
		}
		if (g_Select[nCntSelect].Pos.y < g_Select[nCntSelect].PosHold.y)
		{//�l�����Z����
			g_Select[nCntSelect].Pos.y += 2.0f;

			if (g_Select[nCntSelect].Pos.y > g_Select[nCntSelect].PosHold.y)
			{//�l�̏C��
				g_Select[nCntSelect].Pos.y = g_Select[nCntSelect].PosHold.y;
			}
		}
		if (g_Select[nCntSelect].Pos.y > g_Select[nCntSelect].PosHold.y)
		{//�l�����Z����
			g_Select[nCntSelect].Pos.y -= 2.0f;

			if (g_Select[nCntSelect].Pos.y < g_Select[nCntSelect].PosHold.y)
			{//�l�̏C��
				g_Select[nCntSelect].Pos.y = g_Select[nCntSelect].PosHold.y;
			}
		}


		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSelect(void)
{
	//�ϐ��錾
	int nCntSelect;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSelect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntSelect = 0; nCntSelect < MAX_POLYGON; nCntSelect++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSelect[g_Select[nCntSelect].nTex]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
			nCntSelect * 4,			//�J�n���钸�_�̃C���f�b�N�X
			2);						//�v���~�e�B�u�̐�
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
Select * GetSelect(void)
{
	return &g_Select[0];
}

//=============================================================================
// ��Ԃ̐ݒ�
//=============================================================================
void SetSelectState(SELECTSTATE state)
{
	g_SelectMode = state;
}

//=============================================================================
// ���͏���
//=============================================================================
void Input(void)
{
	//�L�[�{�[�h�̓��͏���
	if (g_SelectMode == SELECTSTATE_START)
	{
		if (GetKeyboardTrigger(DIK_D) == true)
		{
			g_SelectMode = (g_SelectMode + (SELECTSTATE_MAX - 1)) % SELECTSTATE_MAX;
			PlaySound(SOUND_SELECTMOVE);
		}
		if (GetKeyboardTrigger(DIK_S) == true)
		{
			g_SelectMode = (g_SelectMode + 1) % SELECTSTATE_MAX;
			PlaySound(SOUND_SELECTMOVE);
		}
		if ((GetKeyboardTrigger(DIK_A) == true))
		{//���ɂ��炷
			g_Select[0].Pos.x -= OVER_MOVE;
		}
		if ((GetKeyboardTrigger(DIK_W) == true))
		{//��ɂ��炷
			g_Select[0].Pos.y -= OVER_MOVE;
		}
	}
	else if (g_SelectMode == SELECTSTATE_QUESTION)
	{
		if (GetKeyboardTrigger(DIK_W) == true)
		{
			g_SelectMode = (g_SelectMode + (SELECTSTATE_MAX - 1)) % SELECTSTATE_MAX;
			PlaySound(SOUND_SELECTMOVE);
		}
		if (GetKeyboardTrigger(DIK_D) == true)
		{
			g_SelectMode = (g_SelectMode + 1) % SELECTSTATE_MAX;
			PlaySound(SOUND_SELECTMOVE);
		}
		if (GetKeyboardTrigger(DIK_A) == true)
		{//���ɂ��炷
			g_Select[1].Pos.x -= OVER_MOVE;
		}
		if ((GetKeyboardTrigger(DIK_S) == true))
		{//���ɂ��炷
			g_Select[1].Pos.y += OVER_MOVE;
		}
	}
	else if (g_SelectMode == SELECTSTATE_TITLE)
	{
		if (GetKeyboardTrigger(DIK_A) == true)
		{
			g_SelectMode = (g_SelectMode + (SELECTSTATE_MAX - 1)) % SELECTSTATE_MAX;
			PlaySound(SOUND_SELECTMOVE);
		}
		if (GetKeyboardTrigger(DIK_W) == true)
		{
			g_SelectMode = (g_SelectMode + 1) % SELECTSTATE_MAX;
			PlaySound(SOUND_SELECTMOVE);
		}
		if (GetKeyboardTrigger(DIK_D) == true)
		{//�E�ɂ��炷
			g_Select[2].Pos.x += OVER_MOVE;
		}
		if ((GetKeyboardTrigger(DIK_S) == true))
		{//���ɂ��炷
			g_Select[2].Pos.y += OVER_MOVE;
		}
	}

	//�Q�[���p�b�h�̓��͏���
	for (int nIdy = 0; nIdy < MAX_GAMEPAD; nIdy++)
	{
		if (g_SelectMode == SELECTSTATE_START)
		{
			if (GetGamePadStickTrigger(nIdy, ANALOG_STICK_RIGHT) == true)
			{
				g_SelectMode = (g_SelectMode + (SELECTSTATE_MAX - 1)) % SELECTSTATE_MAX;
				PlaySound(SOUND_SELECTMOVE);
			}
			else if (GetGamePadStickTrigger(nIdy, ANALOG_STICK_DOWN) == true)
			{
				g_SelectMode = (g_SelectMode + 1) % SELECTSTATE_MAX;
				PlaySound(SOUND_SELECTMOVE);
			}
			else if (GetGamePadStickTrigger(nIdy, ANALOG_STICK_LEFT) == true)
			{//���ɂ��炷
				g_Select[0].Pos.x -= OVER_MOVE;
			}
			else if (GetGamePadStickTrigger(nIdy, ANALOG_STICK_UP) == true)
			{//��ɂ��炷
				g_Select[0].Pos.y -= OVER_MOVE;
			}
		}
		else if (g_SelectMode == SELECTSTATE_QUESTION)
		{
			if (GetGamePadStickTrigger(nIdy, ANALOG_STICK_UP) == true)
			{
				g_SelectMode = (g_SelectMode + (SELECTSTATE_MAX - 1)) % SELECTSTATE_MAX;
				PlaySound(SOUND_SELECTMOVE);
			}
			else if (GetGamePadStickTrigger(nIdy, ANALOG_STICK_RIGHT) == true)
			{
				g_SelectMode = (g_SelectMode + 1) % SELECTSTATE_MAX;
				PlaySound(SOUND_SELECTMOVE);
			}
			else if (GetGamePadStickTrigger(nIdy, ANALOG_STICK_LEFT) == true)
			{//���ɂ��炷
				g_Select[1].Pos.x -= OVER_MOVE;
			}
			else if (GetGamePadStickTrigger(nIdy, ANALOG_STICK_DOWN) == true)
			{//���ɂ��炷
				g_Select[1].Pos.y += OVER_MOVE;
			}
		}
		else if (g_SelectMode == SELECTSTATE_TITLE)
		{
			if (GetGamePadStickTrigger(nIdy, ANALOG_STICK_LEFT) == true)
			{
				g_SelectMode = (g_SelectMode + (SELECTSTATE_MAX - 1)) % SELECTSTATE_MAX;
				PlaySound(SOUND_SELECTMOVE);
			}
			else if (GetGamePadStickTrigger(nIdy, ANALOG_STICK_UP) == true)
			{
				g_SelectMode = (g_SelectMode + 1) % SELECTSTATE_MAX;
				PlaySound(SOUND_SELECTMOVE);
			}
			else if (GetGamePadStickTrigger(nIdy, ANALOG_STICK_RIGHT) == true)
			{//�E�ɂ��炷
				g_Select[2].Pos.x -= OVER_MOVE;
			}
			else if (GetGamePadStickTrigger(nIdy,ANALOG_STICK_DOWN) == true)
			{//���ɂ��炷
				g_Select[2].Pos.y += OVER_MOVE;
			}
		}
	}
}