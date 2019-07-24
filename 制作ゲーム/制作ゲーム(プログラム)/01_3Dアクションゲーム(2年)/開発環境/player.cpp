////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �v���C���[���� [player.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "model.h"
#include "fade.h"
#include "meshField.h"
#include "meshWall.h"
#include "line.h"
#include "orbit.h"
#include "gamepad.h"
#include "sound.h"
#include "game.h"
#include "effect.h"
#include "life.h"
#include "orbit.h"
#include "guard.h"
#include "effectUP.h"
#include "Item.h"
#include "SP.h"
#include "cutin.h"
#include "event.h"
#include "billboard.h"
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define DOWN_SPEED						(0.4f)	// ������
#define PLAYER_ROT_SPEED_NORMAL			(0.3f)	// �ʏ펞�̊p�x��ς����
#define PLAYER_ROT_SPEED_ATTACK			(0.03f)	// �U�����̊p�x��ς����
#define GRAVITY_SPEED					(0.6f)	// �d�͉��Z�X�s�[�h
#define INIT_JUMP_SPEED					(7)		// �W�����v��
#define INIT_MOVE_SPEED					(0.3f)	// �ړ���
#define PLAYER_MOTION_STEP_MOVE_SPEED	(5.0f)	// �X�e�b�v�̃X�s�[�h
#define BLEND_FRAME						(3)		// �u�����h
#define ATTACKDAMAGE					(1)		// �A�^�b�N�̃_���[�W��
#define WARKZONE						(50)	// �����̃]�[��
#define PLAYER_MOTION_MOVE_ZONE			(1.0f)	// �����̃��[�V�����]�[��
#define MAX_SKY							(1.0f)	// �K�[�h�̍ő僉�C�t
#define MAX_DEPTH						(475)
#define MAX_CAMERASTATE					(30)
#define DOWN_JUMP_SPEED					(1.5f)	// �W�����v
#define CUT_IN_TIME	(60 )
#define FLAM_MATURI (20)
#define FLAM_AMANO (45)
#define FLAM_GOJOU (40)
#define FLAM_MOMIJI (40)
#define FLAM_DONROID (35)
#define MATURI (g_aPlayer[nIdy].type == PLAYERTYPE_MATURI)
#define AMANO (g_aPlayer[nIdy].type == PLAYERTYPE_AMANO)
#define GOJOU (g_aPlayer[nIdy].type == PLAYERTYPE_GOJOU)
#define MOMIJI (g_aPlayer[nIdy].type == PLAYERTYPE_MOMIJI)
#define DONROID (g_aPlayer[nIdy].type == PLAYERTYPE_DONROID)
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void AllReleaseAttack(int nIdy);
bool bAttackOn(int nIdy);
void Special(void);
void StartMove(void);
void SetSpecialUse(bool bSpecial);
void SetPlayerVoice(PLAYERTYPE type, PlayerMotionType motion);
void PlayerLifeZero(int nIdy,float fAngle, float fDamageH, float fDamageV);
//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
Player g_aPlayer[MAX_PLAYER];
PlayerData g_aPlayerData[PLAYERTYPE_MAX];
int g_nNumAll = 0;
int g_nCutInTime;
int g_nSpecialPlayer;
bool g_bCutIn;
bool g_bStartMove;
bool g_bStartCutIn;

