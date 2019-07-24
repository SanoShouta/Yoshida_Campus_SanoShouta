//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �J�[�\������ [ cursor.cpp ]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "cursor.h"
#include "input.h"
#include "marker.h"
#include "charsel.h"
#include "gamepad.h"
#include "fade.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �}�N����`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define MAX_CURSORTOP			(4)								// ���_��
#define CURSOR_TEXTURENAME0		"data/TEXTURE/Cursor000.png"	// �ǂݍ��ރe�N�X�`���̖��O
#define CURSOR_TEXTURENAME1		"data/TEXTURE/Cursor001.png"	// �ǂݍ��ރe�N�X�`���̖��O
#define CURSOR_TEXTURENAME2		"data/TEXTURE/Cursor002.png"	// �ǂݍ��ރe�N�X�`���̖��O
#define CURSOR_TEXTURENAME3		"data/TEXTURE/Cursor003.png"	// �ǂݍ��ރe�N�X�`���̖��O
#define GRAVITY_PLUS			(2.5f)							// �d��
#define MOVE_SPEED				(3.0f)							// �������x

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �O���[�o���ϐ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
VERTEX_2D				g_aVertexCursor[MAX_CURSORTOP];
LPDIRECT3DTEXTURE9		g_pTextureCursor[CURSOR_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCursor = NULL;
CURSOR					g_aCursor[CURSOR_MAX];

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �|���S���̏�����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitCursor(void)
{
	VERTEX_2D*pVtx;		// ���_���ւ̃|�C���^

	LPDIRECT3DDEVICE9 pDevice;

	g_aCursor[0].pos = D3DXVECTOR3(180.0f, 180.0f, 0.0f);
	g_aCursor[1].pos = D3DXVECTOR3(1100.0f, 180.0f, 0.0f);
	g_aCursor[2].pos = D3DXVECTOR3(180.0f, 540.0f, 0.0f);
	g_aCursor[3].pos = D3DXVECTOR3(1100.0f, 540.0f, 0.0f);

	for (int nCntCursor = 0; nCntCursor < CURSOR_MAX; nCntCursor++)
	{
		g_aCursor[nCntCursor].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCursor[nCntCursor].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCursor[nCntCursor].fWidth = CURSOR_WIDTH;
		g_aCursor[nCntCursor].fHeight = CURSOR_HEIGHT;
		g_aCursor[nCntCursor].nPatternAnim = 1;
		g_aCursor[nCntCursor].nNowChar = CHARSELTYPE_NONE;
		g_aCursor[nCntCursor].nCounter = 0;
		g_aCursor[nCntCursor].state = CURSORSTATE_CATCH;
		g_aCursor[nCntCursor].stateOld = CURSORSTATE_CATCH;
		g_aCursor[nCntCursor].colorType = PLAYERCOLOR_STANDARD;
		g_aCursor[nCntCursor].bColor = true;
	}
	// �f�o�C�X�̏���
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		CURSOR_TEXTURENAME0,
		&g_pTextureCursor[0]);

	D3DXCreateTextureFromFile(pDevice,
		CURSOR_TEXTURENAME1,
		&g_pTextureCursor[1]);

	D3DXCreateTextureFromFile(pDevice,
		CURSOR_TEXTURENAME2,
		&g_pTextureCursor[2]);

	D3DXCreateTextureFromFile(pDevice,
		CURSOR_TEXTURENAME3,
		&g_pTextureCursor[3]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_CURSORTOP * CURSOR_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCursor,
		NULL);

	// ���_l�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCursor->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCursor = 0; nCntCursor < CURSOR_MAX; nCntCursor++)
	{
		// ���W
		pVtx[0].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x - g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y - g_aCursor[nCntCursor].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x + g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y - g_aCursor[nCntCursor].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x - g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y + g_aCursor[nCntCursor].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x + g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y + g_aCursor[nCntCursor].fHeight, 0.0f);

		// rhw
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// �F
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffCursor->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitCursor(void)
{
	for (int nCntTex = 0; nCntTex < CURSOR_MAX; nCntTex++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureCursor[nCntTex] != NULL)
		{
			g_pTextureCursor[nCntTex]->Release();
			g_pTextureCursor[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffCursor != NULL)
	{
		g_pVtxBuffCursor->Release();
		g_pVtxBuffCursor = NULL;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateCursor(void)
{
	MARKER *pMarker = GetMarker();
	GamePad *pGamePad = GetgamePadStick();
	if (GetFade() == FADE_NONE)
	{
		for (int nCntCursor = 0; nCntCursor < CURSOR_MAX; nCntCursor++)
		{
			if (g_aCursor[nCntCursor].stateOld != g_aCursor[nCntCursor].state)
			{
				g_aCursor[nCntCursor].nCounter = 10;
			}

			g_aCursor[nCntCursor].posOld = g_aCursor[nCntCursor].pos;			// �O��̍��W������
			g_aCursor[nCntCursor].stateOld = g_aCursor[nCntCursor].state;

			switch (g_aCursor[nCntCursor].state)
			{
			case CURSORSTATE_CATCH:
				pMarker[nCntCursor].move = g_aCursor[nCntCursor].move;
				g_aCursor[nCntCursor].nCounter--;
				if (g_aCursor[nCntCursor].nCounter > 0)
				{
					pMarker[nCntCursor].pos.x += ((g_aCursor[nCntCursor].pos.x - 30) - (pMarker[nCntCursor].pos.x)) * 0.3f;
					pMarker[nCntCursor].pos.y += (g_aCursor[nCntCursor].pos.y - pMarker[nCntCursor].pos.y)*0.3f;
				}
				else
				{
					pMarker[nCntCursor].pos.x = g_aCursor[nCntCursor].pos.x - 30;
					pMarker[nCntCursor].pos.y = g_aCursor[nCntCursor].pos.y;
				}
				break;
			case CURSORSTATE_RELEASE_START:
				g_aCursor[nCntCursor].state = CURSORSTATE_RELEASE;
				break;
			case CURSORSTATE_RELEASE:
				break;
			}
			// �J�[�\�����쏈��
			SetOperation(nCntCursor);

			g_aCursor[nCntCursor].pos.x += g_aCursor[nCntCursor].move.x;	// ���ړ�
			g_aCursor[nCntCursor].pos.y += g_aCursor[nCntCursor].move.y;	// �c�ړ�

			// ����
			g_aCursor[nCntCursor].move.x += (0.0f - g_aCursor[nCntCursor].move.x) * 0.3f;
			g_aCursor[nCntCursor].move.y += (0.0f - g_aCursor[nCntCursor].move.y) * 0.2f;

			// �g�O�ɏo��Ȃ�����
			if (g_aCursor[nCntCursor].pos.x < g_aCursor[nCntCursor].fWidth)
			{	// ��
				g_aCursor[nCntCursor].pos.x = g_aCursor[nCntCursor].fWidth;
			}
			if (g_aCursor[nCntCursor].pos.x > SCREEN_WIDTH - g_aCursor[nCntCursor].fWidth)
			{	// �E
				g_aCursor[nCntCursor].pos.x = SCREEN_WIDTH - g_aCursor[nCntCursor].fWidth;
			}
			if (g_aCursor[nCntCursor].pos.y < g_aCursor[nCntCursor].fHeight)
			{	// ��
				g_aCursor[nCntCursor].pos.y = g_aCursor[nCntCursor].fHeight;
			}
			if (g_aCursor[nCntCursor].pos.y > SCREEN_HEIGHT - g_aCursor[nCntCursor].fHeight)
			{	// ��
				g_aCursor[nCntCursor].pos.y = SCREEN_HEIGHT - g_aCursor[nCntCursor].fHeight;
			}
		}

		for (int nIdy = 0; nIdy < MAX_GAMEPAD; nIdy++)
		{// �Q�[���p�b�h
			if (pGamePad[nIdy].pDevGamePad != NULL)
			{
				if (GetGamePadTrigger(nIdy, BUTTON_B))
				{
					if (g_aCursor[nIdy].state == CURSORSTATE_CATCH)
					{// �͂�
						g_aCursor[nIdy].state = CURSORSTATE_RELEASE_START;		// ��Ԃ�؂�ւ���
						g_aCursor[nIdy].nPatternAnim = 0;					// �e�N�X�`���؂�ւ�
					}
					else if (g_aCursor[nIdy].state == CURSORSTATE_RELEASE)
					{// ����
						g_aCursor[nIdy].state = CURSORSTATE_CATCH;			// ��Ԃ�؂�ւ���
						g_aCursor[nIdy].nPatternAnim = 1;					// �e�N�X�`���؂�ւ�
					}
				}
				if (GetGamePadTrigger(nIdy, BUTTON_A))
				{
					if (g_aCursor[nIdy].state == CURSORSTATE_RELEASE)
					{// ����
						g_aCursor[nIdy].state = CURSORSTATE_CATCH;			// ��Ԃ�؂�ւ���
						g_aCursor[nIdy].nPatternAnim = 1;					// �e�N�X�`���؂�ւ�
					}
				}
				if (g_aCursor[nIdy].state == CURSORSTATE_RELEASE)
				{// �����Ă��鎞(�}�[�J�[��u���Ă�Ƃ�)
					Player *pPlayer = GetPlayer();

					if (GetGamePadTrigger(nIdy, BUTTON_Y))
					{// �F�̕ύX
						g_aCursor[nIdy].colorType = pPlayer[nIdy].colType;	// �v���C���[�̐F������
						SetColSel(false, nIdy, g_aCursor[nIdy].colorType);	// ���̐F�� false �ɂ���
						g_aCursor[nIdy].colorType++;						// �F�̎�ނ�ς���
						if (g_aCursor[nIdy].colorType >= PLAYERCOLOR_MAX)
						{// �F�̎�ނ𒴂����Ƃ�
							g_aCursor[nIdy].colorType = 0;
						}

						if (false == GetColSel(nIdy, g_aCursor[nIdy].colorType))
						{// �F���g���Ă��Ȃ�������
							SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// �V�����F�� true �ɂ���
						}
						else if (true == GetColSel(nIdy, g_aCursor[nIdy].colorType))
						{// �F���g���Ă�����
							do
							{
								g_aCursor[nIdy].colorType++;						// �F��ς���
								if (g_aCursor[nIdy].colorType >= PLAYERCOLOR_MAX)
								{// �F�̎�ނ𒴂����Ƃ�
									g_aCursor[nIdy].colorType = 0;
								}

							} while (false != GetColSel(nIdy, g_aCursor[nIdy].colorType));
							SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// �V�����F�� true �ɂ���
						}

						if (g_aCursor[nIdy].colorType == PLAYERCOLOR_STANDARD)
						{// �����F�̂Ƃ�
							pPlayer[nIdy].colType = PLAYERCOLOR_STANDARD;
						}
						else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF1)
						{// �Ⴄ�F�̂Ƃ�
							pPlayer[nIdy].colType = PLAYERCOLOR_DIF1;
						}
						else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF2)
						{// �Ⴄ�F�̂Ƃ�
							pPlayer[nIdy].colType = PLAYERCOLOR_DIF2;
						}
						else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF3)
						{// �Ⴄ�F�̂Ƃ�
							pPlayer[nIdy].colType = PLAYERCOLOR_DIF3;
						}
					}
					else if (GetGamePadTrigger(nIdy, BUTTON_X))
					{// �J���[�ύX
						g_aCursor[nIdy].colorType = pPlayer[nIdy].colType;	// �v���C���[�̐F������
						SetColSel(false, nIdy, g_aCursor[nIdy].colorType);	// ���̐F�� false �ɂ���
						g_aCursor[nIdy].colorType--;						// �F�̎�ނ�ς���
						if (g_aCursor[nIdy].colorType < 0)
						{// �F�̎�ނ𒴂����Ƃ�
							g_aCursor[nIdy].colorType = PLAYERCOLOR_DIF3;
						}

						if (false == GetColSel(nIdy, g_aCursor[nIdy].colorType))
						{// �F���g���Ă��Ȃ�������
							SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// �V�����F�� true �ɂ���
						}
						else if (true == GetColSel(nIdy, g_aCursor[nIdy].colorType))
						{// �F���g���Ă�����
							do
							{
								g_aCursor[nIdy].colorType++;						// �F��ς���
								if (g_aCursor[nIdy].colorType >= PLAYERCOLOR_MAX)
								{// �F�̎�ނ𒴂����Ƃ�
									g_aCursor[nIdy].colorType = 0;
								}

							} while (false != GetColSel(nIdy, g_aCursor[nIdy].colorType));
							SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// �V�����F�� true �ɂ���
						}
						if (g_aCursor[nIdy].colorType == PLAYERCOLOR_STANDARD)
						{// �����F�̂Ƃ�
							pPlayer[nIdy].colType = PLAYERCOLOR_STANDARD;
						}
						else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF1)
						{// �Ⴄ�F�̂Ƃ�
							pPlayer[nIdy].colType = PLAYERCOLOR_DIF1;
						}
						else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF2)
						{// �Ⴄ�F�̂Ƃ�
							pPlayer[nIdy].colType = PLAYERCOLOR_DIF2;
						}
						else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF3)
						{// �Ⴄ�F�̂Ƃ�
							pPlayer[nIdy].colType = PLAYERCOLOR_DIF3;
						}
					}
				}
			}
		}
	}
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	// ���_l�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCursor->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCursor = 0; nCntCursor < CURSOR_MAX; nCntCursor++)
	{
		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x - g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y - g_aCursor[nCntCursor].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x + g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y - g_aCursor[nCntCursor].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x - g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y + g_aCursor[nCntCursor].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCursor[nCntCursor].pos.x + g_aCursor[nCntCursor].fWidth, g_aCursor[nCntCursor].pos.y + g_aCursor[nCntCursor].fHeight, 0.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.5f * g_aCursor[nCntCursor].nPatternAnim, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f * (g_aCursor[nCntCursor].nPatternAnim + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.5f * g_aCursor[nCntCursor].nPatternAnim, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f * (g_aCursor[nCntCursor].nPatternAnim + 1), 1.0f);

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffCursor->Unlock();

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawCursor(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X����������
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCursor, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntCursor = 0; nCntCursor < CURSOR_MAX; nCntCursor++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureCursor[nCntCursor]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntCursor * MAX_CURSORTOP,
			2);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ���쏈��(�L�[����)
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetOperation(int nIndex)
{
	// �L�[���͂ɂ��ړ�
	static int nIdy = 0;
	if (GetKeyboardTrigger(DIK_0))
	{// 1�Ԗڂ̃J�[�\��
		nIdy = 0;
	}
	if (GetKeyboardTrigger(DIK_1))
	{// 2�Ԗڂ̃J�[�\��
		nIdy = 1;
	}
	if (GetKeyboardTrigger(DIK_2))
	{// 3�Ԗڂ̃J�[�\��
		nIdy = 2;
	}
	if (GetKeyboardTrigger(DIK_3))
	{// 4�Ԗڂ̃J�[�\��
		nIdy = 3;
	}
	if (nIndex == nIdy)
	{
		// �C�ӂ̃L�[�������ꂽ���ǂ���
		if (GetKeyboardPress(DIK_A) == true)
		{// ����
			if (GetKeyboardPress(DIK_W) == true)
			{// ����
				g_aCursor[nIdy].move.x -= sinf(D3DX_PI / 4 * 3) * MOVE_SPEED;
				g_aCursor[nIdy].move.y += cosf(D3DX_PI / 4 * 3) * MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// ����
				g_aCursor[nIdy].move.x -= sinf(D3DX_PI / 4) * MOVE_SPEED;
				g_aCursor[nIdy].move.y += cosf(D3DX_PI / 4) * MOVE_SPEED;
			}
			else
			{// ��
				g_aCursor[nIdy].move.x -= sinf(D3DX_PI / 2) * MOVE_SPEED;
				g_aCursor[nIdy].move.y += cosf(D3DX_PI / 2) * MOVE_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// �E��
			if (GetKeyboardPress(DIK_W) == true)
			{// �E��
				g_aCursor[nIdy].move.x += sinf(D3DX_PI / 4 * 3) * MOVE_SPEED;
				g_aCursor[nIdy].move.y += cosf(D3DX_PI / 4 * 3) * MOVE_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// �E��
				g_aCursor[nIdy].move.x += sinf(D3DX_PI / 4) * MOVE_SPEED;
				g_aCursor[nIdy].move.y += cosf(D3DX_PI / 4) * MOVE_SPEED;
			}
			else
			{// �E
				g_aCursor[nIdy].move.x += sinf(D3DX_PI / 2) * MOVE_SPEED;
				g_aCursor[nIdy].move.y -= cosf(D3DX_PI / 2) * MOVE_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{// ��
			g_aCursor[nIdy].move.x += sinf(D3DX_PI) * MOVE_SPEED;
			g_aCursor[nIdy].move.y += cosf(D3DX_PI) * MOVE_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// ��
			g_aCursor[nIdy].move.x -= sinf(D3DX_PI * 0) * MOVE_SPEED;
			g_aCursor[nIdy].move.y += cosf(D3DX_PI * 0) * MOVE_SPEED;
		}
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			if (g_aCursor[nIdy].state == CURSORSTATE_CATCH)
			{// �͂�
				g_aCursor[nIdy].state = CURSORSTATE_RELEASE_START;		// ��Ԃ�؂�ւ���
				g_aCursor[nIdy].nPatternAnim = 0;					// �e�N�X�`���؂�ւ�
			}
			else if (g_aCursor[nIdy].state == CURSORSTATE_RELEASE)
			{// ����
				g_aCursor[nIdy].state = CURSORSTATE_CATCH;			// ��Ԃ�؂�ւ���
				g_aCursor[nIdy].nPatternAnim = 1;					// �e�N�X�`���؂�ւ�
			}
		}

		if (g_aCursor[nIdy].state == CURSORSTATE_RELEASE)
		{// �����Ă��鎞(�}�[�J�[��u���Ă�Ƃ�)
			Player *pPlayer = GetPlayer();
			if (GetKeyboardTrigger(DIK_E) == true)
			{// �J���[�ύX
				g_aCursor[nIdy].colorType = pPlayer[nIdy].colType;	// �v���C���[�̐F������
				SetColSel(false, nIdy, g_aCursor[nIdy].colorType);	// ���̐F�� false �ɂ���
				g_aCursor[nIdy].colorType++;						// �F�̎�ނ�ς���
				if (g_aCursor[nIdy].colorType >= PLAYERCOLOR_MAX)
				{// �F�̎�ނ𒴂����Ƃ�
					g_aCursor[nIdy].colorType = 0;
				}

				if (false == GetColSel(nIdy, g_aCursor[nIdy].colorType))
				{// �F���g���Ă��Ȃ�������
					SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// �V�����F�� true �ɂ���
				}
				else if (true == GetColSel(nIdy, g_aCursor[nIdy].colorType))
				{// �F���g���Ă�����
					do
					{
						g_aCursor[nIdy].colorType++;						// �F��ς���
						if (g_aCursor[nIdy].colorType >= PLAYERCOLOR_MAX)
						{// �F�̎�ނ𒴂����Ƃ�
							g_aCursor[nIdy].colorType = 0;
						}

					} while (false != GetColSel(nIdy, g_aCursor[nIdy].colorType));
					SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// �V�����F�� true �ɂ���
				}
				if (g_aCursor[nIdy].colorType == PLAYERCOLOR_STANDARD)
				{// �����F�̂Ƃ�
					pPlayer[nIdy].colType = PLAYERCOLOR_STANDARD;
				}
				else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF1)
				{// �Ⴄ�F�̂Ƃ�
					pPlayer[nIdy].colType = PLAYERCOLOR_DIF1;
				}
				else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF2)
				{// �Ⴄ�F�̂Ƃ�
					pPlayer[nIdy].colType = PLAYERCOLOR_DIF2;
				}
				else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF3)
				{// �Ⴄ�F�̂Ƃ�
					pPlayer[nIdy].colType = PLAYERCOLOR_DIF3;
				}
			}
			else if (GetKeyboardTrigger(DIK_Q) == true)
			{// �J���[�ύX
				g_aCursor[nIdy].colorType = pPlayer[nIdy].colType;	// �v���C���[�̐F������
				SetColSel(false, nIdy, g_aCursor[nIdy].colorType);	// ���̐F�� false �ɂ���
				g_aCursor[nIdy].colorType--;						// �F�̎�ނ�ς���
				if (g_aCursor[nIdy].colorType < 0)
				{// �F�̎�ނ𒴂����Ƃ�
					g_aCursor[nIdy].colorType = PLAYERCOLOR_DIF3;
				}

				if (false == GetColSel(nIdy, g_aCursor[nIdy].colorType))
				{// �F���g���Ă��Ȃ�������
					SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// �V�����F�� true �ɂ���
				}
				else if (true == GetColSel(nIdy, g_aCursor[nIdy].colorType))
				{// �F���g���Ă�����
					do
					{
						g_aCursor[nIdy].colorType++;						// �F��ς���
						if (g_aCursor[nIdy].colorType >= PLAYERCOLOR_MAX)
						{// �F�̎�ނ𒴂����Ƃ�
							g_aCursor[nIdy].colorType = 0;
						}

					} while (false != GetColSel(nIdy, g_aCursor[nIdy].colorType));
					SetColSel(true, nIdy, g_aCursor[nIdy].colorType);	// �V�����F�� true �ɂ���
				}
				if (g_aCursor[nIdy].colorType == PLAYERCOLOR_STANDARD)
				{// �����F�̂Ƃ�
					pPlayer[nIdy].colType = PLAYERCOLOR_STANDARD;
				}
				else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF1)
				{// �Ⴄ�F�̂Ƃ�
					pPlayer[nIdy].colType = PLAYERCOLOR_DIF1;
				}
				else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF2)
				{// �Ⴄ�F�̂Ƃ�
					pPlayer[nIdy].colType = PLAYERCOLOR_DIF2;
				}
				else if (g_aCursor[nIdy].colorType == PLAYERCOLOR_DIF3)
				{// �Ⴄ�F�̂Ƃ�
					pPlayer[nIdy].colType = PLAYERCOLOR_DIF3;
				}
			}
		}
	}
	GamePad *pGamePad = GetgamePadStick();
	if (pGamePad[nIndex].pDevGamePad != NULL)
	{
		if (pGamePad[nIndex].aGamePad.lX < -GAMEPAD_DEADZONE || pGamePad[nIndex].aGamePad.lX > GAMEPAD_DEADZONE || pGamePad[nIndex].aGamePad.lY < -GAMEPAD_DEADZONE || pGamePad[nIndex].aGamePad.lY> GAMEPAD_DEADZONE)
		{
			float fGamePagStickAngle = atan2f(float(-pGamePad[nIndex].aGamePad.lX), float(pGamePad[nIndex].aGamePad.lY));
			g_aCursor[nIndex].move.x -= sinf(fGamePagStickAngle) * MOVE_SPEED;
			g_aCursor[nIndex].move.y += cosf(fGamePagStickAngle) * MOVE_SPEED;

		}
	}
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �J�[�\��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
CURSOR *GetCursors(void)
{
	return &g_aCursor[0];
}