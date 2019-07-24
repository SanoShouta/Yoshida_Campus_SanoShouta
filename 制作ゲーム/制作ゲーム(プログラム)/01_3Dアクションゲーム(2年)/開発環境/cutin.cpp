//=============================================================================
//
// カットイン処理 [cutin.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "cutin.h"
#include "main.h"
#include "input.h"
#include "sound.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_SIZEX	(640)		//キャラクターポリゴンのX最大値
#define MAX_SIZEY	(110)		//キャラクターポリゴンのX最大値
#define MIN_SIZEY	(10)		//キャラクターポリゴンのY最小値
#define MOVE_X		(-12.0f)		//移動量
#define MOVESIZE_Y	(3.0f)		//サイズの変化量
#define INTERVAL	(15)		//インターバルタイム

#define MINSKILL_SIZE	(280)	//吹き出しのサイズ
#define MAXSKILL_SIZE	(560)	//吹き出しのサイズ
#define NOMALSKILL_SIZE	(350)	//吹き出しのサイズ
#define SKILL_MOVE		(10)	//サイズの変更料

#define POS				(D3DXVECTOR3(640, 360, 0))	//中心点
#define SIZE			(D3DXVECTOR3(640, 110, 0))	//サイズ
#define SIZE_X			(550)
#define SIZE_Y			(80)

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureCut[CUT_TEXTYPE_MAX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCut = NULL;					//頂点バッファへのポインタ
Cut						g_Cut[MAX_CUTIN];						//情報設定
int						g_nCutTime;								//時間カウンター
int						g_nId;									//Idの取得

//=============================================================================
// スタートボタン初期化処理
//=============================================================================
void InitCut(void)
{
	//変数宣言
	int     nCntCut;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数の初期化
	g_nCutTime = 0;
	g_nId = 0;
	for (nCntCut = 0; nCntCut < MAX_CUTIN; nCntCut++)
	{
		g_Cut[nCntCut].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//中心座標
		g_Cut[nCntCut].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//サイズ
		g_Cut[nCntCut].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
		g_Cut[nCntCut].chara = CHARATAYPE_MAX;					//キャラクタータイプ
		g_Cut[nCntCut].type = CUTTYPE_MAX;						//ポリゴンのタイプ
		g_Cut[nCntCut].nTexNum = 0;								//テクスチャの番号
		g_Cut[nCntCut].CutState = CUTSTATE_NONE;					//カットイン
		g_Cut[nCntCut].bUse = false;							//使用していない状態にする
		g_Cut[nCntCut].bMove = false;							//移動量のリセット
		g_Cut[nCntCut].cola = 1.0f;								//透明度

	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cutIn.png", &g_pTextureCut[0]);		//キャラクター
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cutin01.jpg", &g_pTextureCut[1]);	//黒色
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cutIn02.png", &g_pTextureCut[2]);	//吹き出し

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_CUTIN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCut,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCut->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCut = 0; nCntCut < MAX_CUTIN; nCntCut++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffCut->Unlock();
}

//=============================================================================
// タイトル終了処理
//=============================================================================
void UninitCut(void)
{
	//変数宣言
	int nCntTex;

	//テクスチャの破棄
	for (nCntTex = 0; nCntTex < CUT_TEXTYPE_MAX; nCntTex++)
	{
		if (g_pTextureCut[nCntTex] != NULL)
		{
			g_pTextureCut[nCntTex]->Release();
			g_pTextureCut[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffCut != NULL)
	{
		g_pVtxBuffCut->Release();
		g_pVtxBuffCut = NULL;
	}
}

//=============================================================================
// タイトル更新処理
//=============================================================================
void UpdateCut(void)
{
	//変数宣言
	int nCntCut;

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCut->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCut = 0; nCntCut < MAX_CUTIN; nCntCut++)
	{
		if (g_Cut[nCntCut].bUse == true)
		{
			if (g_Cut[nCntCut].type == CUTTYPE_KYARACTOR)
			{
				switch (g_Cut[nCntCut].CutState)
				{
				case CUTSTATE_IN:
					g_nId = nCntCut;								//Idの保管
					g_Cut[nCntCut].move.x += MOVE_X;				//移動量の加算
					g_Cut[nCntCut].pos.x += g_Cut[nCntCut].move.x;	//位置更新

					if (g_Cut[nCntCut].pos.x < MAX_SIZEX)
					{
						g_Cut[nCntCut].pos.x = MAX_SIZEX;	//位置修正
						g_nCutTime++;						//時間の加算
						g_Cut[nCntCut].move.x = 0;
						SetCut(2, D3DXVECTOR3(400, 360, 0), g_Cut[nCntCut].chara, CUTTYPE_SKILL);	//吹き出しのセット
						g_Cut[nCntCut].CutState = CUTSTATE_OPEN;
					}
					break;

				case CUTSTATE_OPEN:

					g_Cut[nCntCut].nTexNum = 0;					//テクスチャの変更
					g_Cut[nCntCut].move.x += MOVESIZE_Y;			//移動量の加算
					g_Cut[nCntCut].size.y += g_Cut[nCntCut].move.x;	//サイズの更新

					if (g_Cut[nCntCut].size.y > MAX_SIZEY)
					{
						g_Cut[nCntCut].size.y = MAX_SIZEY;
						g_nCutTime++;						//時間の加算

						g_Cut[nCntCut].move.x = 0;
						g_Cut[nCntCut].CutState = CUTSTATE_NOMAL;
					}
					break;

				case CUTSTATE_OUT:
					g_Cut[nCntCut].cola -= 0.2f;

					if (g_Cut[nCntCut].cola < 0.0f)
					{
						g_Cut[nCntCut].cola = 0.0f;
						g_Cut[nCntCut].bUse = false;
					}
					break;
				}
			}
			else if(g_Cut[nCntCut].type == CUTTYPE_SKILL)
			{
				switch (g_Cut[nCntCut].NameState)
				{
				case NAMESTATE_IN:
					//サイズの変更
					g_Cut[nCntCut].move.x += -30.0f;
					g_Cut[nCntCut].move.y += -30.0f;

					//サイズの更新
					g_Cut[nCntCut].size.x += g_Cut[nCntCut].move.x;
					g_Cut[nCntCut].size.y += g_Cut[nCntCut].move.y;

					//値修正
					if (g_Cut[nCntCut].size.x < MINSKILL_SIZE)
					{
						g_Cut[nCntCut].size.x = MINSKILL_SIZE;
						g_Cut[nCntCut].size.y = MINSKILL_SIZE;

						g_nCutTime++;						//時間の加算

						if ((g_nCutTime % 30) == 0)
						{
							g_Cut[nCntCut].NameState = NAMESTATE_OUT;
							SetCutState(CUTSTATE_OUT);
						}
					}
					break;

				case NAMESTATE_OUT:
					g_Cut[nCntCut].cola -= 0.2f;

					if(g_Cut[nCntCut].cola < 0.0f)
					{
						g_Cut[nCntCut].cola = 0.0f;
						g_Cut[nCntCut].bUse = false;
					}
					break;
				}
			}

			//座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x - g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y - g_Cut[nCntCut].size.y, 0);
			pVtx[1].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x + g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y - g_Cut[nCntCut].size.y, 0);
			pVtx[2].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x - g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y + g_Cut[nCntCut].size.y, 0);
			pVtx[3].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x + g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y + g_Cut[nCntCut].size.y, 0);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Cut[nCntCut].cola);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Cut[nCntCut].cola);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Cut[nCntCut].cola);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Cut[nCntCut].cola);
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffCut->Unlock();
}

