//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �L�����N�^�[�Z���N�g���� [marker.cpp]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "main.h"
#include "input.h"
#include "marker.h"
#include "cursor.h"
#include "charsel.h"
#include "gamepad.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �O���[�o���ϐ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
LPDIRECT3DTEXTURE9		g_pTextureMarker[MARKER_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMarker = NULL;
MARKER					g_aMarker[MARKER_MAX];
int						g_nTotalMarker;										// �}�[�J�[�̒u���Ă鑍��
bool					g_bCharColType[PLAYERTYPE_MAX][PLAYERCOLOR_MAX];	// �}�[�J�[��u���ꂽ�Ƃ��̐F�؂�ւ�

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �}�[�J�[�̏���������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitMarker(void)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	LPDIRECT3DDEVICE9 pDevice;

	for (int nCntMarker = 0; nCntMarker < MARKER_MAX; nCntMarker++)
	{
		g_aMarker[nCntMarker].pos = D3DXVECTOR3(300.0f, 250.0f, 0.0f);
		g_aMarker[nCntMarker].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMarker[nCntMarker].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMarker[nCntMarker].fWidth = MARKER_WIDTH;
		g_aMarker[nCntMarker].fHeight = MARKER_HEIGHT;
		g_aMarker[nCntMarker].type = PLAYERTYPE_MAX;
		g_aMarker[nCntMarker].bUse = false;
	}
	g_aMarker[0].pos = D3DXVECTOR3(180.0f, 180.0f, 0.0f);
	g_aMarker[1].pos = D3DXVECTOR3(1100.0f, 180.0f, 0.0f);
	g_aMarker[2].pos = D3DXVECTOR3(180.0f, 540.0f, 0.0f);
	g_aMarker[3].pos = D3DXVECTOR3(1100.0f, 540.0f, 0.0f);

	for (int nCntCharType = 0; nCntCharType < PLAYERTYPE_MAX; nCntCharType++)
	{
		for (int nCntColType = 0; nCntColType < PLAYERCOLOR_MAX; nCntColType++)
		{
			g_bCharColType[nCntCharType][nCntColType] = false;
		}
	}
	g_nTotalMarker = 0;
	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		MARKER_TEXTURENAME0,
		&g_pTextureMarker[0]);
	D3DXCreateTextureFromFile(pDevice,
		MARKER_TEXTURENAME1,
		&g_pTextureMarker[1]);
	D3DXCreateTextureFromFile(pDevice,
		MARKER_TEXTURENAME2,
		&g_pTextureMarker[2]);
	D3DXCreateTextureFromFile(pDevice,
		MARKER_TEXTURENAME3,
		&g_pTextureMarker[3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_MARKERTOP * MARKER_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMarker,
		NULL);

	//���_l�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMarker->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMarker = 0; nCntMarker < MARKER_MAX; nCntMarker++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x - g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y - g_aMarker[nCntMarker].fHeight / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x + g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y - g_aMarker[nCntMarker].fHeight / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x - g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y + g_aMarker[nCntMarker].fHeight / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x + g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y + g_aMarker[nCntMarker].fHeight / 2, 0.0f);
		//rhw
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�F
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMarker->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �}�[�J�[�̏I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitMarker(void)
{
	for (int nCntTex = 0; nCntTex < MARKER_MAX; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureMarker[nCntTex] != NULL)
		{
			g_pTextureMarker[nCntTex]->Release();
			g_pTextureMarker[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMarker != NULL)
	{
		g_pVtxBuffMarker->Release();
		g_pVtxBuffMarker = NULL;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �}�[�J�[�̍X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateMarker(void)
{
	CURSOR *pCarsor = GetCursors();
	int nNumGamePad = GetGamePadNum();
	for (int nCntMarker = 0; nCntMarker < MARKER_MAX; nCntMarker++)
	{
		g_aMarker[nCntMarker].posOld = g_aMarker[nCntMarker].pos;		// �O��̍��W������

		g_aMarker[nCntMarker].pos.x += g_aMarker[nCntMarker].move.x;	// ���ړ�
		g_aMarker[nCntMarker].pos.y += g_aMarker[nCntMarker].move.y;	// �c�ړ�

		// ����
		g_aMarker[nCntMarker].move.x += (0.0f - g_aMarker[nCntMarker].move.x) * 0.3f;
		g_aMarker[nCntMarker].move.y += (0.0f - g_aMarker[nCntMarker].move.y) * 0.3f;

		//�g�O�ɏo��Ȃ�����
		if (g_aMarker[nCntMarker].pos.x < g_aMarker[nCntMarker].fWidth / 2)
		{	// ��
			g_aMarker[nCntMarker].pos.x = g_aMarker[nCntMarker].fWidth / 2;
		}
		if (g_aMarker[nCntMarker].pos.x > SCREEN_WIDTH - g_aMarker[nCntMarker].fWidth / 2)
		{	// �E
			g_aMarker[nCntMarker].pos.x = SCREEN_WIDTH - g_aMarker[nCntMarker].fWidth / 2;
		}
		if (g_aMarker[nCntMarker].pos.y < g_aMarker[nCntMarker].fHeight / 2)
		{	// ��
			g_aMarker[nCntMarker].pos.y = g_aMarker[nCntMarker].fHeight / 2;
		}
		if (g_aMarker[nCntMarker].pos.y > SCREEN_HEIGHT - g_aMarker[nCntMarker].fHeight / 2)
		{	// ��
			g_aMarker[nCntMarker].pos.y = SCREEN_HEIGHT - g_aMarker[nCntMarker].fHeight / 2;
		}

		Player *pPlayer = GetPlayer();

		if (pCarsor[nCntMarker].state == CURSORSTATE_RELEASE_START)
		{// �L�����N�^�[��I�����n�߂̂Ƃ�(�u�����Ƃ�)
			for (int nCntColor = 0; nCntColor < PLAYERCOLOR_MAX; nCntColor++)
			{
 				g_aMarker[nCntMarker].type = CollisionCharsel(g_aMarker[nCntMarker].pos, g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].fHeight / 2, g_aMarker[nCntMarker].type);
				if (g_bCharColType[g_aMarker[nCntMarker].type][nCntColor] == false)
				{// �v���C���[�̔z�F
					pPlayer[nCntMarker].colType = (PLAYERCOLOR)nCntColor;

					if (g_aMarker[nCntMarker].type != PLAYERTYPE_MAX)
					{// �v���C���[�Z�b�g
						PlaySound(SOUND_CHARACTOR_SELECT);
						SetPlayer(nCntMarker, D3DXVECTOR3(nCntMarker * 50.0f, 0, 0), g_aMarker[nCntMarker].type);
						SetTypePlayer(nCntMarker, g_aMarker[nCntMarker].type);
					}
					g_bCharColType[g_aMarker[nCntMarker].type][nCntColor] = true;
					break;
				}
			}
		}
		else if (pCarsor[nCntMarker].state == CURSORSTATE_RELEASE)
		{// �L�����N�^�[��I�������Ƃ�(�u���Ă�Ƃ�)
			if (g_aMarker[nCntMarker].bUse == false)
			{
				g_nTotalMarker++;	// �I�������������Z
				g_aMarker[nCntMarker].bUse = true;
			}
		}
		else
		{// �I�����Ă��Ȃ��Ƃ�(�u���ĂȂ��Ƃ�)
			if (g_aMarker[nCntMarker].bUse == true)
			{
				g_aMarker[nCntMarker].bUse = false;
			}
				ReleasePlayer(nCntMarker);
				SetTypePlayer(nCntMarker, g_aMarker[nCntMarker].type);

			if (g_bCharColType[g_aMarker[nCntMarker].type][pPlayer[nCntMarker].colType] == true)
			{
				g_bCharColType[g_aMarker[nCntMarker].type][pPlayer[nCntMarker].colType] = false;
				g_aMarker[nCntMarker].type = PLAYERTYPE_MAX;
			}
		}

		if (g_nTotalMarker >= nNumGamePad)
		{// �������h�����Ă���Q�[���p�b�h�ȏ�̂Ƃ�
			g_nTotalMarker = nNumGamePad;
		}
		if (pCarsor[nCntMarker].state == CURSORSTATE_CATCH&&
			pCarsor[nCntMarker].stateOld == CURSORSTATE_RELEASE)
		{// �������܂Œu���Ă��āA�����������i�I������߂��u�ԁj
			g_nTotalMarker--;	// �I������߂������Z
			if (g_nTotalMarker <= 0)
			{// ������0�ȉ��ɂȂ����Ƃ�
				g_nTotalMarker = 0;
			}
		}
	}
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_l�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMarker->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMarker = 0; nCntMarker < MARKER_MAX; nCntMarker++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x - g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y - g_aMarker[nCntMarker].fHeight / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x + g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y - g_aMarker[nCntMarker].fHeight / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x - g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y + g_aMarker[nCntMarker].fHeight / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aMarker[nCntMarker].pos.x + g_aMarker[nCntMarker].fWidth / 2, g_aMarker[nCntMarker].pos.y + g_aMarker[nCntMarker].fHeight / 2, 0.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMarker->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �}�[�J�[�̕`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawMarker(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X����������
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMarker, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntMarker = 0; nCntMarker < MARKER_MAX; nCntMarker++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMarker[nCntMarker]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntMarker * MAX_MARKERTOP,
			2);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �}�[�J�[�̎擾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
MARKER *GetMarker(void)
{
	return &g_aMarker[0];
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �}�[�J�[�̎擾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int GetNumMarker(void)
{
	return g_nTotalMarker;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �F���g�p���Ă���̂����Z�b�g
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetColSel(bool bColSel, int nIdy, int nColId)
{
	g_bCharColType[g_aMarker[nIdy].type][nColId] = bColSel;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �F���g�p���Ă���̂����擾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool GetColSel(int nIdy, int nColId)
{
	return g_bCharColType[g_aMarker[nIdy].type][nColId];

}