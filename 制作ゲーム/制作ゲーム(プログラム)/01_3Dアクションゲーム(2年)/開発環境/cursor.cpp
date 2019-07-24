//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// カーソル処理 [ cursor.cpp ]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "cursor.h"
#include "input.h"
#include "marker.h"
#include "charsel.h"
#include "gamepad.h"
#include "fade.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// マクロ定義
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define MAX_CURSORTOP			(4)								// 頂点数
#define CURSOR_TEXTURENAME0		"data/TEXTURE/Cursor000.png"	// 読み込むテクスチャの名前
#define CURSOR_TEXTURENAME1		"data/TEXTURE/Cursor001.png"	// 読み込むテクスチャの名前
#define CURSOR_TEXTURENAME2		"data/TEXTURE/Cursor002.png"	// 読み込むテクスチャの名前
#define CURSOR_TEXTURENAME3		"data/TEXTURE/Cursor003.png"	// 読み込むテクスチャの名前
#define GRAVITY_PLUS			(2.5f)							// 重力
#define MOVE_SPEED				(3.0f)							// 動く速度

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// グローバル変数
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
VERTEX_2D				g_aVertexCursor[MAX_CURSORTOP];
LPDIRECT3DTEXTURE9		g_pTextureCursor[CURSOR_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCursor = NULL;
CURSOR					g_aCursor[CURSOR_MAX];

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ポリゴンの初期化
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitCursor(void)
{
	VERTEX_2D*pVtx;		// 頂点情報へのポインタ

	LPDIRECT3DDEVICE9 pDevice;

	g_aCursor[0].pos = D3DXVECTOR3(180.0f, 180.0f, 0.0f);
	g_aCursor[1].pos = D3DXVECTOR3(1100.0f, 180.0f, 0.0f);
	g_aCursor[2].pos = D3DXVECTOR3(180.0f, 540.0f, 0.0f);
	g_aCursor[3].pos = D3DXVECTOR3(1100.0f, 540.0f, 0.0f);

	for (int nCntCursor = 0; nCntCursor < CURSOR_MAX; nCntCursor++)
	{
		g_aCursor[nCntCursor].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCursor[nCntCursor].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCursor[nCntCursor].fWidth = CURSOR_WIDTH;
		g_aCursor[nCntCursor].fHeight = CURSOR_HEIGHT;
		g_aCursor[nCntCursor].nPatternAnim = 1;
		g_aCursor[nCntCursor].nNowChar = CHARSELTYPE_NONE;
		g_aCursor[nCntCursor].nCounter = 0;
		g_aCursor[nCntCursor].state = CURSORSTATE_CATCH;
		g_aCursor[nCntCursor].stateOld = CURSORSTATE_CATCH;
		g_aCursor[nCntCursor].colorType = PLAYERCOLOR_STANDARD;
		g_aCursor[nCntCursor].bColor = true;
	}
	// デバイスの所得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		CURSOR_TEXTURENAME0,
		&g_pTextureCursor[0]);

	D3DXCreateTextureFromFile(pDevice,
		CURSOR_TEXTURENAME1,
		&g_pTextureCursor[1]);

	D3DXCreateTextureFromFile(pDevice,
		CURSOR_TEXTURENAME2,
		&g_pTextureCursor[2]);

	D3DXCreateTextureFromFile(pDevice,
		CURSOR_TEXTURENAME3,
		&g_pTextureCursor[3]);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_CURSORTOP * CURSOR_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCursor,
		NULL);

	// 頂点lバッファをロックし頂点データへのポインタを取得
	g_pVtxBuffCursor->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCursor = 0; nCntCursor < CURSOR_MAX; nCntCursor++)
	{
		// 座標
		pVtx[0].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x - g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y - g_aCursor[nCntCursor].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x + g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y - g_aCursor[nCntCursor].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x - g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y + g_aCursor[nCntCursor].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x + g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y + g_aCursor[nCntCursor].fHeight, 0.0f);

		// rhw
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 色
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffCursor->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 終了処理
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitCursor(void)
{
	for (int nCntTex = 0; nCntTex < CURSOR_MAX; nCntTex++)
	{
		// テクスチャの破棄
		if (g_pTextureCursor[nCntTex] != NULL)
		{
			g_pTextureCursor[nCntTex]->Release();
			g_pTextureCursor[nCntTex] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffCursor != NULL)
	{
		g_pVtxBuffCursor->Release();
		g_pVtxBuffCursor = NULL;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 更新処理
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateCursor(void)
{
	MARKER *pMarker = GetMarker();
	GamePad *pGamePad = GetgamePadStick();
	if (GetFade() == FADE_NONE)
	{
		for (int nCntCursor = 0; nCntCursor < CURSOR_MAX; nCntCursor++)
		{
			if (g_aCursor[nCntCursor].stateOld != g_aCursor[nCntCursor].state)
			{
				g_aCursor[nCntCursor].nCounter = 10;
			}

			g_aCursor[nCntCursor].posOld = g_aCursor[nCntCursor].pos;			// 前回の座標を入れる
			g_aCursor[nCntCursor].stateOld = g_aCursor[nCntCursor].state;

			switch (g_aCursor[nCntCursor].state)
			{
			case CURSORSTATE_CATCH:
				pMarker[nCntCursor].move = g_aCursor[nCntCursor].move;
				g_aCursor[nCntCursor].nCounter--;
				if (g_aCursor[nCntCursor].nCounter > 0)
				{
					pMarker[nCntCursor].pos.x += ((g_aCursor[nCntCursor].pos.x - 30) - (pMarker[nCntCursor].pos.x)) * 0.3f;
					pMarker[nCntCursor].pos.y += (g_aCursor[nCntCursor].pos.y - pMarker[nCntCursor].pos.y)*0.3f;
				}
				else
				{
					pMarker[nCntCursor].pos.x = g_aCursor[nCntCursor].pos.x - 30;
					pMarker[nCntCursor].pos.y = g_aCursor[nCntCursor].pos.y;
				}
				break;
			case CURSORSTATE_RELEASE_START:
				g_aCursor[nCntCursor].state = CURSORSTATE_RELEASE;
				break;
			case CURSORSTATE_RELEASE:
				break;
			}
			// カーソル操作処理
			SetOperation(nCntCursor);

			g_aCursor[nCntCursor].pos.x += g_aCursor[nCntCursor].move.x;	// 横移動
			g_aCursor[nCntCursor].pos.y += g_aCursor[nCntCursor].move.y;	// 縦移動

			// 慣性
			g_aCursor[nCntCursor].move.x += (0.0f - g_aCursor[nCntCursor].move.x) * 0.3f;
			g_aCursor[nCntCursor].move.y += (0.0f - g_aCursor[nCntCursor].move.y) * 0.2f;

			// 枠外に出れなくする
			if (g_aCursor[nCntCursor].pos.x < g_aCursor[nCntCursor].fWidth)
			{	// 左
				g_aCursor[nCntCursor].pos.x = g_aCursor[nCntCursor].fWidth;
			}
			if (g_aCursor[nCntCursor].pos.x > SCREEN_WIDTH - g_aCursor[nCntCursor].fWidth)
			{	// 右
				g_aCursor[nCntCursor].pos.x = SCREEN_WIDTH - g_aCursor[nCntCursor].fWidth;
			}
			if (g_aCursor[nCntCursor].pos.y < g_aCursor[nCntCursor].fHeight)
			{	// 上
				g_aCursor[nCntCursor].pos.y = g_aCursor[nCntCursor].fHeight;
			}
			if (g_aCursor[nCntCursor].pos.y > SCREEN_HEIGHT - g_aCursor[nCntCursor].fHeight)
			{	// 下
				g_aCursor[nCntCursor].pos.y = SCREEN_HEIGHT - g_aCursor[nCntCursor].fHeight;
			}
		}

		for (int nIdy = 0; nIdy < MAX_GAMEPAD; nIdy++)
		{// ゲームパッド
			if (pGamePad[nIdy].pDevGamePad != NULL)
			{
				if (GetGamePadTrigger(nIdy, BUTTON_B))
				{
					if (g_aCursor[nIdy].state == CURSORSTATE_CATCH)
					{// 掴む
						g_aCursor[nIdy].state = CURSORSTATE_RELEASE_START;		// 状態を切り替える
						g_aCursor[nIdy].nPatternAnim = 0;					// テクスチャ切り替え
					}
					else if (g_aCursor[nIdy].state == CURSORSTATE_RELEASE)
					{// 放す
						g_aCursor[nIdy].state = CURSORSTATE_CATCH;			// 状態を切り替える
						g_aCursor[nIdy].nPatternAnim = 1;					// テクスチャ切り替え
					}
				}
				if (GetGamePadTrigger(nIdy, BUTTON_A))
				{
					if (g_aCursor[nIdy].state == CURSORSTATE_RELEASE)
					{// 放す
						g_aCursor[nIdy].state = CURSORSTATE_CATCH;			// 状態を切り替える
						g_aCursor[nIdy].nPatternAnim = 1;					// テクスチャ切り替え
					}
				}
				if (g_aCursor[nIdy].state == CURSORSTATE_RELEASE)
				{// 放している時(マーカーを置いてるとき)
					Player *pPlayer = GetPlayer();

					if (GetGamePadTrigger(nIdy, BUTTON_Y))
					{// 色の変更
						g_aCursor[nIdy].colorType = pPlayer[nIdy].colType;	// プレイヤーの色を入れる
						SetColSel(false, nIdy, g_aCursor[nIdy].colorType);	// 元の色を false にする
						g_aCursor[nIdy].colorType++;						// 色の種類を変える
						if (g_aCursor[nIdy].colorType >= PLAYERCOLOR_MAX)
						{// 色の種類を超えたとき
							g_aCursor[nIdy].colorType = 0;
						}

						if (false == GetColSel(nIdy, g_aCursor[nIdy].colorType))
						{// 色が使われていなかったら
							SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// 新しい色を true にする
						}
						else if (true == GetColSel(nIdy, g_aCursor[nIdy].colorType))
						{// 色が使われていたら
							do
							{
								g_aCursor[nIdy].colorType++;						// 色を変える
								if (g_aCursor[nIdy].colorType >= PLAYERCOLOR_MAX)
								{// 色の種類を超えたとき
									g_aCursor[nIdy].colorType = 0;
								}

							} while (false != GetColSel(nIdy, g_aCursor[nIdy].colorType));
							SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// 新しい色を true にする
						}

						if (g_aCursor[nIdy].colorType == PLAYERCOLOR_STANDARD)
						{// 初期色のとき
							pPlayer[nIdy].colType = PLAYERCOLOR_STANDARD;
						}
						else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF1)
						{// 違う色のとき
							pPlayer[nIdy].colType = PLAYERCOLOR_DIF1;
						}
						else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF2)
						{// 違う色のとき
							pPlayer[nIdy].colType = PLAYERCOLOR_DIF2;
						}
						else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF3)
						{// 違う色のとき
							pPlayer[nIdy].colType = PLAYERCOLOR_DIF3;
						}
					}
					else if (GetGamePadTrigger(nIdy, BUTTON_X))
					{// カラー変更
						g_aCursor[nIdy].colorType = pPlayer[nIdy].colType;	// プレイヤーの色を入れる
						SetColSel(false, nIdy, g_aCursor[nIdy].colorType);	// 元の色を false にする
						g_aCursor[nIdy].colorType--;						// 色の種類を変える
						if (g_aCursor[nIdy].colorType < 0)
						{// 色の種類を超えたとき
							g_aCursor[nIdy].colorType = PLAYERCOLOR_DIF3;
						}

						if (false == GetColSel(nIdy, g_aCursor[nIdy].colorType))
						{// 色が使われていなかったら
							SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// 新しい色を true にする
						}
						else if (true == GetColSel(nIdy, g_aCursor[nIdy].colorType))
						{// 色が使われていたら
							do
							{
								g_aCursor[nIdy].colorType++;						// 色を変える
								if (g_aCursor[nIdy].colorType >= PLAYERCOLOR_MAX)
								{// 色の種類を超えたとき
									g_aCursor[nIdy].colorType = 0;
								}

							} while (false != GetColSel(nIdy, g_aCursor[nIdy].colorType));
							SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// 新しい色を true にする
						}
						if (g_aCursor[nIdy].colorType == PLAYERCOLOR_STANDARD)
						{// 初期色のとき
							pPlayer[nIdy].colType = PLAYERCOLOR_STANDARD;
						}
						else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF1)
						{// 違う色のとき
							pPlayer[nIdy].colType = PLAYERCOLOR_DIF1;
						}
						else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF2)
						{// 違う色のとき
							pPlayer[nIdy].colType = PLAYERCOLOR_DIF2;
						}
						else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF3)
						{// 違う色のとき
							pPlayer[nIdy].colType = PLAYERCOLOR_DIF3;
						}
					}
				}
			}
		}
	}
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	// 頂点lバッファをロックし頂点データへのポインタを取得
	g_pVtxBuffCursor->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCursor = 0; nCntCursor < CURSOR_MAX; nCntCursor++)
	{
		// 頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x - g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y - g_aCursor[nCntCursor].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x + g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y - g_aCursor[nCntCursor].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x - g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y + g_aCursor[nCntCursor].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x + g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y + g_aCursor[nCntCursor].fHeight, 0.0f);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.5f * g_aCursor[nCntCursor].nPatternAnim, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f * (g_aCursor[nCntCursor].nPatternAnim + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.5f * g_aCursor[nCntCursor].nPatternAnim, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f * (g_aCursor[nCntCursor].nPatternAnim + 1), 1.0f);

		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffCursor->Unlock();

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 描画処理
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawCursor(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスを所得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCursor, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntCursor = 0; nCntCursor < CURSOR_MAX; nCntCursor++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureCursor[nCntCursor]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntCursor * MAX_CURSORTOP,
			2);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 操作処理(キー入力)
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetOperation(int nIndex)
{
	// キー入力による移動
	static int nIdy = 0;
	if (GetKeyboardTrigger(DIK_0))
	{// 1番目のカーソル
		nIdy = 0;
	}
	if (GetKeyboardTrigger(DIK_1))
	{// 2番目のカーソル
		nIdy = 1;
	}
	if (GetKeyboardTrigger(DIK_2))
	{// 3番目のカーソル
		nIdy = 2;
	}
	if (GetKeyboardTrigger(DIK_3))
	{// 4番目のカーソル
		nIdy = 3;
	}
	if (nIndex == nIdy)
	{
		// 任意のキーが押されたかどうか
		if (GetKeyboardPress(DIK_A) == true)
		{// 左側
			if (GetKeyboardPress(DIK_W) == true)
			{// 左上
				g_aCursor[nIdy].move.x -= sinf(D3DX_PI / 4 * 3) * MOVE_SPEED;
				g_aCursor[nIdy].move.y += cosf(D3DX_PI / 4 * 3) * MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// 左下
				g_aCursor[nIdy].move.x -= sinf(D3DX_PI / 4) * MOVE_SPEED;
				g_aCursor[nIdy].move.y += cosf(D3DX_PI / 4) * MOVE_SPEED;
			}
			else
			{// 左
				g_aCursor[nIdy].move.x -= sinf(D3DX_PI / 2) * MOVE_SPEED;
				g_aCursor[nIdy].move.y += cosf(D3DX_PI / 2) * MOVE_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// 右側
			if (GetKeyboardPress(DIK_W) == true)
			{// 右上
				g_aCursor[nIdy].move.x += sinf(D3DX_PI / 4 * 3) * MOVE_SPEED;
				g_aCursor[nIdy].move.y += cosf(D3DX_PI / 4 * 3) * MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// 右下
				g_aCursor[nIdy].move.x += sinf(D3DX_PI / 4) * MOVE_SPEED;
				g_aCursor[nIdy].move.y += cosf(D3DX_PI / 4) * MOVE_SPEED;
			}
			else
			{// 右
				g_aCursor[nIdy].move.x += sinf(D3DX_PI / 2) * MOVE_SPEED;
				g_aCursor[nIdy].move.y -= cosf(D3DX_PI / 2) * MOVE_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{// 上
			g_aCursor[nIdy].move.x += sinf(D3DX_PI) * MOVE_SPEED;
			g_aCursor[nIdy].move.y += cosf(D3DX_PI) * MOVE_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// 下
			g_aCursor[nIdy].move.x -= sinf(D3DX_PI * 0) * MOVE_SPEED;
			g_aCursor[nIdy].move.y += cosf(D3DX_PI * 0) * MOVE_SPEED;
		}
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			if (g_aCursor[nIdy].state == CURSORSTATE_CATCH)
			{// 掴む
				g_aCursor[nIdy].state = CURSORSTATE_RELEASE_START;		// 状態を切り替える
				g_aCursor[nIdy].nPatternAnim = 0;					// テクスチャ切り替え
			}
			else if (g_aCursor[nIdy].state == CURSORSTATE_RELEASE)
			{// 放す
				g_aCursor[nIdy].state = CURSORSTATE_CATCH;			// 状態を切り替える
				g_aCursor[nIdy].nPatternAnim = 1;					// テクスチャ切り替え
			}
		}

		if (g_aCursor[nIdy].state == CURSORSTATE_RELEASE)
		{// 放している時(マーカーを置いてるとき)
			Player *pPlayer = GetPlayer();
			if (GetKeyboardTrigger(DIK_E) == true)
			{// カラー変更
				g_aCursor[nIdy].colorType = pPlayer[nIdy].colType;	// プレイヤーの色を入れる
				SetColSel(false, nIdy, g_aCursor[nIdy].colorType);	// 元の色を false にする
				g_aCursor[nIdy].colorType++;						// 色の種類を変える
				if (g_aCursor[nIdy].colorType >= PLAYERCOLOR_MAX)
				{// 色の種類を超えたとき
					g_aCursor[nIdy].colorType = 0;
				}

				if (false == GetColSel(nIdy, g_aCursor[nIdy].colorType))
				{// 色が使われていなかったら
					SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// 新しい色を true にする
				}
				else if (true == GetColSel(nIdy, g_aCursor[nIdy].colorType))
				{// 色が使われていたら
					do
					{
						g_aCursor[nIdy].colorType++;						// 色を変える
						if (g_aCursor[nIdy].colorType >= PLAYERCOLOR_MAX)
						{// 色の種類を超えたとき
							g_aCursor[nIdy].colorType = 0;
						}

					} while (false != GetColSel(nIdy, g_aCursor[nIdy].colorType));
					SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// 新しい色を true にする
				}
				if (g_aCursor[nIdy].colorType == PLAYERCOLOR_STANDARD)
				{// 初期色のとき
					pPlayer[nIdy].colType = PLAYERCOLOR_STANDARD;
				}
				else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF1)
				{// 違う色のとき
					pPlayer[nIdy].colType = PLAYERCOLOR_DIF1;
				}
				else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF2)
				{// 違う色のとき
					pPlayer[nIdy].colType = PLAYERCOLOR_DIF2;
				}
				else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF3)
				{// 違う色のとき
					pPlayer[nIdy].colType = PLAYERCOLOR_DIF3;
				}
			}
			else if (GetKeyboardTrigger(DIK_Q) == true)
			{// カラー変更
				g_aCursor[nIdy].colorType = pPlayer[nIdy].colType;	// プレイヤーの色を入れる
				SetColSel(false, nIdy, g_aCursor[nIdy].colorType);	// 元の色を false にする
				g_aCursor[nIdy].colorType--;						// 色の種類を変える
				if (g_aCursor[nIdy].colorType < 0)
				{// 色の種類を超えたとき
					g_aCursor[nIdy].colorType = PLAYERCOLOR_DIF3;
				}

				if (false == GetColSel(nIdy, g_aCursor[nIdy].colorType))
				{// 色が使われていなかったら
					SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// 新しい色を true にする
				}
				else if (true == GetColSel(nIdy, g_aCursor[nIdy].colorType))
				{// 色が使われていたら
					do
					{
						g_aCursor[nIdy].colorType++;						// 色を変える
						if (g_aCursor[nIdy].colorType >= PLAYERCOLOR_MAX)
						{// 色の種類を超えたとき
							g_aCursor[nIdy].colorType = 0;
						}

					} while (false != GetColSel(nIdy, g_aCursor[nIdy].colorType));
					SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// 新しい色を true にする
				}
				if (g_aCursor[nIdy].colorType == PLAYERCOLOR_STANDARD)
				{// 初期色のとき
					pPlayer[nIdy].colType = PLAYERCOLOR_STANDARD;
				}
				else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF1)
				{// 違う色のとき
					pPlayer[nIdy].colType = PLAYERCOLOR_DIF1;
				}
				else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF2)
				{// 違う色のとき
					pPlayer[nIdy].colType = PLAYERCOLOR_DIF2;
				}
				else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF3)
				{// 違う色のとき
					pPlayer[nIdy].colType = PLAYERCOLOR_DIF3;
				}
			}
		}
	}
	GamePad *pGamePad = GetgamePadStick();
	if (pGamePad[nIndex].pDevGamePad != NULL)
	{
		if (pGamePad[nIndex].aGamePad.lX < -GAMEPAD_DEADZONE || pGamePad[nIndex].aGamePad.lX > GAMEPAD_DEADZONE || pGamePad[nIndex].aGamePad.lY < -GAMEPAD_DEADZONE || pGamePad[nIndex].aGamePad.lY> GAMEPAD_DEADZONE)
		{
			float fGamePagStickAngle = atan2f(float(-pGamePad[nIndex].aGamePad.lX), float(pGamePad[nIndex].aGamePad.lY));
			g_aCursor[nIndex].move.x -= sinf(fGamePagStickAngle) * MOVE_SPEED;
			g_aCursor[nIndex].move.y += cosf(fGamePagStickAngle) * MOVE_SPEED;

		}
	}
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// カーソル
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
CURSOR *GetCursors(void)
{
	return &g_aCursor[0];
}