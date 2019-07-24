//=============================================================================
//
// �T�E���h���� [sound.cpp]
// Author : Ryota Kinoshita
//
//=============================================================================
#include "sound.h"
//*****************************************************************************
// �p�����[�^�\���̒�`
//*****************************************************************************
typedef struct
{
	char *pFilename;	// �t�@�C����
	int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	D3DXVECTOR3 pos;	// �T�E���h�̈ʒu
} SOUNDPARAM;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
IXAudio2 *g_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X�ւ̃|�C���^
IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X�ւ̃|�C���^
BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�ւ̃|�C���^
DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

															// �e���f�ނ̃p�����[�^
SOUNDPARAM g_aSoundParam[SOUND_LABEL_MAX] =
{
	{ "data/BGM/Title000.wav", -1 },		// �^�C�g��
	{ "data/BGM/M_Select000.wav", -1 },		// �Q�[��
	{ "data/BGM/Select000.wav", -1 },		// �Q�[��
	{ "data/BGM/Buttle000.wav", -1 },		// �Q�[��
	{ "data/BGM/Buttle001.wav", -1 },		// �Q�[��
	{ "data/BGM/Result000.wav", -1 },		// �Q�[��
	{ "data/SE/����SE/hit000.wav", 0 },		// �q�b�g000
	{ "data/SE/����SE/hit001.wav", 0 },		// �q�b�g001
	{ "data/SE/����SE/jump000.wav", 0 },	// �W�����v
	{ "data/SE/����SE/Land000.wav", 0 },	// ���n
	{ "data/SE/����SE/Character_Move000.wav", 0 },	// �ړ�
	{ "data/SE/�V�X�e��/GameEnd000.wav", 0 },		// �Q�[���G���h000
	{ "data/SE/�V�X�e��/GaneSetting000.wav", 0 },	// �Q�[���Z�b�g000
	{ "data/SE/�V�X�e��/GameStart000.wav", 0 },		//�Q�[���X�^�[�g000
	{ "data/SE/�V�X�e��/GameStart001.wav", 0 },		// �Q�[���X�^�[�g001
	{ "data/SE/�V�X�e��/TimeUp000.wav", 0 },		// �^�C���A�b�v000
	{ "data/SE/�V�X�e��/Pause000.wav", 0 },		// �|�[�Y000
	{ "data/SE/�V�X�e��/SystemSelect000.wav", 0 },		// �|�[�Y000
	//���{�b�g
	{ "data/SE/���{�b�g/�K�[�h/Robot_Guard000.wav", 0 },	//���{�b�g�@�K�[�h
	{ "data/SE/���{�b�g/�Ԃ����/Robot_Blow000.wav", 0 },	//���{�b�g�@�Ԃ����
	{ "data/SE/���{�b�g/���/Robot_Avoid000.wav", 0 },		//���{�b�g�@���
	{ "data/SE/���{�b�g/�U��/Robot_Attack000.wav", 0 },		//���{�b�g�@�U�� 000
	{ "data/SE/���{�b�g/�U��/Robot_Attack001.wav", 0 },		//���{�b�g�@�U�� 001
	{ "data/SE/���{�b�g/�U��/Robot_Attack002.wav", 0 },		//���{�b�g�@�U��002
	{ "data/SE/���{�b�g/�U��/Robot_Attack003.wav", 0 },		//���{�b�g�@�U��003
	{ "data/SE/���{�b�g/�U��/Robot_Attack004.wav", 0 },		//���{�b�g�@�U��004
	{ "data/SE/���{�b�g/�U��/Robot_Attack005.wav", 0 },		//���{�b�g�@�U��005
	{ "data/SE/���{�b�g/�퓬�s�\/Robot_Down000.wav", 0 },  //���{�b�g�@�퓬�s�\
	{ "data/SE/���{�b�g/������/Robot_Throw000.wav", 0 },	//���{�b�g�@������
	{ "data/SE/���{�b�g/��_���[�W/Robot_Damage000.wav", 0 },// ���{�b�g�@��_���[�W
	{ "data/SE/���{�b�g/�ړ�/Robot_Move000.wav", 0 },// ���{�b�g�@�ړ�
	{ "data/SE/���{�b�g/�W�����v/Robot_Jump000.wav", 0 },// ���{�b�g�@�W�����v

	 //�͓�
	{ "data/SE/�͓�/�K�[�h/Kappa_Guard000.wav", 0 }, // �͓��@�K�[�h
	{ "data/SE/�͓�/�Ԃ����/Kappa_Blow000.wav", 0 },//�͓��@�Ԃ����
	{ "data/SE/�͓�/���/Kappa_Avoid000.wav", 0 },   // �͓��@���
	{ "data/SE/�͓�/�U��/Kappa_Attack000.wav", 0 },  // �͓��@�U��000
	{ "data/SE/�͓�/�U��/Kappa_Attack001.wav", 0 },  // �͓��@�U��001
	{ "data/SE/�͓�/�U��/Kappa_Attack002.wav", 0 },  // �͓��@�U��002
	{ "data/SE/�͓�/�U��/Kappa_Attack003.wav", 0 },  // �͓��@�U��003
	{ "data/SE/�͓�/�U��/Kappa_Attack004.wav", 0 },  // �͓��@�U��004
	{ "data/SE/�͓�/�U��/Kappa_Attack005.wav", 0 },  // �͓��@�U��005
	{ "data/SE/�͓�/�퓬�s�\/Kappa_Down000.wav", 0 },//�͓��@�퓬�s�\
	{ "data/SE/�͓�/�퓬�s�\/Kappa_Down001.wav", 0 },//�͓��@�퓬�s�\
	{ "data/SE/�͓�/������/Kappa_Throw000.wav", 0 }, // �͓��@������
	{ "data/SE/�͓�/��_���[�W/Kappa_Damage000.wav", 0 },//�͓��@��_���[�W 000
	{ "data/SE/�͓�/��_���[�W/Kappa_Damage001.wav", 0 },//�͓��@��_���[�W 001
	{ "data/SE/�͓�/��_���[�W/Kappa_Damage002.wav", 0 },//�͓��@��_���[�W 002
	{ "data/SE/�͓�/������/Kappa_Win000.wav", 0 },      //�͓��@������
	{ "data/SE/�͓�/�ړ�/Kappa_Move000.wav", 0 },      //�͓��@�ړ�
	//�l��
	{ "data/SE/�l��/�K�[�h/Girl_Guard000.wav", 0 },  // �l�ԁ@�K�[�h
	{ "data/SE/�l��/�K�[�h/Girl_Guard001.wav", 0 },  // �l�ԁ@�K�[�h
	{ "data/SE/�l��/�Ԃ����/Girl_Blow000.wav", 0 }, //�l�ԁ@�Ԃ����
	{ "data/SE/�l��/���/Girl_Avoid000.wav", 0 },    //�l�ԁ@���
	{ "data/SE/�l��/�U��/Girl_Attack000.wav", 0 },   //�l�ԁ@�U��  000
	{ "data/SE/�l��/�U��/Girl_Attack001.wav", 0 },   //�l�ԁ@�U��001
	{ "data/SE/�l��/�U��/Girl_Attack002.wav", 0 },   //�l�ԁ@�U��002
	{ "data/SE/�l��/�U��/Girl_Attack003.wav", 0 },   //�l�ԁ@�U��003
	{ "data/SE/�l��/�U��/Girl_Attack004.wav", 0 },   //�l�ԁ@�U��004
	{ "data/SE/�l��/�U��/Girl_Attack005.wav", 0 },   //�l�ԁ@�U��005
	{ "data/SE/�l��/�U��/Girl_Attack006.wav", 0 },   //�l�ԁ@�U��006
	{ "data/SE/�l��/�U��/Girl_Attack007.wav", 0 },   //�l�ԁ@�U��007
	{ "data/SE/�l��/�U��/Girl_Attack008.wav", 0 },   //�l�ԁ@�U��008
	{ "data/SE/�l��/�U��/Girl_Attack009.wav", 0 },   //�l�ԁ@�U��009
	{ "data/SE/�l��/�퓬�s�\/Girl_Down000.wav", 0 },  //�l�ԁ@�퓬�s�\
	{ "data/SE/�l��/������/Girl_Throw000.wav", 0 },   //�l�ԁ@������
	{ "data/SE/�l��/��_���[�W/Girl_Damage000.wav", 0 },//�l�� ��_���[�W
	{ "data/SE/�l��/������/Girl_win.wav", 0 },      //�l�� �������@

	//�V��
	{ "data/SE/�V��/�K�[�h/Tengu_Guard000.wav", 0 },// �@�V��@�K�[�h
	{ "data/SE/�V��/�Ԃ����/Tengu_Blow000.wav", 0 },//�@�V��@�Ԃ����
	{ "data/SE/�V��/���/Tengu_Avoid000.wav", 0 },// �@�@�V��@���
	{ "data/SE/�V��/�U��/Tengu_Attack000.wav", 0 },// �@�@�V��@�U��000
	{ "data/SE/�V��/�U��/Tengu_Attack001.wav", 0 },// �@�@�V��@�U��001
	{ "data/SE/�V��/�U��/Tengu_Attack002.wav", 0 },// �@�@�V��@�U��002
	{ "data/SE/�V��/�U��/Tengu_Attack003.wav", 0 },// �@�@�V��@�U��003
	{ "data/SE/�V��/�U��/Tengu_Attack004.wav", 0 },// �@�@�V��@�U��004
	{ "data/SE/�V��/�U��/Tengu_Attack005.wav", 0 },// �@�@�V��@�U��005
	{ "data/SE/�V��/�퓬�s�\/Tengu_Down000.wav", 0 },// �@�V��@�퓬�s�\ 000
	{ "data/SE/�V��/�퓬�s�\/Tengu_Down001.wav", 0 },// �@�V��@�퓬�s�\ 001
	{ "data/SE/�V��/������/Tengu_Throw000.wav", 0 },// �@�@�V��@������
	{ "data/SE/�V��/��_���[�W/Tengu_Damage000.wav", 0 },//�V��@��_���[�W
	{ "data/SE/�V��/������/Tengu_Win000.wav", 0 },//�V��@������
	//��
	{ "data/SE/��/�K�[�h/Fox_Guard000.wav", 0 },// �@�ρ@�K�[�h
	{ "data/SE/��/�Ԃ����/Fox_Blow000.wav", 0 },//�@�ρ@�Ԃ����
	{ "data/SE/��/���/Fox_Avoid000.wav", 0 },// �@�@�ρ@���
	{ "data/SE/��/�U��/Fox_Attack000.wav", 0 },// �@�@�ρ@�U��000
	{ "data/SE/��/�U��/Fox_Attack001.wav", 0 },// �@�@�ρ@�U��001
	{ "data/SE/��/�U��/Fox_Attack002.wav", 0 },// �@�@�ρ@�U��002
	{ "data/SE/��/�U��/Fox_Attack003.wav", 0 },// �@�@�ρ@�U��003
	{ "data/SE/��/�U��/Fox_Attack004.wav", 0 },// �@�@�ρ@�U��004
	{ "data/SE/��/�U��/Fox_Attack005.wav", 0 },// �@�@�ρ@�U��005
	{ "data/SE/��/�퓬�s�\/Fox_Down000.wav", 0 },// �@�ρ@�퓬�s�\
	{ "data/SE/��/������/Fox_Throw000.wav", 0 },// �@�@�ρ@������
	{ "data/SE/��/��_���[�W/Fox_Damage000.wav", 0 },//�ρ@��_���[�W
	{ "data/SE/��/������/Fox_Win000.wav", 0 },     //�ρ@�������@
	// �퓬�n
	{ "data/SE/�퓬����SE/Tengu_Wind000.wav", 0 },// ��
	{ "data/SE/�퓬����SE/Tengu_Wing001.wav", 0 },// ��
	{ "data/SE/�퓬����SE/Slash000.wav", 0 },// �Ђ�����000
	{ "data/SE/�퓬����SE/Slash001.wav", 0 },// �Ђ�����001
	{ "data/SE/�퓬����SE/Slash002.wav", 0 },// �Ђ�����002
	{ "data/SE/�퓬����SE/Fox_Flame000.wav", 0 },// �Ή����� 000
	{ "data/SE/�퓬����SE/Fox_Flame001.wav", 0 },// �Ή����ˁ@001
	{ "data/SE/�퓬����SE/bomb1.wav", 0 },// �����@000
	{ "data/SE/�퓬����SE/bomb2.wav", 0 },// �����@001
	{ "data/SE/�퓬����SE/Guard.wav", 0 },// �K�[�h
	{ "data/SE/�퓬����SE/GuardBreak.wav", 0 },// �K�[�h�N���b�V��
	// ���ہ@
	{ "data/SE/taiko01.wav", 0 },// ���ۉ�
	{ "data/SE/taiko02.wav", 0 },// ���ۉ�
	{ "data/SE/taiko03.wav", 0 },// ���ۉ�
	{ "data/SE/taiko04.wav", 0 },// ���ۉ�
	// ����
	{ "data/SE/����/Cheer000.wav", 0 },// ����
	{ "data/SE/����/Cheer001.wav", 0 },// ����
	// �V�X�e��
	{ "data/SE/Select.wav", 0 },// �ړ���
	{ "data/SE/Decision001.wav", 0 },// ���艹
	{ "data/SE/Decision000.wav", 0 },// ���艹
	{ "data/SE/�K�E�Z�pSE/CutIn.wav", 0 },// �J�b�g�C��
	{ "data/SE/�K�E�Z�pSE/SpecialLogo.wav", 0 },// SPECIAL
	{ "data/SE/CharacterSelect.wav", 0 },// �L�����N�^�[�I��
	{ "data/SE/SelectInfo.wav", 0 },// ��������
	{ "data/SE/Alert000.wav", 0 },// �x����
	{ "data/SE/Event_Thunder.wav", 0 },// ��
	{ "data/SE/Event_Rain.wav", 1 },// �J
	{ "data/SE/Event_Flood.wav", 1 },// �×�
	{ "data/SE/LifeUp000.wav", 0 },// UP
	{ "data/SE/AttackUp000.wav", 0 },// UP
	{ "data/SE/SpeedUp000.wav", 0 },// UP
	{ "data/SE/Event_Meteo.wav", -1 },// ���e�I
	{ "data/SE/Event_Explosion.wav", 0 },// ����
	{ "data/SE/Event_Gust.wav", 0 },// �˕�
	{ "data/SE/TimeLimit.wav", 0 },// �˕�



};

