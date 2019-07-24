////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// プレイヤー処理 [player.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "sound.h"
#include "meshField.h"
#include "model.h"
//******************************************************************************************************************************
// マクロ定義
//******************************************************************************************************************************
#define MAX_PLAYER		(4)			// 最大数
#define MAX_PLAYERMODEL	(18)
#define MAX_PLAYER_KEY	(20)	// モーション1つに対するキーフレームの最大数
#define MAX_MOTION		(30)	// モーション数
#define MAX_COLLISION	(50)	// 判定最大数
#define MAX_PLAYER_ORBIT (10)	// 軌跡の最大数
//******************************************************************************************************************************
// 構造体定義
//******************************************************************************************************************************
typedef enum
{
	PLAYERTYPE_MATURI = 0,	// まつり（女の子）
	PLAYERTYPE_AMANO,		// あまの（天狗）
	PLAYERTYPE_GOJOU,		// 悟浄（河童）
	PLAYERTYPE_MOMIJI,		// 紅葉（きつね）
	PLAYERTYPE_DONROID,		// ドンロイド（ロボット）
	PLAYERTYPE_MAX,
}PLAYERTYPE;
typedef enum
{// モーションの種類
	PLAYER_MOTION_TYPE_NEUTRAL = 0,					// ニュートラル時
	PLAYER_MOTION_TYPE_MOVE,						// 移動時
	PLAYER_MOTION_TYPE_JUMP,						// ジャンプ時
	PLAYER_MOTION_TYPE_LANDING,						// 着地時
	PLAYER_MOTION_TYPE_DAMAGE,						// ダメージ(仰け反り)時
	PLAYER_MOTION_TYPE_FLY,							// ダメージ(吹っ飛び)時
	PLAYER_MOTION_TYPE_GETUP,						// 起き上がり時
	PLAYER_MOTION_TYPE_CATCH,						// 拾う
	PLAYER_MOTION_TYPE_THROW,						// 投げる
	PLAYER_MOTION_TYPE_GUARD,						// ガード
	PLAYER_MOTION_TYPE_CRASH,						// 混乱
	PLAYER_MOTION_TYPE_WEAK,						// 弱
	PLAYER_MOTION_TYPE_WEAK_2,						// 弱2
	PLAYER_MOTION_TYPE_WEAK_3,						// 弱3
	PLAYER_MOTION_TYPE_WEAK_4,						// 弱4
	PLAYER_MOTION_TYPE_WEAK_5,						// 弱5
	PLAYER_MOTION_TYPE_SPECIAL,						// 必殺技
	PLAYER_MOTION_TYPE_WIN,							// 勝利
	PLAYER_MOTION_TYPE_MAX							// モーションの総数
}PlayerMotionType;

typedef enum
{// 攻撃の種類
	PLAYER_ATTACK_TYPE_WEAK = 0,				// 弱
	PLAYER_ATTACK_TYPE_WEAK_2,				// 弱2
	PLAYER_ATTACK_TYPE_WEAK_3,		// 弱3
	PLAYER_ATTACK_TYPE_WEAK_4,		// 弱4
	PLAYER_ATTACK_TYPE_WEAK_5,		// 弱5
	PLAYER_ATTACK_TYPE_SPECIAL,		// 必殺技
	PLAYER_ATTACK_TYPE_MAX						// 攻撃の種類の総数
}PlayerAttackType;

typedef enum
{// boolの種類
	PLAYER_BOOL_RUN = 0,			// 走る
	PLAYER_BOOL_JUMP,				// ジャンプ
	PLAYER_BOOL_LANDING,			// 着地
	PLAYER_BOOL_DAMAGE,				// ダメージ
	PLAYER_BOOL_FLY,				// 吹っ飛び
	PLAYER_BOOL_GETUP,				// 起き上がり
	PLAYER_BOOL_CATCH,				// 拾う
	PLAYER_BOOL_THROW,				// なげる
	PLAYER_BOOL_GUARD,				// ガード
	PLAYER_BOOL_CRASH,				// 混乱
	PLAYER_BOOL_WIN,				// 勝利
	PLAYER_BOOL_MAX
}PlayerBool;

typedef enum
{// プレイヤーの状態
	PLAYERSTATE_NONE = 0,		// 何もなし
	PLAYERSTATE_DAMAGESTART,	// 無敵
	PLAYERSTATE_DAMAGE,			// ダメージ
	PLAYERSTATE_FALL,			// 落ちる
	PLAYERSTATE_CRASHSTART,			// 混乱
	PLAYERSTATE_CRASH,			// 混乱
	PLAYERSTATE_INVINCIBLE,		// 無敵
	PLAYERSTATE_DEATH,			// 死ぬ
}PLAYERSTATE;

