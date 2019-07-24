//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : 佐藤安純 Sato_Asumi
//
//=============================================================================
#include "item.h"
#include "shadow.h"
#include <time.h>
//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_NAME00	"data\\TEXTURE\\item.png"		// 読みこむテクスチャファイル名
#define MAX_ITEM		(20)							// アイテムの最大数
#define RANGE			(25.0f)							// 当たり判定の範囲
#define UV				(0.125f)						// UV値の移動量
#define COUNTER			(60 * 5)						// 確立の判定秒数
#define INTERBAL		(60 * 10)						// アイテムを設置するまでの時間
#define GRAVITY			(0.1f)							// 重力

//アイテムのサイズ
#define ITEM_SIZE_X		(50.0f)							// アイテムのサイズ
#define ITEM_SIZE_Y		(50.0f)							// アイテムのサイズ

//４頂点の座標
#define ITEM_MIN_X		((ITEM_SIZE_X / 2) * -1)		// ｘ値の最小値
#define ITEM_MAX_X		(ITEM_SIZE_X / 2)				// ｘ値の最大値
#define ITEM_MIN_Y		(0.0f)							// y値の最小値
#define ITEM_MAX_Y		(ITEM_SIZE_Y)					// y値の最大値

//影の大きさ
#define SHADOW_SIZE		(40.0f)							// 影のサイズ

//アイテムの出現座標
#define ITEM_POS_00		(D3DXVECTOR3(400.0f -float(rand()%800), 300.0f, -100 +float(rand()%500)))		//出現位置00
#define ITEM_POS_01		(D3DXVECTOR3(400.0f -float(rand()%800), 300.0f, -100 +float(rand()%500)))	//出現位置01
#define ITEM_POS_02		(D3DXVECTOR3(400.0f -float(rand()%800), 300.0f, -100 +float(rand()%500)))	//出現位置02
#define ITEM_POS_03		(D3DXVECTOR3(400.0f -float(rand()%800), 300.0f, -100 +float(rand()%500)))	//出現位置03
#define ITEM_POS_04		(D3DXVECTOR3(400.0f -float(rand()%800), 300.0f, -100 +float(rand()%500)))	//出現位置04
#define ITEM_POS_05		(D3DXVECTOR3(400.0f -float(rand()%800), 300.0f, -100 +float(rand()%500)))	//出現位置05
#define ITEM_POS_06		(D3DXVECTOR3(400.0f -float(rand()%800), 300.0f, -100 +float(rand()%500)))		//出現位置06

//綿あめの設定値
#define CHANDY_LOWPIORITY		(10)
#define CHANDY_ATK				(0)
#define CHANDY_HEAL				(10)
#define CHANDY_SPD				(0)

//おみくじの設定値
#define OMIKUZI_LOWPIORITY		(20)
#define OMIKUZI_ATK				(float(rand()%200/100.0f))
#define OMIKUZI_HEAL			(0)
#define OMIKUZI_SPD				(float(rand()%200/100.0f))

//たこ焼きの設定値
#define TAKOYAKI_LOWPIORITY		(30)
#define TAKOYAKI_ATK			(0)
#define TAKOYAKI_HEAL			(5)
#define TAKOYAKI_SPD			(0)

//きゅうりの設定値
#define CUCUMBER_LOWPIORITY		(40)
#define CUCUMBER_ATK			(0)
#define CUCUMBER_HEAL			(3)
#define CUCUMBER_SPD			(0.5f)

//油あげの設定値
#define FRIEDTOUHU_LOWPIORITY	(50)
#define FRIEDTOUHU_ATK			(1.0f)
#define FRIEDTOUHU_HEAL			(3)
#define FRIEDTOUHU_SPD			(0)

//葉っぱの設定値
#define LEAF_LOWPIORITY			(60)
#define LEAF_ATK				(0.5f)
#define LEAF_HEAL				(5)
#define LEAF_SPD				(0.3f)

