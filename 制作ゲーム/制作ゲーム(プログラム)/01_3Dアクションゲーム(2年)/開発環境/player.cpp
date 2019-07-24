////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// プレイヤー処理 [player.cpp]
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
// マクロ定義
//******************************************************************************************************************************
#define DOWN_SPEED						(0.4f)	// 減速量
#define PLAYER_ROT_SPEED_NORMAL			(0.3f)	// 通常時の角度を変える量
#define PLAYER_ROT_SPEED_ATTACK			(0.03f)	// 攻撃時の角度を変える量
#define GRAVITY_SPEED					(0.6f)	// 重力加算スピード
#define INIT_JUMP_SPEED					(7)		// ジャンプ力
#define INIT_MOVE_SPEED					(0.3f)	// 移動量
#define PLAYER_MOTION_STEP_MOVE_SPEED	(5.0f)	// ステップのスピード
#define BLEND_FRAME						(3)		// ブレンド
#define ATTACKDAMAGE					(1)		// アタックのダメージ量
#define WARKZONE						(50)	// 歩きのゾーン
#define PLAYER_MOTION_MOVE_ZONE			(1.0f)	// 歩きのモーションゾーン
#define MAX_SKY							(1.0f)	// ガードの最大ライフ
#define MAX_DEPTH						(475)
#define MAX_CAMERASTATE					(30)
#define DOWN_JUMP_SPEED					(1.5f)	// ジャンプ
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
// プロトタイプ宣言
//******************************************************************************************************************************
void AllReleaseAttack(int nIdy);
bool bAttackOn(int nIdy);
void Special(void);
void StartMove(void);
void SetSpecialUse(bool bSpecial);
void SetPlayerVoice(PLAYERTYPE type, PlayerMotionType motion);
void PlayerLifeZero(int nIdy,float fAngle, float fDamageH, float fDamageV);
//******************************************************************************************************************************
// グローバル変数
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
// 初期化処理
//==============================================================================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 位置・向きの初期設定
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		g_aPlayer[nCnt].pos = D3DXVECTOR3(0.0f + nCnt * 100, 0.0f, 0.0f);		// 座標
		g_aPlayer[nCnt].posOld = D3DXVECTOR3(0.0f + nCnt * 100, 0.0f, 0.0f);		// 前回の座標
		g_aPlayer[nCnt].Diffpos = D3DXVECTOR3(0.0f + nCnt * 100, 0.0f, 0.0f);	// 座標の差分
		g_aPlayer[nCnt].Initpos = D3DXVECTOR3(0.0f + nCnt * 100, 0.0f, 0.0f);	// 初期座標
		g_aPlayer[nCnt].nMotionType = PLAYER_MOTION_TYPE_NEUTRAL;	// モーションタイプ
		g_aPlayer[nCnt].nMotionTypeOld = PLAYER_MOTION_TYPE_MAX;	// 前回のモーションタイプ
		g_aPlayer[nCnt].nMotionGetCol = PLAYER_MOTION_TYPE_NEUTRAL;	// モーションタイプ
		g_aPlayer[nCnt].nMotionGetColOld = PLAYER_MOTION_TYPE_MAX;	// 前回のモーションタイプ
		g_aPlayer[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
		g_aPlayer[nCnt].Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転の差分
		g_aPlayer[nCnt].Destrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 目的の回転
		g_aPlayer[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 回転
		for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
		{// 音
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
		g_aPlayer[nCnt].bJump = false;							// ジャンプ
		g_aPlayer[nCnt].bCatch = false;							// 拾っているかどうか
		g_aPlayer[nCnt].bCatchOld = false;							// 拾っているかどうか
		g_aPlayer[nCnt].nFlyCounter = 0;						// 飛んでいる時間
		g_aPlayer[nCnt].fRotSpeed = 0.0f;						// 回転の減速スピード
		g_aPlayer[nCnt].nAirCounter = 0;						// 浮遊時の攻撃制御カウンター
		g_aPlayer[nCnt].nLoopCounter = 0;						// ループカウンター
		g_aPlayer[nCnt].nIdy = nCnt;							// 番号
		g_aPlayer[nCnt].nKeyCounter = 0;		// キー数
		g_aPlayer[nCnt].nFrameCounter = 0;		// フレーム数
		g_aPlayer[nCnt].nFrameAllCounter = 0;	// 最大フレーム
		g_aPlayer[nCnt].nFrame = 0;				// フレーム
		g_aPlayer[nCnt].fGuardLife = MAX_SKY;		// ガードのライフ
		g_aPlayer[nCnt].bUse = false;
		g_aPlayer[nCnt].bDraw = true;			// 映ってるかどうか
		g_aPlayer[nCnt].fPulsLife = 0;			// アイテムで増えるライフ
		g_aPlayer[nCnt].fPulsAttack = 0;		// アイテムで加算される攻撃力
		g_aPlayer[nCnt].fPulsSpeed = 0;			// アイテムで増えるスピード
		g_aPlayer[nCnt].nItemTime = 0;			// アイテム継続時間
		g_aPlayer[nCnt].nSp = MAX_SP;				// スペシャル
		g_aPlayer[nCnt].bSp = false;				// 座標
		g_aPlayer[nCnt].nComboCounter = 0;			// コンボカウンター
		g_aPlayer[nCnt].bCombo = false;				// コンボ
		g_aPlayer[nCnt].nCntEmote = 0;				// エモート
		g_aPlayer[nCnt].nStopTime = 0;				// 操作不能時間
		g_aPlayer[nCnt].bSpecial = false;
	}
	g_aPlayer[0].col = D3DXCOLOR(0.92f, 0.43f, 0.62f, 1.0f);	// ピンク
	g_aPlayer[1].col = D3DXCOLOR(0.55f, 0.78f, 1.0f, 1.0f);		// 青
	g_aPlayer[2].col = D3DXCOLOR(1.0f, 1.0f, 0.1f, 1.0f);		// 黄色
	g_aPlayer[3].col = D3DXCOLOR(0.1f, 1.0f, 0.1f, 1.0f);		// 緑
	g_nCutInTime = 0;
	g_nSpecialPlayer = 0;
	g_bCutIn = false;
	g_bStartMove = false;
	g_bStartCutIn = false;


	for (int nCnt = 0; nCnt < PLAYERTYPE_MAX; nCnt++)
	{
		for (int nCntParts = 0; nCntParts < g_aPlayerData[nCnt].nNumParts; nCntParts++)
		{// Key - 現在 間の差分計算
			g_aPlayerData[nCnt].aModel[nCntParts].rot = g_aPlayerData[nCnt].aMotion[PLAYER_MOTION_TYPE_JUMP].aKey[0].aPartsKey[nCntParts].rot;
		}
	}
	g_nNumAll = 0;
}

//==============================================================================================================================
// 終了処理
//==============================================================================================================================
void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < PLAYERTYPE_MAX; nCnt++)
	{
		for (int nCntModel = 0; nCntModel < g_aPlayerData[nCnt].nNumParts; nCntModel++)
		{
			// メッシュの開放
			if (g_aPlayerData[nCnt].aModel[nCntModel].pMesh != NULL)
			{
				g_aPlayerData[nCnt].aModel[nCntModel].pMesh->Release();
				g_aPlayerData[nCnt].aModel[nCntModel].pMesh = NULL;
			}
			// マテリアルの開放
			if (g_aPlayerData[nCnt].aModel[nCntModel].pBuffMat != NULL)
			{
				g_aPlayerData[nCnt].aModel[nCntModel].pBuffMat->Release();
				g_aPlayerData[nCnt].aModel[nCntModel].pBuffMat = NULL;
			}
			// テクスチャの開放
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
// 更新処理
//==============================================================================================================================
void UpdatePlayer(int nIdy)
{
	GamePad *pGamePad = GetgamePadStick();
	MeshField *pMeshField = GetMeshField();
	Camera *pCamera = GetCamera();
	Model *pModel = GetModel();

	if (g_bStartCutIn == true)
	{
		Special();						//カットイン
	}

	if (g_aPlayer[nIdy].bUse&& !g_aPlayer[nIdy].bSpecial)
	{
		// 前回の位置 タイプ
		g_aPlayer[nIdy].posOld = g_aPlayer[nIdy].pos;
		g_aPlayer[nIdy].nMotionTypeOld = g_aPlayer[nIdy].nMotionType;
		g_aPlayer[nIdy].bCatchOld = g_aPlayer[nIdy].bCatch;
		g_aPlayer[nIdy].nItemTime--;	// アイテムの時間減少
		if (g_aPlayer[nIdy].nItemTime <= 0)
		{// アイテムの時間
			g_aPlayer[nIdy].fPulsLife = 0;			// アイテムで増えるライフ
			g_aPlayer[nIdy].fPulsAttack = 0;		// アイテムで加算される攻撃力
			g_aPlayer[nIdy].fPulsSpeed = 0;			// アイテムで増えるスピード
			g_aPlayer[nIdy].MoveSpeed = g_aPlayerData[g_aPlayer[nIdy].type].MoveSpeed;

		}
		for (int nbMotion = 0; nbMotion < PLAYER_BOOL_MAX; nbMotion++)
		{// 前回のモーション
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
		case PLAYERSTATE_FALL:	// 落下
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
		case PLAYERSTATE_CRASHSTART:	// 混乱
			g_aPlayer[nIdy].nCntState--;
			g_aPlayer[nIdy].move.x = 0;
			g_aPlayer[nIdy].move.z = 0;
			if (g_aPlayer[nIdy].nCntState <= 0)
			{
				g_aPlayer[nIdy].state = PLAYERSTATE_CRASH;
				g_aPlayer[nIdy].nCntState = 300;

			}
			break;
		case PLAYERSTATE_CRASH:	// 混乱
			g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CRASH] = true;	// 混乱
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
			{// 点滅
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
		{// 下に落ちたら死ぬ
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
		{// 生きているなら
			if (GetMode() != MODE_RESULT&&GetMode() != MODE_CHARACTER&&GetGameState() != GAMESTATE_END)
			{
				if (pCamera->nState == CAMERASTATE_NONE || pCamera->nState == CAMERASTATE_SPECIAL)
				{
					if (!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_WIN])
					{
						PlayerController(nIdy);
					}
				}
				// ダメージの時の計算
				if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] || g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_DAMAGE]
					|| g_aPlayer[nIdy].state == PLAYERSTATE_DAMAGE)
				{// 吹っ飛び力がまだあったら
					if (g_aPlayer[nIdy].fFlyPower.x >= 0.1f ||
						g_aPlayer[nIdy].fFlyPower.x <= -0.1f)
					{// 水平方向の吹っ飛び力があるなら
						g_aPlayer[nIdy].move.x = g_aPlayer[nIdy].fFlyPower.x;	// 吹っ飛び力を加算
					}
					if (g_aPlayer[nIdy].fFlyPower.z >= 0.1f ||
						g_aPlayer[nIdy].fFlyPower.z <= -0.1f)
					{// 水平方向の吹っ飛び力があるなら
						g_aPlayer[nIdy].move.z = g_aPlayer[nIdy].fFlyPower.z;	// 吹っ飛び力を加算
					}

					if (g_aPlayer[nIdy].nFlyCounter > 0)
					{// 吹っ飛ぶカウンターが0より大きかったら
						g_aPlayer[nIdy].fFlyPower.y -= 0.5f;
						if (g_aPlayer[nIdy].fFlyPower.y > 0.0f)
						{// ジャンプ力がまだあったら
							g_aPlayer[nIdy].move.y = g_aPlayer[nIdy].fFlyPower.y;			// 上昇していく
						}
						if (rand() % 2 == 0)
						{// 煙エフェクト
							float fDirection[3] = { SetRandomEffect(),SetRandomEffect(),SetRandomEffect() };
							SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(fDirection[0]) * 10, cosf(fDirection[1]) * 10, cosf(fDirection[2]) * 10),
								D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), g_aPlayer[nIdy].col, float(rand() % 80 + 10), 10, EFFECTTYPE_SMOKE);
						}
					}
					for (int nCntAttack = 0; nCntAttack < PLAYER_ATTACK_TYPE_MAX; nCntAttack++)
					{// 攻撃の種類分ループ
						if (g_aPlayer[nIdy].bAttackType[nCntAttack] == true)
						{// 攻撃中だったら
							g_aPlayer[nIdy].move.x = 0.0f;	// 吹っ飛び力を加算
							g_aPlayer[nIdy].move.z = 0.0f;	// 吹っ飛び力を加算

						}
					}

				}

				// 向きの回転速度の減速
				if (g_aPlayer[nIdy].nMotionType != PLAYER_MOTION_TYPE_GETUP)
				{// 起き上がり時じゃなければ
					g_aPlayer[nIdy].fRotSpeed = PLAYER_ROT_SPEED_NORMAL;			// 通常の回転速度を入れる
					for (int nCntAttack = 0; nCntAttack < PLAYER_ATTACK_TYPE_MAX; nCntAttack++)
					{// 攻撃の種類分ループ
						if (g_aPlayer[nIdy].bAttackType[nCntAttack] == true)
						{// 攻撃中だったら
							g_aPlayer[nIdy].fRotSpeed = PLAYER_ROT_SPEED_ATTACK;	// 向きの回転速度を遅くする
						}
					}

				}

			}
		}
		if (g_aPlayer[nIdy].nMotionType != g_aPlayer[nIdy].nMotionTypeOld)
		{
			g_aPlayer[nIdy].fRotSpeed = PLAYER_ROT_SPEED_NORMAL;			// 通常の回転速度を入れる

		}
		// 重力加算
		if (GetMode() != MODE_CHARACTER)
		{
			g_aPlayer[nIdy].move.y += -GRAVITY_SPEED;

		}

		// 移動量加算
		g_aPlayer[nIdy].pos += g_aPlayer[nIdy].Environment;
		g_aPlayer[nIdy].pos += g_aPlayer[nIdy].move;
		// 減速更新
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

		//--------------------------/ モデルの動きをなめらかにする /---------------------------------------------------------------------------------------//
		if (g_aPlayer[nIdy].Destrot.y > D3DX_PI)
		{// 差分が3.14を超えるなら
			g_aPlayer[nIdy].Destrot.y -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].Destrot.y < -D3DX_PI)
		{// 差分が-3.14を超えるなら
			g_aPlayer[nIdy].Destrot.y += D3DX_PI * 2.0f;
		}
		g_aPlayer[nIdy].Diffrot.y = g_aPlayer[nIdy].Destrot.y - g_aPlayer[nIdy].rot.y;// 現在の角度と目的の角度の差分
		if (g_aPlayer[nIdy].Diffrot.y > D3DX_PI)
		{// 差分が3.14を超えるなら
			g_aPlayer[nIdy].Diffrot.y -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].Diffrot.y < -D3DX_PI)
		{// 差分が-3.14を超えるなら
			g_aPlayer[nIdy].Diffrot.y += D3DX_PI * 2.0f;
		}
		g_aPlayer[nIdy].rot.y += g_aPlayer[nIdy].Diffrot.y * g_aPlayer[nIdy].fRotSpeed;	// 角度の加算
		if (g_aPlayer[nIdy].rot.y > D3DX_PI)
		{// 現在の角度が3.14を超えるなら
			g_aPlayer[nIdy].rot.y -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].rot.y < -D3DX_PI)
		{// 現在の角度が-3.14を超えるなら
			g_aPlayer[nIdy].rot.y += D3DX_PI * 2.0f;
		}
		//----------------------------------/ 当たり判定 /---------------------------------------------------------------------------------------//
			// メッシュフィールド
		if (CollisionMeshField(&g_aPlayer[nIdy].pos, &g_aPlayer[nIdy].posOld, &g_aPlayer[nIdy].move,
			g_aPlayer[nIdy].fRadiusWidth, g_aPlayer[nIdy].fRadiusHeight, &g_aPlayer[nIdy].pMeshFieldLand) == true)
		{
			Shadow *pShadow = GetShadow();
			pShadow[g_aPlayer[nIdy].nIdyShadow].pos.y = g_aPlayer[nIdy].pos.y + 0.1f;
			pShadow[g_aPlayer[nIdy].nIdyShadow].col.a = 1.0f;
			g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] = false;
			g_aPlayer[nIdy].bJump = false;
			g_aPlayer[nIdy].nAirCounter = 0;// 空中攻撃制御カウンター

			if (g_aPlayer[nIdy].state != PLAYERSTATE_DEATH&&g_aPlayer[nIdy].state != PLAYERSTATE_CRASH)
			{
				if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] == true)
				{
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] = false;
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP] = true;
				}
			}
			if (!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] && g_aPlayer[nIdy].bMotionStateOld[PLAYER_BOOL_JUMP])
			{// 着地した
				for (int nCntEffect = 0; nCntEffect < 2; nCntEffect++)
				{// 着地エフェクト
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
		{// 床に乗っている
			if ((g_aPlayer[nIdy].move.x > 1.0f || g_aPlayer[nIdy].move.z > 1.0f ||
				g_aPlayer[nIdy].move.x < -1.0f || g_aPlayer[nIdy].move.z < -1.0f))
			{// 歩いている
			}
			else
			{
			}
		}
		// プレイヤー同士
		PlayerOverLap(g_aPlayer[nIdy].nIdy);

		// モデル
		if (CollisionModelMinMax(&g_aPlayer[nIdy].pos, &g_aPlayer[nIdy].posOld, &g_aPlayer[nIdy].move, g_aPlayer[nIdy].fRadiusWidth, g_aPlayer[nIdy].fRadiusHeight, &g_aPlayer[nIdy].pModel) == 2)
		{// 上にのる
			Shadow *pShadow = GetShadow();
			pShadow[g_aPlayer[nIdy].nIdyShadow].pos.y = g_aPlayer[nIdy].pos.y + 0.1f;
			pShadow[g_aPlayer[nIdy].nIdyShadow].col.a = 1.0f;
			g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] = false;
			g_aPlayer[nIdy].bJump = false;
			g_aPlayer[nIdy].nAirCounter = 0;// 空中攻撃制御カウンター
			if (g_aPlayer[nIdy].state != PLAYERSTATE_DEATH&&g_aPlayer[nIdy].state != PLAYERSTATE_CRASH)
			{
				if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] == true)
				{
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] = false;
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP] = true;
				}
			}
			if (!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] && g_aPlayer[nIdy].bMotionStateOld[PLAYER_BOOL_JUMP])
			{// 着地した
				for (int nCntEffect = 0; nCntEffect < 20; nCntEffect++)
				{// 着地エフェクト
					SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(SetRandomEffect()) * 10, 0.0f, cosf(SetRandomEffect()) * 10),
						D3DXVECTOR3(sinf(SetRandomEffect()) * float(rand()%5) , cosf(SetRandomEffect())*0.5f, cosf(SetRandomEffect()) * float(rand() % 5)),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.9f, 0.9f, 1.0f), float(rand() % 30), 0, EFFECTTYPE_WALK);
				}
				PlaySound(SOUND_LABEL_LAND);
			}
			if ((g_aPlayer[nIdy].move.x > g_aPlayer[nIdy].MoveSpeed || g_aPlayer[nIdy].move.z > g_aPlayer[nIdy].MoveSpeed ||
				g_aPlayer[nIdy].move.x < -g_aPlayer[nIdy].MoveSpeed || g_aPlayer[nIdy].move.z < -g_aPlayer[nIdy].MoveSpeed))
			{// 歩いている　歩く　走る
			 // 敵と当たるものの距離
				float fPosX = (g_aPlayer[nIdy].pos.x - 200);
				float fPosZ = (g_aPlayer[nIdy].pos.z - 200);
				float fRadiusA = fPosX*fPosX  + fPosZ*fPosZ;
				float fRadiusB = (150 + 150)* (150 + 150);

				if (fRadiusB > fRadiusA&&
					-fRadiusB < fRadiusA)
				{// 石の上
					SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(SetRandomEffect()) * 10, cosf(SetRandomEffect()), cosf(SetRandomEffect()) * 10),
						D3DXVECTOR3(sinf(SetRandomEffect()) * 2 + sinf(g_aPlayer[nIdy].rot.y), cosf(SetRandomEffect()), cosf(SetRandomEffect()) * 2 + cosf(g_aPlayer[nIdy].rot.y)),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.9f, 0.9f, 1.0f), float(rand() % 30), 0, EFFECTTYPE_WALK);
					if (rand() % 5 == 0){
						SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(SetRandomEffect()) * 10, cosf(SetRandomEffect()), cosf(SetRandomEffect()) * 10)+ D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y) * 30, cosf(SetRandomEffect()), cosf(g_aPlayer[nIdy].rot.y) * 30),
							D3DXVECTOR3(sinf(SetRandomEffect()) * 2 + sinf(g_aPlayer[nIdy].rot.y), 0.5f, cosf(SetRandomEffect()) * 2 + cosf(g_aPlayer[nIdy].rot.y)),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.9f, 0.9f, 2.0f), float(rand() % 4) * 10, 0, EFFECTTYPE_CARTOON_TA);}
				}
				else
				{// 土
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
		{// 奥行き上限
			g_aPlayer[nIdy].pos.z = MAX_DEPTH;
		}
		// メッシュウォール
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
		{// 前回と今回のジャンプモーションが違ったら着地モーション
			g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_LANDING] = true;
		}
		//------------------------------------/ 基本モーション /-----------------------------------------------------------------/
		//if (g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK] == false)

			if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CRASH])
			{// 混乱状態なら
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_CRASH;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CATCH])
			{// 拾う状態なら
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_CATCH;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_THROW])
			{// 投げる状態なら
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_THROW;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP] )
			{// 倒れてる状態なら
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_GETUP;
				g_aPlayer[nIdy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] )
			{// ダメージ(吹っ飛び)中なら
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_FLY;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_DAMAGE] )
			{// ダメージ(仰け反り)中なら
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_DAMAGE;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] )
			{// プレイヤーがジャンプ中なら
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_JUMP;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_LANDING] )
			{// 着地中なら
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_LANDING;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD])
			{// ガード中なら
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_GUARD;
			}
			else if (g_aPlayer[nIdy].move.x > PLAYER_MOTION_MOVE_ZONE ||
				g_aPlayer[nIdy].move.x < -PLAYER_MOTION_MOVE_ZONE ||
				g_aPlayer[nIdy].move.z >  PLAYER_MOTION_MOVE_ZONE ||
				g_aPlayer[nIdy].move.z < -PLAYER_MOTION_MOVE_ZONE)
			{// プレイヤーが動いているとき
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_MOVE;
			}
			else if (g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_WIN])
			{// 勝利モーションなら
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_WIN;
			}
			else
			{// プレイヤーが動いてないとき
				g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_NEUTRAL;
			}
		//--------------------------- 攻撃モーション -----------------------------------------------------//
		if (g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK])
		{// 弱モーションの設定
			g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_WEAK;
		}
		if (g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2])
		{//  弱2の設定
			g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_WEAK_2;
		}
		if (g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3])
		{// 弱3の設定
			g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_WEAK_3;
		}
		if (g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4])
		{// 弱4の設定
			g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_WEAK_4;
		}
		if (g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5])
		{// 弱5の設定
			g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_WEAK_5;
		}
		if (g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_SPECIAL])
		{// 必殺技の設定
			g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_SPECIAL;
		}
		// モーション
		MotionInfoPlayer(nIdy);
		if (g_aPlayer[nIdy].bCombo)
		{// コンボオン
			g_aPlayer[nIdy].nComboCounter--;

			if (g_aPlayer[nIdy].nComboCounter == 0)
			{
				AllReleaseAttack(nIdy);

				g_aPlayer[nIdy].bCombo = false;
			}
		}
		//********************************************************************************************************************************
		// キャラクター制御
		//*************************************************************************************************************************
		switch (g_aPlayer[nIdy].nMotionType)
		{// プレイヤーのモーションが
		case PLAYER_MOTION_TYPE_JUMP:						// ジャンプモーションだったら
			break;
		case PLAYER_MOTION_TYPE_LANDING:					// 着地モーションだったら
			break;
		case PLAYER_MOTION_TYPE_DAMAGE:						// ダメージ(仰け反り)モーションだったら
			break;
		case PLAYER_MOTION_TYPE_FLY:						// ダメージ(吹っ飛び)モーションだったら
			break;
		case PLAYER_MOTION_TYPE_GETUP:						// 起き上がりモーションだったら
			break;
		case PLAYER_MOTION_TYPE_CATCH:
			break;
		case PLAYER_MOTION_TYPE_THROW:
			if (g_aPlayer[nIdy].nFrameAllCounter == 15)
			{
				if (MATURI) {/* 女の子*/PlaySound(SOUND_HUMAN_NAGERU); }
				if (AMANO) {/* 天狗*/PlaySound(SOUND_TENGU_NAGERU); }
				if (GOJOU) {/* 河童*/PlaySound(SOUND_KAPA_NAGERU); }
				if (MOMIJI) {/* 狐*/PlaySound(SOUND_FOX_NAGERU); }
				if (DONROID) {/* ロボット*/PlaySound(SOUND_ROBOT_GARD); }
				g_aPlayer[nIdy].bCatch = false;
				g_aPlayer[nIdy].pModelAtk->move = D3DXVECTOR3(sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 10, 0, cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * 10);
			}
			if (g_aPlayer[nIdy].nFrameAllCounter >= 15 && g_aPlayer[nIdy].nFrameAllCounter <= 25)
			{// モーションのフレームの時
				g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
			}
			break;
		case PLAYER_MOTION_TYPE_GUARD:						// ガードモーションだったら
			break;
		case PLAYER_MOTION_TYPE_CRASH:						// 混乱モーションだったら
			break;
		case PLAYER_MOTION_TYPE_WEAK:						// 攻撃モーションだったら
			if (MATURI)
			{
				if (g_aPlayer[nIdy].nFrameAllCounter == 5) { PlaySound(SOUND_HUMAN_ATTACK000); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 8 && g_aPlayer[nIdy].nFrameAllCounter <= 15)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			if (AMANO)
			{// 天狗
				if (g_aPlayer[nIdy].nFrameAllCounter == 22) { PlaySound(SOUND_TENGU_ATTACK000); }
				if (g_aPlayer[nIdy].nFrameAllCounter == 22)
				{// 竜巻を起こす
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
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			if (GOJOU)
			{// 河童
				if (g_aPlayer[nIdy].nFrameAllCounter == 5) { PlaySound(SOUND_KAPA_ATTACK000); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 0 && g_aPlayer[nIdy].nFrameAllCounter <= 5)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 14 && g_aPlayer[nIdy].nFrameAllCounter <= 18)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			if (MOMIJI)
			{// きつね
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) {PlaySound(SOUND_FOX_ATTACK000);}// 攻撃ボイス再生
				if (g_aPlayer[nIdy].nFrameAllCounter >= 16 && g_aPlayer[nIdy].nFrameAllCounter <=23)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			if (DONROID)
			{// ロボット
				if (g_aPlayer[nIdy].nFrameAllCounter == 25) {PlaySound(SOUND_ROBOT_ATTACK000);}// 攻撃ボイス再生
				if (g_aPlayer[nIdy].nFrameAllCounter >= 27 && g_aPlayer[nIdy].nFrameAllCounter <= 35)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			break;
		case PLAYER_MOTION_TYPE_WEAK_2:				// 弱2
			if (MATURI)
			{// 女の子
				if (g_aPlayer[nIdy].nFrameAllCounter == 5) { PlaySound(SOUND_HUMAN_ATTACK001); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 6 && g_aPlayer[nIdy].nFrameAllCounter <= 15)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			if (AMANO)
			{// 天狗
				if (g_aPlayer[nIdy].nFrameAllCounter == 25) { PlaySound(SOUND_TENGU_ATTACK001); }
				if (g_aPlayer[nIdy].nFrameAllCounter == 25)
				{// 竜巻を起こす
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
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.y = 10;
				}
			}
			if (GOJOU)
			{// 河童
				if (g_aPlayer[nIdy].nFrameAllCounter == 5) { PlaySound(SOUND_KAPA_ATTACK001); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 9 && g_aPlayer[nIdy].nFrameAllCounter <= 11)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed * 2);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed * 2);
				}
			}
			if (MOMIJI)
			{// きつね
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) { PlaySound(SOUND_FOX_ATTACK001); }// 攻撃ボイス再生
				if (g_aPlayer[nIdy].nFrameAllCounter >= 12 && g_aPlayer[nIdy].nFrameAllCounter <= 21)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			if (DONROID)
			{// ロボット
				if (g_aPlayer[nIdy].nFrameAllCounter == 25) { PlaySound(SOUND_ROBOT_ATTACK001); }// 攻撃ボイス再生
				if (g_aPlayer[nIdy].nFrameAllCounter >= 26 && g_aPlayer[nIdy].nFrameAllCounter <= 35)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			break;
		case PLAYER_MOTION_TYPE_WEAK_3:			// 弱3
			if (MATURI)
			{// 女の子
				if (g_aPlayer[nIdy].nFrameAllCounter == 20) { PlaySound(SOUND_HUMAN_ATTACK002); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 25 && g_aPlayer[nIdy].nFrameAllCounter <= 33)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed);
				}
			}
			if (AMANO)
			{// 天狗
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) { PlaySound(SOUND_TENGU_ATTACK002); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 10 && g_aPlayer[nIdy].nFrameAllCounter <= 15)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.y = 2;
				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 16 && g_aPlayer[nIdy].nFrameAllCounter <= 25)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.y = -15;
				}
				if ( g_aPlayer[nIdy].nFrameAllCounter == 20)
				{// モーションのフレームの時
					float fRadius = 0.0f;
					for (int nCnt = 0; nCnt < 40; nCnt++)
					{// 時計の形
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
			{// 河童
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) { PlaySound(SOUND_KAPA_ATTACK002); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 0 && g_aPlayer[nIdy].nFrameAllCounter <= 13)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed *1.0f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed *1.0f);
				}

			}
			if (MOMIJI)
			{// きつね
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) { PlaySound(SOUND_FOX_ATTACK002); }// 攻撃ボイス再生
				if (g_aPlayer[nIdy].nFrameAllCounter >= 13 && g_aPlayer[nIdy].nFrameAllCounter <= 19)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*2);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*2);
				}
			}
			if (DONROID)
			{// ロボット
				if (g_aPlayer[nIdy].nFrameAllCounter == 5) { PlaySound(SOUND_ROBOT_ATTACK002); }// 攻撃ボイス再生
				if (g_aPlayer[nIdy].nFrameAllCounter >= 24 && g_aPlayer[nIdy].nFrameAllCounter <= 30)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*3);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*3);
				}
			}
			break;
		case PLAYER_MOTION_TYPE_WEAK_4:			// 弱4
			if (MATURI)
			{// 女の子
				if (g_aPlayer[nIdy].nFrameAllCounter == 3) { PlaySound(SOUND_HUMAN_ATTACK003); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 5 && g_aPlayer[nIdy].nFrameAllCounter <= 40)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*1.5f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*1.5f);
				}
			}
			if (AMANO)
			{// 天狗
				if (g_aPlayer[nIdy].nFrameAllCounter == 34) { PlaySound(SOUND_TENGU_ATTACK003); }

				if (g_aPlayer[nIdy].nFrameAllCounter == 45)
				{// モーションのフレームの時
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
			{// 河童
				if (g_aPlayer[nIdy].nFrameAllCounter == 10) { PlaySound(SOUND_KAPA_ATTACK003); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 10 && g_aPlayer[nIdy].nFrameAllCounter <= 20)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed *1.5f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed *1.5f);
				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 21 && g_aPlayer[nIdy].nFrameAllCounter <= 35)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed *1.0f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed *1.0f);
				}

			}
			if (MOMIJI)
			{// きつね
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) { PlaySound(SOUND_FOX_ATTACK003); }// 攻撃ボイス再生
				if (g_aPlayer[nIdy].nFrameAllCounter >= 15 && g_aPlayer[nIdy].nFrameAllCounter <= 21)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed * 2.5f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed * 2.5f);
				}
			}
			if (DONROID)
			{// ロボット
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) { PlaySound(SOUND_ROBOT_ATTACK003); }// 攻撃ボイス再生
				if (g_aPlayer[nIdy].nFrameAllCounter >= 10 && g_aPlayer[nIdy].nFrameAllCounter <= 30)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed );
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed );
				}
			}
			break;
		case PLAYER_MOTION_TYPE_WEAK_5:			// 弱5
			if (MATURI)
			{// 女の子
				if (g_aPlayer[nIdy].nFrameAllCounter == 20) { PlaySound(SOUND_HUMAN_ATTACK004); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 20 && g_aPlayer[nIdy].nFrameAllCounter <= 30)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*2.0f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y - D3DX_PI) * g_aPlayer[nIdy].MoveSpeed*2.0f);
				}
			}
			if (AMANO)
			{// 天狗
				if (g_aPlayer[nIdy].nFrameAllCounter == 30) { PlaySound(SOUND_TENGU_ATTACK004); }

				if (g_aPlayer[nIdy].nFrameAllCounter >= 44 && g_aPlayer[nIdy].nFrameAllCounter <= 50)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y ) * g_aPlayer[nIdy].MoveSpeed * 2.5f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y ) * g_aPlayer[nIdy].MoveSpeed * 2.5f);
				}
				if (g_aPlayer[nIdy].nFrameAllCounter == 44)
				{// モーションのフレームの時
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
			{// 河童
				if (g_aPlayer[nIdy].nFrameAllCounter == 10) { PlaySound(SOUND_KAPA_ATTACK004); }

			}
			if (MOMIJI)
			{// きつね
				if (g_aPlayer[nIdy].nFrameAllCounter == 1) { PlaySound(SOUND_FOX_ATTACK005); }// 攻撃ボイス再生
				if (g_aPlayer[nIdy].nFrameAllCounter >= 5 && g_aPlayer[nIdy].nFrameAllCounter <= 11)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.y = 8;
				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 31 && g_aPlayer[nIdy].nFrameAllCounter <= 40)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.y += -3;
				}
			}
			if (DONROID)
			{// ロボット
				if (g_aPlayer[nIdy].nFrameAllCounter == 30) { PlaySound(SOUND_ROBOT_ATTACK005); }// 攻撃ボイス再生
				if (g_aPlayer[nIdy].nFrameAllCounter >= 34 && g_aPlayer[nIdy].nFrameAllCounter <= 35)
				{// モーションのフレームの時
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
		case PLAYER_MOTION_TYPE_SPECIAL:// 必殺技
			if (MATURI)
			{// 女の子
				if (g_aPlayer[nIdy].nFrameAllCounter == 20) { PlaySound(SOUND_HUMAN_ATTACK008); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 20 && g_aPlayer[nIdy].nFrameAllCounter <= 30)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.y = 5.0f;

				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 20 && g_aPlayer[nIdy].nFrameAllCounter <= 40)
				{
					for (int nCnt = 0; nCnt < 5; nCnt++)
					{// 雷
						SetEffect(D3DXVECTOR3(g_aPlayer[nIdy].aModel[6].mtxWorld._41, g_aPlayer[nIdy].aModel[6].mtxWorld._42, g_aPlayer[nIdy].aModel[6].mtxWorld._43) +
							D3DXVECTOR3(sinf(SetRandomEffect()) * 30.0f, cosf(SetRandomEffect()) * 30.0f, cosf(SetRandomEffect()) * 30.0f)
							, D3DXVECTOR3(sinf(SetRandomEffect()) * 1.5f, cosf(SetRandomEffect()) * 1.5f, cosf(SetRandomEffect()) * 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), float(rand() % 50) + 10, 0, EFFECTTYPE_SUNDER);
					}
				}
			}
			if (GOJOU)
			{// 河童
				if (g_aPlayer[nIdy].nFrameAllCounter == 20) { PlaySound(SOUND_KAPA_ATTACK005); }
				if (g_aPlayer[nIdy].nFrameAllCounter >= 35 && g_aPlayer[nIdy].nFrameAllCounter <= 40)
				{
					g_aPlayer[nIdy].move.x += (sinf(g_aPlayer[nIdy].rot.y) * g_aPlayer[nIdy].MoveSpeed * 2.0f);
					g_aPlayer[nIdy].move.z += (cosf(g_aPlayer[nIdy].rot.y) * g_aPlayer[nIdy].MoveSpeed * 2.0f);
				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 30 && g_aPlayer[nIdy].nFrameAllCounter <= 80)
				{// モーションのフレームの時
					for (int nCnt = 0; nCnt < 10; nCnt++)
					{// 水
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
			{// 天狗
				if (g_aPlayer[nIdy].nFrameAllCounter == 10) { PlaySound(SOUND_TENGU_ATTACK005); }

				if (g_aPlayer[nIdy].nFrameAllCounter >= 10 && g_aPlayer[nIdy].nFrameAllCounter <= 50)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.y = 3.0f;
				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 50)
				{// モーションのフレームの時
					g_aPlayer[nIdy].move.y = 1.0f;
				}
				if (g_aPlayer[nIdy].nFrameAllCounter >= 45&&g_aPlayer[nIdy].nFrameAllCounter <= 55)
				{// モーションのフレームの時
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
			{// きつね
				if (g_aPlayer[nIdy].nFrameAllCounter == 10) { PlaySound(SOUND_FOX_ATTACK004); }// 攻撃ボイス再生

				if (g_aPlayer[nIdy].nFrameAllCounter == 30){PlaySound(SOUND_LABEL( SOUND_EFFECT_FLAME000 + rand()%2));}// 攻撃再生

				if (g_aPlayer[nIdy].nFrameAllCounter >= 30 && g_aPlayer[nIdy].nFrameAllCounter <= 80)
				{// モーションのフレームの時
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
			{// ロボット
				if (g_aPlayer[nIdy].nFrameAllCounter == 30) { PlaySound(SOUND_EFFECT_BOMB000); PlaySound(SOUND_EFFECT_BOMB001);
				g_aPlayer[nIdy].fLife -= 20;
				GetPlayerLife(int(g_aPlayer[nIdy].fLife), nIdy);}// 攻撃ボイス再生
				if (g_aPlayer[nIdy].nFrameAllCounter >= 30 && g_aPlayer[nIdy].nFrameAllCounter <= 35)
				{// モーションのフレームの時
					for (int nCntEffect = 0; nCntEffect < 1; nCntEffect++)
					{// 衝撃は
						SetEffect(g_aPlayer[nIdy].pos,
							D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXCOLOR(0.8f, 0.5f, 0.0f, 1.5f),float( rand()%100), 30, EFFECTTYPE_IMPACT);
					}
					for (int nCnt = 0; nCnt < 50; nCnt++)
					{// 爆発
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
				{// モーションのフレームの時
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
				{// モーションのフレームの時
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
			{// 起き上がり終わったら
				g_aPlayer[nIdy].nCntState = 60;
				g_aPlayer[nIdy].state = PLAYERSTATE_INVINCIBLE;	// 無敵
			}
		}

		if (!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD])
		{// ガードしてない
			g_aPlayer[nIdy].fGuardLife += 0.01f;
			if (g_aPlayer[nIdy].fGuardLife >= 1.0f)
			{
				g_aPlayer[nIdy].fGuardLife = 1.0f;
			}
		}
		else
		{// ガード
			g_aPlayer[nIdy].fGuardLife -= 0.001f;
			if (g_aPlayer[nIdy].fGuardLife <= 0)
			{
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD] = false;
				g_aPlayer[nIdy].state = PLAYERSTATE_CRASH;
				g_aPlayer[nIdy].nCntState = 300;
				// 垂直方向の吹っ飛び力を代入
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CRASH] = true;	// 混乱設定
			}
		}
//-------------------------------------/ 影 線 を移動する /---------------------------------------------------------------------------------------//
		SetPositionShadow(g_aPlayer[nIdy].nIdyShadow, D3DXVECTOR3(g_aPlayer[nIdy].aModel[0].mtxWorld._41, g_aPlayer[nIdy].aModel[0].mtxWorld._42, g_aPlayer[nIdy].aModel[0].mtxWorld._43), g_aPlayer[nIdy].Initpos);
		SetPositionLine(g_aPlayer[nIdy].nIdyLine, g_aPlayer[nIdy].pos, g_aPlayer[nIdy].rot);
		if (g_aPlayer[nIdy].fPulsAttack > 0.0f)
		{// 攻撃力が上昇していたら
			SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(SetRandomEffect())*20.0f, 0.0f, cosf(SetRandomEffect())*20.0f),
				D3DXVECTOR3(0.0f, float(rand() % 2 + 1), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.3f, 0.3f, float(rand()%100)/100.0f),
				float(rand()%50), 60, EFFECTTYPE_STATE_UP);
		}
		if (g_aPlayer[nIdy].fPulsSpeed > 0.0f)
		{// すばやさが上昇していたら
			SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(SetRandomEffect())*20.0f, 0.0f, cosf(SetRandomEffect())*20.0f),
				D3DXVECTOR3(0.0f, float(rand() % 2 + 1), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.3f, 0.3f, 1.0f, float(rand() % 100) / 100.0f),
				float(rand() % 50), 60, EFFECTTYPE_STATE_UP);
		}
	}
}
//==============================================================================================================================
// 描画処理
//==============================================================================================================================
void DrawPlayer(int nIdy, int nCamera)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		// 計算用マトリックス
	D3DMATERIAL9 matDef;				// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;					// マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;				// 親のマトリックス
	D3DXCOLOR col = GetEventColor();

	Shader shader = GetShader();
	// テクニックの設定
	shader.pShader->SetTechnique("StandardShader");
	// シェーダ開始
	shader.pShader->Begin(0, 0);

	// ライト影響受けない
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_aPlayer[nIdy].mtxWorld);
	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer[nIdy].rot.y, g_aPlayer[nIdy].rot.x, g_aPlayer[nIdy].rot.z);
	D3DXMatrixMultiply(&g_aPlayer[nIdy].mtxWorld, &g_aPlayer[nIdy].mtxWorld, &mtxRot);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nIdy].pos.x, g_aPlayer[nIdy].pos.y, g_aPlayer[nIdy].pos.z);
	D3DXMatrixMultiply(&g_aPlayer[nIdy].mtxWorld, &g_aPlayer[nIdy].mtxWorld, &mtxTrans);
	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer[nIdy].mtxWorld);

	if (g_aPlayer[nIdy].bUse)
	{
		for (int nCntPlayerModel = 0; nCntPlayerModel < g_aPlayerData[g_aPlayer[nIdy].type].nNumParts; nCntPlayerModel++)
		{

			// 過去
			g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorldOld = g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld;

			if (g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].nIdxModelPareant == -1)
			{// プレイヤー
				mtxParent = g_aPlayer[nIdy].mtxWorld;
			}
			else
			{// 各親
				mtxParent = g_aPlayer[nIdy].aModel[g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].nIdxModelPareant].mtxWorld;
			}
			// ------------------------/ 親モデルの描画 /-------------------------------------------//
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld);
			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer[nIdy].aModel[nCntPlayerModel].rot.y, g_aPlayer[nIdy].aModel[nCntPlayerModel].rot.x, g_aPlayer[nIdy].aModel[nCntPlayerModel].rot.z);
			D3DXMatrixMultiply(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &mtxRot);
			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nIdy].aModel[nCntPlayerModel].pos.x,
				g_aPlayer[nIdy].aModel[nCntPlayerModel].pos.y,
				g_aPlayer[nIdy].aModel[nCntPlayerModel].pos.z);
			D3DXMatrixMultiply(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &mtxTrans);
			D3DXMatrixMultiply(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &mtxParent);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld);

			// ビューマトリックスを設定
			D3DXMATRIX matrix = g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld *GetCamera()[nCamera].mtxView * GetCamera()[nCamera].mtxProjection;
			shader.pShader->SetMatrix("g_fMatrix", &matrix);
			shader.pShader->SetVector("g_fColor", &D3DXVECTOR4(col.r, col.g, col.b, col.a)); // 色設定
																										 // パスの描画開始
			shader.pShader->BeginPass(0);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);
			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].pBuffMat->GetBufferPointer();
			if (g_aPlayer[nIdy].bDraw)
			{
				for (int nCntPlayer2 = 0; nCntPlayer2 < (int)g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].nNumMat; nCntPlayer2++)
				{
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntPlayer2].MatD3D);
					// テクスチャの設定
					pDevice->SetTexture(0, g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].pTextuer[g_aPlayer[nIdy].colType][nCntPlayer2]);
					// ランプテクスチャの設定(1番にランプテクスチャを設定)
					pDevice->SetTexture(1, shader.pTexture);

					// モデル(パーツ)の描画
					g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].pMesh->DrawSubset(nCntPlayer2);
				}
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);

			// ------------------------/ 子モデルの描画 /-------------------------------------------//
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld);
			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer[nIdy].aModel[nCntPlayerModel].rot.y, g_aPlayer[nIdy].aModel[nCntPlayerModel].rot.x, g_aPlayer[nIdy].aModel[nCntPlayerModel].rot.z);
			D3DXMatrixMultiply(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &mtxRot);
			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nIdy].aModel[nCntPlayerModel].pos.x,
				g_aPlayer[nIdy].aModel[nCntPlayerModel].pos.y,
				g_aPlayer[nIdy].aModel[nCntPlayerModel].pos.z);

			D3DXMatrixMultiply(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &mtxTrans);
			D3DXMatrixMultiply(&g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld, &mtxParent);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer[nIdy].aModel[nCntPlayerModel].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);
			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].pBuffMat->GetBufferPointer();
			if (g_aPlayer[nIdy].bDraw)
			{
				for (int nCntPlayer2 = 0; nCntPlayer2 < (int)g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].nNumMat; nCntPlayer2++)
				{
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntPlayer2].MatD3D);
					// テクスチャの設定
					pDevice->SetTexture(0, g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].pTextuer[g_aPlayer[nIdy].colType][nCntPlayer2]);
					// ランプテクスチャの設定(1番にランプテクスチャを設定)
					pDevice->SetTexture(1, shader.pTexture);
					// モデル(パーツ)の描画
					g_aPlayerData[g_aPlayer[nIdy].type].aModel[nCntPlayerModel].pMesh->DrawSubset(nCntPlayer2);
				}
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
			// パスの描画終了
			shader.pShader->EndPass();
			for (int nCollision = 0; nCollision < MAX_COLLISION; nCollision++)
			{// 判定のマトリックス
				if (g_aPlayer[nIdy].ColAttack[nCollision].bUse)
				{// 攻撃判定
				 // 前回の位置を繁栄
					g_aPlayer[nIdy].ColAttack[nCollision].mtxWorldOld = g_aPlayer[nIdy].ColAttack[nCollision].mtxWorld;
					// 位置を反映
					D3DXMatrixTranslation(&g_aPlayer[nIdy].ColAttack[nCollision].mtxWorld, g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].ofset.x, g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].ofset.y, g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].ofset.z);
					D3DXMatrixMultiply(&g_aPlayer[nIdy].ColAttack[nCollision].mtxWorld, &g_aPlayer[nIdy].ColAttack[nCollision].mtxWorld, &g_aPlayer[nIdy].aModel[g_aPlayer[nIdy].ColAttack[nCollision].nIdxParent].mtxWorld);
				}
				if (g_aPlayer[nIdy].ColBody[nCollision].bUse)
				{// ダメージ判定
				 // 前回の位置を繁栄
					g_aPlayer[nIdy].ColBody[nCollision].mtxWorldOld = g_aPlayer[nIdy].ColBody[nCollision].mtxWorld;
					// 位置を反映
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
			// 軌跡設定
			SetOrbit(g_aPlayer[nIdy].aModel[g_aPlayer[nIdy].orbit[type][nCntOrbit].nIdyOrbit].mtxWorld,
				g_aPlayer[nIdy].aModel[g_aPlayer[nIdy].orbit[type][nCntOrbit].nIdyOrbit].mtxWorldOld,
				g_aPlayer[nIdy].orbit[type][nCntOrbit].nOrbitLength,
				g_aPlayer[nIdy].orbit[type][nCntOrbit].OrbitStart, g_aPlayer[nIdy].orbit[type][nCntOrbit].OrbitEnd,
				ORBITTYPE(g_aPlayer[nIdy].orbit[type][nCntOrbit].nType), g_aPlayer[nIdy].orbit[type][nCntOrbit].motion);
		}
		PlayerColInfo(nIdy);
	}

	// シェーダ終了
	shader.pShader->End();
	// ライト影響受けない
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
//==============================================================================================================================
// モデルの取得
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
// モデルのモーション
//==============================================================================================================================
void MotionInfoPlayer(int nIdy)
{
	for (int nCnt = 0 ; nCnt < MAX_PLAYER; nCnt++)
	{
		if (g_aPlayer[nIdy].nFrameAllCounter == 1)
		{// 今のタイプと前のタイプが違ったら
			g_aPlayer[nCnt].nMotionGetCol = PLAYER_MOTION_TYPE_MAX;
		}
	}
	if (g_aPlayer[nIdy].nMotionType != g_aPlayer[nIdy].nMotionTypeOld)
	{// 今のタイプと前のタイプが違ったら
		g_aPlayer[nIdy].nKeyCounter = 0;						// キーをリセット
		g_aPlayer[nIdy].nFrameCounter = 0;					// フレームをリセット
		g_aPlayer[nIdy].bBlend = true;	// ブレンドにする
		g_aPlayer[nIdy].nFrame = BLEND_FRAME;					// ブレンドのフレーム
		g_aPlayer[nIdy].nFrameAllCounter = 0;					// 全てのフレーム
		g_aPlayer[nIdy].bCombo = false;
	}
	else if (g_aPlayer[nIdy].bBlend == false )
	{// 通常時のフレーム
		g_aPlayer[nIdy].nFrame = g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].aKey[g_aPlayer[nIdy].nKeyCounter].nFrame;
	}
	if (g_aPlayer[nIdy].nFrameCounter == 0)
	{// 次のキーフレームのモーションを読み込む
		for (int nCntParts = 0; nCntParts < g_aPlayerData[g_aPlayer[nIdy].type].nNumParts; nCntParts++)
		{// Key - 現在 間の差分計算
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
	{// モーション差分加算

		if (g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.x > D3DX_PI)
		{// 差分が3.14を超えるなら
			g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.x -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.x < -D3DX_PI)
		{// 差分が-3.14を超えるなら
			g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.x += D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.y > D3DX_PI)
		{// 差分が3.14を超えるなら
			g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.y -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.y < -D3DX_PI)
		{// 差分が-3.14を超えるなら
			g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.y += D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.z > D3DX_PI)
		{// 差分が3.14を超えるなら
			g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.z -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.z < -D3DX_PI)
		{// 差分が-3.14を超えるなら
			g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion.z += D3DX_PI * 2.0f;
		}
		g_aPlayer[nIdy].aModel[nCntParts].pos += g_aPlayer[nIdy].aModel[nCntParts].posAddMotion;
		g_aPlayer[nIdy].aModel[nCntParts].rot += g_aPlayer[nIdy].aModel[nCntParts].rotAddMotion;

		if (g_aPlayer[nIdy].aModel[nCntParts].rot.x > D3DX_PI)
		{// 現在の角度が3.14を超えるなら
			g_aPlayer[nIdy].aModel[nCntParts].rot.x -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rot.x < -D3DX_PI)
		{// 現在の角度が-3.14を超えるなら
			g_aPlayer[nIdy].aModel[nCntParts].rot.x += D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rot.y > D3DX_PI)
		{// 現在の角度が3.14を超えるなら
			g_aPlayer[nIdy].aModel[nCntParts].rot.y -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rot.y < -D3DX_PI)
		{// 現在の角度が-3.14を超えるなら
			g_aPlayer[nIdy].aModel[nCntParts].rot.y += D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rot.z > D3DX_PI)
		{// 現在の角度が3.14を超えるなら
			g_aPlayer[nIdy].aModel[nCntParts].rot.z -= D3DX_PI * 2.0f;
		}
		if (g_aPlayer[nIdy].aModel[nCntParts].rot.z < -D3DX_PI)
		{// 現在の角度が-3.14を超えるなら
			g_aPlayer[nIdy].aModel[nCntParts].rot.z += D3DX_PI * 2.0f;
		}
	}
	g_aPlayer[nIdy].nFrameCounter++;
	g_aPlayer[nIdy].nFrameAllCounter++;
	if (g_aPlayer[nIdy].bBlend  && g_aPlayer[nIdy].nFrameCounter == BLEND_FRAME)
	{// ブレンド　ブレンドのフレーム数に達する
		g_aPlayer[nIdy].bBlend = false;
		g_aPlayer[nIdy].nFrameCounter = 0;
		g_aPlayer[nIdy].nKeyCounter = 0;// ブレンドで次のモーションの0キー目は行ってる
		if (g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_NEUTRAL)
		{
			g_aPlayer[nIdy].nKeyCounter = 1;
		}
	}
	else if (g_aPlayer[nIdy].bBlend == false&& g_aPlayer[nIdy].nFrameCounter == g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].aKey[g_aPlayer[nIdy].nKeyCounter].nFrame)
	{// フレームカウントが上回る
		g_aPlayer[nIdy].nFrameCounter = 0;
		if (g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].bLoop == false &&
			g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].nNumKey - 1 == g_aPlayer[nIdy].nKeyCounter)
		{// ループしないかつキー数が超える
			g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_LANDING] = false;	// 着地キャンセル

			switch (g_aPlayer[nIdy].nMotionType)
			{// プレイヤーのモーションが
			case PLAYER_MOTION_TYPE_JUMP:																// ジャンプモーションだったら
				break;
			case PLAYER_MOTION_TYPE_LANDING:															// 着地モーションだったら
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_LANDING] = false;										// 着地状態じゃない状態にする

				AllReleaseAttack(nIdy);
				break;
			case PLAYER_MOTION_TYPE_DAMAGE:																// ダメージ(仰け反り)モーションだったら
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_DAMAGE] = false;										// 着地状態じゃない状態にする

				break;
			case PLAYER_MOTION_TYPE_FLY:																// ダメージ(吹っ飛び)モーションだったら
				AllReleaseAttack(nIdy);
				break;
			case PLAYER_MOTION_TYPE_GETUP:																// 起き上がりモーションだったら
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP] = false;						// 起き上がりの状態を解除
				AllReleaseAttack(nIdy);
				break;
			case PLAYER_MOTION_TYPE_CATCH:
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CATCH] = false;						// 起き上がりの状態を解除
				AllReleaseAttack(nIdy);
				break;
			case PLAYER_MOTION_TYPE_THROW:
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_THROW] = false;						// 起き上がりの状態を解除
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
					{// コンボオン
						g_aPlayer[nIdy].nComboCounter = 10;
						g_aPlayer[nIdy].bCombo = true;
					}
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CATCH] = false;
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_THROW] = false;						// 起き上がりの状態を解除
				}
				break;
			}
			g_aPlayer[nIdy].nMotionGetCol = PLAYER_MOTION_TYPE_MAX;
		}
		else
		{// 次のキー数を獲得
			g_aPlayer[nIdy].nKeyCounter = (g_aPlayer[nIdy].nKeyCounter + 1) % g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].nNumKey;
		}
	}

}
//==============================================================================================================================
// プレイヤーの体の当たり判定
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
					{// 死んでない
						{// ダメージ中じゃなければ
							for (int nCntCollision = 0; nCntCollision < MAX_COLLISION; nCntCollision++)
							{// 体の当たり判定分ループ
								if (g_aPlayer[nCnt].ColBody[nCntCollision].bUse)
								{
									// 二つの当たり判定の座標の距離を計算
									float PosX = (g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._41 - mtxWorld.x);		// (プレイヤーの体の当たり判定の座標.x - 敵の攻撃の当たり判定の座標.x)
									float PosY = (g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._42 - mtxWorld.y);		// (プレイヤーの体の当たり判定の座標.y - 敵の攻撃の当たり判定の座標.y)
									float PosZ = (g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._43 - mtxWorld.z);		// (プレイヤーの体の当たり判定の座標.z - 敵の攻撃の当たり判定の座標.z)

									float fPosLenght = (PosX * PosX) + (PosY * PosY) + (PosZ * PosZ);				// それぞれを2乗してすべて足して距離を出す
									// 二つの当たり判定の半径の距離を計算
									float fCollisionRadius = (g_aPlayer[nCnt].ColBody[nCntCollision].fRadius + fRadius);	// プレイヤーの体の当たり判定の半径+敵の攻撃の当たり判定の半径を足す
									float fRadiusLenght = fCollisionRadius * fCollisionRadius;	// 二つの半径を足した値を2乗して、半径の距離を計算を計算

									if (fRadiusLenght > fPosLenght &&
										-fRadiusLenght < fPosLenght)
									{// 座標の距離が半径の距離よりも小さかったら
										float fAttackAngle = atan2f(pos.x - g_aPlayer[nCnt].pos.x, pos.z - g_aPlayer[nCnt].pos.z);	// 当たった角度

										if (g_aPlayer[nCnt].nMotionGetCol != g_aPlayer[nIdy].nMotionType)
										{
											if (g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_GUARD])
											{// ガード中
												g_aPlayer[nCnt].fLife -= 0;
												g_aPlayer[nCnt].fGuardLife -= (nPower/2.0f+ g_aPlayer[nIdy].fPulsAttack) / 10.0f;
												g_aPlayer[nCnt].nCntState = 3;
												PlaySound(SOUND_EFFECT_GUARD);
												for (int nCntE = 0; nCntE < 10; nCntE++)
												{// クラッシュ
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
												{// 狐だけ被ダメ増加
													nPulusDamage = 1.3f;
												}
												g_aPlayer[nCnt].fLife -= (nPower + g_aPlayer[nIdy].fPulsAttack)* nPulusDamage;	// ライフを減らす
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
											{// ライフが0以下になったら
												PlayerLifeZero(nCnt, fAttackAngle, fDamageSide, fDamageV);
											}
											else if (g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_GUARD])
											{// ガードしている
												// 水平方向の吹っ飛び力を代入
												g_aPlayer[nCnt].fFlyPower.x = sinf(fAttackAngle - D3DX_PI) * fDamageSide * 3;
												g_aPlayer[nCnt].fFlyPower.z = cosf(fAttackAngle - D3DX_PI) * fDamageSide * 3;
												g_aPlayer[nCnt].nFlyCounter = 0;
												g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_FLY] = false;	// 吹っ飛ばない
												g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_DAMAGE] = false;// ダメージモーションじゃない
												g_aPlayer[nCnt].state = PLAYERSTATE_DAMAGE;
												if (g_aPlayer[nCnt].fGuardLife <= 0)
												{// ガードわれた
													g_aPlayer[nCnt].fFlyPower.x = 0.0f;
													g_aPlayer[nCnt].fFlyPower.z = 0.0f;
													g_aPlayer[nCnt].fFlyPower.y = 10;
													g_aPlayer[nCnt].nFlyCounter = 10;
													g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_FLY] = true;	// 吹っ飛ばない
													PlaySound(SOUND_EFFECT_GUARD_CRASH);
													UnSetGuard(nCnt, g_aPlayer[nCnt].fGuardLife);
													g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_GUARD] = false;
													g_aPlayer[nCnt].state = PLAYERSTATE_CRASHSTART;
													g_aPlayer[nCnt].nCntState = 80;
													for (int nCntE = 0; nCntE < 100; nCntE++)
													{// クラッシュ
														D3DXVECTOR3 rot = D3DXVECTOR3(SetRandomEffect(), SetRandomEffect(), SetRandomEffect());
														D3DXVECTOR3 move = D3DXVECTOR3(sinf(rot.x) * 10, cosf(rot.y) * 10, cosf(rot.z) * 10);
														SetEffectUP(0,D3DXVECTOR3(g_aPlayer[nCnt].aModel[3].mtxWorld._41, g_aPlayer[nCnt].aModel[3].mtxWorld._42, g_aPlayer[nCnt].aModel[3].mtxWorld._43),
															move, rot, g_aPlayer[nCnt].col, EFFECTUPTYPE_GUARD, 15);
													}
												}
											}
											else
											{// ヒット
												if (fDamageSide > 1.0f && fDamageV > 5.0f)
												{// 吹っ飛び力があるとき
													PlaySound(SOUND_LABEL_HIT001);
													SetPlayerVoice(g_aPlayer[nCnt].type, PLAYER_MOTION_TYPE_FLY);
													g_aPlayer[nCnt].state = PLAYERSTATE_DAMAGE;
													g_aPlayer[nCnt].nCntState = 1;
													// 水平方向の吹っ飛び力を代入
													g_aPlayer[nCnt].fFlyPower.x = sinf(fAttackAngle - D3DX_PI) * fDamageSide;
													g_aPlayer[nCnt].fFlyPower.z = cosf(fAttackAngle - D3DX_PI) * fDamageSide;
													// 垂直方向の吹っ飛び力を代入
													g_aPlayer[nCnt].fFlyPower.y = fDamageV;
													g_aPlayer[nCnt].nFlyCounter = 10;
													g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_FLY] = true;	// 吹っ飛び中に設定

													g_aPlayer[nCnt].Destrot.y = fAttackAngle - D3DX_PI;		// キャラクターの向きを変更
													g_aPlayer[nCnt].rot.y = fAttackAngle - D3DX_PI;			// キャラクターの向きを変更
												}
												else
												{// 水平のみ
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
													{// 2と3番目はスーパーアーマー
														g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_DAMAGE] = false;	// ダメージ中に設定
													}
													else
													{// ダメージ
														AllReleaseAttack(nCnt);
														SetPlayerVoice(g_aPlayer[nCnt].type, PLAYER_MOTION_TYPE_DAMAGE);
														// 吹っ飛び力を代入
														g_aPlayer[nCnt].state = PLAYERSTATE_DAMAGE;
														g_aPlayer[nCnt].nCntState = 3;
														g_aPlayer[nCnt].fFlyPower.x = sinf(fAttackAngle - D3DX_PI) * fDamageSide;
														g_aPlayer[nCnt].fFlyPower.z = cosf(fAttackAngle - D3DX_PI) * fDamageSide;
														g_aPlayer[nCnt].fFlyPower.y = fDamageV;
														g_aPlayer[nCnt].nFlyCounter = 10;
														g_aPlayer[nCnt].Destrot.y = fAttackAngle - D3DX_PI;		// キャラクターの向きを変更
														g_aPlayer[nCnt].rot.y = fAttackAngle - D3DX_PI;			// キャラクターの向きを変更
														g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_DAMAGE] = true;	// ダメージ中に設定
													}
												}

											}
											// ヒットエフェクト
											HitEffect(D3DXVECTOR3(g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._41, g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._42, g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._43));

											bHit = true;	// 当たった									// モーション情報取得
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
				// ライフ連動
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
				{// 死んでない
					{// ダメージ中じゃなければ
						for (int nCntCollision = 0; nCntCollision < MAX_COLLISION; nCntCollision++)
						{// 体の当たり判定分ループ
							if (g_aPlayer[nCnt].ColBody[nCntCollision].bUse)
							{
								// 二つの当たり判定の座標の距離を計算
								float PosX = (g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._41 - mtxWorld.x);		// (プレイヤーの体の当たり判定の座標.x - 敵の攻撃の当たり判定の座標.x)
								float PosY = (g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._42 - mtxWorld.y);		// (プレイヤーの体の当たり判定の座標.y - 敵の攻撃の当たり判定の座標.y)
								float PosZ = (g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._43 - mtxWorld.z);		// (プレイヤーの体の当たり判定の座標.z - 敵の攻撃の当たり判定の座標.z)

								float fPosLenght = (PosX * PosX) + (PosY * PosY) + (PosZ * PosZ);				// それぞれを2乗してすべて足して距離を出す
																												// 二つの当たり判定の半径の距離を計算
								float fCollisionRadius = (g_aPlayer[nCnt].ColBody[nCntCollision].fRadius + fRadius);	// プレイヤーの体の当たり判定の半径+敵の攻撃の当たり判定の半径を足す
								float fRadiusLenght = fCollisionRadius * fCollisionRadius;	// 二つの半径を足した値を2乗して、半径の距離を計算を計算

								if (fRadiusLenght > fPosLenght &&
									-fRadiusLenght < fPosLenght)
								{// 座標の距離が半径の距離よりも小さかったら
									float fAttackAngle = atan2f(pos.x - g_aPlayer[nCnt].pos.x, pos.z - g_aPlayer[nCnt].pos.z);	// 当たった角度
									if (nPower > 0.0f)
									{

										if (g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_GUARD])
										{// ガード中
											g_aPlayer[nCnt].fLife -= 0;
											g_aPlayer[nCnt].fGuardLife -= nPower/2.0f;
											g_aPlayer[nCnt].nCntState = 3;
										}
										else
										{

											g_aPlayer[nCnt].fLife -= nPower;	// ライフを減らす
											if (g_aPlayer[nCnt].state == PLAYERSTATE_CRASH)
											{
												g_aPlayer[nCnt].nCntState = 0;
												g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_CRASH] = false;
												g_aPlayer[nCnt].state = PLAYERSTATE_NONE;
												g_aPlayer[nCnt].fGuardLife = 0.5f;
											}
										}
										if (g_aPlayer[nCnt].fLife <= 0)
										{// ライフが0以下になったら
											PlayerLifeZero(nCnt, fAttackAngle, fDamageSide, fDamageV);
										}
										else if (g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_GUARD])
										{// ガードしている
										 // 水平方向の吹っ飛び力を代入
											g_aPlayer[nCnt].fFlyPower.x = sinf(fAttackAngle - D3DX_PI) * fDamageSide * 3;
											g_aPlayer[nCnt].fFlyPower.z = cosf(fAttackAngle - D3DX_PI) * fDamageSide * 3;
											g_aPlayer[nCnt].nFlyCounter = 0;
											g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_FLY] = false;	// 吹っ飛ばない
											g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_DAMAGE] = false;// ダメージモーションじゃない
											g_aPlayer[nCnt].state = PLAYERSTATE_DAMAGE;
											if (g_aPlayer[nCnt].fGuardLife <= 0)
											{
												UnSetGuard(nCnt, g_aPlayer[nCnt].fGuardLife);
												g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_GUARD] = false;
												g_aPlayer[nCnt].state = PLAYERSTATE_CRASHSTART;
												g_aPlayer[nCnt].nCntState = 30;
												g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_CRASH] = true;	// 混乱
											}
										}
										else
										{// ヒット
											if (fDamageSide > 1.0f && fDamageV > 5.0f)
											{// 吹っ飛び力があるとき
												PlaySound(SOUND_LABEL_HIT001);
												SetPlayerVoice(g_aPlayer[nCnt].type, PLAYER_MOTION_TYPE_FLY);
												g_aPlayer[nCnt].state = PLAYERSTATE_DAMAGE;
												g_aPlayer[nCnt].nCntState = 1;
												// 水平方向の吹っ飛び力を代入
												g_aPlayer[nCnt].fFlyPower.x = sinf(fAttackAngle - D3DX_PI) * fDamageSide;
												g_aPlayer[nCnt].fFlyPower.z = cosf(fAttackAngle - D3DX_PI) * fDamageSide;
												// 垂直方向の吹っ飛び力を代入
												g_aPlayer[nCnt].fFlyPower.y = fDamageV;
												g_aPlayer[nCnt].nFlyCounter = 10;
												g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_FLY] = true;	// 吹っ飛び中に設定

												g_aPlayer[nCnt].Destrot.y = fAttackAngle - D3DX_PI;		// キャラクターの向きを変更
												g_aPlayer[nCnt].rot.y = fAttackAngle - D3DX_PI;			// キャラクターの向きを変更
											}
											else
											{// 水平のみ
												PlaySound(SOUND_LABEL_HIT000);
												AllReleaseAttack(nCnt);
												SetPlayerVoice(g_aPlayer[nCnt].type, PLAYER_MOTION_TYPE_DAMAGE);
												// 吹っ飛び力を代入
												g_aPlayer[nCnt].state = PLAYERSTATE_DAMAGE;
												g_aPlayer[nCnt].nCntState = 3;
												g_aPlayer[nCnt].fFlyPower.x = sinf(fAttackAngle - D3DX_PI) * fDamageSide;
												g_aPlayer[nCnt].fFlyPower.z = cosf(fAttackAngle - D3DX_PI) * fDamageSide;
												g_aPlayer[nCnt].fFlyPower.y = fDamageV;
												g_aPlayer[nCnt].nFlyCounter = 10;
												g_aPlayer[nCnt].Destrot.y = fAttackAngle - D3DX_PI;		// キャラクターの向きを変更
												g_aPlayer[nCnt].rot.y = fAttackAngle - D3DX_PI;			// キャラクターの向きを変更
												g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_DAMAGE] = true;	// ダメージ中に設定
											}
										}
										// ヒットエフェクト
										HitEffect(D3DXVECTOR3(g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._41, g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._42, g_aPlayer[nCnt].ColBody[nCntCollision].mtxWorld._43));

										bHit = true;	// 当たった									// モーション情報取得
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
				// ライフ連動
				GetPlayerLife(int(g_aPlayer[nCnt].fLife), g_aPlayer[nCnt].nIdy);

			}
		}
	}
	return bHit;

}
//==============================================================================================================================
// 判定設定(攻撃判定）
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
			// 位置を反映
			D3DXMatrixTranslation(&g_aPlayerData[nIdy].ColAttack[nCollision].mtxWorld, g_aPlayerData[nIdy].ColAttack[nCollision].ofset.x, g_aPlayerData[nIdy].ColAttack[nCollision].ofset.y, g_aPlayerData[nIdy].ColAttack[nCollision].ofset.z);
			D3DXMatrixMultiply(&g_aPlayerData[nIdy].ColAttack[nCollision].mtxWorld, &g_aPlayerData[nIdy].ColAttack[nCollision].mtxWorld, &g_aPlayerData[nIdy].aModel[g_aPlayerData[nIdy].ColAttack[nCollision].nIdxParent].mtxWorld);
			break;
		}
	}

}
//==============================================================================================================================
// 判定設定（ダメージ判定）
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
			// 位置を反映
			D3DXMatrixTranslation(&g_aPlayerData[nIdy].ColBody[nCollision].mtxWorld, g_aPlayerData[nIdy].ColBody[nCollision].ofset.x, g_aPlayerData[nIdy].ColBody[nCollision].ofset.y, g_aPlayerData[nIdy].ColAttack[nCollision].ofset.z);
			D3DXMatrixMultiply(&g_aPlayerData[nIdy].ColBody[nCollision].mtxWorld, &g_aPlayerData[nIdy].ColBody[nCollision].mtxWorld, &g_aPlayerData[nIdy].aModel[g_aPlayerData[nIdy].ColBody[nCollision].nIdxParent].mtxWorld);
			break;
		}
	}

}
//==============================================================================================================================
// プレイヤーの操作
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
		{// 前移動
			if (GetKeyboardPress(DIK_D) )
			{// 右斜め前移動
				g_aPlayer[nIdy].CtrlMove.x = sinf(D3DX_PI / 4 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].CtrlMove.z = cosf(D3DX_PI / 4 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].Destrot.y = -D3DX_PI / 4 * 3 + pCamera->rot.y;	// 目的の角度
			}
			else if (GetKeyboardPress(DIK_A) )
			{// 左斜め前移動
				g_aPlayer[nIdy].CtrlMove.x = sinf(-D3DX_PI / 4 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].CtrlMove.z = cosf(-D3DX_PI / 4 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].Destrot.y = D3DX_PI / 4 * 3 + pCamera->rot.y;	// 目的の角度
			}
			else
			{// 前移動
				g_aPlayer[nIdy].CtrlMove.x = sinf(0.0f + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].CtrlMove.z = cosf(0.0f + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].Destrot.y = D3DX_PI + pCamera->rot.y;		// 目的の角度
			}
		}
		else if (GetKeyboardPress(DIK_S) )
		{// 後ろ移動
			if (GetKeyboardPress(DIK_D) )
			{// 右斜め後ろ移動
				g_aPlayer[nIdy].CtrlMove.x = sinf(D3DX_PI / 4 * 3 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].CtrlMove.z = cosf(D3DX_PI / 4 * 3 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].Destrot.y = -D3DX_PI / 4 + pCamera->rot.y;	// 目的の角度
			}
			else if (GetKeyboardPress(DIK_A) )
			{// 左斜め後ろ移動
				g_aPlayer[nIdy].CtrlMove.x = sinf(-D3DX_PI / 4 * 3 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].CtrlMove.z = cosf(-D3DX_PI / 4 * 3 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].Destrot.y = D3DX_PI / 4 + pCamera->rot.y;	// 目的の角度
			}
			else
			{// 後ろ移動
				g_aPlayer[nIdy].CtrlMove.x = sinf(D3DX_PI + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].CtrlMove.z = cosf(D3DX_PI + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
				g_aPlayer[nIdy].Destrot.y = 0.0f + pCamera->rot.y;		// 目的の角度
			}
		}
		else if (GetKeyboardPress(DIK_D) )
		{// 右移動
			g_aPlayer[nIdy].CtrlMove.x = sinf(D3DX_PI / 2 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
			g_aPlayer[nIdy].CtrlMove.z = cosf(D3DX_PI / 2 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
			g_aPlayer[nIdy].Destrot.y = -D3DX_PI / 2 + pCamera->rot.y;	// 目的の角度
		}
		else if (GetKeyboardPress(DIK_A) )
		{// 左移動
			g_aPlayer[nIdy].CtrlMove.x = sinf(-D3DX_PI / 2 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
			g_aPlayer[nIdy].CtrlMove.z = cosf(-D3DX_PI / 2 + pCamera->rot.y)*g_aPlayer[nIdy].MoveSpeed;
			g_aPlayer[nIdy].Destrot.y = D3DX_PI / 2 + pCamera->rot.y;	// 目的の角度
		}

		if (g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_NEUTRAL ||
			g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_MOVE ||
			g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_JUMP)
		{// 特定のモーションだげ移動量加算
			if (g_aPlayer[nIdy].bJump)
			{// ジャンプ中なら移動量半減
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
		{// 吹っ飛びしていなければ
			if (GetKeyboardTrigger(DIK_K))
			{// 弱
				if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK])
				{// 弱してなければ
					g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK] = true;
				}
				else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] &&
					g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK])
				{// 弱2
					if (MATURI)
					{// 人
						if (g_aPlayer[nIdy].nFrameAllCounter >= 15) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
					}
					if (AMANO)
					{// 天狗
						if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
					}
					if (GOJOU)
					{// 河童
						if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
					}
					if (MOMIJI)
					{// 狐
						if (g_aPlayer[nIdy].nKeyCounter >= 3) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
					}
					if (DONROID)
					{// ロボット
						if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
					}
				}
				else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] &&
					g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2])
				{// 弱3
					if (MATURI)
					{// 人
						if (g_aPlayer[nIdy].nFrameAllCounter >= 10) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
					}
					if (AMANO)
					{// 天狗
						if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
					}
					if (GOJOU)
					{// 河童
						if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
					}
					if (MOMIJI)
					{// 狐
						if (g_aPlayer[nIdy].nKeyCounter >= 3) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
					}
					if (DONROID)
					{// ロボット
						if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
					}
				}
				else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] &&
					g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3])
				{// 弱4
					if (MATURI)
					{// 人
						if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
					}
					if (AMANO)
					{// 天狗
						if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
					}
					if (GOJOU)
					{// 河童
						if (g_aPlayer[nIdy].nKeyCounter >= 4){g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true;}
					}
					if (MOMIJI)
					{// 狐
						if (g_aPlayer[nIdy].nKeyCounter >= 5) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
					}
					if (DONROID)
					{// ロボット
						if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
					}
				}
				else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] &&
					g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4])
				{// 弱5
					if (MATURI)
					{// 人
						if (g_aPlayer[nIdy].nFrameAllCounter >= 25) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
					}
					if (AMANO)
					{// 天狗
						if (g_aPlayer[nIdy].nFrameAllCounter >= 50) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
					}
					if (GOJOU)
					{// 河童
						if (g_aPlayer[nIdy].nFrameAllCounter >= 35) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
					}
					if (MOMIJI)
					{// 狐
						if (g_aPlayer[nIdy].nKeyCounter >= 4){g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true;}
					}
					if (DONROID)
					{// ロボット
						if (g_aPlayer[nIdy].nFrameAllCounter >= 35) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
					}
				}

			}

			if (GetKeyboardTrigger(DIK_J))
			{// つかみ
				if (g_aPlayer[nIdy].bCatch)
				{
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_THROW ]= true;	// 投げ

				}
				else
				{
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CATCH] = true;	// つかみ
				}
			}
		}

		if (!g_aPlayer[nIdy].bJump &&
			!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] &&
			!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_DAMAGE] &&
			!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] &&
			!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP]&&
			!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_SPECIAL])
		{// ジャンプ&吹っ飛びしていなければ
			if (GetKeyboardTrigger(DIK_E))
			{
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_WIN] = true;
				g_aPlayer[nIdy].nCntEmote = 60;
			}

			if (GetKeyboardTrigger(DIK_SPACE)&&!bAttackOn(nIdy))
			{// ジャンプ
				PlaySound(SOUND_LABEL_JUMP);
				g_aPlayer[nIdy].move.y = g_aPlayer[nIdy].JumpSpeed;	// 移動量加算
				g_aPlayer[nIdy].bJump = true;
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] = true;
			}
			if (GetKeyboardTrigger(DIK_B))
			{// 必殺技
				if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_SPECIAL] && g_aPlayer[nIdy].nSp > 0 && !bAttackOn(nIdy))
				{// 必殺技
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
							SetSpecialUse(true);		//必殺技をしている状態にする
							g_nSpecialPlayer = nIdy;	//Idの保存
							g_bStartCutIn = true;		//カットインをやっている状態にする
						}
					}
				}
			}
			if (GetKeyboardPress(DIK_G))
			{// ガード
				if (!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CRASH] && g_aPlayer[nIdy].fGuardLife > 0&&!bAttackOn(nIdy))
				{
					SetGuard(nIdy, D3DXVECTOR3(g_aPlayer[nIdy].aModel[0].mtxWorld._41, g_aPlayer[nIdy].aModel[0].mtxWorld._42, g_aPlayer[nIdy].aModel[0].mtxWorld._43), g_aPlayer[nIdy].fGuardLife);

					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD] = true;
				}
			}
			else
			{// ガードキャンセル
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD] = false;
				UnSetGuard(nIdy, g_aPlayer[nIdy].fGuardLife);
			}
		}
		else
		{// ガードキャンセル
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
				g_aPlayer[nIdy].Destrot.y = fGamePagStickAngle + pCamera->rot.y;	// 目的の角度
			}
			if (g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_NEUTRAL ||
				g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_MOVE ||
				g_aPlayer[nIdy].nMotionType == PLAYER_MOTION_TYPE_JUMP)
			{// 特定のモーションだげ移動量加算
				if (g_aPlayer[nIdy].bJump)
				{// ジャンプ中なら移動量半減
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
			{// 吹っ飛びしていなければ
				if (GetGamePadTrigger(nIdy, BUTTON_B))
				{// 弱
					if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK])
					{// 弱してなければ
						g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK] = true;
					}
					else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] &&
						g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK])
					{// 弱2
						if (MATURI)
						{// 人
							if (g_aPlayer[nIdy].nFrameAllCounter >= 15) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
						}
						if (AMANO)
						{// 天狗
							if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
						}
						if (GOJOU)
						{// 河童
							if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
						}
						if (MOMIJI)
						{// 狐
							if (g_aPlayer[nIdy].nKeyCounter >= 3) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
						}
						if (DONROID)
						{// ロボット
							if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2] = true; }
						}
					}
					else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] &&
						g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_2])
					{// 弱3
						if (MATURI)
						{// 人
							if (g_aPlayer[nIdy].nFrameAllCounter >= 10) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
						}
						if (AMANO)
						{// 天狗
							if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
						}
						if (GOJOU)
						{// 河童
							if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
						}
						if (MOMIJI)
						{// 狐
							if (g_aPlayer[nIdy].nKeyCounter >= 3) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
						}
						if (DONROID)
						{// ロボット
							if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3] = true; }
						}
					}
					else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] &&
						g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_3])
					{// 弱4
						if (MATURI)
						{// 人
							if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
						}
						if (AMANO)
						{// 天狗
							if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
						}
						if (GOJOU)
						{// 河童
							if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
						}
						if (MOMIJI)
						{// 狐
							if (g_aPlayer[nIdy].nKeyCounter >= 5) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
						}
						if (DONROID)
						{// ロボット
							if (g_aPlayer[nIdy].nFrameAllCounter >= 30) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4] = true; }
						}
					}
					else if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] &&
						g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_4])
					{// 弱5
						if (MATURI)
						{// 人
							if (g_aPlayer[nIdy].nFrameAllCounter >= 25) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
						}

						if (AMANO)
						{// 天狗
							if (g_aPlayer[nIdy].nFrameAllCounter >= 50) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
						}
						if (GOJOU)
						{// 河童
							if (g_aPlayer[nIdy].nFrameAllCounter >= 35) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
						}
						if (MOMIJI)
						{// 狐
							if (g_aPlayer[nIdy].nKeyCounter >= 4) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
						}
						if (DONROID)
						{// ロボット
							if (g_aPlayer[nIdy].nFrameAllCounter >= 35) { g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_WEAK_5] = true; }
						}
					}

				}

				if (GetGamePadTrigger(nIdy, BUTTON_R1))
				{// つかみ
					if (g_aPlayer[nIdy].bCatch)
					{
						g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_THROW] = true;	// 投げ

					}
					else
					{
						g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CATCH] = true;	// つかみ

					}
				}

			}
			if (!g_aPlayer[nIdy].bJump &&
				!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] &&
				!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_DAMAGE] &&
				!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_FLY] &&
				!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GETUP]&&
				!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_SPECIAL])

			{// ジャンプ&吹っ飛びしていなければ
				if (GetPovTtigger(nIdy, POV_DOWN) || GetPovTtigger(nIdy, POV_UP) || GetPovTtigger(nIdy, POV_RIGHT) || GetPovTtigger(nIdy, POV_LEFT))
				{
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_WIN] = true;
					g_aPlayer[nIdy].nCntEmote = 60;
				}

				if (GetGamePadTrigger(nIdy, BUTTON_A) && !bAttackOn(nIdy))
				{// ジャンプ
					PlaySound(SOUND_LABEL_JUMP);
					g_aPlayer[nIdy].move.y = g_aPlayer[nIdy].JumpSpeed;	// 移動量加算
					g_aPlayer[nIdy].bJump = true;
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_JUMP] = true;
				}
				if (GetGamePadTrigger(nIdy, BUTTON_X))
				{// 必殺技
					if (!g_aPlayer[nIdy].bAttackType[PLAYER_ATTACK_TYPE_SPECIAL] && g_aPlayer[nIdy].nSp > 0 && !bAttackOn(nIdy))
					{// 必殺技
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
								SetSpecialUse(true);		//必殺技をしている状態にする
								g_nSpecialPlayer = nIdy;	//Idの保存
								g_bStartCutIn = true;		//カットインをやっている状態にする
							}
						}
					}
				}
				if (GetGamePadPress(nIdy, BUTTON_L1))
				{// ガード
					if (!g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_CRASH] && g_aPlayer[nIdy].fGuardLife > 0 && !bAttackOn(nIdy))
					{
						SetGuard(nIdy, D3DXVECTOR3(g_aPlayer[nIdy].aModel[0].mtxWorld._41, g_aPlayer[nIdy].aModel[0].mtxWorld._42, g_aPlayer[nIdy].aModel[0].mtxWorld._43), g_aPlayer[nIdy].fGuardLife);
						g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD] = true;
					}
				}
				else
				{// ガードキャンセル
					g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD] = false;
					UnSetGuard(nIdy, g_aPlayer[nIdy].fGuardLife);
				}
			}
			else
			{// ガードキャンセル
				g_aPlayer[nIdy].bMotionState[PLAYER_BOOL_GUARD] = false;
				UnSetGuard(nIdy, g_aPlayer[nIdy].fGuardLife);
			}
		}
