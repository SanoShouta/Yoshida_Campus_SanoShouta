//=============================================================================
//
// スタッフロール画面 [staff.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "staff.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "gamepad.h"
#include "flontpolygon.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define TEXTURENAME	("data\\TEXTURE\\StaffRoll.png")	//読み込むテクスチャファイル名
#define POS			(D3DXVECTOR3(640, 360, 0))		//中心座標
#define STAFF_TIME	(60 * 140)						//スタッフ画面の切り替え時間
#define TEX_MOVE	(0.0001f)						//UV値の変化量

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureStaff = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStaff = NULL;	//頂点バッファへのポインタ
Staff					g_Staff;					//構造体の情報
int						g_nStaffTime;				//スタッフロールの時間カウンター
float					g_fCntUV;				//UV値の計算

//=============================================================================
// スタッフロール初期化処理
//=============================================================================
void InitStaff(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数の初期化
	g_Staff.Pos = POS;
	g_nStaffTime = 0;
	g_fCntUV = 0.0f;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURENAME,
		&g_pTextureStaff);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStaff,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffStaff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.01f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.01f);

	//頂点バッファをアンロックする
	g_pVtxBuffStaff->Unlock();
}

//=============================================================================
// スタッフロール終了処理
//=============================================================================
void UninitStaff(void)
{
	//テクスチャの破棄
	if (g_pTextureStaff != NULL)
	{
		g_pTextureStaff->Release();
		g_pTextureStaff = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffStaff != NULL)
	{
		g_pVtxBuffStaff->Release();
		g_pVtxBuffStaff = NULL;
	}

	//フロントポリゴンの開放
	ReleaseAllFlontPolygon();
}

//=============================================================================
// スタッフロール更新処理
//=============================================================================
void UpdateStaff(void)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//フェード情報を取得する
	FADE fade = GetFade();

	//タイマーの加算
	g_nStaffTime++;

	//スキップキーを押していたら
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_fCntUV += 0.0005f;
	}
	else
	{
		g_fCntUV += TEX_MOVE;
	}

	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		if (GetPovTpress(nCnt, POV_DOWN) == true)
		{
			g_fCntUV += 0.0005f;
			break;
		}
		if (GetGamePadStickPress(nCnt, ANALOG_STICK_DOWN) == true)
		{
			g_fCntUV += 0.0005f;
			break;
		}
	}

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffStaff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + g_fCntUV);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + g_fCntUV);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.1f + g_fCntUV);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.1f + g_fCntUV);

	//頂点バッファをアンロックする
	g_pVtxBuffStaff->Unlock();

	//決定キーが押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
		{

			//フェードモード設定
			SetFade(MODE_SELECT);
		}

	}
	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		if (GetGamePadTrigger(nCnt, BUTTON_START) || GetGamePadTrigger(nCnt, BUTTON_A) || GetGamePadTrigger(nCnt, BUTTON_B))
		{
			if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
			{
				//フェードモード設定
				SetFade(MODE_SELECT);
			}
		}
	}

	//表示時間が来たら
	if (g_nStaffTime > STAFF_TIME)
	{
		if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
		{
			//フェードモード設定
			SetFade(MODE_SELECT);
		}
	}

	//一定のUV値が来たら
	if (g_fCntUV > 0.84f)
	{
		if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
		{
			//フェードモード設定
			SetFade(MODE_SELECT);
		}
	}
}

//=============================================================================
// スタッフロール描画処理
//=============================================================================
void DrawStaff(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

									//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStaff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureStaff);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
								0,						//開始する頂点のインデックス
								2);						//プリミティブの数
}