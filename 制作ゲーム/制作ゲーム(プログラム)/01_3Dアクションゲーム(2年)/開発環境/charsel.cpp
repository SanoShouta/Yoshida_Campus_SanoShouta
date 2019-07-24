//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �L�����N�^�[�Z���N�g���� [charsel.cpp]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "charsel.h"
#include "input.h"
#include "cursor.h"
#include "marker.h"
#include "camera.h"
#include "player.h"
#include "shadow.h"
#include "line.h"
#include "orbit.h"
#include "fade.h"
#include "flontpolygon.h"
#include "gamepad.h"
#include "sound.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �\���̒�`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct
{
	char *pFileName;
	D3DXVECTOR3	pos;
	float fWidth;
	float fHeight;
	CHARSELTYPE type;
}CharselTexture;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �v���g�^�C�v�錾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
VERTEX_2D				g_aVertexCharsel[MAX_CHARSELTOP];
LPDIRECT3DTEXTURE9		g_pTextureCharsel[CHARSELTYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCharsel = NULL;
Charsel					g_aCharsel[CHARSELTYPE_MAX];
bool					g_bReady;							// �퓬�����������������ǂ���

CharselTexture g_aCharselTexInfo[CHARSELTYPE_MAX] =
{
	{ "data/TEXTURE/CharactorSelectBG.jpg", D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, 0.0f), SCREEN_WIDTH, SCREEN_WIDTH, CHARSELTYPE_BG },	// �w�i
	{ "data/TEXTURE/Chotin000.png", D3DXVECTOR3(SCREEN_WIDTH / 2,50.0f, 0.0f), SCREEN_WIDTH, CHOTIN_HEIGHT, CHARSELTYPE_CHOUTINUP },					// �񓔁i��j
	{ "data/TEXTURE/Chotin000.png", D3DXVECTOR3(SCREEN_WIDTH / 2, 660.0f, 0.0f), SCREEN_WIDTH, CHOTIN_HEIGHT, CHARSELTYPE_CHOUTINDOWN },					// �񓔁i���j
	{ "data/TEXTURE/CharactorBG000.jpg", D3DXVECTOR3(180.0f, 180.0f, 0.0f), PICKUP_WIDTH, PICKUP_HEIGHT, CHARSELTYPE_PLAYER1 },						// �v���C���[1�̔w�i
	{ "data/TEXTURE/CharactorBG001.jpg", D3DXVECTOR3(1100.0f, 180.0f, 0.0f), PICKUP_WIDTH, PICKUP_HEIGHT, CHARSELTYPE_PLAYER2 },						// �v���C���[2�̔w�i
	{ "data/TEXTURE/CharactorBG002.jpg", D3DXVECTOR3(180.0f, 540.0f, 0.0f), PICKUP_WIDTH, PICKUP_HEIGHT, CHARSELTYPE_PLAYER3 },						// �v���C���[3�̔w�i
	{ "data/TEXTURE/CharactorBG003.jpg", D3DXVECTOR3(1100.0f, 540.0f, 0.0f), PICKUP_WIDTH, PICKUP_HEIGHT, CHARSELTYPE_PLAYER4 },						// �v���C���[4�̔w�i
	{ "data/TEXTURE/CharactorIcon000.png", D3DXVECTOR3(570.0f, 160.0f, 0.0f), CHARWINDOW_WIDTH, CHARWINDOW_HEIGHT, CHARSELTYPE_MATURI },			// �܂�i���̎q�j
	{ "data/TEXTURE/CharactorIcon001.png", D3DXVECTOR3(710.0f, 160.0f, 0.0f), CHARWINDOW_WIDTH, CHARWINDOW_HEIGHT, CHARSELTYPE_AMANO },				// ���܂́i�V��j
	{ "data/TEXTURE/CharactorIcon002.png", D3DXVECTOR3(570.0f, 300.0f, 0.0f), CHARWINDOW_WIDTH, CHARWINDOW_HEIGHT, CHARSELTYPE_GOJOU },				// ���i�͓��j
	{ "data/TEXTURE/CharactorIcon003.png", D3DXVECTOR3(710.0f, 300.0f, 0.0f), CHARWINDOW_WIDTH, CHARWINDOW_HEIGHT, CHARSELTYPE_MOMIJI },			// �g�t�i���ˁj
	{ "data/TEXTURE/CharactorIcon004.png", D3DXVECTOR3(570.0f, 440.0f, 0.0f), CHARWINDOW_WIDTH, CHARWINDOW_HEIGHT, CHARSELTYPE_DONROID },			// �h�����C�h�i���{�b�g�j
	{ "data/TEXTURE/CharactorIcon005.png", D3DXVECTOR3(710.0f, 440.0f, 0.0f), CHARWINDOW_WIDTH, CHARWINDOW_HEIGHT, CHARSELTYPE_RANDOM },			// �����_��
	{ "data/TEXTURE/BackTitle000.png", D3DXVECTOR3(640.0f, 620.0f, 0.0f), EXIT_WIDTH, EXIT_HEIGHT, CHARSELTYPE_EXIT },								// �߂�

};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �L�����N�^�[�Z���N�g��ʂ̏���������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitCharsel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���̓ǂݍ���
	for (int nCntCharselTex = 0; nCntCharselTex < CHARSELTYPE_MAX; nCntCharselTex++)
	{
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			g_aCharselTexInfo[nCntCharselTex].pFileName, 	// �t�@�C���̖��O
			&g_pTextureCharsel[nCntCharselTex]);			// �e�N�X�`���ւ̃|�C���^
	}
	for (int nCntCharselTex = 0; nCntCharselTex < CHARSELTYPE_MAX; nCntCharselTex++)
	{
		g_aCharsel[nCntCharselTex].pos = g_aCharselTexInfo[nCntCharselTex].pos;				// �ʒu
		g_aCharsel[nCntCharselTex].fWidth = g_aCharselTexInfo[nCntCharselTex].fWidth;		// ��
		g_aCharsel[nCntCharselTex].fHeight = g_aCharselTexInfo[nCntCharselTex].fHeight;		// ����
		g_aCharsel[nCntCharselTex].type = g_aCharselTexInfo[nCntCharselTex].type;			// ���
		g_aCharsel[nCntCharselTex].bUse = false;											// �g���Ă��邩�ǂ���
		g_aCharsel[nCntCharselTex].moveTex = 0.0f;											// �e�N�X�`���̈ړ���
	}
	g_bReady = false;
	MakeVertexCharsel(pDevice);
	// �J�����̏���������
	InitCamera();
	// �J�[�\���̏���������
	InitCursor();
	// �}�[�J�[�̏���������
	InitMarker();
	InitShadow();
	InitLine();
	InitOrbit();
	// �v���C���[�̏���������
	InitPlayer();
	Player *pPlayer = GetPlayer();
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		pPlayer[nCnt].typeInfo = PLAYERTYPE_MAX;
	}
	for (int nCntCharselTex = 0; nCntCharselTex < CHARSELTYPE_MAX; nCntCharselTex++)
	{
		SetCharsel(g_aCharsel[nCntCharselTex].pos, g_aCharsel[nCntCharselTex].fWidth, g_aCharsel[nCntCharselTex].fHeight, g_aCharsel[nCntCharselTex].type);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitCharsel(void)
{

	for (int nCntTex = 0; nCntTex < CHARSELTYPE_MAX; nCntTex++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureCharsel[nCntTex] != NULL)
		{
			g_pTextureCharsel[nCntTex]->Release();
			g_pTextureCharsel[nCntTex] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffCharsel != NULL)
	{
		g_pVtxBuffCharsel->Release();
		g_pVtxBuffCharsel = NULL;
	}
	// �J�[�\���̏I������
	UninitCursor();
	// �}�[�J�[�̏I������
	UninitMarker();
	// �J�����̏I������
	UninitCamera();

	//�t�����g�|���S���̊J��
	ReleaseAllFlontPolygon();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateCharsel(void)
{
	VERTEX_2D*pVtx;					// ���_���ւ̃|�C���^

	// ���_l�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCharsel->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < CHARSELTYPE_MAX; nCntTex++, pVtx += 4)
	{
		if (g_aCharsel[nCntTex].type == CHARSELTYPE_BG)
		{
			g_aCharsel[nCntTex].moveTex += 0.001f;				// �w�i�̈ړ���

		}
		else if (g_aCharsel[nCntTex].type == CHARSELTYPE_CHOUTINUP)
		{
			g_aCharsel[nCntTex].moveTex += 0.002f;		// ��񓔂̈ړ���
		}
		else if (g_aCharsel[nCntTex].type == CHARSELTYPE_CHOUTINDOWN)
		{
			g_aCharsel[nCntTex].moveTex += 0.002f;		// ���񓔂̈ړ���

		}
		if (g_aCharsel[nCntTex].moveTex >= 1.0f)
		{
			g_aCharsel[nCntTex].moveTex = 0;
		}
		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f + g_aCharsel[nCntTex].moveTex, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f + g_aCharsel[nCntTex].moveTex, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + g_aCharsel[nCntTex].moveTex, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f + g_aCharsel[nCntTex].moveTex, 1.0f);
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffCharsel->Unlock();
	// �J�����̍X�V����
	UpdateCamera();

	// �J�[�\���̍X�V����
	UpdateCursor();
	// �}�[�J�[�̍X�V����
	UpdateMarker();
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		GetPlayer()[nCnt].nMotionType = PLAYER_MOTION_TYPE_NEUTRAL;
	}
	// �v���C���[�̍X�V����
	UpdatePlayer(0);
	UpdatePlayer(1);
	UpdatePlayer(2);
	UpdatePlayer(3);

	int nTotalMarker = GetNumMarker();			// �u�����}�[�J�[�̑���
	int nTotalGamePad = GetGamePadNum();		// �h�����Ă���Q�[���p�b�h�̐�

	if (nTotalGamePad == nTotalMarker)
	{// �Q�[���p�b�h�̐��ƃL������I���������������Ƃ�
		if (!g_bReady)
		{// ��������
			PlaySound(SOUND_CHARACTOR_READY);
		}
		g_bReady = true;
	}
	else
	{// �Q�[���p�b�h�̐��ƃL������I���������������Ƃ�
		g_bReady = false;
	}
	if (g_bReady == true)
	{// �I�����������Ă��鎞

		SetFlontPolygon(FLONTTYPE_READY, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH , SCREEN_HEIGHT / 5, FLONTTYPE_READY);
		if (GetKeyboardTrigger(DIK_9))
		{
			if (GetFade() != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
			{
				PlaySound(SOUND_DECISION);
				PlaySound(SOUND_KANSEI_2);
				//�t�F�[�h���[�h�ݒ�
				SetFade(MODE_GAME);
			}
		}
		for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
		{
			if (GetGamePadTrigger(nCnt, BUTTON_START) )
			{
				if (GetFade() != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
				{
					PlaySound(SOUND_DECISION);
					PlaySound(SOUND_KANSEI_2);

					//�t�F�[�h���[�h�ݒ�
					SetFade(MODE_GAME);
				}
			}
		}
	}
	else
	{// �I�����������ĂȂ���
		ReleaseAllFlontPolygon();
	}
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawCharsel(void)
{
	// �f�o�C�X����������
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();
	Camera *pCamera = GetCamera();
	Player *pPlayer = GetPlayer();
	D3DVIEWPORT9 viewportDef;
	// �r���[�|�[�g�����擾
	pDevice->GetViewport(&viewportDef);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCharsel, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntCharsel = 0; nCntCharsel < CHARSELTYPE_MAX; nCntCharsel++)
	{
		if (g_aCharsel[nCntCharsel].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureCharsel[nCntCharsel]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntCharsel * MAX_CHARSELTOP,
				2);
		}
	}
	// �}�[�J�[�̕`�揈��
	DrawMarker();
	// �J�[�\���̕`�揈��
	DrawCursor();

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (pPlayer[nCnt].typeInfo != PLAYERTYPE_MAX)
		{
			// ����̃v���C���[�i�J�[�\���P�j
			SetCamera(nCnt+1);
			// �y�o�b�t�@�̃r���[�|�[�g�̃G���A���N���A
			pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
			// �v���C���[�̃^�C�v�@�J�����̔ԍ��i�ς��Ȃ��j
			DrawPlayer(nCnt, nCnt+1);

			// �}�[�J�[�̕`�揈��
			DrawMarker();
			// �J�[�\���̕`�揈��
			DrawCursor();

		}
	}


	//// �E����̃v���C���[�i�J�[�\���Q�j
	//SetCamera(2);
	//// �y�o�b�t�@�̃r���[�|�[�g�̃G���A���N���A
	//pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	//// �v���C���[�̃^�C�v�@�J�����̔ԍ��i�ς��Ȃ��j
	//DrawPlayer(1, 2);

	//// �����̃v���C���[�i�J�[�\���R�j
	//SetCamera(3);
	//// �y�o�b�t�@�̃r���[�|�[�g�̃G���A���N���A
	//pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	//// �v���C���[�̃^�C�v�@�J�����̔ԍ��i�ς��Ȃ��j
	//DrawPlayer(2, 3);

	//// �E���̃v���C���[�i�J�[�\���S�j
	//SetCamera(4);
	//// �y�o�b�t�@�̃r���[�|�[�g�̃G���A���N���A
	//pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	//// �v���C���[�̃^�C�v�@�J�����̔ԍ��i�ς��Ȃ��j
	//DrawPlayer(3, 4);

	// �r���[�|�[�g�������Ƃɖ߂�
	pDevice->SetViewport(&viewportDef);
	//�t�����g�|���S��
	DrawFlontPolygon();

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���_���̍쐬
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MakeVertexCharsel(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D*pVtx;		// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_CHARSELTOP * (CHARSELTYPE_MAX),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCharsel,
		NULL);

	// ���_l�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCharsel->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < CHARSELTYPE_MAX; nCnt++, pVtx += 4)
	{
		// ���W
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// rhw
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// �F
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffCharsel->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �L�����N�^�[�I���̐ݒ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetCharsel(D3DXVECTOR3	pos, float fWidth, float fHeight, CHARSELTYPE type)
{
	VERTEX_2D*pVtx;		// ���_���ւ̃|�C���^

	// ���_l�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCharsel->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < CHARSELTYPE_MAX; nCnt++, pVtx += 4)
	{
		if (g_aCharsel[nCnt].bUse == false)
		{
			g_aCharsel[nCnt].pos = pos;				// �ʒu
			g_aCharsel[nCnt].fWidth = fWidth;		// ��
			g_aCharsel[nCnt].fHeight = fHeight;		// ����
			g_aCharsel[nCnt].type = type;			// ���

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(- g_aCharsel[nCnt].fWidth / 2, -g_aCharsel[nCnt].fHeight / 2, 0.0f) + g_aCharsel[nCnt].pos;
			pVtx[1].pos = D3DXVECTOR3(g_aCharsel[nCnt].fWidth / 2, -g_aCharsel[nCnt].fHeight / 2, 0.0f) + g_aCharsel[nCnt].pos;
			pVtx[2].pos = D3DXVECTOR3(- g_aCharsel[nCnt].fWidth / 2, g_aCharsel[nCnt].fHeight / 2, 0.0f) + g_aCharsel[nCnt].pos;
			pVtx[3].pos = D3DXVECTOR3(g_aCharsel[nCnt].fWidth / 2, g_aCharsel[nCnt].fHeight / 2, 0.0f) + g_aCharsel[nCnt].pos;
			g_aCharsel[nCnt].bUse = true;
			break;
		}
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffCharsel->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �����蔻��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
PLAYERTYPE CollisionCharsel(D3DXVECTOR3 pPos, float fWidth, float fHeight, PLAYERTYPE Makertype)
{
	PLAYERTYPE type = Makertype;
	if (type == PLAYERTYPE_MAX)
	{
		for (int nCharsel = CHARSELTYPE_MATURI; nCharsel < CHARSELTYPE_MAX; nCharsel++)
		{
			if (g_aCharsel[nCharsel].pos.x - g_aCharsel[nCharsel].fWidth / 2 <= pPos.x + fWidth / 2 &&
				g_aCharsel[nCharsel].pos.x + g_aCharsel[nCharsel].fWidth / 2 >= pPos.x - fWidth / 2 &&
				g_aCharsel[nCharsel].pos.y - g_aCharsel[nCharsel].fHeight / 2 <= pPos.y + fHeight / 2 &&
				g_aCharsel[nCharsel].pos.y + g_aCharsel[nCharsel].fHeight / 2 >= pPos.y - fHeight / 2)
			{// �͈�
				switch (g_aCharsel[nCharsel].type)
				{
				case CHARSELTYPE_MATURI:
					type = PLAYERTYPE_MATURI;	// �܂�
					break;
				case CHARSELTYPE_AMANO:
					type = PLAYERTYPE_AMANO;	// �܂�
					break;
				case CHARSELTYPE_GOJOU:
					type = PLAYERTYPE_GOJOU;	// �܏�
					break;
				case CHARSELTYPE_MOMIJI:
					type = PLAYERTYPE_MOMIJI;	// ���݂�
					break;
				case CHARSELTYPE_DONROID:
					type = PLAYERTYPE_DONROID;	// �h�����C�h
					break;
				case CHARSELTYPE_RANDOM:
					type = PLAYERTYPE(rand() % PLAYERTYPE_MAX);	// �����_��
					break;
				case CHARSELTYPE_EXIT:
					if (GetFade() == FADE_NONE)
					{
						SetFade(MODE_TITLE);
					}
					break;
				}
			}
		}
	}
	return type;
}
