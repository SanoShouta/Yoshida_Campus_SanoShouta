//=============================================================================
//
// �X�^�b�t���[����� [staff.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "staff.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "gamepad.h"
#include "flontpolygon.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define TEXTURENAME	("data\\TEXTURE\\StaffRoll.png")	//�ǂݍ��ރe�N�X�`���t�@�C����
#define POS			(D3DXVECTOR3(640, 360, 0))		//���S���W
#define STAFF_TIME	(60 * 140)						//�X�^�b�t��ʂ̐؂�ւ�����
#define TEX_MOVE	(0.0001f)						//UV�l�̕ω���

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureStaff = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStaff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Staff					g_Staff;					//�\���̂̏��
int						g_nStaffTime;				//�X�^�b�t���[���̎��ԃJ�E���^�[
float					g_fCntUV;				//UV�l�̌v�Z

//=============================================================================
// �X�^�b�t���[������������
//=============================================================================
void InitStaff(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	g_Staff.Pos = POS;
	g_nStaffTime = 0;
	g_fCntUV = 0.0f;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURENAME,
		&g_pTextureStaff);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStaff,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffStaff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.01f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.01f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffStaff->Unlock();
}

//=============================================================================
// �X�^�b�t���[���I������
//=============================================================================
void UninitStaff(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureStaff != NULL)
	{
		g_pTextureStaff->Release();
		g_pTextureStaff = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffStaff != NULL)
	{
		g_pVtxBuffStaff->Release();
		g_pVtxBuffStaff = NULL;
	}

	//�t�����g�|���S���̊J��
	ReleaseAllFlontPolygon();
}

//=============================================================================
// �X�^�b�t���[���X�V����
//=============================================================================
void UpdateStaff(void)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//�t�F�[�h�����擾����
	FADE fade = GetFade();

	//�^�C�}�[�̉��Z
	g_nStaffTime++;

	//�X�L�b�v�L�[�������Ă�����
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_fCntUV += 0.0005f;
	}
	else
	{
		g_fCntUV += TEX_MOVE;
	}

	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		if (GetPovTpress(nCnt, POV_DOWN) == true)
		{
			g_fCntUV += 0.0005f;
			break;
		}
		if (GetGamePadStickPress(nCnt, ANALOG_STICK_DOWN) == true)
		{
			g_fCntUV += 0.0005f;
			break;
		}
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffStaff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + g_fCntUV);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + g_fCntUV);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.1f + g_fCntUV);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.1f + g_fCntUV);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffStaff->Unlock();

	//����L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
		{

			//�t�F�[�h���[�h�ݒ�
			SetFade(MODE_SELECT);
		}

	}
	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		if (GetGamePadTrigger(nCnt, BUTTON_START) || GetGamePadTrigger(nCnt, BUTTON_A) || GetGamePadTrigger(nCnt, BUTTON_B))
		{
			if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
			{
				//�t�F�[�h���[�h�ݒ�
				SetFade(MODE_SELECT);
			}
		}
	}

	//�\�����Ԃ�������
	if (g_nStaffTime > STAFF_TIME)
	{
		if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
		{
			//�t�F�[�h���[�h�ݒ�
			SetFade(MODE_SELECT);
		}
	}

	//����UV�l��������
	if (g_fCntUV > 0.84f)
	{
		if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
		{
			//�t�F�[�h���[�h�ݒ�
			SetFade(MODE_SELECT);
		}
	}
}

//=============================================================================
// �X�^�b�t���[���`�揈��
//=============================================================================
void DrawStaff(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStaff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureStaff);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
								0,						//�J�n���钸�_�̃C���f�b�N�X
								2);						//�v���~�e�B�u�̐�
}