//ねじの設定値
#define SCREW_LOWPIORITY		(70)
#define SCREW_ATK				(0.7f)
#define SCREW_HEAL				(0)
#define SCREW_SPD				(0.1f)

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexItem(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9		g_pTextureItem = NULL;	// テクスチャへのポインタ
D3DXVECTOR2				g_texItem;				//テクスチャ
Item					g_aItem[MAX_ITEM];		//アイテムの情報
Data					g_aData[ITEMTYPE_MAX];	//アイテムの情報
ITEMPOS					g_ItemPos;				//現在のアイテムの出現位置
ITEMPOS					g_ItemOldPos;			//前回のアイテムの出現位置
bool					g_bSetItem;				//アイテムを置いたかどうか
int						g_nCntTime;				//時間カウンター

//=============================================================================
// 初期化処理
//=============================================================================
void InitItem(void)
{
	//変数宣言
	int nCntItem;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME00,
		&g_pTextureItem);

	//グローバル変数の初期化
	g_ItemPos = ITEMPOS_00;
	g_ItemOldPos = ITEMPOS_00;
	g_bSetItem = false;
	g_nCntTime = 0;

	//変数の初期化
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].fAttack = 0;
		g_aItem[nCntItem].fHeal = 0;
		g_aItem[nCntItem].fSpeed = 0;
		g_aItem[nCntItem].nIdxshadow = 0;
		g_aItem[nCntItem].pMeshFieldLand = NULL;
		g_aItem[nCntItem].pModel = NULL;
		g_aItem[nCntItem].bUse = false;
		g_aItem[nCntItem].nLife = 0;
	}

	//最低確立の設定
	g_aData[0].nLowProbability = CHANDY_LOWPIORITY;		//綿あめ
	g_aData[1].nLowProbability = OMIKUZI_LOWPIORITY;	//おみくじ
	g_aData[2].nLowProbability = TAKOYAKI_LOWPIORITY;	//たこ焼き
	g_aData[3].nLowProbability = CUCUMBER_LOWPIORITY;	//きゅうり
	g_aData[4].nLowProbability = FRIEDTOUHU_LOWPIORITY;	//油揚げ
	g_aData[5].nLowProbability = LEAF_LOWPIORITY;		//葉っぱ
	g_aData[6].nLowProbability = SCREW_LOWPIORITY;		//ねじ

	//タイプのの設定
	g_aData[0].type = ITEMTYPE_CHANDY;					//綿あめ
	g_aData[1].type = ITEMTYPE_OMIKUZI;					//おみくじ
	g_aData[2].type = ITEMTYPE_TAKOYAKI;				//たこ焼き
	g_aData[3].type = ITEMTYPE_CUCUMBER;				//きゅうり
	g_aData[4].type = ITEMTYPE_FRIED_TOUHU;				//油揚げ
	g_aData[5].type = ITEMTYPE_LEAF;					//葉っぱ
	g_aData[6].type = ITEMTYPE_SCREW;					//ねじ

	//変数の初期化
	for (nCntItem = 0; nCntItem < ITEMTYPE_MAX; nCntItem++)
	{
		g_aData[nCntItem].fAttack = 0;
		g_aData[nCntItem].fHeal = 0;
		g_aData[nCntItem].fSpeed = 0;
		g_aData[nCntItem].Probability = 100;
		g_aData[nCntItem].nCounter = 0;

		//タイプ設定
		switch (g_aData[nCntItem].type)
		{
		case ITEMTYPE_CHANDY:		// わたあめ
			g_aData[nCntItem].fAttack = CHANDY_ATK;				//攻撃力
			g_aData[nCntItem].fHeal = CHANDY_HEAL;				//回復力
			g_aData[nCntItem].fSpeed = CHANDY_SPD;				//スピード
			break;

		case ITEMTYPE_OMIKUZI:		// おみくじ
			g_aData[nCntItem].fAttack = OMIKUZI_ATK;				//攻撃力
			g_aData[nCntItem].fHeal = OMIKUZI_HEAL;				//回復力
			g_aData[nCntItem].fSpeed = OMIKUZI_SPD;				//スピード
			break;

		case ITEMTYPE_TAKOYAKI:		// たこ焼き
			g_aData[nCntItem].fAttack = TAKOYAKI_ATK;				//攻撃力
			g_aData[nCntItem].fHeal = TAKOYAKI_HEAL;			//回復力
			g_aData[nCntItem].fSpeed = TAKOYAKI_SPD;				//スピード
			break;

		case ITEMTYPE_CUCUMBER:		// きゅうり
			g_aData[nCntItem].fAttack = CUCUMBER_ATK;				//攻撃力
			g_aData[nCntItem].fHeal = CUCUMBER_HEAL;			//回復力
			g_aData[nCntItem].fSpeed = CUCUMBER_SPD;				//スピード
			break;

		case ITEMTYPE_FRIED_TOUHU:	// 油揚げ
			g_aData[nCntItem].fAttack = FRIEDTOUHU_ATK;			//攻撃力
			g_aData[nCntItem].fHeal = FRIEDTOUHU_HEAL;			//回復力
			g_aData[nCntItem].fSpeed = FRIEDTOUHU_SPD;			//スピード
			break;

		case ITEMTYPE_LEAF:			// 葉っぱ
			g_aData[nCntItem].fAttack = LEAF_ATK;					//攻撃力
			g_aData[nCntItem].fHeal = LEAF_HEAL;				//回復力
			g_aData[nCntItem].fSpeed = LEAF_SPD;					//スピード
			break;

		case ITEMTYPE_SCREW:		// ねじ
			g_aData[nCntItem].fAttack = LEAF_ATK;					//攻撃力
			g_aData[nCntItem].fHeal = LEAF_HEAL;				//回復力
			g_aData[nCntItem].fSpeed = LEAF_SPD;					//スピード
			break;
		}
	}

	// 頂点情報の作成
	MakeVertexItem(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem(void)
{
	//テクスチャの開放
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem(void)
{
	//変数宣言
	int nCntItem;
	int nPriority;

	//メッシュフィールドの取得
	MeshField *pMeshField = GetMeshField();


	//確立の判定
	if (g_bSetItem == false)
	{
		for (nCntItem = 0; nCntItem < ITEMTYPE_MAX; nCntItem++)
		{
			//確立カウンターの加算
			g_aData[nCntItem].nCounter++;

			if ((g_aData[nCntItem].nCounter % COUNTER) == 0)
			{
				//出現判定
				nPriority = rand() % g_aData[nCntItem].Probability;

				//判定値内だったら表示する
				if (nPriority < g_aData[nCntItem].nLowProbability)
				{
					SetItem(g_aData[nCntItem].type);
					g_bSetItem = true;
					break;
				}
			}
		}
	}

	//セットアイテム判定の初期化
	if (g_bSetItem == true)
	{
		//時間の加算
		g_nCntTime++;

		//判定をfalseにする
		if ((g_nCntTime % INTERBAL) == 0)
		{
			g_bSetItem = false;
		}
	}

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			//前回の位置を保存する
			g_aItem[nCntItem].posOld = g_aItem[nCntItem].pos;

			//重力加算をする
			g_aItem[nCntItem].move.y -= GRAVITY;

			//位置更新
			g_aItem[nCntItem].pos += g_aItem[nCntItem].move;
			g_aItem[nCntItem].nLife--;
			if (g_aItem[nCntItem].nLife <= 0)
			{
				DeleteItem(nCntItem);
				DeleteShadow(g_aItem[nCntItem].nIdxshadow);

			}
			if (CollisionMeshField(&g_aItem[nCntItem].pos, &g_aItem[nCntItem].posOld, &g_aItem[nCntItem].move,
				ITEM_SIZE_X, ITEM_SIZE_Y, &g_aItem[nCntItem].pMeshFieldLand) == true)
			{//ｙ軸の座標を修正する
				g_aItem[nCntItem].pos.y = 0.0f;
			}
			if (CollisionModelMinMax(&g_aItem[nCntItem].pos, &g_aItem[nCntItem].posOld, &g_aItem[nCntItem].move, ITEM_SIZE_X, ITEM_SIZE_Y, &g_aItem[nCntItem].pModel) == 2)
			{// 上にのる
				Shadow *pShadow = GetShadow();
				pShadow[g_aItem[nCntItem].nIdxshadow].move.y = 0.0f;
				pShadow[g_aItem[nCntItem].nIdxshadow].pos.y = g_aItem[nCntItem].pos.y + 0.1f;
				pShadow[g_aItem[nCntItem].nIdxshadow].col.a = 1.0f;
			}
		}
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawItem(void)
{
	//変数宣言
	int nCntItem;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX		  mtxRot, mtxTrans;			// 計算用マトリックス
	D3DXMATRIX		  mtxView;					//ビューマトリクス

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aItem[nCntItem].mtxWorld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//逆行列を設定
			g_aItem[nCntItem].mtxWorld._11 = mtxView._11;
			g_aItem[nCntItem].mtxWorld._12 = mtxView._21;
			g_aItem[nCntItem].mtxWorld._13 = mtxView._31;
			g_aItem[nCntItem].mtxWorld._21 = mtxView._12;
			g_aItem[nCntItem].mtxWorld._22 = mtxView._22;
			g_aItem[nCntItem].mtxWorld._23 = mtxView._32;
			g_aItem[nCntItem].mtxWorld._31 = mtxView._13;
			g_aItem[nCntItem].mtxWorld._32 = mtxView._23;
			g_aItem[nCntItem].mtxWorld._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, g_aItem[nCntItem].pos.z);
			D3DXMatrixMultiply(&g_aItem[nCntItem].mtxWorld, &g_aItem[nCntItem].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aItem[nCntItem].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItem);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntItem * 4,
				2);
		}
	}

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexItem(LPDIRECT3DDEVICE9 pDevice)
{
	//変数宣言
	int nCntItem;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	VERTEX_3D * pVtx;		//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(ITEM_MIN_X, ITEM_MAX_Y, 00.0f);
		pVtx[1].pos = D3DXVECTOR3(ITEM_MAX_X, ITEM_MAX_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(ITEM_MIN_X, ITEM_MIN_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(ITEM_MAX_X, ITEM_MIN_Y, 0.0f);

		//法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// 設定情報
//=============================================================================
void SetItem(ITEMTYPE type)
{
	//変数宣言
	int nCntItem;

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].bUse = true;
			g_aItem[nCntItem].type = type;
			g_aItem[nCntItem].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//テクスチャのUV値の設定
			SetTex(nCntItem, g_aItem[nCntItem].type);

			//位置の設定
			g_aItem[nCntItem].pos = SetPos(rand() % (int)ITEMPOS_MAX);
			g_aItem[nCntItem].nLife = 600;
			//ステータスの設定
			g_aItem[nCntItem].fAttack = g_aData[type].fAttack;
			g_aItem[nCntItem].fHeal = g_aData[type].fHeal;
			g_aItem[nCntItem].fSpeed = g_aData[type].fSpeed;

			//影の設定
			g_aItem[nCntItem].nIdxshadow = SetShadow(D3DXVECTOR3(g_aItem[nCntItem].pos.x,
				0.0f,
				g_aItem[nCntItem].pos.z),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				SHADOW_SIZE, SHADOW_SIZE);

			break;
		}
	}
}