typedef enum
{// プレイヤーのカラータイプ
	PLAYERCOLOR_STANDARD = 0,
	PLAYERCOLOR_DIF1,
	PLAYERCOLOR_DIF2,
	PLAYERCOLOR_DIF3,
	PLAYERCOLOR_MAX
}PLAYERCOLOR;

typedef struct
{
	int nIdyOrbit;					// 番号
	int nOrbitLength;				// 軌跡の長さ
	D3DXVECTOR3 OrbitStart;			// 軌跡の始点
	D3DXVECTOR3 OrbitEnd;			// 軌跡の終点
	int nType;						// タイプ
	PlayerMotionType motion;		// モーションタイプ
}PlayerOrbit;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
}PartsKeyPlayer;
typedef struct
{
	int nFrame;									// キーフレーム
	PartsKeyPlayer aPartsKey[MAX_PLAYERMODEL];	// パーツごとのキー情報
}KeyPlayer;
typedef struct
{
	bool bLoop;									// ループするかどうか
	int nNumKey;								// キー数
	KeyPlayer aKey[MAX_PLAYER_KEY];				// キー情報
	float fAttackPower;						// モーションの攻撃力
	float fDamageH;					// モーションの水平方向に吹き飛ばす力
	float fDamageV;						// モーションの垂直方向に吹き飛ばす力
}MotionPlayer;

typedef struct
{// 攻撃の当たり判定のオフセットの構造体
	D3DXVECTOR3			ofset;				// 位置
	D3DXMATRIX			mtxWorld;			// ワールドマトリックス
	D3DXMATRIX			mtxWorldOld;		// ワールドマトリックス
	__int8				nIdxParent;			// 親モデルのインデックス
	float				fRadius;			// 半径
	short int			nCollisionStart;	// 当たり判定の始まりのフレーム数
	short int			nCollisionEnd;		// 当たり判定の終わりのフレーム数
	PlayerMotionType	nMotionType;		// 当たり判定が付くモーションのタイプ
	int					nStopTime;			// 停止時間
	bool				bUse;				// 当たり判定が使われてるかどうか
}CollisionAttackPlayer;
typedef struct
{// 体の当たり判定のオフセットの構造体
	D3DXVECTOR3			ofset;				// 位置
	D3DXMATRIX			mtxWorld;			// ワールドマトリックス
	D3DXMATRIX			mtxWorldOld;		// ワールドマトリックス
	__int8				nIdxParent;			// 親モデルのインデックス
	float				fRadius;			// 半径
	bool				bUse;				// 当たり判定が使われてるかどうか
}CollisionBodyPlayer;

