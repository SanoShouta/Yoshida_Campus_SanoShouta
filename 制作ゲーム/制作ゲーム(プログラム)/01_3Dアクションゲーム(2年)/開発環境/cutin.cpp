//=============================================================================
//
// �J�b�g�C������ [cutin.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "cutin.h"
#include "main.h"
#include "input.h"
#include "sound.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_SIZEX	(640)		//�L�����N�^�[�|���S����X�ő�l
#define MAX_SIZEY	(110)		//�L�����N�^�[�|���S����X�ő�l
#define MIN_SIZEY	(10)		//�L�����N�^�[�|���S����Y�ŏ��l
#define MOVE_X		(-12.0f)		//�ړ���
#define MOVESIZE_Y	(3.0f)		//�T�C�Y�̕ω���
#define INTERVAL	(15)		//�C���^�[�o���^�C��

#define MINSKILL_SIZE	(280)	//�����o���̃T�C�Y
#define MAXSKILL_SIZE	(560)	//�����o���̃T�C�Y
#define NOMALSKILL_SIZE	(350)	//�����o���̃T�C�Y
#define SKILL_MOVE		(10)	//�T�C�Y�̕ύX��

#define POS				(D3DXVECTOR3(640, 360, 0))	//���S�_
#define SIZE			(D3DXVECTOR3(640, 110, 0))	//�T�C�Y
#define SIZE_X			(550)
#define SIZE_Y			(80)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureCut[CUT_TEXTYPE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCut = NULL;					//���_�o�b�t�@�ւ̃|�C���^
Cut						g_Cut[MAX_CUTIN];						//���ݒ�
int						g_nCutTime;								//���ԃJ�E���^�[
int						g_nId;									//Id�̎擾

