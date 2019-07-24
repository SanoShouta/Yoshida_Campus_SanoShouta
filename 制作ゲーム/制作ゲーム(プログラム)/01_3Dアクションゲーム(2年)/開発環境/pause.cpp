//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �|�[�Y���� [pause.cpp]
// Author : suzuki
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "main.h"
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "gamepad.h"
#include "sound.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �}�N����`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define MAX_TOPPAUSE			(4)								// ���_��
#define PAUSE_TEXTURENAME		"data/TEXTURE/PauseBG000.png"	// �ǂݍ��ރe�N�X�`���̖��O
#define PAUSE_TEXTURENAME1		"data/TEXTURE/Continue000.png"	// �ǂݍ��ރe�N�X�`���̖��O
#define PAUSE_TEXTURENAME2		"data/TEXTURE/ReStart000.png"	// �ǂݍ��ރe�N�X�`���̖��O
#define PAUSE_TEXTURENAME3		"data/TEXTURE/Select000.png"	// �ǂݍ��ރe�N�X�`���̖��O
#define PAUSE_TEXTURENAME4		"data/TEXTURE/Select001.png"	// �ǂݍ��ރe�N�X�`���̖��O
#define PAUSE_TEXTURENAME5		"data/TEXTURE/TitleQuit000.png"	// �ǂݍ��ރe�N�X�`���̖��O
#define PAUSE_MENUBG_WIDTH		(350)							// �w�i�̕�
#define PAUSE_MENUBG_HEIGHT		(300)							// �w�i�̍���
#define PAUSE_CONTINUE_WIDTH	(200)							// ���j���[[������]�̕�
#define PAUSE_CONTINUE_HEIGHT	(60)							// ���j���[[������]�̍���
#define PAUSE_RETRY_WIDTH		(200)							// ���j���[[��蒼��]�̕�
#define PAUSE_RETRY_HEIGHT		(60)							// ���j���[[��蒼��]�̍���
#define PAUSE_CHARA_WIDTH		(200)							// ���j���[[�L�����I��]�̕�
#define PAUSE_CHARA_HEIGHT		(60)							// ���j���[[�L�����I��]�̍���
#define PAUSE_MODE_WIDTH		(200)							// ���j���[[���[�h�I��]�̕�
#define PAUSE_MODE_HEIGHT		(60)							// ���j���[[���[�h�I��]�̍���
#define PAUSE_QUIT_WIDTH		(200)							// ���j���[[�^�C�g���ɖ߂�]�̕�
#define PAUSE_QUIT_HEIGHT		(60)							// ���j���[[�^�C�g���ɖ߂�]�̍���
#define PAUSE_SELECTSPEED		(15)							// ���j���[�̑I���X�s�[�h

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �v���g�^�C�v
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetSelectCol(void);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �O���[�o���ϐ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
LPDIRECT3DTEXTURE9	g_pTexturePause[PAUSETEX_MAX + PAUSEMENU_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;
D3DXVECTOR3 g_aPos[PAUSETEX_MAX + PAUSEMENU_MAX];		// �ʒu
int g_nCntPress;										// �L�[�̉����Ă钷��
bool g_bDrawPause;
int g_nSelectMenu;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �|���S���̏�����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitPause(void)
{
	int nCntVertex;
	VERTEX_2D*pVtx;		// ���_���ւ̃|�C���^

	LPDIRECT3DDEVICE9 pDevice;
	g_aPos[PAUSETEX_BG] = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_aPos[PAUSETEX_MENU] = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_aPos[PAUSEMENU_CONTINUE + PAUSETEX_MAX] = D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f);
	g_aPos[PAUSEMENU_RETRY + PAUSETEX_MAX] = D3DXVECTOR3(SCREEN_WIDTH / 2, 250.0f, 0.0f);
	g_aPos[PAUSEMENU_CHARA + PAUSETEX_MAX] = D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f);
	g_aPos[PAUSEMENU_MODE + PAUSETEX_MAX] = D3DXVECTOR3(SCREEN_WIDTH / 2, 450.0f, 0.0f);
	g_aPos[PAUSEMENU_QUIT + PAUSETEX_MAX] = D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f);
	g_nCntPress = 0;
	g_bDrawPause = true;
	g_nSelectMenu = 0;

	// �f�o�C�X�̏���
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂ�
	D3DXCreateTextureFromFile(pDevice,
		"",
		&g_pTexturePause[PAUSETEX_BG]);
	D3DXCreateTextureFromFile(pDevice,
		PAUSE_TEXTURENAME,
		&g_pTexturePause[PAUSETEX_MENU]);
	D3DXCreateTextureFromFile(pDevice,
		PAUSE_TEXTURENAME1,
		&g_pTexturePause[PAUSEMENU_CONTINUE + PAUSETEX_MAX]);
	D3DXCreateTextureFromFile(pDevice,
		PAUSE_TEXTURENAME2,
		&g_pTexturePause[PAUSEMENU_RETRY + PAUSETEX_MAX]);
	D3DXCreateTextureFromFile(pDevice,
		PAUSE_TEXTURENAME3,
		&g_pTexturePause[PAUSEMENU_CHARA + PAUSETEX_MAX]);
	D3DXCreateTextureFromFile(pDevice,
		PAUSE_TEXTURENAME4,
		&g_pTexturePause[PAUSEMENU_MODE + PAUSETEX_MAX]);
	D3DXCreateTextureFromFile(pDevice,
		PAUSE_TEXTURENAME5,
		&g_pTexturePause[PAUSEMENU_QUIT + PAUSETEX_MAX]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (PAUSETEX_MAX + PAUSEMENU_MAX),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	// ���_l�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < PAUSETEX_MAX + PAUSEMENU_MAX; nCntTex++, pVtx += 4)
	{
		if (nCntTex == PAUSETEX_BG)
		{
			// ���W
			pVtx[0].pos = D3DXVECTOR3(g_aPos[PAUSETEX_BG].x, g_aPos[PAUSETEX_BG].y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPos[PAUSETEX_BG].x, g_aPos[PAUSETEX_BG].y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPos[PAUSETEX_BG].x, g_aPos[PAUSETEX_BG].y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPos[PAUSETEX_BG].x, g_aPos[PAUSETEX_BG].y, 0.0f);
		}
		else if (nCntTex == PAUSETEX_MENU)
		{
			// ���W
			pVtx[0].pos = D3DXVECTOR3(g_aPos[PAUSETEX_MENU].x - PAUSE_MENUBG_WIDTH, g_aPos[PAUSETEX_MENU].y - PAUSE_MENUBG_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPos[PAUSETEX_MENU].x + PAUSE_MENUBG_WIDTH, g_aPos[PAUSETEX_MENU].y - PAUSE_MENUBG_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPos[PAUSETEX_MENU].x - PAUSE_MENUBG_WIDTH, g_aPos[PAUSETEX_MENU].y + PAUSE_MENUBG_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPos[PAUSETEX_MENU].x + PAUSE_MENUBG_WIDTH, g_aPos[PAUSETEX_MENU].y + PAUSE_MENUBG_HEIGHT, 0.0f);
		}
		else if (nCntTex == PAUSEMENU_CONTINUE + PAUSETEX_MAX)
		{// �R���e�B�j���[
			// ���W
			pVtx[0].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_CONTINUE + PAUSETEX_MAX].x - PAUSE_CONTINUE_WIDTH, g_aPos[PAUSEMENU_CONTINUE + PAUSETEX_MAX].y - PAUSE_CONTINUE_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_CONTINUE + PAUSETEX_MAX].x + PAUSE_CONTINUE_WIDTH, g_aPos[PAUSEMENU_CONTINUE + PAUSETEX_MAX].y - PAUSE_CONTINUE_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_CONTINUE + PAUSETEX_MAX].x - PAUSE_CONTINUE_WIDTH, g_aPos[PAUSEMENU_CONTINUE + PAUSETEX_MAX].y + PAUSE_CONTINUE_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_CONTINUE + PAUSETEX_MAX].x + PAUSE_CONTINUE_WIDTH, g_aPos[PAUSEMENU_CONTINUE + PAUSETEX_MAX].y + PAUSE_CONTINUE_HEIGHT, 0.0f);
		}
		else if (nCntTex == PAUSEMENU_RETRY + PAUSETEX_MAX)
		{// ���g���C
			// ���W
			pVtx[0].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_RETRY + PAUSETEX_MAX].x - PAUSE_RETRY_WIDTH, g_aPos[PAUSEMENU_RETRY + PAUSETEX_MAX].y - PAUSE_RETRY_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_RETRY + PAUSETEX_MAX].x + PAUSE_RETRY_WIDTH, g_aPos[PAUSEMENU_RETRY + PAUSETEX_MAX].y - PAUSE_RETRY_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_RETRY + PAUSETEX_MAX].x - PAUSE_RETRY_WIDTH, g_aPos[PAUSEMENU_RETRY + PAUSETEX_MAX].y + PAUSE_RETRY_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_RETRY + PAUSETEX_MAX].x + PAUSE_RETRY_WIDTH, g_aPos[PAUSEMENU_RETRY + PAUSETEX_MAX].y + PAUSE_RETRY_HEIGHT, 0.0f);
		}
		else if (nCntTex == PAUSEMENU_CHARA + PAUSETEX_MAX)
		{// �L�����N�^�[�I��
			// ���W
			pVtx[0].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_CHARA + PAUSETEX_MAX].x - PAUSE_CHARA_WIDTH, g_aPos[PAUSEMENU_CHARA + PAUSETEX_MAX].y - PAUSE_CHARA_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_CHARA + PAUSETEX_MAX].x + PAUSE_CHARA_WIDTH, g_aPos[PAUSEMENU_CHARA + PAUSETEX_MAX].y - PAUSE_CHARA_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_CHARA + PAUSETEX_MAX].x - PAUSE_CHARA_WIDTH, g_aPos[PAUSEMENU_CHARA + PAUSETEX_MAX].y + PAUSE_CHARA_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_CHARA + PAUSETEX_MAX].x + PAUSE_CHARA_WIDTH, g_aPos[PAUSEMENU_CHARA + PAUSETEX_MAX].y + PAUSE_CHARA_HEIGHT, 0.0f);
		}
		else if (nCntTex == PAUSEMENU_MODE + PAUSETEX_MAX)
		{// �Q�[�����[�h�I��
			// ���W
			pVtx[0].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_MODE + PAUSETEX_MAX].x - PAUSE_MODE_WIDTH, g_aPos[PAUSEMENU_MODE + PAUSETEX_MAX].y - PAUSE_MODE_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_MODE + PAUSETEX_MAX].x + PAUSE_MODE_WIDTH, g_aPos[PAUSEMENU_MODE + PAUSETEX_MAX].y - PAUSE_MODE_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_MODE + PAUSETEX_MAX].x - PAUSE_MODE_WIDTH, g_aPos[PAUSEMENU_MODE + PAUSETEX_MAX].y + PAUSE_MODE_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_MODE + PAUSETEX_MAX].x + PAUSE_MODE_WIDTH, g_aPos[PAUSEMENU_MODE + PAUSETEX_MAX].y + PAUSE_MODE_HEIGHT, 0.0f);
		}
		else if (nCntTex == PAUSEMENU_QUIT + PAUSETEX_MAX)
		{// �߂�
			// ���W
			pVtx[0].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_QUIT + PAUSETEX_MAX].x - PAUSE_QUIT_WIDTH, g_aPos[PAUSEMENU_QUIT + PAUSETEX_MAX].y - PAUSE_QUIT_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_QUIT + PAUSETEX_MAX].x + PAUSE_QUIT_WIDTH, g_aPos[PAUSEMENU_QUIT + PAUSETEX_MAX].y - PAUSE_QUIT_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_QUIT + PAUSETEX_MAX].x - PAUSE_QUIT_WIDTH, g_aPos[PAUSEMENU_QUIT + PAUSETEX_MAX].y + PAUSE_QUIT_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPos[PAUSEMENU_QUIT + PAUSETEX_MAX].x + PAUSE_QUIT_WIDTH, g_aPos[PAUSEMENU_QUIT + PAUSETEX_MAX].y + PAUSE_QUIT_HEIGHT, 0.0f);
		}

		// rhw
		for (nCntVertex = 0; nCntVertex < MAX_TOPPAUSE; nCntVertex++)
		{
			pVtx[nCntVertex].rhw = 1.0f;
		}

		if (nCntTex == PAUSETEX_MENU)
		{
			// �F
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			// �F
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		}
		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitPause(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < PAUSETEX_MAX + PAUSEMENU_MAX; nCntTex++)
	{
		if (g_pTexturePause[nCntTex] != NULL)
		{
			g_pTexturePause[nCntTex]->Release();
			g_pTexturePause[nCntTex] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdatePause(bool *pPause)
{
	if (GetFade() == FADE_NONE)
	{

		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{// �X�y�[�X�L�[�������ꂽ�ꍇ
			g_bDrawPause = g_bDrawPause ? false : true;	// �|�[�Y�`��ON/OFF
		}
		else if (g_bDrawPause == false)
		{
			return;
		}
		else if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger(0, BUTTON_B))
		{
			FADE pFade;
			pFade = GetFade();
			if (g_nSelectMenu == PAUSEMENU_CONTINUE)
			{// ������
				*pPause = false;
			}
			else if (g_nSelectMenu == PAUSEMENU_RETRY)
			{// ���g���C
				if (pFade == FADE_NONE)
				{
					PlaySound(SOUND_DECISION_1);

					SetFade(MODE_GAME);
				}
			}
			else if (g_nSelectMenu == PAUSEMENU_CHARA)
			{// �L�����I��
				if (pFade == FADE_NONE)
				{
					PlaySound(SOUND_DECISION_1);
					SetFade(MODE_CHARACTER);
				}
			}
			else if (g_nSelectMenu == PAUSEMENU_MODE)
			{// ���[�h�I��
				if (pFade == FADE_NONE)
				{
					PlaySound(SOUND_DECISION_1);
					SetFade(MODE_SELECT);
				}
			}
			else if (g_nSelectMenu == PAUSEMENU_QUIT)
			{// �^�C�g���ɖ߂�
				if (pFade == FADE_NONE)
				{
					PlaySound(SOUND_DECISION_1);
					SetFade(MODE_TITLE);
				}
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{// ��Ɉړ�
			if (GetKeyboardTrigger(DIK_W) == true)
			{// �g���K�[
				g_nSelectMenu = (g_nSelectMenu + (PAUSEMENU_MAX - 1)) % PAUSEMENU_MAX;
				SetSelectCol();
				PlaySound(SOUND_SELECTMOVE);
				g_nCntPress = 0;
			}
			g_nCntPress--;			// �J�E���g�����Z����
			if (g_nCntPress <= -PAUSE_SELECTSPEED)
			{// �����������Ƃ�
				g_nSelectMenu = (g_nSelectMenu + (PAUSEMENU_MAX - 1)) % PAUSEMENU_MAX;
				PlaySound(SOUND_SELECTMOVE);
				SetSelectCol();
				g_nCntPress = 0;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// ���Ɉړ�
			if (GetKeyboardTrigger(DIK_S) == true)
			{// �g���K�[
				g_nSelectMenu = (g_nSelectMenu + 1) % PAUSEMENU_MAX;
				PlaySound(SOUND_SELECTMOVE);
				SetSelectCol();
				g_nCntPress = 0;
			}
			g_nCntPress++;			// �J�E���g�����Z����
			if (g_nCntPress >= PAUSE_SELECTSPEED)
			{// �����������Ƃ�
				g_nSelectMenu = (g_nSelectMenu + 1) % PAUSEMENU_MAX;
				PlaySound(SOUND_SELECTMOVE);
				SetSelectCol();
				g_nCntPress = 0;
			}
		}
		for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
		{
			if (GetGamePadTrigger(nCnt, BUTTON_B))
			{
				FADE pFade;
				pFade = GetFade();
				if (g_nSelectMenu == PAUSEMENU_CONTINUE)
				{// ������
					*pPause = false;
				}
				else if (g_nSelectMenu == PAUSEMENU_RETRY)
				{// ���g���C
					if (pFade == FADE_NONE)
					{
						SetFade(MODE_GAME);
					}
				}
				else if (g_nSelectMenu == PAUSEMENU_CHARA)
				{// �L�����I��
					if (pFade == FADE_NONE)
					{
						SetFade(MODE_CHARACTER);
					}
				}
				else if (g_nSelectMenu == PAUSEMENU_MODE)
				{// ���[�h�I��
					if (pFade == FADE_NONE)
					{
						SetFade(MODE_SELECT);
					}
				}
				else if (g_nSelectMenu == PAUSEMENU_QUIT)
				{// �^�C�g���ɖ߂�
					if (pFade == FADE_NONE)
					{
						SetFade(MODE_TITLE);
					}
				}
			}
			else if (GetGamePadStickPress(nCnt, ANALOG_STICK_UP) == true)
			{// ��Ɉړ�
				if (GetGamePadStickTrigger(nCnt, ANALOG_STICK_UP) == true)
				{// �g���K�[
					g_nSelectMenu = (g_nSelectMenu + (PAUSEMENU_MAX - 1)) % PAUSEMENU_MAX;
					SetSelectCol();
					PlaySound(SOUND_SELECTMOVE);
					g_nCntPress = 0;
				}
				g_nCntPress--;			// �J�E���g�����Z����
				if (g_nCntPress <= -PAUSE_SELECTSPEED)
				{// �����������Ƃ�
					g_nSelectMenu = (g_nSelectMenu + (PAUSEMENU_MAX - 1)) % PAUSEMENU_MAX;
					PlaySound(SOUND_SELECTMOVE);
					SetSelectCol();
					g_nCntPress = 0;
				}
			}
			else if (GetGamePadStickPress(nCnt, ANALOG_STICK_DOWN) == true)
			{// ���Ɉړ�
				if (GetGamePadStickTrigger(nCnt, ANALOG_STICK_DOWN) == true)
				{// �g���K�[
					g_nSelectMenu = (g_nSelectMenu + 1) % PAUSEMENU_MAX;
					PlaySound(SOUND_SELECTMOVE);
					SetSelectCol();
					g_nCntPress = 0;
				}
				g_nCntPress++;			// �J�E���g�����Z����
				if (g_nCntPress >= PAUSE_SELECTSPEED)
				{// �����������Ƃ�
					g_nSelectMenu = (g_nSelectMenu + 1) % PAUSEMENU_MAX;
					PlaySound(SOUND_SELECTMOVE);
					SetSelectCol();
					g_nCntPress = 0;
				}
			}

		}
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X����������
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_bDrawPause == true)
	{
		for (int nCntTex = 0; nCntTex < PAUSETEX_MAX + PAUSEMENU_MAX; nCntTex++)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePause[nCntTex]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntTex,
				2);
		}
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���_�J���[�̐ݒ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetSelectCol(void)
{
	VERTEX_2D*pVtx;		// ���_���ւ̃|�C���^

	// ���_l�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * PAUSETEX_MAX;
	for (int nCntTex = 0; nCntTex < PAUSEMENU_MAX; nCntTex++, pVtx += 4)
	{
		// ���_�J���[�̐ݒ�
		if (nCntTex == g_nSelectMenu)
		{// �I�����Ă�
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �|�[�Y��ʂ̐ݒ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetPause(bool bDraw, int nSelect)
{
	g_bDrawPause = bDraw;
	g_nSelectMenu = nSelect;
	SetSelectCol();
}
