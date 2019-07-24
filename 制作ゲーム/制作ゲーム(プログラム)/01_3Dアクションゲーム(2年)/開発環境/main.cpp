////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���C������ [main.cpp]
// Author : RyotaKinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "sound.h"
#include "input.h"
#include "gamepad.h"
#include "flontpolygon.h"
#include "player.h"
#include "fade.h"
#include "camera.h"
#include "light.h"
#include "game.h"
#include "Select.h"
#include "charsel.h"
#include "title.h"
#include "staff.h"
#include <time.h>
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define CLASS_NAME		"AppClass"				// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"�ǂ񂿂��o�g��"	// �E�C���h�E�̃L���v�V������
#define WINDOW_MODE		(true)		// false�ő剻 true�E�C���h�E
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);

//******************************************************************************************************************************
// �O���[�o���ϐ�:
//******************************************************************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT			g_pFont = NULL;			// �t�H���g�ւ̃|�C���^
int					g_nCountFPS = 0;		// FPS�J�E���^
MODE g_mode = MODE_TITLE;					// ���[�h
//MODE g_mode = MODE_SELECT;					// ���[�h
//MODE g_mode = MODE_CHARACTER;					// ���[�h
//MODE g_mode = MODE_GAME;					// ���[�h

D3DXMATRIX mView;
D3DXMATRIX mProj;
POINT g_Point;
bool g_bDebug[DRAW_DEBUG_MAX];
Shader g_Shader;
//==============================================================================================================================
// ���C���֐�
//==============================================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(0,
							CLASS_NAME,
							WINDOW_NAME,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							(rect.right - rect.left),
							(rect.bottom - rect.top),
							NULL,
							NULL,
							hInstance,
							NULL);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	// �e�J�E���^�[��������
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();		// �V�X�e���������擾(�~���b�P��)
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();		// �V�X�e���������擾(�~���b�P��)

	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			// �V�X�e���������擾
			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b�o��
				// FPS�𑪒�
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;		// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;					// �J�E���g���N���A
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60�b�o��
				dwExecLastTime = dwCurrentTime;		// ���������s����������ۑ�

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				// �}�E�X�J�[�\��
				GetPoint(hWnd);


				dwFrameCount++;		// �J�E���g�����Z
			}
		}
	}

	// �I������
	Uninit();

	// ����\��߂�
	timeEndPeriod(1);

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//==============================================================================================================================
// �E�C���h�E�v���V�[�W��
//==============================================================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_LBUTTONDOWN:


		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//==============================================================================================================================