//=============================================================================
// 当たり判定
//=============================================================================
bool CollsionItem(D3DXVECTOR3 pos, float fRadiusWidth, float fRadiusHeight, float *pLife, float *pAttack, float *pSpeed)
{
	//変数宣言
	bool bGet = false;
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{// 使用している
			if (g_aItem[nCntItem].pos.y + (ITEM_SIZE_Y) >= pos.y&&							// 上
				g_aItem[nCntItem].pos.y <= pos.y + fRadiusHeight&&							// 下
				g_aItem[nCntItem].pos.x + (ITEM_SIZE_X / 2) >= pos.x - fRadiusWidth / 2&&	// 右
				g_aItem[nCntItem].pos.x - (ITEM_SIZE_X / 2) <= pos.x + fRadiusWidth / 2&&	// 左
				g_aItem[nCntItem].pos.z - (ITEM_SIZE_X / 2) <= pos.z + fRadiusWidth / 2&&	// 手前
				g_aItem[nCntItem].pos.z + (ITEM_SIZE_X / 2) >= pos.z - fRadiusWidth / 2)	// 奥
			{// アイテムにぶつかった
				DeleteItem(nCntItem);
				DeleteShadow(g_aItem[nCntItem].nIdxshadow);
				*pLife = (float(g_aData[g_aItem[nCntItem].type].fHeal));
				*pAttack += (float(g_aData[g_aItem[nCntItem].type].fAttack));
				*pSpeed = (float(g_aData[g_aItem[nCntItem].type].fSpeed));
				bGet = true;
				break;
			}
		}
	}
	return bGet;
}

