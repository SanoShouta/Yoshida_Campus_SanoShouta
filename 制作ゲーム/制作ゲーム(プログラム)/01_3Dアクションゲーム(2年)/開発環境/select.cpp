//=============================================================================
//
// 選択画面の処理 [select.cpp]
// Author : 佐藤安純　Sato_Asumi
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
// マクロ定義
//=============================================================================
#define MAX_POLYGON		(3)		//ポリゴンの最大数
#define MAX_TEX			(2)		//テクスチャの最大数
#define CHANGE			(30.0f)	//ポリゴンの変化量
#define MOVE			(3.0f)	//変化量
#define OVER_MOVE		(10.0f)	//該当キーを押さなかった時のポリゴンの移動量

//どんちゃんバトルボタン
#define BATTLE_WHIDTH		(520)											//背景の幅
#define BATTLE_HEIGHT		(280)											//背景の高さ
#define BATTLE_POS_X		((SCREEN_WIDTH / 2) - 570)						//背景の左上X座標
#define BATTLE_POS_Y		(150)											//背景の左上Y座標

//？？？ボタン
#define QUESTION_WHIDTH		(250)											//背景の幅
#define QUESTION_HEIGHT		(250)											//背景の高さ
#define QUESTION_POS_X		((QUESTION_WHIDTH / 2) - 20)					//背景の左上X座標
#define QUESTION_POS_Y		(460)											//背景の左上Y座標