// ����������
//==============================================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = WINDOW_MODE;									// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									hWnd,
									D3DCREATE_HARDWARE_VERTEXPROCESSING,
									&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_REF,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&d3dpp, &g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}
	// �����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ���C�e�B���O���[�h�L��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

	// �f�o�b�O�\���p�t�H���g��ݒ�
	// pDevice         : �f�o�C�X�ւ̃|�C���^
	// Height          : �����̍���
	// Width           : �����̕�
	// Weight          : �t�H���g�̑���
	// MipLevels       : �~�b�v�}�b�v���x����
	// Italic          : �C�^���b�N�t�H���g
	// CharSet         : �t�H���g�̕����Z�b�g
	// OutputPrecision : ���ۂ̃t�H���g�ƖړI�̃t�H���g�̃T�C�Y����ѓ����̈�v���@���w��
	// Quality         : ���ۂ̃t�H���g�ƖړI�̃t�H���g�Ƃ̈�v���@���w��
	// PitchAndFamily  : �s�b�`�ƃt�@�~���C���f�b�N�X
	// pFacename       : �t�H���g�̖��O��ێ����镶����
	// ppFont          : �t�H���g�ւ̃|�C���^
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "MS�S�V�b�N", &g_pFont);

	// �V�F�[�_�̐���
	D3DXCreateEffectFromFile(g_pD3DDevice,	// �`��f�o�C�X
		TEXT("Shader.hlsl"),			// �V�F�[�_���̑��΃p�X
		NULL,							// �v���v���Z�b�T���s���\����(NULL��OK)
		NULL,							// include������s���C���^�[�t�F�[�X(NULL��OK)
		D3DXSHADER_DEBUG,				// �ǂݍ��ݎ��̃I�v�V����(����̓f�o�b�O���[�h�œǂݍ���ł܂����A�ʏ�0�ɂ��Ă����܂�)
		0,								// �V�F�[�_�Ԃł���肷��ϐ����������ꍇ�Ɏw��(�ʏ�0��OK)
		&g_Shader.pShader,						// �V�F�[�_�̃|�C���^���擾
		NULL);							// �G���[���(�K�v�Ȃ����NULL��OK)
										// �e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(g_pD3DDevice,		// �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/ramp.png",			// �t�@�C���̖��O
		&g_Shader.pTexture);		// �e�N�X�`���ւ̃|�C���^

	// ���C�g�̐ݒ�
	g_Shader.pShader->SetVector("g_fLightDir", &D3DXVECTOR4(-0.89f, -0.1f, 0.94f, 0)); // <-�ЂƂ܂�[0]�Ԗڂ̃��C�g�̕����R�s�y���܂���

	//�t�����g�|���S��
	InitFlontPolygon();

	// �T�E���h����������
	InitSound(hWnd);
	// �L�[�{�[�h�̏���������
	InitKeyboard(hInstance, hWnd);
	// �Q�[���p�b�h�̏������ݒ�
	InitGamePad(hInstance, hWnd);
	// �t�F�[�h����������
	InitFade(g_mode);
	// �t�����g�|���S���̏���������
	InitFlontPolygon();
	// �v���C���[���f���ǂݍ���
	SetPlayerFileData(PLAYERTYPE_MATURI, "data/TEXT/maturi.txt");
	SetPlayerFileData(PLAYERTYPE_AMANO, "data/TEXT/tengu.txt");
	SetPlayerFileData(PLAYERTYPE_GOJOU, "data/TEXT/kappa.txt");
	SetPlayerFileData(PLAYERTYPE_MOMIJI, "data/TEXT/fox.txt");
	SetPlayerFileData(PLAYERTYPE_DONROID,"data/TEXT/robo.txt");
	SetObjectFileData();
	// ���[�h�̐ݒ�
	SetMode(g_mode);

	for (int nDebug = 0; nDebug < DRAW_DEBUG_MAX; nDebug++)
	{
		g_bDebug[nDebug] = false;
	}
	return S_OK;
}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void Uninit(void)
{
	if(g_pFont != NULL)
	{// �f�o�b�O�\���p�t�H���g�̊J��
		g_pFont->Release();
		g_pFont = NULL;
	}
	if (g_Shader.pShader != NULL)
	{// �V�F�[�_�[�J��
		g_Shader.pShader->Release();
		g_Shader.pShader = NULL;
	}
	if (g_Shader.pDecl != NULL)
	{
		g_Shader.pDecl->Release();
		g_Shader.pDecl = NULL;
	}
	// �L�[�{�[�h�̏I������
	UninitKeyboard();
	// �Q�[���p�b�h�̏I������
	UninitGamePad();

	// �t�����g�|���S��
	UninitFlontPolygon();

	// �T�E���h�̏I������
	UninitSound();
	// �^�C�g���̏I������
	UninitTitle();
	//�X�^�b�t���[���̏I������
	UninitStaff();
	// �Q�[���̏I������
	UninitGame();
	// ���U���g�̏I������
//	UninitResult();
	// �����L���O�̏I������
//	UninitRanking();
	// �t�F�[�h�̏I������
	UninitFade();
	// �v���C���[�I������
	UninitPlayer();
	if(g_pD3DDevice != NULL)
	{// �f�o�C�X�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	if(g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void Update(void)
{

	// �L�[�{�[�h�̍X�V����
	UpdateKeyboard();
	// �Q�[���p�b�h�̍X�V����
	UpdateGamePad();

	//�t�����g�|���S��
	UpdateFlontPolygon();

	if (GetKeyboardTrigger(DIK_F1) == true)
	{// �f�o�b�O���I���I�t
		g_bDebug[DRAW_DEBUG_POS] = g_bDebug[DRAW_DEBUG_POS] ? false : true;
	}
	if (GetKeyboardTrigger(DIK_F2) == true)
	{// ���C��
		g_bDebug[DRAW_DEBUG_LINE]= g_bDebug[DRAW_DEBUG_LINE] ? false : true;
	}
	if (GetKeyboardTrigger(DIK_F3) == true)
	{// �f�o�b�O���I���I�t
		g_bDebug[DRAW_DEBUG_WIREFRAME] = g_bDebug[DRAW_DEBUG_WIREFRAME] ? false : true;
	}
	switch (g_mode)
	{
	case MODE_TITLE:	// �^�C�g��
		UpdateTitle();
		break;
	case MODE_SELECT:	// �I�����
		UpdateSelect();
		break;
	case MODE_CHARACTER:// �L�����N�^�[�I��
		UpdateCharsel();
		break;
	case MODE_STAGE:	// �X�e�[�W
		break;
	case MODE_GAME:		// �Q�[��
		UpdateGame();
		break;
	case MODE_RESULT:	// ���U���g
//		UpdateResult();
		break;
	case MODE_STAFF:	// �X�^�b�t���[��
		UpdateStaff();
		break;
	}
	// �t�F�[�h�̍X�V����
	UpdateFade();

}

//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		if (g_bDebug[DRAW_DEBUG_POS] == true)
		{
			// FPS�\��
			DrawFPS();
			// ���W�\��
			DrawPOS();
		}
		if (g_bDebug[DRAW_DEBUG_WIREFRAME] == true)
		{
			// ���C���[�t���[��
			g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
		else if (g_bDebug[DRAW_DEBUG_WIREFRAME] == false)
		{
			// ���C���[�t���[��
			g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}

		// �e��I�u�W�F�N�g�̕`�揈��
		switch (g_mode)
		{
		case MODE_TITLE:	// �^�C�g��
			DrawTitle();
			//�t�����g�|���S��
			DrawFlontPolygon();
			break;
		case MODE_SELECT:	// �I�����
			//�t�����g�|���S��
			DrawFlontPolygon();


			DrawSelect();
			break;
		case MODE_CHARACTER:// �L�����N�^�[�I��
			DrawCharsel();
			break;
		case MODE_STAGE:	// �X�e�[�W�I��
			break;
		case MODE_GAME:		// �Q�[��
			DrawGame();
			break;
		case MODE_RESULT:	// ���U���g
//			DrawResult();
			break;
		case MODE_STAFF:	// �X�^�b�t���[��
			DrawStaff();
			break;
		}


		DrawFade();


		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//==============================================================================================================================
// �f�o�C�X�̎擾
//==============================================================================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//=============================================================================
// ���[�h�̐ݒ菈��
//=============================================================================
void SetMode(MODE mode)
{
	//�|���S��������
	ReleaseAllFlontPolygon();

	// �e��I������
	switch (g_mode)
	{
	case MODE_TITLE:	// �^�C�g��
		UninitTitle();
		StopSound();// �T�E���h�I��
		break;
	case MODE_SELECT:	// �I�����
		UninitSelect();
		StopSound();// �T�E���h�I��
		break;
	case MODE_CHARACTER:// �L�����N�^�[�I��
		UninitCharsel();
		StopSound(SOUND_LABEL_CHARASELECTBGM);// �T�E���h�I��
		break;
	case MODE_STAGE:	// �X�e�[�W�I��
		break;
	case MODE_GAME:		// �Q�[��
		StopSound();				// �T�E���h�I��
		UninitGame();
		break;
	case MODE_RESULT:	// ���U���g
//		UninitResult();
		StopSound();				// �T�E���h�I��
		break;
	case MODE_STAFF:	// �X�^�b�t���[��
		UninitStaff();
		StopSound();				// �T�E���h�I��
		break;
	}
	g_mode = mode;
	int SoundRand = 0;
	// �e�평��������
	switch (mode)
	{
	case MODE_TITLE:	// �^�C�g��
		InitTitle();
		PlaySound(SOUND_LABEL_TITLEBGM);
		break;
	case MODE_SELECT:	// �I�����
		InitSelect();
		PlaySound(SOUND_LABEL_SELECTBGM);
		break;
	case MODE_CHARACTER:// �L�����N�^�[�I��
		InitCharsel();
		PlaySound(SOUND_LABEL_CHARASELECTBGM);
		break;
	case MODE_STAGE:	// �X�e�[�W�I��
		break;
	case MODE_GAME:		// �Q�[��
		InitGame();
		srand((unsigned int)time(0));
		SoundRand =rand() % 3;
		if (SoundRand==0)
		{
			PlaySound(SOUND_LABEL_GAMEBGM000);
		}
		else if(SoundRand==1)
		{
			PlaySound(SOUND_LABEL_GAMEBGM001);
		}
		else
		{
			PlaySound(SOUND_LABEL_TITLEBGM);
		}
		break;
	case MODE_RESULT:	// ���U���g
//		InitResult();
		break;
	case MODE_STAFF:	// �X�^�b�t���[��
		InitStaff();
		PlaySound(SOUND_LABEL_TITLEBGM);
		break;
	}
}
//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
MODE GetMode(void)
{
	return g_mode;
}
//=============================================================================
// �}�E�X�̊l��
//=============================================================================
void GetPoint(HWND hWnd)
{
	//�}�E�X�N���b�N���W�Z�o����
	if (GetKeyState(VK_LBUTTON) & 0x80)//�}�E�X�@���{�^������
	{
		GetCursorPos(&g_Point);//�J�[�\���ʒu�̐�΍��W���擾
		ScreenToClient(hWnd, &g_Point);//�J�[�\����΍��W����A���̃E�B���h�E���̍��W�ɕ␳
		g_Point.x = LONG((FLOAT)g_Point.x * ((FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_WIDTH));//����ɃT�C�Y�ύX���l�����āA���݂̃T�C�Y�ŕ␳�i�g�T�C�Y������̂Ō����ł͂Ȃ��j
		g_Point.y = LONG((FLOAT)g_Point.y * ((FLOAT)SCREEN_HEIGHT / (FLOAT)SCREEN_HEIGHT));
	}

	//	D3DXMATRIX mWorldView;
	//	D3DXMATRIX m;
	//	D3DXVECTOR3 vRayDir;
	//	D3DXVECTOR3 vStartPoint;
	//	D3DXVECTOR3 v;

	//	//�}�E�X���W���X�N���[���̒��S�����_�ɂȂ�悤�ɕ␳�i���K���j
	//	v.x = (((2.0*g_Point.x) / (float)SCREEN_WIDTH) - 1) / mProj._11;
	//	v.y = -(((2.0*g_Point.y) / (float)SCREEN_HEIGHT) - 1) / mProj._22;
	//	v.z = 1.0;

	//	/*		mWorldView = XMesh[i].mWorld * mView;
	//	D3DXMatrixInverse(&m, NULL, &mWorldView);*/

	//	//��RayDir�̓��C���΂������x�N�g��
	//	vRayDir.x = v.x*m._11 + v.y*m._21 + v.z*m._31;
	//	vRayDir.y = v.x*m._12 + v.y*m._22 + v.z*m._32;
	//	vRayDir.z = v.x*m._13 + v.y*m._23 + v.z*m._33;

	//	//vStartPoint�̓X�N���[����̂QD���W�i�N���b�N�ʒu�j��3D��ԍ��W�ɕϊ���������
	//	vStartPoint.x = m._41;
	//	vStartPoint.y = m._42;
	//	vStartPoint.z = m._43;

	//}
}
POINT *GetPoint(void)
{
	return &g_Point;
}
//==============================================================================================================================
// FPS�\������
//==============================================================================================================================
void DrawFPS(void)
{
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	char aStr[256];

	// ���������
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	// �e�L�X�g�`��
	// hDC      : �f�o�C�X�R���e�L�X�g�̃n���h��
	// lpString : �`�悷�镶����ւ̃|�C���^
	// nCount   : ������̕�����
	// lpRect   : �����`�̈�
	// uFormat  : �e�L�X�g�̐��`���@���w��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 0xff));
}
//==============================================================================================================================
// ���_�f�[�^����
//==============================================================================================================================
void DrawPOS(void)
{
	Camera *pCamera;
	pCamera = GetCamera();
	Player *pPlayer = GetPlayer();
	RECT rect = { 0, 40, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[512];

	char *pName = "0,1,2,3�F����v���C���[�؂�ւ�\n4�F����v���C���[����\nWASD�F�ړ�\nSPACE�F�W�����v\nK�F�U��\nJ�F����\nG�F�K�[�h\nF1:�����\��/F2�F����\��/F3�F���C���[�t���[��/F5�F����ύX\nP�F�|�[�Y[V�FUI�폜]\n";
	// ���������
	wsprintf(&aStr[0], "�v���C���[�ʒu\n%d %d %d  \n\n�}�E�X���W\n%d %d\n\n�J�������W0\n%d %d %d\n\n�J�������W1V\n%d %d %d\n�J�������W1R\n%d %d %d\n\n�J������]\n%d %d %d\n\nF1:���W�\��\n\nF2:���C���\��\n\nF3:���C���[�t���[��\n\n�v���C���[�O�̃t���[��\n%d\n�v���C���[�P�̃t���[��\n%d\n�v���C���[�O�̃L�[\n%d\n%s"
		,(int)pPlayer->pos.x, (int)pPlayer->pos.y, (int)pPlayer->pos.z,g_Point.x,g_Point.y,
		(int)pCamera->posV.x, (int)pCamera->posV.y, (int)pCamera->posV.z, (int)pCamera[1].posV.x, (int)pCamera[1].posV.y, (int)pCamera[1].posV.z, (int)pCamera[1].posR.x, (int)pCamera[1].posR.y, (int)pCamera[1].posR.z,(int)(pCamera->rot.x * 100.0f), (int)(pCamera->rot.y * 100.0f), (int)(pCamera->rot.z * 100.0f)
	,pPlayer[0].nFrameAllCounter,pPlayer[1].nFrameAllCounter, pPlayer[0].nKeyCounter, pName);

	// �e�L�X�g�`��
	// hDC      : �f�o�C�X�R���e�L�X�g�̃n���h��
	// lpString : �`�悷�镶����ւ̃|�C���^
	// nCount   : ������̕�����
	// lpRect   : �����`�̈�
	// uFormat  : �e�L�X�g�̐��`���@���w��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 0xff));
}
//==============================================================================================================================
// �f�o�b�O���\���I���I�t
//==============================================================================================================================
bool *GetDrawDebug(void)
{
	return &g_bDebug[0];
}
Shader GetShader(void)
{
	return g_Shader;
}