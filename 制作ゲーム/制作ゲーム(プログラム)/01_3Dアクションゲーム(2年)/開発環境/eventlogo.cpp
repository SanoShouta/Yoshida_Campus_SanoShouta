//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �C�x���g���S���� [ eventlogo.cpp ]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "eventlogo.h"
#include "input.h"
#include "gamepad.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �\���̒�`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct
{
	char *pFileName;
	EVENTLOGOTEX type;
}EventlogoTexture;

typedef struct
{
	EVENTLOGOTEX texType;
	EVENTTYPE eventType;
}EventTypeInfo;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �O���[�o���ϐ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
VERTEX_2D				g_aVertexEventlogo;
LPDIRECT3DTEXTURE9		g_pTextureEventlogo[EVENTLOGOTEX_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEventlogo = NULL;
EVENTLOGO				g_Eventlogo[EVENTTYPE_MAX];

EventlogoTexture g_aEventlogoTexInfo[EVENTLOGOTEX_MAX] =
{
	{ " ",										EVENTLOGOTEX_NONE },			// �����Ȃ�
	{ "data/TEXTURE/Event_Flood4-2.png",		EVENTLOGOTEX_WATER },			// �^��
	{ "data/TEXTURE/Event_Fire002.png",			EVENTLOGOTEX_FIRE },			// �Ύ�
	{ "data/TEXTURE/Event_Fall_Rock001.png",	EVENTLOGOTEX_FALLING_ROCK },	// ����
	{ "data/TEXTURE/Event_Meteo003.png",		EVENTLOGOTEX_METEORITE },		// 覐�
	{ "data/TEXTURE/Event_Rain cloud004.png",	EVENTLOGOTEX_RAIN },			// �J
	{ "data/TEXTURE/Event_Lightning4-3.png",	EVENTLOGOTEX_THUNDER },			// ��
	{ "data/TEXTURE/Event_Fall_Obj000.png",		EVENTLOGOTEX_FALLING_OBJECT },	// ����
	{ "data/TEXTURE/Event_Gust4-1.png",			EVENTLOGOTEX_GUST },			// �˕�
};

EventTypeInfo g_aEventTypeInfo[EVENTTYPE_MAX] =
{
	{ EVENTLOGOTEX_NONE,			EVENTTYPE_NONE },				// �����Ȃ�
	{ EVENTLOGOTEX_WATER,			EVENTTYPE_WATER },				// �^��
	{ EVENTLOGOTEX_FIRE,			EVENTTYPE_FIRE },				// �Ύ�
	{ EVENTLOGOTEX_FALLING_ROCK,	EVENTTYPE_FALLING_ROCK },		// �����̗���
	{ EVENTLOGOTEX_FALLING_ROCK,	EVENTTYPE_FALLING_BIGROCK },	// �傫����̗���
	{ EVENTLOGOTEX_METEORITE,		EVENTTYPE_METEORSHOWER },		// �����Q
	{ EVENTLOGOTEX_METEORITE,		EVENTTYPE_METEORITE },			// 覐�
	{ EVENTLOGOTEX_RAIN,			EVENTTYPE_RAIN },				// �J�Ō����ɂ���
	{ EVENTLOGOTEX_THUNDER,			EVENTTYPE_THUNDER },			// ��
	{ EVENTLOGOTEX_FALLING_OBJECT,	EVENTTYPE_FALLING_CHOUTIN },	// �񓔗���
	{ EVENTLOGOTEX_FALLING_OBJECT,	EVENTTYPE_FALLING_BRANCH },		// �؂̎}����
	{ EVENTLOGOTEX_GUST,			EVENTTYPE_LEEF },				// �t���ςŌ����ɂ���
	{ EVENTLOGOTEX_GUST,			EVENTTYPE_GUST },				// �˕�
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �C�x���g���S�̏�����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitEventlogo(void)
{
	VERTEX_2D*pVtx;		// ���_���ւ̃|�C���^

	LPDIRECT3DDEVICE9 pDevice;
	// �f�o�C�X�̏���
	pDevice = GetDevice();
	// �e�N�X�`���̓ǂݍ���
	for (int nCntEventlogoTex = 0; nCntEventlogoTex < EVENTLOGOTEX_MAX; nCntEventlogoTex++)
	{// �e�N�X�`����
		D3DXCreateTextureFromFile(pDevice,
			g_aEventlogoTexInfo[nCntEventlogoTex].pFileName,
			&g_pTextureEventlogo[nCntEventlogoTex]);
	}
	for (int nCntEventlogo = 0; nCntEventlogo < EVENTTYPE_MAX; nCntEventlogo++)
	{// �C�x���g����
		g_Eventlogo[nCntEventlogo].pos = D3DXVECTOR3(EVENTLOGO_POS_X, EVENTLOGO_POS_Y, 0.0f);
		g_Eventlogo[nCntEventlogo].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Eventlogo[nCntEventlogo].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Eventlogo[nCntEventlogo].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		g_Eventlogo[nCntEventlogo].fWidth = EVENTLOGO_WIDTH;
		g_Eventlogo[nCntEventlogo].fHeight = EVENTLOGO_HEIGHT;
		g_Eventlogo[nCntEventlogo].bAlpha = false;
		g_Eventlogo[nCntEventlogo].nCountDiaplay = 0;
		g_Eventlogo[nCntEventlogo].nNumTimes = 0;
		g_Eventlogo[nCntEventlogo].bUse = false;
		g_Eventlogo[nCntEventlogo].type = g_aEventTypeInfo[nCntEventlogo].eventType;
		g_Eventlogo[nCntEventlogo].texType = g_aEventTypeInfo[nCntEventlogo].texType;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * EVENTLOGO_MAX * EVENTTYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEventlogo,
		NULL);

	// ���_l�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEventlogo->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEventlogo = 0; nCntEventlogo < EVENTTYPE_MAX; nCntEventlogo++, pVtx += 4)
	{
		// ���W
		pVtx[0].pos = D3DXVECTOR3(g_Eventlogo[nCntEventlogo].pos.x - g_Eventlogo[nCntEventlogo].fWidth, g_Eventlogo[nCntEventlogo].pos.y - g_Eventlogo[nCntEventlogo].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Eventlogo[nCntEventlogo].pos.x + g_Eventlogo[nCntEventlogo].fWidth, g_Eventlogo[nCntEventlogo].pos.y - g_Eventlogo[nCntEventlogo].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Eventlogo[nCntEventlogo].pos.x - g_Eventlogo[nCntEventlogo].fWidth, g_Eventlogo[nCntEventlogo].pos.y + g_Eventlogo[nCntEventlogo].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Eventlogo[nCntEventlogo].pos.x + g_Eventlogo[nCntEventlogo].fWidth, g_Eventlogo[nCntEventlogo].pos.y + g_Eventlogo[nCntEventlogo].fHeight, 0.0f);

		// rhw
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// �F
		pVtx[0].col = g_Eventlogo[nCntEventlogo].col;
		pVtx[1].col = g_Eventlogo[nCntEventlogo].col;
		pVtx[2].col = g_Eventlogo[nCntEventlogo].col;
		pVtx[3].col = g_Eventlogo[nCntEventlogo].col;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEventlogo->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �C�x���g���S�̏I������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UninitEventlogo(void)
{
	// �e�N�X�`���̔j��
	for (int nCntEventlogo = 0; nCntEventlogo < EVENTLOGOTEX_MAX; nCntEventlogo++)
	{
		if (g_pTextureEventlogo[nCntEventlogo] != NULL)
		{
			g_pTextureEventlogo[nCntEventlogo]->Release();
			g_pTextureEventlogo[nCntEventlogo] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffEventlogo != NULL)
	{
		g_pVtxBuffEventlogo->Release();
		g_pVtxBuffEventlogo = NULL;
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �C�x���g���S�̍X�V����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UpdateEventlogo(void)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
	// ���_l�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEventlogo->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEventlogo = 0; nCntEventlogo < EVENTTYPE_MAX; nCntEventlogo++, pVtx += 4)
	{
		if (g_Eventlogo[nCntEventlogo].bUse == true)
		{
			if (g_Eventlogo[nCntEventlogo].nNumTimes < EVENTLOGO_NUMTIMES)
			{// ��萔��菬�����Ƃ�
				if (g_Eventlogo[nCntEventlogo].bAlpha == true)
				{// �\�����Ă�Ƃ�
					g_Eventlogo[nCntEventlogo].col.a -= EVENTLOGO_APPEARSPEED;		// �����x�̌��Z
					if (g_Eventlogo[nCntEventlogo].col.a <= 0.0f)
					{// �����x�� 0 �ȉ��ɂȂ����Ƃ�
						g_Eventlogo[nCntEventlogo].bAlpha = false;					// �\�����Ă��Ԃɂ���
						g_Eventlogo[nCntEventlogo].nNumTimes++;	  					// �\������J�E���g�����Z
					}
				}
				else if (g_Eventlogo[nCntEventlogo].bAlpha == false)
				{// �\�����ĂȂ��Ƃ�
					g_Eventlogo[nCntEventlogo].col.a += EVENTLOGO_APPEARSPEED;		// �����x�̉��Z
					if (g_Eventlogo[nCntEventlogo].col.a >= 1.0f)
					{// �����x�� 1 �ȏ�̂Ƃ�
						g_Eventlogo[nCntEventlogo].nCountDiaplay++;					// �\�����̃J�E���g�����Z
						if (g_Eventlogo[nCntEventlogo].nCountDiaplay >= 15)
						{// ��莞�Ԍo�����Ƃ�
							g_Eventlogo[nCntEventlogo].bAlpha = true;				// �\�����Ă��Ԃɂ���
							g_Eventlogo[nCntEventlogo].nCountDiaplay = 0;			// �\�����̃J�E���g������������
						}
					}
				}
			}
			else
			{// ��߂�ꂽ�񐔂𒴂����Ƃ�
				g_Eventlogo[nCntEventlogo].bUse = false;
				g_Eventlogo[nCntEventlogo].nNumTimes = 0;
			}
		}
		// ���_���W
		pVtx[0].col = g_Eventlogo[nCntEventlogo].col;
		pVtx[1].col = g_Eventlogo[nCntEventlogo].col;
		pVtx[2].col = g_Eventlogo[nCntEventlogo].col;
		pVtx[3].col = g_Eventlogo[nCntEventlogo].col;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEventlogo->Unlock();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �C�x���g���S�̕`�揈��
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DrawEventlogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X����������
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEventlogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEventlogo = 0; nCntEventlogo < EVENTTYPE_MAX; nCntEventlogo++)
	{
		if (g_Eventlogo[nCntEventlogo].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEventlogo[g_Eventlogo[nCntEventlogo].texType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEventlogo * EVENTLOGO_MAX,
				2);
		}
	}
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �C�x���g���S�̐ݒ�
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void SetEventlogo(D3DXVECTOR3 pos, float fWidth, float fHeight, EVENTTYPE type)
{
	g_Eventlogo[type].pos = pos;
	g_Eventlogo[type].fWidth = fWidth;
	g_Eventlogo[type].fHeight = fHeight;
	g_Eventlogo[type].type = type;
	g_Eventlogo[type].bUse = true;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �C�x���g���S����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void DeleteEventLogo(void)
{
	for (int nCntEventlogo = 0; nCntEventlogo < EVENTTYPE_MAX; nCntEventlogo++)
	{
		if (g_Eventlogo[nCntEventlogo].bUse == true)
		{
			g_Eventlogo[nCntEventlogo].bUse = false;
		}
	}
}