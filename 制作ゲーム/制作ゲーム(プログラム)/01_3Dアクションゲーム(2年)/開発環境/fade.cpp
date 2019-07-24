////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �t�F�[�h���� [fade.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "fade.h"
#include "main.h"

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define FADE_TEX "data/TEXTURE/black.png"				// �ǂݍ��ރe�N�X�`��
#define FADE_TEX1 "data/TEXTURE/black.png"		// �ǂݍ��ރe�N�X�`��
//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureFade[2] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
FADE					g_fade;					// �t�F�[�h���
MODE					g_modeNext;				// ���̃��[�h
D3DXCOLOR				g_colorFade;			// �t�F�[�h�F
int						g_nCounterAnim;
int						g_nPatternAnim;
bool					g_bChangeMode;
//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_fade = FADE_IN;									// �t�F�[�h�C����Ԃɂ���
	g_modeNext = modeNext;								// ���[�h�ݒ�
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// ������ʁi�����j�ɂ��Ă���
	g_nCounterAnim = 0;
	g_nPatternAnim = 0;
	g_bChangeMode = false;
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
						FADE_TEX,
						&g_pTextureFade[0]);
	D3DXCreateTextureFromFile(pDevice,
						FADE_TEX1,
						&g_pTextureFade[1]);

	// ���_���̐ݒ�
	MakeVertexFade(pDevice);
}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitFade(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureFade[nCnt] != NULL)
		{
			g_pTextureFade[nCnt]->Release();
			g_pTextureFade[nCnt] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateFade(void)
{
	VERTEX_2D*pVtx;		// ���_���ւ̃|�C���^

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)			// �t�F�[�h�C����Ԃ�
		{
			g_colorFade.a -= 0.02f;	// ��ʂ𓧖��ɂ��Ă���
			if (g_colorFade.a <= 0.0f)
			{// �����ɂȂ�����
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT)	// �t�F�[�h�A�E�g��Ԃ�
		{
			g_colorFade.a += 0.02f;	// ��ʂ�s�����ɂ��Ă���
			if (g_colorFade.a >= 1.0f)
			{// �s�����ɂȂ�����
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;	// �t�F�[�h�C����Ԃ�
				if (g_bChangeMode == true)
				{
					// ���[�h�̐ݒ�
					SetMode(g_modeNext);
				}
			}
		}
	}

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	pVtx[4].col = g_colorFade;
	pVtx[5].col = g_colorFade;
	pVtx[6].col = g_colorFade;
	pVtx[7].col = g_colorFade;
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();
}

//==============================================================================================================================
// �^�C�g�����
//==============================================================================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFade[0]);
	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pTextureFade[1]);
	//// �|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);
}

//==============================================================================================================================
// ���_���̍쐬
//==============================================================================================================================
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D*pVtx;		// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	// rhw�̐ݒ�
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].rhw = 1.0f;
	}
	// ���_�J���[�̐ݒ�
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;
	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���̐ݒ�
	pVtx[4].pos = D3DXVECTOR3(-(70*1.6f / 2) + (SCREEN_WIDTH/2) - 50, -(140 / 2)+ (630), 0.0f);
	pVtx[5].pos = D3DXVECTOR3((70 * 1.6f / 2) +( SCREEN_WIDTH / 2) - 50, -(140 / 2) +(630), 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-(70 * 1.6f / 2) + (SCREEN_WIDTH / 2) - 50, (140 / 2) + (630), 0.0f);
	pVtx[7].pos = D3DXVECTOR3((70 * 1.6f / 2) + (SCREEN_WIDTH / 2) - 50, (140 / 2) + (630), 0.0f);
	// rhw�̐ݒ�
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt+4].rhw = 1.0f;
	}
	// ���_�J���[�̐ݒ�
	pVtx[4].col = g_colorFade;
	pVtx[5].col = g_colorFade;
	pVtx[6].col = g_colorFade;
	pVtx[7].col = g_colorFade;
	// �e�N�X�`�����W�̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();

}

//==============================================================================================================================
// �t�F�[�h�̐ݒ�
//==============================================================================================================================
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;									// �t�F�[�h�A�E�g��Ԃɂ���
	g_modeNext = modeNext;								// ���[�h�ݒ�
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// ������ʁi�s�����j�ɂ��Ă���
	g_bChangeMode = true;								// ���[�h�ς���
}

//==============================================================================================================================
// �t�F�[�h�̐ݒ�
//==============================================================================================================================
void SetFadeNone(void)
{
	g_fade = FADE_OUT;									// �t�F�[�h�A�E�g��Ԃɂ���
	g_bChangeMode = false;								// ���[�h�ς��Ȃ�
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// ������ʁi�s�����j�ɂ��Ă���
}

//==============================================================================================================================
// �t�F�[�h�̎擾
//==============================================================================================================================
FADE GetFade(void)
{
	return g_fade;
}