//タイトルボタン
#define TITLE_WHIDTH		(250)											//背景の幅
#define TITLE_HEIGHT		(250)											//背景の高さ
#define TITLE_POS_X			((TITLE_WHIDTH / 2) + 350)						//背景の左上X座標
#define TITLE_POS_Y			(460)											//背景の左上Y座標

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureSelect[MAX_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelect = NULL;		//頂点バッファへのポインタ
int g_SelectMode;										//選択されているモード
Select					g_Select[MAX_POLYGON];			//情報設定
int						g_SelectTime;					//時間カウンター
int						g_CommentID;					//コメントポリゴンの取得

//=============================================================================
// 初期化処理
//=============================================================================
void InitSelect(void)
{
	//変数宣言
	int		nCntTex;
	int		nCntSelect;
	char	cTexName[MAX_TEX][48];		//ファイル名を格納する

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数の初期化
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

	g_SelectMode = SELECTSTATE_START;			//選択状態の設定
	g_SelectTime = 0;							//時間カウンター
	g_CommentID = 0;							//コメントポリゴンのID

	//テクスチャファイル名を格納する
	wsprintf(&cTexName[0][0], "data\\TEXTURE\\title_logo.png");		//どんちゃんバトルボタン
	wsprintf(&cTexName[1][0], "data\\TEXTURE\\select00.png");		//タイトル、？？？ボタン

	//テクスチャの読み込み
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			&cTexName[nCntTex][0],
			&g_pTextureSelect[nCntTex]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelect,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

						//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	//コンテニューボタン-----------------------------------------------------------

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(BATTLE_POS_X, BATTLE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BATTLE_POS_X + BATTLE_WHIDTH, BATTLE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BATTLE_POS_X, BATTLE_POS_Y + BATTLE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BATTLE_POS_X + BATTLE_WHIDTH, BATTLE_POS_Y + BATTLE_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//リトライボタン-----------------------------------------------------------

	//頂点座標の設定
	pVtx[4].pos = D3DXVECTOR3(QUESTION_POS_X, QUESTION_POS_Y, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(QUESTION_POS_X + QUESTION_WHIDTH, QUESTION_POS_Y, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(QUESTION_POS_X, QUESTION_POS_Y + QUESTION_HEIGHT, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(QUESTION_POS_X + QUESTION_WHIDTH, QUESTION_POS_Y + QUESTION_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//クイットボタン-----------------------------------------------------------

	//頂点座標の設定
	pVtx[8].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(TITLE_POS_X + TITLE_WHIDTH, TITLE_POS_Y, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y + TITLE_HEIGHT, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(TITLE_POS_X + TITLE_WHIDTH, TITLE_POS_Y + TITLE_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.5f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffSelect->Unlock();

	//フロントポリゴン
	SetFlontPolygon(11, D3DXVECTOR3(640.0f, 360.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, FLONTTYPE_NOMAL);
	SetFlontPolygon(FLONT_TEXTYPE_CHARACTOR, D3DXVECTOR3(1120.0f, 500.0f, 0.0f), 380.0f, 880.0f, FLONTTYPE_CYARACTOR);
	SetFlontPolygon(10, D3DXVECTOR3(640.0f, 360.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, FLONTTYPE_NOMAL);
	g_CommentID = SetFlontPolygon(FLONT_TEXTYPE_HUKIDASHI, D3DXVECTOR3(875.0f, 350.0f, 0.0f), 350.0f, 500.0f, FLONTTYPE_COMMENT);
	SetFlontPolygon(FLONT_TEXTYPE_CHOTIN, D3DXVECTOR3(640.0f, 50.0f, 0.0f), 1340.0f, 140.0f, FLONTTYPE_CHOTIN);
	SetFlontPolygon(FLONT_TEXTYPE_CHOTIN, D3DXVECTOR3(640.0f, 670.0f, 0.0f), 1340.0f, 140.0f, FLONTTYPE_CHOTIN);

	SetTexture(g_CommentID, COMMENTTYPE_BTTLE);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSelect(void)
{
	//変数宣言
	int nCntTex;

	//テクスチャの破棄
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (g_pTextureSelect[nCntTex] != NULL)
		{
			g_pTextureSelect[nCntTex]->Release();
			g_pTextureSelect[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSelect != NULL)
	{
		g_pVtxBuffSelect->Release();
		g_pVtxBuffSelect = NULL;
	}

	//フロントポリゴンの開放
	ReleaseAllFlontPolygon();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSelect(void)
{
	//変数宣言
	int nCntSelect;

	//フェード情報を取得する
	FADE fade;
	fade = GetFade();

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//入力処理
	Input();

	//選択処理
	switch (g_SelectMode)
	{
	case SELECTSTATE_START:

		//ボタンの状態設定
		g_Select[0].state = BOTTUNSTATE_SELECT;
		g_Select[1].state = BOTTUNSTATE_NOMAL;
		g_Select[2].state = BOTTUNSTATE_NOMAL;

		//決定キーが押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_SelectMode = SELECTSTATE_MAX;
			g_Select[0].state = BOTTUNSTATE_MAX;

			if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
			{
				PlaySound(SOUND_DECISION_1);
				//フェードモード設定
				SetFade(MODE_CHARACTER);
			}
		}
		else
		{
			//ゲームパッドの入力処理
			for (int nIdy = 0; nIdy < MAX_GAMEPAD; nIdy++)
			{
				if (GetGamePadPress(nIdy, BUTTON_A) == true || GetGamePadPress(nIdy, BUTTON_B))
				{
					g_SelectMode = SELECTSTATE_MAX;
					g_Select[0].state = BOTTUNSTATE_MAX;

					if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
					{
						PlaySound(SOUND_DECISION_1);
						//フェードモード設定
						SetFade(MODE_CHARACTER);
					}
				}
			}
		}

		//コメントテクスチャの設定
		SetTexture(g_CommentID, COMMENTTYPE_BTTLE);
		break;

	case SELECTSTATE_QUESTION:
		//ボタンの状態設定
		g_Select[0].state = BOTTUNSTATE_NOMAL;
		g_Select[1].state = BOTTUNSTATE_SELECT;
		g_Select[2].state = BOTTUNSTATE_NOMAL;

		//決定キーが押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_SelectMode = SELECTSTATE_MAX;
			g_Select[1].state = BOTTUNSTATE_MAX;

			if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
			{
				PlaySound(SOUND_DECISION_1);
				//フェードモード設定
				SetFade(MODE_STAFF);
			}
		}
		else
		{
			//ゲームパッドの入力処理
			for (int nIdy = 0; nIdy < MAX_GAMEPAD; nIdy++)
			{
				if (GetGamePadPress(nIdy, BUTTON_A) == true || GetGamePadPress(nIdy, BUTTON_B))
				{
					g_SelectMode = SELECTSTATE_MAX;
					g_Select[1].state = BOTTUNSTATE_MAX;

					if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
					{
						PlaySound(SOUND_DECISION_1);
						//フェードモード設定
						SetFade(MODE_STAFF);
					}
				}
			}
		}

		//コメントテクスチャの設定
		SetTexture(g_CommentID, COMMENTTYPE_QUESTION);
		break;

	case SELECTSTATE_TITLE:

		//ボタンの状態設定
		g_Select[0].state = BOTTUNSTATE_NOMAL;
		g_Select[1].state = BOTTUNSTATE_NOMAL;
		g_Select[2].state = BOTTUNSTATE_SELECT;

		//決定キーが押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_SelectMode = SELECTSTATE_MAX;
			g_Select[2].state = BOTTUNSTATE_MAX;

			if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
			{
				PlaySound(SOUND_DECISION_1);
				//フェードモード設定
				SetFade(MODE_TITLE);
			}
		}
		else
		{
			//ゲームパッドの入力処理
			for (int nIdy = 0; nIdy < MAX_GAMEPAD; nIdy++)
			{
				if (GetGamePadPress(nIdy, BUTTON_A) == true|| GetGamePadPress(nIdy, BUTTON_B))
				{
					g_SelectMode = SELECTSTATE_MAX;
					g_Select[2].state = BOTTUNSTATE_MAX;

					if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
					{
						PlaySound(SOUND_DECISION_1);
						//フェードモード設定
						SetFade(MODE_TITLE);
					}
				}
			}
		}

		//コメントテクスチャの設定
		SetTexture(g_CommentID, COMMENTTYPE_TITLE);
		break;
	}

	//頂点バッファをロックし、頂点データへのポインタを取得
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

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x - g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y - g_Select[nCntSelect].fChange, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x + g_Select[nCntSelect].Size.x + g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y - g_Select[nCntSelect].fChange, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x - g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y + g_Select[nCntSelect].Size.y + g_Select[nCntSelect].fChange, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x + g_Select[nCntSelect].Size.x + g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y + g_Select[nCntSelect].Size.y + g_Select[nCntSelect].fChange, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			break;

		case BOTTUNSTATE_SELECT:

			//変化量
			g_Select[nCntSelect].fChange += MOVE;

			if (g_Select[nCntSelect].fChange > CHANGE)
			{
				g_Select[nCntSelect].fChange = CHANGE;
			}

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x - g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y - g_Select[nCntSelect].fChange, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x + g_Select[nCntSelect].Size.x + g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y - g_Select[nCntSelect].fChange, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x - g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y + g_Select[nCntSelect].Size.y + g_Select[nCntSelect].fChange, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Select[nCntSelect].Pos.x + g_Select[nCntSelect].Size.x + g_Select[nCntSelect].fChange, g_Select[nCntSelect].Pos.y + g_Select[nCntSelect].Size.y + g_Select[nCntSelect].fChange, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;

		case BOTTUNSTATE_NONE:
			//頂点カラーの設定
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
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(fSelect, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(fSelect, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(fSelect, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(fSelect, 0.0f, 0.0f, 1.0f);
			break;
		}

		//座標を戻す
		if (g_Select[nCntSelect].Pos.x < g_Select[nCntSelect].PosHold.x)
		{//値を加算する
			g_Select[nCntSelect].Pos.x += 2.0f;

			if (g_Select[nCntSelect].Pos.x > g_Select[nCntSelect].PosHold.x)
			{//値の修正
				g_Select[nCntSelect].Pos.x = g_Select[nCntSelect].PosHold.x;
			}
		}
		if (g_Select[nCntSelect].Pos.x > g_Select[nCntSelect].PosHold.x)
		{//値を加算する
			g_Select[nCntSelect].Pos.x -= 2.0f;

			if (g_Select[nCntSelect].Pos.x < g_Select[nCntSelect].PosHold.x)
			{//値の修正
				g_Select[nCntSelect].Pos.x = g_Select[nCntSelect].PosHold.x;
			}
		}
		if (g_Select[nCntSelect].Pos.y < g_Select[nCntSelect].PosHold.y)
		{//値を加算する
			g_Select[nCntSelect].Pos.y += 2.0f;

			if (g_Select[nCntSelect].Pos.y > g_Select[nCntSelect].PosHold.y)
			{//値の修正
				g_Select[nCntSelect].Pos.y = g_Select[nCntSelect].PosHold.y;
			}
		}
		if (g_Select[nCntSelect].Pos.y > g_Select[nCntSelect].PosHold.y)
		{//値を加算する
			g_Select[nCntSelect].Pos.y -= 2.0f;

			if (g_Select[nCntSelect].Pos.y < g_Select[nCntSelect].PosHold.y)
			{//値の修正
				g_Select[nCntSelect].Pos.y = g_Select[nCntSelect].PosHold.y;
			}
		}


		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSelect->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSelect(void)
{
	//変数宣言
	int nCntSelect;

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

									//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSelect, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntSelect = 0; nCntSelect < MAX_POLYGON; nCntSelect++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureSelect[g_Select[nCntSelect].nTex]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
			nCntSelect * 4,			//開始する頂点のインデックス
			2);						//プリミティブの数
	}
}

//=============================================================================
// 描画処理
//=============================================================================
Select * GetSelect(void)
{
	return &g_Select[0];
}

//=============================================================================
// 状態の設定
//=============================================================================
void SetSelectState(SELECTSTATE state)
{
	g_SelectMode = state;
}

//=============================================================================
// 入力処理
//=============================================================================
void Input(void)
{
	//キーボードの入力処理
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
		{//左にずらす
			g_Select[0].Pos.x -= OVER_MOVE;
		}
		if ((GetKeyboardTrigger(DIK_W) == true))
		{//上にずらす
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
		{//左にずらす
			g_Select[1].Pos.x -= OVER_MOVE;
		}
		if ((GetKeyboardTrigger(DIK_S) == true))
		{//下にずらす
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
		{//右にずらす
			g_Select[2].Pos.x += OVER_MOVE;
		}
		if ((GetKeyboardTrigger(DIK_S) == true))
		{//下にずらす
			g_Select[2].Pos.y += OVER_MOVE;
		}
	}

	//ゲームパッドの入力処理
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
			{//左にずらす
				g_Select[0].Pos.x -= OVER_MOVE;
			}
			else if (GetGamePadStickTrigger(nIdy, ANALOG_STICK_UP) == true)
			{//上にずらす
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
			{//左にずらす
				g_Select[1].Pos.x -= OVER_MOVE;
			}
			else if (GetGamePadStickTrigger(nIdy, ANALOG_STICK_DOWN) == true)
			{//下にずらす
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
			{//右にずらす
				g_Select[2].Pos.x -= OVER_MOVE;
			}
			else if (GetGamePadStickTrigger(nIdy,ANALOG_STICK_DOWN) == true)
			{//下にずらす
				g_Select[2].Pos.y += OVER_MOVE;
			}
		}
	}
}