//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ʒu�E�����̏����ݒ�
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		g_aPlayer[nCnt].pos = D3DXVECTOR3(0.0f + nCnt * 100, 0.0f, 0.0f);		// ���W
		g_aPlayer[nCnt].posOld = D3DXVECTOR3(0.0f + nCnt * 100, 0.0f, 0.0f);		// �O��̍��W
		g_aPlayer[nCnt].Diffpos = D3DXVECTOR3(0.0f + nCnt * 100, 0.0f, 0.0f);	// ���W�̍���
		g_aPlayer[nCnt].Initpos = D3DXVECTOR3(0.0f + nCnt * 100, 0.0f, 0.0f);	// �������W
		g_aPlayer[nCnt].nMotionType = PLAYER_MOTION_TYPE_NEUTRAL;	// ���[�V�����^�C�v
		g_aPlayer[nCnt].nMotionTypeOld = PLAYER_MOTION_TYPE_MAX;	// �O��̃��[�V�����^�C�v
		g_aPlayer[nCnt].nMotionGetCol = PLAYER_MOTION_TYPE_NEUTRAL;	// ���[�V�����^�C�v
		g_aPlayer[nCnt].nMotionGetColOld = PLAYER_MOTION_TYPE_MAX;	// �O��̃��[�V�����^�C�v
		g_aPlayer[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
		g_aPlayer[nCnt].Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]�̍���
		g_aPlayer[nCnt].Destrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړI�̉�]
		g_aPlayer[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]
		for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
		{// ��
			g_aPlayer[nCnt].bSound[nCntSound] = false;
		}
		;		g_aPlayer[nCnt].state = PLAYERSTATE_NONE;
		g_aPlayer[nCnt].nCntState = 0;
		g_aPlayer[nCnt].pMeshFieldLand = NULL;
		g_aPlayer[nCnt].pModel = NULL;
		g_aPlayer[nCnt].pModelAtkData = NULL;
		g_aPlayer[nCnt].pModelAtk = NULL;
		for (int nbMotion = 0; nbMotion < PLAYER_BOOL_MAX; nbMotion++)
		{
			g_aPlayer[nCnt].bMotionState[nbMotion] = false;
			g_aPlayer[nCnt].bMotionStateOld[nbMotion] = false;
		}
		for (int nbMotion = 0; nbMotion < PLAYER_ATTACK_TYPE_MAX; nbMotion++)
		{
			g_aPlayer[nCnt].bAttackType[nbMotion]=false;
		}
		g_aPlayer[nCnt].bBlend = false;
		g_aPlayer[nCnt].nDamage = 0;
		g_aPlayer[nCnt].bJump = false;							// �W�����v
		g_aPlayer[nCnt].bCatch = false;							// �E���Ă��邩�ǂ���
		g_aPlayer[nCnt].bCatchOld = false;							// �E���Ă��邩�ǂ���
		g_aPlayer[nCnt].nFlyCounter = 0;						// ���ł��鎞��
		g_aPlayer[nCnt].fRotSpeed = 0.0f;						// ��]�̌����X�s�[�h
		g_aPlayer[nCnt].nAirCounter = 0;						// ���V���̍U������J�E���^�[
		g_aPlayer[nCnt].nLoopCounter = 0;						// ���[�v�J�E���^�[
		g_aPlayer[nCnt].nIdy = nCnt;							// �ԍ�
		g_aPlayer[nCnt].nKeyCounter = 0;		// �L�[��
		g_aPlayer[nCnt].nFrameCounter = 0;		// �t���[����
		g_aPlayer[nCnt].nFrameAllCounter = 0;	// �ő�t���[��
		g_aPlayer[nCnt].nFrame = 0;				// �t���[��
		g_aPlayer[nCnt].fGuardLife = MAX_SKY;		// �K�[�h�̃��C�t
		g_aPlayer[nCnt].bUse = false;
		g_aPlayer[nCnt].bDraw = true;			// �f���Ă邩�ǂ���
		g_aPlayer[nCnt].fPulsLife = 0;			// �A�C�e���ő����郉�C�t
		g_aPlayer[nCnt].fPulsAttack = 0;		// �A�C�e���ŉ��Z�����U����
		g_aPlayer[nCnt].fPulsSpeed = 0;			// �A�C�e���ő�����X�s�[�h
		g_aPlayer[nCnt].nItemTime = 0;			// �A�C�e���p������
		g_aPlayer[nCnt].nSp = MAX_SP;				// �X�y�V����
		g_aPlayer[nCnt].bSp = false;				// ���W
		g_aPlayer[nCnt].nComboCounter = 0;			// �R���{�J�E���^�[
		g_aPlayer[nCnt].bCombo = false;				// �R���{
		g_aPlayer[nCnt].nCntEmote = 0;				// �G���[�g
		g_aPlayer[nCnt].nStopTime = 0;				// ����s�\����
		g_aPlayer[nCnt].bSpecial = false;
	}
	g_aPlayer[0].col = D3DXCOLOR(0.92f, 0.43f, 0.62f, 1.0f);	// �s���N
	g_aPlayer[1].col = D3DXCOLOR(0.55f, 0.78f, 1.0f, 1.0f);		// ��
	g_aPlayer[2].col = D3DXCOLOR(1.0f, 1.0f, 0.1f, 1.0f);		// ���F
	g_aPlayer[3].col = D3DXCOLOR(0.1f, 1.0f, 0.1f, 1.0f);		// ��
	g_nCutInTime = 0;
	g_nSpecialPlayer = 0;
	g_bCutIn = false;
	g_bStartMove = false;
	g_bStartCutIn = false;


	for (int nCnt = 0; nCnt < PLAYERTYPE_MAX; nCnt++)
	{
		for (int nCntParts = 0; nCntParts < g_aPlayerData[nCnt].nNumParts; nCntParts++)
		{// Key - ���� �Ԃ̍����v�Z
			g_aPlayerData[nCnt].aModel[nCntParts].rot = g_aPlayerData[nCnt].aMotion[PLAYER_MOTION_TYPE_JUMP].aKey[0].aPartsKey[nCntParts].rot;
		}
	}
	g_nNumAll = 0;
}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < PLAYERTYPE_MAX; nCnt++)
	{
		for (int nCntModel = 0; nCntModel < g_aPlayerData[nCnt].nNumParts; nCntModel++)
		{
			// ���b�V���̊J��
			if (g_aPlayerData[nCnt].aModel[nCntModel].pMesh != NULL)
			{
				g_aPlayerData[nCnt].aModel[nCntModel].pMesh->Release();
				g_aPlayerData[nCnt].aModel[nCntModel].pMesh = NULL;
			}
			// �}�e���A���̊J��
			if (g_aPlayerData[nCnt].aModel[nCntModel].pBuffMat != NULL)
			{
				g_aPlayerData[nCnt].aModel[nCntModel].pBuffMat->Release();
				g_aPlayerData[nCnt].aModel[nCntModel].pBuffMat = NULL;
			}
			// �e�N�X�`���̊J��
			for (int nCntMat = 0; nCntMat < int(g_aPlayerData[nCnt].aModel[nCntModel].nNumMat); nCntMat++)
			{
				for (int nCntCol = 0; nCntCol < PLAYERCOLOR_MAX; nCntCol++)
				{
					if (g_aPlayerData[nCnt].aModel[nCntModel].pTextuer[nCntCol][nCntMat] != NULL)
					{
						g_aPlayerData[nCnt].aModel[nCntModel].pTextuer[nCntCol][nCntMat]->Release();
						g_aPlayerData[nCnt].aModel[nCntModel].pTextuer[nCntCol][nCntMat] = NULL;
					}
				}
			}
		}
	}

}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdatePlayer(int nIdy)
{
	GamePad *pGamePad = GetgamePadStick();
	MeshField *pMeshField = GetMeshField();
	Camera *pCamera = GetCamera();
	Model *pModel = GetModel();

	if (g_bStartCutIn == true)
	{
		Special();						//�J�b�g�C��
	}

	if (g_aPlayer[nIdy].bUse&& !g_aPlayer[nIdy].bSpecial)
	{
		// �O��̈ʒu �^�C�v
		g_aPlayer[nIdy].posOld = g_aPlayer[nIdy].pos;
		g_aPlayer[nIdy].nMotionTypeOld = g_aPlayer[nIdy].nMotionType;
		g_aPlayer[nIdy].bCatchOld = g_aPlayer[nIdy].bCatch;
		g_aPlayer[nIdy].nItemTime--;	// �A�C�e���̎��Ԍ���
		if (g_aPlayer[nIdy].nItemTime <= 0)
		{// �A�C�e���̎���
			g_aPlayer[nIdy].fPulsLife = 0;			// �A�C�e���ő����郉�C�t
			g_aPlayer[nIdy].fPulsAttack = 0;		// �A�C�e���ŉ��Z�����U����
			g_aPlayer[nIdy].fPulsSpeed = 0;			// �A�C�e���ő�����X�s�[�h
			g_aPlayer[nIdy].MoveSpeed = g_aPlayerData[g_aPlayer[nIdy].type].MoveSpeed;

		}
		for (int nbMotion = 0; nbMotion < PLAYER_BOOL_MAX; nbMotion++)
		{// �O��̃��[�V����
			g_aPlayer[nIdy].bMotionStateOld[nbMotion] = g_aPlayer[nIdy].bMotionState[nbMotion];
		}
		g_aPlayer[nIdy].nCntEmote--;
		if (g_aPlayer[nIdy].nCntEmote <= 0)
		{
			g_aPlayer[nIdy].nCntEmote = 0;
			g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_WIN] = false;
		}
		switch (g_aPlayer[nIdy].state)
		{
		case PLAYERSTATE_NONE:

			if (g_nNumAll <= 1&& GetGameState() == GAMESTATE_END)
			{
				g_aPlayer[nIdy].rot.y = 0.0f;
				g_aPlayer[nIdy].Destrot.y = 0.0f;
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_WIN] = true;
				pCamera[0].nState = CAMERASTATE_SPECIAL;
			}
			break;
		case PLAYERSTATE_DAMAGESTART:
			g_aPlayer[nIdy].state = PLAYERSTATE_DAMAGE;
			break;
		case PLAYERSTATE_DAMAGE:
			g_aPlayer[nIdy].nCntState--;
			if (g_aPlayer[nIdy].nCntState <= 0)
			{
				g_aPlayer[nIdy].state = PLAYERSTATE_NONE;
			}
			break;
		case PLAYERSTATE_FALL:	// ����
			g_aPlayer[nIdy].move.y = 0;
			g_aPlayer[nIdy].Environment = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			AllReleaseAttack(nIdy);
			for (int nbMotion = 0; nbMotion < PLAYER_BOOL_MAX; nbMotion++)
			{
				g_aPlayer[nIdy].bMotionState[nbMotion] = false;
				g_aPlayer[nIdy].bMotionStateOld[nbMotion] = false;
			}
			g_aPlayer[nIdy].nCntState--;
			if (g_aPlayer[nIdy].nCntState <= 0)
			{
				g_aPlayer[nIdy].state = PLAYERSTATE_NONE;
			}
			break;
		case PLAYERSTATE_CRASHSTART:	// ����
			g_aPlayer[nIdy].nCntState--;
			g_aPlayer[nIdy].move.x = 0;
			g_aPlayer[nIdy].move.z = 0;
			if (g_aPlayer[nIdy].nCntState <= 0)
			{
				g_aPlayer[nIdy].state = PLAYERSTATE_CRASH;
				g_aPlayer[nIdy].nCntState = 300;

			}
			break;
		case PLAYERSTATE_CRASH:	// ����
			g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CRASH] = true;	// ����
			g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] = false;
			g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP] = false;

			g_aPlayer[nIdy].nCntState--;
			g_aPlayer[nIdy].move.x = 0;
			g_aPlayer[nIdy].move.z = 0;
			if ((g_aPlayer[nIdy].nCntState + 1) % 10 == 0&& g_aPlayer[nIdy].nCntState >=60)
			{
				SetEffect(D3DXVECTOR3(g_aPlayer[nIdy].aModel[3].mtxWorld._41 +sinf(SetRandomEffect())*5, g_aPlayer[nIdy].aModel[3].mtxWorld._42 + float(rand()%50),
					g_aPlayer[nIdy].aModel[3].mtxWorld._43 -g_aPlayer[nIdy].fRadiusWidth + cosf(SetRandomEffect()) * 5),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
					float(rand()%50+5.0f), (rand()%100+30), EFFECTTYPE_CRASH);
			}
			if (g_aPlayer[nIdy].nCntState <= 0)
			{
				g_aPlayer[nIdy].state = PLAYERSTATE_NONE;
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CRASH] = false;
				g_aPlayer[nIdy].fGuardLife = 0.5f;
			}

			break;
		case PLAYERSTATE_INVINCIBLE:
			g_aPlayer[nIdy].nCntState--;
			if (g_aPlayer[nIdy].nCntState % 2 == 0)
			{// �_��
				g_aPlayer[nIdy].bDraw = g_aPlayer[nIdy].bDraw ? false : true;
			}
			if (g_aPlayer[nIdy].nCntState <= 0)
			{
				g_aPlayer[nIdy].bDraw = true;
				g_aPlayer[nIdy].state = PLAYERSTATE_NONE;
			}
			break;
		case PLAYERSTATE_DEATH:
			DeleteShadow(g_aPlayer[nIdy].nIdyShadow);
			g_aPlayer[nIdy].move = D3DXVECTOR3(0, 0, 0);
			UnSetGuard(nIdy, 1.0f);
			g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] = true;
			if (g_nNumAll <= 1)
			{
				if (GetGameState() != GAMESTATE_END)
				{
					SetGameState(GAMESTATE_END);
				}
			}
			break;
		}
		if (g_aPlayer[nIdy].pos.y <= -500&&g_aPlayer[nIdy].state != PLAYERSTATE_DEATH)
		{// ���ɗ������玀��
			g_aPlayer[nIdy].fLife -= 5;
			GetPlayerLife((int)g_aPlayer[nIdy].fLife, nIdy);
			if (g_aPlayer[nIdy].fLife <= 0)
			{
				g_aPlayer[nIdy].bUse = false;
				g_nNumAll--;
				g_aPlayer[nIdy].state = PLAYERSTATE_DEATH;
			}
			else
			{
				g_aPlayer[nIdy].pos.y = 300;
				g_aPlayer[nIdy].posOld.y = 300;
				g_aPlayer[nIdy].pos.x = 0;
				g_aPlayer[nIdy].pos.z = 0;
				g_aPlayer[nIdy].nCntState = 30;
				g_aPlayer[nIdy].state = PLAYERSTATE_FALL;
				SetPlayerVoice(g_aPlayer[nIdy].type, PLAYER_MOTION_TYPE_MAX);
			}
		}
		switch (pCamera[0].nState)
		{
		case CAMERASTATE_NONE:
			break;
		case CAMERASTATE_SPECIAL:
			if (g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_SPECIAL)
			{
				pCamera[0].posRDest = g_aPlayer[nIdy].pos;
			}
			if (g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_WIN)
			{
				pCamera[0].posRDest = g_aPlayer[nIdy].pos;
			}
			break;

		}
		if (g_aPlayer[nIdy].state != PLAYERSTATE_DEATH&&g_aPlayer[nIdy].state != PLAYERSTATE_CRASH)
		{// �����Ă���Ȃ�
			if (GetMode() != MODE_RESULT&&GetMode() != MODE_CHARACTER&&GetGameState() != GAMESTATE_END)
			{
				if (pCamera->nState == CAMERASTATE_NONE || pCamera->nState == CAMERASTATE_SPECIAL)
				{
					if (!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_WIN])
					{
						PlayerController(nIdy);
					}
				}
				// �_���[�W�̎��̌v�Z
				if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] || g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_DAMAGE]
					|| g_aPlayer[nIdy].state == PLAYERSTATE_DAMAGE)
				{// ������ї͂��܂���������
					if (g_aPlayer[nIdy].fFlyPower.x >= 0.1f ||
						g_aPlayer[nIdy].fFlyPower.x <= -0.1f)
					{// ���������̐�����ї͂�����Ȃ�
						g_aPlayer[nIdy].move.x = g_aPlayer[nIdy].fFlyPower.x;	// ������ї͂����Z
					}
					if (g_aPlayer[nIdy].fFlyPower.z >= 0.1f ||
						g_aPlayer[nIdy].fFlyPower.z <= -0.1f)
					{// ���������̐�����ї͂�����Ȃ�
						g_aPlayer[nIdy].move.z = g_aPlayer[nIdy].fFlyPower.z;	// ������ї͂����Z
					}

					if (g_aPlayer[nIdy].nFlyCounter > 0)
					{// ������ԃJ�E���^�[��0���傫��������
						g_aPlayer[nIdy].fFlyPower.y -= 0.5f;
						if (g_aPlayer[nIdy].fFlyPower.y > 0.0f)
						{// �W�����v�͂��܂���������
							g_aPlayer[nIdy].move.y = g_aPlayer[nIdy].fFlyPower.y;			// �㏸���Ă���
						}
						if (rand() % 2 == 0)
						{// ���G�t�F�N�g
							float fDirection[3] = { SetRandomEffect(),SetRandomEffect(),SetRandomEffect() };
							SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(fDirection[0]) * 10, cosf(fDirection[1]) * 10, cosf(fDirection[2]) * 10),
								D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), g_aPlayer[nIdy].col, float(rand() % 80 + 10), 10, EFFECTTYPE_SMOKE);
						}
					}
					for (int nCntAttack = 0; nCntAttack < PLAYER_ATTACK_TYPE_MAX; nCntAttack++)
					{// �U���̎�ޕ����[�v
						if (g_aPlayer[nIdy].bAttackType[nCntAttack] == true)
						{// �U������������
							g_aPlayer[nIdy].move.x = 0.0f;	// ������ї͂����Z
							g_aPlayer[nIdy].move.z = 0.0f;	// ������ї͂����Z

						}
					}

				}

				// �����̉�]���x�̌���
				if (g_aPlayer[nIdy].nMotionType != PLAYER_MOTION_TYPE_GETUP)
				{// �N���オ�莞����Ȃ����
					g_aPlayer[nIdy].fRotSpeed = PLAYER_ROT_SPEED_NORMAL;			// �ʏ�̉�]���x������
					for (int nCntAttack = 0; nCntAttack < PLAYER_ATTACK_TYPE_MAX; nCntAttack++)
					{// �U���̎�ޕ����[�v
						if (g_aPlayer[nIdy].bAttackType[nCntAttack] == true)
						{// �U������������
							g_aPlayer[nIdy].fRotSpeed = PLAYER_ROT_SPEED_ATTACK;	// �����̉�]���x��x������
						}
					}

				}

			}
		}
		if (g_aPlayer[nIdy].nMotionType != g_aPlayer[nIdy].nMotionTypeOld)
		{
			g_aPlayer[nIdy].fRotSpeed = PLAYER_ROT_SPEED_NORMAL;			// �ʏ�̉�]���x������

		}
		// �d�͉��Z
		if (GetMode() != MODE_CHARACTER)
		{
			g_aPlayer[nIdy].move.y += -GRAVITY_SPEED;

		}

		// �ړ��ʉ��Z
		g_aPlayer[nIdy].pos += g_aPlayer[nIdy].Environment;
		g_aPlayer[nIdy].pos += g_aPlayer[nIdy].move;
		// �����X�V
		if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] == false&&g_aPlayer[nIdy].state != PLAYERSTATE_DEATH)
		{
			if (GetEventType() == EVENTTYPE_RAIN)
			{
				g_aPlayer[nIdy].move.x += (0 - g_aPlayer[nIdy].move.x)*0.3f;
				g_aPlayer[nIdy].move.z += (0 - g_aPlayer[nIdy].move.z)*0.3f;
			}
			else
			{
				g_aPlayer[nIdy].move.x += (0 - g_aPlayer[nIdy].move.x)*DOWN_SPEED;
				g_aPlayer[nIdy].move.z += (0 - g_aPlayer[nIdy].move.z)*DOWN_SPEED;
			}
			g_aPlayer[nIdy].Environment.x += (0 - g_aPlayer[nIdy].Environment.x)*DOWN_SPEED;
			g_aPlayer[nIdy].Environment.z += (0 - g_aPlayer[nIdy].Environment.z)*DOWN_SPEED;

		}

		//--------------------------/ ���f���̓������Ȃ߂炩�ɂ��� /---------------------------------------------------------------------------------------//
		if (g_aPlayer[nIdy].Destrot.y > D3DX_PI)
		{// ������3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].Destrot.y -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].Destrot.y < -D3DX_PI)
		{// ������-3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].Destrot.y += D3DX_PI * 2.0f;
		}
		g_aPlayer[nIdy].Diffrot.y = g_aPlayer[nIdy].Destrot.y - g_aPlayer[nIdy].rot.y;// ���݂̊p�x�ƖړI�̊p�x�̍���
		if (g_aPlayer[nIdy].Diffrot.y > D3DX_PI)
		{// ������3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].Diffrot.y -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].Diffrot.y < -D3DX_PI)
		{// ������-3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].Diffrot.y += D3DX_PI * 2.0f;
		}
		g_aPlayer[nIdy].rot.y += g_aPlayer[nIdy].Diffrot.y * g_aPlayer[nIdy].fRotSpeed;	// �p�x�̉��Z
		if (g_aPlayer[nIdy].rot.y > D3DX_PI)
		{// ���݂̊p�x��3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].rot.y -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].rot.y < -D3DX_PI)
		{// ���݂̊p�x��-3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].rot.y += D3DX_PI * 2.0f;
		}
		//----------------------------------/ �����蔻�� /---------------------------------------------------------------------------------------//
			// ���b�V���t�B�[���h
		if (CollisionMeshField(&g_aPlayer[nIdy].pos, &g_aPlayer[nIdy].posOld, &g_aPlayer[nIdy].move,
			g_aPlayer[nIdy].fRadiusWidth, g_aPlayer[nIdy].fRadiusHeight, &g_aPlayer[nIdy].pMeshFieldLand) == true)
		{
			Shadow *pShadow = GetShadow();
			pShadow[g_aPlayer[nIdy].nIdyShadow].pos.y = g_aPlayer[nIdy].pos.y + 0.1f;
			pShadow[g_aPlayer[nIdy].nIdyShadow].col.a = 1.0f;
			g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] = false;
			g_aPlayer[nIdy].bJump = false;
			g_aPlayer[nIdy].nAirCounter = 0;// �󒆍U������J�E���^�[

			if (g_aPlayer[nIdy].state != PLAYERSTATE_DEATH&&g_aPlayer[nIdy].state != PLAYERSTATE_CRASH)
			{
				if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] == true)
				{
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] = false;
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP] = true;
				}
			}
			if (!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] && g_aPlayer[nIdy].bMotionStateOld[PLAYER_BOOL_JUMP])
			{// ���n����
				for (int nCntEffect = 0; nCntEffect < 2; nCntEffect++)
				{// ���n�G�t�F�N�g
					float nDirection = SetRandomEffect();
					float nDirection2 = SetRandomEffect();
					SetEffect(g_aPlayer[nIdy].pos, D3DXVECTOR3(sinf(nDirection) * float(rand() % 10 + 3), cosf(rand() % 314 / 100.0f) * 0, cosf(nDirection) *  float(rand() % 10 + 3)), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, float(rand() % 100 / 100.0f)), float(rand() % 50) + 10, 30, EFFECTTYPE_SMOKE);
					SetEffect(g_aPlayer[nIdy].pos, D3DXVECTOR3(sinf(nDirection2) *  float(rand() % 10 + 3), cosf(rand() % 314 / 100.0f) * 0, cosf(nDirection2) *  float(rand() % 10 + 3)), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, float(rand() % 100 / 100.0f)), float(rand() % 50) + 10, 30, EFFECTTYPE_SMOKE);
				}
				PlaySound(SOUND_LABEL_LAND);
			}
		}
		else
		{
		}
		if (g_aPlayer[nIdy].pMeshFieldLand != NULL)
		{// ���ɏ���Ă���
			if ((g_aPlayer[nIdy].move.x > 1.0f || g_aPlayer[nIdy].move.z > 1.0f ||
				g_aPlayer[nIdy].move.x < -1.0f || g_aPlayer[nIdy].move.z < -1.0f))
			{// �����Ă���
			}
			else
			{
			}
		}
		// �v���C���[���m
		PlayerOverLap(g_aPlayer[nIdy].nIdy);

		// ���f��
		if (CollisionModelMinMax(&g_aPlayer[nIdy].pos, &g_aPlayer[nIdy].posOld, &g_aPlayer[nIdy].move, g_aPlayer[nIdy].fRadiusWidth, g_aPlayer[nIdy].fRadiusHeight, &g_aPlayer[nIdy].pModel) == 2)
		{// ��ɂ̂�
			Shadow *pShadow = GetShadow();
			pShadow[g_aPlayer[nIdy].nIdyShadow].pos.y = g_aPlayer[nIdy].pos.y + 0.1f;
			pShadow[g_aPlayer[nIdy].nIdyShadow].col.a = 1.0f;
			g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] = false;
			g_aPlayer[nIdy].bJump = false;
			g_aPlayer[nIdy].nAirCounter = 0;// �󒆍U������J�E���^�[
			if (g_aPlayer[nIdy].state != PLAYERSTATE_DEATH&&g_aPlayer[nIdy].state != PLAYERSTATE_CRASH)
			{
				if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] == true)
				{
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] = false;
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP] = true;
				}
			}
			if (!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] && g_aPlayer[nIdy].bMotionStateOld[PLAYER_BOOL_JUMP])
			{// ���n����
				for (int nCntEffect = 0; nCntEffect < 20; nCntEffect++)
				{// ���n�G�t�F�N�g
					SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(SetRandomEffect()) * 10, 0.0f, cosf(SetRandomEffect()) * 10),
						D3DXVECTOR3(sinf(SetRandomEffect()) * float(rand()%5) , cosf(SetRandomEffect())*0.5f, cosf(SetRandomEffect()) * float(rand() % 5)),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.9f, 0.9f, 1.0f), float(rand() % 30), 0, EFFECTTYPE_WALK);
				}
				PlaySound(SOUND_LABEL_LAND);
			}
			if ((g_aPlayer[nIdy].move.x > g_aPlayer[nIdy].MoveSpeed || g_aPlayer[nIdy].move.z > g_aPlayer[nIdy].MoveSpeed ||
				g_aPlayer[nIdy].move.x < -g_aPlayer[nIdy].MoveSpeed || g_aPlayer[nIdy].move.z < -g_aPlayer[nIdy].MoveSpeed))
			{// �����Ă���@�����@����
			 // �G�Ɠ�������̂̋���
				float fPosX = (g_aPlayer[nIdy].pos.x - 200);
				float fPosZ = (g_aPlayer[nIdy].pos.z - 200);
				float fRadiusA = fPosX*fPosX  + fPosZ*fPosZ;
				float fRadiusB = (150 + 150)* (150 + 150);

				if (fRadiusB > fRadiusA&&
					-fRadiusB < fRadiusA)
				{// �΂̏�
					SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(SetRandomEffect()) * 10, cosf(SetRandomEffect()), cosf(SetRandomEffect()) * 10),
						D3DXVECTOR3(sinf(SetRandomEffect()) * 2 + sinf(g_aPlayer[nIdy].rot.y), cosf(SetRandomEffect()), cosf(SetRandomEffect()) * 2 + cosf(g_aPlayer[nIdy].rot.y)),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.9f, 0.9f, 1.0f), float(rand() % 30), 0, EFFECTTYPE_WALK);
					if (rand() % 5 == 0){
						SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(SetRandomEffect()) * 10, cosf(SetRandomEffect()), cosf(SetRandomEffect()) * 10)+ D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y) * 30, cosf(SetRandomEffect()), cosf(g_aPlayer[nIdy].rot.y) * 30),
							D3DXVECTOR3(sinf(SetRandomEffect()) * 2 + sinf(g_aPlayer[nIdy].rot.y), 0.5f, cosf(SetRandomEffect()) * 2 + cosf(g_aPlayer[nIdy].rot.y)),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.9f, 0.9f, 2.0f), float(rand() % 4) * 10, 0, EFFECTTYPE_CARTOON_TA);}
				}
				else
				{// �y
					SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(SetRandomEffect()) * 10, cosf(SetRandomEffect()), cosf(SetRandomEffect()) * 10),
						D3DXVECTOR3(sinf(SetRandomEffect()) * 2 + sinf(g_aPlayer[nIdy].rot.y), cosf(SetRandomEffect()), cosf(SetRandomEffect()) * 2 + cosf(g_aPlayer[nIdy].rot.y)),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.9f, 0.9f, 1.0f), float(rand() % 30), 0, EFFECTTYPE_DIRTY);
				}

			}
			else
			{
			}
		}
		else
		{
			if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] == true&&g_aPlayer[nIdy].move.y == 0)
			{
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] = false;
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP] = true;
			}
		}
		if (g_aPlayer[nIdy].pos.z >= MAX_DEPTH)
		{// ���s�����
			g_aPlayer[nIdy].pos.z = MAX_DEPTH;
		}
		// ���b�V���E�H�[��
		if (CollisionMeshWall(&g_aPlayer[nIdy].pos, &g_aPlayer[nIdy].posOld, &g_aPlayer[nIdy].move, g_aPlayer[nIdy].fRadiusWidth, g_aPlayer[nIdy].fRadiusHeight))
		{


		}



		if (g_aPlayer[nIdy].bCatch == true)
		{
			if (g_aPlayer[nIdy].pModelAtk->bUse)
			{
				g_aPlayer[nIdy].pModelAtk->rot = g_aPlayer[nIdy].rot;
				g_aPlayer[nIdy].pModelAtk->pos = D3DXVECTOR3(g_aPlayer[nIdy].aModel[9].mtxWorld._41, g_aPlayer[nIdy].aModel[9].mtxWorld._42, g_aPlayer[nIdy].aModel[9].mtxWorld._43);
				g_aPlayer[nIdy].pModelAtk->mtxWorld = g_aPlayer[nIdy].aModel[9].mtxWorld;
			}
			else
			{
				g_aPlayer[nIdy].bCatch = false;
			}
		}
		if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] != g_aPlayer[nIdy].bMotionStateOld[PLAYER_BOOL_JUMP])
		{// �O��ƍ���̃W�����v���[�V������������璅�n���[�V����
			g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_LANDING] = true;
		}
		//------------------------------------/ ��{���[�V���� /-----------------------------------------------------------------/
		//if (g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK] == false)

			if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CRASH])
			{// ������ԂȂ�
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_CRASH;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CATCH])
			{// �E����ԂȂ�
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_CATCH;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_THROW])
			{// �������ԂȂ�
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_THROW;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP] )
			{// �|��Ă��ԂȂ�
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_GETUP;
				g_aPlayer[nIdy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] )
			{// �_���[�W(�������)���Ȃ�
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_FLY;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_DAMAGE] )
			{// �_���[�W(������)���Ȃ�
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_DAMAGE;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] )
			{// �v���C���[���W�����v���Ȃ�
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_JUMP;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_LANDING] )
			{// ���n���Ȃ�
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_LANDING;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD])
			{// �K�[�h���Ȃ�
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_GUARD;
			}
			else if (g_aPlayer[nIdy].move.x > PLAYER_MOTION_MOVE_ZONE ||
				g_aPlayer[nIdy].move.x < -PLAYER_MOTION_MOVE_ZONE ||
				g_aPlayer[nIdy].move.z >  PLAYER_MOTION_MOVE_ZONE ||
				g_aPlayer[nIdy].move.z < -PLAYER_MOTION_MOVE_ZONE)
			{// �v���C���[�������Ă���Ƃ�
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_MOVE;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_WIN])
			{// �������[�V�����Ȃ�
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_WIN;
			}
			else
			{// �v���C���[�������ĂȂ��Ƃ�
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_NEUTRAL;
			}
		//--------------------------- �U�����[�V���� -----------------------------------------------------//
		if (g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK])
		{// �ヂ�[�V�����̐ݒ�
			g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_WEAK;
		}
		if (g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2])
		{//  ��2�̐ݒ�
			g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_WEAK_2;
		}
		if (g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3])
		{// ��3�̐ݒ�
			g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_WEAK_3;
		}
		if (g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4])
		{// ��4�̐ݒ�
			g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_WEAK_4;
		}
		if (g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5])
		{// ��5�̐ݒ�
			g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_WEAK_5;
		}
		if (g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_SPECIAL])
		{// �K�E�Z�̐ݒ�
			g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_SPECIAL;
		}
		// ���[�V����
		MotionInfoPlayer(nIdy);
		if (g_aPlayer[nIdy].bCombo)
		{// �R���{�I��
			g_aPlayer[nIdy].nComboCounter--;

			if (g_aPlayer[nIdy].nComboCounter == 0)
			{
				AllReleaseAttack(nIdy);

				g_aPlayer[nIdy].bCombo = false;
			}
		}
		//********************************************************************************************************************************
		// �L�����N�^�[����
		//*************************************************************************************************************************
		switch (g_aPlayer[nIdy].nMotionType)
		{// �v���C���[�̃��[�V������
		case PLAYER_MOTION_TYPE_JUMP:						// �W�����v���[�V������������
			break;
		case PLAYER_MOTION_TYPE_LANDING:					// ���n���[�V������������
			break;
		case PLAYER_MOTION_TYPE_DAMAGE:						// �_���[�W(������)���[�V������������
			break;
		case PLAYER_MOTION_TYPE_FLY:						// �_���[�W(�������)���[�V������������
			break;
		case PLAYER_MOTION_TYPE_GETUP:						// �N���オ�胂�[�V������������
			break;
		case PLAYER_MOTION_TYPE_CATCH:
			break;
		case PLAYER_MOTION_TYPE_THROW:
			if (g_aPlayer[nIdy].nFrameAllCounter == 15)
			{
				if (MATURI) {/* ���̎q*/PlaySound(SOUND_HUMAN_NAGERU); }
				if (AMANO) {/* �V��*/PlaySound(SOUND_TENGU_NAGERU); }
				if (GOJOU) {/* �͓�*/PlaySound(SOUND_KAPA_NAGERU); }
				if (MOMIJI) {/* ��*/PlaySound(SOUND_FOX_NAGERU); }
				if (DONROID) {/* ���{�b�g*/PlaySound(SOUND_ROBOT_GARD); }
				g_aPlayer[nIdy].bCatch = false;
				g_aPlayer[nIdy].pModelAtk->move = D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 10, 0, cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 10);
			}
			if (g_aPlayer[nIdy].nFrameAllCounter >= 15 && g_aPlayer[nIdy].nFrameAllCounter <= 25)
			{// ���[�V�����̃t���[���̎�
				g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
			}
			break;
		case PLAYER_MOTION_TYPE_GUARD:						// �K�[�h���[�V������������
			break;
		case PLAYER_MOTION_TYPE_CRASH:						// �������[�V������������
			break;
		case PLAYER_MOTION_TYPE_WEAK:						// �U�����[�V������������
			if (MATURI)
			{
				if (g_aPlayer[nIdy].nFrameAllCounter == 5) { PlaySound(SOUND_HUMAN_ATTACK000); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 8 && g_aPlayer[nIdy].nFrameAllCounter <= 15)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			if (AMANO)
			{// �V��
				if (g_aPlayer[nIdy].nFrameAllCounter == 22) { PlaySound(SOUND_TENGU_ATTACK000); }
				if (g_aPlayer[nIdy].nFrameAllCounter == 22)
				{// �������N����
					for (int nCnt = 0; nCnt < 40; nCnt++)
					{
						SetEffectUPDamage(nIdy, 1.5f , 2.0f, 1.0f, g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 50, nCnt*2.0f, cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 50)
							, D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 5, 0.0f, cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 5)
							, D3DXVECTOR3(rand()%50/100.0f, SetRandomEffect(), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
							EFFECTUPTYPE_LEAF, nCnt*1.3f);

					}
					SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(0,50,-50), D3DXVECTOR3(0,0,0),D3DXVECTOR3(0, 0, 0),D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 0, EFFECTTYPE_CARTOON_WIND);

				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 22 && g_aPlayer[nIdy].nFrameAllCounter <= 30)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			if (GOJOU)
			{// �͓�
				if (g_aPlayer[nIdy].nFrameAllCounter == 5) { PlaySound(SOUND_KAPA_ATTACK000); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 0 && g_aPlayer[nIdy].nFrameAllCounter <= 5)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 14 && g_aPlayer[nIdy].nFrameAllCounter <= 18)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			if (MOMIJI)
			{// ����
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) {PlaySound(SOUND_FOX_ATTACK000);}// �U���{�C�X�Đ�
				if (g_aPlayer[nIdy].nFrameAllCounter >= 16 && g_aPlayer[nIdy].nFrameAllCounter <=23)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			if (DONROID)
			{// ���{�b�g
				if (g_aPlayer[nIdy].nFrameAllCounter == 25) {PlaySound(SOUND_ROBOT_ATTACK000);}// �U���{�C�X�Đ�
				if (g_aPlayer[nIdy].nFrameAllCounter >= 27 && g_aPlayer[nIdy].nFrameAllCounter <= 35)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			break;
		case PLAYER_MOTION_TYPE_WEAK_2:				// ��2
			if (MATURI)
			{// ���̎q
				if (g_aPlayer[nIdy].nFrameAllCounter == 5) { PlaySound(SOUND_HUMAN_ATTACK001); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 6 && g_aPlayer[nIdy].nFrameAllCounter <= 15)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			if (AMANO)
			{// �V��
				if (g_aPlayer[nIdy].nFrameAllCounter == 25) { PlaySound(SOUND_TENGU_ATTACK001); }
				if (g_aPlayer[nIdy].nFrameAllCounter == 25)
				{// �������N����
					for (int nCnt = 0; nCnt < 40; nCnt++)
					{
						SetEffectUPDamage(nIdy, 1.8f, 2.0f, 1.0f, g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 50, nCnt*4.0f, cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 50)
							, D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 5, 0.0f, cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 5)
							, D3DXVECTOR3(rand() % 50 / 100.0f, SetRandomEffect(), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
							EFFECTUPTYPE_LEAF, sinf(float(nCnt))*30.0f);

					}
					SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(0, 50, -50)
						, D3DXVECTOR3(0, 0, 0),
						D3DXVECTOR3(0, 0, 0),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 0, EFFECTTYPE_CARTOON_WIND);

				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 25 && g_aPlayer[nIdy].nFrameAllCounter <= 25)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.y = 10;
				}
			}
			if (GOJOU)
			{// �͓�
				if (g_aPlayer[nIdy].nFrameAllCounter == 5) { PlaySound(SOUND_KAPA_ATTACK001); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 9 && g_aPlayer[nIdy].nFrameAllCounter <= 11)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed * 2);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed * 2);
				}
			}
			if (MOMIJI)
			{// ����
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) { PlaySound(SOUND_FOX_ATTACK001); }// �U���{�C�X�Đ�
				if (g_aPlayer[nIdy].nFrameAllCounter >= 12 && g_aPlayer[nIdy].nFrameAllCounter <= 21)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			if (DONROID)
			{// ���{�b�g
				if (g_aPlayer[nIdy].nFrameAllCounter == 25) { PlaySound(SOUND_ROBOT_ATTACK001); }// �U���{�C�X�Đ�
				if (g_aPlayer[nIdy].nFrameAllCounter >= 26 && g_aPlayer[nIdy].nFrameAllCounter <= 35)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			break;
		case PLAYER_MOTION_TYPE_WEAK_3:			// ��3
			if (MATURI)
			{// ���̎q
				if (g_aPlayer[nIdy].nFrameAllCounter == 20) { PlaySound(SOUND_HUMAN_ATTACK002); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 25 && g_aPlayer[nIdy].nFrameAllCounter <= 33)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			if (AMANO)
			{// �V��
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) { PlaySound(SOUND_TENGU_ATTACK002); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 10 && g_aPlayer[nIdy].nFrameAllCounter <= 15)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.y = 2;
				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 16 && g_aPlayer[nIdy].nFrameAllCounter <= 25)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.y = -15;
				}
				if ( g_aPlayer[nIdy].nFrameAllCounter == 20)
				{// ���[�V�����̃t���[���̎�
					float fRadius = 0.0f;
					for (int nCnt = 0; nCnt < 40; nCnt++)
					{// ���v�̌`
						fRadius = (D3DX_PI) /40.0f* float(nCnt);
						SetEffectUPDamage(nIdy, 2.0f, 2.0f, 1.0f, g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 50, nCnt*4.0f -30.0f, cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 50)
							, D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 6, 0.0f, cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) *6)
							, D3DXVECTOR3( rand() % 50 / 100.0f, SetRandomEffect(), 0.0f), D3DXCOLOR(0.3f, 1.0f, 0.3f, 2.0f),
							EFFECTUPTYPE_LEAF, cosf(fRadius)*100);
					}
					SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(0, 50, -50), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 0, EFFECTTYPE_CARTOON_WIND);

				}
			}
			if (GOJOU)
			{// �͓�
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) { PlaySound(SOUND_KAPA_ATTACK002); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 0 && g_aPlayer[nIdy].nFrameAllCounter <= 13)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed *1.0f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed *1.0f);
				}

			}
			if (MOMIJI)
			{// ����
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) { PlaySound(SOUND_FOX_ATTACK002); }// �U���{�C�X�Đ�
				if (g_aPlayer[nIdy].nFrameAllCounter >= 13 && g_aPlayer[nIdy].nFrameAllCounter <= 19)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*2);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*2);
				}
			}
			if (DONROID)
			{// ���{�b�g
				if (g_aPlayer[nIdy].nFrameAllCounter == 5) { PlaySound(SOUND_ROBOT_ATTACK002); }// �U���{�C�X�Đ�
				if (g_aPlayer[nIdy].nFrameAllCounter >= 24 && g_aPlayer[nIdy].nFrameAllCounter <= 30)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*3);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*3);
				}
			}
			break;
		case PLAYER_MOTION_TYPE_WEAK_4:			// ��4
			if (MATURI)
			{// ���̎q
				if (g_aPlayer[nIdy].nFrameAllCounter == 3) { PlaySound(SOUND_HUMAN_ATTACK003); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 5 && g_aPlayer[nIdy].nFrameAllCounter <= 40)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*1.5f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*1.5f);
				}
			}
			if (AMANO)
			{// �V��
				if (g_aPlayer[nIdy].nFrameAllCounter == 34) { PlaySound(SOUND_TENGU_ATTACK003); }

				if (g_aPlayer[nIdy].nFrameAllCounter == 45)
				{// ���[�V�����̃t���[���̎�
					PlaySound(SOUND_EFFECT_WIND001);
					for (int nCnt = 0; nCnt < 40; nCnt++)
					{
						SetEffectUPDamage(nIdy,2.0f,2.0f,5.0f, g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 100, 0.0f, cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 100)
							, D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 0.1f, 4.0f, cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 0.1f)
							, D3DXVECTOR3(rand() % 50 / 100.0f, SetRandomEffect(), 0.0f), D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f),
							EFFECTUPTYPE_LEAF, nCnt*3.0f + 3.0f);
					}
				}
			}
			if (GOJOU)
			{// �͓�
				if (g_aPlayer[nIdy].nFrameAllCounter == 10) { PlaySound(SOUND_KAPA_ATTACK003); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 10 && g_aPlayer[nIdy].nFrameAllCounter <= 20)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed *1.5f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed *1.5f);
				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 21 && g_aPlayer[nIdy].nFrameAllCounter <= 35)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed *1.0f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed *1.0f);
				}

			}
			if (MOMIJI)
			{// ����
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) { PlaySound(SOUND_FOX_ATTACK003); }// �U���{�C�X�Đ�
				if (g_aPlayer[nIdy].nFrameAllCounter >= 15 && g_aPlayer[nIdy].nFrameAllCounter <= 21)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed * 2.5f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed * 2.5f);
				}
			}
			if (DONROID)
			{// ���{�b�g
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) { PlaySound(SOUND_ROBOT_ATTACK003); }// �U���{�C�X�Đ�
				if (g_aPlayer[nIdy].nFrameAllCounter >= 10 && g_aPlayer[nIdy].nFrameAllCounter <= 30)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed );
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed );
				}
			}
			break;
		case PLAYER_MOTION_TYPE_WEAK_5:			// ��5
			if (MATURI)
			{// ���̎q
				if (g_aPlayer[nIdy].nFrameAllCounter == 20) { PlaySound(SOUND_HUMAN_ATTACK004); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 20 && g_aPlayer[nIdy].nFrameAllCounter <= 30)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*2.0f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*2.0f);
				}
			}
			if (AMANO)
			{// �V��
				if (g_aPlayer[nIdy].nFrameAllCounter == 30) { PlaySound(SOUND_TENGU_ATTACK004); }

				if (g_aPlayer[nIdy].nFrameAllCounter >= 44 && g_aPlayer[nIdy].nFrameAllCounter <= 50)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y ) * g_aPlayer[nIdy].MoveSpeed * 2.5f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y ) * g_aPlayer[nIdy].MoveSpeed * 2.5f);
				}
				if (g_aPlayer[nIdy].nFrameAllCounter == 44)
				{// ���[�V�����̃t���[���̎�
					PlaySound(SOUND_EFFECT_WIND000);
					for (int nCnt = 0; nCnt < 50; nCnt++)
					{
						SetEffectUPDamage(nIdy, 10.0f, 3.0f, 8.0f, g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 70, nCnt*5.0f - 50, cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 70)
							, D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 5.0f, 0.0f, cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 5.0f)
							, D3DXVECTOR3(rand() % 50 / 100.0f, SetRandomEffect(), 0.0f),
							D3DXCOLOR(rand()%100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f, 2.0f),
							EFFECTUPTYPE_LEAF, cosf(float(nCnt))*80.0f + 40.0f);
					}
				}

			}
			if (GOJOU)
			{// �͓�
				if (g_aPlayer[nIdy].nFrameAllCounter == 10) { PlaySound(SOUND_KAPA_ATTACK004); }

			}
			if (MOMIJI)
			{// ����
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) { PlaySound(SOUND_FOX_ATTACK005); }// �U���{�C�X�Đ�
				if (g_aPlayer[nIdy].nFrameAllCounter >= 5 && g_aPlayer[nIdy].nFrameAllCounter <= 11)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.y = 8;
				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 31 && g_aPlayer[nIdy].nFrameAllCounter <= 40)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.y += -3;
				}
			}
			if (DONROID)
			{// ���{�b�g
				if (g_aPlayer[nIdy].nFrameAllCounter == 30) { PlaySound(SOUND_ROBOT_ATTACK005); }// �U���{�C�X�Đ�
				if (g_aPlayer[nIdy].nFrameAllCounter >= 34 && g_aPlayer[nIdy].nFrameAllCounter <= 35)
				{// ���[�V�����̃t���[���̎�
					for (int nCnt = 0; nCnt < 40; nCnt++)
					{
						SetEffectDamage(nIdy, g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_WEAK_5].fAttackPower,
							g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_WEAK_5].fDamageH
							, g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_WEAK_5].fDamageV, D3DXVECTOR3(g_aPlayer[nIdy].aModel[3].mtxWorld._41 + sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * (nCnt*10 + 10), g_aPlayer[nIdy].aModel[3].mtxWorld._42, g_aPlayer[nIdy].aModel[3].mtxWorld._43 + cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * (nCnt*10+ 10)),
							D3DXVECTOR3(0,0,0), D3DXVECTOR3(0, 0, 0),
							D3DXCOLOR(float(rand() % 50) / 100.0f, 0.3f,1.0f,1.5f), 20 + float(rand() % 20), 0, EFFECTTYPE_LASER);
					}
					for (int nCnt = 0; nCnt < 40; nCnt++)
					{
						SetEffectDamage(nIdy, g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_WEAK_5].fAttackPower,
							g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_WEAK_5].fDamageH
							, g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_WEAK_5].fDamageV, D3DXVECTOR3(g_aPlayer[nIdy].aModel[3].mtxWorld._41 + sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * (nCnt * 10 + 10), g_aPlayer[nIdy].aModel[3].mtxWorld._42, g_aPlayer[nIdy].aModel[3].mtxWorld._43 + cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * (nCnt * 10 + 10)),
							D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0),
							D3DXCOLOR(float(rand() % 50) / 100.0f, 0.3f, 1.0f, 1.5f), 20 + float(rand() % 10), 0, EFFECTTYPE_LASER);
					}
				}
			}
			break;
		case PLAYER_MOTION_TYPE_SPECIAL:// �K�E�Z
			if (MATURI)
			{// ���̎q
				if (g_aPlayer[nIdy].nFrameAllCounter == 20) { PlaySound(SOUND_HUMAN_ATTACK008); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 20 && g_aPlayer[nIdy].nFrameAllCounter <= 30)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.y = 5.0f;

				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 20 && g_aPlayer[nIdy].nFrameAllCounter <= 40)
				{
					for (int nCnt = 0; nCnt < 5; nCnt++)
					{// ��
						SetEffect(D3DXVECTOR3(g_aPlayer[nIdy].aModel[6].mtxWorld._41, g_aPlayer[nIdy].aModel[6].mtxWorld._42, g_aPlayer[nIdy].aModel[6].mtxWorld._43) +
							D3DXVECTOR3(sinf(SetRandomEffect()) * 30.0f, cosf(SetRandomEffect()) * 30.0f, cosf(SetRandomEffect()) * 30.0f)
							, D3DXVECTOR3(sinf(SetRandomEffect()) * 1.5f, cosf(SetRandomEffect()) * 1.5f, cosf(SetRandomEffect()) * 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), float(rand() % 50) + 10, 0, EFFECTTYPE_SUNDER);
					}
				}
			}
			if (GOJOU)
			{// �͓�
				if (g_aPlayer[nIdy].nFrameAllCounter == 20) { PlaySound(SOUND_KAPA_ATTACK005); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 35 && g_aPlayer[nIdy].nFrameAllCounter <= 40)
				{
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y) * g_aPlayer[nIdy].MoveSpeed * 2.0f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y) * g_aPlayer[nIdy].MoveSpeed * 2.0f);
				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 30 && g_aPlayer[nIdy].nFrameAllCounter <= 80)
				{// ���[�V�����̃t���[���̎�
					for (int nCnt = 0; nCnt < 10; nCnt++)
					{// ��
						SetEffectDamage(nIdy, g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_SPECIAL].fAttackPower,
							g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_SPECIAL].fDamageH
							, g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_SPECIAL].fDamageV,
							D3DXVECTOR3(g_aPlayer[nIdy].aModel[3].mtxWorld._41, g_aPlayer[nIdy].aModel[3].mtxWorld._42, g_aPlayer[nIdy].aModel[3].mtxWorld._43),
							D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) *(rand() % 10 + 10) + sinf(SetRandomEffect()) * 2,
								cosf(float(rand()%314)/100.0f) * 5.0f, cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * (rand() % 10 + 10) + cosf(SetRandomEffect()) * 1.0f),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
							float(rand() % 30), 0, EFFECTTYPE_WATER);
					}
				}
			}
			if (AMANO)
			{// �V��
				if (g_aPlayer[nIdy].nFrameAllCounter == 10) { PlaySound(SOUND_TENGU_ATTACK005); }

				if (g_aPlayer[nIdy].nFrameAllCounter >= 10 && g_aPlayer[nIdy].nFrameAllCounter <= 50)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.y = 3.0f;
				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 50)
				{// ���[�V�����̃t���[���̎�
					g_aPlayer[nIdy].move.y = 1.0f;
				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 45&&g_aPlayer[nIdy].nFrameAllCounter <= 55)
				{// ���[�V�����̃t���[���̎�
					for (int nCnt = 0; nCnt < 20; nCnt++)
					{
						SetEffectUPDamage(nIdy, g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_SPECIAL].fAttackPower, 1.1f, g_aPlayer[nIdy].nFrameAllCounter/9.0f, g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * (100),
							-nCnt*6.5f - 100,
							cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) *(100))
							, D3DXVECTOR3(0.0f,3.0f,0.0f)
							, D3DXVECTOR3(rand() % 50 / 100.0f, SetRandomEffect(), 0.0f),
							D3DXCOLOR(rand() % 50 / 100.0f + 0.5f, rand() % 50 / 100.0f + 0.5f, rand() % 50 / 100.0f + 0.5f, 2.0f),
							EFFECTUPTYPE_LEAF, cosf(float(nCnt))*60.0f + 200.0f);
					}
					for (int nCnt = 0; nCnt < 10; nCnt++)
					{
						SetEffect(D3DXVECTOR3( g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(SetRandomEffect()) * (50),
							-nCnt*6.5f - 100,
							cosf(SetRandomEffect()) *(50))),
							D3DXVECTOR3(sinf(SetRandomEffect()) *(rand() % 5) + sinf(SetRandomEffect()) * 2,
								cosf(SetRandomEffect()) * 1.5f, cosf(SetRandomEffect()) * (rand() % 5) + cosf(SetRandomEffect()) * 2),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
							float(rand() % 100 + 10), 0, EFFECTTYPE_DIRTY);
					}
				}

			}
			if (MOMIJI)
			{// ����
				if (g_aPlayer[nIdy].nFrameAllCounter == 10) { PlaySound(SOUND_FOX_ATTACK004); }// �U���{�C�X�Đ�

				if (g_aPlayer[nIdy].nFrameAllCounter == 30){PlaySound(SOUND_LABEL( SOUND_EFFECT_FLAME000 + rand()%2));}// �U���Đ�

				if (g_aPlayer[nIdy].nFrameAllCounter >= 30 && g_aPlayer[nIdy].nFrameAllCounter <= 80)
				{// ���[�V�����̃t���[���̎�
					for (int nCnt = 0; nCnt < 10; nCnt++)
					{
						SetEffectDamage(nIdy, g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_SPECIAL].fAttackPower
							, g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_SPECIAL].fDamageH
							, g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_SPECIAL].fDamageV,
							D3DXVECTOR3(g_aPlayer[nIdy].aModel[3].mtxWorld._41, g_aPlayer[nIdy].aModel[3].mtxWorld._42, g_aPlayer[nIdy].aModel[3].mtxWorld._43),
							D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) *( rand()%10 + 5)+sinf(SetRandomEffect())*2,
								cosf(SetRandomEffect()) * 1.5f, cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * (rand() % 10 + 5) + cosf(SetRandomEffect())*2),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, float(rand() % 100) / 100.0f, 0.0f, 1.0f),
							float(rand() % 50), 0, EFFECTTYPE_FIRE);
					}

				}
			}
			if (DONROID)
			{// ���{�b�g
				if (g_aPlayer[nIdy].nFrameAllCounter == 30) { PlaySound(SOUND_EFFECT_BOMB000); PlaySound(SOUND_EFFECT_BOMB001);
				g_aPlayer[nIdy].fLife -= 20;
				GetPlayerLife(int(g_aPlayer[nIdy].fLife), nIdy);}// �U���{�C�X�Đ�
				if (g_aPlayer[nIdy].nFrameAllCounter >= 30 && g_aPlayer[nIdy].nFrameAllCounter <= 35)
				{// ���[�V�����̃t���[���̎�
					for (int nCntEffect = 0; nCntEffect < 1; nCntEffect++)
					{// �Ռ���
						SetEffect(g_aPlayer[nIdy].pos,
							D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXCOLOR(0.8f, 0.5f, 0.0f, 1.5f),float( rand()%100), 30, EFFECTTYPE_IMPACT);
					}
					for (int nCnt = 0; nCnt < 50; nCnt++)
					{// ����
						SetEffectDamage(nIdy, g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_SPECIAL].fAttackPower
							, g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_SPECIAL].fDamageH
							, g_aPlayerData[g_aPlayer[nIdy].type].aMotion[PLAYER_MOTION_TYPE_SPECIAL].fDamageV,
							D3DXVECTOR3(g_aPlayer[nIdy].aModel[3].mtxWorld._41, g_aPlayer[nIdy].aModel[3].mtxWorld._42, g_aPlayer[nIdy].aModel[3].mtxWorld._43)
							+ D3DXVECTOR3(sinf(SetRandomEffect()) *(rand() % 50), cosf(SetRandomEffect()) *(rand() % 50), cosf(SetRandomEffect()) *(rand() % 50)),
							D3DXVECTOR3(sinf(SetRandomEffect()) *(rand() % 3), cosf(SetRandomEffect()) *(rand() % 3), cosf(SetRandomEffect()) *(rand() % 3)),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, float(rand() % 100) / 100.0f, 0.0f, 1.0f),
							float(rand() % 150) + 50.0f, 0, EFFECTTYPE_BOMB);
					}
				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 50 )
				{// ���[�V�����̃t���[���̎�
					for (int nCnt = 0; nCnt < 10; nCnt++)
					{
						SetEffect(D3DXVECTOR3(g_aPlayer[nIdy].aModel[3].mtxWorld._41, g_aPlayer[nIdy].aModel[3].mtxWorld._42, g_aPlayer[nIdy].aModel[3].mtxWorld._43) + D3DXVECTOR3(sinf(SetRandomEffect()) * 10, 0.0f, cosf(SetRandomEffect()) * 10),
							D3DXVECTOR3(sinf(SetRandomEffect()) * float(rand() % 3),float(rand()%500/100.0f), cosf(SetRandomEffect()) * float(rand() % 3)),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), float(rand() % 30), 0, EFFECTTYPE_DIRTY);
					}
				}
			}
			break;
			case PLAYER_MOTION_TYPE_WIN:
				if (g_aPlayer[nIdy].nFrameAllCounter ==1)
				{// ���[�V�����̃t���[���̎�
					if (GetGameState() == GAMESTATE_GAME)
					{
						SetPlayerVoice(g_aPlayer[nIdy].type, PLAYER_MOTION_TYPE_WIN);
					}
				}
				AllReleaseAttack(nIdy);
			break;
		}
		if (g_aPlayer[nIdy].state != PLAYERSTATE_CRASH&&g_aPlayer[nIdy].state != PLAYERSTATE_CRASHSTART)
		{
			if (!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP] && g_aPlayer[nIdy].bMotionStateOld[PLAYER_BOOL_GETUP])
			{// �N���オ��I�������
				g_aPlayer[nIdy].nCntState = 60;
				g_aPlayer[nIdy].state = PLAYERSTATE_INVINCIBLE;	// ���G
			}
		}

		if (!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD])
		{// �K�[�h���ĂȂ�
			g_aPlayer[nIdy].fGuardLife += 0.01f;
			if (g_aPlayer[nIdy].fGuardLife >= 1.0f)
			{
				g_aPlayer[nIdy].fGuardLife = 1.0f;
			}
		}
		else
		{// �K�[�h
			g_aPlayer[nIdy].fGuardLife -= 0.001f;
			if (g_aPlayer[nIdy].fGuardLife <= 0)
			{
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD] = false;
				g_aPlayer[nIdy].state = PLAYERSTATE_CRASH;
				g_aPlayer[nIdy].nCntState = 300;
				// ���������̐�����ї͂���
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CRASH] = true;	// �����ݒ�
			}
		}