//=============================================================================
// ������
//=============================================================================
HRESULT InitSound(HWND hWnd)
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&g_pXAudio2, 0);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();
		return E_FAIL;
	}

	// �}�X�^�[�{�C�X�̐���
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if (g_pXAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(g_aSoundParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�

			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		if (dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �\�[�X�{�C�X�̐���
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = g_aSizeAudio[nCntSound];
		buffer.pAudioData = g_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = g_aSoundParam[nCntSound].nCntLoop;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		g_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSound(void)
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);

			// �\�[�X�{�C�X�̔j��
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;

			// �I�[�f�B�I�f�[�^�̊J��
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}

	// �}�X�^�[�{�C�X�̔j��
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;

	if (g_pXAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}

	// COM���C�u�����̏I������
	CoUninitialize();
}

//=============================================================================
// �Z�O�����g�Đ�(��~)
//=============================================================================
HRESULT PlaySound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = g_aSoundParam[label].nCntLoop;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
	 // �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_apSourceVoice[label]->Start(0);


	return S_OK;

}

//=============================================================================
// �Z�O�����g��~
//=============================================================================
void StopSound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
	 // �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//=============================================================================
// �Z�O�����g��~
//=============================================================================
void StopSound(void)
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);

			// �I�[�f�B�I�o�b�t�@�̍폜
			g_apSourceVoice[nCntSound]->FlushSourceBuffers();
		}
	}
}

