//=============================================================================
//
//				スコアの処理[score.h]
//				Auther : Shun Yokomichi
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"		// メイン
#include "scene.h"		// シーン
#include "number.h"		// 数字

//*****************************************************************************
//				マクロ定義
//*****************************************************************************
#define MAX_SCORE		(6)		// 桁数の最大数

//*****************************************************************************
//				クラス定義(スコア)
//*****************************************************************************
class CScore : public CScene
{
public:
	CScore();
	~CScore();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	int GetScore(void);		// スコアの取得

	// 静的メンバ関数
	static CScore *Create();			// 生成
	static void SetScore(int nScore);	// スコアの設定
	static void AddScore(int nValue);	// スコアの加算

private:
	// 静的メンバ変数
	static CNumber2D *m_apNumber[MAX_SCORE];		// スコアの最大桁数
	static int m_nScore;
};
#endif