typedef struct
{
	char *pFileName;								// ファイル名
	LPD3DXMESH pMesh;								// メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMat;							// マテリアル情報へのポインタ
	DWORD nNumMat;									// マテリアル情報の数
	LPDIRECT3DTEXTURE9 *pTextuer[PLAYERCOLOR_MAX];	// テクスチャ
	D3DXVECTOR3 rot;								// 角度
	D3DXVECTOR3 pos;								// 位置
	D3DXVECTOR3 Initpos;							// 初期オフセット位置
	D3DXVECTOR3	posAddMotion;						// 加算モーション位置
	D3DXVECTOR3	rotAddMotion;						// 加算モーション向き
	D3DXVECTOR3 DiffrotMotion;						// 差分
	D3DXMATRIX mtxWorld;							// ワールドマトリックス
	D3DXMATRIX mtxWorldOld;							// ワールドマトリックス
	int nIdxModel;									// 自分のモデルの番号
	int nIdxModelPareant;							// 親モデルのインデックス
}PlayerModel;
typedef struct
{
	CollisionAttackPlayer ColAttack[MAX_COLLISION];	// 攻撃判定
	CollisionBodyPlayer ColBody[MAX_COLLISION];		// ダメージ判定
	PlayerModel aModel[MAX_PLAYERMODEL];// パーツ数
	MotionPlayer aMotion[MAX_MOTION];	// モーションの情報
	PlayerOrbit orbit[PLAYER_MOTION_TYPE_MAX][MAX_PLAYER_ORBIT];			// 軌跡の最大
	float fRadiusWidth;					// 半径横
	float fRadiusHeight;				// 半径高さ
	int nNumParts;						// パーツ数
	int nNumMotion;						// モーション番号
	float JumpSpeed;					// ジャンプ量
	float MoveSpeed;					// 移動速度
	int nInitLife;						// 初期ライフ
}PlayerData;
typedef struct
{
	CollisionAttackPlayer ColAttack[MAX_COLLISION];	// 攻撃判定
	CollisionBodyPlayer ColBody[MAX_COLLISION];		// ダメージ判定
	PlayerModel aModel[MAX_PLAYERMODEL];// パーツ数
	PlayerOrbit orbit[PLAYER_MOTION_TYPE_MAX][MAX_PLAYER_ORBIT];			// 軌跡の最大

	D3DXVECTOR3 pos;					// 位置
	D3DXVECTOR3 posOld;					// 前回の位置
	D3DXVECTOR3 Diffpos;				// 目的の位置
	D3DXVECTOR3 Initpos;				// 初期位置
	D3DXVECTOR3 move;					// 移動量
	D3DXVECTOR3 CtrlMove;				// 操作の移動量
	D3DXVECTOR3 Environment;			// 環境
	D3DXCOLOR col;						// 色
	float fRadiusWidth;					// 半径横
	float fRadiusHeight;				// 半径高さ
	float JumpSpeed;					// ジャンプ量
	float MoveSpeed;					// 移動速度
	D3DXVECTOR3 Diffrot;				// 角度の差分
	D3DXVECTOR3 Destrot;				// 目的の角度
	D3DXVECTOR3 rot;					// 角度
	D3DXMATRIX mtxWorld;				// ワールドマトリックス
	PlayerMotionType nMotionType;		// 状態
	PlayerMotionType nMotionTypeOld;	// 前の状態
	PlayerMotionType nMotionGetCol;		// ダメージ与えたときの状態
	PlayerMotionType nMotionGetColOld;	// ダメージ与えたときの前の状態
	PLAYERSTATE state;					// 状態
	int nCntState;						// 状態
	int nIdyShadow;						// 影の番号
	int nIdyLine;						// 判定の番号
	bool bMotionState[PLAYER_BOOL_MAX];			// モーション使用判定
	bool bMotionStateOld[PLAYER_BOOL_MAX];		// 前回のモーション使用判定
	bool bBlend;						// ブレンド中かどうか
	bool bJump;							// ジャンプしているかどうか
	bool bCatch;						// 拾ったかどうか
	bool bCatchOld;						// 拾ったかどうか
	int nDamage;						// ダメージ
	float fLife;							// ライフ
	bool bSound[SOUND_LABEL_MAX];		// 音
	int nIdy;							// 番号
	MeshField *pMeshFieldLand;			// どの床に乗っているか
	D3DXVECTOR3 fFlyPower;									// 吹っ飛び速度
	int nFlyCounter;										// 飛んでいる時間
	float fRotSpeed;										// 回転の減速スピード
	bool bAttackType[PLAYER_ATTACK_TYPE_MAX];				// アタックの種類
	Model *pModel;											// 当たったモデルの情報
	Model *pModelAtkData;									// 当たったモデルの情報
	Model *pModelAtk;										// 当たったモデルの情報
	int nAirCounter;										// 飛んでる時のコンボ制限
	int nLoopCounter;										// モーションのループカウンタ
	int nKeyCounter;										// キー数
	int nFrameCounter;										// フレーム数
	int nFrameAllCounter;									// 最大フレーム数
	int nFrame;												// フレー
	float fGuardLife;										// ガードの寿命
	PLAYERTYPE type;										// タイプ
	PLAYERTYPE typeInfo;									// 静的タイプ
	bool bUse;
	bool bDraw;
	PLAYERCOLOR colType;									// プレイヤーカラータイプ
	float fPulsLife;			// アイテムで増えるライフ
	float fPulsAttack;		// アイテムで加算される攻撃力
	float fPulsSpeed;			// アイテムで増えるスピード
	int nItemTime;				// アイテム継続時間
	int nSp;				// スペシャル
	bool bSp;			// 天狗のスペシャル
	int nComboCounter;
	bool bCombo;	// コンボ
	int nCntEmote;	// エモート
	int nStopTime;	// 操作不能
	bool bSpecial;
}Player;

//******************************************************************************************************************************
// プロトタイプ宣言
//******************************************************************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(int nIdy);
void DrawPlayer(int nIdy,int nCamera);
Player *GetPlayer(void);
PlayerData *GetPlayerData(void);
void MotionInfoPlayer(int nIdy);
void SetAttackCollisionPlayer(int nIdy,int nIdxParent, D3DXVECTOR3 offset,float fRadius,  int nCollisionStart, int nCollisionEnd,int nStopTime,PlayerMotionType nMotionType);
void SetBodyCollisionPlayer(int nIdy,int nIdxParent, D3DXVECTOR3 offset, float fRadius);
bool CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 mtxWorld, float fRadius, float nPower, float fDamageSide, float fDamageV, int nIdy);
bool CollisionPlayerEffect(D3DXVECTOR3 pos, D3DXVECTOR3 mtxWorld, float fRadius, float nPower, float fDamageSide, float fDamageV);
void PlayerController(int nIdy);					// プレイヤーの操作
void PlayerOverLap(int nIdy);
void PlayerColInfo(int nIdy);
void PlayerMotionEffect(int nIdy,int nCollision);
void SetPlayer(int nIdy, D3DXVECTOR3 pos, PLAYERTYPE type);
void ReleasePlayer(int nIdy);
void SetTypePlayer(int nIdy,PLAYERTYPE type);
int CheckLife(void);
#endif
