//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// プレイヤー番号の表示の処理 [playerMark.h]
// Author : suzuki
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _PLAYERMARK_H_
#define _PLAYERMARK_H_

#include "main.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// マクロ定義
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define PLAYERMARK_TEXTURE_0	"data/TEXTURE/CharacterMarker000.png"	// テクスチャ
#define PLAYERMARK_TEXTURE_1	"data/TEXTURE/CharacterMarker001.png"	// テクスチャ
#define PLAYERMARK_TEXTURE_2	"data/TEXTURE/CharacterMarker002.png"	// テクスチャ
#define PLAYERMARK_TEXTURE_3	"data/TEXTURE/CharacterMarker003.png"	// テクスチャ
#define PLAYERMARK_MAX			(4)										// 最大数
#define PLAYERMARK_WIDTH		(20)									// 幅
#define PLAYERMARK_HEIGHT		(20)									// 高さ
#define PLAYERMARK_COUNTSPEED	(300)									// 表示切り替えの速さ

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//構造体の定義
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct
{
	D3DXVECTOR3 pos;					// 位置
	D3DXVECTOR3 rot;					// 向き
	D3DXMATRIX	mtxWorldPlayerMark;		// ワールドマトリックス
	D3DXCOLOR	col;					// 色
	int			nCntSwitch;				// 表示する、しないを切り替えるカウント
	float		fWidth;					// 幅
	float		fHeight;				// 高さ
	bool		bUse;					// 使用いているかどうか
}PlayerMark;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// プロトタイプ宣言
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitPlayerMark(void);
void UninitPlayerMark(void);
void UpdatePlayerMark(void);
void DrawPlayerMark(void);

void SetPlayerMark(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col);
#endif
