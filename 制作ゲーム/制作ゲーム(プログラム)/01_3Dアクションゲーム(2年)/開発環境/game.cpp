////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �Q�[������ [game.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>		// �C���N���[�h�֐�
#include <string.h>		// �X�g�����O�֐�
#include <stdlib.h>		// �����h�֐�
#include "main.h"
#include "game.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "gamepad.h"
#include "player.h"
#include "fade.h"
#include "time.h"
#include "light.h"
#include "line.h"
#include "meshWall.h"
#include "meshField.h"
#include "model.h"
#include "orbit.h"
#include "shadow.h"
#include "effect.h"
#include "life.h"
#include "guard.h"
#include "effectUP.h"
#include "Item.h"
#include "sky.h"
#include "SP.h"
#include "flontpolygon.h"
#include "pause.h"
#include "time.h"
#include "cutin.h"
#include "eventlogo.h"
#include "event.h"
#include "billboard.h"
#include "lineEffect.h"
#include "playerMark.h"
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define MAX_CHAR	(256)
#define TAKOYAKI_TIME (600)
#define CHOKO_TIME (600)
#define FISH_TIME (600)
//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
GAMESTATE g_gameState = GAMESTATE_GAME;	// �Q�[���̏��
int g_nCounterGameState;				// ��ԊǗ��J�E���^�[
bool g_bPause;							// �|�[�Y�����ǂ���
bool g_bPauseView;						// �|�[�Y��\��
bool g_bGameState[GAMESTAGEMAX];		// �Q�[���؂�ւ��
bool g_bGameSpecial;					// �J�b�g�C�����Ă��邩�ǂ���
int	g_nCntGame;							// ���Ԃ̃J�E���^�[
int g_nGetTakoyaki;						// �^�R�Ă��Q�b�g
bool g_bGetTakoyaki;					// �^�R�Ă��Q�b�g
int g_nGetChoco;						// �`���R�o�i�i�Q�b�g
bool g_bGetChoco;						// �`���R�o�i�i�Q�b�g
int g_nGetFish;							// ���Q�b�g
bool g_bGetFish;						// ���Q�b�g
	//==============================================================================================================================
	// ����������
	//==============================================================================================================================
void InitGame(void)
{
	Player *pPlayer = GetPlayer();
	// �e��I�u�W�F�N�g�̏���������
	g_bPause = false;			// �|�[�Y���Ȃ�
	g_bPauseView = false;		// �|�[�Y�������Ȃ�
	g_bGameSpecial = false;		//�J�b�g�C�����Ă��Ȃ���Ԃɐݒ�
	g_nCntGame = 1;
	g_nGetTakoyaki = 0;			// �^�R�Ă��Q�b�g
	g_bGetTakoyaki = false;			// �^�R�Ă��Q�b�g
	g_nGetChoco = 0;				  // �`���R�o�i�i�Q�b�g
	g_bGetChoco = false;			  // �`���R�o�i�i�Q�b�g
	g_nGetFish = 0;							// ���Q�b�g
	g_bGetFish = false;						// ���Q�b�g
	for (int nCntState = 0; nCntState < GAMESTAGEMAX; nCntState++)
	{
		g_bGameState[nCntState] = false;
	}
	g_gameState = GAMESTATE_GAME;
	g_nCounterGameState = 0;

	// �J�����̏���������
	InitCamera();
	// ���̏���������
	InitLine();
	// ���C�g�̏���������
	InitLight();
	// �C�x���g
	InitEvent();

	// �e�̏���������
	InitShadow();
	// �v���C���[�̏���������
	InitPlayer();
	// ���b�V�����̏���������
	InitMeshField();
	// ���b�V���ǂ̏���������
	InitMeshWall();
	// ���f���̏���������
	InitModel();
	// �t�@�C���ǂݍ���
	SetStagePos("data/stage1.txt");
	// �G�t�F�N�g�̏���������
	InitEffect();
	// �O�Ղ̏���������
	InitOrbit();
	// �K�[�h�̏���������
	InitGuard();
	// �G�t�F�N�g�|���S���̏���������
	InitEffectUP();
	// �A�C�e���̐���
	InitItem();
	// ��̐���
	InitSky();
	//�J�b�g�C��
	InitCut();
	// �C�x���g���S
	InitEventlogo();
	// �r���{�[�h
	InitBillboard();
	// ���C���G�t�F�N�g
	InitLineEffect();
	// �v���C���[�}�[�J�[
	InitPlayerMark();
	D3DXVECTOR3 StartPos[MAX_PLAYER]=
	{
		{ D3DXVECTOR3(-220,100,-50) },
		{ D3DXVECTOR3(-70,100,220) },
		{ D3DXVECTOR3(100,100,220) },
		{ D3DXVECTOR3(250,100,-50) },

	};
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (pPlayer[nCnt].typeInfo != PLAYERTYPE_MAX)
		{
			SetPlayer(nCnt, StartPos[nCnt], pPlayer[nCnt].typeInfo);
		}
	}
#ifdef _DEBUG
	pPlayer[0].typeInfo = PLAYERTYPE_DONROID;
	pPlayer[1].typeInfo = PLAYERTYPE_MATURI;
	pPlayer[2].typeInfo = PLAYERTYPE_GOJOU;
	pPlayer[3].typeInfo = PLAYERTYPE_MOMIJI;
	SetPlayer(0, D3DXVECTOR3(-200.0f, 30, 0), PLAYERTYPE_DONROID);
	SetPlayer(1, D3DXVECTOR3(0.0f, 30, 0), PLAYERTYPE_MATURI);
	SetPlayer(2, D3DXVECTOR3(200.0f, 30, 0), PLAYERTYPE_GOJOU);
	SetPlayer(3, D3DXVECTOR3(100.0f, 30, 100), PLAYERTYPE_MOMIJI);


