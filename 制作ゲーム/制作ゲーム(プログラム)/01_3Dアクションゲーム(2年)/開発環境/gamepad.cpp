////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �R���g���[���[���͏��� [gamepad.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "gamepad.h"

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidinstance, VOID* pContext);
BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext);

//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
LPDIRECTINPUT8 g_pGamePad = NULL;			// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
GamePad		   g_aGamePad[MAX_GAMEPAD];		// �Q�[���p�b�h�̏��
int		   	   g_JoyconNumber;				// joystick�p�R�[���o�b�N�֐��Ŏg���W���C�R���̔ԍ�
int		   	   g_JoyconAxesNumber;			// joystick�̋@�\�R�[���o�b�N�֐��Ŏg���W���C�R���̔ԍ�

//==============================================================================================================================
// �Q�[���p�b�h�̏�����
//==============================================================================================================================
HRESULT InitGamePad(HINSTANCE hInstance, HWND hWnd)
{
	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		g_aGamePad[nCnt].pDevGamePad = NULL;
	}
	g_JoyconNumber = 0;
	g_JoyconAxesNumber = 0;

	HRESULT hr;
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pGamePad, NULL)))
	{
		return FALSE;
	}

	// ���̓f�o�C�X(�R���g���[���[)�̐���
	if (FAILED(g_pGamePad->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY)))		// ��4���� (ATTACHEDONLY = ���ݐڑ�����Ă���W���C�X�e�B�b�N�̂݌��o����)
	{
		return FALSE;
	}

	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		if (g_aGamePad[nCnt].pDevGamePad != NULL)
		{// �R���g���[���[���q�����Ă��Ȃ��Ƃ��������Ȃ�
			// �f�o�C�X�Ƀf�[�^�t�H�[�}�b�g��ݒ�
			if (FAILED(hr = g_aGamePad[nCnt].pDevGamePad->SetDataFormat(&c_dfDIJoystick2)))
			{
				return FALSE;
			}

			// �������[�h��ݒ�
			if (FAILED(hr = g_aGamePad[nCnt].pDevGamePad->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
			{
				return FALSE;
			}

			// �Q�[���p�b�h�̋@�\�̏������W
			g_aGamePad[nCnt].GamepadCaps.dwSize = sizeof(DIDEVCAPS);

			if (FAILED(hr = g_aGamePad[nCnt].pDevGamePad->GetCapabilities(&g_aGamePad[nCnt].GamepadCaps)))
			{
				g_aGamePad[nCnt].pDevGamePad->Release();
				return FALSE;
			}

			// �e���̃��[�h�ݒ�
			hr = g_aGamePad[nCnt].pDevGamePad->EnumObjects(EnumAxesCallback, (void*)g_aGamePad[nCnt].pDevGamePad, DIDFT_AXIS);

			g_JoyconAxesNumber++;		// �ԍ���i�߂�

			// �Q�[���p�b�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
			hr = g_aGamePad[nCnt].pDevGamePad->Poll();

			if (FAILED(hr))
			{
				hr = g_aGamePad[nCnt].pDevGamePad->Acquire();

				while (hr == DIERR_INPUTLOST)
				{
					hr = g_aGamePad[nCnt].pDevGamePad->Acquire();
				}
			}
		}
	}

	return S_OK;
}

//==============================================================================================================================
// �Q�[���p�b�h�̏I������
//==============================================================================================================================
void UninitGamePad(void)
{
	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		if (g_aGamePad[nCnt].pDevGamePad != NULL)
		{
			g_aGamePad[nCnt].pDevGamePad->Unacquire();
			g_aGamePad[nCnt].pDevGamePad->Release();
			g_aGamePad[nCnt].pDevGamePad = NULL;
		}
	}
	// DirectInput�I�u�W�F�N�g�̊J��
	if (g_pGamePad != NULL)
	{
		g_pGamePad->Release();
		g_pGamePad = NULL;
	}
}