//=============================================================================
// �`�����N�̃`�F�b�N
//=============================================================================
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

//=============================================================================
// �`�����N�f�[�^�̓ǂݍ���
//=============================================================================
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}
//=============================================================================
// ���ʕω�
//=============================================================================
void ChangeVolume(SOUND_LABEL label, float fVolume)
{
	g_apSourceVoice[label]->SetVolume(fVolume);
}
//=============================================================================
// ���a�`�F�b�N
//=============================================================================
void CheckPos(D3DXVECTOR3 pos)
{
	//bool bGetRadius = false;
	//for (int nCntPos = 0; nCntPos < 3; nCntPos++)
	//{
	//	float fPosX = (g_aSoundParam[SOUND_LABEL_SE_WATERFALL].pos.x - pos.x);
	//	float fPosZ = (g_aSoundParam[SOUND_LABEL_SE_WATERFALL].pos.z + nCntPos*500 - pos.z);
	//	float fLength = fPosX*fPosX + fPosZ*fPosZ;	// �v���C���[�ƓG�̋���
	//	for (int nCntSound = 0; nCntSound < 100; nCntSound++)
	//	{
	//		float fRadius = float((3500 * 3500) / (nCntSound + 1));		// Active�͈�
	//		if (fRadius > fLength &&
	//			-fRadius < fLength)
	//		{// ���ʕω�
	//			g_apSourceVoice[SOUND_LABEL_SE_WATERFALL]->SetVolume(nCntSound / 10.0f);
	//			bGetRadius = true;
	//		}
	//	}
	//	if (bGetRadius == false)
	//	{
	//		g_apSourceVoice[SOUND_LABEL_SE_WATERFALL]->SetVolume(0.0f);

	//	}
	//}
}