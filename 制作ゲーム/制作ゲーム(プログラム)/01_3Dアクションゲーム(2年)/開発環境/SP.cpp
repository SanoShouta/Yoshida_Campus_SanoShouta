////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 必殺技処理 [SP.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "SP.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "player.h"
//******************************************************************************************************************************
// マクロ定義
//******************************************************************************************************************************
#define MAX_SP_NUM	(12)
#define SP_WHIDTH		(20)
#define SP_HIGHT		(30)
#define ANIM			(0.3333f)
#define SP_Y			(90)
//******************************************************************************************************************************
// プロトタイプ宣言
//******************************************************************************************************************************
void MakeVertexSp(LPDIRECT3DDEVICE9 pDevice);
//******************************************************************************************************************************
// グローバル変数
//******************************************************************************************************************************
Sp g_aSp[MAX_SP_NUM];
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSP = NULL;	// 頂点バッファへのポインタ
SpData g_aSpData[SPTEX_MAX] =
{
	{ NULL,"data/TEXTURE/Attack_UI000.png" },
};
int g_nSetNum;		//ライフのセットカウンター
int g_nCounter;
//==============================================================================================================================
// 初期化処理
//==============================================================================================================================
void InitSp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	Player *pPlayer = GetPlayer();

	//構造体の初期化

	for (int nCntSp = 0; nCntSp < MAX_SP_NUM; nCntSp++)
	{
		g_aSp[nCntSp].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 位置
		g_aSp[nCntSp].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き
		g_aSp[nCntSp].fWidth = 0;									// 幅
		g_aSp[nCntSp].fHeight = 0;									// 高さ
		g_aSp[nCntSp].nPatternAnim = 0;								// パターン
		g_aSp[nCntSp].nCounterAnim = 0;								// カウンター
		g_aSp[nCntSp].nIdy = 0;										// プレイヤーナンバー
		g_aSp[nCntSp].nNumber = 0;									// 個数ナンバー
		g_aSp[nCntSp].bUse = false;									// 使用されているかどうか
	}

	//テクスチャの読み込み
	for (int nCntTex = 0; nCntTex < SPTEX_MAX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			g_aSpData[nCntTex].pFileName,						// ファイルの名前
			&g_aSpData[nCntTex].pTexture);						// テクスチャへのポインタ
	}

	// 頂点情報の設定
	MakeVertexSp(pDevice);

	//変数の初期化
	int nNum = 0;
	g_nSetNum = 0;
	g_nCounter = 1;

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (pPlayer[nCnt].typeInfo != PLAYERTYPE_MAX)
		{
			nNum++;
		}
	}
	if (nNum == 2)
	{// 2人なら
		if (pPlayer[0].typeInfo != PLAYERTYPE_MAX)
		{// 選択されていたら
		 // 左を中心としての初期座標・回転・テクスチャ・ライフ分割数・いじらない・長さ横・縦
			SetSp(D3DXVECTOR3(155 + 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 0, 0);
			SetSp(D3DXVECTOR3(110 + 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 0, 1);
			SetSp(D3DXVECTOR3(65 + 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 0, 2);

		}
		if (pPlayer[1].typeInfo != PLAYERTYPE_MAX)
		{// 選択されていたら
			SetSp(D3DXVECTOR3(455 - 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 1, 0);
			SetSp(D3DXVECTOR3(410 - 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 1, 1);
			SetSp(D3DXVECTOR3(365 - 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 1, 2);

		}
	}
	else
	{
		if (pPlayer[0].typeInfo != PLAYERTYPE_MAX)
		{// 選択されていたら
			// 左を中心としての初期座標・回転・テクスチャ・ライフ分割数・いじらない・長さ横・縦
			SetSp(D3DXVECTOR3(155 +15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 0, 0);
			SetSp(D3DXVECTOR3(110+15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 0, 1);
			SetSp(D3DXVECTOR3(65+15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 0, 2);

		}
		if (pPlayer[1].typeInfo != PLAYERTYPE_MAX)
		{// 選択されていたら
			SetSp(D3DXVECTOR3(455-15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 1, 0);
			SetSp(D3DXVECTOR3(410 - 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 1, 1);
			SetSp(D3DXVECTOR3(365 - 15, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 1, 2);

		}
		if (pPlayer[2].typeInfo != PLAYERTYPE_MAX)
		{// 選択されていたら
			SetSp(D3DXVECTOR3(755+70, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 2, 0);
			SetSp(D3DXVECTOR3(710 + 70, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 2, 1);
			SetSp(D3DXVECTOR3(665 + 70, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 2, 2);
		}
		if (pPlayer[3].typeInfo != PLAYERTYPE_MAX)
		{
			// 選択されていたら
			SetSp(D3DXVECTOR3(1055+50, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 3, 0);
			SetSp(D3DXVECTOR3(1010+50, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 3, 1);
			SetSp(D3DXVECTOR3(965+50, SP_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SP_WHIDTH, SP_HIGHT, 3, 2);
		}
	}
}

//==============================================================================================================================
// 終了処理
//==============================================================================================================================
void UninitSp(void)
{
	// テクスチャの破棄
	for (int nCntSp = 0; nCntSp <SPTEX_MAX; nCntSp++)
	{
		if (g_aSpData[nCntSp].pTexture!= NULL)
		{
			g_aSpData[nCntSp].pTexture->Release();
			g_aSpData[nCntSp].pTexture = NULL;
		}
	}
	for (int nCntSp = 0; nCntSp < MAX_SP_NUM; nCntSp++)
	{
		for (int nCntSetSp = 0; nCntSetSp < MAX_SP; nCntSetSp++)
		{
			// 頂点バッファの破棄
			if (g_pVtxBuffSP != NULL)
			{
				g_pVtxBuffSP->Release();
				g_pVtxBuffSP = NULL;
			}
		}
	}
}

//==============================================================================================================================
// 更新処理
//==============================================================================================================================
void UpdateSp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();				// デバイスの取得
	//VERTEX_2D *pVtx;	// 頂点情報のポインタ
}

//==============================================================================================================================
// 描画処理
//==============================================================================================================================
void DrawSp(void)
{
	//変数宣言
	int nCntDraw = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSP, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntSp = 0; nCntSp < MAX_SP_NUM; nCntSp++)
	{
		if (g_aSp[nCntSp].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_aSpData[SPTEX_BG].pTexture);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,						//プリミティブの種類
				nCntSp * 4,									//開始する頂点のインデックス
				2);											//プリミティブの数
		}
	}
}

//==============================================================================================================================
// 頂点情報の作成
//==============================================================================================================================
void MakeVertexSp(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;	// 頂点情報のポインタ

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SP_NUM * MAX_SP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSP,
		NULL);


	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffSP->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSp = 0; nCntSp < MAX_SP_NUM; nCntSp++)
	{
		for (int nCntSetSp = 0; nCntSetSp < MAX_SP; nCntSetSp++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0, 0, 0);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0);
			pVtx[2].pos = D3DXVECTOR3(0, 0, 0);
			pVtx[3].pos = D3DXVECTOR3(0, 0, 0);

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
			pVtx[3].tex = D3DXVECTOR2(1.0, 1.0f);

			pVtx += 4;		//頂点データのポインタを４つ分進める
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffSP->Unlock();
}

//==============================================================================================================================
// メッシュの設定
//==============================================================================================================================
void SetSp(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, int nIdy, int nNumber)
{
	//変数宣言
	int nCounter = 1;
	VERTEX_2D *pVtx;	// 頂点情報のポインタ

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffSP->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSp = 0; nCntSp < MAX_SP_NUM; nCntSp++)
	{
		if (g_aSp[nCntSp].bUse == false)
		{
			g_aSp[nCntSp].pos = pos;			// 位置
			g_aSp[nCntSp].rot = rot;			// 向き
			g_aSp[nCntSp].fWidth = fWidth;		// 幅
			g_aSp[nCntSp].fHeight = fHeight;	// 奥行き
			g_aSp[nCntSp].nIdy = nIdy;			// プレイヤーナンバー
			g_aSp[nCntSp].nNumber = nNumber;	// 個数ナンバー
			g_aSp[nCntSp].bUse = true;			// 使用されているかどうか

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aSp[nCntSp].pos.x - g_aSp[nCntSp].fWidth, g_aSp[nCntSp].pos.y - g_aSp[nCntSp].fHeight, g_aSp[nCntSp].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aSp[nCntSp].pos.x + g_aSp[nCntSp].fWidth, g_aSp[nCntSp].pos.y - g_aSp[nCntSp].fHeight, g_aSp[nCntSp].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aSp[nCntSp].pos.x - g_aSp[nCntSp].fWidth, g_aSp[nCntSp].pos.y + g_aSp[nCntSp].fHeight, g_aSp[nCntSp].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aSp[nCntSp].pos.x + g_aSp[nCntSp].fWidth, g_aSp[nCntSp].pos.y + g_aSp[nCntSp].fHeight, g_aSp[nCntSp].pos.z);
			break;
		}

		pVtx += 4;		//頂点データのポインタを４つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffSP->Unlock();
}
//==============================================================================================================================
// ライフの獲得
//==============================================================================================================================
Sp *GetSp(void)
{
	return &g_aSp[0];
}
SpData *GetSpData(void)
{
	return &g_aSpData[0];
}
//==============================================================================================================================
// ライフの初期設定
//==============================================================================================================================
void SetPlayerSp(int nSp,int nIdy)
{
}
//==============================================================================================================================
// ライフの変更
//==============================================================================================================================
void GetPlayerSp(int nSp, int nIdy)
{

}

//==============================================================================================================================
// 必殺技の回数を減らす
//==============================================================================================================================
void DeleteSp(int nIdy)
{
	for (int nCntSp = 0; nCntSp < MAX_SP_NUM; nCntSp++)
	{
		if (g_aSp[nCntSp].nIdy == nIdy)
		{
			if (g_aSp[nCntSp].bUse == true)
			{
				if (g_aSp[nCntSp].nNumber == 2)
				{
					g_aSp[nCntSp].bUse = false;
					break;
				}
				else if (g_aSp[nCntSp].nNumber == 1)
				{
					g_aSp[nCntSp].bUse = false;
					break;
				}
				else
				{
					g_aSp[nCntSp].bUse = false;
					break;
				}
			}
		}
	}
}