//=============================================================================
//
// タイトル画面 [title.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "title.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "flontpolygon.h"
#include "camera.h"
#include "light.h"
#include "line.h"
#include "meshWall.h"
#include "meshField.h"
#include "model.h"
#include "game.h"
#include "gamepad.h"
#include "effect.h"
#include "effectUP.h"
#include "shadow.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_NAME	("data\\TEXTURE\\title_logo.png")	//読み込むファイル名
#define TEXTURE_NAME2	("data\\TEXTURE\\StartBottun.jpg")	//読み込むファイル名
#define MAX_POLYGON		(2)
#define MAX_TEXTURE		(2)

#define MAXSIZE_X		(450.0f)
#define MAXSIZE_Y		(281.25f)
#define MAXSIZE2_X		(100.0f)
#define MAXSIZE2_Y		(50.25f)

#define MINSIZE_X		(400.0f)
#define MINSIZE_Y		(250.0f)

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTitle[MAX_TEXTURE] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//頂点バッファへのポインタ
int						g_TitleTime;						//時間カウンター
int						g_TitleButtonTime;						//時間カウンター
Title					g_Title[MAX_POLYGON];				//タイトルの情報
LOGOSIZE				g_Logo;								//ロゴの状態
BOTTNSTATE				g_Bottun;							//ボタンの状態

//=============================================================================
// タイトル初期化処理
//=============================================================================
void InitTitle(void)
{
	// カメラの初期化処理
	InitCamera();
	// 線の初期化処理
	InitLine();
	// 影の初期化処理
	InitShadow();
	// ライトの初期化処理
	InitLight();
	// メッシュ床の初期化処理
	InitMeshField();
	// メッシュ壁の初期化処理
	InitMeshWall();
	// モデルの初期化処理
	InitModel();
	// エフェクトの初期化処理
	InitEffect();
	// エフェクトポリゴンの初期化処理
	InitEffectUP();
	// ファイル読み込み
	SetStagePos("data/stage1.txt");

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数の初期化
	g_Title[0].Pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f);
	g_Title[0].PosHold = D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f);
	g_Title[0].Size = D3DXVECTOR3(MAXSIZE_X, MAXSIZE_Y, 0.0f);
	g_Title[0].fCola = 1.0f;
	g_Title[0].Type = TITLETYPE_LOGO;

	g_Title[1].Pos = D3DXVECTOR3(600, 650, 0.0f);
	g_Title[1].PosHold = D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f);
	g_Title[1].Size = D3DXVECTOR3(MAXSIZE2_X, MAXSIZE2_Y, 0.0f);
	g_Title[1].fCola = 1.0f;
	g_Title[1].Type = TITLETYPE_BOTTUN;

	g_Logo = LOGOSIZE_SMALL;
	g_Bottun = BOTTNSTATE_TRUE;
	g_TitleButtonTime = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&g_pTextureTitle[0]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME2,
		&g_pTextureTitle[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

// タイトルロゴ -----------------------------------------------------------------------------------------------------
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Title[0].Pos.x - g_Title[0].Size.x, g_Title[0].Pos.y - g_Title[0].Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Title[0].Pos.x + g_Title[0].Size.x, g_Title[0].Pos.y - g_Title[0].Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Title[0].Pos.x - g_Title[0].Size.x, g_Title[0].Pos.y + g_Title[0].Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Title[0].Pos.x + g_Title[0].Size.x, g_Title[0].Pos.y + g_Title[0].Size.y, 0.0f);

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

// ボタン -----------------------------------------------------------------------------------------------------
//頂点座標の設定
	pVtx[4].pos = D3DXVECTOR3(g_Title[1].Pos.x - g_Title[1].Size.x, g_Title[1].Pos.y - g_Title[1].Size.y, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_Title[1].Pos.x + g_Title[1].Size.x, g_Title[1].Pos.y - g_Title[1].Size.y, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_Title[1].Pos.x - g_Title[1].Size.x, g_Title[1].Pos.y + g_Title[1].Size.y, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(g_Title[1].Pos.x + g_Title[1].Size.x, g_Title[1].Pos.y + g_Title[1].Size.y, 0.0f);

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
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	//タイトルロゴ
	//SetFlontPolygon(FLONTTYPE_NOMAL, D3DXVECTOR3(SCREEN_WIDTH/2, 300.0f, 0.0f), 800.0f, 500.0f, FLONTTYPE_NOMAL);
}