//=============================================================================
// タイトル描画処理
//=============================================================================
void DrawCut(void)
{
	//変数宣言
	int nCntCut;

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCut, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntCut = 0; nCntCut < MAX_CUTIN; nCntCut++)
	{
		if (g_Cut[nCntCut].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureCut[g_Cut[nCntCut].nTexNum]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
				nCntCut * 4,	//開始する頂点のインデックス
				2);						//プリミティブの数
		}
	}
}

//=============================================================================
// 情報設定
//=============================================================================
int SetCut(int nTexNum, D3DXVECTOR3 pos, CHARATAYPE chara, CUTTYPE type)
{
	//変数宣言
	int nCntCut;
	int nNumIndx = 0;
	float fHalfWidth = 0;		//幅
	float fHalfHight = 0;		//高さ

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCut->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCut = 0; nCntCut < MAX_CUTIN; nCntCut++)
	{
		if (g_Cut[nCntCut].bUse == false)
		{
			g_Cut[nCntCut].pos = pos;								//中心座標
			g_Cut[nCntCut].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
			g_Cut[nCntCut].chara= chara;							//キャラクタータイプ
			g_Cut[nCntCut].type = type;								//ポリゴンのタイプ
			g_Cut[nCntCut].bMove = false;							//移動量のリセット
			g_Cut[nCntCut].CutState = CUTSTATE_NONE;				//カットインの状態
			g_Cut[nCntCut].NameState = NAMESTATE_NONE;				//カットインの状態
			g_Cut[nCntCut].cola = 1.0f;								//透明度

			if (g_Cut[nCntCut].chara == CHARATAYPE_HUMAN)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.2f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.2f);
			}
			else if (g_Cut[nCntCut].chara == CHARATAYPE_TENGU)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.2f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.2f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.4f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.4f);
			}
			else if (g_Cut[nCntCut].chara == CHARATAYPE_KAPPA)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.4f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.4f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.6f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.6f);
			}
			else if (g_Cut[nCntCut].chara == CHARATAYPE_FOX)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.6f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.6f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.8f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.8f);
			}
			else if (g_Cut[nCntCut].chara == CHARATAYPE_ROBOT)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.8f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.8f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}

			switch (g_Cut[nCntCut].type)
			{
			case CUTTYPE_KYARACTOR:
				PlaySound(SOUND_CUTIN);
				//サイズの設定
				g_Cut[nCntCut].size = D3DXVECTOR3(MAX_SIZEX, MIN_SIZEY, 0.0f);
				g_Cut[nCntCut].CutState = CUTSTATE_IN;		//入る状態に設定する
				break;

			case CUTTYPE_SKILL:
				PlaySound(SOUND_SPECIALROGO);
				//サイズの設定
				g_Cut[nCntCut].size = D3DXVECTOR3(MAXSKILL_SIZE, MAXSKILL_SIZE, 0.0f);
				g_Cut[nCntCut].NameState = NAMESTATE_IN;		//入る状態に設定する
				break;
			}

			//テクスチャ座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x - g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y - g_Cut[nCntCut].size.y, 0);
			pVtx[1].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x + g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y - g_Cut[nCntCut].size.y, 0);
			pVtx[2].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x - g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y + g_Cut[nCntCut].size.y, 0);
			pVtx[3].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x + g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y + g_Cut[nCntCut].size.y, 0);

			g_Cut[nCntCut].nTexNum = nTexNum;		//テクスチャの番号

			g_Cut[nCntCut].bUse = true;			//使用している状態にする
			nNumIndx = nCntCut;
			break;
		}

		//該当の位置まで進める
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffCut->Unlock();

	return nNumIndx;
}

//=============================================================================
// 特定のポリゴンを消す
//=============================================================================
void DeleteAllCut(void)
{
	for (int nCntCut = 0; nCntCut < MAX_CUTIN; nCntCut++)
	{
		g_Cut[nCntCut].bUse = false;
	}
}

//=============================================================================
// 情報を取得
//=============================================================================
Cut * GetCut(void)
{
	return &g_Cut[0];
}

//=============================================================================
//　状態の設定
//=============================================================================
void SetCutState(CUTSTATE state)
{
	g_Cut[g_nId].CutState = state;
}