//-------------------------------------/ �e �� ���ړ����� /---------------------------------------------------------------------------------------//
		SetPositionShadow(g_aPlayer[nIdy].nIdyShadow, D3DXVECTOR3(g_aPlayer[nIdy].aModel[0].mtxWorld._41, g_aPlayer[nIdy].aModel[0].mtxWorld._42, g_aPlayer[nIdy].aModel[0].mtxWorld._43), g_aPlayer[nIdy].Initpos);
		SetPositionLine(g_aPlayer[nIdy].nIdyLine, g_aPlayer[nIdy].pos, g_aPlayer[nIdy].rot);
		if (g_aPlayer[nIdy].fPulsAttack > 0.0f)
		{// �U���͂��㏸���Ă�����
			SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(SetRandomEffect())*20.0f, 0.0f, cosf(SetRandomEffect())*20.0f),
				D3DXVECTOR3(0.0f, float(rand() % 2 + 1), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.3f, 0.3f, float(rand()%100)/100.0f),
				float(rand()%50), 60, EFFECTTYPE_STATE_UP);
		}
		if (g_aPlayer[nIdy].fPulsSpeed > 0.0f)
		{// ���΂₳���㏸���Ă�����
			SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(SetRandomEffect())*20.0f, 0.0f, cosf(SetRandomEffect())*20.0f),
				D3DXVECTOR3(0.0f, float(rand() % 2 + 1), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.3f, 0.3f, 1.0f, float(rand() % 100) / 100.0f),
				float(rand() % 50), 60, EFFECTTYPE_STATE_UP);
		}
	}
}
//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawPlayer(int nIdy, int nCamera)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;				// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;					// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;				// �e�̃}�g���b�N�X
	D3DXCOLOR col = GetEventColor();

	Shader shader = GetShader();
	// �e�N�j�b�N�̐ݒ�
	shader.pShader->SetTechnique("StandardShader");
	// �V�F�[�_�J�n
	shader.pShader->Begin(0, 0);

	// ���C�g�e���󂯂Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_aPlayer[nIdy].mtxWorld);
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer[nIdy].rot.y, g_aPlayer[nIdy].rot.x, g_aPlayer[nIdy].rot.z);
	D3DXMatrixMultiply(&g_aPlayer[nIdy].mtxWorld, &g_aPlayer[nIdy].mtxWorld, &mtxRot);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nIdy].pos.x, g_aPlayer[nIdy].pos.y, g_aPlayer[nIdy].pos.z);
	D3DXMatrixMultiply(&g_aPlayer[nIdy].mtxWorld, &g_aPlayer[nIdy].mtxWorld, &mtxTrans);
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer[nIdy].mtxWorld);

	if (g_aPlayer[nIdy].bUse)
	{
		for (int nCntPlayerModel = 0; nCntPlayerModel < g_aPlayerData[g_aPlayer[nIdy].type].nNumParts; nCntPlayerModel++)
		{

			// �ߋ�
			g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorldOld = g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld;

			if (g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].nIdxModelPareant == -1)
			{// �v���C���[
				mtxParent = g_aPlayer[nIdy].mtxWorld;
			}
			else
			{// �e�e
				mtxParent = g_aPlayer[nIdy].aModel[g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].nIdxModelPareant].mtxWorld;
			}
			// ------------------------/ �e���f���̕`�� /-------------------------------------------//
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer[nIdy].aModel[nCntPlayerModel].rot.y, g_aPlayer[nIdy].aModel[nCntPlayerModel].rot.x, g_aPlayer[nIdy].aModel[nCntPlayerModel].rot.z);
			D3DXMatrixMultiply(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nIdy].aModel[nCntPlayerModel].pos.x,
				g_aPlayer[nIdy].aModel[nCntPlayerModel].pos.y,
				g_aPlayer[nIdy].aModel[nCntPlayerModel].pos.z);
			D3DXMatrixMultiply(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &mtxTrans);
			D3DXMatrixMultiply(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &mtxParent);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld);

			// �r���[�}�g���b�N�X��ݒ�
			D3DXMATRIX matrix = g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld *GetCamera()[nCamera].mtxView * GetCamera()[nCamera].mtxProjection;
			shader.pShader->SetMatrix("g_fMatrix", &matrix);
			shader.pShader->SetVector("g_fColor", &D3DXVECTOR4(col.r, col.g, col.b, col.a)); // �F�ݒ�
																										 // �p�X�̕`��J�n
			shader.pShader->BeginPass(0);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);
			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].pBuffMat->GetBufferPointer();
			if (g_aPlayer[nIdy].bDraw)
			{
				for (int nCntPlayer2 = 0; nCntPlayer2 < (int)g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].nNumMat; nCntPlayer2++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntPlayer2].MatD3D);
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].pTextuer[g_aPlayer[nIdy].colType][nCntPlayer2]);
					// �����v�e�N�X�`���̐ݒ�(1�ԂɃ����v�e�N�X�`����ݒ�)
					pDevice->SetTexture(1, shader.pTexture);

					// ���f��(�p�[�c)�̕`��
					g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].pMesh->DrawSubset(nCntPlayer2);
				}
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);

			// ------------------------/ �q���f���̕`�� /-------------------------------------------//
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer[nIdy].aModel[nCntPlayerModel].rot.y, g_aPlayer[nIdy].aModel[nCntPlayerModel].rot.x, g_aPlayer[nIdy].aModel[nCntPlayerModel].rot.z);
			D3DXMatrixMultiply(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nIdy].aModel[nCntPlayerModel].pos.x,
				g_aPlayer[nIdy].aModel[nCntPlayerModel].pos.y,
				g_aPlayer[nIdy].aModel[nCntPlayerModel].pos.z);

			D3DXMatrixMultiply(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &mtxTrans);
			D3DXMatrixMultiply(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &mtxParent);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);
			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].pBuffMat->GetBufferPointer();
			if (g_aPlayer[nIdy].bDraw)
			{
				for (int nCntPlayer2 = 0; nCntPlayer2 < (int)g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].nNumMat; nCntPlayer2++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntPlayer2].MatD3D);
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].pTextuer[g_aPlayer[nIdy].colType][nCntPlayer2]);
					// �����v�e�N�X�`���̐ݒ�(1�ԂɃ����v�e�N�X�`����ݒ�)
					pDevice->SetTexture(1, shader.pTexture);
					// ���f��(�p�[�c)�̕`��
					g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].pMesh->DrawSubset(nCntPlayer2);
				}
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
			// �p�X�̕`��I��
			shader.pShader->EndPass();
			for (int nCollision = 0; nCollision < MAX_COLLISION; nCollision++)
			{// ����̃}�g���b�N�X
				if (g_aPlayer[nIdy].ColAttack[nCollision].bUse)
				{// �U������
				 // �O��̈ʒu��ɉh
					g_aPlayer[nIdy].ColAttack[nCollision].mtxWorldOld = g_aPlayer[nIdy].ColAttack[nCollision].mtxWorld;
					// �ʒu�𔽉f
					D3DXMatrixTranslation(&g_aPlayer[nIdy].ColAttack[nCollision].mtxWorld, g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].ofset.x, g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].ofset.y, g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].ofset.z);
					D3DXMatrixMultiply(&g_aPlayer[nIdy].ColAttack[nCollision].mtxWorld, &g_aPlayer[nIdy].ColAttack[nCollision].mtxWorld, &g_aPlayer[nIdy].aModel[g_aPlayer[nIdy].ColAttack[nCollision].nIdxParent].mtxWorld);
				}
				if (g_aPlayer[nIdy].ColBody[nCollision].bUse)
				{// �_���[�W����
				 // �O��̈ʒu��ɉh
					g_aPlayer[nIdy].ColBody[nCollision].mtxWorldOld = g_aPlayer[nIdy].ColBody[nCollision].mtxWorld;
					// �ʒu�𔽉f
					D3DXMatrixTranslation(&g_aPlayer[nIdy].ColBody[nCollision].mtxWorld, g_aPlayer[nIdy].ColBody[nCollision].ofset.x, g_aPlayer[nIdy].ColBody[nCollision].ofset.y, g_aPlayer[nIdy].ColBody[nCollision].ofset.z);
					D3DXMatrixMultiply(&g_aPlayer[nIdy].ColBody[nCollision].mtxWorld, &g_aPlayer[nIdy].ColBody[nCollision].mtxWorld, &g_aPlayer[nIdy].aModel[g_aPlayer[nIdy].ColBody[nCollision].nIdxParent].mtxWorld);
				}
			}

		}
		PlayerMotionType type = g_aPlayer[nIdy].nMotionType;
		for (int nCntOrbit = 0; nCntOrbit < MAX_PLAYER_ORBIT; nCntOrbit++)
		{
			if (g_aPlayer[nIdy].orbit[type][nCntOrbit].nOrbitLength <= 0)
			{
				break;
			}
			// �O�Րݒ�
			SetOrbit(g_aPlayer[nIdy].aModel[g_aPlayer[nIdy].orbit[type][nCntOrbit].nIdyOrbit].mtxWorld,
				g_aPlayer[nIdy].aModel[g_aPlayer[nIdy].orbit[type][nCntOrbit].nIdyOrbit].mtxWorldOld,
				g_aPlayer[nIdy].orbit[type][nCntOrbit].nOrbitLength,
				g_aPlayer[nIdy].orbit[type][nCntOrbit].OrbitStart, g_aPlayer[nIdy].orbit[type][nCntOrbit].OrbitEnd,
				ORBITTYPE(g_aPlayer[nIdy].orbit[type][nCntOrbit].nType), g_aPlayer[nIdy].orbit[type][nCntOrbit].motion);
		}
		PlayerColInfo(nIdy);
	}

	// �V�F�[�_�I��
	shader.pShader->End();
	// ���C�g�e���󂯂Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
