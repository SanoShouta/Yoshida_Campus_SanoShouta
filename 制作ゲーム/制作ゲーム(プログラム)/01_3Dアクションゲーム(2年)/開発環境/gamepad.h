//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �R���g���[���[���͏��� [gamepad.h]
// Author : Ryota Kinoshita
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAMEPAD_DEADZONE		(3)
#define MAX_ZONE				(1000)
#define	GAMEPAD_NUM_KEY_MAX		(128)		// �L�[�̍ő吔
#define MAX_GAMEPAD				(4)			// �R���g���[���[�̐�

#define BUTTON_X	   (ELECOM_X)		// X�{�^���̔ԍ�
#define BUTTON_Y	   (ELECOM_Y)		// Y�{�^���̔ԍ�
#define BUTTON_A	   (ELECOM_A)		// A�{�^���̔ԍ�
#define BUTTON_B	   (ELECOM_B)		// B�{�^���̔ԍ�
#define BUTTON_L1	   (ELECOM_L1)		// L1�{�^���̔ԍ�
#define BUTTON_R1	   (ELECOM_R1)		// R1�{�^���̔ԍ�
#define BUTTON_L2	   (ELECOM_L2)		// L2�{�^���̔ԍ�
#define BUTTON_R2	   (ELECOM_R2)		// R2�{�^���̔ԍ�
#define BUTTON_L_STICK (ELECOM_L_STICK)	// L_STICK�{�^���̔ԍ�
#define BUTTON_R_STICK (ELECOM_R_STICK)	// R_STICK�{�^���̔ԍ�
#define BUTTON_BACK	   (ELECOM_BACK)	// BACK�{�^���̔ԍ�
#define BUTTON_START   (ELECOM_START)	// START�{�^���̔ԍ�
#define BUTTON_GUIDE   (ELECOM_GUIDE)	// GUIDE�{�^���̔ԍ�
#define BUTTON_MAX	   (ELECOM_MAX)		// �{�^���̍ő�

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
//typedef enum
//{
//	STICK_NONE = 0,
//	STICK_UP ,
//	STICK_RIGHT ,
//	STICK_LEFT ,
//	STICK_DOWN ,
//	STICK_MAX,
//}STICK_CTRL;

typedef enum
{// �A�i���O�X�e�B�b�N�̕����̎��(4����)
	ANALOG_STICK_UP = 0,
	ANALOG_STICK_RIGHT,
	ANALOG_STICK_LEFT,
	ANALOG_STICK_DOWN,
	ANALOG_STICK_MAX
}ANALOG_STICK;

typedef enum
{// �\���L�[�̕����̎��
	POV_UP = 0,
	POV_DOWN,
	POV_RIGHT,
	POV_LEFT,
	POV_MAX
}POV;

typedef enum
{
	ELECOM_X = 0,
	ELECOM_Y,
	ELECOM_A,
	ELECOM_B,
	ELECOM_L1,
	ELECOM_R1,
	ELECOM_L2,
	ELECOM_R2,
	ELECOM_L_STICK,
	ELECOM_R_STICK,
	ELECOM_BACK,
	ELECOM_START,
	ELECOM_GUIDE,
	ELECOM_MAX
}ELECOM_CTRL;

typedef struct
{
	LPDIRECTINPUTDEVICE8 pDevGamePad;							// ���̓f�o�C�X(k�R���g���[���[)�ւ̃|�C���^
	DIDEVCAPS GamepadCaps;										// �Q�[���p�b�h�̋@�\���

	DIJOYSTATE2 aGamePad;										// �R���g���[���[�̏��

	BYTE		aGamePadKeyState[GAMEPAD_NUM_KEY_MAX];			// �W���C�X�e�B�b�N�̃v���X���͏��
	BYTE		aGamePadKeyStateTrigger[GAMEPAD_NUM_KEY_MAX];	// �W���C�X�e�B�b�N�̃g���K�[���͏��
	BYTE		aGamePadKeyStateRelease[GAMEPAD_NUM_KEY_MAX];	// �W���C�X�e�B�b�N�̃����[�X���͏��
	BYTE		aLeftAnalogStick[ANALOG_STICK_MAX];				// ���A�i���O�X�e�B�b�N�̃v���X���
	BYTE		aLeftAnalogStickTrigger[ANALOG_STICK_MAX];		// ���A�i���O�X�e�B�b�N�̃g���K�[���
	BYTE		aPov[POV_MAX];									// �\���L�[�̃v���X���
	BYTE		aPovTrigger[POV_MAX];							// �\���L�[�̃g���K�[���
}GamePad;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGamePad(HINSTANCE hInstance, HWND hWnd);
void UninitGamePad(void);
void UpdateGamePad(void);

// �Q�[���p�b�h�̃{�^�����͏��
bool GetGamePadPress(int nIndex, int nKey);
bool GetGamePadTrigger(int nIndex, int nKey);
bool GetGamePadRelease(int nIndex, int nKey);

// �Q�[���p�b�h�̃X�e�B�b�N�̓��͏��
bool GetGamePadStickPress(int nIndex, int nKey);
bool GetGamePadStickTrigger(int nIndex, int nKey);

// �Q�[���p�b�h�̏\���L�[�̓��͏��
bool GetPovTpress(int nIndex, int nAngle);
bool GetPovTtigger(int nIndex, int nAngle);

GamePad *GetgamePadStick(void);
int GetGamePadNum(void);
#endif
