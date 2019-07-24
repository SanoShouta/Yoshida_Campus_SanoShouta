//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : �������� Sato_Asumi
//
//=============================================================================
#include "item.h"
#include "shadow.h"
#include <time.h>
//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_NAME00	"data\\TEXTURE\\item.png"		// �ǂ݂��ރe�N�X�`���t�@�C����
#define MAX_ITEM		(20)							// �A�C�e���̍ő吔
#define RANGE			(25.0f)							// �����蔻��͈̔�
#define UV				(0.125f)						// UV�l�̈ړ���
#define COUNTER			(60 * 5)						// �m���̔���b��
#define INTERBAL		(60 * 10)						// �A�C�e����ݒu����܂ł̎���
#define GRAVITY			(0.1f)							// �d��

//�A�C�e���̃T�C�Y
#define ITEM_SIZE_X		(50.0f)							// �A�C�e���̃T�C�Y
#define ITEM_SIZE_Y		(50.0f)							// �A�C�e���̃T�C�Y

//�S���_�̍��W
#define ITEM_MIN_X		((ITEM_SIZE_X / 2) * -1)		// ���l�̍ŏ��l
#define ITEM_MAX_X		(ITEM_SIZE_X / 2)				// ���l�̍ő�l
#define ITEM_MIN_Y		(0.0f)							// y�l�̍ŏ��l
#define ITEM_MAX_Y		(ITEM_SIZE_Y)					// y�l�̍ő�l

//�e�̑傫��
#define SHADOW_SIZE		(40.0f)							// �e�̃T�C�Y

//�A�C�e���̏o�����W
#define ITEM_POS_00		(D3DXVECTOR3(400.0f -float(rand()%800), 300.0f, -100 +float(rand()%500)))		//�o���ʒu00
#define ITEM_POS_01		(D3DXVECTOR3(400.0f -float(rand()%800), 300.0f, -100 +float(rand()%500)))	//�o���ʒu01
#define ITEM_POS_02		(D3DXVECTOR3(400.0f -float(rand()%800), 300.0f, -100 +float(rand()%500)))	//�o���ʒu02
#define ITEM_POS_03		(D3DXVECTOR3(400.0f -float(rand()%800), 300.0f, -100 +float(rand()%500)))	//�o���ʒu03
#define ITEM_POS_04		(D3DXVECTOR3(400.0f -float(rand()%800), 300.0f, -100 +float(rand()%500)))	//�o���ʒu04
#define ITEM_POS_05		(D3DXVECTOR3(400.0f -float(rand()%800), 300.0f, -100 +float(rand()%500)))	//�o���ʒu05
#define ITEM_POS_06		(D3DXVECTOR3(400.0f -float(rand()%800), 300.0f, -100 +float(rand()%500)))		//�o���ʒu06

//�Ȃ��߂̐ݒ�l
#define CHANDY_LOWPIORITY		(10)
#define CHANDY_ATK				(0)
#define CHANDY_HEAL				(10)
#define CHANDY_SPD				(0)

//���݂����̐ݒ�l
#define OMIKUZI_LOWPIORITY		(20)
#define OMIKUZI_ATK				(float(rand()%200/100.0f))
#define OMIKUZI_HEAL			(0)
#define OMIKUZI_SPD				(float(rand()%200/100.0f))

//�����Ă��̐ݒ�l
#define TAKOYAKI_LOWPIORITY		(30)
#define TAKOYAKI_ATK			(0)
#define TAKOYAKI_HEAL			(5)
#define TAKOYAKI_SPD			(0)

//���イ��̐ݒ�l
#define CUCUMBER_LOWPIORITY		(40)
#define CUCUMBER_ATK			(0)
#define CUCUMBER_HEAL			(3)
#define CUCUMBER_SPD			(0.5f)

//�������̐ݒ�l
#define FRIEDTOUHU_LOWPIORITY	(50)
#define FRIEDTOUHU_ATK			(1.0f)
#define FRIEDTOUHU_HEAL			(3)
#define FRIEDTOUHU_SPD			(0)

//�t���ς̐ݒ�l
#define LEAF_LOWPIORITY			(60)
#define LEAF_ATK				(0.5f)
#define LEAF_HEAL				(5)
#define LEAF_SPD				(0.3f)

