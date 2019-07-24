//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// イベントロゴ処理 [ eventlogo.cpp ]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "eventlogo.h"
#include "input.h"
#include "gamepad.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 構造体定義
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct
{
	char *pFileName;
	EVENTLOGOTEX type;
}EventlogoTexture;

typedef struct
{
	EVENTLOGOTEX texType;
	EVENTTYPE eventType;
}EventTypeInfo;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// グローバル変数
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
VERTEX_2D				g_aVertexEventlogo;
LPDIRECT3DTEXTURE9		g_pTextureEventlogo[EVENTLOGOTEX_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEventlogo = NULL;
EVENTLOGO				g_Eventlogo[EVENTTYPE_MAX];

EventlogoTexture g_aEventlogoTexInfo[EVENTLOGOTEX_MAX] =
{
	{ " ",										EVENTLOGOTEX_NONE },			// 何もない
	{ "data/TEXTURE/Event_Flood4-2.png",		EVENTLOGOTEX_WATER },			// 洪水
	{ "data/TEXTURE/Event_Fire002.png",			EVENTLOGOTEX_FIRE },			// 火事
	{ "data/TEXTURE/Event_Fall_Rock001.png",	EVENTLOGOTEX_FALLING_ROCK },	// 落石
	{ "data/TEXTURE/Event_Meteo003.png",		EVENTLOGOTEX_METEORITE },		// 隕石
	{ "data/TEXTURE/Event_Rain cloud004.png",	EVENTLOGOTEX_RAIN },			// 雨
	{ "data/TEXTURE/Event_Lightning4-3.png",	EVENTLOGOTEX_THUNDER },			// 雷
	{ "data/TEXTURE/Event_Fall_Obj000.png",		EVENTLOGOTEX_FALLING_OBJECT },	// 落下
	{ "data/TEXTURE/Event_Gust4-1.png",			EVENTLOGOTEX_GUST },			// 突風
};

EventTypeInfo g_aEventTypeInfo[EVENTTYPE_MAX] =
{
	{ EVENTLOGOTEX_NONE,			EVENTTYPE_NONE },				// 何もない
	{ EVENTLOGOTEX_WATER,			EVENTTYPE_WATER },				// 洪水
	{ EVENTLOGOTEX_FIRE,			EVENTTYPE_FIRE },				// 火事
	{ EVENTLOGOTEX_FALLING_ROCK,	EVENTTYPE_FALLING_ROCK },		// 複数の落石
	{ EVENTLOGOTEX_FALLING_ROCK,	EVENTTYPE_FALLING_BIGROCK },	// 大きい岩の落石
	{ EVENTLOGOTEX_METEORITE,		EVENTTYPE_METEORSHOWER },		// 流星群
	{ EVENTLOGOTEX_METEORITE,		EVENTTYPE_METEORITE },			// 隕石
	{ EVENTLOGOTEX_RAIN,			EVENTTYPE_RAIN },				// 雨で見えにくく
	{ EVENTLOGOTEX_THUNDER,			EVENTTYPE_THUNDER },			// 雷
	{ EVENTLOGOTEX_FALLING_OBJECT,	EVENTTYPE_FALLING_CHOUTIN },	// 提灯落下
	{ EVENTLOGOTEX_FALLING_OBJECT,	EVENTTYPE_FALLING_BRANCH },		// 木の枝落下
	{ EVENTLOGOTEX_GUST,			EVENTTYPE_LEEF },				// 葉っぱで見えにくく
	{ EVENTLOGOTEX_GUST,			EVENTTYPE_GUST },				// 突風
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// イベントロゴの初期化
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitEventlogo(void)
{
	VERTEX_2D*pVtx;		// 頂点情報へのポインタ

	LPDIRECT3DDEVICE9 pDevice;
	// デバイスの所得
	pDevice = GetDevice();
	// テクスチャの読み込み
	for (int nCntEventlogoTex = 0; nCntEventlogoTex < EVENTLOGOTEX_MAX; nCntEventlogoTex++)
	{// テクスチャ分
		D3DXCreateTextureFromFile(pDevice,
			g_aEventlogoTexInfo[nCntEventlogoTex].pFileName,
			&g_pTextureEventlogo[nCntEventlogoTex]);
	}
	for (int nCntEventlogo = 0; nCntEventlogo < EVENTTYPE_MAX; nCntEventlogo++)
	{// イベント数分
		g_Eventlogo[nCntEventlogo].pos = D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f);
		g_Eventlogo[nCntEventlogo].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Eventlogo[nCntEventlogo].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Eventlogo[nCntEventlogo].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		g_Eventlogo[nCntEventlogo].fWidth = EVENTLOGO_WIDTH;
		g_Eventlogo[nCntEventlogo].fHeight = EVENTLOGO_HEIGHT;
		g_Eventlogo[nCntEventlogo].bAlpha = false;
		g_Eventlogo[nCntEventlogo].nCountDiaplay = 0;
		g_Eventlogo[nCntEventlogo].nNumTimes = 0;
		g_Eventlogo[nCntEventlogo].bUse = false;
		g_Eventlogo[nCntEventlogo].type = g_aEventTypeInfo[nCntEventlogo].eventType;
		g_Eventlogo[nCntEventlogo].texType = g_aEventTypeInfo[nCntEventlogo].texType;
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * EVENTLOGO_MAX * EVENTTYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEventlogo,
		NULL);

	// 頂点lバッファをロックし頂点データへのポインタを取得
	g_pVtxBuffEventlogo->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEventlogo = 0; nCntEventlogo < EVENTTYPE_MAX; nCntEventlogo++, pVtx += 4)
	{
		// 座標
		pVtx[0].pos = D3DXVECTOR3(g_Eventlogo[nCntEventlogo].pos.x - g_Eventlogo[nCntEventlogo].fWidth, g_Eventlogo[nCntEventlogo].pos.y - g_Eventlogo[nCntEventlogo].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Eventlogo[nCntEventlogo].pos.x + g_Eventlogo[nCntEventlogo].fWidth, g_Eventlogo[nCntEventlogo].pos.y - g_Eventlogo[nCntEventlogo].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Eventlogo[nCntEventlogo].pos.x - g_Eventlogo[nCntEventlogo].fWidth, g_Eventlogo[nCntEventlogo].pos.y + g_Eventlogo[nCntEventlogo].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Eventlogo[nCntEventlogo].pos.x + g_Eventlogo[nCntEventlogo].fWidth, g_Eventlogo[nCntEventlogo].pos.y + g_Eventlogo[nCntEventlogo].fHeight, 0.0f);

		// rhw
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 色
		pVtx[0].col = g_Eventlogo[nCntEventlogo].col;
		pVtx[1].col = g_Eventlogo[nCntEventlogo].col;
		pVtx[2].col = g_Eventlogo[nCntEventlogo].col;
		pVtx[3].col = g_Eventlogo[nCntEventlogo].col;

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロック
	g_pVtxBuffEventlogo->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// イベントロゴの終了処理
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitEventlogo(void)
{
	// テクスチャの破棄
	for (int nCntEventlogo = 0; nCntEventlogo < EVENTLOGOTEX_MAX; nCntEventlogo++)
	{
		if (g_pTextureEventlogo[nCntEventlogo] != NULL)
		{
			g_pTextureEventlogo[nCntEventlogo]->Release();
			g_pTextureEventlogo[nCntEventlogo] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffEventlogo != NULL)
	{
		g_pVtxBuffEventlogo->Release();
		g_pVtxBuffEventlogo = NULL;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// イベントロゴの更新処理
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateEventlogo(void)
{
	VERTEX_2D *pVtx;		//頂点情報へのポインタ
	// 頂点lバッファをロックし頂点データへのポインタを取得
	g_pVtxBuffEventlogo->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEventlogo = 0; nCntEventlogo < EVENTTYPE_MAX; nCntEventlogo++, pVtx += 4)
	{
		if (g_Eventlogo[nCntEventlogo].bUse == true)
		{
			if (g_Eventlogo[nCntEventlogo].nNumTimes < EVENTLOGO_NUMTIMES)
			{// 一定数より小さいとき
				if (g_Eventlogo[nCntEventlogo].bAlpha == true)
				{// 表示してるとき
					g_Eventlogo[nCntEventlogo].col.a -= EVENTLOGO_APPEARSPEED;		// 透明度の減算
					if (g_Eventlogo[nCntEventlogo].col.a <= 0.0f)
					{// 透明度が 0 以下になったとき
						g_Eventlogo[nCntEventlogo].bAlpha = false;					// 表示してる状態にする
						g_Eventlogo[nCntEventlogo].nNumTimes++;	  					// 表示するカウントを加算
					}
				}
				else if (g_Eventlogo[nCntEventlogo].bAlpha == false)
				{// 表示してないとき
					g_Eventlogo[nCntEventlogo].col.a += EVENTLOGO_APPEARSPEED;		// 透明度の加算
					if (g_Eventlogo[nCntEventlogo].col.a >= 1.0f)
					{// 透明度が 1 以上のとき
						g_Eventlogo[nCntEventlogo].nCountDiaplay++;					// 表示中のカウントを加算
						if (g_Eventlogo[nCntEventlogo].nCountDiaplay >= 15)
						{// 一定時間経ったとき
							g_Eventlogo[nCntEventlogo].bAlpha = true;				// 表示してる状態にする
							g_Eventlogo[nCntEventlogo].nCountDiaplay = 0;			// 表示中のカウントを初期化する
						}
					}
				}
			}
			else
			{// 定められた回数を超えたとき
				g_Eventlogo[nCntEventlogo].bUse = false;
				g_Eventlogo[nCntEventlogo].nNumTimes = 0;
			}
		}
		// 頂点座標
		pVtx[0].col = g_Eventlogo[nCntEventlogo].col;
		pVtx[1].col = g_Eventlogo[nCntEventlogo].col;
		pVtx[2].col = g_Eventlogo[nCntEventlogo].col;
		pVtx[3].col = g_Eventlogo[nCntEventlogo].col;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffEventlogo->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// イベントロゴの描画処理
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawEventlogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスを所得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEventlogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEventlogo = 0; nCntEventlogo < EVENTTYPE_MAX; nCntEventlogo++)
	{
		if (g_Eventlogo[nCntEventlogo].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEventlogo[g_Eventlogo[nCntEventlogo].texType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEventlogo * EVENTLOGO_MAX,
				2);
		}
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// イベントロゴの設定
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetEventlogo(D3DXVECTOR3 pos, float fWidth, float fHeight, EVENTTYPE type)
{
	g_Eventlogo[type].pos = pos;
	g_Eventlogo[type].fWidth = fWidth;
	g_Eventlogo[type].fHeight = fHeight;
	g_Eventlogo[type].type = type;
	g_Eventlogo[type].bUse = true;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// イベントロゴ解除
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DeleteEventLogo(void)
{
	for (int nCntEventlogo = 0; nCntEventlogo < EVENTTYPE_MAX; nCntEventlogo++)
	{
		if (g_Eventlogo[nCntEventlogo].bUse == true)
		{
			g_Eventlogo[nCntEventlogo].bUse = false;
		}
	}
}