//=============================================================================
// �X�^�[�g�{�^������������
//=============================================================================
void InitCut(void)
{
	//�ϐ��錾
	int     nCntCut;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	g_nCutTime = 0;
	g_nId = 0;
	for (nCntCut = 0; nCntCut < MAX_CUTIN; nCntCut++)
	{
		g_Cut[nCntCut].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���S���W
		g_Cut[nCntCut].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�T�C�Y
		g_Cut[nCntCut].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
		g_Cut[nCntCut].chara = CHARATAYPE_MAX;					//�L�����N�^�[�^�C�v
		g_Cut[nCntCut].type = CUTTYPE_MAX;						//�|���S���̃^�C�v
		g_Cut[nCntCut].nTexNum = 0;								//�e�N�X�`���̔ԍ�
		g_Cut[nCntCut].CutState = CUTSTATE_NONE;					//�J�b�g�C��
		g_Cut[nCntCut].bUse = false;							//�g�p���Ă��Ȃ���Ԃɂ���
		g_Cut[nCntCut].bMove = false;							//�ړ��ʂ̃��Z�b�g
		g_Cut[nCntCut].cola = 1.0f;								//�����x

	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cutIn.png", &g_pTextureCut[0]);		//�L�����N�^�[
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cutin01.jpg", &g_pTextureCut[1]);	//���F
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cutIn02.png", &g_pTextureCut[2]);	//�����o��

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_CUTIN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCut,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCut->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCut = 0; nCntCut < MAX_CUTIN; nCntCut++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCut->Unlock();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitCut(void)
{
	//�ϐ��錾
	int nCntTex;

	//�e�N�X�`���̔j��
	for (nCntTex = 0; nCntTex < CUT_TEXTYPE_MAX; nCntTex++)
	{
		if (g_pTextureCut[nCntTex] != NULL)
		{
			g_pTextureCut[nCntTex]->Release();
			g_pTextureCut[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCut != NULL)
	{
		g_pVtxBuffCut->Release();
		g_pVtxBuffCut = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateCut(void)
{
	//�ϐ��錾
	int nCntCut;

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCut->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCut = 0; nCntCut < MAX_CUTIN; nCntCut++)
	{
		if (g_Cut[nCntCut].bUse == true)
		{
			if (g_Cut[nCntCut].type == CUTTYPE_KYARACTOR)
			{
				switch (g_Cut[nCntCut].CutState)
				{
				case CUTSTATE_IN:
					g_nId = nCntCut;								//Id�̕ۊ�
					g_Cut[nCntCut].move.x += MOVE_X;				//�ړ��ʂ̉��Z
					g_Cut[nCntCut].pos.x += g_Cut[nCntCut].move.x;	//�ʒu�X�V

					if (g_Cut[nCntCut].pos.x < MAX_SIZEX)
					{
						g_Cut[nCntCut].pos.x = MAX_SIZEX;	//�ʒu�C��
						g_nCutTime++;						//���Ԃ̉��Z
						g_Cut[nCntCut].move.x = 0;
						SetCut(2, D3DXVECTOR3(400, 360, 0), g_Cut[nCntCut].chara, CUTTYPE_SKILL);	//�����o���̃Z�b�g
						g_Cut[nCntCut].CutState = CUTSTATE_OPEN;
					}
					break;

				case CUTSTATE_OPEN:

					g_Cut[nCntCut].nTexNum = 0;					//�e�N�X�`���̕ύX
					g_Cut[nCntCut].move.x += MOVESIZE_Y;			//�ړ��ʂ̉��Z
					g_Cut[nCntCut].size.y += g_Cut[nCntCut].move.x;	//�T�C�Y�̍X�V

					if (g_Cut[nCntCut].size.y > MAX_SIZEY)
					{
						g_Cut[nCntCut].size.y = MAX_SIZEY;
						g_nCutTime++;						//���Ԃ̉��Z

						g_Cut[nCntCut].move.x = 0;
						g_Cut[nCntCut].CutState = CUTSTATE_NOMAL;
					}
					break;

				case CUTSTATE_OUT:
					g_Cut[nCntCut].cola -= 0.2f;

					if (g_Cut[nCntCut].cola < 0.0f)
					{
						g_Cut[nCntCut].cola = 0.0f;
						g_Cut[nCntCut].bUse = false;
					}
					break;
				}
			}
			else if(g_Cut[nCntCut].type == CUTTYPE_SKILL)
			{
				switch (g_Cut[nCntCut].NameState)
				{
				case NAMESTATE_IN:
					//�T�C�Y�̕ύX
					g_Cut[nCntCut].move.x += -30.0f;
					g_Cut[nCntCut].move.y += -30.0f;

					//�T�C�Y�̍X�V
					g_Cut[nCntCut].size.x += g_Cut[nCntCut].move.x;
					g_Cut[nCntCut].size.y += g_Cut[nCntCut].move.y;

					//�l�C��
					if (g_Cut[nCntCut].size.x < MINSKILL_SIZE)
					{
						g_Cut[nCntCut].size.x = MINSKILL_SIZE;
						g_Cut[nCntCut].size.y = MINSKILL_SIZE;

						g_nCutTime++;						//���Ԃ̉��Z

						if ((g_nCutTime % 30) == 0)
						{
							g_Cut[nCntCut].NameState = NAMESTATE_OUT;
							SetCutState(CUTSTATE_OUT);
						}
					}
					break;

				case NAMESTATE_OUT:
					g_Cut[nCntCut].cola -= 0.2f;

					if(g_Cut[nCntCut].cola < 0.0f)
					{
						g_Cut[nCntCut].cola = 0.0f;
						g_Cut[nCntCut].bUse = false;
					}
					break;
				}
			}

			//���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x - g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y - g_Cut[nCntCut].size.y, 0);
			pVtx[1].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x + g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y - g_Cut[nCntCut].size.y, 0);
			pVtx[2].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x - g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y + g_Cut[nCntCut].size.y, 0);
			pVtx[3].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x + g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y + g_Cut[nCntCut].size.y, 0);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Cut[nCntCut].cola);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Cut[nCntCut].cola);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Cut[nCntCut].cola);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Cut[nCntCut].cola);
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCut->Unlock();
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawCut(void)
{
	//�ϐ��錾
	int nCntCut;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCut, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntCut = 0; nCntCut < MAX_CUTIN; nCntCut++)
	{
		if (g_Cut[nCntCut].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureCut[g_Cut[nCntCut].nTexNum]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
				nCntCut * 4,	//�J�n���钸�_�̃C���f�b�N�X
				2);						//�v���~�e�B�u�̐�
		}
	}
}