//==============================================================================================================================
// �Q�[���p�b�h�̍X�V����
//==============================================================================================================================
void UpdateGamePad(void)
{
	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		if (g_aGamePad[nCnt].pDevGamePad != NULL)
		{
			DIJOYSTATE2 aGamePadKeyState;								// �R���g���[���[�̓��͏��
			BYTE aLeftAnalogStick[ANALOG_STICK_MAX] = { 0,0,0,0 };		// �X�e�B�b�N�̓��͏��
			BYTE aPov[POV_MAX] = { 0,0,0,0 };							// �\���L�[�̓��͏��

			HRESULT hr;
			hr = g_aGamePad[nCnt].pDevGamePad->Poll();

			// ���̓f�o�C�X����f�[�^���擾
			if (SUCCEEDED(hr = g_aGamePad[nCnt].pDevGamePad->GetDeviceState(sizeof(DIJOYSTATE2), &aGamePadKeyState)))
			{
				// �{�^��
				for (int nCntKey = 0; nCntKey < GAMEPAD_NUM_KEY_MAX; nCntKey++)
				{
					// �R���g���[���[�̓��͏��̕ۑ�(�g���K�[)
					g_aGamePad[nCnt].aGamePadKeyStateTrigger[nCntKey] = (g_aGamePad[nCnt].aGamePadKeyState[nCntKey] ^ aGamePadKeyState.rgbButtons[nCntKey]) & aGamePadKeyState.rgbButtons[nCntKey];
					// �R���g���[���[�̓��͏��̕ۑ�(�����[�X)
					g_aGamePad[nCnt].aGamePadKeyStateRelease[nCntKey] = (aGamePadKeyState.rgbButtons[nCntKey] ^ g_aGamePad[nCnt].aGamePadKeyState[nCntKey]) & g_aGamePad[nCnt].aGamePadKeyState[nCntKey];
					// �R���g���[���[�̓��͏��̕ۑ�(�v���X)
					g_aGamePad[nCnt].aGamePadKeyState[nCntKey] = aGamePadKeyState.rgbButtons[nCntKey];
				}

				//--------------------------------------------------------
				// ���A�i���O�X�e�B�b�N�̓��͏��̎擾
				//--------------------------------------------------------
				if (aGamePadKeyState.lY < -GAMEPAD_DEADZONE)
				{// ���X�e�B�b�N����ɓ|����
					aLeftAnalogStick[ANALOG_STICK_UP] = 128;			// ���͂��ꂽ
				}
				else if (aGamePadKeyState.lY > GAMEPAD_DEADZONE)
				{// ���X�e�B�b�N�����ɓ|����
					aLeftAnalogStick[ANALOG_STICK_DOWN] = 128;			// ���͂��ꂽ
				}
				else if (aGamePadKeyState.lX > GAMEPAD_DEADZONE)
				{// ��g�X�e�B�b�N���E�ɓ|����
					aLeftAnalogStick[ANALOG_STICK_RIGHT] = 128;			// ���͂��ꂽ
				}
				else if (aGamePadKeyState.lX < -GAMEPAD_DEADZONE)
				{// ���X�e�B�b�N�����ɓ|����
					aLeftAnalogStick[ANALOG_STICK_LEFT] = 128;			// ���͂��ꂽ
				}

				for (int nCntAnalogStick = 0; nCntAnalogStick < ANALOG_STICK_MAX; nCntAnalogStick++)
				{// ���A�i���O�X�e�B�b�N�̕����̎�ޕ����[�v
				 // ���X�e�B�b�N�̃g���K�[���
					g_aGamePad[nCnt].aLeftAnalogStickTrigger[nCntAnalogStick] = (g_aGamePad[nCnt].aLeftAnalogStick[nCntAnalogStick] ^ aLeftAnalogStick[nCntAnalogStick])&aLeftAnalogStick[nCntAnalogStick];		// ���A�i���O�X�e�B�b�N�̃g���K�[���
																																													// ���X�e�B�b�N�̃v���X���
					g_aGamePad[nCnt].aLeftAnalogStick[nCntAnalogStick] = aLeftAnalogStick[nCntAnalogStick];																						// ���A�i���O�X�e�B�b�N�̃v���X���
				}

				//--------------------------------------------------------
				// �\���L�[�̓��͏��̎擾
				//--------------------------------------------------------
				if (aGamePadKeyState.rgdwPOV[0] == 0.0f)
				{// �\���L�[�̏��������
					aPov[POV_UP] = 128;			// ���͂��ꂽ
				}
				if (aGamePadKeyState.rgdwPOV[0] == 18000.0f)
				{// �\���L�[�̉���������
					aPov[POV_DOWN] = 128;			// ���͂��ꂽ
				}
				if (aGamePadKeyState.rgdwPOV[0] == 9000.0f)
				{// �\���L�[�̉E��������
					aPov[POV_RIGHT] = 128;			// ���͂��ꂽ
				}
				if (aGamePadKeyState.rgdwPOV[0] == 27000.0f)
				{// �\���L�[�̍���������
					aPov[POV_LEFT] = 128;			// ���͂��ꂽ
				}

				for (int nCntPov = 0; nCntPov < POV_MAX; nCntPov++)
				{// �\���L�[�̕����̎�ޕ����[�v
				 // �\���L�[�̃g���K�[���
					g_aGamePad[nCnt].aPovTrigger[nCntPov] = (g_aGamePad[nCnt].aPov[nCntPov] ^ aPov[nCntPov])&aPov[nCntPov];		// �\���L�[�̃g���K�[���

					// �\���L�[�̃v���X���
					g_aGamePad[nCnt].aPov[nCntPov] = aPov[nCntPov];		// �\���L�[�̃v���X���
				}
				g_aGamePad[nCnt].aGamePad = aGamePadKeyState;			// ���݂̏�Ԃ�ۑ�
			}
			else
			{
				g_aGamePad[nCnt].pDevGamePad->Acquire();				// �Q�[���p�b�h�ւ̃A�N�Z�X�����l��
			}
		}
	}
}

