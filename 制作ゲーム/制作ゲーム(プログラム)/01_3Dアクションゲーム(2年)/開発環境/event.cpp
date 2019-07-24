//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// イベント処理 [event.cpp]
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
// グローバル変数:
//******************************************************************************************************************************
D3DXCOLOR g_EventCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// イベントの色
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
// イベントの設定
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
	{// イベントが「洪水」のとき
		PlaySound(SOUND_ALERT);
		PlaySound(SOUND_FLOOD);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_WATER);
	}
	else if (g_type == EVENTTYPE_FIRE)
	{//	イベントが「火事」のとき
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_FIRE);
	}
	else if (g_type == EVENTTYPE_FALLING_ROCK)
	{// イベントが「複数の落石」のとき
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_FALLING_ROCK);
	}
	else if (g_type == EVENTTYPE_FALLING_BIGROCK)
	{// イベントが「大きい岩の落石」のとき
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_FALLING_BIGROCK);
	}
	else if (g_type == EVENTTYPE_METEORSHOWER)
	{// イベントが「流星群」のとき
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_METEORSHOWER);
	}
	else if (g_type == EVENTTYPE_METEORITE)
	{// イベントが「隕石」のとき
		PlaySound(SOUND_METEO);
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_METEORITE);
	}
	else if (g_type == EVENTTYPE_RAIN)
	{// イベントが「雨で見えにくく」のとき
		PlaySound(SOUND_ALERT);
		PlaySound(SOUND_RAIN);
		SetLineEffect(LINETYPE_EFFECT_RAIN, true);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_RAIN);
	}
	else if (g_type == EVENTTYPE_THUNDER)
	{// イベントが「雷」のとき
		PlaySound(SOUND_ALERT);
		PlaySound(SOUND_RAIN);
		SetLineEffect(LINETYPE_EFFECT_RAIN, true);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_THUNDER);
	}
	else if (g_type == EVENTTYPE_FALLING_CHOUTIN)
	{// イベントが「提灯落下」のとき
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_FALLING_CHOUTIN);
	}
	else if (g_type == EVENTTYPE_FALLING_BRANCH)
	{// イベントが「木の枝落下」のとき
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_FALLING_BRANCH);
	}
	else if (g_type == EVENTTYPE_LEEF)
	{// イベントが「葉っぱで見えにくく」のとき
		PlaySound(SOUND_ALERT);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_LEEF);
	}
	else if (g_type == EVENTTYPE_GUST)
	{// イベントが「突風」のとき
		PlaySound(SOUND_ALERT);
		PlaySound(SOUND_GUST);
		SetLineEffect(LINETYPE_EFFECT_WINDY, true);
		SetEventlogo(D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f), EVENTLOGO_WIDTH, EVENTLOGO_HEIGHT, EVENTTYPE_GUST);
	}
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// イベントの初期化
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitEvent(void)
{
	g_type = EVENTTYPE_NONE;
	g_nEventCounter = 0;							// イベントカウンター
	g_nEventStartCounter = 0;
	g_EventCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// イベントの色
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// イベントの終了
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitEvent(void)
{
	g_type = EVENTTYPE_NONE;
	g_nEventCounter = 0;							// イベントカウンター
	g_nEventStartCounter = 0;
	g_EventCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// イベントの色
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// イベントの更新
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
				SetEvent(EVENTTYPE_FIRE);	// イベント発生
				break;
			case 1:
				SetEvent(EVENTTYPE_GUST);	// イベント発生
				break;
			case 2:
				SetEvent(EVENTTYPE_THUNDER);	// イベント発生
				break;
			case 3:
				SetEvent(EVENTTYPE_RAIN);	// イベント発生
				break;
			case 4:
				SetEvent(EVENTTYPE_WATER);	// イベント発生
				break;
			case 5:
				SetEvent(EVENTTYPE_METEORITE);	// イベント発生
				break;
			}
		}
		if (g_type != EVENTTYPE_NONE)
		{
			g_nEventStartCounter++;
			if (g_nEventStart[g_type] <= g_nEventStartCounter)
			{
				SetEvent(EVENTTYPE_NONE);	// イベント発生
			}
		}
		else
		{
			g_nEventStartCounter = 0;
		}
		g_nEventCounter++;
	}
	if (GetKeyboardTrigger(DIK_NUMPAD1) == true)
	{// 火事
		SetEvent(EVENTTYPE_FIRE);	// イベント発生
	}
	if (GetKeyboardTrigger(DIK_NUMPAD2) == true)
	{// 突風
		SetEvent(EVENTTYPE_GUST);	// イベント発生
	}
	if (GetKeyboardTrigger(DIK_NUMPAD3) == true)
	{// 雷
		SetEvent(EVENTTYPE_THUNDER);	// イベント発生
	}
	if (GetKeyboardTrigger(DIK_NUMPAD4) == true)
	{//雨
		SetEvent(EVENTTYPE_RAIN);	// イベント発生
	}
	if (GetKeyboardTrigger(DIK_NUMPAD5) == true)
	{//洪水
		SetEvent(EVENTTYPE_WATER);	// イベント発生
	}
	if (GetKeyboardTrigger(DIK_NUMPAD6) == true)
	{//隕石
		SetEvent(EVENTTYPE_METEORITE);	// イベント発生
	}
	if (GetKeyboardTrigger(DIK_NUMPAD0) == true)
	{
		SetEvent(EVENTTYPE_NONE);	// イベント発生
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
	case EVENTTYPE_FIRE://	イベントが「火事」のとき
		g_EventCol += (D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f) - g_EventCol)*0.01f;
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{// 火
			// 木
			SetEffectDamage(4, FIRE_DAMAGE, 3.0f, 5.3f,
				D3DXVECTOR3(sinf(SetRandomEffect()) * 30 - 500, nCnt*50.0f, cosf(SetRandomEffect()) * 50),
				D3DXVECTOR3(sinf(SetRandomEffect()) * (rand() % 5),
					cosf(SetRandomEffect()) * (rand() % 5), cosf(SetRandomEffect()) * (rand() % 5)),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, float(rand() % 100) / 100.0f, 0.0f, 1.0f),
				float(rand() % 200) + 10, 0, EFFECTTYPE_FIRE);

			// 太鼓
			SetEffectDamage(4, FIRE_DAMAGE, 3.0f, 5.3f,
				D3DXVECTOR3(sinf(SetRandomEffect()) * 30 - 50.0f, nCnt*50.0f, 400),
				D3DXVECTOR3(sinf(SetRandomEffect()) * (rand() % 5),
					cosf(SetRandomEffect()) * (rand() % 5), cosf(SetRandomEffect()) * (rand() % 5)),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, float(rand() % 100) / 100.0f, 0.0f, 1.0f),
				float(rand() % 200) + 10, 0, EFFECTTYPE_FIRE);

			// 金魚
			SetEffectDamage(4, FIRE_DAMAGE, 3.0f, 5.3f,
				D3DXVECTOR3(100, 0, 400),
				D3DXVECTOR3(sinf(SetRandomEffect()) * (rand() % 5),
					cosf(SetRandomEffect()) * (rand() % 5), cosf(SetRandomEffect()) * (rand() % 5)),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, float(rand() % 100) / 100.0f, 0.0f, 1.0f),
				float(rand() % 200) + 10, 0, EFFECTTYPE_FIRE);
			// タコ焼き
			SetEffectDamage(4, FIRE_DAMAGE, 3.0f, 5.3f,
				D3DXVECTOR3(300, 0, 400),
				D3DXVECTOR3(sinf(SetRandomEffect()) * (rand() % 5),
					cosf(SetRandomEffect()) * (rand() % 5), cosf(SetRandomEffect()) * (rand() % 5)),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, float(rand() % 100) / 100.0f, 0.0f, 1.0f),
				float(rand() % 200) + 10, 0, EFFECTTYPE_FIRE);
			// チョコバナナ
			SetEffectDamage(4, FIRE_DAMAGE, 3.0f, 5.3f,
				D3DXVECTOR3(450, 0, 400),
				D3DXVECTOR3(sinf(SetRandomEffect()) * (rand() % 5),
					cosf(SetRandomEffect()) * (rand() % 5), cosf(SetRandomEffect()) * (rand() % 5)),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, float(rand() % 100) / 100.0f, 0.0f, 1.0f),
				float(rand() % 200) + 10, 0, EFFECTTYPE_FIRE);

		}
		break;
	case EVENTTYPE_THUNDER:		// 雷
		g_EventCol += (D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f) - g_EventCol)*0.1f;
		if (g_nEventCounter % 200 == 0)
		{
			g_EventCol = D3DXCOLOR(2.0f, 2.0f, 2.0f, 2.0f);
			PlaySound(SOUND_SUNDER);
			for (int nCntR = 0; nCntR < 3; nCntR++)
			{
				for (int nCnt = 0; nCnt < 10; nCnt++)
				{// 雷
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
	case EVENTTYPE_RAIN:// イベントが「雨で見えにくく」のとき
		g_EventCol += (D3DXCOLOR(0.8f, 0.8f, 1.0f, 1.0f) - g_EventCol)*0.01f;
		break;
	case EVENTTYPE_GUST://イベントが「突風」のとき
		g_EventCol += (D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f) - g_EventCol)*0.01f;
		for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
		{
			if (pPlayer[nCnt].bUse)
			{
				pPlayer[nCnt].Environment.x += GUST_MOVE;
			}
		}

		break;
	case EVENTTYPE_WATER:// 洪水
		g_EventCol += (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) - g_EventCol)*0.01f;
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{// 水
			SetEffectDamage(4, 0.0f,
				5.0f
				, 1.0f,
				D3DXVECTOR3(-330 + sinf(SetRandomEffect())*50.0f, 5, 250),
				D3DXVECTOR3(sinf(SetRandomEffect()) * 10.0f, cosf(float(rand() % 314) / 100.0f) * 10.0f, cosf(SetRandomEffect()) * 10.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				float(rand() % 50 + 10), 0, EFFECTTYPE_WATER);
		}
		break;
	case EVENTTYPE_METEORITE:// 隕石
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
// イベントの色の取得
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
D3DXCOLOR GetEventColor(void)
{
	return g_EventCol;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// イベントの色の設定
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetEventColor(D3DXCOLOR col)
{
	g_EventCol = col;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// イベントの取得
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
EVENTTYPE GetEventType(void)
{
	return g_type;
}