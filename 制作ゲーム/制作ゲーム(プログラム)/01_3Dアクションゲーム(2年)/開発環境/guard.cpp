////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 空（球体）処理 [sky.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "guard.h"
#include "camera.h"
//******************************************************************************************************************************
// マクロ定義
//******************************************************************************************************************************
#define MAX_GUARD	(4)
#define BLOCK_X	(50)
#define BLOCK_Y	(30)
#define VERTEX_WIDTH	(2+2*BLOCK_X)
//******************************************************************************************************************************
// 構造体定義
//******************************************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			// 中心座標
	D3DXVECTOR3 rot;			// 向き
	D3DXCOLOR col;			// 色
	GUARDTYPE nType;		// 種類
	float fWidth;				// 幅
	float fHeight;				// 高さ
	float fDepth;				// 奥行き
	float fLength;				// 半径
} GuardInfo;
typedef struct
{
	char *pFileName;
}GuardTexture;
//******************************************************************************************************************************
// プロトタイプ宣言
//******************************************************************************************************************************
void MakeVertexGuard(LPDIRECT3DDEVICE9 pDevice);

//******************************************************************************************************************************
// グローバル変数
//******************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureGuard[GUARDTYPE_MAX] = {};		// テクスチャへのポインタ
Guard g_aGuard[MAX_GUARD];
GuardInfo g_aGuardInfo[] =
{// 座標	向き	タイプ	幅	高さ	奥行き	半径
	{ D3DXVECTOR3(0.0f, 100.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(0.92f, 0.43f, 0.62f, 0.5f), GUARDTYPE_0, 10.0f,1.7f, 0.0f,50.0f },
	{ D3DXVECTOR3(0.0f, 100.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(0.55f, 0.78f, 1.0f,0.5f), GUARDTYPE_0, 10.0f,1.7f, 0.0f,50.0f },
	{ D3DXVECTOR3(0.0f, 100.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(1.0f, 1.0f, 0.1f, 0.5f), GUARDTYPE_0, 10.0f,1.7f, 0.0f,50.0f },
	{ D3DXVECTOR3(0.0f, 100.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXCOLOR(0.1f, 1.0f, 0.1f, 0.5f), GUARDTYPE_0, 10.0f,1.7f, 0.0f,50.0f },
};
GuardTexture g_aGuardTexInfo[GUARDTYPE_MAX] =
{
	{ "data/TEXTURE/Guard.jpg" },
};
//==============================================================================================================================
// 初期化処理
//==============================================================================================================================
void InitGuard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCntGuardTex = 0; nCntGuardTex < GUARDTYPE_MAX; nCntGuardTex++)
	{// テクスチャの設定
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			g_aGuardTexInfo[nCntGuardTex].pFileName,	// ファイルの名前
			&g_apTextureGuard[nCntGuardTex]);			// テクスチャへのポインタ
	}
	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{
		g_aGuard[nCnt].nNumVertex = (BLOCK_X + 1) * (BLOCK_Y + 1);					// 頂点数
		g_aGuard[nCnt].nNumIndex = 2 * (BLOCK_X*BLOCK_Y) + 4 * (BLOCK_Y - 1) + 2;	// インデックス数
		g_aGuard[nCnt].nNumPolygon = 2 * (BLOCK_X*BLOCK_Y) + 4 * (BLOCK_Y - 1);	// ポリゴン数


		g_aGuard[nCnt].pos = g_aGuardInfo[nCnt].pos;			// 位置
		g_aGuard[nCnt].rot = g_aGuardInfo[nCnt].rot;			// 向き
		g_aGuard[nCnt].col = g_aGuardInfo[nCnt].col;			// 色
		g_aGuard[nCnt].fWidth = g_aGuardInfo[nCnt].fWidth;	// 幅
		g_aGuard[nCnt].fHeight = g_aGuardInfo[nCnt].fHeight;	// 高さ
		g_aGuard[nCnt].fDepth = g_aGuardInfo[nCnt].fDepth;	// 奥行き
		g_aGuard[nCnt].fLength = g_aGuardInfo[nCnt].fLength;	// 半径
		g_aGuard[nCnt].nIdx = nCnt;							// 番号
		g_aGuard[nCnt].nType = g_aGuardInfo[nCnt].nType;		// 種類
		g_aGuard[nCnt].bUse = false;										// 使用されているかどうか

	}
	MakeVertexGuard(pDevice);
}

//==============================================================================================================================
// 終了処理
//==============================================================================================================================
void UninitGuard(void)
{
	// テクスチャの破棄
	for (int nCntGuard = 0; nCntGuard < GUARDTYPE_MAX; nCntGuard++)
	{
		if (g_apTextureGuard[nCntGuard] != NULL)
		{
			g_apTextureGuard[nCntGuard]->Release();
			g_apTextureGuard[nCntGuard] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{
		// 頂点バッファの破棄
		if (g_aGuard[nCnt].pVtxBuff != NULL)
		{
			g_aGuard[nCnt].pVtxBuff->Release();
			g_aGuard[nCnt].pVtxBuff = NULL;
		}
		// インデックスバッファバッファの破棄
		if (g_aGuard[nCnt].pIdxBuff != NULL)
		{
			g_aGuard[nCnt].pIdxBuff->Release();
			g_aGuard[nCnt].pIdxBuff = NULL;
		}
	}
}

//==============================================================================================================================
// 更新処理
//==============================================================================================================================
void UpdateGuard(void)
{
	VERTEX_3D *pVtx;	// 頂点情報のポインタ

	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{
		// 頂点バッファをロックし頂点データへのポインタを取得
		g_aGuard[nCnt].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


		for (int nCntV = 0; nCntV < BLOCK_Y + 1; nCntV++)
		{
			for (int nCntH = 0; nCntH < BLOCK_X + 1; nCntH++)
			{// "X"は元に戻すから％　"Z"は減少または増加し続けるので÷
			 // 頂点座標の設定
				pVtx[nCntH + (BLOCK_X + 1)*nCntV].pos = D3DXVECTOR3(sinf(0 + (-D3DX_PI * 2 / (BLOCK_X))* nCntH)*(sinf(D3DX_PI / BLOCK_Y*nCntV)*g_aGuard[nCnt].fLength),
					(cosf(0 + D3DX_PI / BLOCK_Y*nCntV)*g_aGuard[nCnt].fHeight*BLOCK_Y),
					cosf(0 + (-D3DX_PI * 2 / (BLOCK_X))* nCntH)*(sinf(0.1f + D3DX_PI / BLOCK_Y*nCntV)*g_aGuard[nCnt].fLength));
			}
		}
		// 頂点バッファをアンロックする
		g_aGuard[nCnt].pVtxBuff->Unlock();
	}
}

//==============================================================================================================================
// 描画処理
//==============================================================================================================================
void DrawGuard(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxProjection;				// 計算用マトリックス
	// ライト影響受けない
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αテストを設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// αテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);					// α値が0
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// より大きい


	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{
		if (g_aGuard[nCnt].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aGuard[nCnt].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aGuard[nCnt].rot.y, g_aGuard[nCnt].rot.x, g_aGuard[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aGuard[nCnt].mtxWorld, &g_aGuard[nCnt].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aGuard[nCnt].pos.x, g_aGuard[nCnt].pos.y, g_aGuard[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aGuard[nCnt].mtxWorld, &g_aGuard[nCnt].mtxWorld, &mtxTrans);

			// ビューマトリックスを設定
			D3DXMATRIX matrix = g_aGuard[nCnt].mtxWorld *GetCamera()[0].mtxView * GetCamera()[0].mtxProjection;

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aGuard[nCnt].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_aGuard[nCnt].pVtxBuff, 0, sizeof(VERTEX_3D));

			// インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_aGuard[nCnt].pIdxBuff);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureGuard[g_aGuard[nCnt].nType]);

			// ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aGuard[nCnt].nNumVertex, 0, g_aGuard[nCnt].nNumPolygon);

		}
	}

	// αテストを元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// αテストを無効化
	// ライト影響受けない
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//==============================================================================================================================
// 頂点情報の作成
//==============================================================================================================================
void MakeVertexGuard(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;	// 頂点情報のポインタ
	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{

		// 頂点情報の作成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aGuard[nCnt].nNumVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_aGuard[nCnt].pVtxBuff,
			NULL);
		// インデックスバッファの作成
		pDevice->CreateIndexBuffer(sizeof(WORD)*g_aGuard[nCnt].nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_aGuard[nCnt].pIdxBuff,
			NULL);

		// 頂点バッファをロックし頂点データへのポインタを取得
		g_aGuard[nCnt].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


		for (int nCntV = 0; nCntV < BLOCK_Y + 1; nCntV++)
		{
			for (int nCntH = 0; nCntH < BLOCK_X + 1; nCntH++)
			{// "X"は元に戻すから％　"Z"は減少または増加し続けるので÷
				// 頂点座標の設定
				pVtx[nCntH + (BLOCK_X + 1)*nCntV].pos = D3DXVECTOR3(sinf(0 + (-D3DX_PI * 2 / (BLOCK_X))* nCntH)*(sinf(D3DX_PI / BLOCK_Y*nCntV)*g_aGuard[nCnt].fLength),
					(cosf(0 + D3DX_PI / BLOCK_Y*nCntV)*g_aGuard[nCnt].fHeight*BLOCK_Y),
					cosf(0 + (-D3DX_PI * 2 / (BLOCK_X))* nCntH)*(sinf(0.1f + D3DX_PI / BLOCK_Y*nCntV)*g_aGuard[nCnt].fLength));
			}
		}

		for (int nCntVtx = 0; nCntVtx < g_aGuard[nCnt].nNumVertex; nCntVtx++)
		{
			// 法線の設定
			pVtx[nCntVtx].nor = pVtx[nCntVtx].pos / g_aGuard[nCnt].fLength;
		}
		for (int nCntVtx = 0; nCntVtx < g_aGuard[nCnt].nNumVertex; nCntVtx++)
		{
			// 頂点カラーの設定
			pVtx[nCntVtx].col = g_aGuard[nCnt].col;
		}
		for (int nCntV = 0; nCntV < BLOCK_Y + 1; nCntV++)
		{// テクスチャの設定
			for (int nCntH = 0; nCntH < BLOCK_X + 1; nCntH++)
			{// "X"は元に戻すから％　"Z"は減少または増加し続けるので÷
			// テクスチャの設定
				pVtx[nCntH + (BLOCK_X + 1)*nCntV].tex = D3DXVECTOR2(float(nCntH * 100 / BLOCK_X) / 100.0f, float(nCntV * 100 / BLOCK_Y) / 100.0f);
			}
		}

		// 頂点バッファをアンロックする
		g_aGuard[nCnt].pVtxBuff->Unlock();
	}
	for (int nCntIdxGuard = 0; nCntIdxGuard < MAX_GUARD; nCntIdxGuard++)
	{// インデックスの設定
		int nCnt = 0;

		WORD *pIdx;	// インデックスデータへのポインタ
		// インデックスバッファをロックし頂点データへのポインタを取得
		g_aGuard[nCntIdxGuard].pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
		// 頂点座標の設定
		for (int nCntX = 0; nCntX < g_aGuard[nCntIdxGuard].nNumIndex; nCntX += 2)
		{
			if (BLOCK_Y > 1 && nCntX % (VERTEX_WIDTH + 2) == VERTEX_WIDTH)
			{// 重なり部分
				pIdx[nCntX] = pIdx[nCntX - 1];
				pIdx[nCntX + 1] = (BLOCK_X + 1) + int(nCnt / 2);
			}
			else
			{// 通常部分
				pIdx[nCntX] = (BLOCK_X + 1) + int(nCnt / 2);
				pIdx[nCntX + 1] = int(nCnt / 2);
				nCnt += 2;
			}
		}

		// 頂点バッファをアンロックする
		g_aGuard[nCntIdxGuard].pIdxBuff->Unlock();
	}

}
//==============================================================================================================================
// ガードセット
//==============================================================================================================================
void SetGuard(int nIdx, D3DXVECTOR3 pos, float fLength)
{
	g_aGuard[nIdx].bUse = true;
	g_aGuard[nIdx].pos = pos;
	g_aGuard[nIdx].fLength = g_aGuardInfo[nIdx].fLength*fLength;
	g_aGuard[nIdx].fHeight = g_aGuardInfo[nIdx].fHeight*fLength;
}
//==============================================================================================================================
// ガード削除
//==============================================================================================================================
void UnSetGuard(int nIdx, float fLength)
{
	g_aGuard[nIdx].bUse = false;
	g_aGuard[nIdx].fLength = g_aGuardInfo[nIdx].fLength*fLength;
	g_aGuard[nIdx].fHeight = g_aGuardInfo[nIdx].fHeight*fLength;

}
