//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �C�x���g���� [event.cpp]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "event.h"
#include "eventlogo.h"
#include "input.h"
#include "effect.h"
#include "player.h"
#include "lineEffect.h"
#include "camera.h"
#include "model.h"
#define FIRE_DAMAGE (5)
#define SUNDER_DAMAGE (20)
#define GUST_MOVE (1.0f)
//******************************************************************************************************************************
// �O���[�o���ϐ�:
//******************************************************************************************************************************
D3DXCOLOR g_EventCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �C�x���g�̐F
EVENTTYPE g_type = EVENTTYPE_NONE;
int g_nEventCounter = 0;
int g_nEventStartCounter = 0;
int g_nEventStart[EVENTTYPE_MAX] =
{ 15 * 60,
15 * 60 ,
15 * 60 ,
15 * 60 ,
15 * 60 ,
15 * 60 ,
15 * 60 ,
15 * 60 ,
15 * 60 ,
15 * 60 ,
15 * 60 ,
15 * 60 ,
15 * 60 ,
};
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �C�x���g�̐ݒ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetEvent(EVENTTYPE eventType)
{

	SetLineEffect(LINETYPE_EFFECT_RAIN, false);
	SetLineEffect(LINETYPE_EFFECT_WINDY, false);
	StopSound(SOUND_RAIN);
	StopSound(SOUND_FLOOD);
	StopSound(SOUND_METEO);
	StopSound(SOUND_GUST);

	DeleteEventLogo();
	g_type = eventType;

	if (g_type == EVENTTYPE_WATER)
	{// �C�x���g���u�^���v�̂Ƃ�
		PlaySound(SOUND_ALERT);
		PlaySound(SOUND_FLOOD);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_WATER);
	}
	else if (g_type == EVENTTYPE_FIRE)
	{//	�C�x���g���u�Ύ��v�̂Ƃ�
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_FIRE);
	}
	else if (g_type == EVENTTYPE_FALLING_ROCK)
	{// �C�x���g���u�����̗��΁v�̂Ƃ�
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_FALLING_ROCK);
	}
	else if (g_type == EVENTTYPE_FALLING_BIGROCK)
	{// �C�x���g���u�傫����̗��΁v�̂Ƃ�
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_FALLING_BIGROCK);
	}
	else if (g_type == EVENTTYPE_METEORSHOWER)
	{// �C�x���g���u�����Q�v�̂Ƃ�
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_METEORSHOWER);
	}
	else if (g_type == EVENTTYPE_METEORITE)
	{// �C�x���g���u覐΁v�̂Ƃ�
		PlaySound(SOUND_METEO);
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_METEORITE);
	}
	else if (g_type == EVENTTYPE_RAIN)
	{// �C�x���g���u�J�Ō����ɂ����v�̂Ƃ�
		PlaySound(SOUND_ALERT);
		PlaySound(SOUND_RAIN);
		SetLineEffect(LINETYPE_EFFECT_RAIN, true);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_RAIN);
	}
	else if (g_type == EVENTTYPE_THUNDER)
	{// �C�x���g���u���v�̂Ƃ�
		PlaySound(SOUND_ALERT);
		PlaySound(SOUND_RAIN);
		SetLineEffect(LINETYPE_EFFECT_RAIN, true);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_THUNDER);
	}
	else if (g_type == EVENTTYPE_FALLING_CHOUTIN)
	{// �C�x���g���u�񓔗����v�̂Ƃ�
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_FALLING_CHOUTIN);
	}
	else if (g_type == EVENTTYPE_FALLING_BRANCH)
	{// �C�x���g���u�؂̎}�����v�̂Ƃ�
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_FALLING_BRANCH);
	}
	else if (g_type == EVENTTYPE_LEEF)
	{// �C�x���g���u�t���ςŌ����ɂ����v�̂Ƃ�
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_LEEF);
	}
	else if (g_type == EVENTTYPE_GUST)
	{// �C�x���g���u�˕��v�̂Ƃ�
		PlaySound(SOUND_ALERT);
		PlaySound(SOUND_GUST);
		SetLineEffect(LINETYPE_EFFECT_WINDY, true);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_GUST);
	}
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �C�x���g�̏�����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitEvent(void)
{
	g_type = EVENTTYPE_NONE;
	g_nEventCounter = 0;							// �C�x���g�J�E���^�[
	g_nEventStartCounter = 0;
	g_EventCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �C�x���g�̐F
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �C�x���g�̏I��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitEvent(void)
{
	g_type = EVENTTYPE_NONE;
	g_nEventCounter = 0;							// �C�x���g�J�E���^�[
	g_nEventStartCounter = 0;
	g_EventCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �C�x���g�̐F
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �C�x���g�̍X�V
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateEvent()
{
	if (GetCamera()[0].nState == CAMERASTATE_NONE)
	{
		if (g_nEventCounter == 5 * 60 || g_nEventCounter == 30 * 60 || g_nEventCounter == 60 * 60
			|| g_nEventCounter == 90 * 60 || g_nEventCounter == 120 * 60)
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
		if (g_type != EVENTTYPE_NONE)
		{
			g_nEventStartCounter++;
			if (g_nEventStart[g_type] <= g_nEventStartCounter)
			{
				SetEvent(EVENTTYPE_NONE);	// �C�x���g����
			}
		}
		else
		{
			g_nEventStartCounter = 0;
		}
		g_nEventCounter++;
	}
	if (GetKeyboardTrigger(DIK_NUMPAD1) == true)
	{// �Ύ�
		SetEvent(EVENTTYPE_FIRE);	// �C�x���g����
	}
	if (GetKeyboardTrigger(DIK_NUMPAD2) == true)
	{// �˕�
		SetEvent(EVENTTYPE_GUST);	// �C�x���g����
	}
	if (GetKeyboardTrigger(DIK_NUMPAD3) == true)
	{// ��
		SetEvent(EVENTTYPE_THUNDER);	// �C�x���g����
	}
	if (GetKeyboardTrigger(DIK_NUMPAD4) == true)
	{//�J
		SetEvent(EVENTTYPE_RAIN);	// �C�x���g����
	}
	if (GetKeyboardTrigger(DIK_NUMPAD5) == true)
	{//�^��
		SetEvent(EVENTTYPE_WATER);	// �C�x���g����
	}
	if (GetKeyboardTrigger(DIK_NUMPAD6) == true)
	{//覐�
		SetEvent(EVENTTYPE_METEORITE);	// �C�x���g����
	}
	if (GetKeyboardTrigger(DIK_NUMPAD0) == true)
	{
		SetEvent(EVENTTYPE_NONE);	// �C�x���g����
	}

	float RandX = float(500 - rand() % 900);
	float RandZ = float(350 - rand() % 450);
	Player *pPlayer = GetPlayer();
	Model *pModel = GetModel();
	int nModel = 0;

	switch (g_type)
	{
	case EVENTTYPE_NONE:
		g_EventCol += (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) - g_EventCol)*0.1f;
		break;
	case EVENTTYPE_FIRE://	�C�x���g���u�Ύ��v�̂Ƃ�
		g_EventCol += (D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f) - g_EventCol)*0.01f;
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{// ��
			// ��
			SetEffectDamage(4, FIRE_DAMAGE, 3.0f, 5.3f,
				D3DXVECTOR3(sinf(SetRandomEffect()) * 30 - 500, nCnt*50.0f, cosf(SetRandomEffect()) * 50),
				D3DXVECTOR3(sinf(SetRandomEffect()) * (rand() % 5),
					cosf(SetRandomEffect()) * (rand() % 5), cosf(SetRandomEffect()) * (rand() % 5)),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, float(rand() % 100) / 100.0f, 0.0f, 1.0f),
				float(rand() % 200) + 10, 0, EFFECTTYPE_FIRE);

			// ����
			SetEffectDamage(4, FIRE_DAMAGE, 3.0f, 5.3f,
				D3DXVECTOR3(sinf(SetRandomEffect()) * 30 - 50.0f, nCnt*50.0f, 400),
				D3DXVECTOR3(sinf(SetRandomEffect()) * (rand() % 5),
					cosf(SetRandomEffect()) * (rand() % 5), cosf(SetRandomEffect()) * (rand() % 5)),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, float(rand() % 100) / 100.0f, 0.0f, 1.0f),
				float(rand() % 200) + 10, 0, EFFECTTYPE_FIRE);

			// ����
			SetEffectDamage(4, FIRE_DAMAGE, 3.0f, 5.3f,
				D3DXVECTOR3(100, 0, 400),
				D3DXVECTOR3(sinf(SetRandomEffect()) * (rand() % 5),
					cosf(SetRandomEffect()) * (rand() % 5), cosf(SetRandomEffect()) * (rand() % 5)),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, float(rand() % 100) / 100.0f, 0.0f, 1.0f),
				float(rand() % 200) + 10, 0, EFFECTTYPE_FIRE);
			// �^�R�Ă�
			SetEffectDamage(4, FIRE_DAMAGE, 3.0f, 5.3f,
				D3DXVECTOR3(300, 0, 400),
				D3DXVECTOR3(sinf(SetRandomEffect()) * (rand() % 5),
					cosf(SetRandomEffect()) * (rand() % 5), cosf(SetRandomEffect()) * (rand() % 5)),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, float(rand() % 100) / 100.0f, 0.0f, 1.0f),
				float(rand() % 200) + 10, 0, EFFECTTYPE_FIRE);
			// �`���R�o�i�i
			SetEffectDamage(4, FIRE_DAMAGE, 3.0f, 5.3f,
				D3DXVECTOR3(450, 0, 400),
				D3DXVECTOR3(sinf(SetRandomEffect()) * (rand() % 5),
					cosf(SetRandomEffect()) * (rand() % 5), cosf(SetRandomEffect()) * (rand() % 5)),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, float(rand() % 100) / 100.0f, 0.0f, 1.0f),
				float(rand() % 200) + 10, 0, EFFECTTYPE_FIRE);

		}
		break;
	case EVENTTYPE_THUNDER:		// ��
		g_EventCol += (D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f) - g_EventCol)*0.1f;
		if (g_nEventCounter % 200 == 0)
		{
			g_EventCol = D3DXCOLOR(2.0f, 2.0f, 2.0f, 2.0f);
			PlaySound(SOUND_SUNDER);
			for (int nCntR = 0; nCntR < 3; nCntR++)
			{
				for (int nCnt = 0; nCnt < 10; nCnt++)
				{// ��
					SetEffectDamage(4, SUNDER_DAMAGE
						, 5.0f
						, 10.3f,
						D3DXVECTOR3(RandX, 0 + nCnt * 50.0f, RandZ),
						D3DXVECTOR3(0.0f,
							cosf(SetRandomEffect()) * 1.5f, 0.0f),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
						float(rand() % 200) + 10, 0, EFFECTTYPE_SUNDER);
				}
			}
		}
		break;
	case EVENTTYPE_RAIN:// �C�x���g���u�J�Ō����ɂ����v�̂Ƃ�
		g_EventCol += (D3DXCOLOR(0.8f, 0.8f, 1.0f, 1.0f) - g_EventCol)*0.01f;
		break;
	case EVENTTYPE_GUST://�C�x���g���u�˕��v�̂Ƃ�
		g_EventCol += (D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f) - g_EventCol)*0.01f;
		for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
		{
			if (pPlayer[nCnt].bUse)
			{
				pPlayer[nCnt].Environment.x += GUST_MOVE;
			}
		}

		break;
	case EVENTTYPE_WATER:// �^��
		g_EventCol += (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) - g_EventCol)*0.01f;
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{// ��
			SetEffectDamage(4, 0.0f,
				5.0f
				, 1.0f,
				D3DXVECTOR3(-330 + sinf(SetRandomEffect())*50.0f, 5, 250),
				D3DXVECTOR3(sinf(SetRandomEffect()) * 10.0f, cosf(float(rand() % 314) / 100.0f) * 10.0f, cosf(SetRandomEffect()) * 10.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				float(rand() % 50 + 10), 0, EFFECTTYPE_WATER);
		}
		break;
	case EVENTTYPE_METEORITE:// 覐�
		g_EventCol += (D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f) - g_EventCol)*0.01f;
		if (g_nEventCounter % 100 == 0)
		{
			nModel = SetModel(D3DXVECTOR3(RandX, 700, RandZ), D3DXVECTOR3(0, 0, 0), MODELTYPE_METEO);
			pModel[nModel].move.y = -10;
			pModel[nModel].move.x = float(sin(SetRandomEffect())*5.0f);
			pModel[nModel].nIdy = 4;
		}
		break;
	}


}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �C�x���g�̐F�̎擾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
D3DXCOLOR GetEventColor(void)
{
	return g_EventCol;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �C�x���g�̐F�̐ݒ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetEventColor(D3DXCOLOR col)
{
	g_EventCol = col;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �C�x���g�̎擾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
EVENTTYPE GetEventType(void)
{
	return g_type;
}