//=============================================================================
// 炎を消す
//=============================================================================
void DeleteItem(int nCntItem)
{
	if (g_aItem[nCntItem].bUse == true)
	{
		g_aItem[nCntItem].bUse = false;				//オブジェクトを消す
		DeleteShadow(g_aItem[nCntItem].nIdxshadow);	//影を消す
	}
}

//=============================================================================
// UVの割り当て
//=============================================================================
void SetTex(int nIndex, int nType)
{
	VERTEX_3D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	//該当の位置まで進める
	pVtx += (4 * nIndex);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (UV * nType), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(UV + (UV * nType), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (UV * nType), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(UV + (UV * nType), 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// アイテムの情報取得
//=============================================================================
Item * GetItem(void)
{
	return &g_aItem[0];
}

//=============================================================================
// アイテムの出現位置の設定
//=============================================================================
D3DXVECTOR3 SetPos(int nItemPos)
{
	//変数宣言
	D3DXVECTOR3 ItemPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//座標設定
	switch (nItemPos)
	{
	case ITEMPOS_00:
		ItemPos = ITEM_POS_00;
		break;

	case ITEMPOS_01:
		ItemPos = ITEM_POS_01;
		break;

	case ITEMPOS_02:
		ItemPos = ITEM_POS_02;
		break;

	case ITEMPOS_03:
		ItemPos = ITEM_POS_03;
		break;

	case ITEMPOS_04:
		ItemPos = ITEM_POS_04;
		break;

	case ITEMPOS_05:
		ItemPos = ITEM_POS_05;
		break;

	case ITEMPOS_06:
		ItemPos = ITEM_POS_06;
		break;
	}

	return ItemPos;

}