//=============================================================================
// タイトル終了処理
//=============================================================================
void UninitTitle(void)
{
	// カメラの終了処理
	UninitCamera();
	// ラインの終了処理
	UninitLine();
	// 影の終了処理
	UninitShadow();
	// ライトの終了処理
	UninitLight();
	// エフェクトの終了処理
	UninitEffect();
	// エフェクトポリゴンの終了処理
	UninitEffectUP();
	//フロントポリゴンをすべて非表示にする
	//ReleaseAllFlontPolygon();

	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (g_pTextureTitle[nCntTex] != NULL)
		{
			g_pTextureTitle[nCntTex]->Release();
			g_pTextureTitle[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//=============================================================================
// タイトル更新処理
//=============================================================================
void UpdateTitle(void)
{
	//フェード情報を取得する
	FADE fade = GetFade();

	// カメラの更新処理
	UpdateCamera();
	// 線の更新処理
	UpdateLine();
	// 影の更新処理
	UpdateShadow();
	// ライトの更新処理
	UpdateLight();
	// メッシュ床の更新処理
	UpdateMeshField();
	// メッシュ壁の更新処理
	UpdateMeshWall();
	// モデルの更新処理
	UpdateModel();
	// エフェクトの更新処理
	UpdateEffect();
	// エフェクトポリゴンの更新処理
	UpdateEffectUP();
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		SetEffectUP(0, D3DXVECTOR3(sinf(SetRandomEffect())*600.0f, 600 + float(rand() % 300), cosf(SetRandomEffect())*300.0f + 200.0f),
			D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(SetRandomEffect(), SetRandomEffect(), SetRandomEffect()),
			D3DXCOLOR(float(rand() % 100) / 100.0f, float(rand() % 100) / 100.0f, float(rand() % 100) / 100.0f, 1.0f),
			EFFECTUPTYPE_PAPER, 10);
	}

	//フロントポリゴンの情報を取得
	FlontPolygon * pFlontPolygon;
	pFlontPolygon = GetFlontPolygon();

		//決定キーが押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
		{
			PlaySound(SOUND_DECISION_1);

			//ボタンを赤色に
			g_Bottun = BOTTNSTATE_NOMAL;

			//フェードモード設定
			SetFade(MODE_SELECT);
		}

	}
	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		if (GetGamePadTrigger(nCnt, BUTTON_START)|| GetGamePadTrigger(nCnt, BUTTON_A)|| GetGamePadTrigger(nCnt, BUTTON_B))
		{
			if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
			{
				//ボタンを赤色に
				g_Bottun = BOTTNSTATE_NOMAL;

				//フェードモード設定
				SetFade(MODE_SELECT);
			}
		}
	}

	//ロゴのサイズ更新
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_POLYGON; nCntTitle++)
	{
		switch (g_Title[nCntTitle].Type)
		{
		case TITLETYPE_LOGO:
			switch (g_Logo)
			{

			case LOGOSIZE_NONE:
				g_TitleTime++;

				if ((g_TitleTime % 50) == 0)
				{
					g_Logo = LOGOSIZE_BIG;
					g_TitleTime = 0;
				}
				break;

			case LOGOSIZE_BIG:
				//サイズの加算
				g_Title[nCntTitle].Size.x += 20;
				g_Title[nCntTitle].Size.y += 12.5f;

				if (g_Title[nCntTitle].Size.x > MAXSIZE_X && g_Title[nCntTitle].Size.y > MAXSIZE_Y)
				{
					g_Title[nCntTitle].Size.x = MAXSIZE_X;
					g_Title[nCntTitle].Size.y = MAXSIZE_Y;
					g_Logo = LOGOSIZE_SMALL;
				}

				break;

			case LOGOSIZE_SMALL:
				//サイズの減算
				g_Title[nCntTitle].Size.x -= 5;
				g_Title[nCntTitle].Size.y -= 3.125f;

				if (g_Title[nCntTitle].Size.x < MINSIZE_X && g_Title[nCntTitle].Size.y < MINSIZE_Y)
				{
					g_Title[nCntTitle].Size.x = MINSIZE_X;
					g_Title[nCntTitle].Size.y = MINSIZE_Y;
					g_Logo = LOGOSIZE_NONE;
				}
				break;
			}
			break;

		case TITLETYPE_BOTTUN:

			switch (g_Bottun)
			{
			case BOTTNSTATE_TRUE:

				//透明度の加算
				g_Title[nCntTitle].fCola += 0.02f;

				if (g_Title[nCntTitle].fCola > 1.0f)
				{
					g_Title[nCntTitle].fCola = 1.0f;

					//時間の加算
					g_TitleButtonTime++;

					if (g_TitleButtonTime % 30 == 0)
					{
						g_Bottun = BOTTNSTATE_FALSE;
						g_TitleButtonTime = 0;
					}
				}

				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				break;

			case BOTTNSTATE_FALSE:
				//透明度の減算
				g_Title[nCntTitle].fCola -= 0.02f;

				if (g_Title[nCntTitle].fCola < 0.0f)
				{
					g_Title[nCntTitle].fCola = 0.0f;
					g_Bottun = BOTTNSTATE_TRUE;
				}

				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				break;

			case BOTTNSTATE_NOMAL:
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				break;

			}
			break;
		}

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Title[nCntTitle].Pos.x - g_Title[nCntTitle].Size.x, g_Title[nCntTitle].Pos.y - g_Title[nCntTitle].Size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Title[nCntTitle].Pos.x + g_Title[nCntTitle].Size.x, g_Title[nCntTitle].Pos.y - g_Title[nCntTitle].Size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Title[nCntTitle].Pos.x - g_Title[nCntTitle].Size.x, g_Title[nCntTitle].Pos.y + g_Title[nCntTitle].Size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Title[nCntTitle].Pos.x + g_Title[nCntTitle].Size.x, g_Title[nCntTitle].Pos.y + g_Title[nCntTitle].Size.y, 0.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}

//=============================================================================
// タイトル描画処理
//=============================================================================
void DrawTitle(void)
{
	// カメラの設定
	SetCamera(0);
	// メッシュ床の描画処理
	DrawMeshField();
	// メッシュ壁の描画処理
	DrawMeshWall();
	// モデルの描画処理
	DrawModel();
	// 影の描画処理
	DrawShadow();
	// エフェクトの描画処理
	DrawEffect();
	// エフェクトポリゴンの描画処理
	DrawEffectUP();

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPolygon = 0; nCntPolygon < MAX_POLYGON; nCntPolygon++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCntPolygon]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
			nCntPolygon * 4,			//開始する頂点のインデックス
			2);					//プリミティブの数
	}
}