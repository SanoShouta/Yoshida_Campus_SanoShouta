//=============================================================================
//
// ラインエフェクト処理 [lineEffect.cpp]
// Author : 佐藤安純 Sato_Asumi
//
//=============================================================================
#include "lineEffect.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define LINE_EFFECT	(400)

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexLineEffect(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLineEffect = NULL;	//頂点バッファへのポインタ
LineEffect				g_LineEffect[LINE_EFFECT];
LINETYPEEFFECT			g_TypeEffect;					//エフェクトの種類
int						g_nCntTimeLine;					//時間カウンター
bool					g_bPlay;						//使用しているかどうか

//=============================================================================
// 初期化処理
//=============================================================================
void InitLineEffect(void)
{
	//変数宣言
	int nCntLineEffect;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	//変数の初期化
	g_nCntTimeLine = 0;
	g_bPlay = false;
	for (nCntLineEffect = 0; nCntLineEffect < LINE_EFFECT; nCntLineEffect++)
	{
		g_LineEffect[nCntLineEffect].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		g_LineEffect[nCntLineEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_LineEffect[nCntLineEffect].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_LineEffect[nCntLineEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_LineEffect[nCntLineEffect].type = LINETYPE_EFFECT_MAX;
		g_LineEffect[nCntLineEffect].bUse = false;
	}

	// 頂点情報の作成
	MakeVertexLineEffect(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLineEffect(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffLineEffect != NULL)
	{
		g_pVtxBuffLineEffect->Release();
		g_pVtxBuffLineEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLineEffect(void)
{
	//変数宣言
	int nCntLineEffect;
	D3DXVECTOR3 Pos = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 Pos2 = D3DXVECTOR3(0, 0, 0);

	g_nCntTimeLine++;		//時間の加算

	if (g_bPlay == true)
	{
		if (g_TypeEffect == LINETYPE_EFFECT_RAIN)
		{
			for (int nCntRain = 0; nCntRain < 3; nCntRain++)
			{
				Pos.x = (float)-500 + rand() % 1200;
				Pos.z = (float)-100 + rand() % 600;

				CreateLineEffect(D3DXVECTOR3(Pos.x, 300, Pos.z), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(0.7f, 0.9f, 0.9f, 1.0f), 100.0f, LINETYPE_EFFECT_RAIN);
			}
		}
		else
		{

			if (g_nCntTimeLine % 10 == 0)
			{
				for (int nCntRain = 0; nCntRain < 2; nCntRain++)
				{
					Pos.y = (float)600 + rand() % 300;
					Pos.z = (float)-300 + rand() % 600;
					Pos2.y = (float)600 + rand() % 300;

					CreateLineEffect(D3DXVECTOR3(-600, Pos.y, Pos.z), D3DXVECTOR3(0, 0, D3DX_PI * 0.5f), D3DXCOLOR(0.5f, 0.9f, 0.6f, 0.5f), 100.0f, LINETYPE_EFFECT_WINDY);
					CreateLineEffect(D3DXVECTOR3(-600, Pos2.y, Pos2.z), D3DXVECTOR3(0, 0, D3DX_PI * 0.5f), D3DXCOLOR(0.4f, 0.5f, 0.4f, 0.5f), 100.0f, LINETYPE_EFFECT_WINDY);
				}
			}
		}
	}

	for (nCntLineEffect = 0; nCntLineEffect < LINE_EFFECT; nCntLineEffect++)
	{
		if (g_LineEffect[nCntLineEffect].bUse == true)
		{
			switch (g_LineEffect[nCntLineEffect].type)
			{
			case LINETYPE_EFFECT_RAIN:
				//位置更新
				g_LineEffect[nCntLineEffect].move.y += -0.1f;
				g_LineEffect[nCntLineEffect].pos.y += g_LineEffect[nCntLineEffect].move.y;

				if (g_LineEffect[nCntLineEffect].pos.y < -350.0)
				{
					g_LineEffect[nCntLineEffect].bUse = false;
				}
				break;

			case LINETYPE_EFFECT_WINDY:
				//位置更新
				g_LineEffect[nCntLineEffect].pos.x += 9.0f;

				if (g_LineEffect[nCntLineEffect].pos.x > 1600.0)
				{
					g_LineEffect[nCntLineEffect].bUse = false;
				}
				break;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLineEffect(void)
{
	//変数宣言
	int nCntLineEffect;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX		  mtxRot, mtxTrans;			// 計算用マトリックス

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (nCntLineEffect = 0; nCntLineEffect < LINE_EFFECT; nCntLineEffect++)
	{
		if (g_LineEffect[nCntLineEffect].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_LineEffect[nCntLineEffect].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_LineEffect[nCntLineEffect].rot.y, g_LineEffect[nCntLineEffect].rot.x, g_LineEffect[nCntLineEffect].rot.z);
			D3DXMatrixMultiply(&g_LineEffect[nCntLineEffect].mtxWorld, &g_LineEffect[nCntLineEffect].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_LineEffect[nCntLineEffect].pos.x, g_LineEffect[nCntLineEffect].pos.y, g_LineEffect[nCntLineEffect].pos.z);
			D3DXMatrixMultiply(&g_LineEffect[nCntLineEffect].mtxWorld, &g_LineEffect[nCntLineEffect].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_LineEffect[nCntLineEffect].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffLineEffect, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, NULL);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_LINELIST, nCntLineEffect * 2, 1);
		}
	}

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexLineEffect(LPDIRECT3DDEVICE9 pDevice)
{
	//変数宣言
	int nCntLineEffect;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * LINE_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLineEffect,
		NULL);

	VERTEX_3D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffLineEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLineEffect = 0; nCntLineEffect < LINE_EFFECT; nCntLineEffect++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

		pVtx += 2;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLineEffect->Unlock();
}

//=============================================================================
// ラインのタイプ設定
//=============================================================================
void SetLineEffect(LINETYPEEFFECT type, bool bPlayEffect)
{
	g_TypeEffect = type;
	g_bPlay = bPlayEffect;
}

//=============================================================================
// ラインの設定
//=============================================================================
void CreateLineEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float nLong, LINETYPEEFFECT type)
{
	//変数宣言
	int nCntLineEffect;

	VERTEX_3D * pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffLineEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLineEffect = 0; nCntLineEffect < LINE_EFFECT; nCntLineEffect++)
	{
		if (g_LineEffect[nCntLineEffect].bUse == false)
		{
			g_LineEffect[nCntLineEffect].pos = pos;
			g_LineEffect[nCntLineEffect].type = type;
			g_LineEffect[nCntLineEffect].rot = rot;
			g_LineEffect[nCntLineEffect].color = col;
			g_LineEffect[nCntLineEffect].nLong = nLong;
			g_LineEffect[nCntLineEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_LineEffect[nCntLineEffect].bUse = true;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y, pos.z);
			pVtx[1].pos = D3DXVECTOR3(pos.x, pos.y + nLong, pos.z);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			break;
		}

		pVtx += 2;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLineEffect->Unlock();
}