//�˂��̐ݒ�l
#define SCREW_LOWPIORITY		(70)
#define SCREW_ATK				(0.7f)
#define SCREW_HEAL				(0)
#define SCREW_SPD				(0.1f)

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexItem(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureItem = NULL;	// �e�N�X�`���ւ̃|�C���^
D3DXVECTOR2				g_texItem;				//�e�N�X�`��
Item					g_aItem[MAX_ITEM];		//�A�C�e���̏��
Data					g_aData[ITEMTYPE_MAX];	//�A�C�e���̏��
ITEMPOS					g_ItemPos;				//���݂̃A�C�e���̏o���ʒu
ITEMPOS					g_ItemOldPos;			//�O��̃A�C�e���̏o���ʒu
bool					g_bSetItem;				//�A�C�e����u�������ǂ���
int						g_nCntTime;				//���ԃJ�E���^�[

//=============================================================================
// ����������
//=============================================================================
void InitItem(void)
{
	//�ϐ��錾
	int nCntItem;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME00,
		&g_pTextureItem);

	//�O���[�o���ϐ��̏�����
	g_ItemPos = ITEMPOS_00;
	g_ItemOldPos = ITEMPOS_00;
	g_bSetItem = false;
	g_nCntTime = 0;

	//�ϐ��̏�����
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].fAttack = 0;
		g_aItem[nCntItem].fHeal = 0;
		g_aItem[nCntItem].fSpeed = 0;
		g_aItem[nCntItem].nIdxshadow = 0;
		g_aItem[nCntItem].pMeshFieldLand = NULL;
		g_aItem[nCntItem].pModel = NULL;
		g_aItem[nCntItem].bUse = false;
		g_aItem[nCntItem].nLife = 0;
	}

	//�Œ�m���̐ݒ�
	g_aData[0].nLowProbability = CHANDY_LOWPIORITY;		//�Ȃ���
	g_aData[1].nLowProbability = OMIKUZI_LOWPIORITY;	//���݂���
	g_aData[2].nLowProbability = TAKOYAKI_LOWPIORITY;	//�����Ă�
	g_aData[3].nLowProbability = CUCUMBER_LOWPIORITY;	//���イ��
	g_aData[4].nLowProbability = FRIEDTOUHU_LOWPIORITY;	//���g��
	g_aData[5].nLowProbability = LEAF_LOWPIORITY;		//�t����
	g_aData[6].nLowProbability = SCREW_LOWPIORITY;		//�˂�

	//�^�C�v�̂̐ݒ�
	g_aData[0].type = ITEMTYPE_CHANDY;					//�Ȃ���
	g_aData[1].type = ITEMTYPE_OMIKUZI;					//���݂���
	g_aData[2].type = ITEMTYPE_TAKOYAKI;				//�����Ă�
	g_aData[3].type = ITEMTYPE_CUCUMBER;				//���イ��
	g_aData[4].type = ITEMTYPE_FRIED_TOUHU;				//���g��
	g_aData[5].type = ITEMTYPE_LEAF;					//�t����
	g_aData[6].type = ITEMTYPE_SCREW;					//�˂�

	//�ϐ��̏�����
	for (nCntItem = 0; nCntItem < ITEMTYPE_MAX; nCntItem++)
	{
		g_aData[nCntItem].fAttack = 0;
		g_aData[nCntItem].fHeal = 0;
		g_aData[nCntItem].fSpeed = 0;
		g_aData[nCntItem].Probability = 100;
		g_aData[nCntItem].nCounter = 0;

		//�^�C�v�ݒ�
		switch (g_aData[nCntItem].type)
		{
		case ITEMTYPE_CHANDY:		// �킽����
			g_aData[nCntItem].fAttack = CHANDY_ATK;				//�U����
			g_aData[nCntItem].fHeal = CHANDY_HEAL;				//�񕜗�
			g_aData[nCntItem].fSpeed = CHANDY_SPD;				//�X�s�[�h
			break;

		case ITEMTYPE_OMIKUZI:		// ���݂���
			g_aData[nCntItem].fAttack = OMIKUZI_ATK;				//�U����
			g_aData[nCntItem].fHeal = OMIKUZI_HEAL;				//�񕜗�
			g_aData[nCntItem].fSpeed = OMIKUZI_SPD;				//�X�s�[�h
			break;

		case ITEMTYPE_TAKOYAKI:		// �����Ă�
			g_aData[nCntItem].fAttack = TAKOYAKI_ATK;				//�U����
			g_aData[nCntItem].fHeal = TAKOYAKI_HEAL;			//�񕜗�
			g_aData[nCntItem].fSpeed = TAKOYAKI_SPD;				//�X�s�[�h
			break;

		case ITEMTYPE_CUCUMBER:		// ���イ��
			g_aData[nCntItem].fAttack = CUCUMBER_ATK;				//�U����
			g_aData[nCntItem].fHeal = CUCUMBER_HEAL;			//�񕜗�
			g_aData[nCntItem].fSpeed = CUCUMBER_SPD;				//�X�s�[�h
			break;

		case ITEMTYPE_FRIED_TOUHU:	// ���g��
			g_aData[nCntItem].fAttack = FRIEDTOUHU_ATK;			//�U����
			g_aData[nCntItem].fHeal = FRIEDTOUHU_HEAL;			//�񕜗�
			g_aData[nCntItem].fSpeed = FRIEDTOUHU_SPD;			//�X�s�[�h
			break;

		case ITEMTYPE_LEAF:			// �t����
			g_aData[nCntItem].fAttack = LEAF_ATK;					//�U����
			g_aData[nCntItem].fHeal = LEAF_HEAL;				//�񕜗�
			g_aData[nCntItem].fSpeed = LEAF_SPD;					//�X�s�[�h
			break;

		case ITEMTYPE_SCREW:		// �˂�
			g_aData[nCntItem].fAttack = LEAF_ATK;					//�U����
			g_aData[nCntItem].fHeal = LEAF_HEAL;				//�񕜗�
			g_aData[nCntItem].fSpeed = LEAF_SPD;					//�X�s�[�h
			break;
		}
	}

	// ���_���̍쐬
	MakeVertexItem(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{
	//�ϐ��錾
	int nCntItem;
	int nPriority;

	//���b�V���t�B�[���h�̎擾
	MeshField *pMeshField = GetMeshField();


	//�m���̔���
	if (g_bSetItem == false)
	{
		for (nCntItem = 0; nCntItem < ITEMTYPE_MAX; nCntItem++)
		{
			//�m���J�E���^�[�̉��Z
			g_aData[nCntItem].nCounter++;

			if ((g_aData[nCntItem].nCounter % COUNTER) == 0)
			{
				//�o������
				nPriority = rand() % g_aData[nCntItem].Probability;

				//����l����������\������
				if (nPriority < g_aData[nCntItem].nLowProbability)
				{
					SetItem(g_aData[nCntItem].type);
					g_bSetItem = true;
					break;
				}
			}
		}
	}

	//�Z�b�g�A�C�e������̏�����
	if (g_bSetItem == true)
	{
		//���Ԃ̉��Z
		g_nCntTime++;

		//�����false�ɂ���
		if ((g_nCntTime % INTERBAL) == 0)
		{
			g_bSetItem = false;
		}
	}

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			//�O��̈ʒu��ۑ�����
			g_aItem[nCntItem].posOld = g_aItem[nCntItem].pos;

			//�d�͉��Z������
			g_aItem[nCntItem].move.y -= GRAVITY;

			//�ʒu�X�V
			g_aItem[nCntItem].pos += g_aItem[nCntItem].move;
			g_aItem[nCntItem].nLife--;
			if (g_aItem[nCntItem].nLife <= 0)
			{
				DeleteItem(nCntItem);
				DeleteShadow(g_aItem[nCntItem].nIdxshadow);

			}
			if (CollisionMeshField(&g_aItem[nCntItem].pos, &g_aItem[nCntItem].posOld, &g_aItem[nCntItem].move,
				ITEM_SIZE_X, ITEM_SIZE_Y, &g_aItem[nCntItem].pMeshFieldLand) == true)
			{//�����̍��W���C������
				g_aItem[nCntItem].pos.y = 0.0f;
			}
			if (CollisionModelMinMax(&g_aItem[nCntItem].pos, &g_aItem[nCntItem].posOld, &g_aItem[nCntItem].move, ITEM_SIZE_X, ITEM_SIZE_Y, &g_aItem[nCntItem].pModel) == 2)
			{// ��ɂ̂�
				Shadow *pShadow = GetShadow();
				pShadow[g_aItem[nCntItem].nIdxshadow].move.y = 0.0f;
				pShadow[g_aItem[nCntItem].nIdxshadow].pos.y = g_aItem[nCntItem].pos.y + 0.1f;
				pShadow[g_aItem[nCntItem].nIdxshadow].col.a = 1.0f;
			}
		}
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	//�ϐ��錾
	int nCntItem;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX		  mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X
	D3DXMATRIX		  mtxView;					//�r���[�}�g���N�X

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aItem[nCntItem].mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�t�s���ݒ�
			g_aItem[nCntItem].mtxWorld._11 = mtxView._11;
			g_aItem[nCntItem].mtxWorld._12 = mtxView._21;
			g_aItem[nCntItem].mtxWorld._13 = mtxView._31;
			g_aItem[nCntItem].mtxWorld._21 = mtxView._12;
			g_aItem[nCntItem].mtxWorld._22 = mtxView._22;
			g_aItem[nCntItem].mtxWorld._23 = mtxView._32;
			g_aItem[nCntItem].mtxWorld._31 = mtxView._13;
			g_aItem[nCntItem].mtxWorld._32 = mtxView._23;
			g_aItem[nCntItem].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, g_aItem[nCntItem].pos.z);
			D3DXMatrixMultiply(&g_aItem[nCntItem].mtxWorld, &g_aItem[nCntItem].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aItem[nCntItem].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItem);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntItem * 4,
				2);
		}
	}

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexItem(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	int nCntItem;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	VERTEX_3D * pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(ITEM_MIN_X, ITEM_MAX_Y, 00.0f);
		pVtx[1].pos = D3DXVECTOR3(ITEM_MAX_X, ITEM_MAX_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(ITEM_MIN_X, ITEM_MIN_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(ITEM_MAX_X, ITEM_MIN_Y, 0.0f);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �ݒ���
//=============================================================================
void SetItem(ITEMTYPE type)
{
	//�ϐ��錾
	int nCntItem;

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].bUse = true;
			g_aItem[nCntItem].type = type;
			g_aItem[nCntItem].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�e�N�X�`����UV�l�̐ݒ�
			SetTex(nCntItem, g_aItem[nCntItem].type);

			//�ʒu�̐ݒ�
			g_aItem[nCntItem].pos = SetPos(rand() % (int)ITEMPOS_MAX);
			g_aItem[nCntItem].nLife = 600;
			//�X�e�[�^�X�̐ݒ�
			g_aItem[nCntItem].fAttack = g_aData[type].fAttack;
			g_aItem[nCntItem].fHeal = g_aData[type].fHeal;
			g_aItem[nCntItem].fSpeed = g_aData[type].fSpeed;

			//�e�̐ݒ�
			g_aItem[nCntItem].nIdxshadow = SetShadow(D3DXVECTOR3(g_aItem[nCntItem].pos.x,
				0.0f,
				g_aItem[nCntItem].pos.z),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				SHADOW_SIZE, SHADOW_SIZE);

			break;
		}
	}
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CollsionItem(D3DXVECTOR3 pos, float fRadiusWidth, float fRadiusHeight, float *pLife, float *pAttack, float *pSpeed)
{
	//�ϐ��錾
	bool bGet = false;
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{// �g�p���Ă���
			if (g_aItem[nCntItem].pos.y + (ITEM_SIZE_Y) >= pos.y&&							// ��
				g_aItem[nCntItem].pos.y <= pos.y + fRadiusHeight&&							// ��
				g_aItem[nCntItem].pos.x + (ITEM_SIZE_X / 2) >= pos.x - fRadiusWidth / 2&&	// �E
				g_aItem[nCntItem].pos.x - (ITEM_SIZE_X / 2) <= pos.x + fRadiusWidth / 2&&	// ��
				g_aItem[nCntItem].pos.z - (ITEM_SIZE_X / 2) <= pos.z + fRadiusWidth / 2&&	// ��O
				g_aItem[nCntItem].pos.z + (ITEM_SIZE_X / 2) >= pos.z - fRadiusWidth / 2)	// ��
			{// �A�C�e���ɂԂ�����
				DeleteItem(nCntItem);
				DeleteShadow(g_aItem[nCntItem].nIdxshadow);
				*pLife = (float(g_aData[g_aItem[nCntItem].type].fHeal));
				*pAttack += (float(g_aData[g_aItem[nCntItem].type].fAttack));
				*pSpeed = (float(g_aData[g_aItem[nCntItem].type].fSpeed));
				bGet = true;
				break;
			}
		}
	}
	return bGet;
}

//=============================================================================
// ��������
//=============================================================================
void DeleteItem(int nCntItem)
{
	if (g_aItem[nCntItem].bUse == true)
	{
		g_aItem[nCntItem].bUse = false;				//�I�u�W�F�N�g������
		DeleteShadow(g_aItem[nCntItem].nIdxshadow);	//�e������
	}
}

//=============================================================================
// UV�̊��蓖��
//=============================================================================
void SetTex(int nIndex, int nType)
{
	VERTEX_3D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	//�Y���̈ʒu�܂Ői�߂�
	pVtx += (4 * nIndex);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (UV * nType), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(UV + (UV * nType), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (UV * nType), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(UV + (UV * nType), 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �A�C�e���̏��擾
//=============================================================================
Item * GetItem(void)
{
	return &g_aItem[0];
}

//=============================================================================
// �A�C�e���̏o���ʒu�̐ݒ�
//=============================================================================
D3DXVECTOR3 SetPos(int nItemPos)
{
	//�ϐ��錾
	D3DXVECTOR3 ItemPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//���W�ݒ�
	switch (nItemPos)
	{
	case ITEMPOS_00:
		ItemPos = ITEM_POS_00;
		break;

	case ITEMPOS_01:
		ItemPos = ITEM_POS_01;
		break;

	case ITEMPOS_02:
		ItemPos = ITEM_POS_02;
		break;

	case ITEMPOS_03:
		ItemPos = ITEM_POS_03;
		break;

	case ITEMPOS_04:
		ItemPos = ITEM_POS_04;
		break;

	case ITEMPOS_05:
		ItemPos = ITEM_POS_05;
		break;

	case ITEMPOS_06:
		ItemPos = ITEM_POS_06;
		break;
	}

	return ItemPos;

}