//==============================================================================================================================
// ���f���̎擾
//==============================================================================================================================
Player *GetPlayer(void)
{
	return &g_aPlayer[0];
}
PlayerData *GetPlayerData(void)
{
	return &g_aPlayerData[0];
}

//==============================================================================================================================
// ���f���̃��[�V����
//==============================================================================================================================
void MotionInfoPlayer(int nIdy)
{
	for (int nCnt = 0 ; nCnt < MAX_PLAYER; nCnt++)
	{
		if (g_aPlayer[nIdy].nFrameAllCounter == 1)
		{// ���̃^�C�v�ƑO�̃^�C�v���������
			g_aPlayer[nCnt].nMotionGetCol = PLAYER_MOTION_TYPE_MAX;
		}
	}
	if (g_aPlayer[nIdy].nMotionType != g_aPlayer[nIdy].nMotionTypeOld)
	{// ���̃^�C�v�ƑO�̃^�C�v���������
		g_aPlayer[nIdy].nKeyCounter = 0;						// �L�[�����Z�b�g
		g_aPlayer[nIdy].nFrameCounter = 0;					// �t���[�������Z�b�g
		g_aPlayer[nIdy].bBlend = true;	// �u�����h�ɂ���
		g_aPlayer[nIdy].nFrame = BLEND_FRAME;					// �u�����h�̃t���[��
		g_aPlayer[nIdy].nFrameAllCounter = 0;					// �S�Ẵt���[��
		g_aPlayer[nIdy].bCombo = false;
	}
	else if (g_aPlayer[nIdy].bBlend == false )
	{// �ʏ펞�̃t���[��
		g_aPlayer[nIdy].nFrame = g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].aKey[g_aPlayer[nIdy].nKeyCounter].nFrame;
	}
	if (g_aPlayer[nIdy].nFrameCounter == 0)
	{// ���̃L�[�t���[���̃��[�V������ǂݍ���
		for (int nCntParts = 0; nCntParts < g_aPlayerData[g_aPlayer[nIdy].type].nNumParts; nCntParts++)
		{// Key - ���� �Ԃ̍����v�Z
			g_aPlayer[nIdy].aModel[nCntParts].posAddMotion =
				(g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].aKey[g_aPlayer[nIdy].nKeyCounter].aPartsKey[nCntParts].pos
					- g_aPlayer[nIdy].aModel[nCntParts].pos + g_aPlayer[nIdy].aModel[nCntParts].Initpos) / float(g_aPlayer[nIdy].nFrame);

			g_aPlayer[nIdy].aModel[nCntParts].DiffrotMotion = (g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].aKey[g_aPlayer[nIdy].nKeyCounter].aPartsKey[nCntParts].rot - g_aPlayer[nIdy].aModel[nCntParts].rot);

			if (g_aPlayer[nIdy].aModel[nCntParts].DiffrotMotion.x > D3DX_PI)
			{
				g_aPlayer[nIdy].aModel[nCntParts].DiffrotMotion.x -= D3DX_PI * 2.0f;
			}
			if (g_aPlayer[nIdy].aModel[nCntParts].DiffrotMotion.x < -D3DX_PI)
			{
				g_aPlayer[nIdy].aModel[nCntParts].DiffrotMotion.x += D3DX_PI * 2.0f;
			}
			if (g_aPlayer[nIdy].aModel[nCntParts].DiffrotMotion.y > D3DX_PI)
			{
				g_aPlayer[nIdy].aModel[nCntParts].DiffrotMotion.y -= D3DX_PI * 2.0f;
			}
			if (g_aPlayer[nIdy].aModel[nCntParts].DiffrotMotion.y < -D3DX_PI)
			{
				g_aPlayer[nIdy].aModel[nCntParts].DiffrotMotion.y += D3DX_PI * 2.0f;
			}
			if (g_aPlayer[nIdy].aModel[nCntParts].DiffrotMotion.z > D3DX_PI)
			{
				g_aPlayer[nIdy].aModel[nCntParts].DiffrotMotion.z -= D3DX_PI * 2.0f;
			}
			if (g_aPlayer[nIdy].aModel[nCntParts].DiffrotMotion.z < -D3DX_PI)
			{
				g_aPlayer[nIdy].aModel[nCntParts].DiffrotMotion.z += D3DX_PI * 2.0f;
			}
			g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion = g_aPlayer[nIdy].aModel[nCntParts].DiffrotMotion / float(g_aPlayer[nIdy].nFrame);
		}
	}
	for (int nCntParts = 0; nCntParts < g_aPlayerData[g_aPlayer[nIdy].type].nNumParts; nCntParts++)
	{// ���[�V�����������Z

		if (g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.x > D3DX_PI)
		{// ������3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.x -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.x < -D3DX_PI)
		{// ������-3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.x += D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.y > D3DX_PI)
		{// ������3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.y -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.y < -D3DX_PI)
		{// ������-3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.y += D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.z > D3DX_PI)
		{// ������3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.z -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.z < -D3DX_PI)
		{// ������-3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.z += D3DX_PI * 2.0f;
		}
		g_aPlayer[nIdy].aModel[nCntParts].pos += g_aPlayer[nIdy].aModel[nCntParts].posAddMotion;
		g_aPlayer[nIdy].aModel[nCntParts].rot += g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion;

		if (g_aPlayer[nIdy].aModel[nCntParts].rot.x > D3DX_PI)
		{// ���݂̊p�x��3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].aModel[nCntParts].rot.x -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rot.x < -D3DX_PI)
		{// ���݂̊p�x��-3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].aModel[nCntParts].rot.x += D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rot.y > D3DX_PI)
		{// ���݂̊p�x��3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].aModel[nCntParts].rot.y -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rot.y < -D3DX_PI)
		{// ���݂̊p�x��-3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].aModel[nCntParts].rot.y += D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rot.z > D3DX_PI)
		{// ���݂̊p�x��3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].aModel[nCntParts].rot.z -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rot.z < -D3DX_PI)
		{// ���݂̊p�x��-3.14�𒴂���Ȃ�
			g_aPlayer[nIdy].aModel[nCntParts].rot.z += D3DX_PI * 2.0f;
		}
	}
	g_aPlayer[nIdy].nFrameCounter++;
	g_aPlayer[nIdy].nFrameAllCounter++;
	if (g_aPlayer[nIdy].bBlend  && g_aPlayer[nIdy].nFrameCounter == BLEND_FRAME)
	{// �u�����h�@�u�����h�̃t���[�����ɒB����
		g_aPlayer[nIdy].bBlend = false;
		g_aPlayer[nIdy].nFrameCounter = 0;
		g_aPlayer[nIdy].nKeyCounter = 0;// �u�����h�Ŏ��̃��[�V������0�L�[�ڂ͍s���Ă�
		if (g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_NEUTRAL)
		{
			g_aPlayer[nIdy].nKeyCounter = 1;
		}
	}
	else if (g_aPlayer[nIdy].bBlend == false&& g_aPlayer[nIdy].nFrameCounter == g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].aKey[g_aPlayer[nIdy].nKeyCounter].nFrame)
	{// �t���[���J�E���g������
		g_aPlayer[nIdy].nFrameCounter = 0;
		if (g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].bLoop == false &&
			g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].nNumKey - 1 == g_aPlayer[nIdy].nKeyCounter)
		{// ���[�v���Ȃ����L�[����������
			g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_LANDING] = false;	// ���n�L�����Z��

			switch (g_aPlayer[nIdy].nMotionType)
			{// �v���C���[�̃��[�V������
			case PLAYER_MOTION_TYPE_JUMP:																// �W�����v���[�V������������
				break;
			case PLAYER_MOTION_TYPE_LANDING:															// ���n���[�V������������
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_LANDING] = false;										// ���n��Ԃ���Ȃ���Ԃɂ���

				AllReleaseAttack(nIdy);
				break;
			case PLAYER_MOTION_TYPE_DAMAGE:																// �_���[�W(������)���[�V������������
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_DAMAGE] = false;										// ���n��Ԃ���Ȃ���Ԃɂ���

				break;
			case PLAYER_MOTION_TYPE_FLY:																// �_���[�W(�������)���[�V������������
				AllReleaseAttack(nIdy);
				break;
			case PLAYER_MOTION_TYPE_GETUP:																// �N���オ�胂�[�V������������
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP] = false;						// �N���オ��̏�Ԃ�����
				AllReleaseAttack(nIdy);
				break;
			case PLAYER_MOTION_TYPE_CATCH:
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CATCH] = false;						// �N���オ��̏�Ԃ�����
				AllReleaseAttack(nIdy);
				break;
			case PLAYER_MOTION_TYPE_THROW:
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_THROW] = false;						// �N���オ��̏�Ԃ�����
				AllReleaseAttack(nIdy);
				break;
			default:
				if (g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_WEAK||
					g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_WEAK_2 ||
					g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_WEAK_3 ||
					g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_WEAK_4 ||
					g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_WEAK_5 ||
					g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_SPECIAL)
				{

					if (!g_aPlayer[nIdy].bCombo)
					{// �R���{�I��
						g_aPlayer[nIdy].nComboCounter = 10;
						g_aPlayer[nIdy].bCombo = true;
					}
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CATCH] = false;
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_THROW] = false;						// �N���オ��̏�Ԃ�����
				}
				break;
			}
			g_aPlayer[nIdy].nMotionGetCol = PLAYER_MOTION_TYPE_MAX;
		}
		else
		{// ���̃L�[�����l��
			g_aPlayer[nIdy].nKeyCounter = (g_aPlayer[nIdy].nKeyCounter + 1) % g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].nNumKey;
		}
	}

}
//==============================================================================================================================
// �v���C���[�̑̂̓����蔻��
//==============================================================================================================================
bool CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 mtxWorld, float fRadius, float nPower, float fDamageSide, float fDamageV,int nIdy)
{
	bool bHit = false;
	if (GetCamera()->nState == CAMERASTATE_NONE || GetCamera()->nState == CAMERASTATE_SPECIAL)
	{
		for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
		{
			if (g_aPlayer[nCnt].bUse)
			{
				if (nCnt != nIdy)
				{
					if (g_aPlayer[nCnt].state != PLAYERSTATE_DEATH&&
						g_aPlayer[nCnt].state != PLAYERSTATE_INVINCIBLE&&
						g_aPlayer[nCnt].state != PLAYERSTATE_DAMAGE &&
						g_aPlayer[nCnt].state != PLAYERSTATE_CRASHSTART &&
						!g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_GETUP] &&
						!g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_FLY])
					{// ����łȂ�
						{// �_���[�W������Ȃ����
							for (int nCntCollision = 0; nCntCollision < MAX_COLLISION; nCntCollision++)
							{// �̂̓����蔻�蕪���[�v
								if (g_aPlayer[nCnt].ColBody[nCntCollision].bUse)
								{
									// ��̓����蔻��̍��W�̋������v�Z
									float PosX = (g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._41 - mtxWorld.x);		// (�v���C���[�̑̂̓����蔻��̍��W.x - �G�̍U���̓����蔻��̍��W.x)
									float PosY = (g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._42 - mtxWorld.y);		// (�v���C���[�̑̂̓����蔻��̍��W.y - �G�̍U���̓����蔻��̍��W.y)
									float PosZ = (g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._43 - mtxWorld.z);		// (�v���C���[�̑̂̓����蔻��̍��W.z - �G�̍U���̓����蔻��̍��W.z)

									float fPosLenght = (PosX * PosX) + (PosY * PosY) + (PosZ * PosZ);				// ���ꂼ���2�悵�Ă��ׂđ����ċ������o��
									// ��̓����蔻��̔��a�̋������v�Z
									float fCollisionRadius = (g_aPlayer[nCnt].ColBody[nCntCollision].fRadius + fRadius);	// �v���C���[�̑̂̓����蔻��̔��a+�G�̍U���̓����蔻��̔��a�𑫂�
									float fRadiusLenght = fCollisionRadius * fCollisionRadius;	// ��̔��a�𑫂����l��2�悵�āA���a�̋������v�Z���v�Z

									if (fRadiusLenght > fPosLenght &&
										-fRadiusLenght < fPosLenght)
									{// ���W�̋��������a�̋�������������������
										float fAttackAngle = atan2f(pos.x - g_aPlayer[nCnt].pos.x, pos.z - g_aPlayer[nCnt].pos.z);	// ���������p�x

										if (g_aPlayer[nCnt].nMotionGetCol != g_aPlayer[nIdy].nMotionType)
										{
											if (g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_GUARD])
											{// �K�[�h��
												g_aPlayer[nCnt].fLife -= 0;
												g_aPlayer[nCnt].fGuardLife -= (nPower/2.0f+ g_aPlayer[nIdy].fPulsAttack) / 10.0f;
												g_aPlayer[nCnt].nCntState = 3;
												PlaySound(SOUND_EFFECT_GUARD);
												for (int nCntE = 0; nCntE < 10; nCntE++)
												{// �N���b�V��
													D3DXVECTOR3 rot = D3DXVECTOR3(SetRandomEffect(), SetRandomEffect(), SetRandomEffect());
													D3DXVECTOR3 move = D3DXVECTOR3(sinf(rot.x) * 10, cosf(rot.y) * 10, cosf(rot.z) * 10);
													SetEffectUP(0,mtxWorld,
														move, rot, g_aPlayer[nCnt].col, EFFECTUPTYPE_GUARD, 15);
												}
											}
											else
											{
												float nPulusDamage = 1;
												if (g_aPlayer[nCnt].type == PLAYERTYPE_MOMIJI)
												{// �ς�����_������
													nPulusDamage = 1.3f;
												}
												g_aPlayer[nCnt].fLife -= (nPower + g_aPlayer[nIdy].fPulsAttack)* nPulusDamage;	// ���C�t�����炷
												if (g_aPlayer[nCnt].state == PLAYERSTATE_CRASH)
												{
													g_aPlayer[nCnt].nCntState = 0;
													g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_CRASH] = false;
													g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_FLY] = false;
													g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_GETUP] = false;
													g_aPlayer[nCnt].nFlyCounter = 0;
													g_aPlayer[nCnt].state = PLAYERSTATE_NONE;
													g_aPlayer[nCnt].fGuardLife = 0.5f;
												}
											}
											if (g_aPlayer[nCnt].fLife <= 0)
											{// ���C�t��0�ȉ��ɂȂ�����
												PlayerLifeZero(nCnt, fAttackAngle, fDamageSide, fDamageV);
											}
											else if (g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_GUARD])
											{// �K�[�h���Ă���
												// ���������̐�����ї͂���
												g_aPlayer[nCnt].fFlyPower.x = sinf(fAttackAngle - D3DX_PI) * fDamageSide * 3;
												g_aPlayer[nCnt].fFlyPower.z = cosf(fAttackAngle - D3DX_PI) * fDamageSide * 3;
												g_aPlayer[nCnt].nFlyCounter = 0;
												g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_FLY] = false;	// ������΂Ȃ�
												g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_DAMAGE] = false;// �_���[�W���[�V��������Ȃ�
												g_aPlayer[nCnt].state = PLAYERSTATE_DAMAGE;
												if (g_aPlayer[nCnt].fGuardLife <= 0)
												{// �K�[�h��ꂽ
													g_aPlayer[nCnt].fFlyPower.x = 0.0f;
													g_aPlayer[nCnt].fFlyPower.z = 0.0f;
													g_aPlayer[nCnt].fFlyPower.y = 10;
													g_aPlayer[nCnt].nFlyCounter = 10;
													g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_FLY] = true;	// ������΂Ȃ�
													PlaySound(SOUND_EFFECT_GUARD_CRASH);
													UnSetGuard(nCnt, g_aPlayer[nCnt].fGuardLife);
													g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_GUARD] = false;
													g_aPlayer[nCnt].state = PLAYERSTATE_CRASHSTART;
													g_aPlayer[nCnt].nCntState = 80;
													for (int nCntE = 0; nCntE < 100; nCntE++)
													{// �N���b�V��
														D3DXVECTOR3 rot = D3DXVECTOR3(SetRandomEffect(), SetRandomEffect(), SetRandomEffect());
														D3DXVECTOR3 move = D3DXVECTOR3(sinf(rot.x) * 10, cosf(rot.y) * 10, cosf(rot.z) * 10);
														SetEffectUP(0,D3DXVECTOR3(g_aPlayer[nCnt].aModel[3].mtxWorld._41, g_aPlayer[nCnt].aModel[3].mtxWorld._42, g_aPlayer[nCnt].aModel[3].mtxWorld._43),
															move, rot, g_aPlayer[nCnt].col, EFFECTUPTYPE_GUARD, 15);
													}
												}
											}
											else
											{// �q�b�g
												if (fDamageSide > 1.0f && fDamageV > 5.0f)
												{// ������ї͂�����Ƃ�
													PlaySound(SOUND_LABEL_HIT001);
													SetPlayerVoice(g_aPlayer[nCnt].type, PLAYER_MOTION_TYPE_FLY);
													g_aPlayer[nCnt].state = PLAYERSTATE_DAMAGE;
													g_aPlayer[nCnt].nCntState = 1;
													// ���������̐�����ї͂���
													g_aPlayer[nCnt].fFlyPower.x = sinf(fAttackAngle - D3DX_PI) * fDamageSide;
													g_aPlayer[nCnt].fFlyPower.z = cosf(fAttackAngle - D3DX_PI) * fDamageSide;
													// ���������̐�����ї͂���
													g_aPlayer[nCnt].fFlyPower.y = fDamageV;
													g_aPlayer[nCnt].nFlyCounter = 10;
													g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_FLY] = true;	// ������ђ��ɐݒ�

													g_aPlayer[nCnt].Destrot.y = fAttackAngle - D3DX_PI;		// �L�����N�^�[�̌�����ύX
													g_aPlayer[nCnt].rot.y = fAttackAngle - D3DX_PI;			// �L�����N�^�[�̌�����ύX
												}
												else
												{// �����̂�
													if ((g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_WEAK ||
														g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_WEAK_2) && MOMIJI)
													{
														if (g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_WEAK) { PlaySound(SOUND_EFFECT_SRASH000); }
														else { PlaySound(SOUND_EFFECT_SRASH001); }
														SetEffect(D3DXVECTOR3(g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._41, g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._42, g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._43) + D3DXVECTOR3(0.0f, 0.0f, -50), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0),
															D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 0, EFFECTTYPE_CARTOON_SLICE_0);
													}
													else
													{
														if (GOJOU || MOMIJI)
														{
															if (g_aPlayer[nIdy].nMotionType != PLAYER_MOTION_TYPE_SPECIAL)
															{
																SetEffect(D3DXVECTOR3(g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._41, g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._42, g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._43) + D3DXVECTOR3(0, 0, -50)
																	, D3DXVECTOR3(0, 0, 0),
																	D3DXVECTOR3(0, 0, 0),
																	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 0, EFFECTTYPE_CARTOON_DON);
															}
														}
														PlaySound(SOUND_LABEL_HIT000);
													}
													if (g_aPlayer[nCnt].type == PLAYERTYPE_DONROID &&
														(g_aPlayer[nCnt].bAttackType[PLAYER_ATTACK_TYPE_WEAK]  &&
														g_aPlayer[nCnt].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2]&&
															g_aPlayer[nCnt].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3]&&
															!g_aPlayer[nCnt].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4]&&
															!g_aPlayer[nCnt].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5])||
															(g_aPlayer[nCnt].bAttackType[PLAYER_ATTACK_TYPE_WEAK] &&
																g_aPlayer[nCnt].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] &&
																!g_aPlayer[nCnt].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] &&
																!g_aPlayer[nCnt].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] &&
																!g_aPlayer[nCnt].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5]))
													{// 2��3�Ԗڂ̓X�[�p�[�A�[�}�[
														g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_DAMAGE] = false;	// �_���[�W���ɐݒ�
													}
													else
													{// �_���[�W
														AllReleaseAttack(nCnt);
														SetPlayerVoice(g_aPlayer[nCnt].type, PLAYER_MOTION_TYPE_DAMAGE);
														// ������ї͂���
														g_aPlayer[nCnt].state = PLAYERSTATE_DAMAGE;
														g_aPlayer[nCnt].nCntState = 3;
														g_aPlayer[nCnt].fFlyPower.x = sinf(fAttackAngle - D3DX_PI) * fDamageSide;
														g_aPlayer[nCnt].fFlyPower.z = cosf(fAttackAngle - D3DX_PI) * fDamageSide;
														g_aPlayer[nCnt].fFlyPower.y = fDamageV;
														g_aPlayer[nCnt].nFlyCounter = 10;
														g_aPlayer[nCnt].Destrot.y = fAttackAngle - D3DX_PI;		// �L�����N�^�[�̌�����ύX
														g_aPlayer[nCnt].rot.y = fAttackAngle - D3DX_PI;			// �L�����N�^�[�̌�����ύX
														g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_DAMAGE] = true;	// �_���[�W���ɐݒ�
													}
												}

											}
											// �q�b�g�G�t�F�N�g
											HitEffect(D3DXVECTOR3(g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._41, g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._42, g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._43));

											bHit = true;	// ��������									// ���[�V�������擾
										}
										g_aPlayer[nCnt].nMotionGetCol = g_aPlayer[nIdy].nMotionType;
										g_aPlayer[nCnt].nStopTime = g_aPlayer[nCnt].ColAttack[g_aPlayer[nCnt].nMotionGetCol].nStopTime;
										break;
									}
								}
							}
						}
					}
				}
				// ���C�t�A��
				GetPlayerLife(int(g_aPlayer[nCnt].fLife), g_aPlayer[nCnt].nIdy);

			}
		}
	}
	return bHit;
}
bool CollisionPlayerEffect(D3DXVECTOR3 pos, D3DXVECTOR3 mtxWorld, float fRadius, float nPower, float fDamageSide, float fDamageV)
{
	bool bHit = false;
	if (GetCamera()->nState == CAMERASTATE_NONE || GetCamera()->nState == CAMERASTATE_SPECIAL)
	{
		for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
		{
			if (g_aPlayer[nCnt].bUse)
			{
				if (g_aPlayer[nCnt].state != PLAYERSTATE_DEATH&&
					g_aPlayer[nCnt].state != PLAYERSTATE_INVINCIBLE&&
					g_aPlayer[nCnt].state != PLAYERSTATE_DAMAGE &&
					g_aPlayer[nCnt].state != PLAYERSTATE_CRASHSTART &&
					!g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_GETUP] &&
					!g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_FLY])
				{// ����łȂ�
					{// �_���[�W������Ȃ����
						for (int nCntCollision = 0; nCntCollision < MAX_COLLISION; nCntCollision++)
						{// �̂̓����蔻�蕪���[�v
							if (g_aPlayer[nCnt].ColBody[nCntCollision].bUse)
							{
								// ��̓����蔻��̍��W�̋������v�Z
								float PosX = (g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._41 - mtxWorld.x);		// (�v���C���[�̑̂̓����蔻��̍��W.x - �G�̍U���̓����蔻��̍��W.x)
								float PosY = (g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._42 - mtxWorld.y);		// (�v���C���[�̑̂̓����蔻��̍��W.y - �G�̍U���̓����蔻��̍��W.y)
								float PosZ = (g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._43 - mtxWorld.z);		// (�v���C���[�̑̂̓����蔻��̍��W.z - �G�̍U���̓����蔻��̍��W.z)

								float fPosLenght = (PosX * PosX) + (PosY * PosY) + (PosZ * PosZ);				// ���ꂼ���2�悵�Ă��ׂđ����ċ������o��
																												// ��̓����蔻��̔��a�̋������v�Z
								float fCollisionRadius = (g_aPlayer[nCnt].ColBody[nCntCollision].fRadius + fRadius);	// �v���C���[�̑̂̓����蔻��̔��a+�G�̍U���̓����蔻��̔��a�𑫂�
								float fRadiusLenght = fCollisionRadius * fCollisionRadius;	// ��̔��a�𑫂����l��2�悵�āA���a�̋������v�Z���v�Z

								if (fRadiusLenght > fPosLenght &&
									-fRadiusLenght < fPosLenght)
								{// ���W�̋��������a�̋�������������������
									float fAttackAngle = atan2f(pos.x - g_aPlayer[nCnt].pos.x, pos.z - g_aPlayer[nCnt].pos.z);	// ���������p�x
									if (nPower > 0.0f)
									{

										if (g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_GUARD])
										{// �K�[�h��
											g_aPlayer[nCnt].fLife -= 0;
											g_aPlayer[nCnt].fGuardLife -= nPower/2.0f;
											g_aPlayer[nCnt].nCntState = 3;
										}
										else
										{

											g_aPlayer[nCnt].fLife -= nPower;	// ���C�t�����炷
											if (g_aPlayer[nCnt].state == PLAYERSTATE_CRASH)
											{
												g_aPlayer[nCnt].nCntState = 0;
												g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_CRASH] = false;
												g_aPlayer[nCnt].state = PLAYERSTATE_NONE;
												g_aPlayer[nCnt].fGuardLife = 0.5f;
											}
										}
										if (g_aPlayer[nCnt].fLife <= 0)
										{// ���C�t��0�ȉ��ɂȂ�����
											PlayerLifeZero(nCnt, fAttackAngle, fDamageSide, fDamageV);
										}
										else if (g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_GUARD])
										{// �K�[�h���Ă���
										 // ���������̐�����ї͂���
											g_aPlayer[nCnt].fFlyPower.x = sinf(fAttackAngle - D3DX_PI) * fDamageSide * 3;
											g_aPlayer[nCnt].fFlyPower.z = cosf(fAttackAngle - D3DX_PI) * fDamageSide * 3;
											g_aPlayer[nCnt].nFlyCounter = 0;
											g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_FLY] = false;	// ������΂Ȃ�
											g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_DAMAGE] = false;// �_���[�W���[�V��������Ȃ�
											g_aPlayer[nCnt].state = PLAYERSTATE_DAMAGE;
											if (g_aPlayer[nCnt].fGuardLife <= 0)
											{
												UnSetGuard(nCnt, g_aPlayer[nCnt].fGuardLife);
												g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_GUARD] = false;
												g_aPlayer[nCnt].state = PLAYERSTATE_CRASHSTART;
												g_aPlayer[nCnt].nCntState = 30;
												g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_CRASH] = true;	// ����
											}
										}
										else
										{// �q�b�g
											if (fDamageSide > 1.0f && fDamageV > 5.0f)
											{// ������ї͂�����Ƃ�
												PlaySound(SOUND_LABEL_HIT001);
												SetPlayerVoice(g_aPlayer[nCnt].type, PLAYER_MOTION_TYPE_FLY);
												g_aPlayer[nCnt].state = PLAYERSTATE_DAMAGE;
												g_aPlayer[nCnt].nCntState = 1;
												// ���������̐�����ї͂���
												g_aPlayer[nCnt].fFlyPower.x = sinf(fAttackAngle - D3DX_PI) * fDamageSide;
												g_aPlayer[nCnt].fFlyPower.z = cosf(fAttackAngle - D3DX_PI) * fDamageSide;
												// ���������̐�����ї͂���
												g_aPlayer[nCnt].fFlyPower.y = fDamageV;
												g_aPlayer[nCnt].nFlyCounter = 10;
												g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_FLY] = true;	// ������ђ��ɐݒ�

												g_aPlayer[nCnt].Destrot.y = fAttackAngle - D3DX_PI;		// �L�����N�^�[�̌�����ύX
												g_aPlayer[nCnt].rot.y = fAttackAngle - D3DX_PI;			// �L�����N�^�[�̌�����ύX
											}
											else
											{// �����̂�
												PlaySound(SOUND_LABEL_HIT000);
												AllReleaseAttack(nCnt);
												SetPlayerVoice(g_aPlayer[nCnt].type, PLAYER_MOTION_TYPE_DAMAGE);
												// ������ї͂���
												g_aPlayer[nCnt].state = PLAYERSTATE_DAMAGE;
												g_aPlayer[nCnt].nCntState = 3;
												g_aPlayer[nCnt].fFlyPower.x = sinf(fAttackAngle - D3DX_PI) * fDamageSide;
												g_aPlayer[nCnt].fFlyPower.z = cosf(fAttackAngle - D3DX_PI) * fDamageSide;
												g_aPlayer[nCnt].fFlyPower.y = fDamageV;
												g_aPlayer[nCnt].nFlyCounter = 10;
												g_aPlayer[nCnt].Destrot.y = fAttackAngle - D3DX_PI;		// �L�����N�^�[�̌�����ύX
												g_aPlayer[nCnt].rot.y = fAttackAngle - D3DX_PI;			// �L�����N�^�[�̌�����ύX
												g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_DAMAGE] = true;	// �_���[�W���ɐݒ�
											}
										}
										// �q�b�g�G�t�F�N�g
										HitEffect(D3DXVECTOR3(g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._41, g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._42, g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._43));

										bHit = true;	// ��������									// ���[�V�������擾
										break;
									}
									else
									{
										g_aPlayer[nCnt].move.x += sinf(fAttackAngle - D3DX_PI) * fDamageSide;
										g_aPlayer[nCnt].move.z += cosf(fAttackAngle - D3DX_PI) * fDamageSide;
									}
								}
							}
						}
					}
				}
				// ���C�t�A��
				GetPlayerLife(int(g_aPlayer[nCnt].fLife), g_aPlayer[nCnt].nIdy);

			}
		}
	}
	return bHit;

}
//==============================================================================================================================
// ����ݒ�(�U������j
//==============================================================================================================================
void SetAttackCollisionPlayer(int nIdy,int nIdxParent, D3DXVECTOR3 offset, float fRadius, int nCollisionStart, int nCollisionEnd,int nStopTime, PlayerMotionType nMotionType)
{
	for (int nCollision = 0; nCollision < MAX_COLLISION; nCollision++)
	{
		if (g_aPlayerData[nIdy].ColAttack[nCollision].bUse == false)
		{
			g_aPlayerData[nIdy].ColAttack[nCollision].nIdxParent = nIdxParent;
			g_aPlayerData[nIdy].ColAttack[nCollision].ofset = offset;
			g_aPlayerData[nIdy].ColAttack[nCollision].fRadius = fRadius;
			g_aPlayerData[nIdy].ColAttack[nCollision].nCollisionStart = nCollisionStart;
			g_aPlayerData[nIdy].ColAttack[nCollision].nCollisionEnd = nCollisionEnd;
			g_aPlayerData[nIdy].ColAttack[nCollision].nStopTime = nStopTime;
			g_aPlayerData[nIdy].ColAttack[nCollision].nMotionType = nMotionType;
			g_aPlayerData[nIdy].ColAttack[nCollision].bUse = true;
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&g_aPlayerData[nIdy].ColAttack[nCollision].mtxWorld, g_aPlayerData[nIdy].ColAttack[nCollision].ofset.x, g_aPlayerData[nIdy].ColAttack[nCollision].ofset.y, g_aPlayerData[nIdy].ColAttack[nCollision].ofset.z);
			D3DXMatrixMultiply(&g_aPlayerData[nIdy].ColAttack[nCollision].mtxWorld, &g_aPlayerData[nIdy].ColAttack[nCollision].mtxWorld, &g_aPlayerData[nIdy].aModel[g_aPlayerData[nIdy].ColAttack[nCollision].nIdxParent].mtxWorld);
			break;
		}
	}

}
//==============================================================================================================================
// ����ݒ�i�_���[�W����j
//==============================================================================================================================
void SetBodyCollisionPlayer(int nIdy,int nIdxParent, D3DXVECTOR3 offset, float fRadius)
{
	for (int nCollision = 0; nCollision < MAX_COLLISION; nCollision++)
	{
		if (g_aPlayerData[nIdy].ColBody[nCollision].bUse == false)
		{
			g_aPlayerData[nIdy].ColBody[nCollision].nIdxParent = nIdxParent;
			g_aPlayerData[nIdy].ColBody[nCollision].ofset = offset;
			g_aPlayerData[nIdy].ColBody[nCollision].fRadius = fRadius;
			g_aPlayerData[nIdy].ColBody[nCollision].bUse = true;
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&g_aPlayerData[nIdy].ColBody[nCollision].mtxWorld, g_aPlayerData[nIdy].ColBody[nCollision].ofset.x, g_aPlayerData[nIdy].ColBody[nCollision].ofset.y, g_aPlayerData[nIdy].ColAttack[nCollision].ofset.z);
			D3DXMatrixMultiply(&g_aPlayerData[nIdy].ColBody[nCollision].mtxWorld, &g_aPlayerData[nIdy].ColBody[nCollision].mtxWorld, &g_aPlayerData[nIdy].aModel[g_aPlayerData[nIdy].ColBody[nCollision].nIdxParent].mtxWorld);
			break;
		}
	}

}
//==============================================================================================================================
// �v���C���[�̑���
//==============================================================================================================================
void PlayerController(int nIdy)
{
	GamePad *pGamePad = GetgamePadStick();
	Camera *pCamera = GetCamera();
	g_aPlayer[0].CtrlMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer[1].CtrlMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer[2].CtrlMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer[3].CtrlMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer[nIdy].nStopTime--;
	if (g_aPlayer[nIdy].nStopTime <= 0)
	{
		g_aPlayer[nIdy].nStopTime = 0;
	}
#if 1
	static int nCon = 4;
	if (GetKeyboardTrigger(DIK_0))
	{
		nCon = 0;
	}
	else if (GetKeyboardTrigger(DIK_1))
	{
		nCon = 1;
	}
	else if (GetKeyboardTrigger(DIK_2))
	{
		nCon = 2;
	}
	else if (GetKeyboardTrigger(DIK_3))
	{
		nCon = 3;
	}
	else if (GetKeyboardTrigger(DIK_4))
	{
		nCon = 4;
	}
	if (nCon == nIdy)
	{
		if (GetKeyboardPress(DIK_W) )
		{// �O�ړ�
			if (GetKeyboardPress(DIK_D) )
			{// �E�΂ߑO�ړ�
				g_aPlayer[nIdy].CtrlMove.x = sinf(D3DX_PI / 4 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].CtrlMove.z = cosf(D3DX_PI / 4 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].Destrot.y = -D3DX_PI / 4 * 3 + pCamera->rot.y;	// �ړI�̊p�x
			}
			else if (GetKeyboardPress(DIK_A) )
			{// ���΂ߑO�ړ�
				g_aPlayer[nIdy].CtrlMove.x = sinf(-D3DX_PI / 4 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].CtrlMove.z = cosf(-D3DX_PI / 4 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].Destrot.y = D3DX_PI / 4 * 3 + pCamera->rot.y;	// �ړI�̊p�x
			}
			else
			{// �O�ړ�
				g_aPlayer[nIdy].CtrlMove.x = sinf(0.0f + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].CtrlMove.z = cosf(0.0f + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].Destrot.y = D3DX_PI + pCamera->rot.y;		// �ړI�̊p�x
			}
		}
		else if (GetKeyboardPress(DIK_S) )
		{// ���ړ�
			if (GetKeyboardPress(DIK_D) )
			{// �E�΂ߌ��ړ�
				g_aPlayer[nIdy].CtrlMove.x = sinf(D3DX_PI / 4 * 3 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].CtrlMove.z = cosf(D3DX_PI / 4 * 3 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].Destrot.y = -D3DX_PI / 4 + pCamera->rot.y;	// �ړI�̊p�x
			}
			else if (GetKeyboardPress(DIK_A) )
			{// ���΂ߌ��ړ�
				g_aPlayer[nIdy].CtrlMove.x = sinf(-D3DX_PI / 4 * 3 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].CtrlMove.z = cosf(-D3DX_PI / 4 * 3 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].Destrot.y = D3DX_PI / 4 + pCamera->rot.y;	// �ړI�̊p�x
			}
			else
			{// ���ړ�
				g_aPlayer[nIdy].CtrlMove.x = sinf(D3DX_PI + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].CtrlMove.z = cosf(D3DX_PI + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].Destrot.y = 0.0f + pCamera->rot.y;		// �ړI�̊p�x
			}
		}
		else if (GetKeyboardPress(DIK_D) )
		{// �E�ړ�
			g_aPlayer[nIdy].CtrlMove.x = sinf(D3DX_PI / 2 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
			g_aPlayer[nIdy].CtrlMove.z = cosf(D3DX_PI / 2 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
			g_aPlayer[nIdy].Destrot.y = -D3DX_PI / 2 + pCamera->rot.y;	// �ړI�̊p�x
		}
		else if (GetKeyboardPress(DIK_A) )
		{// ���ړ�
			g_aPlayer[nIdy].CtrlMove.x = sinf(-D3DX_PI / 2 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
			g_aPlayer[nIdy].CtrlMove.z = cosf(-D3DX_PI / 2 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
			g_aPlayer[nIdy].Destrot.y = D3DX_PI / 2 + pCamera->rot.y;	// �ړI�̊p�x
		}

		if (g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_NEUTRAL ||
			g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_MOVE ||
			g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_JUMP)
		{// ����̃��[�V���������ړ��ʉ��Z
			if (g_aPlayer[nIdy].bJump)
			{// �W�����v���Ȃ�ړ��ʔ���
				g_aPlayer[nIdy].CtrlMove.x = g_aPlayer[nIdy].CtrlMove.x / DOWN_JUMP_SPEED;
				g_aPlayer[nIdy].CtrlMove.z = g_aPlayer[nIdy].CtrlMove.z / DOWN_JUMP_SPEED;
			}
			g_aPlayer[nIdy].move += g_aPlayer[nIdy].CtrlMove;
		}

		if (!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_DAMAGE] &&
			!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] &&
			!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP] &&
			!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CRASH] &&
			!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD]&&
			g_aPlayer[nIdy].state!=PLAYERSTATE_DAMAGE&&
			g_aPlayer[nIdy].nStopTime == 0)
		{// ������т��Ă��Ȃ����
			if (GetKeyboardTrigger(DIK_K))
			{// ��
				if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK])
				{// �サ�ĂȂ����
					g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK] = true;
				}
				else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] &&
					g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK])
				{// ��2
					if (MATURI)
					{// �l
						if (g_aPlayer[nIdy].nFrameAllCounter >= 15) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
					}
					if (AMANO)
					{// �V��
						if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
					}
					if (GOJOU)
					{// �͓�
						if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
					}
					if (MOMIJI)
					{// ��
						if (g_aPlayer[nIdy].nKeyCounter >= 3) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
					}
					if (DONROID)
					{// ���{�b�g
						if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
					}
				}
				else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] &&
					g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2])
				{// ��3
					if (MATURI)
					{// �l
						if (g_aPlayer[nIdy].nFrameAllCounter >= 10) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
					}
					if (AMANO)
					{// �V��
						if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
					}
					if (GOJOU)
					{// �͓�
						if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
					}
					if (MOMIJI)
					{// ��
						if (g_aPlayer[nIdy].nKeyCounter >= 3) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
					}
					if (DONROID)
					{// ���{�b�g
						if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
					}
				}
				else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] &&
					g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3])
				{// ��4
					if (MATURI)
					{// �l
						if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
					}
					if (AMANO)
					{// �V��
						if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
					}
					if (GOJOU)
					{// �͓�
						if (g_aPlayer[nIdy].nKeyCounter >= 4){g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true;}
					}
					if (MOMIJI)
					{// ��
						if (g_aPlayer[nIdy].nKeyCounter >= 5) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
					}
					if (DONROID)
					{// ���{�b�g
						if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
					}
				}
				else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] &&
					g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4])
				{// ��5
					if (MATURI)
					{// �l
						if (g_aPlayer[nIdy].nFrameAllCounter >= 25) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
					}
					if (AMANO)
					{// �V��
						if (g_aPlayer[nIdy].nFrameAllCounter >= 50) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
					}
					if (GOJOU)
					{// �͓�
						if (g_aPlayer[nIdy].nFrameAllCounter >= 35) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
					}
					if (MOMIJI)
					{// ��
						if (g_aPlayer[nIdy].nKeyCounter >= 4){g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true;}
					}
					if (DONROID)
					{// ���{�b�g
						if (g_aPlayer[nIdy].nFrameAllCounter >= 35) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
					}
				}

			}

			if (GetKeyboardTrigger(DIK_J))
			{// ����
				if (g_aPlayer[nIdy].bCatch)
				{
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_THROW ]= true;	// ����

				}
				else
				{
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CATCH] = true;	// ����
				}
			}
		}

		if (!g_aPlayer[nIdy].bJump &&
			!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] &&
			!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_DAMAGE] &&
			!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] &&
			!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP]&&
			!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_SPECIAL])
		{// �W�����v&������т��Ă��Ȃ����
			if (GetKeyboardTrigger(DIK_E))
			{
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_WIN] = true;
				g_aPlayer[nIdy].nCntEmote = 60;
			}

			if (GetKeyboardTrigger(DIK_SPACE)&&!bAttackOn(nIdy))
			{// �W�����v
				PlaySound(SOUND_LABEL_JUMP);
				g_aPlayer[nIdy].move.y = g_aPlayer[nIdy].JumpSpeed;	// �ړ��ʉ��Z
				g_aPlayer[nIdy].bJump = true;
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] = true;
			}
			if (GetKeyboardTrigger(DIK_B))
			{// �K�E�Z
				if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_SPECIAL] && g_aPlayer[nIdy].nSp > 0 && !bAttackOn(nIdy))
				{// �K�E�Z
					if (pCamera[0].nState != CAMERASTATE_SPECIAL)
					{
						g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_SPECIAL] = true;
						g_aPlayer[nIdy].nSp--;
						DeleteSp(nIdy);
						pCamera[0].posRDest = g_aPlayer[nIdy].pos;
						pCamera[0].nState = CAMERASTATE_SPECIAL;
						pCamera[0].nStateCounter = MAX_CAMERASTATE;

						if (g_bStartCutIn == false)
						{
							SetSpecialUse(true);		//�K�E�Z�����Ă����Ԃɂ���
							g_nSpecialPlayer = nIdy;	//Id�̕ۑ�
							g_bStartCutIn = true;		//�J�b�g�C��������Ă����Ԃɂ���
						}
					}
				}
			}
			if (GetKeyboardPress(DIK_G))
			{// �K�[�h
				if (!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CRASH] && g_aPlayer[nIdy].fGuardLife > 0&&!bAttackOn(nIdy))
				{
					SetGuard(nIdy, D3DXVECTOR3(g_aPlayer[nIdy].aModel[0].mtxWorld._41, g_aPlayer[nIdy].aModel[0].mtxWorld._42, g_aPlayer[nIdy].aModel[0].mtxWorld._43), g_aPlayer[nIdy].fGuardLife);

					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD] = true;
				}
			}
			else
			{// �K�[�h�L�����Z��
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD] = false;
				UnSetGuard(nIdy, g_aPlayer[nIdy].fGuardLife);
			}
		}
		else
		{// �K�[�h�L�����Z��
			g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD] = false;
			UnSetGuard(nIdy, g_aPlayer[nIdy].fGuardLife);
		}
	}