#endif
	}
}
//==============================================================================================================================
// プレイヤー同士の衝突の判定
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
					// 敵と当たるものの距離
					float fPosX = (g_aPlayer[nIdy].pos.x - g_aPlayer[nCnt].pos.x);
					float fPosY = (g_aPlayer[nIdy].pos.y - g_aPlayer[nCnt].pos.y);
					float fPosZ = (g_aPlayer[nIdy].pos.z - g_aPlayer[nCnt].pos.z);
					float fRadiusA = fPosX*fPosX + fPosY*fPosY + fPosZ*fPosZ;
					float fRadiusB = 0;

					fRadiusB = (g_aPlayer[nIdy].fRadiusWidth + g_aPlayer[nIdy].fRadiusWidth)* (g_aPlayer[nCnt].fRadiusWidth + g_aPlayer[nCnt].fRadiusWidth);

					if (fRadiusB > fRadiusA&&
						-fRadiusB < fRadiusA)
					{// 人と人のあたり判定
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
// プレイヤーのタイプ設定
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
		g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_NEUTRAL;	// モーションタイプ
		g_aPlayer[nIdy].nMotionTypeOld = PLAYER_MOTION_TYPE_MAX;	// 前回のモーションタイプ
		g_aPlayer[nIdy].nMotionGetCol = PLAYER_MOTION_TYPE_NEUTRAL;	// モーションタイプ
		g_aPlayer[nIdy].nMotionGetColOld = PLAYER_MOTION_TYPE_MAX;	// 前回のモーションタイプ
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
		{// ダメージ設定
			g_aPlayer[nIdy].ColBody[nCollision].nIdxParent = g_aPlayerData[g_aPlayer[nIdy].type].ColBody[nCollision].nIdxParent;
			g_aPlayer[nIdy].ColBody[nCollision].ofset = g_aPlayerData[g_aPlayer[nIdy].type].ColBody[nCollision].ofset;
			g_aPlayer[nIdy].ColBody[nCollision].fRadius = g_aPlayerData[g_aPlayer[nIdy].type].ColBody[nCollision].fRadius;
			g_aPlayer[nIdy].ColBody[nCollision].bUse = g_aPlayerData[g_aPlayer[nIdy].type].ColBody[nCollision].bUse;
			// 位置を反映
			D3DXMatrixTranslation(&g_aPlayer[nIdy].ColBody[nCollision].mtxWorld, g_aPlayer[nIdy].ColBody[nCollision].ofset.x, g_aPlayer[nIdy].ColBody[nCollision].ofset.y, g_aPlayer[nIdy].ColAttack[nCollision].ofset.z);
			D3DXMatrixMultiply(&g_aPlayer[nIdy].ColBody[nCollision].mtxWorld, &g_aPlayer[nIdy].ColBody[nCollision].mtxWorld, &g_aPlayer[nIdy].aModel[g_aPlayer[nIdy].ColBody[nCollision].nIdxParent].mtxWorld);
		}
		for (int nCollision = 0; nCollision < MAX_COLLISION; nCollision++)
		{// 攻撃設定
			g_aPlayer[nIdy].ColAttack[nCollision].nIdxParent = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].nIdxParent;
			g_aPlayer[nIdy].ColAttack[nCollision].ofset = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].ofset;
			g_aPlayer[nIdy].ColAttack[nCollision].fRadius = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].fRadius;
			g_aPlayer[nIdy].ColAttack[nCollision].nCollisionStart = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].nCollisionStart;
			g_aPlayer[nIdy].ColAttack[nCollision].nCollisionEnd = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].nCollisionEnd;
			g_aPlayer[nIdy].ColAttack[nCollision].nStopTime = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].nStopTime;
			g_aPlayer[nIdy].ColAttack[nCollision].nMotionType = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].nMotionType;
			g_aPlayer[nIdy].ColAttack[nCollision].bUse = g_aPlayerData[g_aPlayer[nIdy].type].ColAttack[nCollision].bUse;
			// 位置を反映
			D3DXMatrixTranslation(&g_aPlayer[nIdy].ColAttack[nCollision].mtxWorld, g_aPlayer[nIdy].ColAttack[nCollision].ofset.x, g_aPlayer[nIdy].ColAttack[nCollision].ofset.y, g_aPlayer[nIdy].ColAttack[nCollision].ofset.z);
			D3DXMatrixMultiply(&g_aPlayer[nIdy].ColAttack[nCollision].mtxWorld, &g_aPlayer[nIdy].ColAttack[nCollision].mtxWorld, &g_aPlayer[nIdy].aModel[g_aPlayer[nIdy].ColAttack[nCollision].nIdxParent].mtxWorld);

		}
		for (int nIdyModel = 0; nIdyModel < g_aPlayerData[g_aPlayer[nIdy].type].nNumParts; nIdyModel++)
		{// モデル初期位置設定
			g_aPlayer[nIdy].aModel[nIdyModel].pos = g_aPlayerData[g_aPlayer[nIdy].type].aModel[nIdyModel].pos;
			g_aPlayer[nIdy].aModel[nIdyModel].Initpos = g_aPlayerData[g_aPlayer[nIdy].type].aModel[nIdyModel].pos;
			g_aPlayer[nIdy].aModel[nIdyModel].rot = g_aPlayerData[g_aPlayer[nIdy].type].aModel[nIdyModel].rot;
			g_aPlayer[nIdy].aModel[nIdyModel].rot = g_aPlayerData[g_aPlayer[nIdy].type].aMotion[g_aPlayer[nIdy].nMotionType].aKey[0].aPartsKey[nIdyModel].rot;
		}
		for (int nIdyMotion = 0; nIdyMotion < PLAYER_MOTION_TYPE_MAX; nIdyMotion++)
		{
			for (int nIdyOrbit = 0; nIdyOrbit < MAX_PLAYER_ORBIT; nIdyOrbit++)
			{
				g_aPlayer[nIdy].orbit[nIdyMotion][nIdyOrbit].nIdyOrbit = g_aPlayerData[g_aPlayer[nIdy].type].orbit[nIdyMotion][nIdyOrbit].nIdyOrbit;				// 軌跡の数
				g_aPlayer[nIdy].orbit[nIdyMotion][nIdyOrbit].nOrbitLength = g_aPlayerData[g_aPlayer[nIdy].type].orbit[nIdyMotion][nIdyOrbit].nOrbitLength;		// 軌跡の長さ
				g_aPlayer[nIdy].orbit[nIdyMotion][nIdyOrbit].OrbitStart = g_aPlayerData[g_aPlayer[nIdy].type].orbit[nIdyMotion][nIdyOrbit].OrbitStart;			// 視点
				g_aPlayer[nIdy].orbit[nIdyMotion][nIdyOrbit].OrbitEnd = g_aPlayerData[g_aPlayer[nIdy].type].orbit[nIdyMotion][nIdyOrbit].OrbitEnd;				// 終点
				g_aPlayer[nIdy].orbit[nIdyMotion][nIdyOrbit].nType = g_aPlayerData[g_aPlayer[nIdy].type].orbit[nIdyMotion][nIdyOrbit].nType;					// 軌跡のタイプ
				g_aPlayer[nIdy].orbit[nIdyMotion][nIdyOrbit].motion = g_aPlayerData[g_aPlayer[nIdy].type].orbit[nIdyMotion][nIdyOrbit].motion;	// モーション
			}
		}
		if (GetMode() == MODE_GAME)
		{
			// 影設定
			g_aPlayer[nIdy].nIdyShadow = SetShadow(g_aPlayer[nIdy].pos, g_aPlayer[nIdy].rot, g_aPlayer[nIdy].fRadiusWidth * 2.5f, g_aPlayer[nIdy].fRadiusWidth);
			// ライン判定設定
			g_aPlayer[nIdy].nIdyLine = CollisionLine(g_aPlayer[nIdy].pos, D3DXVECTOR3(-g_aPlayer[nIdy].fRadiusWidth, 0.0f, -g_aPlayer[nIdy].fRadiusWidth), D3DXVECTOR3(g_aPlayer[nIdy].fRadiusWidth, g_aPlayer[nIdy].fRadiusHeight, g_aPlayer[nIdy].fRadiusWidth), LINETYPE_PLAYER);
			// ライフ設定
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
		g_aPlayer[nIdy].nMotionType = PLAYER_MOTION_TYPE_NEUTRAL;	// モーションタイプ
		g_aPlayer[nIdy].nMotionTypeOld = PLAYER_MOTION_TYPE_MAX;	// 前回のモーションタイプ
		g_aPlayer[nIdy].nMotionGetCol = PLAYER_MOTION_TYPE_NEUTRAL;	// モーションタイプ
		g_aPlayer[nIdy].nMotionGetColOld = PLAYER_MOTION_TYPE_MAX;	// 前回のモーションタイプ
		g_aPlayer[nIdy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
		g_aPlayer[nIdy].Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転の差分
		g_aPlayer[nIdy].Destrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 目的の回転
		g_aPlayer[nIdy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 回転
		g_aPlayer[nIdy].Environment = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//環境

		for (int nIdySound = 0; nIdySound < SOUND_LABEL_MAX; nIdySound++)
		{// 音
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
		g_aPlayer[nIdy].bJump = false;							// ジャンプ
		g_aPlayer[nIdy].nFlyCounter = 0;						// 飛んでいる時間
		g_aPlayer[nIdy].fRotSpeed = 0.0f;						// 回転の減速スピード
		g_aPlayer[nIdy].nAirCounter = 0;						// 浮遊時の攻撃制御カウンター
		g_aPlayer[nIdy].nLoopCounter = 0;						// ループカウンター
		g_aPlayer[nIdy].nIdy = nIdy;							// 番号
		g_aPlayer[nIdy].nKeyCounter = 0;		// キー数
		g_aPlayer[nIdy].nFrameCounter = 0;		// フレーム数
		g_aPlayer[nIdy].nFrameAllCounter = 0;	// 最大フレーム
		g_aPlayer[nIdy].nFrame = 0;				// フレーム
		g_aPlayer[nIdy].fGuardLife = MAX_SKY;		// ガードのライフ
		g_aPlayer[nIdy].bUse = false;
		g_aPlayer[nIdy].bDraw = true;			// 映ってるかどうか
		g_aPlayer[nIdy].fPulsLife = 0;			// アイテムで増えるライフ
		g_aPlayer[nIdy].fPulsAttack = 0;		// アイテムで加算される攻撃力
		g_aPlayer[nIdy].fPulsSpeed = 0;			// アイテムで増えるスピード
		g_aPlayer[nIdy].nItemTime = 0;			// アイテム継続時間
		g_aPlayer[nIdy].nSp = MAX_SP;
		g_aPlayer[nIdy].nComboCounter = 0;			// コンボカウンター
		g_aPlayer[nIdy].bCombo = false;				// コンボ
		g_aPlayer[nIdy].typeInfo = PLAYERTYPE_MAX;
		g_aPlayer[nIdy].nCntEmote = 0;				// エモート
		g_aPlayer[nIdy].bSpecial = false;
	}
}
void SetTypePlayer(int nIdy, PLAYERTYPE type)
{
	g_aPlayer[nIdy].typeInfo = type;
}
//==============================================================================================================================
// プレイヤーのエフェクト
//==============================================================================================================================
void PlayerMotionEffect(int nCntPlayer, int nCollision)
{
//	SetEffect(D3DXVECTOR3(g_aPlayer[nCntPlayer].ColAttack[nCollision].mtxWorld._41, g_aPlayer[nCntPlayer].ColAttack[nCollision].mtxWorld._42, g_aPlayer[nCntPlayer].ColAttack[nCollision].mtxWorld._43), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aPlayer[nCntPlayer].ColAttack[nCollision].fRadius, 10,EFFECTTYPE_SMOKE);
}
//==============================================================================================================================
// プレイヤーの判定
//==============================================================================================================================
void PlayerColInfo(int nIdy)
{
	// 攻撃判定処理
	for (int nCnt = 0; nCnt < MAX_COLLISION; nCnt++)
	{
		if (g_aPlayer[nIdy].ColAttack[nCnt].bUse == true)
		{
			if (g_aPlayer[nIdy].ColAttack[nCnt].nMotionType == g_aPlayer[nIdy].nMotionType)
			{// 決めたステートと今のステートが一緒だったら判定開始
				if (g_aPlayer[nIdy].nFrameAllCounter >= g_aPlayer[nIdy].ColAttack[nCnt].nCollisionStart &&
					g_aPlayer[nIdy].nFrameAllCounter <= g_aPlayer[nIdy].ColAttack[nCnt].nCollisionEnd)
				{
					if (CollisionModelMinMax(&D3DXVECTOR3(g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._41, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._42, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._43),
						&D3DXVECTOR3(g_aPlayer[nIdy].aModel[0].mtxWorld._41, g_aPlayer[nIdy].aModel[0].mtxWorld._42, g_aPlayer[nIdy].aModel[0].mtxWorld._43), &D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						g_aPlayer[nIdy].ColAttack[nCnt].fRadius, g_aPlayer[nIdy].ColAttack[nCnt].fRadius, &g_aPlayer[nIdy].pModel) != 0)
					{
					}
					PlayerMotionEffect(nIdy, nCnt);
					// 攻撃当たり判定
					if (g_aPlayer[nIdy].nMotionType != PLAYER_MOTION_TYPE_CATCH)
					{// キャッチは判定しない
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
						{// 太鼓音
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
						}
						if (g_aPlayer[nIdy].pModelAtkData->nType == MODELTYPE_CHOKO&&g_aPlayer[nIdy].nMotionType != PLAYER_MOTION_TYPE_CATCH)
						{// チョコバナナ
							PlaySound(SOUND_LABEL_HIT000);
							HitEffect(D3DXVECTOR3(g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._41, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._42, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._43));
							if ((rand()+1) % 100 == 0)
							{
								PlaySound(SOUND_SUNDER);
								SetEventColor(D3DXCOLOR(2.0f, 2.0f, 2.0f, 1.0f));

								for (int nCntR = 0; nCntR < 3; nCntR++)
								{
									for (int nCnt = 0; nCnt < 10; nCnt++)
									{// 雷
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
						{// キャッチできるかどうか
							int nIdyModel = 0;
							if (g_aPlayer[nIdy].pModelAtkData->nType == MODELTYPE_TAKOYAKI)
							{// タコ焼きなら
								if (GetTakoyaki())
								{// ゲット可能なら
									nIdyModel = SetModel(D3DXVECTOR3(g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._41, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._42, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._43), D3DXVECTOR3(0, 0, 0), MODELTYPE_TAKOYAKI_BALL);
									g_aPlayer[nIdy].pModelAtk = &pModel[nIdyModel];
									g_aPlayer[nIdy].pModelAtk->nIdy = nIdy;
									g_aPlayer[nIdy].pModelAtk->bCatch = true;
									g_aPlayer[nIdy].bCatch = true;
									SetTakoyaki(false);
								}
							}
							if (g_aPlayer[nIdy].pModelAtkData->nType == MODELTYPE_KINGYO)
							{// 金魚なら
								if (GetFish())
								{// ゲット可能なら
									nIdyModel = SetModel(D3DXVECTOR3(g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._41, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._42, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._43), D3DXVECTOR3(0, 0, 0), MODELTYPE_FISH);
									g_aPlayer[nIdy].pModelAtk = &pModel[nIdyModel];
									g_aPlayer[nIdy].pModelAtk->nIdy = nIdy;
									g_aPlayer[nIdy].pModelAtk->bCatch = true;
									g_aPlayer[nIdy].bCatch = true;
									SetFish(false);
								}
							}
							else if (g_aPlayer[nIdy].pModelAtkData->nType == MODELTYPE_CHOKO)
							{// チョコバナナなら
								if (GetChoco())
								{// ゲット可能なら
									g_aPlayer[nIdy].nItemTime = 6 * 60;
									int nCnt = rand() % 3;
									switch (nCnt)
									{
									case 0: // ライフ
										g_aPlayer[nIdy].fPulsLife = 3;
										PlaySound(SOUND_LIFE);
										SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(GetCamera()->rot.y - D3DX_PI) * 50, 50.0f, cosf(GetCamera()->rot.y - D3DX_PI) * 50), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 0, EFFECTTYPE_LIFE_UP);
										break;
									case 1:// アタック
										g_aPlayer[nIdy].fPulsAttack = 1;
										PlaySound(SOUND_ATTACK);
										SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(GetCamera()->rot.y - D3DX_PI) * 50 + float(nCnt), 50.0f, cosf(GetCamera()->rot.y - D3DX_PI) * 50), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 0, EFFECTTYPE_POW_UP);
										break;
									case 2:// スピード
										g_aPlayer[nIdy].fPulsSpeed = 1;
										PlaySound(SOUND_SPEED);
										SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(GetCamera()->rot.y - D3DX_PI) * 50 + float(nCnt), 50.0f, cosf(GetCamera()->rot.y - D3DX_PI) * 50), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 0, EFFECTTYPE_SPEED_UP);
										break;
									}
									g_aPlayer[nIdy].fLife += g_aPlayer[nIdy].fPulsLife;
									g_aPlayer[nIdy].MoveSpeed += g_aPlayer[nIdy].fPulsSpeed;
									if (g_aPlayer[nIdy].fLife >= float(g_aPlayerData[g_aPlayer[nIdy].type].nInitLife))
									{// 最大ライフ超えない
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
					{// キャッチならアイテムを取る
						float fLife = 0;
						g_aPlayer[nIdy].fPulsLife = 0;
						float fAttack = g_aPlayer[nIdy].fPulsAttack;
						float fSpeed = g_aPlayer[nIdy].fPulsSpeed;
						if (CollsionItem(D3DXVECTOR3(g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._41, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._42, g_aPlayer[nIdy].ColAttack[nCnt].mtxWorld._43)
							, g_aPlayer[nIdy].ColAttack[nCnt].fRadius, g_aPlayer[nIdy].ColAttack[nCnt].fRadius,
							&g_aPlayer[nIdy].fPulsLife, &g_aPlayer[nIdy].fPulsAttack, &g_aPlayer[nIdy].fPulsSpeed))
						{//アイテム
							g_aPlayer[nIdy].nItemTime = 5*60;
							int nCnt = 0;
							if (fLife != g_aPlayer[nIdy].fPulsLife)
							{// ライフ増加
								PlaySound(SOUND_LIFE);
								SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(GetCamera()->rot.y - D3DX_PI) * 50, 50.0f, cosf(GetCamera()->rot.y - D3DX_PI) * 50),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
									50, 0, EFFECTTYPE_LIFE_UP);
								nCnt += 30;
							}
							if (fAttack != g_aPlayer[nIdy].fPulsAttack)
							{// 攻撃増加
								PlaySound(SOUND_ATTACK);
								SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(GetCamera()->rot.y - D3DX_PI) * 50+ float(nCnt), 50.0f, cosf(GetCamera()->rot.y - D3DX_PI) * 50),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
									50, 0, EFFECTTYPE_POW_UP);
								nCnt += 30;
							}
							if (fSpeed != g_aPlayer[nIdy].fPulsSpeed)
							{// スピード増加
								PlaySound(SOUND_SPEED);
								SetEffect(g_aPlayer[nIdy].pos + D3DXVECTOR3(sinf(GetCamera()->rot.y - D3DX_PI) * 50 + float(nCnt), 50.0f, cosf(GetCamera()->rot.y - D3DX_PI) * 50),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
									50, 0, EFFECTTYPE_SPEED_UP);
							}
							g_aPlayer[nIdy].fLife += g_aPlayer[nIdy].fPulsLife;
							g_aPlayer[nIdy].MoveSpeed += g_aPlayer[nIdy].fPulsSpeed;
							if (g_aPlayer[nIdy].fLife >= float(g_aPlayerData[g_aPlayer[nIdy].type].nInitLife))
							{// 最大ライフ超えない
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
	{// 攻撃の種類分ループ
		if (g_aPlayer[nIdy].bAttackType[nCntAttack])
		{// 攻撃中だったら
			g_aPlayer[nIdy].bAttackType[nCntAttack] = false;								// 攻撃状態を解除
		}
	}
}
bool bAttackOn(int nIdy)
{
	bool On = false;
	for (int nCntAttack = 0; nCntAttack < PLAYER_ATTACK_TYPE_MAX; nCntAttack++)
	{// 攻撃の種類分ループ
		if (g_aPlayer[nIdy].bAttackType[nCntAttack])
		{// 攻撃中だったら
			On = true; //攻撃中
		}
	}
	return On;
}
//=====================================================================================================================
//　必殺技の使用判定
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
		//時間の取得
		g_nCutInTime = GetTimeGame();

		if (g_bCutIn == false)
		{
			nType = g_aPlayer[g_nSpecialPlayer].type;
			SetCut(1, D3DXVECTOR3(1920.0f, 360.0f, 0.0f), (CHARATAYPE)nType, CUTTYPE_KYARACTOR);
			SetSpecalUse(true);		//ゲームのカットイン使用状態にする（Updateを止める）
			g_bCutIn = true;
		}

		if ((g_nCutInTime % CUT_IN_TIME) == 0)
		{
			if (g_bStartMove == false)
			{
				g_aPlayer[g_nSpecialPlayer].bSpecial = false;
				g_bCutIn = false;

				//ポリゴンを消す
				DeleteAllCut();

				//カットイン使用していない状態にする（Updateを再開）
				SetSpecalUse(false);

				//一体だけ動かした状態にする
				g_bStartMove = true;
			}
		}
	}

	//一体だけ動き始めたら
	if (g_bStartMove == true)
	{
		StartMove();
	}
}

//=====================================================================================================================
//　キャラクターを動かし始める
//=====================================================================================================================
void StartMove(void)
{
	switch (g_aPlayer[g_nSpecialPlayer].type)
	{
	case PLAYERTYPE_MATURI:
		if (g_aPlayer[g_nSpecialPlayer].nFrameAllCounter == FLAM_MATURI)
		{//使用状態の設定
			SetSpecialUse(false);
			g_bStartMove = false;	//初期化する
			g_bStartCutIn = false;	//カットインを終了させる
		}
		break;

	case PLAYERTYPE_AMANO:
		if (g_aPlayer[g_nSpecialPlayer].nFrameAllCounter == FLAM_AMANO)
		{//使用状態の設定
			SetSpecialUse(false);
			g_bStartMove = false;	//初期化する
			g_bStartCutIn = false;	//カットインを終了させる
		}
		break;

	case PLAYERTYPE_GOJOU:
		if (g_aPlayer[g_nSpecialPlayer].nFrameAllCounter == FLAM_GOJOU)
		{//使用状態の設定
			SetSpecialUse(false);
			g_bStartMove = false;	//初期化する
			g_bStartCutIn = false;	//カットインを終了させる
		}
		break;

	case PLAYERTYPE_MOMIJI:
		if (g_aPlayer[g_nSpecialPlayer].nFrameAllCounter == FLAM_MOMIJI)
		{//使用状態の設定
			SetSpecialUse(false);
			g_bStartMove = false;	//初期化する
			g_bStartCutIn = false;	//カットインを終了させる
		}
		break;

	case PLAYERTYPE_DONROID:
		if (g_aPlayer[g_nSpecialPlayer].nFrameAllCounter == FLAM_DONROID)
		{//使用状態の設定
			SetSpecialUse(false);
			g_bStartMove = false;	//初期化する
			g_bStartCutIn = false;	//カットインを終了させる
		}
		break;
	}
}

//=====================================================================================================================
//　使用状態の設定
//=====================================================================================================================
void SetSpecialUse(bool bSpecial)
{
	for (int nCntCut = 0; nCntCut < MAX_PLAYER; nCntCut++)
	{
		g_aPlayer[nCntCut].bSpecial = bSpecial;
	}
}
//=====================================================================================================================
// ライフゼロ
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

	// 水平方向の吹っ飛び力を代入
	g_aPlayer[nCnt].fFlyPower.x = sinf(fAngle - D3DX_PI) * fDamageH;
	g_aPlayer[nCnt].fFlyPower.z = cosf(fAngle - D3DX_PI) * fDamageH;

	// 垂直方向の吹っ飛び力を代入
	g_aPlayer[nCnt].fFlyPower.y = fDamageV;
	g_aPlayer[nCnt].nFlyCounter = 20;
	g_aPlayer[nCnt].bMotionState[PLAYER_BOOL_FLY] = true;													// 吹っ飛び中に設定
	g_aPlayer[nCnt].Destrot.y = fAngle - D3DX_PI;							// キャラクターの向きを変更
	g_aPlayer[nCnt].rot.y = fAngle - D3DX_PI;							// キャラクターの向きを変更

}
//=========================================================================================================================
// ボイス
//===========================================================================================================================
void SetPlayerVoice(PLAYERTYPE type, PlayerMotionType motion)
{
	if (motion == PLAYER_MOTION_TYPE_DAMAGE)
	{
		switch (type)
		{
		case PLAYERTYPE_MATURI:// まつり（女の子）
			PlaySound(SOUND_HUMAN_DAMEJI);
			break;
		case PLAYERTYPE_AMANO:// あまの（天狗）
			PlaySound(SOUND_TENGU_DAMEJI);
			break;
		case PLAYERTYPE_GOJOU:// 悟浄（河童）
			PlaySound(SOUND_LABEL( SOUND_KAPA_DAMEJI000 + rand()%3));
			break;
		case PLAYERTYPE_MOMIJI:// 紅葉（きつね）
			PlaySound(SOUND_FOX_DAMEJI);
			break;
		case PLAYERTYPE_DONROID:// ドンロイド（ロボット）
			PlaySound(SOUND_ROBOT_DAMEJI);
			break;
		}
	}
	if (motion == PLAYER_MOTION_TYPE_FLY)
	{
		switch (type)
		{
		case PLAYERTYPE_MATURI:// まつり（女の子）
			PlaySound(SOUND_HUMAN_BUTOBI);
			break;
		case PLAYERTYPE_AMANO:// あまの（天狗）
			PlaySound(SOUND_TENGU_BUTOBI);
			break;
		case PLAYERTYPE_GOJOU:// 悟浄（河童）
			PlaySound(SOUND_KAPA_BUTOBI);
			break;
		case PLAYERTYPE_MOMIJI:// 紅葉（きつね）
			PlaySound(SOUND_FOX_BUTOBI);
			break;
		case PLAYERTYPE_DONROID:// ドンロイド（ロボット）
			PlaySound(SOUND_ROBOT_BUTOBI);
			break;
		}
	}
	if (motion == PLAYER_MOTION_TYPE_MAX)
	{
		switch (type)
		{
		case PLAYERTYPE_MATURI:// まつり（女の子）
			PlaySound(SOUND_HUMAN_GARD000);
			break;
		case PLAYERTYPE_AMANO:// あまの（天狗）
			PlaySound(SOUND_TENGU_GARD);
			break;
		case PLAYERTYPE_GOJOU:// 悟浄（河童）
			PlaySound(SOUND_KAPA_GARD);
			break;
		case PLAYERTYPE_MOMIJI:// 紅葉（きつね）
			PlaySound(SOUND_FOX_GARD);
			break;
		case PLAYERTYPE_DONROID:// ドンロイド（ロボット）
			PlaySound(SOUND_ROBOT_GARD);
			break;
		}

	}
	if (motion == PLAYER_MOTION_TYPE_WIN)
	{
		switch (type)
		{
		case PLAYERTYPE_MATURI:// まつり（女の子）
			PlaySound(SOUND_HUMAN_KAIHI);
			break;
		case PLAYERTYPE_AMANO:// あまの（天狗）
			PlaySound(SOUND_TENGU_KAIHI);
			break;
		case PLAYERTYPE_GOJOU:// 悟浄（河童）
			PlaySound(SOUND_KAPA_KAIHI);
			break;
		case PLAYERTYPE_MOMIJI:// 紅葉（きつね）
			PlaySound(SOUND_FOX_KAIHI);
			break;
		case PLAYERTYPE_DONROID:// ドンロイド（ロボット）
			PlaySound(SOUND_ROBOT_KAIHI);
			break;
		}
	}

}
//==============================================================================================================================
//　ライフのチェック
//==============================================================================================================================
int CheckLife(void)
{
	//変数宣言
	int BigLife = 0;

	for (int nCntId = 0; nCntId < MAX_PLAYER - 1; nCntId++)
	{
		if (g_aPlayer[BigLife].fLife > g_aPlayer[nCntId + 1].fLife)
		{
			BigLife = BigLife;		//Idの保存
		}
		else
		{
			BigLife = nCntId + 1;	//Idの保存
		}
	}

	return BigLife;
}