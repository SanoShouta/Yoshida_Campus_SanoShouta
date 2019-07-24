//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// キャラクター選択処理 [marker.h]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _MARKER_H_		//2重インクルード防止のマクロ定義
#define _MARKER_H_
#include "player.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// マクロ定義
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define MARKER_WIDTH		(40)							// 幅
#define MARKER_HEIGHT		(40)							// 高さ
#define MARKER_MAX			(4)								// 最大数
#define MAX_MARKERTOP		(4)								// 頂点数
#define MARKER_TEXTURENAME0	"data/TEXTURE/Marker000.png"	// 読み込むテクスチャの名前
#define MARKER_TEXTURENAME1	"data/TEXTURE/Marker001.png"	// 読み込むテクスチャの名前
#define MARKER_TEXTURENAME2	"data/TEXTURE/Marker002.png"	// 読み込むテクスチャの名前
#define MARKER_TEXTURENAME3	"data/TEXTURE/Marker003.png"	// 読み込むテクスチャの名前

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 構造体の定義
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct
{// カーソル
	D3DXVECTOR3 pos;				// 現在の位置
	D3DXVECTOR3 posOld;				// 前回の位置
	D3DXVECTOR3 move;				// 移動量
	float		fWidth;				// 幅
	float		fHeight;			// 高さ
	PLAYERTYPE	type;
	bool		bUse;				// 置いているかどうか
}MARKER;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// プロトタイプ宣言
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitMarker(void);
void UninitMarker(void);
void UpdateMarker(void);
void DrawMarker(void);
MARKER *GetMarker(void);
int GetNumMarker(void);
void SetColSel(bool bColSel, int nIdy, int nColId);
bool GetColSel(int nIdy, int nColId);
#endif