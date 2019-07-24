//=============================================================================
//
// �|���S������ [flontpolygon.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "flontpolygon.h"
#include "main.h"
#include "input.h"
#include <time.h>
#include "game.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define TEX_MOVE	(0.0005f)	//�e�N�X�`����UV�ړ��l

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureFlontPolygon[FLONT_TEXTYPE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFlontPolygon = NULL;			//���_�o�b�t�@�ւ̃|�C���^
FlontPolygon			g_FlontPolygon[MAX_FLONTPOLYGON];		//���ݒ�
int						g_nMaxFlontPolygon;

//=============================================================================
// �X�^�[�g�{�^������������
//=============================================================================
void InitFlontPolygon(void)
{
	//�ϐ��錾
	int     nCntFlontPolygon;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		g_FlontPolygon[nCntFlontPolygon].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���S���W
		g_FlontPolygon[nCntFlontPolygon].fHight = 0.0f;								//����
		g_FlontPolygon[nCntFlontPolygon].fWidth = 0.0f;								//��
		g_FlontPolygon[nCntFlontPolygon].fUv = 0.0f;								//UV�l
		g_FlontPolygon[nCntFlontPolygon].nTexNum = 0;								//�e�N�X�`���̔ԍ�
		g_FlontPolygon[nCntFlontPolygon].type = FLONTTYPE_MAX;						//�^�C�v
		g_FlontPolygon[nCntFlontPolygon].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
		g_FlontPolygon[nCntFlontPolygon].bUse = false;								//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Chotin000.png",	&g_pTextureFlontPolygon[0]);		//��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\CharactorAll001.png", &g_pTextureFlontPolygon[1]);	//�L�����N�^�[�̗����G
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Comment000.png", &g_pTextureFlontPolygon[2]);	//�����o��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\AreYouReady.png", &g_pTextureFlontPolygon[3]);	//����
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title_logo.png", &g_pTextureFlontPolygon[4]);	//�^�C�g��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\StateUI000.png", &g_pTextureFlontPolygon[5]);		//UI
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\CharactorAll002.png", &g_pTextureFlontPolygon[6]);//��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GameSetting000.png", &g_pTextureFlontPolygon[7]);//�w��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GameStart000.png", &g_pTextureFlontPolygon[8]);//�w��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GameEnd000.png", &g_pTextureFlontPolygon[9]);//�w��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\fg.png", &g_pTextureFlontPolygon[10]);	//�I����ʂ̉���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg.jpg", &g_pTextureFlontPolygon[11]);	//�I����ʂ̔w�i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\TimeUp000.png", &g_pTextureFlontPolygon[12]);//�^�C���A�b�v

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FLONTPOLYGON,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffFlontPolygon,
								NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFlontPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(250.0f, 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(750.0f, 100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(250.0f, 200.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(750.0f, 200.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_FlontPolygon[nCntFlontPolygon].col;
		pVtx[1].col = g_FlontPolygon[nCntFlontPolygon].col;
		pVtx[2].col = g_FlontPolygon[nCntFlontPolygon].col;
		pVtx[3].col = g_FlontPolygon[nCntFlontPolygon].col;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFlontPolygon->Unlock();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitFlontPolygon(void)
{
	//�ϐ��錾
	int nCntTex;

	//�e�N�X�`���̔j��
	for (nCntTex = 0; nCntTex < FLONT_TEXTYPE_MAX; nCntTex++)
	{
		if (g_pTextureFlontPolygon[nCntTex] != NULL)
		{
			g_pTextureFlontPolygon[nCntTex]->Release();
			g_pTextureFlontPolygon[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFlontPolygon != NULL)
	{
		g_pVtxBuffFlontPolygon->Release();
		g_pVtxBuffFlontPolygon = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateFlontPolygon(void)
{
	//�ϐ��錾
	int nCntFP;

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFlontPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFP = 0; nCntFP < MAX_FLONTPOLYGON; nCntFP++, pVtx += 4)
	{
		if (g_FlontPolygon[nCntFP].bUse == true)
		{
			switch (g_FlontPolygon[nCntFP].type)
			{
			case FLONTTYPE_CHOTIN:

				//�ړ��l�̍X�V
				g_FlontPolygon[nCntFP].fUv += TEX_MOVE;

				if (g_FlontPolygon[nCntFP].fUv >= 1.0f)
				{
					g_FlontPolygon[nCntFP].fUv = 0.0f;
				}

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f + g_FlontPolygon[nCntFP].fUv, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f + g_FlontPolygon[nCntFP].fUv, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + g_FlontPolygon[nCntFP].fUv, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f + g_FlontPolygon[nCntFP].fUv, 1.0f);

				break;
			case FLONTTYPE_NARRATION:// �i���[�V����
				break;
			}
			switch (g_FlontPolygon[nCntFP].nTexNum)
			{
			case FLONT_TEXTYPE_SETTING:
				g_FlontPolygon[nCntFP].col.a += 0.1f;
				if (g_FlontPolygon[nCntFP].col.a >= 1.0f)
				{
					g_FlontPolygon[nCntFP].col.a = 1.0f;
				}
				g_FlontPolygon[nCntFP].pos.x += -0.1f;
				break;
			case FLONT_TEXTYPE_START:

				g_FlontPolygon[nCntFP].fWidth += (SCREEN_WIDTH / 1.5f - g_FlontPolygon[nCntFP].fWidth)*0.2f;
				g_FlontPolygon[nCntFP].fHight += (200 - g_FlontPolygon[nCntFP].fHight)*0.2f;
				if (g_FlontPolygon[nCntFP].fWidth - 10 <= SCREEN_WIDTH / 1.5f&&
					g_FlontPolygon[nCntFP].fHight - 10 <= 200)
				{
					g_FlontPolygon[nCntFP].col.a -= 0.1f;
					if (g_FlontPolygon[nCntFP].col.a <= 0.0f)
					{
						g_FlontPolygon[nCntFP].bUse = false;
					}
				}
				else
				{
					g_FlontPolygon[nCntFP].col.a += 0.1f;
					if (g_FlontPolygon[nCntFP].col.a >= 1.0f)
					{
						g_FlontPolygon[nCntFP].col.a = 1.0f;
					}
				}
				break;
			case FLONT_TEXTYPE_GAMEEND:
				g_FlontPolygon[nCntFP].col.a += 0.1f;
				if (g_FlontPolygon[nCntFP].col.a >= 1.0f)
				{
					g_FlontPolygon[nCntFP].col.a = 1.0f;
				}
				break;
			case FLONT_TEXTYPE_TIMEUP:
				g_FlontPolygon[nCntFP].pos.x += -1.0f;

				if (g_FlontPolygon[nCntFP].col.a >= 1.0f)
				{
					g_FlontPolygon[nCntFP].col.a = 1.0f;
				}
				if (GetGameStateCounter() >= 60)
				{
					g_FlontPolygon[nCntFP].col.a -= 0.1f;
					if (g_FlontPolygon[nCntFP].col.a <= 0.0f)
					{
						g_FlontPolygon[nCntFP].bUse = false;
						g_FlontPolygon[nCntFP].col.a = 0.0f;
					}

				}
				else
				{
					g_FlontPolygon[nCntFP].col.a += 0.1f;
				}
				break;
			}
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_FlontPolygon[nCntFP].fWidth / 2, -g_FlontPolygon[nCntFP].fHight / 2, 0.0f) + g_FlontPolygon[nCntFP].pos;
			pVtx[1].pos = D3DXVECTOR3(g_FlontPolygon[nCntFP].fWidth / 2, -g_FlontPolygon[nCntFP].fHight / 2, 0.0f) + g_FlontPolygon[nCntFP].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_FlontPolygon[nCntFP].fWidth / 2, g_FlontPolygon[nCntFP].fHight / 2, 0.0f) + g_FlontPolygon[nCntFP].pos;
			pVtx[3].pos = D3DXVECTOR3(g_FlontPolygon[nCntFP].fWidth / 2, g_FlontPolygon[nCntFP].fHight / 2, 0.0f) + g_FlontPolygon[nCntFP].pos;
			// �F�ݒ�
			pVtx[0].col = g_FlontPolygon[nCntFP].col;
			pVtx[1].col = g_FlontPolygon[nCntFP].col;
			pVtx[2].col = g_FlontPolygon[nCntFP].col;
			pVtx[3].col = g_FlontPolygon[nCntFP].col;

		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFlontPolygon->Unlock();

}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawFlontPolygon(void)
{
	//�ϐ��錾
	int nCntFlontPolygon;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFlontPolygon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureFlontPolygon[g_FlontPolygon[nCntFlontPolygon].nTexNum]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
								   nCntFlontPolygon * 4,	//�J�n���钸�_�̃C���f�b�N�X
								   2);						//�v���~�e�B�u�̐�
		}
	}
}

//=============================================================================
// ���ݒ�
//=============================================================================
int SetFlontPolygon(int nTexNum, D3DXVECTOR3 pos, float fWidth, float fHight, FLONTTYPE type)
{
	//�ϐ��錾
	int nCntFlontPolygon;
	int nNumIndx = 0;
	float fHalfWidth = 0;		//��
	float fHalfHight = 0;		//����

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFlontPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == false)
		{
			g_FlontPolygon[nCntFlontPolygon].pos = pos;				//���S���W
			g_FlontPolygon[nCntFlontPolygon].fHight = fHight;		//����
			g_FlontPolygon[nCntFlontPolygon].fWidth = fWidth;		//��
			g_FlontPolygon[nCntFlontPolygon].type = type;			//�^�C�v
			g_FlontPolygon[nCntFlontPolygon].fUv = 0.0f;			//UV�l

			//���ƍ�����ݒ肷��
			fHalfWidth = g_FlontPolygon[nCntFlontPolygon].fWidth * 0.5f;
			fHalfHight = g_FlontPolygon[nCntFlontPolygon].fHight * 0.5f;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_FlontPolygon[nCntFlontPolygon].fWidth/2,-g_FlontPolygon[nCntFlontPolygon].fHight/2, 0.0f)+g_FlontPolygon[nCntFlontPolygon].pos;
			pVtx[1].pos = D3DXVECTOR3(g_FlontPolygon[nCntFlontPolygon].fWidth/2,-g_FlontPolygon[nCntFlontPolygon].fHight/2, 0.0f)+g_FlontPolygon[nCntFlontPolygon].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_FlontPolygon[nCntFlontPolygon].fWidth/2,g_FlontPolygon[nCntFlontPolygon].fHight/2, 0.0f)+g_FlontPolygon[nCntFlontPolygon].pos;
			pVtx[3].pos = D3DXVECTOR3(g_FlontPolygon[nCntFlontPolygon].fWidth/2,g_FlontPolygon[nCntFlontPolygon].fHight/2, 0.0f)+g_FlontPolygon[nCntFlontPolygon].pos;

			if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_CYARACTOR)
			{
				//����ݒ肷��
				srand((unsigned int)time(0));
				int nChara = rand() % 5;			//�L�����N�^�[�̐ݒ�

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.2f * nChara), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.2f + (0.2f * nChara), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.2f * nChara), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.2f + (0.2f * nChara), 1.0f);
			}
			else if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_FACE_HUMAN)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.2f, 1.0f);
			}
			else if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_FACE_TENGU)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.2f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.4f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.2f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.4f, 1.0f);
			}
			else if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_FACE_KAPPA)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.4f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.6f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.4f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.6f, 1.0f);
			}
			else if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_FACE_FOX)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.6f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.8f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.6f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.8f, 1.0f);
			}
			else if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_FACE_ROBOT)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.8f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.8f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_NARRATION)
			{
				g_FlontPolygon[nCntFlontPolygon].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			else if (g_FlontPolygon[nCntFlontPolygon].type == FLONTTYPE_UI)
			{
				g_FlontPolygon[nCntFlontPolygon].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);

			}
			else
			{
				g_FlontPolygon[nCntFlontPolygon].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}

			g_FlontPolygon[nCntFlontPolygon].nTexNum = nTexNum;		//�e�N�X�`���̔ԍ�

			pVtx[0].col = g_FlontPolygon[nCntFlontPolygon].col;
			pVtx[1].col = g_FlontPolygon[nCntFlontPolygon].col;
			pVtx[2].col = g_FlontPolygon[nCntFlontPolygon].col;
			pVtx[3].col = g_FlontPolygon[nCntFlontPolygon].col;


			g_FlontPolygon[nCntFlontPolygon].bUse = true;			//�g�p���Ă����Ԃɂ���
			nNumIndx = nCntFlontPolygon;
			break;
		}

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFlontPolygon->Unlock();

	return nNumIndx;
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
void SetTexture(int nIdx, int nNumComment)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFlontPolygon->Lock(0, 0, (void**)&pVtx, 0);

	if (g_FlontPolygon[nIdx].bUse == true)
	{
		pVtx += 4 * nIdx;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.25f * nNumComment), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f + (0.25f * nNumComment), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.25f * nNumComment), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f + (0.25f * nNumComment), 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFlontPolygon->Unlock();
}

//=============================================================================
// �|���S�������ׂď���
//=============================================================================
void  ReleaseAllFlontPolygon()
{
	//�ϐ��錾
	int nCntFlontPolygon;

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == true)
		{
			g_FlontPolygon[nCntFlontPolygon].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
		}
	}
}

//=============================================================================
// ����̃|���S��������
//=============================================================================
void DeleteFlontPolygon(int nIdx)
{
	if (g_FlontPolygon[nIdx].bUse == true)
	{
		g_FlontPolygon[nIdx].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
	}
}

//=============================================================================
// �����擾
//=============================================================================
FlontPolygon * GetFlontPolygon(void)
{
	return &g_FlontPolygon[0];
}