#endif
	//else
	{
#if 1
		if (pGamePad[nIdy].pDevGamePad != NULL)
		{
			if (pGamePad[nIdy].aGamePad.lX < -WARKZONE || pGamePad[nIdy].aGamePad.lX > WARKZONE || pGamePad[nIdy].aGamePad.lY < -WARKZONE || pGamePad[nIdy].aGamePad.lY> WARKZONE)
			{
				float fGamePagStickAngle = atan2f(float(-pGamePad[nIdy].aGamePad.lX), float(pGamePad[nIdy].aGamePad.lY));

				g_aPlayer[nIdy].CtrlMove.x = sinf(fGamePagStickAngle + D3DX_PI + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].CtrlMove.z = cosf(fGamePagStickAngle + D3DX_PI + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].Destrot.y = fGamePagStickAngle + pCamera->rot.y;	// �ړI�̊p�x
			}
			if (g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_NEUTRAL ||
				g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_MOVE ||
				g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_JUMP)
			{// ����̃��[�V���������ړ��ʉ��Z
				if (g_aPlayer[nIdy].bJump)
				{// �W�����v���Ȃ�ړ��ʔ���
					g_aPlayer[nIdy].CtrlMove.x = g_aPlayer[nIdy].CtrlMove.x / DOWN_JUMP_SPEED;
					g_aPlayer[nIdy].CtrlMove.z = g_aPlayer[nIdy].CtrlMove.z / DOWN_JUMP_SPEED;
				}
				g_aPlayer[nIdy].move += g_aPlayer[nIdy].CtrlMove;
			}
			if (!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_DAMAGE] &&
				!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] &&
				!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP] &&
				!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CRASH] &&
				!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD]&&
				g_aPlayer[nIdy].state != PLAYERSTATE_DAMAGE&&
				g_aPlayer[nIdy].nStopTime <= 0)
			{// ������т��Ă��Ȃ����
				if (GetGamePadTrigger(nIdy, BUTTON_B))
				{// ��
					if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK])
					{// �サ�ĂȂ����
						g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK] = true;
					}
					else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] &&
						g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK])
					{// ��2
						if (MATURI)
						{// �l
							if (g_aPlayer[nIdy].nFrameAllCounter >= 15) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
						}
						if (AMANO)
						{// �V��
							if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
						}
						if (GOJOU)
						{// �͓�
							if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
						}
						if (MOMIJI)
						{// ��
							if (g_aPlayer[nIdy].nKeyCounter >= 3) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
						}
						if (DONROID)
						{// ���{�b�g
							if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
						}
					}
					else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] &&
						g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2])
					{// ��3
						if (MATURI)
						{// �l
							if (g_aPlayer[nIdy].nFrameAllCounter >= 10) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
						}
						if (AMANO)
						{// �V��
							if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
						}
						if (GOJOU)
						{// �͓�
							if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
						}
						if (MOMIJI)
						{// ��
							if (g_aPlayer[nIdy].nKeyCounter >= 3) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
						}
						if (DONROID)
						{// ���{�b�g
							if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
						}
					}
					else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] &&
						g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3])
					{// ��4
						if (MATURI)
						{// �l
							if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
						}
						if (AMANO)
						{// �V��
							if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
						}
						if (GOJOU)
						{// �͓�
							if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
						}
						if (MOMIJI)
						{// ��
							if (g_aPlayer[nIdy].nKeyCounter >= 5) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
						}
						if (DONROID)
						{// ���{�b�g
							if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
						}
					}
					else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] &&
						g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4])
					{// ��5
						if (MATURI)
						{// �l
							if (g_aPlayer[nIdy].nFrameAllCounter >= 25) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
						}

						if (AMANO)
						{// �V��
							if (g_aPlayer[nIdy].nFrameAllCounter >= 50) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
						}
						if (GOJOU)
						{// �͓�
							if (g_aPlayer[nIdy].nFrameAllCounter >= 35) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
						}
						if (MOMIJI)
						{// ��
							if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
						}
						if (DONROID)
						{// ���{�b�g
							if (g_aPlayer[nIdy].nFrameAllCounter >= 35) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
						}
					}

				}

				if (GetGamePadTrigger(nIdy, BUTTON_R1))
				{// ����
					if (g_aPlayer[nIdy].bCatch)
					{
						g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_THROW] = true;	// ����

					}
					else
					{
						g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CATCH] = true;	// ����

					}
				}

			}
			if (!g_aPlayer[nIdy].bJump &&
				!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] &&
				!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_DAMAGE] &&
				!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] &&
				!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP]&&
				!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_SPECIAL])

			{// �W�����v&������т��Ă��Ȃ����
				if (GetPovTtigger(nIdy, POV_DOWN) || GetPovTtigger(nIdy, POV_UP) || GetPovTtigger(nIdy, POV_RIGHT) || GetPovTtigger(nIdy, POV_LEFT))
				{
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_WIN] = true;
					g_aPlayer[nIdy].nCntEmote = 60;
				}

				if (GetGamePadTrigger(nIdy, BUTTON_A) && !bAttackOn(nIdy))
				{// �W�����v
					PlaySound(SOUND_LABEL_JUMP);
					g_aPlayer[nIdy].move.y = g_aPlayer[nIdy].JumpSpeed;	// �ړ��ʉ��Z
					g_aPlayer[nIdy].bJump = true;
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] = true;
				}
				if (GetGamePadTrigger(nIdy, BUTTON_X))
				{// �K�E�Z
					if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_SPECIAL] && g_aPlayer[nIdy].nSp > 0 && !bAttackOn(nIdy))
					{// �K�E�Z
						if (pCamera[0].nState != CAMERASTATE_SPECIAL)
						{
							g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_SPECIAL] = true;
							g_aPlayer[nIdy].nSp--;
							DeleteSp(nIdy);
							pCamera[0].posRDest = g_aPlayer[nIdy].pos;
							pCamera[0].nState = CAMERASTATE_SPECIAL;
							pCamera[0].nStateCounter = MAX_CAMERASTATE;

							if (g_bStartCutIn == false)
							{
								SetSpecialUse(true);		//�K�E�Z�����Ă����Ԃɂ���
								g_nSpecialPlayer = nIdy;	//Id�̕ۑ�
								g_bStartCutIn = true;		//�J�b�g�C��������Ă����Ԃɂ���
							}
						}
					}
				}
				if (GetGamePadPress(nIdy, BUTTON_L1))
				{// �K�[�h
					if (!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CRASH] && g_aPlayer[nIdy].fGuardLife > 0 && !bAttackOn(nIdy))
					{
						SetGuard(nIdy, D3DXVECTOR3(g_aPlayer[nIdy].aModel[0].mtxWorld._41, g_aPlayer[nIdy].aModel[0].mtxWorld._42, g_aPlayer[nIdy].aModel[0].mtxWorld._43), g_aPlayer[nIdy].fGuardLife);
						g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD] = true;
					}
				}
				else
				{// �K�[�h�L�����Z��
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD] = false;
					UnSetGuard(nIdy, g_aPlayer[nIdy].fGuardLife);
				}
			}
			else
			{// �K�[�h�L�����Z��
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD] = false;
				UnSetGuard(nIdy, g_aPlayer[nIdy].fGuardLife);
			}
		}
