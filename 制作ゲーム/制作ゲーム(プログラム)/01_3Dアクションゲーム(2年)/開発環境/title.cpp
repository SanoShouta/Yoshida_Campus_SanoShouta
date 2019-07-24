//=============================================================================
//
// �^�C�g����� [title.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "title.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "flontpolygon.h"
#include "camera.h"
#include "light.h"
#include "line.h"
#include "meshWall.h"
#include "meshField.h"
#include "model.h"
#include "game.h"
#include "gamepad.h"
#include "effect.h"
#include "effectUP.h"
#include "shadow.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_NAME	("data\\TEXTURE\\title_logo.png")	//�ǂݍ��ރt�@�C����
#define TEXTURE_NAME2	("data\\TEXTURE\\StartBottun.jpg")	//�ǂݍ��ރt�@�C����
#define MAX_POLYGON		(2)
#define MAX_TEXTURE		(2)

#define MAXSIZE_X		(450.0f)
#define MAXSIZE_Y		(281.25f)
#define MAXSIZE2_X		(100.0f)
#define MAXSIZE2_Y		(50.25f)

#define MINSIZE_X		(400.0f)
#define MINSIZE_Y		(250.0f)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTitle[MAX_TEXTURE] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//���_�o�b�t�@�ւ̃|�C���^
int						g_TitleTime;						//���ԃJ�E���^�[
int						g_TitleButtonTime;						//���ԃJ�E���^�[
Title					g_Title[MAX_POLYGON];				//�^�C�g���̏��
LOGOSIZE				g_Logo;								//���S�̏��
BOTTNSTATE				g_Bottun;							//�{�^���̏��

//=============================================================================
// �^�C�g������������
//=============================================================================
void InitTitle(void)
{
	// �J�����̏���������
	InitCamera();
	// ���̏���������
	InitLine();
	// �e�̏���������
	InitShadow();
	// ���C�g�̏���������
	InitLight();
	// ���b�V�����̏���������
	InitMeshField();
	// ���b�V���ǂ̏���������
	InitMeshWall();
	// ���f���̏���������
	InitModel();
	// �G�t�F�N�g�̏���������
	InitEffect();
	// �G�t�F�N�g�|���S���̏���������
	InitEffectUP();
	// �t�@�C���ǂݍ���
	SetStagePos("data/stage1.txt");

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	g_Title[0].Pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f);
	g_Title[0].PosHold = D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f);
	g_Title[0].Size = D3DXVECTOR3(MAXSIZE_X, MAXSIZE_Y, 0.0f);
	g_Title[0].fCola = 1.0f;
	g_Title[0].Type = TITLETYPE_LOGO;

	g_Title[1].Pos = D3DXVECTOR3(600, 650, 0.0f);
	g_Title[1].PosHold = D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f);
	g_Title[1].Size = D3DXVECTOR3(MAXSIZE2_X, MAXSIZE2_Y, 0.0f);
	g_Title[1].fCola = 1.0f;
	g_Title[1].Type = TITLETYPE_BOTTUN;

	g_Logo = LOGOSIZE_SMALL;
	g_Bottun = BOTTNSTATE_TRUE;
	g_TitleButtonTime = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&g_pTextureTitle[0]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME2,
		&g_pTextureTitle[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

// �^�C�g�����S -----------------------------------------------------------------------------------------------------
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Title[0].Pos.x - g_Title[0].Size.x, g_Title[0].Pos.y - g_Title[0].Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Title[0].Pos.x + g_Title[0].Size.x, g_Title[0].Pos.y - g_Title[0].Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Title[0].Pos.x - g_Title[0].Size.x, g_Title[0].Pos.y + g_Title[0].Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Title[0].Pos.x + g_Title[0].Size.x, g_Title[0].Pos.y + g_Title[0].Size.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

// �{�^�� -----------------------------------------------------------------------------------------------------
//���_���W�̐ݒ�
	pVtx[4].pos = D3DXVECTOR3(g_Title[1].Pos.x - g_Title[1].Size.x, g_Title[1].Pos.y - g_Title[1].Size.y, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_Title[1].Pos.x + g_Title[1].Size.x, g_Title[1].Pos.y - g_Title[1].Size.y, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_Title[1].Pos.x - g_Title[1].Size.x, g_Title[1].Pos.y + g_Title[1].Size.y, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(g_Title[1].Pos.x + g_Title[1].Size.x, g_Title[1].Pos.y + g_Title[1].Size.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	//�^�C�g�����S
	//SetFlontPolygon(FLONTTYPE_NOMAL, D3DXVECTOR3(SCREEN_WIDTH/2, 300.0f, 0.0f), 800.0f, 500.0f, FLONTTYPE_NOMAL);
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitTitle(void)
{
	// �J�����̏I������
	UninitCamera();
	// ���C���̏I������
	UninitLine();
	// �e�̏I������
	UninitShadow();
	// ���C�g�̏I������
	UninitLight();
	// �G�t�F�N�g�̏I������
	UninitEffect();
	// �G�t�F�N�g�|���S���̏I������
	UninitEffectUP();
	//�t�����g�|���S�������ׂĔ�\���ɂ���
	//ReleaseAllFlontPolygon();

	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (g_pTextureTitle[nCntTex] != NULL)
		{
			g_pTextureTitle[nCntTex]->Release();
			g_pTextureTitle[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateTitle(void)
{
	//�t�F�[�h�����擾����
	FADE fade = GetFade();

	// �J�����̍X�V����
	UpdateCamera();
	// ���̍X�V����
	UpdateLine();
	// �e�̍X�V����
	UpdateShadow();
	// ���C�g�̍X�V����
	UpdateLight();
	// ���b�V�����̍X�V����
	UpdateMeshField();
	// ���b�V���ǂ̍X�V����
	UpdateMeshWall();
	// ���f���̍X�V����
	UpdateModel();
	// �G�t�F�N�g�̍X�V����
	UpdateEffect();
	// �G�t�F�N�g�|���S���̍X�V����
	UpdateEffectUP();
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		SetEffectUP(0, D3DXVECTOR3(sinf(SetRandomEffect())*600.0f, 600 + float(rand() % 300), cosf(SetRandomEffect())*300.0f + 200.0f),
			D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(SetRandomEffect(), SetRandomEffect(), SetRandomEffect()),
			D3DXCOLOR(float(rand() % 100) / 100.0f, float(rand() % 100) / 100.0f, float(rand() % 100) / 100.0f, 1.0f),
			EFFECTUPTYPE_PAPER, 10);
	}

	//�t�����g�|���S���̏����擾
	FlontPolygon * pFlontPolygon;
	pFlontPolygon = GetFlontPolygon();

		//����L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
		{
			PlaySound(SOUND_DECISION_1);

			//�{�^����ԐF��
			g_Bottun = BOTTNSTATE_NOMAL;

			//�t�F�[�h���[�h�ݒ�
			SetFade(MODE_SELECT);
		}

	}
	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		if (GetGamePadTrigger(nCnt, BUTTON_START)|| GetGamePadTrigger(nCnt, BUTTON_A)|| GetGamePadTrigger(nCnt, BUTTON_B))
		{
			if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
			{
				//�{�^����ԐF��
				g_Bottun = BOTTNSTATE_NOMAL;

				//�t�F�[�h���[�h�ݒ�
				SetFade(MODE_SELECT);
			}
		}
	}

	//���S�̃T�C�Y�X�V
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_POLYGON; nCntTitle++)
	{
		switch (g_Title[nCntTitle].Type)
		{
		case TITLETYPE_LOGO:
			switch (g_Logo)
			{

			case LOGOSIZE_NONE:
				g_TitleTime++;

				if ((g_TitleTime % 50) == 0)
				{
					g_Logo = LOGOSIZE_BIG;
					g_TitleTime = 0;
				}
				break;

			case LOGOSIZE_BIG:
				//�T�C�Y�̉��Z
				g_Title[nCntTitle].Size.x += 20;
				g_Title[nCntTitle].Size.y += 12.5f;

				if (g_Title[nCntTitle].Size.x > MAXSIZE_X && g_Title[nCntTitle].Size.y > MAXSIZE_Y)
				{
					g_Title[nCntTitle].Size.x = MAXSIZE_X;
					g_Title[nCntTitle].Size.y = MAXSIZE_Y;
					g_Logo = LOGOSIZE_SMALL;
				}

				break;

			case LOGOSIZE_SMALL:
				//�T�C�Y�̌��Z
				g_Title[nCntTitle].Size.x -= 5;
				g_Title[nCntTitle].Size.y -= 3.125f;

				if (g_Title[nCntTitle].Size.x < MINSIZE_X && g_Title[nCntTitle].Size.y < MINSIZE_Y)
				{
					g_Title[nCntTitle].Size.x = MINSIZE_X;
					g_Title[nCntTitle].Size.y = MINSIZE_Y;
					g_Logo = LOGOSIZE_NONE;
				}
				break;
			}
			break;

		case TITLETYPE_BOTTUN:

			switch (g_Bottun)
			{
			case BOTTNSTATE_TRUE:

				//�����x�̉��Z
				g_Title[nCntTitle].fCola += 0.02f;

				if (g_Title[nCntTitle].fCola > 1.0f)
				{
					g_Title[nCntTitle].fCola = 1.0f;

					//���Ԃ̉��Z
					g_TitleButtonTime++;

					if (g_TitleButtonTime % 30 == 0)
					{
						g_Bottun = BOTTNSTATE_FALSE;
						g_TitleButtonTime = 0;
					}
				}

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				break;

			case BOTTNSTATE_FALSE:
				//�����x�̌��Z
				g_Title[nCntTitle].fCola -= 0.02f;

				if (g_Title[nCntTitle].fCola < 0.0f)
				{
					g_Title[nCntTitle].fCola = 0.0f;
					g_Bottun = BOTTNSTATE_TRUE;
				}

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Title[nCntTitle].fCola);
				break;

			case BOTTNSTATE_NOMAL:
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				break;

			}
			break;
		}

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Title[nCntTitle].Pos.x - g_Title[nCntTitle].Size.x, g_Title[nCntTitle].Pos.y - g_Title[nCntTitle].Size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Title[nCntTitle].Pos.x + g_Title[nCntTitle].Size.x, g_Title[nCntTitle].Pos.y - g_Title[nCntTitle].Size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Title[nCntTitle].Pos.x - g_Title[nCntTitle].Size.x, g_Title[nCntTitle].Pos.y + g_Title[nCntTitle].Size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Title[nCntTitle].Pos.x + g_Title[nCntTitle].Size.x, g_Title[nCntTitle].Pos.y + g_Title[nCntTitle].Size.y, 0.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawTitle(void)
{
	// �J�����̐ݒ�
	SetCamera(0);
	// ���b�V�����̕`�揈��
	DrawMeshField();
	// ���b�V���ǂ̕`�揈��
	DrawMeshWall();
	// ���f���̕`�揈��
	DrawModel();
	// �e�̕`�揈��
	DrawShadow();
	// �G�t�F�N�g�̕`�揈��
	DrawEffect();
	// �G�t�F�N�g�|���S���̕`�揈��
	DrawEffectUP();

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPolygon = 0; nCntPolygon < MAX_POLYGON; nCntPolygon++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCntPolygon]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
			nCntPolygon * 4,			//�J�n���钸�_�̃C���f�b�N�X
			2);					//�v���~�e�B�u�̐�
	}
}