//=============================================================================
// ���ݒ�
//=============================================================================
int SetCut(int nTexNum, D3DXVECTOR3 pos, CHARATAYPE chara, CUTTYPE type)
{
	//�ϐ��錾
	int nCntCut;
	int nNumIndx = 0;
	float fHalfWidth = 0;		//��
	float fHalfHight = 0;		//����

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCut->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCut = 0; nCntCut < MAX_CUTIN; nCntCut++)
	{
		if (g_Cut[nCntCut].bUse == false)
		{
			g_Cut[nCntCut].pos = pos;								//���S���W
			g_Cut[nCntCut].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
			g_Cut[nCntCut].chara= chara;							//�L�����N�^�[�^�C�v
			g_Cut[nCntCut].type = type;								//�|���S���̃^�C�v
			g_Cut[nCntCut].bMove = false;							//�ړ��ʂ̃��Z�b�g
			g_Cut[nCntCut].CutState = CUTSTATE_NONE;				//�J�b�g�C���̏��
			g_Cut[nCntCut].NameState = NAMESTATE_NONE;				//�J�b�g�C���̏��
			g_Cut[nCntCut].cola = 1.0f;								//�����x

			if (g_Cut[nCntCut].chara == CHARATAYPE_HUMAN)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.2f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.2f);
			}
			else if (g_Cut[nCntCut].chara == CHARATAYPE_TENGU)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.2f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.2f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.4f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.4f);
			}
			else if (g_Cut[nCntCut].chara == CHARATAYPE_KAPPA)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.4f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.4f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.6f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.6f);
			}
			else if (g_Cut[nCntCut].chara == CHARATAYPE_FOX)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.6f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.6f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.8f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.8f);
			}
			else if (g_Cut[nCntCut].chara == CHARATAYPE_ROBOT)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.8f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.8f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}

			switch (g_Cut[nCntCut].type)
			{
			case CUTTYPE_KYARACTOR:
				PlaySound(SOUND_CUTIN);
				//�T�C�Y�̐ݒ�
				g_Cut[nCntCut].size = D3DXVECTOR3(MAX_SIZEX, MIN_SIZEY, 0.0f);
				g_Cut[nCntCut].CutState = CUTSTATE_IN;		//�����Ԃɐݒ肷��
				break;

			case CUTTYPE_SKILL:
				PlaySound(SOUND_SPECIALROGO);
				//�T�C�Y�̐ݒ�
				g_Cut[nCntCut].size = D3DXVECTOR3(MAXSKILL_SIZE, MAXSKILL_SIZE, 0.0f);
				g_Cut[nCntCut].NameState = NAMESTATE_IN;		//�����Ԃɐݒ肷��
				break;
			}

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x - g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y - g_Cut[nCntCut].size.y, 0);
			pVtx[1].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x + g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y - g_Cut[nCntCut].size.y, 0);
			pVtx[2].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x - g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y + g_Cut[nCntCut].size.y, 0);
			pVtx[3].pos = D3DXVECTOR3(g_Cut[nCntCut].pos.x + g_Cut[nCntCut].size.x, g_Cut[nCntCut].pos.y + g_Cut[nCntCut].size.y, 0);

			g_Cut[nCntCut].nTexNum = nTexNum;		//�e�N�X�`���̔ԍ�

			g_Cut[nCntCut].bUse = true;			//�g�p���Ă����Ԃɂ���
			nNumIndx = nCntCut;
			break;
		}

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCut->Unlock();

	return nNumIndx;
}

//=============================================================================
// ����̃|���S��������
//=============================================================================
void DeleteAllCut(void)
{
	for (int nCntCut = 0; nCntCut < MAX_CUTIN; nCntCut++)
	{
		g_Cut[nCntCut].bUse = false;
	}
}

//=============================================================================
// �����擾
//=============================================================================
Cut * GetCut(void)
{
	return &g_Cut[0];
}

//=============================================================================
//�@��Ԃ̐ݒ�
//=============================================================================
void SetCutState(CUTSTATE state)
{
	g_Cut[g_nId].CutState = state;
}