#endif
	// ���C�t�̏���������
	InitLife();
	// SP�̏���������
	InitSp();
	// �|�[�Y�̏���������
	InitPause();
	// �^�C���̏���������
	InitTime();

}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitGame(void)
{
	// �e��I�u�W�F�N�g�̏I������
#if 1
	// �J�����̏I������
	UninitCamera();
	// ���C���̏I������
	UninitLine();
	// ���C�g�̏I������
	UninitLight();
	// �e�̏I������
	UninitShadow();
	// �G�t�F�N�g�̏I������
	UninitEffect();
	// ���C�t�̏I������
	UninitLife();
	// �O�Ղ̏I������
	UninitOrbit();
	// �K�[�h�̏I������
	UninitGuard();
	// �G�t�F�N�g�|���S���̏I������
	UninitEffectUP();
	// �A�C�e���̏I��
	UninitItem();
	// ��̏I��
	UninitSky();
	//�J�b�g�C��
	UninitCut();
	// SP�̏I��
	UninitSp();
	// �|�[�Y�̏I������
	UninitPause();
	// �^�C���̏I������
	UninitTime();
	// �C�x���g���S
	UninitEventlogo();
	// �r���{�[�h
	UninitBillboard();
	// ���C���G�t�F�N�g
	UninitLineEffect();
	// �C�x���g
	UninitEvent();
	// �v���C���[�}�[�J�[
	UninitPlayerMark();
	//�t�����g�|���S�������ׂĔ�\���ɂ���
	ReleaseAllFlontPolygon();

	g_gameState = GAMESTATE_GAME;
	g_bPause = false;
	g_bPauseView = false;
#endif
}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	Player *pPlayer = GetPlayer();
	Camera *pCamera = GetCamera();
	GamePad *pGamePad = GetgamePadStick();
	// �|�[�Y����
	if (GetKeyboardTrigger(DIK_P) == true)
	{// �L�[�{�[�h
		if (g_bPauseView == true)
		{
			g_bPauseView = false;
		}
		PlaySound(SOUND_LABEL_PAUSE000);
		SetPause(true, 0);
		g_bPause = g_bPause ? false : true;
	}
	for (int nIdy = 0; nIdy < MAX_GAMEPAD; nIdy++)
	{// �Q�[���p�b�h
		if (pGamePad[nIdy].pDevGamePad != NULL)
		{
			if (GetGamePadTrigger(nIdy, BUTTON_START))
			{
				PlaySound(SOUND_LABEL_PAUSE000);
				if (g_bPauseView == true)
				{
					g_bPauseView = false;
				}
				SetPause(true, 0);
				g_bPause = g_bPause ? false : true;
			}
		}
	}
	// �|�[�Y�����ǂ���
	if (g_bPause == true)
	{
		if (GetKeyboardTrigger(DIK_V) == true)
		{// �|�[�Y��ʏ������ǂ���
			g_bPauseView = g_bPauseView ? false : true;
		}
		for (int nIdy = 0; nIdy < MAX_GAMEPAD; nIdy++)
		{// �Q�[���p�b�h
			if (pGamePad[nIdy].pDevGamePad != NULL)
			{
				if (GetGamePadTrigger(nIdy, BUTTON_A))
				{
					g_bPauseView = g_bPauseView ? false : true;
				}
			}
		}
	}


	if (g_bPause == false)
	{
		if (g_bGameSpecial == false)
		{

			// �e��I�u�W�F�N�g�̍X�V����
			// �J�����̍X�V����
			UpdateCamera();
			// ���̍X�V����
			UpdateLine();
			// �O�Ղ̕`��
			UpdateOrbit();
			// ���C�g�̍X�V����
			UpdateLight();
		}

		for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
		{
			if (pPlayer[nCnt].typeInfo != PLAYERTYPE_MAX)
			{
				// �v���C���[�̍X�V����
				UpdatePlayer(nCnt);
			}
		}

		if (g_bGameSpecial == false)
		{
			// �^�R�Ă��o��
			g_nGetTakoyaki++;
			if (g_nGetTakoyaki %TAKOYAKI_TIME == 0)
			{// �^�R�Ă��l���\
				if (!g_bGetTakoyaki)
				{
					SetBillboard(D3DXVECTOR3(310, 50, 320), BILLBOARDTYPE_EVENT, 50, 50);
					g_bGetTakoyaki = true;
				}
			}
			// �`���R�o�i�i�o��
			g_nGetChoco++;
			if (g_nGetChoco %CHOKO_TIME == 0)
			{// �`���R�o�i�i�l���\
				if (!g_bGetChoco)
				{
					SetBillboard(D3DXVECTOR3(490, 50, 320), BILLBOARDTYPE_EVENT_1, 50, 50);
					g_bGetChoco = true;
				}
			}
			// ���o��
			g_nGetFish++;
			if (g_nGetFish %FISH_TIME == 0)
			{// �`���R�o�i�i�l���\
				if (!g_bGetFish)
				{
					SetBillboard(D3DXVECTOR3(130, 50, 320), BILLBOARDTYPE_EVENT_2, 50, 50);
					g_bGetFish = true;
				}
			}
			// �C�x���g�̍X�V����
			UpdateEvent();

			// �^�C���̍X�V����
			UpdateTime();
			// �C�x���g���S
			UpdateEventlogo();
			// �e�̍X�V����
			UpdateShadow();
			// ���b�V�����̍X�V����
			UpdateMeshField();
			// ���b�V���ǂ̍X�V����
			UpdateMeshWall();
			// ���f���̍X�V����
			UpdateModel();
			// �G�t�F�N�g�̍X�V����
			UpdateEffect();
			// ���C�t�̍X�V����
			UpdateLife();
			// �K�[�h�̍X�V����
			UpdateGuard();
			// �G�t�F�N�g�|���S���̍X�V����
			UpdateEffectUP();
			// �A�C�e���̍X�V����
			UpdateItem();
			// ��̍X�V����
			UpdateSky();
			// �r���{�[�h�̍X�V����
			UpdateBillboard();
			// ���C���G�t�F�N�g
			UpdateLineEffect();
			// �v���C���[�}�[�J�[
			UpdatePlayerMark();
		}

		//�J�b�g�C��
		UpdateCut();
	}

	if (g_bPause == false)
	{
		if (g_bGameSpecial == false)
		{
			g_nCntGame = 1;


			// SP�̍X�V����
			UpdateSp();
			switch (g_gameState)
			{
			case GAMESTATE_NONE:
				break;
			case GAMESTATE_START:
				break;
			case GAMESTATE_GAME:
					SetEffectUP(0, D3DXVECTOR3(sinf(SetRandomEffect())*600.0f, 600 + float(rand() % 300), cosf(SetRandomEffect())*300.0f + 200.0f),
						D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(SetRandomEffect(), SetRandomEffect(), SetRandomEffect()),
						D3DXCOLOR(float(rand() % 100) / 100.0f, float(rand() % 100) / 100.0f, float(rand() % 100) / 100.0f, 1.0f),
						EFFECTUPTYPE_PAPER, 10);
				break;
			case GAMESTATE_END:
				int nIdy = CheckLife();
				for (int nCnt = 0; nCnt < 5; nCnt++)
				{
					SetEffectUP(0, D3DXVECTOR3(sinf(SetRandomEffect())*600.0f, 600 + float(rand() % 300), cosf(SetRandomEffect())*300.0f + 200.0f),
						D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(SetRandomEffect(), SetRandomEffect(), SetRandomEffect()),
						D3DXCOLOR(float(rand() % 100) / 100.0f, float(rand() % 100) / 100.0f, float(rand() % 100) / 100.0f, 1.0f),
						EFFECTUPTYPE_PAPER, 10);
				}
				if (g_nCounterGameState == 80)
				{
					SetFlontPolygon(FLONT_TEXTYPE_GAMEEND, D3DXVECTOR3(SCREEN_WIDTH / 2, 600, 0.0f),
						SCREEN_WIDTH / 1.5f, 200, FLONTTYPE_NARRATION);

					PlaySound(SOUND_LABEL_GAMEEND000);
					for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
					{
						if (nCntPlayer != nIdy)
						{
							GetPlayer()[nCntPlayer].state = PLAYERSTATE_DEATH;
						}
					}
					GetPlayer()[nIdy].rot.y = 0.0f;
					GetPlayer()[nIdy].Destrot.y = 0.0f;
					GetPlayer()[nIdy].bMotionState[PLAYER_BOOL_WIN] = true;
					GetPlayer()[nIdy].nCntEmote = 10000;

					GetCamera()[0].nState = CAMERASTATE_SPECIAL;
					GetCamera()[0].posRDest = GetPlayer()[nIdy].pos;
					GetCamera()[0].nStateCounter = 10000;
				}
				if (g_nCounterGameState == 150)
				{
					if (pPlayer[nIdy].state != PLAYERSTATE_DEATH)
					{
						if (pPlayer[nIdy].typeInfo == PLAYERTYPE_MATURI) { PlaySound(SOUND_HUMAN_VICTORY); }
						else if (pPlayer[nIdy].typeInfo == PLAYERTYPE_AMANO) { PlaySound(SOUND_KAPA_VICTORY); }
						else if (pPlayer[nIdy].typeInfo == PLAYERTYPE_GOJOU) { PlaySound(SOUND_TENGU_VICTORY); }
						else if (pPlayer[nIdy].typeInfo == PLAYERTYPE_DONROID) { PlaySound(SOUND_ROBOT_ATTACK005); }
						else if (pPlayer[nIdy].typeInfo == PLAYERTYPE_MOMIJI) { PlaySound(SOUND_FOX_VICTORY); }
					}

				}
				g_nCounterGameState++;

				if (g_nCounterGameState >= 250)
				{
					g_gameState = GAMESTATE_NONE;
					if (GetFade() == FADE_NONE)
					{
						// ��ʃ��[�h�̐ݒ�
						SetFade(MODE_CHARACTER);
					}
				}
				break;
			}
		}
		else
		{
			//���Ԃ̉��Z
			g_nCntGame++;
		}

		if (GetKeyboardTrigger(DIK_F9))
		{
			UninitLine();
			UninitModel();
			InitLine();
			SetObjectFileData();
			InitModel();
			InitMeshField();
			InitMeshWall();
			// �t�@�C���ǂݍ���
			SetStagePos("data/stage1.txt");

		}
	}
	else
	{
		if (g_bPauseView == false)
		{
			UpdatePause(&g_bPause);		// �|�[�Y

		}
		else
		{
			// �J�����̍X�V����
			UpdateCamera();

		}
	}

}
//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	Player *pPlayer = GetPlayer();
	Camera *pCamera = GetCamera();
	D3DVIEWPORT9 viewportDef;

	// �r���[�|�[�g�����擾
	pDevice->GetViewport(&viewportDef);

	// �e��I�u�W�F�N�g�̕`�揈��
