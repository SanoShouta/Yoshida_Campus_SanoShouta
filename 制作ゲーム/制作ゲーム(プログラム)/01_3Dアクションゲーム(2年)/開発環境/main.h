//=============================================================================
//
// デバッグ情報表示処理 [main.h]
// Author : RyotaKinoshita
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	// 警告対処用
#include "dinput.h"
#include "xaudio2.h"					// サウンド処理で必要

//*****************************************************************************
// ライブラリのリンク
// [構成プロパティ]->[リンカー]->[入力]->[追加の依存ファイル]に記述しても可能
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")		// システム時刻取得用に必要
#pragma comment (lib, "dinput8.lib")


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1280)				// ウインドウの幅
#define SCREEN_HEIGHT	(720)				// ウインドウの高さ

// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線ベクトル / 頂点カラー  / テクスチャ座標)
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE|D3DFVF_TEX1)

typedef enum
{
	MODE_TITLE = 0,	// タイトル
	MODE_SELECT,	// セレクト
	MODE_CHARACTER, // キャラクター
	MODE_STAGE,		// ステージ
	MODE_GAME,		// ゲーム
	MODE_RESULT,	// リザルト
	MODE_STAFF,		// スタッフロール
	MODE_MAX		// 最大
}MODE;
typedef enum
{
	DRAW_DEBUG_POS = 0,
	DRAW_DEBUG_LINE,
	DRAW_DEBUG_WIREFRAME,
	DRAW_DEBUG_MAX,
}DRAWDEBUG;
// ２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;
// ３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_3D;
typedef struct
{
	LPD3DXEFFECT pShader;							// シェーダデータ
	LPDIRECT3DVERTEXDECLARATION9 pDecl;			// シェーダー
	LPDIRECT3DTEXTURE9 pTexture = NULL;			// シェーダーテクスチャ
}Shader;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
void GetPoint(HWND hWnd);
POINT *GetPoint(void);
bool *GetDrawDebug(void);
Shader GetShader(void);
void DrawPOS(void);

#endif