#endif
	}
}
//==============================================================================================================================
// �v���C���[���m�̏Փ˂̔���
//==============================================================================================================================
void PlayerOverLap(int nIdy)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (g_aPlayer[nCnt].bUse)
		{
			if (g_aPlayer[nIdy].state != PLAYERSTATE_DEATH || g_aPlayer[nCnt].state != PLAYERSTATE_DAMAGE)
			{
				if (nIdy != g_aPlayer[nCnt].nIdy)
				{
					// �G�Ɠ�������̂̋���
					float fPosX = (g_aPlayer[nIdy].pos.x - g_aPlayer[nCnt].pos.x);
					float fPosY = (g_aPlayer[nIdy].pos.y - g_aPlayer[nCnt].pos.y);
					float fPosZ = (g_aPlayer[nIdy].pos.z - g_aPlayer[nCnt].pos.z);
					float fRadiusA = fPosX*fPosX + fPosY*fPosY + fPosZ*fPosZ;
					float fRadiusB = 0;

					fRadiusB = (g_aPlayer[nIdy].fRadiusWidth + g_aPlayer[nIdy].fRadiusWidth)* (g_aPlayer[nCnt].fRadiusWidth + g_aPlayer[nCnt].fRadiusWidth);

					if (fRadiusB > fRadiusA&&
						-fRadiusB < fRadiusA)
					{// �l�Ɛl�̂����蔻��
						float fAngle2 = atan2f(g_aPlayer[nIdy].mtxWorld._41 - g_aPlayer[nCnt].pos.x, g_aPlayer[nIdy].mtxWorld._43 - g_aPlayer[nCnt].pos.z);
						g_aPlayer[nIdy].pos.x = g_aPlayer[nCnt].pos.x + sinf(fAngle2) * (g_aPlayer[nIdy].fRadiusWidth + g_aPlayer[nCnt].fRadiusWidth);
						g_aPlayer[nIdy].pos.z = g_aPlayer[nCnt].pos.z + cosf(fAngle2) * (g_aPlayer[nIdy].fRadiusWidth + g_aPlayer[nCnt].fRadiusWidth);
					}
				}

			}
		}
	}

}
//==============================================================================================================================
// �v���C���[�̃^�C�v�ݒ�
//==============================================================================================================================
void SetPlayer(int nIdy, D3DXVECTOR3 pos, PLAYERTYPE type)
{
	if (!g_aPlayer[nIdy].bUse)
	{
		g_nNumAll++;
		g_aPlayer[nIdy].type = type;
		g_aPlayer[nIdy].pos = pos;
		g_aPlayer[nIdy].MoveSpeed = g_aPlayerData[g_aPlayer[nIdy].type].MoveSpeed;
		g_aPlayer[nIdy].JumpSpeed = g_aPlayerData[g_aPlayer[nIdy].type].JumpSpeed;
		g_aPlayer[nIdy].fRadiusWidth = g_aPlayerData[g_aPlayer[nIdy].type].fRadiusWidth;
		g_aPlayer[nIdy].fRadiusHeight = g_aPlayerData[g_aPlayer[nIdy].type].fRadiusHeight;
		g_aPlayer[nIdy].fLife = float(g_aPlayerData[g_aPlayer[nIdy].type].nInitLife);
		g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_NEUTRAL;	// ���[�V�����^�C�v
		g_aPlayer[nIdy].nMotionTypeOld = PLAYER_MOTION_TYPE_MAX;	// �O��̃��[�V�����^�C�v
		g_aPlayer[nIdy].nMotionGetCol = PLAYER_MOTION_TYPE_NEUTRAL;	// ���[�V�����^�C�v
		g_aPlayer[nIdy].nMotionGetColOld = PLAYER_MOTION_TYPE_MAX;	// �O��̃��[�V�����^�C�v
		g_aPlayer[nIdy].nIdy = nIdy;
		for (int nbMotion = 0; nbMotion < PLAYER_BOOL_MAX; nbMotion++)
		{
			g_aPlayer[nIdy].bMotionState[nbMotion] = false;
			g_aPlayer[nIdy].bMotionStateOld[nbMotion] = false;
		}
		for (int nbMotion = 0; nbMotion < PLAYER_ATTACK_TYPE_MAX; nbMotion++)
		{
			g_aPlayer[nIdy].bAttackType[nbMotion] = false;
		}
		for (int nCollision = 0; nCollision < MAX_COLLISION; nCollision++)
		{// �_���[�W�ݒ�
			g_aPlayer[nIdy].ColBody[nCollision].nIdxParent = g_aPlayerData[g_aPlayer[nIdy].type].ColBody[nCollision].nIdxParent;
			g_aPlayer[nIdy].ColBody[nCollision].ofset = g_aPlayerData[g_aPlayer[nIdy].type].ColBody[nCollision].ofset;
			g_aPlayer[nIdy].ColBody[nCollision].fRadius = g_aPlayerData[g_aPlayer[nIdy].type].ColBody[nCollision].fRadius;
			g_aPlayer[nIdy].ColBody[nCollision].bUse = g_aPlayerData[g_aPlayer[nIdy].type].ColBody[nCollision].bUse;
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&g_aPlayer[nIdy].ColBody[nCollision].mtxWorld, g_aPlayer[nIdy].ColBody[nCollision].ofset.x, g_aPlayer[nIdy].ColBody[nCollision].ofset.y, g_aPlayer[nIdy].ColAttack[nCollision].ofset.z);
			D3DXMatrixMultiply(&g_aPlayer[nIdy].ColBody[nCollision].mtxWorld, &g_aPlayer[nIdy].ColBody[nCollision].mtxWorld, &g_aPlayer[nIdy].aModel[g_aPlayer[nIdy].ColBody[nCollision].nIdxParent].mtxWorld);
		}
		for (int nCollision = 0; nCollision < MAX_COLLISION; nCollision++)
		{// �U���ݒ�
			g_aPlayer[nIdy].ColAttack[nCollision].nIdxParent = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].nIdxParent;
			g_aPlayer[nIdy].ColAttack[nCollision].ofset = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].ofset;
			g_aPlayer[nIdy].ColAttack[nCollision].fRadius = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].fRadius;
			g_aPlayer[nIdy].ColAttack[nCollision].nCollisionStart = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].nCollisionStart;
			g_aPlayer[nIdy].ColAttack[nCollision].nCollisionEnd = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].nCollisionEnd;
			g_aPlayer[nIdy].ColAttack[nCollision].nStopTime = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].nStopTime;
			g_aPlayer[nIdy].ColAttack[nCollision].nMotionType = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].nMotionType;
			g_aPlayer[nIdy].ColAttack[nCollision].bUse = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].bUse;
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&g_aPlayer[nIdy].ColAttack[nCollision].mtxWorld, g_aPlayer[nIdy].ColAttack[nCollision].ofset.x, g_aPlayer[nIdy].ColAttack[nCollision].ofset.y, g_aPlayer[nIdy].ColAttack[nCollision].ofset.z);
			D3DXMatrixMultiply(&g_aPlayer[nIdy].ColAttack[nCollision].mtxWorld, &g_aPlayer[nIdy].ColAttack[nCollision].mtxWorld, &g_aPlayer[nIdy].aModel[g_aPlayer[nIdy].ColAttack[nCollision].nIdxParent].mtxWorld);

		}
		for (int nIdyModel = 0; nIdyModel < g_aPlayerData[g_aPlayer[nIdy].type].nNumParts; nIdyModel++)
		{// ���f�������ʒu�ݒ�
			g_aPlayer[nIdy].aModel[nIdyModel].pos = g_aPlayerData[g_aPlayer[nIdy].type].aModel[nIdyModel].pos;
			g_aPlayer[nIdy].aModel[nIdyModel].Initpos = g_aPlayerData[g_aPlayer[nIdy].type].aModel[nIdyModel].pos;
			g_aPlayer[nIdy].aModel[nIdyModel].rot = g_aPlayerData[g_aPlayer[nIdy].type].aModel[nIdyModel].rot;
			g_aPlayer[nIdy].aModel[nIdyModel].rot = g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].aKey[0].aPartsKey[nIdyModel].rot;
		}
		for (int nIdyMotion = 0; nIdyMotion < PLAYER_MOTION_TYPE_MAX; nIdyMotion++)
		{
			for (int nIdyOrbit = 0; nIdyOrbit < MAX_PLAYER_ORBIT; nIdyOrbit++)
			{
				g_aPlayer[nIdy].orbit[nIdyMotion][nIdyOrbit].nIdyOrbit = g_aPlayerData[g_aPlayer[nIdy].type].orbit[nIdyMotion][nIdyOrbit].nIdyOrbit;				// �O�Ղ̐�
				g_aPlayer[nIdy].orbit[nIdyMotion][nIdyOrbit].nOrbitLength = g_aPlayerData[g_aPlayer[nIdy].type].orbit[nIdyMotion][nIdyOrbit].nOrbitLength;		// �O�Ղ̒���
				g_aPlayer[nIdy].orbit[nIdyMotion][nIdyOrbit].OrbitStart = g_aPlayerData[g_aPlayer[nIdy].type].orbit[nIdyMotion][nIdyOrbit].OrbitStart;			// ���_
				g_aPlayer[nIdy].orbit[nIdyMotion][nIdyOrbit].OrbitEnd = g_aPlayerData[g_aPlayer[nIdy].type].orbit[nIdyMotion][nIdyOrbit].OrbitEnd;				// �I�_
				g_aPlayer[nIdy].orbit[nIdyMotion][nIdyOrbit].nType = g_aPlayerData[g_aPlayer[nIdy].type].orbit[nIdyMotion][nIdyOrbit].nType;					// �O�Ղ̃^�C�v
				g_aPlayer[nIdy].orbit[nIdyMotion][nIdyOrbit].motion = g_aPlayerData[g_aPlayer[nIdy].type].orbit[nIdyMotion][nIdyOrbit].motion;	// ���[�V����
			}
		}
		if (GetMode() == MODE_GAME)
		{
			// �e�ݒ�
			g_aPlayer[nIdy].nIdyShadow = SetShadow(g_aPlayer[nIdy].pos, g_aPlayer[nIdy].rot, g_aPlayer[nIdy].fRadiusWidth * 2.5f, g_aPlayer[nIdy].fRadiusWidth);
			// ���C������ݒ�
			g_aPlayer[nIdy].nIdyLine = CollisionLine(g_aPlayer[nIdy].pos, D3DXVECTOR3(-g_aPlayer[nIdy].fRadiusWidth, 0.0f, -g_aPlayer[nIdy].fRadiusWidth), D3DXVECTOR3(g_aPlayer[nIdy].fRadiusWidth, g_aPlayer[nIdy].fRadiusHeight, g_aPlayer[nIdy].fRadiusWidth), LINETYPE_PLAYER);
			// ���C�t�ݒ�
			SetPlayerLife(int(g_aPlayer[nIdy].fLife), g_aPlayer[nIdy].nIdy);
		}
		g_aPlayer[nIdy].bUse = true;
	}
}
void ReleasePlayer(int nIdy)
{
	if (g_aPlayer[nIdy].bUse)
	{
		g_nNumAll--;
		g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_NEUTRAL;	// ���[�V�����^�C�v
		g_aPlayer[nIdy].nMotionTypeOld = PLAYER_MOTION_TYPE_MAX;	// �O��̃��[�V�����^�C�v
		g_aPlayer[nIdy].nMotionGetCol = PLAYER_MOTION_TYPE_NEUTRAL;	// ���[�V�����^�C�v
		g_aPlayer[nIdy].nMotionGetColOld = PLAYER_MOTION_TYPE_MAX;	// �O��̃��[�V�����^�C�v
		g_aPlayer[nIdy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
		g_aPlayer[nIdy].Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]�̍���
		g_aPlayer[nIdy].Destrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړI�̉�]
		g_aPlayer[nIdy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]
		g_aPlayer[nIdy].Environment = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//��

		for (int nIdySound = 0; nIdySound < SOUND_LABEL_MAX; nIdySound++)
		{// ��
			g_aPlayer[nIdy].bSound[nIdySound] = false;
		}
		g_aPlayer[nIdy].state = PLAYERSTATE_NONE;
		g_aPlayer[nIdy].nCntState = 0;
		g_aPlayer[nIdy].pMeshFieldLand = NULL;
		g_aPlayer[nIdy].pModel = NULL;
		g_aPlayer[nIdy].pModelAtk = NULL;
		for (int nbMotion = 0; nbMotion < PLAYER_BOOL_MAX; nbMotion++)
		{
			g_aPlayer[nIdy].bMotionState[nbMotion] = false;
			g_aPlayer[nIdy].bMotionStateOld[nbMotion] = false;
		}
		for (int nbMotion = 0; nbMotion < PLAYER_ATTACK_TYPE_MAX; nbMotion++)
		{
			g_aPlayer[nIdy].bAttackType[nbMotion] = false;
		}
		g_aPlayer[nIdy].bBlend = false;
		g_aPlayer[nIdy].nDamage = 0;
		g_aPlayer[nIdy].bJump = false;							// �W�����v
		g_aPlayer[nIdy].nFlyCounter = 0;						// ���ł��鎞��
		g_aPlayer[nIdy].fRotSpeed = 0.0f;						// ��]�̌����X�s�[�h
		g_aPlayer[nIdy].nAirCounter = 0;						// ���V���̍U������J�E���^�[
		g_aPlayer[nIdy].nLoopCounter = 0;						// ���[�v�J�E���^�[
		g_aPlayer[nIdy].nIdy = nIdy;							// �ԍ�
		g_aPlayer[nIdy].nKeyCounter = 0;		// �L�[��
		g_aPlayer[nIdy].nFrameCounter = 0;		// �t���[����
		g_aPlayer[nIdy].nFrameAllCounter = 0;	// �ő�t���[��
		g_aPlayer[nIdy].nFrame = 0;				// �t���[��
		g_aPlayer[nIdy].fGuardLife = MAX_SKY;		// �K�[�h�̃��C�t
		g_aPlayer[nIdy].bUse = false;
		g_aPlayer[nIdy].bDraw = true;			// �f���Ă邩�ǂ���
		g_aPlayer[nIdy].fPulsLife = 0;			// �A�C�e���ő����郉�C�t
		g_aPlayer[nIdy].fPulsAttack = 0;		// �A�C�e���ŉ��Z�����U����
		g_aPlayer[nIdy].fPulsSpeed = 0;			// �A�C�e���ő�����X�s�[�h
		g_aPlayer[nIdy].nItemTime = 0;			// �A�C�e���p������
		g_aPlayer[nIdy].nSp = MAX_SP;
		g_aPlayer[nIdy].nComboCounter = 0;			// �R���{�J�E���^�[
		g_aPlayer[nIdy].bCombo = false;				// �R���{
		g_aPlayer[nIdy].typeInfo = PLAYERTYPE_MAX;
		g_aPlayer[nIdy].nCntEmote = 0;				// �G���[�g
		g_aPlayer[nIdy].bSpecial = false;
	}
}
void SetTypePlayer(int nIdy, PLAYERTYPE type)
{
	g_aPlayer[nIdy].typeInfo = type;
}
//==============================================================================================================================
// �v���C���[�̃G�t�F�N�g
//==============================================================================================================================
void PlayerMotionEffect(int nCntPlayer, int nCollision)
{
//	SetEffect(D3DXVECTOR3(g_aPlayer[nCntPlayer].ColAttack[nCollision].mtxWorld._41, g_aPlayer[nCntPlayer].ColAttack[nCollision].mtxWorld._42, g_aPlayer[nCntPlayer].ColAttack[nCollision].mtxWorld._43), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aPlayer[nCntPlayer].ColAttack[nCollision].fRadius, 10,EFFECTTYPE_SMOKE);
}
//==============================================================================================================================
// �v���C���[�̔���
//==============================================================================================================================
void PlayerColInfo(int nIdy)
{
	// �U�����菈��
	for (int nCnt = 0; nCnt < MAX_COLLISION; nCnt++)
	{
		if (g_aPlayer[nIdy].ColAttack[nCnt].bUse == true)
		{
			if (g_aPlayer[nIdy].ColAttack[nCnt].nMotionType == g_aPlayer[nIdy].nMotionType)
			{// ���߂��X�e�[�g�ƍ��̃X�e�[�g���ꏏ�������画��J�n
				if (g_aPlayer[nIdy].nFrameAllCounter >= g_aPlayer[nIdy].ColAttack[nCnt].nCollisionStart &&
					g_aPlayer[nIdy].nFrameAllCounter <= g_aPlayer[nIdy].ColAttack[nCnt].nCollisionEnd)
				{
					if (CollisionModelMinMax(&D3DXVECTOR3(g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._41, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._42, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._43),
						&D3DXVECTOR3(g_aPlayer[nIdy].aModel[0].mtxWorld._41, g_aPlayer[nIdy].aModel[0].mtxWorld._42, g_aPlayer[nIdy].aModel[0].mtxWorld._43), &D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						g_aPlayer[nIdy].ColAttack[nCnt].fRadius, g_aPlayer[nIdy].ColAttack[nCnt].fRadius, &g_aPlayer[nIdy].pModel) != 0)
					{
					}
					PlayerMotionEffect(nIdy, nCnt);
					// �U�������蔻��
					if (g_aPlayer[nIdy].nMotionType != PLAYER_MOTION_TYPE_CATCH)
					{// �L���b�`�͔��肵�Ȃ�
						if (CollisionPlayer(g_aPlayer[nIdy].pos,
							D3DXVECTOR3(g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._41, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._42, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._43),
							g_aPlayer[nIdy].ColAttack[nCnt].fRadius, g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].fAttackPower,
							g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].fDamageH,
							g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].fDamageV, g_aPlayer[nIdy].nIdy))
						{
						}
					}
					if (CollisionModelGetInfo(&D3DXVECTOR3(g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._41, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._42, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._43),
						g_aPlayer[nIdy].ColAttack[nCnt].fRadius, g_aPlayer[nIdy].ColAttack[nCnt].fRadius, &g_aPlayer[nIdy].pModelAtkData) != 0)
					{
					}
					if (g_aPlayer[nIdy].pModelAtkData != NULL)
					{
						if (g_aPlayer[nIdy].pModelAtkData->nType == MODELTYPE_TAIKO&&g_aPlayer[nIdy].nMotionType != PLAYER_MOTION_TYPE_CATCH)
						{// ���ۉ�
							PlaySound(SOUND_LABEL(SOUND_TAIKO_1 + (rand() % 4)));
							HitEffect(D3DXVECTOR3(g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._41, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._42, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._43));
							for (int nCnt = 0; nCnt < 5; nCnt++)
							{
								SetEffectUP(0, D3DXVECTOR3(sinf(SetRandomEffect())*600.0f, 600 +float(rand()%300), cosf(SetRandomEffect())*300.0f+200.0f),
									D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(SetRandomEffect(), SetRandomEffect(), SetRandomEffect()),
									D3DXCOLOR(float(rand() % 100) / 100.0f, float(rand() % 100) / 100.0f, float(rand() % 100) / 100.0f,1.0f),
									EFFECTUPTYPE_PAPER, 10);
							}
							if ((rand() + 1) % 300 == 0)
							{
								int nRand = rand() % 6;
								switch (nRand)
								{
								case 0:
									SetEvent(EVENTTYPE_FIRE);	// �C�x���g����
									break;
								case 1:
									SetEvent(EVENTTYPE_GUST);	// �C�x���g����
									break;
								case 2:
									SetEvent(EVENTTYPE_THUNDER);	// �C�x���g����
									break;
								case 3:
									SetEvent(EVENTTYPE_RAIN);	// �C�x���g����
									break;
								case 4:
									SetEvent(EVENTTYPE_WATER);	// �C�x���g����
									break;
								case 5:
									SetEvent(EVENTTYPE_METEORITE);	// �C�x���g����
									break;
								}
							}
						}
						if (g_aPlayer[nIdy].pModelAtkData->nType == MODELTYPE_CHOKO&&g_aPlayer[nIdy].nMotionType != PLAYER_MOTION_TYPE_CATCH)
						{// �`���R�o�i�i
							PlaySound(SOUND_LABEL_HIT000);
							HitEffect(D3DXVECTOR3(g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._41, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._42, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._43));
							if ((rand()+1) % 100 == 0)
							{
								PlaySound(SOUND_SUNDER);
								SetEventColor(D3DXCOLOR(2.0f, 2.0f, 2.0f, 1.0f));

								for (int nCntR = 0; nCntR < 3; nCntR++)
								{
									for (int nCnt = 0; nCnt < 10; nCnt++)
									{// ��
										SetEffectDamage(4, 10, 5.0f, 10.3f,D3DXVECTOR3(490, 0 + nCnt * 50.0f, 330),D3DXVECTOR3(0.0f,cosf(SetRandomEffect()) * 1.5f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),float(rand() % 200) + 10, 0, EFFECTTYPE_SUNDER);
									}
								}
								SetBillboard(D3DXVECTOR3(490, 50, 350), BILLBOARDTYPE_SHOP, 100, 100);
							}
						}
						ModelData *pModelData = GetModelData();
						Model *pModel = GetModel();
						if (g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_CATCH&&
							!g_aPlayer[nIdy].bCatch&&!g_aPlayer[nIdy].pModelAtkData->bCatch)
						{// �L���b�`�ł��邩�ǂ���
							int nIdyModel = 0;
							if (g_aPlayer[nIdy].pModelAtkData->nType == MODELTYPE_TAKOYAKI)
							{// �^�R�Ă��Ȃ�
								if (GetTakoyaki())
								{// �Q�b�g�\�Ȃ�
									nIdyModel = SetModel(D3DXVECTOR3(g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._41, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._42, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._43), D3DXVECTOR3(0, 0, 0), MODELTYPE_TAKOYAKI_BALL);
									g_aPlayer[nIdy].pModelAtk = &pModel[nIdyModel];
									g_aPlayer[nIdy].pModelAtk->nIdy = nIdy;
									g_aPlayer[nIdy].pModelAtk->bCatch = true;
									g_aPlayer[nIdy].bCatch = true;
									SetTakoyaki(false);
								}
							}
							if (g_aPlayer[nIdy].pModelAtkData->nType == MODELTYPE_KINGYO)
							{// �����Ȃ�
								if (GetFish())
								{// �Q�b�g�\�Ȃ�
									nIdyModel = SetModel(D3DXVECTOR3(g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._41, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._42, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._43), D3DXVECTOR3(0, 0, 0), MODELTYPE_FISH);
									g_aPlayer[nIdy].pModelAtk = &pModel[nIdyModel];
									g_aPlayer[nIdy].pModelAtk->nIdy = nIdy;
									g_aPlayer[nIdy].pModelAtk->bCatch = true;
									g_aPlayer[nIdy].bCatch = true;
									SetFish(false);
								}
							}
							else if (g_aPlayer[nIdy].pModelAtkData->nType == MODELTYPE_CHOKO)
							{// �`���R�o�i�i�Ȃ�
								if (GetChoco())
								{// �Q�b�g�\�Ȃ�
									g_aPlayer[nIdy].nItemTime = 6 * 60;
									int nCnt = rand() % 3;
									switch (nCnt)
									{
									case 0: // ���C�t
										g_aPlayer[nIdy].fPulsLife = 3;
										PlaySound(SOUND_LIFE);
										SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(GetCamera()->rot.y - D3DX_PI) * 50, 50.0f, cosf(GetCamera()->rot.y - D3DX_PI) * 50), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 0, EFFECTTYPE_LIFE_UP);
										break;
									case 1:// �A�^�b�N
										g_aPlayer[nIdy].fPulsAttack = 1;
										PlaySound(SOUND_ATTACK);
										SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(GetCamera()->rot.y - D3DX_PI) * 50 + float(nCnt), 50.0f, cosf(GetCamera()->rot.y - D3DX_PI) * 50), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 0, EFFECTTYPE_POW_UP);
										break;
									case 2:// �X�s�[�h
										g_aPlayer[nIdy].fPulsSpeed = 1;
										PlaySound(SOUND_SPEED);
										SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(GetCamera()->rot.y - D3DX_PI) * 50 + float(nCnt), 50.0f, cosf(GetCamera()->rot.y - D3DX_PI) * 50), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 0, EFFECTTYPE_SPEED_UP);
										break;
									}
									g_aPlayer[nIdy].fLife += g_aPlayer[nIdy].fPulsLife;
									g_aPlayer[nIdy].MoveSpeed += g_aPlayer[nIdy].fPulsSpeed;
									if (g_aPlayer[nIdy].fLife >= float(g_aPlayerData[g_aPlayer[nIdy].type].nInitLife))
									{// �ő僉�C�t�����Ȃ�
										g_aPlayer[nIdy].fLife = float(g_aPlayerData[g_aPlayer[nIdy].type].nInitLife);
									}
									GetPlayerLife(int(g_aPlayer[nIdy].fLife), nIdy);
									SetChoco(false);
								}
							}
							else if (pModelData[g_aPlayer[nIdy].pModelAtkData->nType].bCatch)
							{
								g_aPlayer[nIdy].pModelAtk = g_aPlayer[nIdy].pModelAtkData;
								g_aPlayer[nIdy].pModelAtk->nIdy = nIdy;
								g_aPlayer[nIdy].pModelAtk->bCatch = true;
								g_aPlayer[nIdy].bCatch = true;
							}
						}
					}
					if (g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_CATCH)
					{// �L���b�`�Ȃ�A�C�e�������
						float fLife = 0;
						g_aPlayer[nIdy].fPulsLife = 0;
						float fAttack = g_aPlayer[nIdy].fPulsAttack;
						float fSpeed = g_aPlayer[nIdy].fPulsSpeed;
						if (CollsionItem(D3DXVECTOR3(g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._41, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._42, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._43)
							, g_aPlayer[nIdy].ColAttack[nCnt].fRadius, g_aPlayer[nIdy].ColAttack[nCnt].fRadius,
							&g_aPlayer[nIdy].fPulsLife, &g_aPlayer[nIdy].fPulsAttack, &g_aPlayer[nIdy].fPulsSpeed))
						{//�A�C�e��
							g_aPlayer[nIdy].nItemTime = 5*60;
							int nCnt = 0;
							if (fLife != g_aPlayer[nIdy].fPulsLife)
							{// ���C�t����
								PlaySound(SOUND_LIFE);
								SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(GetCamera()->rot.y - D3DX_PI) * 50, 50.0f, cosf(GetCamera()->rot.y - D3DX_PI) * 50),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
									50, 0, EFFECTTYPE_LIFE_UP);
								nCnt += 30;
							}
							if (fAttack != g_aPlayer[nIdy].fPulsAttack)
							{// �U������
								PlaySound(SOUND_ATTACK);
								SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(GetCamera()->rot.y - D3DX_PI) * 50+ float(nCnt), 50.0f, cosf(GetCamera()->rot.y - D3DX_PI) * 50),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
									50, 0, EFFECTTYPE_POW_UP);
								nCnt += 30;
							}
							if (fSpeed != g_aPlayer[nIdy].fPulsSpeed)
							{// �X�s�[�h����
								PlaySound(SOUND_SPEED);
								SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(GetCamera()->rot.y - D3DX_PI) * 50 + float(nCnt), 50.0f, cosf(GetCamera()->rot.y - D3DX_PI) * 50),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
									50, 0, EFFECTTYPE_SPEED_UP);
							}
							g_aPlayer[nIdy].fLife += g_aPlayer[nIdy].fPulsLife;
							g_aPlayer[nIdy].MoveSpeed += g_aPlayer[nIdy].fPulsSpeed;
							if (g_aPlayer[nIdy].fLife >= float(g_aPlayerData[g_aPlayer[nIdy].type].nInitLife))
							{// �ő僉�C�t�����Ȃ�
								g_aPlayer[nIdy].fLife = float(g_aPlayerData[g_aPlayer[nIdy].type].nInitLife);
							}
							GetPlayerLife(int(g_aPlayer[nIdy].fLife), nIdy);
						}
					}
				}
			}
		}
	}

}

