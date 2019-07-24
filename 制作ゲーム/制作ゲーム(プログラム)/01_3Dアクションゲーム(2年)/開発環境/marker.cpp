//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// キャラクターセレクト処理 [marker.cpp]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "main.h"
#include "input.h"
#include "marker.h"
#include "cursor.h"
#include "charsel.h"
#include "gamepad.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// グローバル変数
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
LPDIRECT3DTEXTURE9		g_pTextureMarker[MARKER_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMarker = NULL;
MARKER					g_aMarker[MARKER_MAX];
int						g_nTotalMarker;										// マーカーの置いてる総数
bool					g_bCharColType[PLAYERTYPE_MAX][PLAYERCOLOR_MAX];	// マーカーを置かれたときの色切り替え

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// マーカーの初期化処理
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitMarker(void)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	LPDIRECT3DDEVICE9 pDevice;

	for (int nCntMarker = 0; nCntMarker < MARKER_MAX; nCntMarker++)
	{
		g_aMarker[nCntMarker].pos = D3DXVECTOR3(300.0f, 250.0f, 0.0f);
		g_aMarker[nCntMarker].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMarker[nCntMarker].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMarker[nCntMarker].fWidth = MARKER_WIDTH;
		g_aMarker[nCntMarker].fHeight = MARKER_HEIGHT;
		g_aMarker[nCntMarker].type = PLAYERTYPE_MAX;
		g_aMarker[nCntMarker].bUse = false;
	}
	g_aMarker[0].pos = D3DXVECTOR3(180.0f, 180.0f, 0.0f);
	g_aMarker[1].pos = D3DXVECTOR3(1100.0f, 180.0f, 0.0f);
	g_aMarker[2].pos = D3DXVECTOR3(180.0f, 540.0f, 0.0f);
	g_aMarker[3].pos = D3DXVECTOR3(1100.0f, 540.0f, 0.0f);

	for (int nCntCharType = 0; nCntCharType < PLAYERTYPE_MAX; nCntCharType++)
	{
		for (int nCntColType = 0; nCntColType < PLAYERCOLOR_MAX; nCntColType++)
		{
			g_bCharColType[nCntCharType][nCntColType] = false;
		}
	}
	g_nTotalMarker = 0;
	//デバイスの所得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		MARKER_TEXTURENAME0,
		&g_pTextureMarker[0]);
	D3DXCreateTextureFromFile(pDevice,
		MARKER_TEXTURENAME1,
		&g_pTextureMarker[1]);
	D3DXCreateTextureFromFile(pDevice,
		MARKER_TEXTURENAME2,
		&g_pTextureMarker[2]);
	D3DXCreateTextureFromFile(pDevice,
		MARKER_TEXTURENAME3,
		&g_pTextureMarker[3]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_MARKERTOP * MARKER_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMarker,
		NULL);

	//頂点lバッファをロックし頂点データへのポインタを取得
	g_pVtxBuffMarker->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMarker = 0; nCntMarker < MARKER_MAX; nCntMarker++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x - g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y - g_aMarker[nCntMarker].fHeight / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x + g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y - g_aMarker[nCntMarker].fHeight / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x - g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y + g_aMarker[nCntMarker].fHeight / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x + g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y + g_aMarker[nCntMarker].fHeight / 2, 0.0f);
		//rhw
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//色
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
	//頂点バッファをアンロック
	g_pVtxBuffMarker->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// マーカーの終了処理
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitMarker(void)
{
	for (int nCntTex = 0; nCntTex < MARKER_MAX; nCntTex++)
	{
		//テクスチャの破棄
		if (g_pTextureMarker[nCntTex] != NULL)
		{
			g_pTextureMarker[nCntTex]->Release();
			g_pTextureMarker[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMarker != NULL)
	{
		g_pVtxBuffMarker->Release();
		g_pVtxBuffMarker = NULL;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// マーカーの更新処理
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateMarker(void)
{
	CURSOR *pCarsor = GetCursors();
	int nNumGamePad = GetGamePadNum();
	for (int nCntMarker = 0; nCntMarker < MARKER_MAX; nCntMarker++)
	{
		g_aMarker[nCntMarker].posOld = g_aMarker[nCntMarker].pos;		// 前回の座標を入れる

		g_aMarker[nCntMarker].pos.x += g_aMarker[nCntMarker].move.x;	// 横移動
		g_aMarker[nCntMarker].pos.y += g_aMarker[nCntMarker].move.y;	// 縦移動

		// 慣性
		g_aMarker[nCntMarker].move.x += (0.0f - g_aMarker[nCntMarker].move.x) * 0.3f;
		g_aMarker[nCntMarker].move.y += (0.0f - g_aMarker[nCntMarker].move.y) * 0.3f;

		//枠外に出れなくする
		if (g_aMarker[nCntMarker].pos.x < g_aMarker[nCntMarker].fWidth / 2)
		{	// 左
			g_aMarker[nCntMarker].pos.x = g_aMarker[nCntMarker].fWidth / 2;
		}
		if (g_aMarker[nCntMarker].pos.x > SCREEN_WIDTH - g_aMarker[nCntMarker].fWidth / 2)
		{	// 右
			g_aMarker[nCntMarker].pos.x = SCREEN_WIDTH - g_aMarker[nCntMarker].fWidth / 2;
		}
		if (g_aMarker[nCntMarker].pos.y < g_aMarker[nCntMarker].fHeight / 2)
		{	// 上
			g_aMarker[nCntMarker].pos.y = g_aMarker[nCntMarker].fHeight / 2;
		}
		if (g_aMarker[nCntMarker].pos.y > SCREEN_HEIGHT - g_aMarker[nCntMarker].fHeight / 2)
		{	// 下
			g_aMarker[nCntMarker].pos.y = SCREEN_HEIGHT - g_aMarker[nCntMarker].fHeight / 2;
		}

		Player *pPlayer = GetPlayer();

		if (pCarsor[nCntMarker].state == CURSORSTATE_RELEASE_START)
		{// キャラクターを選択し始めのとき(置いたとき)
			for (int nCntColor = 0; nCntColor < PLAYERCOLOR_MAX; nCntColor++)
			{
 				g_aMarker[nCntMarker].type = CollisionCharsel(g_aMarker[nCntMarker].pos, g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].fHeight / 2, g_aMarker[nCntMarker].type);
				if (g_bCharColType[g_aMarker[nCntMarker].type][nCntColor] == false)
				{// プレイヤーの配色
					pPlayer[nCntMarker].colType = (PLAYERCOLOR)nCntColor;

					if (g_aMarker[nCntMarker].type != PLAYERTYPE_MAX)
					{// プレイヤーセット
						PlaySound(SOUND_CHARACTOR_SELECT);
						SetPlayer(nCntMarker, D3DXVECTOR3(nCntMarker * 50.0f, 0, 0), g_aMarker[nCntMarker].type);
						SetTypePlayer(nCntMarker, g_aMarker[nCntMarker].type);
					}
					g_bCharColType[g_aMarker[nCntMarker].type][nCntColor] = true;
					break;
				}
			}
		}
		else if (pCarsor[nCntMarker].state == CURSORSTATE_RELEASE)
		{// キャラクターを選択したとき(置いてるとき)
			if (g_aMarker[nCntMarker].bUse == false)
			{
				g_nTotalMarker++;	// 選択した分を加算
				g_aMarker[nCntMarker].bUse = true;
			}
		}
		else
		{// 選択していないとき(置いてないとき)
			if (g_aMarker[nCntMarker].bUse == true)
			{
				g_aMarker[nCntMarker].bUse = false;
			}
				ReleasePlayer(nCntMarker);
				SetTypePlayer(nCntMarker, g_aMarker[nCntMarker].type);

			if (g_bCharColType[g_aMarker[nCntMarker].type][pPlayer[nCntMarker].colType] == true)
			{
				g_bCharColType[g_aMarker[nCntMarker].type][pPlayer[nCntMarker].colType] = false;
				g_aMarker[nCntMarker].type = PLAYERTYPE_MAX;
			}
		}

		if (g_nTotalMarker >= nNumGamePad)
		{// 総数が刺さっているゲームパッド以上のとき
			g_nTotalMarker = nNumGamePad;
		}
		if (pCarsor[nCntMarker].state == CURSORSTATE_CATCH&&
			pCarsor[nCntMarker].stateOld == CURSORSTATE_RELEASE)
		{// さっきまで置いていて、今持った時（選択をやめた瞬間）
			g_nTotalMarker--;	// 選択をやめた分減算
			if (g_nTotalMarker <= 0)
			{// 総数が0以下になったとき
				g_nTotalMarker = 0;
			}
		}
	}
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点lバッファをロックし頂点データへのポインタを取得
	g_pVtxBuffMarker->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMarker = 0; nCntMarker < MARKER_MAX; nCntMarker++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x - g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y - g_aMarker[nCntMarker].fHeight / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x + g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y - g_aMarker[nCntMarker].fHeight / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x - g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y + g_aMarker[nCntMarker].fHeight / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x + g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y + g_aMarker[nCntMarker].fHeight / 2, 0.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffMarker->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// マーカーの描画処理
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawMarker(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを所得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMarker, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntMarker = 0; nCntMarker < MARKER_MAX; nCntMarker++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMarker[nCntMarker]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntMarker * MAX_MARKERTOP,
			2);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// マーカーの取得
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
MARKER *GetMarker(void)
{
	return &g_aMarker[0];
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// マーカーの取得
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int GetNumMarker(void)
{
	return g_nTotalMarker;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 色を使用しているのかをセット
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetColSel(bool bColSel, int nIdy, int nColId)
{
	g_bCharColType[g_aMarker[nIdy].type][nColId] = bColSel;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 色を使用しているのかを取得
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool GetColSel(int nIdy, int nColId)
{
	return g_bCharColType[g_aMarker[nIdy].type][nColId];

}