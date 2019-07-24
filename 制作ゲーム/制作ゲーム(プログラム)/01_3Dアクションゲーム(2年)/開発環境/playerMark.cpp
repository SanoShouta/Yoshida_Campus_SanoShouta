//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// プレイヤー番号の表示の処理 [playerMark.cpp]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "playerMark.h"
#include "player.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// プロトタイプ宣言
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void MakeVertexPlayerMark(LPDIRECT3DDEVICE9 pDevice);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// グローバル変数
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
LPDIRECT3DTEXTURE9		g_pTexturePlayerMark[PLAYERMARK_MAX] = {};			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerMark = NULL;							//頂点バッファへのポインタ
PlayerMark			g_aPlayerMark[PLAYERMARK_MAX];

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 初期化処理
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitPlayerMark(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCntPlayerMark = 0; nCntPlayerMark < PLAYERMARK_MAX; nCntPlayerMark++)
	{
		g_aPlayerMark[nCntPlayerMark].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayerMark[nCntPlayerMark].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayerMark[nCntPlayerMark].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPlayerMark[nCntPlayerMark].nCntSwitch = 0;
		g_aPlayerMark[nCntPlayerMark].fWidth = PLAYERMARK_WIDTH;
		g_aPlayerMark[nCntPlayerMark].fHeight = PLAYERMARK_HEIGHT;
		g_aPlayerMark[nCntPlayerMark].bUse = true;
	}
	// 頂点情報の作成
	MakeVertexPlayerMark(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerMark(void)
{
	// テクスチャの開放
	for (int nCntPlayerMark = 0; nCntPlayerMark < PLAYERMARK_MAX; nCntPlayerMark++)
	{
		if (g_pTexturePlayerMark[nCntPlayerMark] != NULL)
		{
			g_pTexturePlayerMark[nCntPlayerMark]->Release();
			g_pTexturePlayerMark[nCntPlayerMark] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffPlayerMark != NULL)
	{
		g_pVtxBuffPlayerMark->Release();
		g_pVtxBuffPlayerMark = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerMark(void)
{
	Player *pPlayer = GetPlayer();
	for (int nCntPlayerMark = 0; nCntPlayerMark < PLAYERMARK_MAX; nCntPlayerMark++)
	{
		if (pPlayer[nCntPlayerMark].typeInfo != PLAYERTYPE_MAX)
		{
			if (g_aPlayerMark[nCntPlayerMark].bUse == true)
			{// 表示している時
				Player *pPlayer = GetPlayer();
				if (pPlayer[nCntPlayerMark].bUse == true)
				{
					if (g_aPlayerMark[nCntPlayerMark].bUse == true)
					{
						g_aPlayerMark[nCntPlayerMark].pos = D3DXVECTOR3(pPlayer[nCntPlayerMark].aModel[3].mtxWorld._41, pPlayer[nCntPlayerMark].aModel[3].mtxWorld._42 + 50.0f, pPlayer[nCntPlayerMark].aModel[3].mtxWorld._43);
						g_aPlayerMark[nCntPlayerMark].nCntSwitch++;
						if (g_aPlayerMark[nCntPlayerMark].nCntSwitch >= PLAYERMARK_COUNTSPEED)
						{// 一定時間経ったとき
							g_aPlayerMark[nCntPlayerMark].bUse = false;
							g_aPlayerMark[nCntPlayerMark].nCntSwitch = 0;
						}
					}
					else
					{
						g_aPlayerMark[nCntPlayerMark].bUse = false;
					}
				}

			}
			else if (g_aPlayerMark[nCntPlayerMark].bUse == false)
			{// 表示してない時
				g_aPlayerMark[nCntPlayerMark].nCntSwitch++;
				if (g_aPlayerMark[nCntPlayerMark].nCntSwitch >= PLAYERMARK_COUNTSPEED)
				{// 一定時間経ったとき
					g_aPlayerMark[nCntPlayerMark].bUse = true;
					g_aPlayerMark[nCntPlayerMark].nCntSwitch = 0;
				}
			}
		}
		else
		{
			g_aPlayerMark[nCntPlayerMark].bUse = false;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerMark(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxView, mtxTrans;				//計算用マトリックス

	//Zバッファを有効
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 10);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	for (int nCntPlayerMark = 0; nCntPlayerMark < PLAYERMARK_MAX; nCntPlayerMark++)
	{
		if (g_aPlayerMark[nCntPlayerMark].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//逆行列を設定
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._11 = mtxView._11;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._12 = mtxView._21;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._13 = mtxView._31;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._21 = mtxView._12;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._22 = mtxView._22;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._23 = mtxView._32;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._31 = mtxView._13;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._32 = mtxView._23;
			g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_aPlayerMark[nCntPlayerMark].pos.x, g_aPlayerMark[nCntPlayerMark].pos.y, g_aPlayerMark[nCntPlayerMark].pos.z);

			D3DXMatrixMultiply(&g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark, &g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aPlayerMark[nCntPlayerMark].mtxWorldPlayerMark);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0,
				g_pVtxBuffPlayerMark,
				0,
				sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePlayerMark[nCntPlayerMark]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntPlayerMark * 4,
				2);
		}
	}

	//Zバッファを無効
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexPlayerMark(LPDIRECT3DDEVICE9 pDevice)
{
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		PLAYERMARK_TEXTURE_0,
		&g_pTexturePlayerMark[0]);
	D3DXCreateTextureFromFile(pDevice,
		PLAYERMARK_TEXTURE_1,
		&g_pTexturePlayerMark[1]);
	D3DXCreateTextureFromFile(pDevice,
		PLAYERMARK_TEXTURE_2,
		&g_pTexturePlayerMark[2]);
	D3DXCreateTextureFromFile(pDevice,
		PLAYERMARK_TEXTURE_3,
		&g_pTexturePlayerMark[3]);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * PLAYERMARK_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerMark,
		NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayerMark->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPlayerMark = 0; nCntPlayerMark < PLAYERMARK_MAX; nCntPlayerMark++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_aPlayerMark[nCntPlayerMark].fWidth, g_aPlayerMark[nCntPlayerMark].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPlayerMark[nCntPlayerMark].fWidth, g_aPlayerMark[nCntPlayerMark].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aPlayerMark[nCntPlayerMark].fWidth, -g_aPlayerMark[nCntPlayerMark].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPlayerMark[nCntPlayerMark].fWidth, -g_aPlayerMark[nCntPlayerMark].fHeight, 0.0f);

		//法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[1].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[2].nor = D3DXVECTOR3(0.0, 0.0, -1.0);
		pVtx[3].nor = D3DXVECTOR3(0.0, 0.0, -1.0);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPlayerMark->Unlock();

}