#if 1
	// �J�����̐ݒ�
	SetCamera(0);
	if (GetDrawDebug()[DRAW_DEBUG_LINE] == true)
	{
		// ���̏���������
		DrawLine();
	}
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (pPlayer[nCnt].typeInfo != PLAYERTYPE_MAX)
		{
			// �v���C���[�̕`�揈��
			DrawPlayer(nCnt, 0);
		}
	}
	// ��̕`�揈��
	DrawSky();
	// ���b�V�����̕`�揈��
	DrawMeshField();
	// ���b�V���ǂ̕`�揈��
	DrawMeshWall();
	// ���f���̕`�揈��
	DrawModel();
	// �e�̕`�揈��
	DrawShadow();
	// �G�t�F�N�g�̕`�揈��
	DrawEffect();
	// �v���C���[�}�[�J�[
	DrawPlayerMark();
	// ���C���G�t�F�N�g
	DrawLineEffect();
	// �G�t�F�N�g�|���S���̕`�揈��
	DrawEffectUP();
	// �K�[�h�̕`�揈��
	DrawGuard();
	// �r���{�[�h
	DrawBillboard();
	// �O�Ղ̕`��
	DrawOrbit();
	// �A�C�e���̕`�揈��
	DrawItem();
	//�J�b�g�C��
	DrawCut();
	if (g_bPauseView == false)
	{// �|�[�Y�\������\�����@���S���[�r�[��
	 //�t�����g�|���S��
		DrawFlontPolygon();
		// ���C�t�̕`�揈��
		DrawLife();
		// SP�̕`�揈��
		DrawSp();
		// �^�C���̕`�揈��
		DrawTime();
		// �C�x���g���S�̕`�揈��
		DrawEventlogo();
	}