//==============================================================================================================================
// �Q�[���p�b�h�̓��͏��(�X�e�B�b�N)���擾
//==============================================================================================================================
GamePad *GetgamePadStick(void)
{
	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		if (g_aGamePad[nCnt].pDevGamePad != NULL)
		{// �f�o�C�X��NULL����Ȃ�������
			// �W���C�X�e�B�b�N�̏����擾
			g_aGamePad[nCnt].pDevGamePad->GetDeviceState(sizeof(DIJOYSTATE2), &g_aGamePad[nCnt].aGamePad);
		}
	}
	return &g_aGamePad[0];			// �W���C�X�e�B�b�N�̏���Ԃ�
}

//==============================================================================================================================
// �Q�[���p�b�h�̓��͏��(�v���X���)���擾
//==============================================================================================================================
bool GetGamePadPress(int nIndex, int nKey)
{
	if (g_aGamePad[nIndex].pDevGamePad == NULL)
	{// �ڑ�����Ă��Ȃ��Ȃ�FALSE��Ԃ�
		return false;
	}
	return(g_aGamePad[nIndex].aGamePadKeyState[nKey] & 0x80) ? true : false;
}

//==============================================================================================================================
// �Q�[���p�b�h�̓��͏��(�g���K�[���)���擾
//==============================================================================================================================
bool GetGamePadTrigger(int nIndex, int nKey)
{
	if (g_aGamePad[nIndex].pDevGamePad == NULL)
	{// �ڑ�����Ă��Ȃ��Ȃ�FALSE��Ԃ�
		return false;
	}
	return(g_aGamePad[nIndex].aGamePadKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//==============================================================================================================================
// �Q�[���p�b�h�̓��͏��(�����[�X���)���擾
//==============================================================================================================================
bool GetGamePadRelease(int nIndex, int nKey)
{
	if (g_aGamePad[nIndex].pDevGamePad == NULL)
	{// �ڑ�����Ă��Ȃ��Ȃ�FALSE��Ԃ�
		return false;
	}
	return(g_aGamePad[nIndex].aGamePadKeyStateRelease[nKey] & 0x80) ? true : false;
}
//==============================================================================================================================
// �Q�[���p�b�h�̃X�e�B�b�N���͏��(�v���X���)���擾
//==============================================================================================================================
bool GetGamePadStickPress(int nIndex, int nKey)
{
	if (g_aGamePad[nIndex].pDevGamePad == NULL)
	{// �ڑ�����Ă��Ȃ��Ȃ�FALSE��Ԃ�
		return false;
	}
	return (g_aGamePad[nIndex].aLeftAnalogStick[nKey] & 0x80) ? true : false;
}

//==============================================================================================================================
// �Q�[���p�b�h�̃X�e�B�b�N���͏��(�g���K�[���)���擾
//==============================================================================================================================
bool GetGamePadStickTrigger(int nIndex, int nKey)
{
	if (g_aGamePad[nIndex].pDevGamePad == NULL)
	{// �ڑ�����Ă��Ȃ��Ȃ�FALSE��Ԃ�
		return false;
	}
	return (g_aGamePad[nIndex].aLeftAnalogStickTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �\���L�[���͏��(�v���X�[���)���擾
//=============================================================================
bool GetPovTpress(int nIndex, int nAngle)
{
	if (g_aGamePad[nIndex].pDevGamePad == NULL)
	{// �ڑ�����Ă��Ȃ��Ȃ�FALSE��Ԃ�
		return false;
	}
	return (g_aGamePad[nIndex].aPov[nAngle] & 0x80) ? true : false;
}

//=============================================================================
// �\���L�[���͏��(�g���K�[���)���擾
//=============================================================================
bool GetPovTtigger(int nIndex, int nAngle)
{
	if (g_aGamePad[nIndex].pDevGamePad == NULL)
	{// �ڑ�����Ă��Ȃ��Ȃ�FALSE��Ԃ�
		return false;
	}
	return (g_aGamePad[nIndex].aPovTrigger[nAngle] & 0x80) ? true : false;
}

//*****************************************************************************
// joystick�p�R�[���o�b�N�֐�
//*****************************************************************************
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidinstance, VOID* pContext)
{
	HRESULT hr;

	// �񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���擾
	hr = g_pGamePad->CreateDevice(pdidinstance->guidInstance, &g_aGamePad[g_JoyconNumber].pDevGamePad, NULL);

	// �f�o�C�X�����o�o���Ȃ������ꍇ
	if (FAILED(hr))
	{
		return DIENUM_CONTINUE;
	}

	g_JoyconNumber++;		// �ԍ���i�߂�

	return DIENUM_CONTINUE;
}

//*****************************************************************************
// joystick�̋@�\�R�[���o�b�N�֐�
//*****************************************************************************
BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext)
{
	HRESULT hr;
	DIPROPRANGE diprg;

	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	diprg.lMin = -(GAMEPAD_DEADZONE / GAMEPAD_DEADZONE * MAX_ZONE);				// �\���L�[�̍ŏ��l [��] [��]
	diprg.lMax = GAMEPAD_DEADZONE / GAMEPAD_DEADZONE * MAX_ZONE;				// �\���L�[�̍ő�l [��] [�E]

	// �f�o�C�X�ɐݒ�
	hr = g_aGamePad[g_JoyconAxesNumber].pDevGamePad->SetProperty(DIPROP_RANGE, &diprg.diph);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}

//*****************************************************************************
// �Q�[���p�b�h�̎h�����Ă��鐔�̎擾
//*****************************************************************************
int GetGamePadNum(void)
{
	return g_JoyconNumber;
}