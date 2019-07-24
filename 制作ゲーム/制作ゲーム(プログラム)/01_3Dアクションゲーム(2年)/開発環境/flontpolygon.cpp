//=============================================================================
//
// ポリゴン処理 [flontpolygon.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "flontpolygon.h"
#include "main.h"
#include "input.h"
#include <time.h>
#include "game.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define TEX_MOVE	(0.0005f)	//テクスチャのUV移動値

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureFlontPolygon[FLONT_TEXTYPE_MAX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFlontPolygon = NULL;			//頂点バッファへのポインタ
FlontPolygon			g_FlontPolygon[MAX_FLONTPOLYGON];		//情報設定
int						g_nMaxFlontPolygon;

//=============================================================================
// スタートボタン初期化処理
//=============================================================================
void InitFlontPolygon(void)
{
	//変数宣言
	int     nCntFlontPolygon;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数の初期化
	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		g_FlontPolygon[nCntFlontPolygon].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//中心座標
		g_FlontPolygon[nCntFlontPolygon].fHight = 0.0f;								//高さ
		g_FlontPolygon[nCntFlontPolygon].fWidth = 0.0f;								//幅
		g_FlontPolygon[nCntFlontPolygon].fUv = 0.0f;								//UV値
		g_FlontPolygon[nCntFlontPolygon].nTexNum = 0;								//テクスチャの番号
		g_FlontPolygon[nCntFlontPolygon].type = FLONTTYPE_MAX;						//タイプ
		g_FlontPolygon[nCntFlontPolygon].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色
		g_FlontPolygon[nCntFlontPolygon].bUse = false;								//使用していない状態にする
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Chotin000.png",	&g_pTextureFlontPolygon[0]);		//提灯
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\CharactorAll001.png", &g_pTextureFlontPolygon[1]);	//キャラクターの立ち絵
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Comment000.png", &g_pTextureFlontPolygon[2]);	//吹き出し
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\AreYouReady.png", &g_pTextureFlontPolygon[3]);	//準備
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title_logo.png", &g_pTextureFlontPolygon[4]);	//タイトル
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\StateUI000.png", &g_pTextureFlontPolygon[5]);		//UI
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\CharactorAll002.png", &g_pTextureFlontPolygon[6]);//顔
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GameSetting000.png", &g_pTextureFlontPolygon[7]);//指示
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GameStart000.png", &g_pTextureFlontPolygon[8]);//指示
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GameEnd000.png", &g_pTextureFlontPolygon[9]);//指示
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\fg.png", &g_pTextureFlontPolygon[10]);	//選択画面の屋台
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg.jpg", &g_pTextureFlontPolygon[11]);	//選択画面の背景
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\TimeUp000.png", &g_pTextureFlontPolygon[12]);//タイムアップ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FLONTPOLYGON,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffFlontPolygon,
								NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFlontPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(250.0f, 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(750.0f, 100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(250.0f, 200.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(750.0f, 200.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = g_FlontPolygon[nCntFlontPolygon].col;
		pVtx[1].col = g_FlontPolygon[nCntFlontPolygon].col;
		pVtx[2].col = g_FlontPolygon[nCntFlontPolygon].col;
		pVtx[3].col = g_FlontPolygon[nCntFlontPolygon].col;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffFlontPolygon->Unlock();
}

//=============================================================================
// タイトル終了処理
//=============================================================================
void UninitFlontPolygon(void)
{
	//変数宣言
	int nCntTex;

	//テクスチャの破棄
	for (nCntTex = 0; nCntTex < FLONT_TEXTYPE_MAX; nCntTex++)
	{
		if (g_pTextureFlontPolygon[nCntTex] != NULL)
		{
			g_pTextureFlontPolygon[nCntTex]->Release();
			g_pTextureFlontPolygon[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffFlontPolygon != NULL)
	{
		g_pVtxBuffFlontPolygon->Release();
		g_pVtxBuffFlontPolygon = NULL;
	}
}

//=============================================================================
// タイトル更新処理
//=============================================================================
void UpdateFlontPolygon(void)
{
	//変数宣言
	int nCntFP;

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFlontPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFP = 0; nCntFP < MAX_FLONTPOLYGON; nCntFP++, pVtx += 4)
	{
		if (g_FlontPolygon[nCntFP].bUse == true)
		{
			switch (g_FlontPolygon[nCntFP].type)
			{
			case FLONTTYPE_CHOTIN:

				//移動値の更新
				g_FlontPolygon[nCntFP].fUv += TEX_MOVE;

				if (g_FlontPolygon[nCntFP].fUv >= 1.0f)
				{
					g_FlontPolygon[nCntFP].fUv = 0.0f;
				}

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f + g_FlontPolygon[nCntFP].fUv, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f + g_FlontPolygon[nCntFP].fUv, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + g_FlontPolygon[nCntFP].fUv, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f + g_FlontPolygon[nCntFP].fUv, 1.0f);

				break;
			case FLONTTYPE_NARRATION:// ナレーション
				break;
			}
			switch (g_FlontPolygon[nCntFP].nTexNum)
			{
			case FLONT_TEXTYPE_SETTING:
				g_FlontPolygon[nCntFP].col.a += 0.1f;
				if (g_FlontPolygon[nCntFP].col.a >= 1.0f)
				{
					g_FlontPolygon[nCntFP].col.a = 1.0f;
				}
				g_FlontPolygon[nCntFP].pos.x += -0.1f;
				break;
			case FLONT_TEXTYPE_START:

				g_FlontPolygon[nCntFP].fWidth += (SCREEN_WIDTH / 1.5f - g_FlontPolygon[nCntFP].fWidth)*0.2f;
				g_FlontPolygon[nCntFP].fHight += (200 - g_FlontPolygon[nCntFP].fHight)*0.2f;
				if (g_FlontPolygon[nCntFP].fWidth - 10 <= SCREEN_WIDTH / 1.5f&&
					g_FlontPolygon[nCntFP].fHight - 10 <= 200)
				{
					g_FlontPolygon[nCntFP].col.a -= 0.1f;
					if (g_FlontPolygon[nCntFP].col.a <= 0.0f)
					{
						g_FlontPolygon[nCntFP].bUse = false;
					}
				}
				else
				{
					g_FlontPolygon[nCntFP].col.a += 0.1f;
					if (g_FlontPolygon[nCntFP].col.a >= 1.0f)
					{
						g_FlontPolygon[nCntFP].col.a = 1.0f;
					}
				}
				break;
			case FLONT_TEXTYPE_GAMEEND:
				g_FlontPolygon[nCntFP].col.a += 0.1f;
				if (g_FlontPolygon[nCntFP].col.a >= 1.0f)
				{
					g_FlontPolygon[nCntFP].col.a = 1.0f;
				}
				break;
			case FLONT_TEXTYPE_TIMEUP:
				g_FlontPolygon[nCntFP].pos.x += -1.0f;

				if (g_FlontPolygon[nCntFP].col.a >= 1.0f)
				{
					g_FlontPolygon[nCntFP].col.a = 1.0f;
				}
				if (GetGameStateCounter() >= 60)
				{
					g_FlontPolygon[nCntFP].col.a -= 0.1f;
					if (g_FlontPolygon[nCntFP].col.a <= 0.0f)
					{
						g_FlontPolygon[nCntFP].bUse = false;
						g_FlontPolygon[nCntFP].col.a = 0.0f;
					}

				}
				else
				{
					g_FlontPolygon[nCntFP].col.a += 0.1f;
				}
				break;
			}
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_FlontPolygon[nCntFP].fWidth / 2, -g_FlontPolygon[nCntFP].fHight / 2, 0.0f) + g_FlontPolygon[nCntFP].pos;
			pVtx[1].pos = D3DXVECTOR3(g_FlontPolygon[nCntFP].fWidth / 2, -g_FlontPolygon[nCntFP].fHight / 2, 0.0f) + g_FlontPolygon[nCntFP].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_FlontPolygon[nCntFP].fWidth / 2, g_FlontPolygon[nCntFP].fHight / 2, 0.0f) + g_FlontPolygon[nCntFP].pos;
			pVtx[3].pos = D3DXVECTOR3(g_FlontPolygon[nCntFP].fWidth / 2, g_FlontPolygon[nCntFP].fHight / 2, 0.0f) + g_FlontPolygon[nCntFP].pos;
			// 色設定
			pVtx[0].col = g_FlontPolygon[nCntFP].col;
			pVtx[1].col = g_FlontPolygon[nCntFP].col;
			pVtx[2].col = g_FlontPolygon[nCntFP].col;
			pVtx[3].col = g_FlontPolygon[nCntFP].col;

		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffFlontPolygon->Unlock();

}

//=============================================================================
// タイトル描画処理
//=============================================================================
void DrawFlontPolygon(void)
{
	//変数宣言
	int nCntFlontPolygon;

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFlontPolygon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureFlontPolygon[g_FlontPolygon[nCntFlontPolygon].nTexNum]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
								   nCntFlontPolygon * 4,	//開始する頂点のインデックス
								   2);						//プリミティブの数
		}
	}
}

//=============================================================================
// 情報設定
//=============================================================================
int SetFlontPolygon(int nTexNum, D3DXVECTOR3 pos, float fWidth, float fHight, FLONTTYPE type)
{
	//変数宣言
	int nCntFlontPolygon;
	int nNumIndx = 0;
	float fHalfWidth = 0;		//幅
	float fHalfHight = 0;		//高さ

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFlontPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == false)
		{
			g_FlontPolygon[nCntFlontPolygon].pos = pos;				//中心座標
			g_FlontPolygon[nCntFlontPolygon].fHight = fHight;		//高さ
			g_FlontPolygon[nCntFlontPolygon].fWidth = fWidth;		//幅
			g_FlontPolygon[nCntFlontPolygon].type = type;			//タイプ
			g_FlontPolygon[nCntFlontPolygon].fUv = 0.0f;			//UV値

			//幅と高さを設定する
			fHalfWidth = g_FlontPolygon[nCntFlontPolygon].fWidth * 0.5f;
			fHalfHight = g_FlontPolygon[nCntFlontPolygon].fHight * 0.5f;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_FlontPolygon[nCntFlontPolygon].fWidth/2,-g_FlontPolygon[nCntFlontPolygon].fHight/2, 0.0f)+g_FlontPolygon[nCntFlontPolygon].pos;
			pVtx[1].pos = D3DXVECTOR3(g_FlontPolygon[nCntFlontPolygon].fWidth/2,-g_FlontPolygon[nCntFlontPolygon].fHight/2, 0.0f)+g_FlontPolygon[nCntFlontPolygon].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_FlontPolygon[nCntFlontPolygon].fWidth/2,g_FlontPolygon[nCntFlontPolygon].fHight/2, 0.0f)+g_FlontPolygon[nCntFlontPolygon].pos;
			pVtx[3].pos = D3DXVECTOR3(g_FlontPolygon[nCntFlontPolygon].fWidth/2,g_FlontPolygon[nCntFlontPolygon].fHight/2, 0.0f)+g_FlontPolygon[nCntFlontPolygon].pos;

			if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_CYARACTOR)
			{
				//答を設定する
				srand((unsigned int)time(0));
				int nChara = rand() % 5;			//キャラクターの設定

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.2f * nChara), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.2f + (0.2f * nChara), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.2f * nChara), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.2f + (0.2f * nChara), 1.0f);
			}
			else if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_FACE_HUMAN)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.2f, 1.0f);
			}
			else if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_FACE_TENGU)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.2f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.4f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.2f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.4f, 1.0f);
			}
			else if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_FACE_KAPPA)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.4f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.6f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.4f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.6f, 1.0f);
			}
			else if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_FACE_FOX)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.6f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.8f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.6f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.8f, 1.0f);
			}
			else if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_FACE_ROBOT)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.8f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.8f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_NARRATION)
			{
				g_FlontPolygon[nCntFlontPolygon].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			else if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_UI)
			{
				g_FlontPolygon[nCntFlontPolygon].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);

			}
			else
			{
				g_FlontPolygon[nCntFlontPolygon].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}

			g_FlontPolygon[nCntFlontPolygon].nTexNum = nTexNum;		//テクスチャの番号

			pVtx[0].col = g_FlontPolygon[nCntFlontPolygon].col;
			pVtx[1].col = g_FlontPolygon[nCntFlontPolygon].col;
			pVtx[2].col = g_FlontPolygon[nCntFlontPolygon].col;
			pVtx[3].col = g_FlontPolygon[nCntFlontPolygon].col;


			g_FlontPolygon[nCntFlontPolygon].bUse = true;			//使用している状態にする
			nNumIndx = nCntFlontPolygon;
			break;
		}

		//該当の位置まで進める
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffFlontPolygon->Unlock();

	return nNumIndx;
}

//=============================================================================
// テクスチャの設定
//=============================================================================
void SetTexture(int nIdx, int nNumComment)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFlontPolygon->Lock(0, 0, (void**)&pVtx, 0);

	if (g_FlontPolygon[nIdx].bUse == true)
	{
		pVtx += 4 * nIdx;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.25f * nNumComment), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f + (0.25f * nNumComment), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.25f * nNumComment), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f + (0.25f * nNumComment), 1.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffFlontPolygon->Unlock();
}

//=============================================================================
// ポリゴンをすべて消す
//=============================================================================
void  ReleaseAllFlontPolygon()
{
	//変数宣言
	int nCntFlontPolygon;

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == true)
		{
			g_FlontPolygon[nCntFlontPolygon].bUse = false;		//使用していない状態にする
		}
	}
}

//=============================================================================
// 特定のポリゴンを消す
//=============================================================================
void DeleteFlontPolygon(int nIdx)
{
	if (g_FlontPolygon[nIdx].bUse == true)
	{
		g_FlontPolygon[nIdx].bUse = false;		//使用していない状態にする
	}
}

//=============================================================================
// 情報を取得
//=============================================================================
FlontPolygon * GetFlontPolygon(void)
{
	return &g_FlontPolygon[0];
}