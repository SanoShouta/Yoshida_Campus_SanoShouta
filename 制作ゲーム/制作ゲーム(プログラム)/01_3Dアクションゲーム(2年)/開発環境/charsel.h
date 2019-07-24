//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �L�����N�^�[�I������ [charSel.h]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _CHARSEL_H_
#define _CHARSEL_H_		// 2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#include "player.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �}�N����`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define MAX_CHARSELTOP		(4)		// ���_��
#define CHOTIN_HEIGHT		(150)	// �񓔂̍���
#define PICKUP_WIDTH		(340)	// �L�����\���E�B���h�E�̕�
#define PICKUP_HEIGHT		(310)	// �L�����\���E�B���h�E�̍���
#define CHARWINDOW_WIDTH	(140)	// �L�����E�B���h�E�̕�
#define CHARWINDOW_HEIGHT	(140)	// �L�����E�B���h�E�̍���
#define EXIT_WIDTH			(320)	// �߂�E�B���h�E�̕�
#define EXIT_HEIGHT			(100)	// �߂�E�B���h�E�̍���

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �񋓑̂̒�`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef enum
{// �I���E�B���h�E���
	CHARSELTYPE_BG = 0,			// �w�i
	CHARSELTYPE_CHOUTINUP,		// ��(��)
	CHARSELTYPE_CHOUTINDOWN,	// ��(��)
	CHARSELTYPE_PLAYER1,		// 1P�̑I���L�����N�^�[�E�B���h�E
	CHARSELTYPE_PLAYER2,		// 2P�̑I���L�����N�^�[�E�B���h�E
	CHARSELTYPE_PLAYER3,		// 3P�̑I���L�����N�^�[�E�B���h�E
	CHARSELTYPE_PLAYER4,		// 4P�̑I���L�����N�^�[�E�B���h�E
	CHARSELTYPE_MATURI,			// �܂�i���̎q�j
	CHARSELTYPE_AMANO,			// ���܂́i�V��j
	CHARSELTYPE_GOJOU,			// ���i�͓��j
	CHARSELTYPE_MOMIJI,			// �g�t�i���ˁj
	CHARSELTYPE_DONROID,		// �h�����C�h�i���{�b�g�j
	CHARSELTYPE_RANDOM,			// �����_��
	CHARSELTYPE_EXIT,			// �߂�
	CHARSELTYPE_MAX,			// ����
	CHARSELTYPE_NONE,			// �ǂ�ł��Ȃ� (�����Ɋ܂܂Ȃ����߈�ԉ��ɒu���Ă���)
}CHARSELTYPE;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �\���̂̒�`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct
{// �I������E�B���h�E
	D3DXVECTOR3	pos;	// �ʒu
	float fWidth;		// ��
	float fHeight;		// ����
	CHARSELTYPE type;	// ���
	bool bUse;			// �g���Ă��邩�ǂ���
	float moveTex;		// �e�N�X�`���̈ړ���
}Charsel;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �v���g�^�C�v�錾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitCharsel(void);
void UninitCharsel(void);
void UpdateCharsel(void);
void DrawCharsel(void);
void MakeVertexCharsel(LPDIRECT3DDEVICE9 pDevice);
void SetCharsel(D3DXVECTOR3	pos, float fWidth, float fHeight, CHARSELTYPE type);
PLAYERTYPE CollisionCharsel(D3DXVECTOR3 pPos, float fWidth, float fHeight, PLAYERTYPE type);
#endif