void AllReleaseAttack(int nIdy)
{
	for (int nCntAttack = 0; nCntAttack < PLAYER_ATTACK_TYPE_MAX; nCntAttack++)
	{// �U���̎�ޕ����[�v
		if (g_aPlayer[nIdy].bAttackType[nCntAttack])
		{// �U������������
			g_aPlayer[nIdy].bAttackType[nCntAttack] = false;								// �U����Ԃ�����
		}
	}
}
bool bAttackOn(int nIdy)
{
	bool On = false;
	for (int nCntAttack = 0; nCntAttack < PLAYER_ATTACK_TYPE_MAX; nCntAttack++)
	{// �U���̎�ޕ����[�v
		if (g_aPlayer[nIdy].bAttackType[nCntAttack])
		{// �U������������
			On = true; //�U����
		}
	}
	return On;
}
//=====================================================================================================================
//�@�K�E�Z�̎g�p����
//=====================================================================================================================
void Special(void)
{
	int nCntUse = 0;
	int nType = 0;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer[nCntPlayer].bSpecial == true)
		{
			nCntUse++;
		}
	}

	if (nCntUse == MAX_PLAYER)
	{
		//���Ԃ̎擾
		g_nCutInTime = GetTimeGame();

		if (g_bCutIn == false)
		{
			nType = g_aPlayer[g_nSpecialPlayer].type;
			SetCut(1, D3DXVECTOR3(1920.0f, 360.0f, 0.0f), (CHARATAYPE)nType, CUTTYPE_KYARACTOR);
			SetSpecalUse(true);		//�Q�[���̃J�b�g�C���g�p��Ԃɂ���iUpdate���~�߂�j
			g_bCutIn = true;
		}

		if ((g_nCutInTime % CUT_IN_TIME) == 0)
		{
			if (g_bStartMove == false)
			{
				g_aPlayer[g_nSpecialPlayer].bSpecial = false;
				g_bCutIn = false;

				//�|���S��������
				DeleteAllCut();

				//�J�b�g�C���g�p���Ă��Ȃ���Ԃɂ���iUpdate���ĊJ�j
				SetSpecalUse(false);

				//��̂�������������Ԃɂ���
				g_bStartMove = true;
			}
		}
	}

	//��̂��������n�߂���
	if (g_bStartMove == true)
	{
		StartMove();
	}
}

