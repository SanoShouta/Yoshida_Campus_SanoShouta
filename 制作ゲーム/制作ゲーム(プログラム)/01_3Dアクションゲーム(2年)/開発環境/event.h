//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �C�x���g���� [event.h]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _EVENT_H_
#define _EVENT_H_		// 2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �}�N����`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define EVENT_TOPMAX		(4)		// ���_��

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �񋓑̂̒�`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef enum
{// �C�x���g�̎��
	EVENTTYPE_NONE = 0,			// �����Ȃ�
	EVENTTYPE_WATER,			// �^��
	EVENTTYPE_FIRE,				// �Ύ�
	EVENTTYPE_FALLING_ROCK,		// �����̗���
	EVENTTYPE_FALLING_BIGROCK,	// �傫����̗���
	EVENTTYPE_METEORSHOWER,		// �����Q
	EVENTTYPE_METEORITE,		// 覐�
	EVENTTYPE_RAIN,				// �J�Ō����ɂ���
	EVENTTYPE_THUNDER,			// ��
	EVENTTYPE_FALLING_CHOUTIN,	// �񓔗���
	EVENTTYPE_FALLING_BRANCH,	// �؂̎}����
	EVENTTYPE_LEEF,				// �t���ςŌ����ɂ���
	EVENTTYPE_GUST,				// �˕�
	EVENTTYPE_MAX,				// �ő吔
}EVENTTYPE;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �v���g�^�C�v�錾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetEvent(EVENTTYPE eventType);
void InitEvent();
void UninitEvent();
void UpdateEvent();
D3DXCOLOR GetEventColor(void);
void SetEventColor(D3DXCOLOR col);
EVENTTYPE GetEventType(void);
#endif