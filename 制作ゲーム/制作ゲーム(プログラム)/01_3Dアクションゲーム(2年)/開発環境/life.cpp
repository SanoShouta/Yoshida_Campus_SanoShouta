////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ライフ処理 [life.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "life.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "player.h"
#include "flontpolygon.h"
//******************************************************************************************************************************
// マクロ定義
//******************************************************************************************************************************
#define MAX_LIFE_NUM	(16)
#define MAX_LIFE		(100)
#define LIFE_WHIDTH		(145)
#define ANIM			(0.3333f)

//UI値
#define UI_Y			(73)
#define UI_WHITH		(250)
#define UI_HIGHT		(115)

//アイコン
#define ICON_Y			(63)
#define ICON_WHITH		(100)
#define ICON_HIGHT		(85)
//******************************************************************************************************************************
// プロトタイプ宣言
//******************************************************************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);
//******************************************************************************************************************************
// グローバル変数
//******************************************************************************************************************************
Life g_aLife[MAX_LIFE_NUM];
LifeData g_aLifeData[LIFETEX_MAX] =
{
	{ NULL,"data/TEXTURE/.jpg" },
	{ NULL,"data/TEXTURE/.jpg" },
	{ NULL,"data/TEXTURE/.jpg" },
	{ NULL,"data/TEXTURE/orbit003.jpg" },
};
int g_nLife[MAX_PLAYER];
bool g_bDown[MAX_PLAYER];
bool g_bUp[MAX_PLAYER];
//==============================================================================================================================
// 初期化処理
//==============================================================================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	Player *pPlayer = GetPlayer();

	for (int nCntLife = 0; nCntLife < MAX_LIFE_NUM; nCntLife++)
	{
		g_aLife[nCntLife].pVtxBuff = NULL;										// 頂点バッファへのポインタ
		g_aLife[nCntLife].pIdxBuff = NULL;										// インデックスバッファへのポインタ
		g_aLife[nCntLife].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);					// 位置
		g_aLife[nCntLife].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 向き
		g_aLife[nCntLife].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);				// 色
		g_aLife[nCntLife].fWidth = 0;											// 幅
		g_aLife[nCntLife].fHeight = 0;											// 高さ
		g_aLife[nCntLife].nBlock_X = 0;											// ブロックX
		g_aLife[nCntLife].nBlock_Y = 0;											// ブロックY
		g_aLife[nCntLife].nPatternAnim = 0;										// パターン
		g_aLife[nCntLife].nCounterAnim = 0;										// カウンター
		g_aLife[nCntLife].nType = 0;											// 種類
		g_aLife[nCntLife].bUse = false;											// 使用されているかどうか
		g_aLife[nCntLife].bUseDown = false;										// ダウン中かどうか
		g_aLife[nCntLife].bDownRed = false;									// 背景の赤いライフ用
		g_aLife[nCntLife].nDownRedCounter = 0;								// 背景の赤いライフ用減少
		g_aLife[nCntLife].nDrawDown = 0;									// ポリゴン減算用
	}
	for (int nCntTex = 0; nCntTex < LIFETEX_MAX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			g_aLifeData[nCntTex].pFileName,						// ファイルの名前
			&g_aLifeData[nCntTex].pTexture);						// テクスチャへのポインタ
	}
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		g_nLife[nCnt] = MAX_LIFE;
		g_bDown[nCnt] = false;
		g_bUp[nCnt] = false;
	}

	int nNum = 0;
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (pPlayer[nCnt].typeInfo != PLAYERTYPE_MAX)
		{
			nNum++;
		}
	}
	if (nNum == 2)
	{// 2人なら
		//////if (pPlayer[0].typeInfo != PLAYERTYPE_MAX)
		//////{// 選択されていたら
		////// // 左を中心としての初期座標・回転・テクスチャ・ライフ分割数・いじらない・長さ横・縦
		//////	SetFlontPolygon(5, D3DXVECTOR3(170, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
		//////	SetFlontPolygon(6, D3DXVECTOR3(250, ICON_Y, 0), ICON_WHITH, ICON_HIGHT, FLONTTYPE(FLONTTYPE_UI + (int)pPlayer[0].typeInfo + 1));
		//////	SetLife(D3DXVECTOR3(45, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH*3 + 5, 35, false);
		//////	SetLife(D3DXVECTOR3(50, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH*3, 30, false);
		//////	SetLife(D3DXVECTOR3(50, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH*3, 30, true);
		//////	SetLife(D3DXVECTOR3(50, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH*3, 30, true);
		//////}
		//////if (pPlayer[1].typeInfo != PLAYERTYPE_MAX)
		//////{// 選択されていたら
		//////	SetFlontPolygon(5, D3DXVECTOR3(770, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
		//////	SetFlontPolygon(6, D3DXVECTOR3(860, ICON_Y, 0), ICON_WHITH, ICON_HIGHT, FLONTTYPE(FLONTTYPE_UI + (int)pPlayer[1].typeInfo + 1));
		//////	SetLife(D3DXVECTOR3(675, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH*3 + 5, 35, false);
		//////	SetLife(D3DXVECTOR3(680, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH*3, 30, false);
		//////	SetLife(D3DXVECTOR3(680, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH*3, 30, true);
		//////	SetLife(D3DXVECTOR3(680, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH*3, 30, true);
		//////}
		if (pPlayer[0].typeInfo != PLAYERTYPE_MAX)
		{// 選択されていたら
		 // 左を中心としての初期座標・回転・テクスチャ・ライフ分割数・いじらない・長さ横・縦
			SetFlontPolygon(5, D3DXVECTOR3(170, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
			SetFlontPolygon(6, D3DXVECTOR3(245, ICON_Y, 0), ICON_WHITH, ICON_HIGHT, (FLONTTYPE)(FLONTTYPE_UI + (int)pPlayer[0].typeInfo + 1));
			SetLife(D3DXVECTOR3(52.5f, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH + 5, 35, false);
			SetLife(D3DXVECTOR3(55, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH, 30, false);
			SetLife(D3DXVECTOR3(55, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH, 30, true);
			SetLife(D3DXVECTOR3(55, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH, 30, true);
		}
		if (pPlayer[1].typeInfo != PLAYERTYPE_MAX)
		{// 選択されていたら
			SetFlontPolygon(5, D3DXVECTOR3(440, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
			SetFlontPolygon(6, D3DXVECTOR3(515, ICON_Y, 0), ICON_WHITH, ICON_HIGHT, (FLONTTYPE)(FLONTTYPE_UI + (int)pPlayer[1].typeInfo + 1));
			SetLife(D3DXVECTOR3(322.5f, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH + 5, 35, false);
			SetLife(D3DXVECTOR3(325, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH, 30, false);
			SetLife(D3DXVECTOR3(325, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH, 30, true);
			SetLife(D3DXVECTOR3(325, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH, 30, true);
		}
	}
	else
	{
		if (pPlayer[0].typeInfo != PLAYERTYPE_MAX)
		{// 選択されていたら
			// 左を中心としての初期座標・回転・テクスチャ・ライフ分割数・いじらない・長さ横・縦
			SetFlontPolygon(5, D3DXVECTOR3(170, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
			SetFlontPolygon(6, D3DXVECTOR3(245, ICON_Y, 0), ICON_WHITH, ICON_HIGHT, (FLONTTYPE)(FLONTTYPE_UI + (int)pPlayer[0].typeInfo + 1));
			SetLife(D3DXVECTOR3(52.5f, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH + 5, 35, false);
			SetLife(D3DXVECTOR3(55, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH, 30, false);
			SetLife(D3DXVECTOR3(55, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH, 30, true);
			SetLife(D3DXVECTOR3(55, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH, 30, true);
		}
		if (pPlayer[1].typeInfo != PLAYERTYPE_MAX)
		{// 選択されていたら
			SetFlontPolygon(5, D3DXVECTOR3(440, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
			SetFlontPolygon(6, D3DXVECTOR3(515, ICON_Y, 0), ICON_WHITH, ICON_HIGHT, (FLONTTYPE)(FLONTTYPE_UI + (int)pPlayer[1].typeInfo + 1));
			SetLife(D3DXVECTOR3(322.5f, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH + 5, 35, false);
			SetLife(D3DXVECTOR3(325, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH, 30, false);
			SetLife(D3DXVECTOR3(325, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH, 30, true);
			SetLife(D3DXVECTOR3(325, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH, 30, true);
		}
		if (pPlayer[2].typeInfo != PLAYERTYPE_MAX)
		{// 選択されていたら
			SetFlontPolygon(5, D3DXVECTOR3(830, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
			SetFlontPolygon(6, D3DXVECTOR3(905, ICON_Y, 0), ICON_WHITH, ICON_HIGHT, (FLONTTYPE)(FLONTTYPE_UI + (int)pPlayer[2].typeInfo + 1));
			SetLife(D3DXVECTOR3(712.5f, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH + 5, 35, false);
			SetLife(D3DXVECTOR3(715, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH, 30, false);
			SetLife(D3DXVECTOR3(715, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH, 30, true);
			SetLife(D3DXVECTOR3(715, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH, 30, true);
		}
		if (pPlayer[3].typeInfo != PLAYERTYPE_MAX)
		{
			// 選択されていたら
			SetFlontPolygon(5, D3DXVECTOR3(1100, UI_Y, 0), UI_WHITH, UI_HIGHT, FLONTTYPE_UI);
			SetFlontPolygon(6, D3DXVECTOR3(1175, ICON_Y, 0), ICON_WHITH, ICON_HIGHT,(FLONTTYPE)(FLONTTYPE_UI + (int)pPlayer[3].typeInfo + 1));
			SetLife(D3DXVECTOR3(982.5f, 22.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG, 100, 1, LIFE_WHIDTH + 5, 35, false);
			SetLife(D3DXVECTOR3(985, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), LIFETEX_BG2, 100, 1, LIFE_WHIDTH, 30, false);
			SetLife(D3DXVECTOR3(985, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), LIFETEX_GAGERED, 100, 1, LIFE_WHIDTH, 30, true);
			SetLife(D3DXVECTOR3(985, 25, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LIFETEX_GAGE, 100, 1, LIFE_WHIDTH, 30, true);
		}
	}
}

//==============================================================================================================================
// 終了処理
//==============================================================================================================================
void UninitLife(void)
{
	// テクスチャの破棄
	for (int nCntLife = 0; nCntLife <LIFETEX_MAX; nCntLife++)
	{
		if (g_aLifeData[nCntLife].pTexture!= NULL)
		{
			g_aLifeData[nCntLife].pTexture->Release();
			g_aLifeData[nCntLife].pTexture = NULL;
		}
	}
	for (int nCntLife = 0; nCntLife < MAX_LIFE_NUM; nCntLife++)
	{
		// 頂点バッファの破棄
		if (g_aLife[nCntLife].pVtxBuff != NULL)
		{
			g_aLife[nCntLife].pVtxBuff->Release();
			g_aLife[nCntLife].pVtxBuff = NULL;
		}
		// インデックスバッファバッファの破棄
		if (g_aLife[nCntLife].pIdxBuff != NULL)
		{
			g_aLife[nCntLife].pIdxBuff->Release();
			g_aLife[nCntLife].pIdxBuff = NULL;
		}
	}
}

//==============================================================================================================================
// 更新処理
//==============================================================================================================================
void UpdateLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();				// デバイスの取得
	VERTEX_2D *pVtx;	// 頂点情報のポインタ

	int nCnt = 0;
	for (int nCntL = 0; nCntL < MAX_LIFE_NUM; nCntL++)
	{
		nCnt = nCntL / LIFETEX_MAX;
		if (g_aLife[nCntL].bUse == true)
		{
			// 頂点バッファをロックし頂点データへのポインタを取得
			g_aLife[nCntL].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			if (g_aLife[nCntL].bUseDown == true)
			{
				if (g_aLife[nCntL].nType == LIFETEX_GAGE)
				{
					if (g_bDown[nCnt])
					{// 減少中
						g_aLife[nCntL].nDrawDown++;
						if (g_aLife[nCntL].nDrawDown >= 100 - ((float)g_nLife[nCnt] / MAX_LIFE) * 100)
						{// 100%中 X%減ったとこまで減らす
							g_bDown[nCnt] = false;
							g_aLife[nCntL - 1].bDownRed = true;		// ライフの前が赤ライフなら-1
							g_aLife[nCntL - 1].nDownRedCounter = 60; // 赤ライフ減少間隔保管
							if (g_nLife[nCnt] <= 0)
							{// 死んだら保管なし
								g_aLife[nCntL - 1].nDownRedCounter = 0;
							}
						}
					}
				}
				if (g_aLife[nCntL].nType == LIFETEX_GAGERED)
				{
					if (g_aLife[nCntL].bDownRed)
					{
						g_aLife[nCntL].nDownRedCounter--;
						if (g_aLife[nCntL].nDownRedCounter <= 0)
						{
							g_aLife[nCntL].nDownRedCounter = 0;
							g_aLife[nCntL].nDrawDown++;
							if (g_aLife[nCntL].nDrawDown >= 100 - ((float)g_nLife[nCnt] / MAX_LIFE) * 100)
							{// 100%中 X%減ったとこまで減らす
								g_aLife[nCntL].bDownRed = false;
							}
						}
					}
				}
				if (g_bUp[nCnt])
				{
					if (g_aLife[nCntL].nType == LIFETEX_GAGE)
					{
						g_aLife[nCntL].nDrawDown--;
						if (g_aLife[nCntL].nDrawDown <= 100 - ((float)g_nLife[nCnt] / MAX_LIFE) * 100)
						{// 100%中 X%増えたとこまで増やす
							g_bUp[nCnt] = false;
						}
					}
					if (g_aLife[nCntL].nType == LIFETEX_GAGERED)
					{
						g_aLife[nCntL].nDrawDown--;
						if (g_aLife[nCntL].nDrawDown <= 100 - ((float)g_nLife[nCnt] / MAX_LIFE) * 100)
						{// 100%中 X%増えたとこまで増やす
						}
					}
				}

			}
		}
	}
}

//==============================================================================================================================
// 描画処理
//==============================================================================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	// ワイヤーフレーム
//	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	for (int nCntLife = 0; nCntLife < MAX_LIFE_NUM; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aLife[nCntLife].mtxWorld);
			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aLife[nCntLife].rot.y, g_aLife[nCntLife].rot.x, g_aLife[nCntLife].rot.z);
			D3DXMatrixMultiply(&g_aLife[nCntLife].mtxWorld, &g_aLife[nCntLife].mtxWorld, &mtxRot);
			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aLife[nCntLife].pos.x, g_aLife[nCntLife].pos.y, g_aLife[nCntLife].pos.z);
			D3DXMatrixMultiply(&g_aLife[nCntLife].mtxWorld, &g_aLife[nCntLife].mtxWorld, &mtxTrans);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_aLife[nCntLife].pVtxBuff, 0, sizeof(VERTEX_2D));
			// インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_aLife[nCntLife].pIdxBuff);
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_aLifeData[g_aLife[nCntLife].nType].pTexture);
			if (g_aLife[nCntLife].bUseDown == true)
			{
				// ポリゴンの描画
				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aLife[nCntLife].nNumIndex, 0, g_aLife[nCntLife].nNumPolygon - g_aLife[nCntLife].nDrawDown * 2);
			}
			else
			{
				// ポリゴンの描画
				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aLife[nCntLife].nNumIndex, 0, g_aLife[nCntLife].nNumPolygon );

			}
		}
	}

}

//==============================================================================================================================
// 頂点情報の作成
//==============================================================================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;	// 頂点情報のポインタ
	for (int nCntLife = 0; nCntLife < MAX_LIFE_NUM; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == false)
		{
			// 頂点情報の作成
			pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * g_aLife[nCntLife].nNumVertex,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_2D,
				D3DPOOL_MANAGED,
				&g_aLife[nCntLife].pVtxBuff,
				NULL);


			// 頂点バッファをロックし頂点データへのポインタを取得

			g_aLife[nCntLife].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			// 頂点座標の設定

			for (int nCnt = 0; nCnt < g_aLife[nCntLife].nNumVertex; nCnt++)
			{// "X"は元に戻すから％　"Z"は減少または増加し続けるので÷
				pVtx[nCnt].pos = D3DXVECTOR3( (g_aLife[nCntLife].fWidth / g_aLife[nCntLife].nBlock_X)*(nCnt % (g_aLife[nCntLife].nBlock_X + 1)),
					+(g_aLife[nCntLife].fHeight)*(nCnt / (g_aLife[nCntLife].nBlock_X + 1)), 0.0f) + g_aLife[nCntLife].pos;

			}
			// rhwの設定
			for (int nCnt = 0; nCnt < g_aLife[nCntLife].nNumVertex; nCnt++)
			{
				pVtx[nCnt].rhw = 1.0f;
			}
			// 頂点カラーの設定
			for (int nCnt = 0; nCnt < g_aLife[nCntLife].nNumVertex; nCnt++)
			{
				pVtx[nCnt].col = g_aLife[nCntLife].col;
			}

			// 全体テクスチャ
			for (int nCntV = 0; nCntV < g_aLife[nCntLife].nBlock_Y + 1; nCntV++)
			{// テクスチャの設定
				for (int nCntH = 0; nCntH < g_aLife[nCntLife].nBlock_X + 1; nCntH++)
				{// "X"は元に戻すから％　"Z"は減少または増加し続けるので÷
				 // テクスチャの設定
					pVtx[nCntH + (g_aLife[nCntLife].nBlock_X + 1)*nCntV].tex = D3DXVECTOR2(float(nCntH * 100 / g_aLife[nCntLife].nBlock_X) / 100.0f , float(nCntV * 100 / g_aLife[nCntLife].nBlock_Y) / 100.0f);
				}
			}
			// 頂点バッファをアンロックする
			g_aLife[nCntLife].pVtxBuff->Unlock();
			WORD *pIdx;	// インデックスデータへのポインタ

				// インデックスバッファの作成
			pDevice->CreateIndexBuffer(sizeof(WORD)*g_aLife[nCntLife].nNumIndex,
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,
				D3DPOOL_MANAGED,
				&g_aLife[nCntLife].pIdxBuff,
				NULL);

			// インデックスバッファをロックし頂点データへのポインタを取得
			g_aLife[nCntLife].pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);


			// インデックスの設定
			for (int nCntIdx = 0, nCntPos = 0; nCntIdx < g_aLife[nCntLife].nNumIndex; nCntIdx += 2)
			{
				if ((nCntIdx / 2) % (g_aLife[nCntLife].nBlock_X + 2) == g_aLife[nCntLife].nBlock_X + 1)
				{
					pIdx[nCntIdx] = nCntPos - 1;
					pIdx[nCntIdx + 1] = nCntPos + g_aLife[nCntLife].nBlock_X + 1;
				}
				else
				{
					pIdx[nCntIdx] = nCntPos + g_aLife[nCntLife].nBlock_X + 1;
					pIdx[nCntIdx + 1] = nCntPos;

					nCntPos++;
				}
			}
			// 頂点バッファをアンロックする
			g_aLife[nCntLife].pIdxBuff->Unlock();
			break;
		}
	}
}
//==============================================================================================================================
// メッシュの設定
//==============================================================================================================================
void SetLife(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXCOLOR col, int nType, int nBlock_X, int nBlock_Y, float fWidth, float fHeight,bool bUseDown)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCntLife = 0; nCntLife < MAX_LIFE_NUM; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == false)
		{
			g_aLife[nCntLife].pos = pos;				// 位置
			g_aLife[nCntLife].rot = rot;				// 向き
			g_aLife[nCntLife].col = col;				// 色
			g_aLife[nCntLife].fWidth = fWidth;			// 幅
			g_aLife[nCntLife].fHeight = fHeight;		// 奥行き
			g_aLife[nCntLife].nBlock_X = nBlock_X;		// ブロックX
			g_aLife[nCntLife].nBlock_Y = nBlock_Y;		// ブロックZ
			g_aLife[nCntLife].nType = nType;			// 種類
			g_aLife[nCntLife].bUseDown = bUseDown;
			g_aLife[nCntLife].nNumVertex = (g_aLife[nCntLife].nBlock_X + 1)*(g_aLife[nCntLife].nBlock_Y + 1);											// 頂点数
			g_aLife[nCntLife].nNumIndex = 2 * (g_aLife[nCntLife].nBlock_X*g_aLife[nCntLife].nBlock_Y) + 4 * (g_aLife[nCntLife].nBlock_Y - 1) + 2;	// インデックス数										//
			g_aLife[nCntLife].nNumPolygon = 2 * (g_aLife[nCntLife].nBlock_X*g_aLife[nCntLife].nBlock_Y) + 4 * (g_aLife[nCntLife].nBlock_Y - 1);	// ポリゴン数

			MakeVertexLife(pDevice);
			g_aLife[nCntLife].bUse = true;										// 使用されているかどうか
			break;
		}
	}
}
//==============================================================================================================================
// ライフの獲得
//==============================================================================================================================
Life *GetLife(void)
{
	return &g_aLife[0];
}
LifeData *GetLifeData(void)
{
	return &g_aLifeData[0];
}
//==============================================================================================================================
// ライフの初期設定
//==============================================================================================================================
void SetPlayerLife(int nLife,int nIdy)
{
	g_nLife[nIdy] = nLife;
}
//==============================================================================================================================
// ライフの変更
//==============================================================================================================================
void GetPlayerLife(int nLife, int nIdy)
{
	if (g_nLife[nIdy] < nLife)
	{
		g_nLife[nIdy] = nLife;
		g_bUp[nIdy] = true;
	}
	else if (g_nLife[nIdy] != nLife)
	{
		g_nLife[nIdy] = nLife;
		g_bDown[nIdy] = true;
	}

}