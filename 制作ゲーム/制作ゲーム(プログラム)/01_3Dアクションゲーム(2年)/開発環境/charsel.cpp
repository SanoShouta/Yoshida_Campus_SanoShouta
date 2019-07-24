//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// キャラクターセレクト処理 [charsel.cpp]
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
// 構造体定義
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
// プロトタイプ宣言
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
VERTEX_2D				g_aVertexCharsel[MAX_CHARSELTOP];
LPDIRECT3DTEXTURE9		g_pTextureCharsel[CHARSELTYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCharsel = NULL;
Charsel					g_aCharsel[CHARSELTYPE_MAX];
bool					g_bReady;							// 戦闘準備が完了したかどうか

CharselTexture g_aCharselTexInfo[CHARSELTYPE_MAX] =
{
	{ "data/TEXTURE/CharactorSelectBG.jpg", D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, 0.0f), SCREEN_WIDTH, SCREEN_WIDTH, CHARSELTYPE_BG },	// 背景
	{ "data/TEXTURE/Chotin000.png", D3DXVECTOR3(SCREEN_WIDTH / 2,50.0f, 0.0f), SCREEN_WIDTH, CHOTIN_HEIGHT, CHARSELTYPE_CHOUTINUP },					// 提灯（上）
	{ "data/TEXTURE/Chotin000.png", D3DXVECTOR3(SCREEN_WIDTH / 2, 660.0f, 0.0f), SCREEN_WIDTH, CHOTIN_HEIGHT, CHARSELTYPE_CHOUTINDOWN },					// 提灯（下）
	{ "data/TEXTURE/CharactorBG000.jpg", D3DXVECTOR3(180.0f, 180.0f, 0.0f), PICKUP_WIDTH, PICKUP_HEIGHT, CHARSELTYPE_PLAYER1 },						// プレイヤー1の背景
	{ "data/TEXTURE/CharactorBG001.jpg", D3DXVECTOR3(1100.0f, 180.0f, 0.0f), PICKUP_WIDTH, PICKUP_HEIGHT, CHARSELTYPE_PLAYER2 },						// プレイヤー2の背景
	{ "data/TEXTURE/CharactorBG002.jpg", D3DXVECTOR3(180.0f, 540.0f, 0.0f), PICKUP_WIDTH, PICKUP_HEIGHT, CHARSELTYPE_PLAYER3 },						// プレイヤー3の背景
	{ "data/TEXTURE/CharactorBG003.jpg", D3DXVECTOR3(1100.0f, 540.0f, 0.0f), PICKUP_WIDTH, PICKUP_HEIGHT, CHARSELTYPE_PLAYER4 },						// プレイヤー4の背景
	{ "data/TEXTURE/CharactorIcon000.png", D3DXVECTOR3(570.0f, 160.0f, 0.0f), CHARWINDOW_WIDTH, CHARWINDOW_HEIGHT, CHARSELTYPE_MATURI },			// まつり（女の子）
	{ "data/TEXTURE/CharactorIcon001.png", D3DXVECTOR3(710.0f, 160.0f, 0.0f), CHARWINDOW_WIDTH, CHARWINDOW_HEIGHT, CHARSELTYPE_AMANO },				// あまの（天狗）
	{ "data/TEXTURE/CharactorIcon002.png", D3DXVECTOR3(570.0f, 300.0f, 0.0f), CHARWINDOW_WIDTH, CHARWINDOW_HEIGHT, CHARSELTYPE_GOJOU },				// 悟浄（河童）
	{ "data/TEXTURE/CharactorIcon003.png", D3DXVECTOR3(710.0f, 300.0f, 0.0f), CHARWINDOW_WIDTH, CHARWINDOW_HEIGHT, CHARSELTYPE_MOMIJI },			// 紅葉（きつね）
	{ "data/TEXTURE/CharactorIcon004.png", D3DXVECTOR3(570.0f, 440.0f, 0.0f), CHARWINDOW_WIDTH, CHARWINDOW_HEIGHT, CHARSELTYPE_DONROID },			// ドンロイド（ロボット）
	{ "data/TEXTURE/CharactorIcon005.png", D3DXVECTOR3(710.0f, 440.0f, 0.0f), CHARWINDOW_WIDTH, CHARWINDOW_HEIGHT, CHARSELTYPE_RANDOM },			// ランダム
	{ "data/TEXTURE/BackTitle000.png", D3DXVECTOR3(640.0f, 620.0f, 0.0f), EXIT_WIDTH, EXIT_HEIGHT, CHARSELTYPE_EXIT },								// 戻る

};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// キャラクターセレクト画面の初期化処理
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitCharsel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// テクスチャの読み込み
	for (int nCntCharselTex = 0; nCntCharselTex < CHARSELTYPE_MAX; nCntCharselTex++)
	{
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			g_aCharselTexInfo[nCntCharselTex].pFileName, 	// ファイルの名前
			&g_pTextureCharsel[nCntCharselTex]);			// テクスチャへのポインタ
	}
	for (int nCntCharselTex = 0; nCntCharselTex < CHARSELTYPE_MAX; nCntCharselTex++)
	{
		g_aCharsel[nCntCharselTex].pos = g_aCharselTexInfo[nCntCharselTex].pos;				// 位置
		g_aCharsel[nCntCharselTex].fWidth = g_aCharselTexInfo[nCntCharselTex].fWidth;		// 幅
		g_aCharsel[nCntCharselTex].fHeight = g_aCharselTexInfo[nCntCharselTex].fHeight;		// 高さ
		g_aCharsel[nCntCharselTex].type = g_aCharselTexInfo[nCntCharselTex].type;			// 種類
		g_aCharsel[nCntCharselTex].bUse = false;											// 使っているかどうか
		g_aCharsel[nCntCharselTex].moveTex = 0.0f;											// テクスチャの移動量
	}
	g_bReady = false;
	MakeVertexCharsel(pDevice);
	// カメラの初期化処理
	InitCamera();
	// カーソルの初期化処理
	InitCursor();
	// マーカーの初期化処理
	InitMarker();
	InitShadow();
	InitLine();
	InitOrbit();
	// プレイヤーの初期化処理
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
// 終了処理
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitCharsel(void)
{

	for (int nCntTex = 0; nCntTex < CHARSELTYPE_MAX; nCntTex++)
	{
		// テクスチャの破棄
		if (g_pTextureCharsel[nCntTex] != NULL)
		{
			g_pTextureCharsel[nCntTex]->Release();
			g_pTextureCharsel[nCntTex] = NULL;
		}
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffCharsel != NULL)
	{
		g_pVtxBuffCharsel->Release();
		g_pVtxBuffCharsel = NULL;
	}
	// カーソルの終了処理
	UninitCursor();
	// マーカーの終了処理
	UninitMarker();
	// カメラの終了処理
	UninitCamera();

	//フロントポリゴンの開放
	ReleaseAllFlontPolygon();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 更新処理
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateCharsel(void)
{
	VERTEX_2D*pVtx;					// 頂点情報へのポインタ

	// 頂点lバッファをロックし頂点データへのポインタを取得
	g_pVtxBuffCharsel->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < CHARSELTYPE_MAX; nCntTex++, pVtx += 4)
	{
		if (g_aCharsel[nCntTex].type == CHARSELTYPE_BG)
		{
			g_aCharsel[nCntTex].moveTex += 0.001f;				// 背景の移動量

		}
		else if (g_aCharsel[nCntTex].type == CHARSELTYPE_CHOUTINUP)
		{
			g_aCharsel[nCntTex].moveTex += 0.002f;		// 上提灯の移動量
		}
		else if (g_aCharsel[nCntTex].type == CHARSELTYPE_CHOUTINDOWN)
		{
			g_aCharsel[nCntTex].moveTex += 0.002f;		// 下提灯の移動量

		}
		if (g_aCharsel[nCntTex].moveTex >= 1.0f)
		{
			g_aCharsel[nCntTex].moveTex = 0;
		}
		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f + g_aCharsel[nCntTex].moveTex, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f + g_aCharsel[nCntTex].moveTex, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + g_aCharsel[nCntTex].moveTex, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f + g_aCharsel[nCntTex].moveTex, 1.0f);
	}
	// 頂点バッファをアンロック
	g_pVtxBuffCharsel->Unlock();
	// カメラの更新処理
	UpdateCamera();

	// カーソルの更新処理
	UpdateCursor();
	// マーカーの更新処理
	UpdateMarker();
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		GetPlayer()[nCnt].nMotionType = PLAYER_MOTION_TYPE_NEUTRAL;
	}
	// プレイヤーの更新処理
	UpdatePlayer(0);
	UpdatePlayer(1);
	UpdatePlayer(2);
	UpdatePlayer(3);

	int nTotalMarker = GetNumMarker();			// 置いたマーカーの総数
	int nTotalGamePad = GetGamePadNum();		// 刺さっているゲームパッドの数

	if (nTotalGamePad == nTotalMarker)
	{// ゲームパッドの数とキャラを選択した数が同じとき
		if (!g_bReady)
		{// 準備完了
			PlaySound(SOUND_CHARACTOR_READY);
		}
		g_bReady = true;
	}
	else
	{// ゲームパッドの数とキャラを選択した数が同じとき
		g_bReady = false;
	}
	if (g_bReady == true)
	{// 選択が完了している時

		SetFlontPolygon(FLONTTYPE_READY, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH , SCREEN_HEIGHT / 5, FLONTTYPE_READY);
		if (GetKeyboardTrigger(DIK_9))
		{
			if (GetFade() != FADE_OUT)		//フェードアウトが実行されていないなら
			{
				PlaySound(SOUND_DECISION);
				PlaySound(SOUND_KANSEI_2);
				//フェードモード設定
				SetFade(MODE_GAME);
			}
		}
		for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
		{
			if (GetGamePadTrigger(nCnt, BUTTON_START) )
			{
				if (GetFade() != FADE_OUT)		//フェードアウトが実行されていないなら
				{
					PlaySound(SOUND_DECISION);
					PlaySound(SOUND_KANSEI_2);

					//フェードモード設定
					SetFade(MODE_GAME);
				}
			}
		}
	}
	else
	{// 選択が完了してない時
		ReleaseAllFlontPolygon();
	}
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 描画処理
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawCharsel(void)
{
	// デバイスを所得する
	LPDIRECT3DDEVICE9 	pDevice = GetDevice();
	Camera *pCamera = GetCamera();
	Player *pPlayer = GetPlayer();
	D3DVIEWPORT9 viewportDef;
	// ビューポート情報を取得
	pDevice->GetViewport(&viewportDef);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCharsel, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntCharsel = 0; nCntCharsel < CHARSELTYPE_MAX; nCntCharsel++)
	{
		if (g_aCharsel[nCntCharsel].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureCharsel[nCntCharsel]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntCharsel * MAX_CHARSELTOP,
				2);
		}
	}
	// マーカーの描画処理
	DrawMarker();
	// カーソルの描画処理
	DrawCursor();

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (pPlayer[nCnt].typeInfo != PLAYERTYPE_MAX)
		{
			// 左上のプレイヤー（カーソル１）
			SetCamera(nCnt+1);
			// Ｚバッファのビューポートのエリアをクリア
			pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
			// プレイヤーのタイプ　カメラの番号（変えない）
			DrawPlayer(nCnt, nCnt+1);

			// マーカーの描画処理
			DrawMarker();
			// カーソルの描画処理
			DrawCursor();

		}
	}


	//// 右下上のプレイヤー（カーソル２）
	//SetCamera(2);
	//// Ｚバッファのビューポートのエリアをクリア
	//pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	//// プレイヤーのタイプ　カメラの番号（変えない）
	//DrawPlayer(1, 2);

	//// 左下のプレイヤー（カーソル３）
	//SetCamera(3);
	//// Ｚバッファのビューポートのエリアをクリア
	//pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	//// プレイヤーのタイプ　カメラの番号（変えない）
	//DrawPlayer(2, 3);

	//// 右下のプレイヤー（カーソル４）
	//SetCamera(4);
	//// Ｚバッファのビューポートのエリアをクリア
	//pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	//// プレイヤーのタイプ　カメラの番号（変えない）
	//DrawPlayer(3, 4);

	// ビューポート情報をもとに戻す
	pDevice->SetViewport(&viewportDef);
	//フロントポリゴン
	DrawFlontPolygon();

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 頂点情報の作成
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MakeVertexCharsel(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D*pVtx;		// 頂点情報へのポインタ

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_CHARSELTOP * (CHARSELTYPE_MAX),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCharsel,
		NULL);

	// 頂点lバッファをロックし頂点データへのポインタを取得
	g_pVtxBuffCharsel->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < CHARSELTYPE_MAX; nCnt++, pVtx += 4)
	{
		// 座標
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// rhw
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 色
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// 頂点バッファをアンロック
	g_pVtxBuffCharsel->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// キャラクター選択の設定
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetCharsel(D3DXVECTOR3	pos, float fWidth, float fHeight, CHARSELTYPE type)
{
	VERTEX_2D*pVtx;		// 頂点情報へのポインタ

	// 頂点lバッファをロックし頂点データへのポインタを取得
	g_pVtxBuffCharsel->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < CHARSELTYPE_MAX; nCnt++, pVtx += 4)
	{
		if (g_aCharsel[nCnt].bUse == false)
		{
			g_aCharsel[nCnt].pos = pos;				// 位置
			g_aCharsel[nCnt].fWidth = fWidth;		// 幅
			g_aCharsel[nCnt].fHeight = fHeight;		// 高さ
			g_aCharsel[nCnt].type = type;			// 種類

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(- g_aCharsel[nCnt].fWidth / 2, -g_aCharsel[nCnt].fHeight / 2, 0.0f) + g_aCharsel[nCnt].pos;
			pVtx[1].pos = D3DXVECTOR3(g_aCharsel[nCnt].fWidth / 2, -g_aCharsel[nCnt].fHeight / 2, 0.0f) + g_aCharsel[nCnt].pos;
			pVtx[2].pos = D3DXVECTOR3(- g_aCharsel[nCnt].fWidth / 2, g_aCharsel[nCnt].fHeight / 2, 0.0f) + g_aCharsel[nCnt].pos;
			pVtx[3].pos = D3DXVECTOR3(g_aCharsel[nCnt].fWidth / 2, g_aCharsel[nCnt].fHeight / 2, 0.0f) + g_aCharsel[nCnt].pos;
			g_aCharsel[nCnt].bUse = true;
			break;
		}
	}
	// 頂点バッファをアンロック
	g_pVtxBuffCharsel->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 当たり判定
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
			{// 範囲
				switch (g_aCharsel[nCharsel].type)
				{
				case CHARSELTYPE_MATURI:
					type = PLAYERTYPE_MATURI;	// まつり
					break;
				case CHARSELTYPE_AMANO:
					type = PLAYERTYPE_AMANO;	// まの
					break;
				case CHARSELTYPE_GOJOU:
					type = PLAYERTYPE_GOJOU;	// 五条
					break;
				case CHARSELTYPE_MOMIJI:
					type = PLAYERTYPE_MOMIJI;	// もみじ
					break;
				case CHARSELTYPE_DONROID:
					type = PLAYERTYPE_DONROID;	// ドンロイド
					break;
				case CHARSELTYPE_RANDOM:
					type = PLAYERTYPE(rand() % PLAYERTYPE_MAX);	// ランダム
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
