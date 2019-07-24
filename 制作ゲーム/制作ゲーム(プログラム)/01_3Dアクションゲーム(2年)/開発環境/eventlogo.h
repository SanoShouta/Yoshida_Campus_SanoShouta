//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �C�x���g���S���� [eventlogo.h]
// Author : suzuki
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _EVENTLOGO_H_
#define _EVENTLOGO_H_

#include "main.h"
#include "event.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �}�N����`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define EVENTLOGO_WIDTH			(130)										// ��
#define EVENTLOGO_HEIGHT		(70)										// ����
#define EVENTLOGO_POS_X			(SCREEN_WIDTH - EVENTLOGO_WIDTH - 20.0f)	// X���W (�E�[ - �� - �E�[�Ƃ̌���)
#define EVENTLOGO_POS_Y			(SCREEN_HEIGHT - EVENTLOGO_HEIGHT - 20.0f)	// Y���W (���[ - ���� - ���[�Ƃ̌���)
#define EVENTLOGO_MAX			(4)											// ���_��
#define EVENTLOGO_MOVESPEED		(5.0f)										// �������x
#define EVENTLOGO_NUMTIMES		(5)											// �e���b�v���o����(����)
#define EVENTLOGO_APPEARSPEED	(1.0f/ (60.0f * 0.5f))						// ���o�X�s�[�h( Alpha�̍ő�l / (�t���[���� * �b��))
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �񋓑̂̒�`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef enum
{// �C�x���g�̎��
	EVENTLOGOTEX_NONE = 0,			// �����Ȃ�
	EVENTLOGOTEX_WATER,				// �^��
	EVENTLOGOTEX_FIRE,				// �Ύ�
	EVENTLOGOTEX_FALLING_ROCK,		// ����
	EVENTLOGOTEX_METEORITE,			// 覐�
	EVENTLOGOTEX_RAIN,				// �J
	EVENTLOGOTEX_THUNDER,			// ��
	EVENTLOGOTEX_FALLING_OBJECT,	// ����
	EVENTLOGOTEX_GUST,				// �˕�
	EVENTLOGOTEX_MAX,				// �ő吔
}EVENTLOGOTEX;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �\���̂̒�`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct
{// �J�[�\��
	D3DXVECTOR3		pos;			// ���݂̈ʒu
	D3DXVECTOR3		posOld;			// �O��̈ʒu
	D3DXVECTOR3		move;			// �ړ���
	D3DXCOLOR		col;			// �F
	float			fWidth;			// ��
	float			fHeight;		// ����
	int				nCountDiaplay;	// �\�����̃J�E���g
	int				nNumTimes;		// ���S���o������
	bool			bUse;			// �g���Ă��邩�ǂ���
	bool			bAlpha;			// �������ǂ���
	EVENTTYPE		type;			// �C�x���g�̎��
	EVENTLOGOTEX	texType;		// �e�N�X�`���̎��
}EVENTLOGO;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �v���g�^�C�v�錾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitEventlogo(void);
void UninitEventlogo(void);
void UpdateEventlogo(void);
void DrawEventlogo(void);
void SetEventlogo(D3DXVECTOR3 pos, float fWidth, float fHeight, EVENTTYPE type);
void DeleteEventLogo(void);
#endif