#endif

	if (g_bPause == true)
	{// �|�[�Y
		if (g_bPauseView == false)
		{// �|�[�Y�\������\����
		 // �J�����̐ݒ�
			SetCamera(0);
			DrawPause();
		}
	}
	// �r���[�|�[�g�������Ƃɖ߂�
	pDevice->SetViewport(&viewportDef);


}
//==============================================================================================================================
// �e��I�u�W�F�N�g����
//==============================================================================================================================
void SetPlayerFileData(int nIdy, char *cFilename)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PlayerData *pPlayerData = GetPlayerData();
	Player *pPlayer = GetPlayer();
	FILE *pFile;
	char cLine[MAX_CHAR];	// �s�S�ēǂݍ���
	char cData[MAX_CHAR];	// ��������
	pFile = fopen(cFilename, "r");
	int nLoop = 0;							// ���[�v���邩�ǂ���[0:���[�v���Ȃ� / 1:���[�v����]
	int nOrbit = 0;							// �O�Ղ̐�
	int nOrbitLength = 0;					// �O�Ղ̒���
	int nIdyOrbit = 0;						// �O�Ղ̐e
	ORBITTYPE nOrbitType;					// �O�Ղ̃^�C�v
	int nCollisionIdy = 0;										// �U������̐e
	D3DXVECTOR3 CollisionOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// �U������̃I�t�Z�b�g
	float fCollisionRadius = 0;									// �U������̔��a
	int nCollisionStart = 0;									// �U������̃X�^�[�g
	int nCollisionEnd = 0;										// �U������̏I���
	D3DXVECTOR3 OrbitStart = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �O�Վn��
	D3DXVECTOR3 OrbitEnd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �O�ՏI���
	int nDamageIdx = 0;											// �_���[�W�ԍ�
	D3DXVECTOR3 DamageOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �_���[�W�I�t�Z�b�g
	float fDamageRadius = 0;									// �_���[�W���a
	int nStopTime = 0;											// �X�g�b�v
	for (int nCollision = 0; nCollision < MAX_COLLISION; nCollision++)
	{// ����̏�����
		pPlayerData[nIdy].ColAttack[nCollision].bUse = false;
	}
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		pPlayer[nCntPlayer].typeInfo = PLAYERTYPE_MAX;
	}
	if (pFile != NULL)
	{
		while (fgets(&cLine[0], MAX_CHAR, pFile) != NULL || strcmp(cData, "END_SCRIPT") != 0)
		{
			sscanf(&cLine[0], "%s", &cData);
			if (strcmp(cData, "NUM_MODEL") == 0)		// ���f���̐�
			{// �g���ĂȂ�����ǂ�����
				sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &pPlayerData[nIdy].nNumParts);
			}
			// ���f���̃t�@�C���ǂݍ���
			if (strcmp(cData, "MODEL_FILENAME") == 0)
			{
				for (int nCntModel = 0; nCntModel < pPlayerData[nIdy].nNumParts; nCntModel++)
				{
					sscanf(&cLine[0], "%s %s %s", &cData[0], &cData[0], &cData[0]);
					pPlayerData[nIdy].aModel[nCntModel].pFileName = &cData[0];

					// X�t�@�C���̓ǂݍ���
					D3DXLoadMeshFromX(pPlayerData[nIdy].aModel[nCntModel].pFileName,
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&pPlayerData[nIdy].aModel[nCntModel].pBuffMat,
						NULL,
						&pPlayerData[nIdy].aModel[nCntModel].nNumMat,
						&pPlayerData[nIdy].aModel[nCntModel].pMesh);
					D3DXMATERIAL *pMat;					// �}�e���A���f�[�^�ւ̃|�C���^
														// �}�e���A���f�[�^�ւ̃|�C���^���擾
					pMat = (D3DXMATERIAL*)pPlayerData[nIdy].aModel[nCntModel].pBuffMat->GetBufferPointer();
					// �e�N�X�`���̔z��ݒ�
					pPlayerData[nIdy].aModel[nCntModel].pTextuer[0] = new LPDIRECT3DTEXTURE9[(int)pPlayerData[nIdy].aModel[nCntModel].nNumMat];
					pPlayerData[nIdy].aModel[nCntModel].pTextuer[1] = new LPDIRECT3DTEXTURE9[(int)pPlayerData[nIdy].aModel[nCntModel].nNumMat];
					pPlayerData[nIdy].aModel[nCntModel].pTextuer[2] = new LPDIRECT3DTEXTURE9[(int)pPlayerData[nIdy].aModel[nCntModel].nNumMat];
					pPlayerData[nIdy].aModel[nCntModel].pTextuer[3] = new LPDIRECT3DTEXTURE9[(int)pPlayerData[nIdy].aModel[nCntModel].nNumMat];
					for (int nCntPlayerTex = 0; nCntPlayerTex < (int)pPlayerData[nIdy].aModel[nCntModel].nNumMat; nCntPlayerTex++)
					{

						pPlayerData[nIdy].aModel[nCntModel].pTextuer[0][nCntPlayerTex] = NULL;
						pPlayerData[nIdy].aModel[nCntModel].pTextuer[1][nCntPlayerTex] = NULL;
						pPlayerData[nIdy].aModel[nCntModel].pTextuer[2][nCntPlayerTex] = NULL;
						pPlayerData[nIdy].aModel[nCntModel].pTextuer[3][nCntPlayerTex] = NULL;
						if (pMat[nCntPlayerTex].pTextureFilename != NULL)
						{
							// �e�N�X�`���̐ݒ�
							D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
								pMat[nCntPlayerTex].pTextureFilename,	// �t�@�C���̖��O
								&pPlayerData[nIdy].aModel[nCntModel].pTextuer[0][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
																										// �e�N�X�`���̐ݒ�
							D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
								pMat[nCntPlayerTex].pTextureFilename,	// �t�@�C���̖��O
								&pPlayerData[nIdy].aModel[nCntModel].pTextuer[1][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
							D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
								pMat[nCntPlayerTex].pTextureFilename,	// �t�@�C���̖��O
								&pPlayerData[nIdy].aModel[nCntModel].pTextuer[2][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
							D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
								pMat[nCntPlayerTex].pTextureFilename,	// �t�@�C���̖��O
								&pPlayerData[nIdy].aModel[nCntModel].pTextuer[3][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^

							if (nCntModel <= 15)
							{
								if (nIdy == PLAYERTYPE_MATURI)
								{// �܂�
									D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�ւ̃|�C���^
										"data/TEXTURE/musume_B.jpg",												// �t�@�C���̖��O
										&pPlayerData[nIdy].aModel[nCntModel].pTextuer[1][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
									D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�ւ̃|�C���^
										"data/TEXTURE/musume_C.jpg",												// �t�@�C���̖��O
										&pPlayerData[nIdy].aModel[nCntModel].pTextuer[2][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
									D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�ւ̃|�C���^
										"data/TEXTURE/musume_D.jpg",												// �t�@�C���̖��O
										&pPlayerData[nIdy].aModel[nCntModel].pTextuer[3][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
								}
								else if (nIdy == PLAYERTYPE_AMANO)
								{// ���܂�
									D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�ւ̃|�C���^
										"data/TEXTURE/tengu_B.jpg",												// �t�@�C���̖��O
										&pPlayerData[nIdy].aModel[nCntModel].pTextuer[1][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
									D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�ւ̃|�C���^
										"data/TEXTURE/tengu_C.jpg",												// �t�@�C���̖��O
										&pPlayerData[nIdy].aModel[nCntModel].pTextuer[2][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
									D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�ւ̃|�C���^
										"data/TEXTURE/tengu_D.jpg",												// �t�@�C���̖��O
										&pPlayerData[nIdy].aModel[nCntModel].pTextuer[3][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
								}
								else if (nIdy == PLAYERTYPE_GOJOU)
								{// �����傤
									D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�ւ̃|�C���^
										"data/TEXTURE/kappa_B.jpg",												// �t�@�C���̖��O
										&pPlayerData[nIdy].aModel[nCntModel].pTextuer[1][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
									D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�ւ̃|�C���^
										"data/TEXTURE/kappa_C.jpg",												// �t�@�C���̖��O
										&pPlayerData[nIdy].aModel[nCntModel].pTextuer[2][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
									D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�ւ̃|�C���^
										"data/TEXTURE/kappa_D.jpg",												// �t�@�C���̖��O
										&pPlayerData[nIdy].aModel[nCntModel].pTextuer[3][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
								}
								else if (nIdy == PLAYERTYPE_MOMIJI)
								{// ���݂�
									D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�ւ̃|�C���^
										"data/TEXTURE/kitune_B.jpg",											// �t�@�C���̖��O
										&pPlayerData[nIdy].aModel[nCntModel].pTextuer[1][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
									D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�ւ̃|�C���^
										"data/TEXTURE/kitune_C.jpg",											// �t�@�C���̖��O
										&pPlayerData[nIdy].aModel[nCntModel].pTextuer[2][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
									D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�ւ̃|�C���^
										"data/TEXTURE/kitune_D.jpg",											// �t�@�C���̖��O
										&pPlayerData[nIdy].aModel[nCntModel].pTextuer[3][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
								}
								else if (nIdy == PLAYERTYPE_DONROID)
								{// �h�����C�h
									D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�ւ̃|�C���^
										"data/TEXTURE/robo_B.jpg",												// �t�@�C���̖��O
										&pPlayerData[nIdy].aModel[nCntModel].pTextuer[1][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
									D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�ւ̃|�C���^
										"data/TEXTURE/robo_C.jpg",												// �t�@�C���̖��O
										&pPlayerData[nIdy].aModel[nCntModel].pTextuer[2][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
									D3DXCreateTextureFromFile(pDevice,											// �f�o�C�X�ւ̃|�C���^
										"data/TEXTURE/robo_D.jpg",												// �t�@�C���̖��O
										&pPlayerData[nIdy].aModel[nCntModel].pTextuer[3][nCntPlayerTex]);		// �e�N�X�`���ւ̃|�C���^
								}
							}
						}
					}
					fgets(&cLine[0], MAX_CHAR, pFile);
				}
			}
			// �v���C���[�̃I�t�Z�b�g���
			if (strcmp(cData, "CHARACTERSET") == 0)
			{
				int nCntPlayerModel = 0;	// ���f���ԍ�
				while (strcmp(cData, "END_CHARACTERSET") != 0)
				{
					fgets(&cLine[0], MAX_CHAR, pFile);
					sscanf(&cLine[0], "%s", &cData);
					if (strcmp(cData, "MOVE") == 0)
					{
						sscanf(&cLine[0], "%s %s %f", &cData[0], &cData[0], &pPlayerData[nIdy].MoveSpeed);
					}
					else if (strcmp(cData, "JUMP") == 0)
					{
						sscanf(&cLine[0], "%s %s %f", &cData[0], &cData[0], &pPlayerData[nIdy].JumpSpeed);
					}
					else if (strcmp(cData, "RADIUS") == 0)
					{
						sscanf(&cLine[0], "%s %s %f", &cData[0], &cData[0], &pPlayerData[nIdy].fRadiusWidth);
					}
					else if (strcmp(cData, "HEIGHT") == 0)
					{
						sscanf(&cLine[0], "%s %s %f", &cData[0], &cData[0], &pPlayerData[nIdy].fRadiusHeight);
					}
					else if (strcmp(cData, "LIFE") == 0)
					{
						sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &pPlayerData[nIdy].nInitLife);
					}
					else if (strcmp(cData, "NUM_PARTS") == 0)		// ���f���̐�
					{// ���f����
						sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &pPlayerData[nIdy].nNumParts);
					}
					else if (strcmp(cData, "BODY_COLLISION") == 0)		// ���f���̐�
					{// ���f����
						sscanf(&cLine[0], "%s %s %d %f %f %f %f", &cData[0], &cData[0], &nDamageIdx, &DamageOffset.x, &DamageOffset.y, &DamageOffset.z, &fDamageRadius);
						SetBodyCollisionPlayer(nIdy, nDamageIdx, DamageOffset, fDamageRadius);
					}
					if (strcmp(cData, "PARTSSET") == 0)
					{
						while (strcmp(cData, "END_PARTSSET") != 0)
						{
							fgets(&cLine[0], MAX_CHAR, pFile);
							sscanf(&cLine[0], "%s", &cData);
							if (strcmp(cData, "INDEX") == 0)
							{
								sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &pPlayerData[nIdy].aModel[nCntPlayerModel].nIdxModel);
							}
							else if (strcmp(cData, "PARENT") == 0)
							{
								sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &pPlayerData[nIdy].aModel[nCntPlayerModel].nIdxModelPareant);
							}
							else if (strcmp(cData, "POS") == 0)
							{
								sscanf(&cLine[0], "%s %s %f %f %f", &cData[0], &cData[0], &pPlayerData[nIdy].aModel[nCntPlayerModel].pos.x, &pPlayerData[nIdy].aModel[nCntPlayerModel].pos.y, &pPlayerData[nIdy].aModel[nCntPlayerModel].pos.z);
								sscanf(&cLine[0], "%s %s %f %f %f", &cData[0], &cData[0], &pPlayerData[nIdy].aModel[nCntPlayerModel].Initpos.x, &pPlayerData[nIdy].aModel[nCntPlayerModel].Initpos.y, &pPlayerData[nIdy].aModel[nCntPlayerModel].Initpos.z);
							}
							else if (strcmp(cData, "ROT") == 0)
							{
								sscanf(&cLine[0], "%s %s %f %f %f", &cData[0], &cData[0], &pPlayerData[nIdy].aModel[nCntPlayerModel].rot.x, &pPlayerData[nIdy].aModel[nCntPlayerModel].rot.y, &pPlayerData[nIdy].aModel[nCntPlayerModel].rot.z);
							}
						}
						nCntPlayerModel++;
					}

				}
			}
			// �v���C���[�̃��[�V�����ݒ�
			if (strcmp(cData, "MOTIONSET") == 0)
			{
				int nCntKey = 0;	// �L�[��
				while (strcmp(cData, "END_MOTIONSET") != 0)
				{
					fgets(&cLine[0], MAX_CHAR, pFile);
					sscanf(&cLine[0], "%s", &cData);
					if (strcmp(cData, "LOOP") == 0)
					{
						sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &nLoop);
						if (nLoop == 0)
						{// ���[�v���Ȃ�
							pPlayerData[nIdy].aMotion[pPlayerData[nIdy].nNumMotion].bLoop = false;
						}
						else if (nLoop == 1)
						{// ���[�v����
							pPlayerData[nIdy].aMotion[pPlayerData[nIdy].nNumMotion].bLoop = true;
						}
					}
					else if (strcmp(cData, "NUM_KEY") == 0)
					{
						sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &pPlayerData[nIdy].aMotion[pPlayerData[nIdy].nNumMotion].nNumKey);
					}
					else if (strcmp(cData, "SETORBIT") == 0)
					{
						sscanf(&cLine[0], "%s %s %d %d %f %f %f %f %f %f %d", &cData[0], &cData[0], &nIdyOrbit, &nOrbitLength, &OrbitStart.x, &OrbitStart.y, &OrbitStart.z, &OrbitEnd.x, &OrbitEnd.y, &OrbitEnd.z, &nOrbitType);
						if (pPlayerData[nIdy].orbit[pPlayerData[nIdy].nNumMotion][nOrbit].motion == PlayerMotionType(pPlayerData[nIdy].nNumMotion))
						{
							nOrbit++;
						}
						else
						{
							nOrbit = 0;
						}
						pPlayerData[nIdy].orbit[pPlayerData[nIdy].nNumMotion][nOrbit].nIdyOrbit = nIdyOrbit;				// �O�Ղ̐�
						pPlayerData[nIdy].orbit[pPlayerData[nIdy].nNumMotion][nOrbit].nOrbitLength = nOrbitLength;		// �O�Ղ̒���
						pPlayerData[nIdy].orbit[pPlayerData[nIdy].nNumMotion][nOrbit].OrbitStart = OrbitStart;			// ���_
						pPlayerData[nIdy].orbit[pPlayerData[nIdy].nNumMotion][nOrbit].OrbitEnd = OrbitEnd;				// �I�_
						pPlayerData[nIdy].orbit[pPlayerData[nIdy].nNumMotion][nOrbit].nType = nOrbitType;					// �O�Ղ̃^�C�v
						pPlayerData[nIdy].orbit[pPlayerData[nIdy].nNumMotion][nOrbit].motion = PlayerMotionType(pPlayerData[nIdy].nNumMotion);	// ���[�V����

					}
					else if (strcmp(cData, "COLLISION") == 0)
					{
						sscanf(&cLine[0], "%s %s %d %f %f %f %f %d %d %d", &cData[0], &cData[0], &nCollisionIdy, &CollisionOffset.x, &CollisionOffset.y, &CollisionOffset.z, &fCollisionRadius, &nCollisionStart, &nCollisionEnd, &nStopTime);
						SetAttackCollisionPlayer(nIdy, nCollisionIdy, CollisionOffset, fCollisionRadius, nCollisionStart, nCollisionEnd, nStopTime, PlayerMotionType(pPlayerData[nIdy].nNumMotion));
					}
					else if (strcmp(cData, "ATTACK_POWER") == 0)
					{
						sscanf(&cLine[0], "%s %s %f", &cData[0], &cData[0], &pPlayerData[nIdy].aMotion[pPlayerData[nIdy].nNumMotion].fAttackPower);
					}
					else if (strcmp(cData, "COLLISION_DAMAGE") == 0)
					{
						sscanf(&cLine[0], "%s %s %f %f", &cData[0], &cData[0], &pPlayerData[nIdy].aMotion[pPlayerData[nIdy].nNumMotion].fDamageH, &pPlayerData[nIdy].aMotion[pPlayerData[nIdy].nNumMotion].fDamageV);
					}
					if (strcmp(cData, "KEYSET") == 0)
					{
						int nCntParts = 0;
						while (strcmp(cData, "END_KEYSET") != 0)
						{
							fgets(&cLine[0], MAX_CHAR, pFile);
							sscanf(&cLine[0], "%s", &cData);
							if (strcmp(cData, "FRAME") == 0)
							{
								sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &pPlayerData[nIdy].aMotion[pPlayerData[nIdy].nNumMotion].aKey[nCntKey].nFrame);
							}
							else if (strcmp(cData, "KEY") == 0)
							{
								while (strcmp(cData, "END_KEY") != 0)
								{
									fgets(&cLine[0], MAX_CHAR, pFile);
									sscanf(&cLine[0], "%s", &cData);
									if (strcmp(cData, "POS") == 0)
									{
										sscanf(&cLine[0], "%s %s %f %f %f", &cData[0], &cData[0]
											, &pPlayerData[nIdy].aMotion[pPlayerData[nIdy].nNumMotion].aKey[nCntKey].aPartsKey[nCntParts].pos.x, &pPlayerData[nIdy].aMotion[pPlayerData[nIdy].nNumMotion].aKey[nCntKey].aPartsKey[nCntParts].pos.y, &pPlayerData[nIdy].aMotion[pPlayerData[nIdy].nNumMotion].aKey[nCntKey].aPartsKey[nCntParts].pos.z);
									}
									else if (strcmp(cData, "ROT") == 0)
									{
										sscanf(&cLine[0], "%s %s %f %f %f", &cData[0], &cData[0]
											, &pPlayerData[nIdy].aMotion[pPlayerData[nIdy].nNumMotion].aKey[nCntKey].aPartsKey[nCntParts].rot.x, &pPlayerData[nIdy].aMotion[pPlayerData[nIdy].nNumMotion].aKey[nCntKey].aPartsKey[nCntParts].rot.y, &pPlayerData[nIdy].aMotion[pPlayerData[nIdy].nNumMotion].aKey[nCntKey].aPartsKey[nCntParts].rot.z);
										sscanf(&cLine[0], "%s %s %f %f %f", &cData[0], &cData[0]
											, &pPlayerData[nIdy].aModel[nCntParts].rot.x, &pPlayerData[nIdy].aModel[nCntParts].rot.y, &pPlayerData[nIdy].aModel[nCntParts].rot.z);
									}
								}
								nCntParts++;// ���̃p�[�c��
							}
						}
						nCntKey++;	// ���̃L�[��
					}
				}
				pPlayerData[nIdy].nNumMotion++; // ���̃��[�V������
			}
		}

	}

	fclose(pFile);

}
//==============================================================================================================================
// �e��I�u�W�F�N�g����
//==============================================================================================================================
void SetObjectFileData(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FILE *pFile;
	char cLine[MAX_CHAR];
	char cData[MAX_CHAR];
	int nNumModel;
	pFile = fopen("data/model.txt", "r");
	MeshField *pMeshField = GetMeshField();
	MeshFieldData  *pMeshFieldData = GetMeshFieldData();
	MeshWall *pMeshWall = GetMeshWall();
	MeshWallData *pMeshWallData = GetMeshWallData();
	Model *pModel = GetModel();
	ModelData *pModelData = GetModelData();
	ModelData *pModelData2 = GetModelData();
	for (int nCntMat = 0; nCntMat < MAX_MODEL_TYPE; nCntMat++)
	{
		for (int nCntCollision = 0; nCntCollision < MAX_MODEL_COLLISION; nCntCollision++)
		{
			pModelData[nCntMat].bCollison[nCntCollision] = false;
		}
		pModelData[nCntMat].bCatch = false;// ���ĂȂ�
		pModelData[nCntMat].bGetInfo = false;// ���擾�ł��Ȃ�
	}
	if (pFile != NULL)
	{
		while (fgets(&cLine[0], MAX_CHAR, pFile) != NULL)
		{
			sscanf(&cLine[0], "%s", &cData);

			if (strcmp(cData, "NUM_TEXTURE") == 0)
			{// �g���ĂȂ�����ǂ�����
				sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &pMeshFieldData[0].nNumTex);
			}
			if (strcmp(cData, "TEXTURE_FILENAME") == 0)
			{
				sscanf(&cLine[0], "%s %s %s", &cData[0], &cData[0], &cData[0]);
				pMeshFieldData->pFileName = &cData[0];

				D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
					pMeshFieldData->pFileName,							// �t�@�C���̖��O
					&pMeshFieldData->pTexture);							// �e�N�X�`���ւ̃|�C���^
				pMeshFieldData++;
			}
			if (strcmp(cData, "NUM_WALL") == 0)
			{// �g���ĂȂ�����ǂ�����
				sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &pMeshWallData[0].nNumTex);
			}
			if (strcmp(cData, "WALL_FILENAME") == 0)
			{
				sscanf(&cLine[0], "%s %s %s", &cData[0], &cData[0], &cData[0]);
				pMeshWallData->pFileName = &cData[0];

				D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
					pMeshWallData->pFileName,						// �t�@�C���̖��O
					&pMeshWallData->pTexture);						// �e�N�X�`���ւ̃|�C���^
				pMeshWallData++;
			}

			if (strcmp(cData, "NUM_MODEL") == 0)
			{// �g���ĂȂ�����ǂ�����
				sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &nNumModel);
			}

			if (strcmp(cData, "MODEL_FILENAME") == 0)
			{
				sscanf(&cLine[0], "%s %s %s", &cData[0], &cData[0], &cData[0]);
				pModelData->pFileName = &cData[0];

				// ���f���f�[�^�̓ǂݍ���
				pModelData->pMesh = NULL;
				pModelData->pBuffMat = NULL;
				pModelData->nNumMat = 0;
				for (int nCnt = 0; nCnt < MAX_MODEL_COLLISION; nCnt++)
				{
					pModelData->CollisionPos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					pModelData->fRadiusCollision[nCnt] = 0;
					pModelData->bCollison[nCnt] = false;
				}
				// X�t�@�C���̓ǂݍ���
				D3DXLoadMeshFromX(pModelData->pFileName,
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&pModelData->pBuffMat,
					NULL,
					&pModelData->nNumMat,
					&pModelData->pMesh);
				D3DXMATERIAL *pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

													// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)pModelData->pBuffMat->GetBufferPointer();
				// �e�N�X�`���̔z��ݒ�
				pModelData->pTextuer = new LPDIRECT3DTEXTURE9[(int)pModelData->nNumMat];

				// �e�N�X�`���̓ǂݍ���
				for (int nCntMatTex = 0; nCntMatTex < (int)pModelData->nNumMat; nCntMatTex++)
				{
					pModelData->pTextuer[nCntMatTex] = NULL;

					if (pMat[nCntMatTex].pTextureFilename != NULL)
					{
						// �e�N�X�`���̐ݒ�
						D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
							pMat[nCntMatTex].pTextureFilename,	// �t�@�C���̖��O
							&pModelData->pTextuer[nCntMatTex]);		// �e�N�X�`���ւ̃|�C���^


					}
				}
				pModelData++;
			}
			if (strcmp(cData, "SETCATCH") == 0)
			{
				int nType = 0;
				int nCatch = 0;
				while (strcmp(cData, "ENDSETCATCH") != 0)
				{
					fgets(&cLine[0], 256, pFile);
					sscanf(&cLine[0], "%s", &cData);
					if (strcmp(cData, "CATCH") == 0)
					{
						sscanf(&cLine[0], "%s %s %d %d", &cData[0], &cData[0], &nType, &nCatch);
						if (nCatch == 1)
						{
							pModelData2[nType].bCatch = true;
						}
					}
				}
			}
			if (strcmp(cData, "SETGETINFO") == 0)
			{// ���擾
				int nType = 0;
				int nGetInfo = 0;
				while (strcmp(cData, "ENDSETGETINFO") != 0)
				{
					fgets(&cLine[0], 256, pFile);
					sscanf(&cLine[0], "%s", &cData);
					if (strcmp(cData, "GETINFO") == 0)
					{
						sscanf(&cLine[0], "%s %s %d %d", &cData[0], &cData[0], &nType, &nGetInfo);
						if (nGetInfo == 1)
						{
							pModelData2[nType].bGetInfo = true;
						}
					}
				}
			}
			if (strcmp(cData, "SETCOLLISION") == 0)
			{
				int nType = 0;
				D3DXVECTOR3 ofset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				float fRadius = 0;
				float fWidth = 0;
				float fDepth = 0;
				float fHeight = 0;
				while (strcmp(cData, "ENDSETCOLLISION") != 0)
				{
					fgets(&cLine[0], 256, pFile);
					sscanf(&cLine[0], "%s", &cData);
					if (strcmp(cData, "COLLISION") == 0)
					{
						sscanf(&cLine[0], "%s %s %d %f %f %f %f %f %f %f", &cData[0], &cData[0], &nType, &ofset.x, &ofset.y, &ofset.z, &fRadius, &fWidth, &fDepth, &fHeight);
						SetCollisionModel(ofset, fRadius, fWidth, fDepth, fHeight, MODELTYPE(nType));
					}
				}
			}
		}
		fclose(pFile);
	}
}
//==============================================================================================================================
// �X�e�[�W�ݒu
//==============================================================================================================================
void SetStagePos(char *cFilename)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FILE *pFile;
	char cLine[MAX_CHAR];
	char cData[MAX_CHAR];
	pFile = fopen(cFilename, "r");
	MeshField *pMeshField = GetMeshField();
	MeshWall *pMeshWall = GetMeshWall();
	Model *pModel = GetModel();
	if (pFile != NULL)
	{
		while (fgets(&cLine[0], MAX_CHAR, pFile) != NULL)
		{
			sscanf(&cLine[0], "%s", &cData);
			if (strcmp(cData, "WALLSET") == 0)
			{
				while (strcmp(cData, "END_WALLSET") != 0)
				{
					fgets(&cLine[0], 256, pFile);
					sscanf(&cLine[0], "%s", &cData);
					if (strcmp(cData, "TEXTYPE") == 0)
					{
						sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &pMeshWall->nType);
					}
					else if (strcmp(cData, "POS") == 0)
					{
						sscanf(&cLine[0], "%s %s %f %f %f", &cData[0], &cData[0], &pMeshWall->pos.x, &pMeshWall->pos.y, &pMeshWall->pos.z);
					}
					else if (strcmp(cData, "ROT") == 0)
					{
						sscanf(&cLine[0], "%s %s %f %f %f", &cData[0], &cData[0], &pMeshWall->rot.x, &pMeshWall->rot.y, &pMeshWall->rot.z);

						if (pMeshWall->rot.y == 90.0f)
						{
							pMeshWall->rot.y = D3DX_PI / 2;
						}
						if (pMeshWall->rot.y == 180.0f)
						{
							pMeshWall->rot.y = D3DX_PI;
						}
						if (pMeshWall->rot.y == -90.0f)
						{
							pMeshWall->rot.y = -D3DX_PI / 2;
						}
					}
					else if (strcmp(cData, "BLOCK") == 0)
					{
						sscanf(&cLine[0], "%s %s %d %d", &cData[0], &cData[0], &pMeshWall->nBlock_X, &pMeshWall->nBlock_Y);
					}
					else if (strcmp(cData, "SIZE") == 0)
					{
						sscanf(&cLine[0], "%s %s %f %f", &cData[0], &cData[0], &pMeshWall->fWidth, &pMeshWall->fHeight);
					}
					else if (strcmp(cData, "CULL") == 0)
					{
						int nCull = 0;
						sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &nCull);
						if (nCull == 0)
						{// �J�����O����
							pMeshWall->bCull = false;
						}
						else
						{// �J�����O���Ȃ�
							pMeshWall->bCull = true;
						}
					}
					else if (strcmp(cData, "COLLISION") == 0)
					{
						int nCollision = 0;
						sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &nCollision);
						if (nCollision == 0)
						{// �J�����O����
							pMeshWall->bCollision = false;
						}
						else
						{// �J�����O���Ȃ�
							pMeshWall->bCollision = true;
						}
					}
				}
				SetMeshWall(pMeshWall->pos, pMeshWall->rot, pMeshWall->nType, pMeshWall->nBlock_X, pMeshWall->nBlock_Y, pMeshWall->fWidth, pMeshWall->fHeight, pMeshWall->bCull);
				pMeshWall++;
			}
			if (strcmp(cData, "FIELDSET") == 0)
			{
				while (strcmp(cData, "END_FIELDSET") != 0)
				{
					fgets(&cLine[0], 256, pFile);
					sscanf(&cLine[0], "%s", &cData);
					if (strcmp(cData, "TEXTYPE") == 0)
					{
						sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &pMeshField->nType);
					}
					else if (strcmp(cData, "POS") == 0)
					{
						sscanf(&cLine[0], "%s %s %f %f %f", &cData[0], &cData[0], &pMeshField->pos.x, &pMeshField->pos.y, &pMeshField->pos.z);
					}
					else if (strcmp(cData, "ROT") == 0)
					{
						sscanf(&cLine[0], "%s %s %f %f %f", &cData[0], &cData[0], &pMeshField->rot.x, &pMeshField->rot.y, &pMeshField->rot.z);
						pMeshField->rot.x /= 57.3248408f;
						pMeshField->rot.y /= 57.3248408f;
						pMeshField->rot.z /= 57.3248408f;
						if (pMeshField->rot.x == 180.0f)
						{
							pMeshField->rot.x = D3DX_PI;
						}
					}
					else if (strcmp(cData, "BLOCK") == 0)
					{
						sscanf(&cLine[0], "%s %s %d %d", &cData[0], &cData[0], &pMeshField->nBlock_X, &pMeshField->nBlock_Z);
					}
					else if (strcmp(cData, "SIZE") == 0)
					{
						sscanf(&cLine[0], "%s %s %f %f", &cData[0], &cData[0], &pMeshField->fWidth, &pMeshField->fDepth);
					}
					else if (strcmp(cData, "SLOPE") == 0)
					{
						sscanf(&cLine[0], "%s %s %f %f", &cData[0], &cData[0], &pMeshField->fSlopeSin, &pMeshField->fSlopeCos);
					}
					else if (strcmp(cData, "CULL") == 0)
					{
						int nCull = 0;
						sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &nCull);
						if (nCull == 0)
						{// �J�����O����
							pMeshField->bCull = false;
						}
						else
						{// �J�����O���Ȃ�
							pMeshField->bCull = true;
						}
					}
					else if (strcmp(cData, "MOVE") == 0)
					{
						sscanf(&cLine[0], "%s %s %f %f", &cData[0], &cData[0], &pMeshField->fTexmove.x, &pMeshField->fTexmove.y);
					}
					else if (strcmp(cData, "COLLISION") == 0)
					{
						int nCollison = 0;
						sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &nCollison);
						if (nCollison == 0)
						{// ����Ȃ�
							pMeshField->bCollision = false;
						}
						else
						{// ���肠��
							pMeshField->bCollision = true;
						}
					}
				}
				SetMeshField(pMeshField->pos, pMeshField->rot, pMeshField->nType, pMeshField->nBlock_X, pMeshField->nBlock_Z, pMeshField->fWidth, pMeshField->fDepth, pMeshField->fSlopeSin, pMeshField->bCull);
				pMeshField++;
			}

			if (strcmp(cData, "SETMODEL") == 0)
			{
				while (strcmp(cData, "ENDSETMODEL") != 0)
				{
					fgets(&cLine[0], 256, pFile);
					sscanf(&cLine[0], "%s", &cData);
					if (strcmp(cData, "POS") == 0)
					{
						sscanf(&cLine[0], "%s %s %f %f %f", &cData[0], &cData[0], &pModel->pos.x, &pModel->pos.y, &pModel->pos.z);
					}
					else if (strcmp(cData, "RANDOMPOS") == 0)
					{
						D3DXVECTOR3 randomPos;
						sscanf(&cLine[0], "%s %s %f %f %f", &cData[0], &cData[0], &randomPos.x, &randomPos.y, &randomPos.z);
						pModel->pos += D3DXVECTOR3((sinf(float(rand() % 624) / 100.0f)*randomPos.x), (cosf(float(rand() % 624) / 100.0f)*randomPos.y), (cosf(float(rand() % 624) / 100.0f)*randomPos.z));
					}
					else if (strcmp(cData, "ROT") == 0)
					{
						sscanf(&cLine[0], "%s %s %f %f %f", &cData[0], &cData[0], &pModel->rot.x, &pModel->rot.y, &pModel->rot.z);
						pModel->rot.x /= 57.3248408f;
						pModel->rot.y /= 57.3248408f;
						pModel->rot.z /= 57.3248408f;
					}
					else if (strcmp(cData, "TYPE") == 0)
					{
						sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &pModel->nType);
					}
					else if (strcmp(cData, "COLLISION") == 0)
					{
						int nCollision = 0;
						sscanf(&cLine[0], "%s %s %d", &cData[0], &cData[0], &nCollision);
						if (nCollision == 0)
						{// ����Ȃ�
							pModel->bCollision = false;
						}
						else
						{// ���肠��
							pModel->bCollision = true;
						}
					}
				}
				SetModel(pModel->pos, pModel->rot, pModel->nType);
				pModel++;
			}
		}
		fclose(pFile);
	}
}
//==============================================================================================================================
// ���z�u
//==============================================================================================================================
void PrintStagePos(void)
{
	FILE *pFileQ;						// �t�@�C���^�̃|�C���^�ϐ�
	Model *pModel = GetModel();
	int nCollision = 0;
	pFileQ = fopen("data/�X�e�[�W���.txt", "w");	// ���̓ǂݍ���
	if (pFileQ != NULL)
	{// �t�@�C�����J������
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++, pModel++)
		{
			if (pModel->bUse == true)
			{
				fprintf(pFileQ, "SETMODEL\n");
				fprintf(pFileQ, "	POS = %.1f %.1f %.1f\n", pModel->pos.x, pModel->pos.y, pModel->pos.z);
				fprintf(pFileQ, "	ROT = %.1f %.1f %.1f\n", pModel->rot.x, pModel->rot.y, pModel->rot.z);
				fprintf(pFileQ, "	TYPE = %d\n", pModel->nType);
				if (pModel->bCollision == false)
				{
					nCollision = 0;
				}
				else
				{
					nCollision = 1;
				}
				fprintf(pFileQ, "	COLLISION = %d\n", nCollision);
				fprintf(pFileQ, "ENDSETMODEL\n");
			}
		}
		fclose(pFileQ);
	}
}
//==============================================================================================================================
// �Q�[���̏�Ԃ̐ݒ�
//==============================================================================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}
//==============================================================================================================================
// �Q�[���̏�Ԃ̎擾
//==============================================================================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}
int GetGameStateCounter(void)
{
	return g_nCounterGameState;
}
//==============================================================================================================================
// �|�[�Y��Ԃ�ς���
//==============================================================================================================================
void ReleaseGamePause(void)
{
	g_bPause = g_bPause ? false : true;
}
//==============================================================================================================================
// �|�[�Y�擾
//==============================================================================================================================
bool GetPause(void)
{
	return g_bPause;
}
bool GetPauseView(void)
{
	return g_bPauseView;
}