//=====================================================================================================================
//�@�L�����N�^�[�𓮂����n�߂�
//=====================================================================================================================
void StartMove(void)
{
	switch (g_aPlayer[g_nSpecialPlayer].type)
	{
	case PLAYERTYPE_MATURI:
		if (g_aPlayer[g_nSpecialPlayer].nFrameAllCounter == FLAM_MATURI)
		{//�g�p��Ԃ̐ݒ�
			SetSpecialUse(false);
			g_bStartMove = false;	//����������
			g_bStartCutIn = false;	//�J�b�g�C�����I��������
		}
		break;

	case PLAYERTYPE_AMANO:
		if (g_aPlayer[g_nSpecialPlayer].nFrameAllCounter == FLAM_AMANO)
		{//�g�p��Ԃ̐ݒ�
			SetSpecialUse(false);
			g_bStartMove = false;	//����������
			g_bStartCutIn = false;	//�J�b�g�C�����I��������
		}
		break;

	case PLAYERTYPE_GOJOU:
		if (g_aPlayer[g_nSpecialPlayer].nFrameAllCounter == FLAM_GOJOU)
		{//�g�p��Ԃ̐ݒ�
			SetSpecialUse(false);
			g_bStartMove = false;	//����������
			g_bStartCutIn = false;	//�J�b�g�C�����I��������
		}
		break;

	case PLAYERTYPE_MOMIJI:
		if (g_aPlayer[g_nSpecialPlayer].nFrameAllCounter == FLAM_MOMIJI)
		{//�g�p��Ԃ̐ݒ�
			SetSpecialUse(false);
			g_bStartMove = false;	//����������
			g_bStartCutIn = false;	//�J�b�g�C�����I��������
		}
		break;

	case PLAYERTYPE_DONROID:
		if (g_aPlayer[g_nSpecialPlayer].nFrameAllCounter == FLAM_DONROID)
		{//�g�p��Ԃ̐ݒ�
			SetSpecialUse(false);
			g_bStartMove = false;	//����������
			g_bStartCutIn = false;	//�J�b�g�C�����I��������
		}
		break;
	}
}

//=====================================================================================================================
//�@�g�p��Ԃ̐ݒ�
//=====================================================================================================================
void SetSpecialUse(bool bSpecial)
{
	for (int nCntCut = 0; nCntCut < MAX_PLAYER; nCntCut++)
	{
		g_aPlayer[nCntCut].bSpecial = bSpecial;
	}
}
//=====================================================================================================================
// ���C�t�[��
//=====================================================================================================================
void PlayerLifeZero(int nCnt, float fAngle, float fDamageH, float fDamageV)
{
	g_nNumAll--;
	if (g_aPlayer[nCnt].type == PLAYERTYPE_AMANO) { PlaySound(SOUND_TENGU_HUNOU000); }
	if (g_aPlayer[nCnt].type == PLAYERTYPE_GOJOU) { PlaySound(SOUND_KAPA_HUNOU000); }
	if (g_aPlayer[nCnt].type == PLAYERTYPE_MOMIJI) { PlaySound(SOUND_FOX_HUNOU); }
	if (g_aPlayer[nCnt].type == PLAYERTYPE_DONROID) { PlaySound(SOUND_ROBOT_HUNOU); }
	g_aPlayer[nCnt].state = PLAYERSTATE_DEATH;
	g_aPlayer[nCnt].nCntState = 100;

	// ���������̐�����ї͂���
	g_aPlayer[nCnt].fFlyPower.x = sinf(fAngle - D3DX_PI) * fDamageH;
	g_aPlayer[nCnt].fFlyPower.z = cosf(fAngle - D3DX_PI) * fDamageH;

	// ���������̐�����ї͂���
	g_aPlayer[nCnt].fFlyPower.y = fDamageV;
	g_aPlayer[nCnt].nFlyCounter = 20;
	g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_FLY] = true;													// ������ђ��ɐݒ�
	g_aPlayer[nCnt].Destrot.y = fAngle - D3DX_PI;							// �L�����N�^�[�̌�����ύX
	g_aPlayer[nCnt].rot.y = fAngle - D3DX_PI;							// �L�����N�^�[�̌�����ύX

}
//=========================================================================================================================
// �{�C�X
//===========================================================================================================================
void SetPlayerVoice(PLAYERTYPE type, PlayerMotionType motion)
{
	if (motion == PLAYER_MOTION_TYPE_DAMAGE)
	{
		switch (type)
		{
		case PLAYERTYPE_MATURI:// �܂�i���̎q�j
			PlaySound(SOUND_HUMAN_DAMEJI);
			break;
		case PLAYERTYPE_AMANO:// ���܂́i�V��j
			PlaySound(SOUND_TENGU_DAMEJI);
			break;
		case PLAYERTYPE_GOJOU:// ���i�͓��j
			PlaySound(SOUND_LABEL( SOUND_KAPA_DAMEJI000 + rand()%3));
			break;
		case PLAYERTYPE_MOMIJI:// �g�t�i���ˁj
			PlaySound(SOUND_FOX_DAMEJI);
			break;
		case PLAYERTYPE_DONROID:// �h�����C�h�i���{�b�g�j
			PlaySound(SOUND_ROBOT_DAMEJI);
			break;
		}
	}
	if (motion == PLAYER_MOTION_TYPE_FLY)
	{
		switch (type)
		{
		case PLAYERTYPE_MATURI:// �܂�i���̎q�j
			PlaySound(SOUND_HUMAN_BUTOBI);
			break;
		case PLAYERTYPE_AMANO:// ���܂́i�V��j
			PlaySound(SOUND_TENGU_BUTOBI);
			break;
		case PLAYERTYPE_GOJOU:// ���i�͓��j
			PlaySound(SOUND_KAPA_BUTOBI);
			break;
		case PLAYERTYPE_MOMIJI:// �g�t�i���ˁj
			PlaySound(SOUND_FOX_BUTOBI);
			break;
		case PLAYERTYPE_DONROID:// �h�����C�h�i���{�b�g�j
			PlaySound(SOUND_ROBOT_BUTOBI);
			break;
		}
	}
	if (motion == PLAYER_MOTION_TYPE_MAX)
	{
		switch (type)
		{
		case PLAYERTYPE_MATURI:// �܂�i���̎q�j
			PlaySound(SOUND_HUMAN_GARD000);
			break;
		case PLAYERTYPE_AMANO:// ���܂́i�V��j
			PlaySound(SOUND_TENGU_GARD);
			break;
		case PLAYERTYPE_GOJOU:// ���i�͓��j
			PlaySound(SOUND_KAPA_GARD);
			break;
		case PLAYERTYPE_MOMIJI:// �g�t�i���ˁj
			PlaySound(SOUND_FOX_GARD);
			break;
		case PLAYERTYPE_DONROID:// �h�����C�h�i���{�b�g�j
			PlaySound(SOUND_ROBOT_GARD);
			break;
		}

	}
	if (motion == PLAYER_MOTION_TYPE_WIN)
	{
		switch (type)
		{
		case PLAYERTYPE_MATURI:// �܂�i���̎q�j
			PlaySound(SOUND_HUMAN_KAIHI);
			break;
		case PLAYERTYPE_AMANO:// ���܂́i�V��j
			PlaySound(SOUND_TENGU_KAIHI);
			break;
		case PLAYERTYPE_GOJOU:// ���i�͓��j
			PlaySound(SOUND_KAPA_KAIHI);
			break;
		case PLAYERTYPE_MOMIJI:// �g�t�i���ˁj
			PlaySound(SOUND_FOX_KAIHI);
			break;
		case PLAYERTYPE_DONROID:// �h�����C�h�i���{�b�g�j
			PlaySound(SOUND_ROBOT_KAIHI);
			break;
		}
	}

}
//==============================================================================================================================
//�@���C�t�̃`�F�b�N
//==============================================================================================================================
int CheckLife(void)
{
	//�ϐ��錾
	int BigLife = 0;

	for (int nCntId = 0; nCntId < MAX_PLAYER - 1; nCntId++)
	{
		if (g_aPlayer[BigLife].fLife > g_aPlayer[nCntId + 1].fLife)
		{
			BigLife = BigLife;		//Id�̕ۑ�
		}
		else
		{
			BigLife = nCntId + 1;	//Id�̕ۑ�
		}
	}

	return BigLife;
}