//==============================================================================================================================
// �J�b�g�C���g�p�̐ݒ�
//==============================================================================================================================
void SetSpecalUse(bool bSpesal)
{
	g_bGameSpecial = bSpesal;
}

//==============================================================================================================================
// ���Ԃ̎擾
//==============================================================================================================================
int GetTimeGame(void)
{
	return g_nCntGame;
}
//==============================================================================================================================
// �^�R�Ă��Q�b�g�s�擾
//============================================================================================================================
bool GetTakoyaki(void)
{
	return g_bGetTakoyaki;
}
//==============================================================================================================================
// �^�R�Ă��Q�b�g�������ǂ���
//============================================================================================================================
void SetTakoyaki(bool bSet)
{
	g_bGetTakoyaki = bSet;
	DeleteBillboard(BILLBOARDTYPE_EVENT);
}
//==============================================================================================================================
// �`���R�o�i�i�Q�b�g�s�擾
//============================================================================================================================
bool GetChoco(void)
{
	return g_bGetChoco;
}
//==============================================================================================================================
// �`���R�o�i�i�Q�b�g�������ǂ���
//============================================================================================================================
void SetChoco(bool bSet)
{
	g_bGetChoco = bSet;
	DeleteBillboard(BILLBOARDTYPE_EVENT_1);
}
//==============================================================================================================================
// ���Q�b�g�s�擾
//============================================================================================================================
bool GetFish(void)
{
	return g_bGetFish;
}
//==============================================================================================================================
// ���Q�b�g�������ǂ���
//============================================================================================================================
void SetFish(bool bSet)
{
	g_bGetFish = bSet;
	DeleteBillboard(BILLBOARDTYPE_EVENT_2);
}