////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "effect.h"
#include "player.h"
#include "game.h"
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define MAX_EFFECT	    (2244)
#define ANIM			(0.2f)
#define MAX_PATTERN		(5)
#define MAX_ANIMSPEED	(5)

//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef struct
{
	char *pFileName;
}EffectTexture;
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_apTextureEffect[EFFECTTYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
Effect g_aEffect[MAX_EFFECT];

EffectTexture g_aEffectTexInfo[EFFECTTYPE_MAX] =
{
	{ "data/TEXTURE/smokeEffect.png" },
	{ "data/TEXTURE/HitEffect000.jpg" },
	{ "data/TEXTURE/effect000.jpg" },
	{ "data/TEXTURE/smokeEffect.png" },
	{ "data/TEXTURE/smokeEffect.png" },
	{ "data/TEXTURE/StateUp.jpg" },
	{ "data/TEXTURE/smokeEffect.png" },
	{ "data/TEXTURE/Water.jpg" },
	{ "data/TEXTURE/powerUP000.png" },
	{ "data/TEXTURE/LifeUP000.png" },
	{ "data/TEXTURE/speedUP000.png" },
	{ "data/TEXTURE/smokeEffect.png" },
	{ "data/TEXTURE/effect000.jpg" },
	{ "data/TEXTURE/smokeEffect.png" },
	{ "data/TEXTURE/DirtyEffect.png" },
	{ "data/TEXTURE/Sunder001.jpg" },
	{ "data/TEXTURE/star.png" },
	{ "data/TEXTURE/EffectCartoon/slice000.png" },
	{ "data/TEXTURE/EffectCartoon/fire.png" },
	{ "data/TEXTURE/EffectCartoon/wind.png" },
	{ "data/TEXTURE/EffectCartoon/don.png" },
	{"data/TEXTURE/EffectCartoon/ta.png"},
};
//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntEffectTex = 0; nCntEffectTex < EFFECTTYPE_MAX; nCntEffectTex++)
	{// �e�N�X�`���̐ݒ�
		D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
			g_aEffectTexInfo[nCntEffectTex].pFileName,		// �t�@�C���̖��O
			&g_apTextureEffect[nCntEffectTex]);				// �e�N�X�`���ւ̃|�C���^
	}
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
		g_aEffect[nCntEffect].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �O��̈ʒu
		g_aEffect[nCntEffect].Destpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړI�̈ʒu
		g_aEffect[nCntEffect].Initpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����ʒu
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_aEffect[nCntEffect].fAngle = 0;							// �p�x
		g_aEffect[nCntEffect].fLength = 0;							// ����
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
		g_aEffect[nCntEffect].fWidth = 0;							// ��
		g_aEffect[nCntEffect].fHeight = 0;							// ����
		g_aEffect[nCntEffect].fDepth = 0;							// ���s��
		g_aEffect[nCntEffect].fRadius = 0;							// ����
		g_aEffect[nCntEffect].fSinCosMove = 0;						// �h��
		g_aEffect[nCntEffect].fChangeRadius = 0;					// �g��k��
		g_aEffect[nCntEffect].nLife = 0;							// ����
		g_aEffect[nCntEffect].nType = EFFECTTYPE_SMOKE;			// ���
		g_aEffect[nCntEffect].nIdyShadow = 0;						// �e��ID
		g_aEffect[nCntEffect].nCounterAnim = 0;						// �A�j���[�V�����J�E���^�[
		g_aEffect[nCntEffect].nPatternAnim = 0;						// �A�j���[�V�����p�^�[��
		g_aEffect[nCntEffect].nRandAnim = 0;					// �J�E���^�[
		g_aEffect[nCntEffect].bUse = false;							// �g�p����Ă��邩�ǂ���
		g_aEffect[nCntEffect].nIdy = 0;								// �ԍ�
		g_aEffect[nCntEffect].fAttackPower = 0;						// �_���[�W
		g_aEffect[nCntEffect].fDamageH = 0;							// ���������_���[�W
		g_aEffect[nCntEffect].fDamageV = 0;							// ���������_���[�W
		g_aEffect[nCntEffect].pModel = NULL;
	}
	MakeVertexEffect(pDevice);
}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitEffect(void)
{
	// �e�N�X�`���̔j��
	for (int nCntEffect = 0; nCntEffect < EFFECTTYPE_MAX; nCntEffect++)
	{
		if (g_apTextureEffect[nCntEffect] != NULL)
		{
			g_apTextureEffect[nCntEffect]->Release();
			g_apTextureEffect[nCntEffect] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateEffect(void)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^
	Player *pPlayer = GetPlayer();
	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++,pVtx+=4)
	{
		if (g_aEffect[nCnt].bUse == true)
		{
			// �O��̈ʒu�̐ݒ�
			g_aEffect[nCnt].posOld = g_aEffect[nCnt].pos;
			// �ړ��ʉ��Z
			g_aEffect[nCnt].pos += g_aEffect[nCnt].move;

			switch (g_aEffect[nCnt].nType)
			{
			case EFFECTTYPE_SMOKE:			// ��
				g_aEffect[nCnt].col.a -= 0.01f;
				g_aEffect[nCnt].fRadius -= 0.1f;
				if (g_aEffect[nCnt].col.a <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				break;
			case EFFECTTYPE_IMPACT:			// �Ռ���
				g_aEffect[nCnt].fRadius += 20.0f;
				g_aEffect[nCnt].col.a -= 0.05f;
				if (g_aEffect[nCnt].col.a <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				if (g_aEffect[nCnt].pos.y <= -200)
				{
					g_aEffect[nCnt].bUse = false;
				}
				break;
			case EFFECTTYPE_HITEXPLOSION:
				g_aEffect[nCnt].fRadius--;
				if (g_aEffect[nCnt].fRadius <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				if (g_aEffect[nCnt].col.a <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				if (g_aEffect[nCnt].move.x <= 1 && g_aEffect[nCnt].move.x >= -1)
				{
					g_aEffect[nCnt].col.a -= 0.01f;
				}

				g_aEffect[nCnt].move.x *= 0.97f;
				g_aEffect[nCnt].move.z *= 0.97f;
				g_aEffect[nCnt].move.y *= 0.97f;
				break;
			case EFFECTTYPE_WATERFALL_0:
				g_aEffect[nCnt].fRadius++;
				if (g_aEffect[nCnt].col.a <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				if (g_aEffect[nCnt].move.x <= 2)
				{
					g_aEffect[nCnt].col.a -= 0.01f;
				}
				if (g_aEffect[nCnt].pos.y <= -100)
				{
					g_aEffect[nCnt].bUse = false;
				}
				g_aEffect[nCnt].move.x *= 0.97f;
				g_aEffect[nCnt].move.z *= 0.97f;
				g_aEffect[nCnt].move.y -= 0.30f;
				break;
			case EFFECTTYPE_WATERFALL_1:	// ���ނ�
				g_aEffect[nCnt].fRadius++;
				if (g_aEffect[nCnt].col.a <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				if (g_aEffect[nCnt].move.x <= 2)
				{
					g_aEffect[nCnt].col.a -= 0.01f;
				}
				g_aEffect[nCnt].move.x *= 0.97f;
				g_aEffect[nCnt].move.z *= 0.97f;
				g_aEffect[nCnt].move.y += 0.001f;
				break;
			case EFFECTTYPE_STATE_UP:
				g_aEffect[nCnt].nLife--;
				g_aEffect[nCnt].fRadius--;
				g_aEffect[nCnt].col.a -= 0.01f;
				if (g_aEffect[nCnt].col.a <= 0||g_aEffect[nCnt].nLife<= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				break;
			case EFFECTTYPE_FIRE:	// ��
				g_aEffect[nCnt].fRadius += 0.3f;
				if (g_aEffect[nCnt].col.a <= 0.0f)
				{
					g_aEffect[nCnt].bUse = false;
				}
				if ((g_aEffect[nCnt].move.x <= 1.0f&&g_aEffect[nCnt].move.x >= -1.0f) &&
					(g_aEffect[nCnt].move.z <= 1.0f&&g_aEffect[nCnt].move.z >= -1.0f))
				{
					g_aEffect[nCnt].col.a -= 0.1f;
				}
				if (rand() %50 == 0)
				{
					SetEffect(g_aEffect[nCnt].pos + D3DXVECTOR3(sinf(SetRandomEffect())*30, cosf(SetRandomEffect()) * 30, cosf(SetRandomEffect()) * 30)
						, g_aEffect[nCnt].move,
						D3DXVECTOR3(0, 0, 0),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 0, EFFECTTYPE_CARTOON_FIRE);
				}
				g_aEffect[nCnt].move.x *= 0.97f;
				g_aEffect[nCnt].move.z *= 0.97f;
				g_aEffect[nCnt].move.y += 0.0001f;
				break;
			case EFFECTTYPE_WATER:	// �����Ԃ�
				g_aEffect[nCnt].move.y -= 0.49f;
				g_aEffect[nCnt].fRadius -= 0.1f;
				g_aEffect[nCnt].col.a -= 0.01f;
				g_aEffect[nCnt].move.x *= 0.97f;
				g_aEffect[nCnt].move.z *= 0.97f;
				if (g_aEffect[nCnt].fRadius <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				if (g_aEffect[nCnt].col.a <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				if (g_aEffect[nCnt].pos.y <= -300)
				{
					g_aEffect[nCnt].bUse = false;
				}
				if (CollisionModelMinMax(&g_aEffect[nCnt].pos, &g_aEffect[nCnt].posOld, &D3DXVECTOR3(0, 0, 0),
					g_aEffect[nCnt].fRadius, g_aEffect[nCnt].fRadius, &g_aEffect[nCnt].pModel) == 2)
				{
					g_aEffect[nCnt].fRadius -= 0.5f;
					g_aEffect[nCnt].move.y *= -1;
				}
				break;
			case EFFECTTYPE_POW_UP:
				g_aEffect[nCnt].col.a -= 0.02f;
				g_aEffect[nCnt].move.y = 1.0f;
				if (g_aEffect[nCnt].col.a <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				break;
			case EFFECTTYPE_LIFE_UP:
				g_aEffect[nCnt].col.a -= 0.02f;
				g_aEffect[nCnt].move.y = 1.0f;
				if (g_aEffect[nCnt].col.a <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				break;
			case EFFECTTYPE_SPEED_UP:
				g_aEffect[nCnt].col.a -= 0.02f;
				g_aEffect[nCnt].move.y = 1.0f;
				if (g_aEffect[nCnt].col.a <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				break;
			case EFFECTTYPE_WALK:	// �y��
				if ((g_aEffect[nCnt].move.x <= 1.0f&&g_aEffect[nCnt].move.x >= -1.0f) &&
					(g_aEffect[nCnt].move.z <= 1.0f&&g_aEffect[nCnt].move.z >= -1.0f))
				{
					g_aEffect[nCnt].col.a -= 0.1f;
				}

				g_aEffect[nCnt].move.x *= 0.97f;
				g_aEffect[nCnt].move.z *= 0.97f;
				g_aEffect[nCnt].move.y += 0.0001f;
				if (g_aEffect[nCnt].col.a <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				break;
			case EFFECTTYPE_LASER:		// ���[�U�[
				g_aEffect[nCnt].col.a -= 0.01f;
				if (g_aEffect[nCnt].col.a <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				break;
			case EFFECTTYPE_BOMB:		// ����
				g_aEffect[nCnt].col.a -= 0.1f;
				g_aEffect[nCnt].fRadius -= 0.1f;
				if (g_aEffect[nCnt].col.a <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				break;
			case EFFECTTYPE_DIRTY:	// �D
				g_aEffect[nCnt].fRadius += 0.3f;
				if (g_aEffect[nCnt].col.a <= 0.0f)
				{
					g_aEffect[nCnt].bUse = false;
				}
				if ((g_aEffect[nCnt].move.x <= 1.0f&&g_aEffect[nCnt].move.x >= -1.0f) &&
					(g_aEffect[nCnt].move.z <= 1.0f&&g_aEffect[nCnt].move.z >= -1.0f))
				{
					g_aEffect[nCnt].col.a -= 0.1f;
				}

				g_aEffect[nCnt].move.x *= 0.97f;
				g_aEffect[nCnt].move.z *= 0.97f;
				g_aEffect[nCnt].move.y += 0.0001f;
				break;
			case EFFECTTYPE_SUNDER:	// ��
				g_aEffect[nCnt].col.a -= 0.1f;
				if (g_aEffect[nCnt].col.a <= 0.0f)
				{
					g_aEffect[nCnt].bUse = false;
				}
				break;
			case EFFECTTYPE_CRASH: // ����
				g_aEffect[nCnt].rot.x += 0.1f;
				g_aEffect[nCnt].rot.z += 0.1f;
				if (g_aEffect[nCnt].rot.x > D3DX_PI)
				{// ������3.14�𒴂���Ȃ�
					g_aEffect[nCnt].rot.x -= D3DX_PI * 2.0f;
				}
				if (g_aEffect[nCnt].rot.y > D3DX_PI)
				{// ������3.14�𒴂���Ȃ�
					g_aEffect[nCnt].rot.y -= D3DX_PI * 2.0f;
				}
				g_aEffect[nCnt].move.x = sinf(-D3DX_PI / 2 + g_aEffect[nCnt].rot.x)*3;
				g_aEffect[nCnt].move.z = cosf(-D3DX_PI / 2 + g_aEffect[nCnt].rot.z)*3;
				g_aEffect[nCnt].nLife--;
				if (g_aEffect[nCnt].nLife <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				break;
			default:
				g_aEffect[nCnt].col.a -= 0.1f;
				if (g_aEffect[nCnt].col.a <= 0)
				{
					g_aEffect[nCnt].bUse = false;
				}
				break;
			}
			if (g_aEffect[nCnt].pos.y <= -300)
			{
				g_aEffect[nCnt].bUse = false;
			}
			//// ���_���̐ݒ�
			//pVtx[0].pos = D3DXVECTOR3(sinf(-g_aEffect[nCnt].fAngle + g_aEffect[nCnt].rot.x)*g_aEffect[nCnt].fLength,
			//	cosf(-g_aEffect[nCnt].fAngle + g_aEffect[nCnt].rot.y)*g_aEffect[nCnt].fLength, 0.0f) + g_aEffect[nCnt].pos;
			//pVtx[1].pos = D3DXVECTOR3(sinf(g_aEffect[nCnt].fAngle + g_aEffect[nCnt].rot.x)*g_aEffect[nCnt].fLength,
			//	cosf( g_aEffect[nCnt].fAngle + g_aEffect[nCnt].rot.y)*g_aEffect[nCnt].fLength, 0.0f) + g_aEffect[nCnt].pos;
			//pVtx[2].pos = D3DXVECTOR3(D3DX_PI + sinf(-g_aEffect[nCnt].fAngle + g_aEffect[nCnt].rot.x)*g_aEffect[nCnt].fLength,
			//	cosf(D3DX_PI - g_aEffect[nCnt].fAngle + g_aEffect[nCnt].rot.y)*g_aEffect[nCnt].fLength, 0.0f) + g_aEffect[nCnt].pos;
			//pVtx[3].pos = D3DXVECTOR3(D3DX_PI + sinf(g_aEffect[nCnt].fAngle + g_aEffect[nCnt].rot.x)*g_aEffect[nCnt].fLength,
			//	cosf(D3DX_PI - g_aEffect[nCnt].fAngle + g_aEffect[nCnt].rot.y)*g_aEffect[nCnt].fLength, 0.0f) + g_aEffect[nCnt].pos;
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-(g_aEffect[nCnt].fRadius / 2), (g_aEffect[nCnt].fRadius / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3((g_aEffect[nCnt].fRadius / 2), (g_aEffect[nCnt].fRadius / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-(g_aEffect[nCnt].fRadius / 2), -(g_aEffect[nCnt].fRadius / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3((g_aEffect[nCnt].fRadius / 2), -(g_aEffect[nCnt].fRadius / 2), 0.0f);
			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aEffect[nCnt].col;
			pVtx[1].col = g_aEffect[nCnt].col;
			pVtx[2].col = g_aEffect[nCnt].col;
			pVtx[3].col = g_aEffect[nCnt].col;

			g_aEffect[nCnt].nCounterAnim++;

			if (g_aEffect[nCnt].nType == EFFECTTYPE_SMOKE|| g_aEffect[nCnt].nType == EFFECTTYPE_WATERFALL_0
				|| g_aEffect[nCnt].nType == EFFECTTYPE_WATERFALL_1|| g_aEffect[nCnt].nType==EFFECTTYPE_FIRE||
				g_aEffect[nCnt].nType == EFFECTTYPE_WALK||g_aEffect[nCnt].nType== EFFECTTYPE_BOMB||
				g_aEffect[nCnt].nType == EFFECTTYPE_DIRTY)
			{
				if (g_aEffect[nCnt].nCounterAnim % 5 == 0)
				{
					g_aEffect[nCnt].nPatternAnim = (g_aEffect[nCnt].nPatternAnim + 1) % 8;
					// �e�N�X�`���̐ݒ�
					pVtx[0].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 8) *0.125f, (g_aEffect[nCnt].nPatternAnim / 8)*0.125f*g_aEffect[nCnt].nRandAnim);
					pVtx[1].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 8)*0.125f + 0.125f, (g_aEffect[nCnt].nPatternAnim / 8)*0.125f*g_aEffect[nCnt].nRandAnim);
					pVtx[2].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 8)*0.125f, (g_aEffect[nCnt].nPatternAnim / 8)*0.125f*g_aEffect[nCnt].nRandAnim + 0.125f);
					pVtx[3].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 8)*0.125f + 0.125f, (g_aEffect[nCnt].nPatternAnim / 8)*0.125f*g_aEffect[nCnt].nRandAnim + 0.125f);
				}
			}
			else if (g_aEffect[nCnt].nType == EFFECTTYPE_SUNDER)
			{// ��
				if (g_aEffect[nCnt].nCounterAnim % 5 == 0)
				{
					g_aEffect[nCnt].nPatternAnim = (g_aEffect[nCnt].nPatternAnim + 1) % 4;

					pVtx[0].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 4) *0.25f, (g_aEffect[nCnt].nPatternAnim / 4)*1.0f);
					pVtx[1].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 4)*0.25f + 0.25f, (g_aEffect[nCnt].nPatternAnim / 4)*1.0f);
					pVtx[2].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 4)*0.25f, (g_aEffect[nCnt].nPatternAnim / 4)*1.0f + 1.0f);
					pVtx[3].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 4)*0.25f + 0.25f, (g_aEffect[nCnt].nPatternAnim / 4)*1.0f + 1.0f);
				}
			}
			else
			{
				// �e�N�X�`���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();

	SetEffect(D3DXVECTOR3(-280 - float(rand()%300), 460, 460- float(rand() % 200)), D3DXVECTOR3(sinf(SetRandomEffect())*1, cosf(SetRandomEffect() )* 1, cosf(SetRandomEffect()) * 1),
		D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		float(rand() % 100 + 100), 0, EFFECTTYPE_WATERFALL_0);
	SetEffect(D3DXVECTOR3(-280 - float(rand() % 300), 10, 460 - float(rand() % 200)), D3DXVECTOR3(sinf(SetRandomEffect()) * 1, cosf(SetRandomEffect()) * 1, cosf(SetRandomEffect()) * 1),
		D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		float(rand() % 50 + 50), 0, EFFECTTYPE_WATERFALL_1);



}

//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;							// �r���{�[�h�p�}�g���b�N�X


	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// Z�o�b�t�@�ւ̏�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// ���C�g�e���󂯂Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�\�[�X
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_aEffect[nCnt].bUse )
		{
			if (g_aEffect[nCnt].nType == EFFECTTYPE_SMOKE||g_aEffect[nCnt].nType == EFFECTTYPE_LIFE_UP||
				g_aEffect[nCnt].nType == EFFECTTYPE_POW_UP|| g_aEffect[nCnt].nType == EFFECTTYPE_SPEED_UP
				|| g_aEffect[nCnt].nType == EFFECTTYPE_DIRTY||g_aEffect[nCnt].nType >=EFFECTTYPE_CARTOON_SLICE_0)
			{
				// ���u�����f�B���O�����ɖ߂�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			}
			else
			{
				// ���u�����f�B���O�����Z�����ɐݒ�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCnt].mtxWorld);

			// �r���{�[�h�̐ݒ�
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			// �t�s��̐ݒ�
			g_aEffect[nCnt].mtxWorld._11 = mtxView._11;
			g_aEffect[nCnt].mtxWorld._12 = mtxView._21;
			g_aEffect[nCnt].mtxWorld._13 = mtxView._31;
			g_aEffect[nCnt].mtxWorld._21 = mtxView._12;
			g_aEffect[nCnt].mtxWorld._22 = mtxView._22;
			g_aEffect[nCnt].mtxWorld._23 = mtxView._32;
			g_aEffect[nCnt].mtxWorld._31 = mtxView._13;
			g_aEffect[nCnt].mtxWorld._32 = mtxView._23;
			g_aEffect[nCnt].mtxWorld._33 = mtxView._33;
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCnt].pos.x, g_aEffect[nCnt].pos.y, g_aEffect[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCnt].mtxWorld, &g_aEffect[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEffect[g_aEffect[nCnt].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

			if (g_aEffect[nCnt].nType == EFFECTTYPE_FIRE|| g_aEffect[nCnt].nType == EFFECTTYPE_WATER|| g_aEffect[nCnt].nType==EFFECTTYPE_LASER
				||g_aEffect[nCnt].nType==EFFECTTYPE_BOMB|| g_aEffect[nCnt].nType == EFFECTTYPE_SUNDER)
			{// �΂Ɛ��Ɨ��Ȃ画��
				if (g_aEffect[nCnt].col.a >= 0.3f&&g_aEffect[nCnt].fDamageV > 0.0f&&g_aEffect[nCnt].fDamageH > 0.0f)
				{// ����
					if (g_aEffect[nCnt].nIdy >= 4)
					{
						if (CollisionPlayerEffect(GetPlayer()[g_aEffect[nCnt].nIdy].pos,
							D3DXVECTOR3(g_aEffect[nCnt].mtxWorld._41, g_aEffect[nCnt].mtxWorld._42, g_aEffect[nCnt].mtxWorld._43),
							g_aEffect[nCnt].fRadius / 2, g_aEffect[nCnt].fAttackPower,
							g_aEffect[nCnt].fDamageH,
							g_aEffect[nCnt].fDamageV))
						{
						}
					}
					else
					{
						if (CollisionPlayer(GetPlayer()[g_aEffect[nCnt].nIdy].pos,
							D3DXVECTOR3(g_aEffect[nCnt].mtxWorld._41, g_aEffect[nCnt].mtxWorld._42, g_aEffect[nCnt].mtxWorld._43),
							g_aEffect[nCnt].fRadius / 2, g_aEffect[nCnt].fAttackPower,
							g_aEffect[nCnt].fDamageH,
							g_aEffect[nCnt].fDamageV, g_aEffect[nCnt].nIdy))
						{
						}
					}

				}
			}
		}

	}

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// Z�o�b�t�@�ւ̏�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	// ���C�g�e���󂯂Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


}

//==============================================================================================================================
// ���_���̍쐬
//==============================================================================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-(g_aEffect[nCntEffect].fRadius / 2), (g_aEffect[nCntEffect].fRadius / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_aEffect[nCntEffect].fRadius / 2), (g_aEffect[nCntEffect].fRadius / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-(g_aEffect[nCntEffect].fRadius / 2), -(g_aEffect[nCntEffect].fRadius / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_aEffect[nCntEffect].fRadius / 2), -(g_aEffect[nCntEffect].fRadius / 2), 0.0f);
		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_aEffect[nCntEffect].col;
		pVtx[1].col = g_aEffect[nCntEffect].col;
		pVtx[2].col = g_aEffect[nCntEffect].col;
		pVtx[3].col = g_aEffect[nCntEffect].col;
		// �e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();

}
//==============================================================================================================================
// �G�t�F�N�g�̐ݒ�
//==============================================================================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fRadius, int nLife, EFFECTTYPE nType)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++, pVtx += 4)
	{
		if (g_aEffect[nCnt].bUse == false)
		{
			g_aEffect[nCnt].pos = pos;
			g_aEffect[nCnt].Initpos = pos;
			g_aEffect[nCnt].Destpos = pos;
			g_aEffect[nCnt].move = move;
			g_aEffect[nCnt].rot = rot;
			g_aEffect[nCnt].col = col;
			g_aEffect[nCnt].fRadius = fRadius;
			g_aEffect[nCnt].nType = nType;
			g_aEffect[nCnt].nLife = nLife;
			g_aEffect[nCnt].fChangeRadius = 0;
			g_aEffect[nCnt].nPatternAnim = 0;
			g_aEffect[nCnt].nCounterAnim = 0;
			g_aEffect[nCnt].nRandAnim = rand()%8;
			g_aEffect[nCnt].fAttackPower = 0;						// �_���[�W
			g_aEffect[nCnt].fDamageH = 0;							// ���������_���[�W
			g_aEffect[nCnt].fDamageV = 0;							// ���������_���[�W

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-(g_aEffect[nCnt].fRadius / 2), (g_aEffect[nCnt].fRadius / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3((g_aEffect[nCnt].fRadius / 2), (g_aEffect[nCnt].fRadius / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-(g_aEffect[nCnt].fRadius / 2), -(g_aEffect[nCnt].fRadius / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3((g_aEffect[nCnt].fRadius / 2), -(g_aEffect[nCnt].fRadius / 2), 0.0f);
			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aEffect[nCnt].col;
			pVtx[1].col = g_aEffect[nCnt].col;
			pVtx[2].col = g_aEffect[nCnt].col;
			pVtx[3].col = g_aEffect[nCnt].col;
			if (g_aEffect[nCnt].nType == EFFECTTYPE_SMOKE || g_aEffect[nCnt].nType == EFFECTTYPE_WATERFALL_0
				|| g_aEffect[nCnt].nType == EFFECTTYPE_WATERFALL_1 || g_aEffect[nCnt].nType == EFFECTTYPE_FIRE ||
				g_aEffect[nCnt].nType == EFFECTTYPE_WALK || g_aEffect[nCnt].nType == EFFECTTYPE_BOMB||
				g_aEffect[nCnt].nType == EFFECTTYPE_DIRTY)
			{
				g_aEffect[nCnt].nPatternAnim = rand() % 8;
				// �e�N�X�`���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 8) *0.125f, (g_aEffect[nCnt].nPatternAnim / 8)*0.125f*g_aEffect[nCnt].nRandAnim);
				pVtx[1].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 8)*0.125f + 0.125f, (g_aEffect[nCnt].nPatternAnim / 8)*0.125f*g_aEffect[nCnt].nRandAnim);
				pVtx[2].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 8)*0.125f, (g_aEffect[nCnt].nPatternAnim / 8)*0.125f*g_aEffect[nCnt].nRandAnim + 0.125f);
				pVtx[3].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 8)*0.125f + 0.125f, (g_aEffect[nCnt].nPatternAnim / 8)*0.125f*g_aEffect[nCnt].nRandAnim + 0.125f);
			}
			if (g_aEffect[nCnt].nType == EFFECTTYPE_SUNDER)
			{
				g_aEffect[nCnt].nPatternAnim = rand() % 4;
				pVtx[0].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 4) *0.25f, (g_aEffect[nCnt].nPatternAnim / 4)*1.0f);
				pVtx[1].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 4)*0.25f + 0.25f, (g_aEffect[nCnt].nPatternAnim / 4)*1.0f);
				pVtx[2].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 4)*0.25f, (g_aEffect[nCnt].nPatternAnim / 4)*1.0f + 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 4)*0.25f + 0.25f, (g_aEffect[nCnt].nPatternAnim / 4)*1.0f + 1.0f);
			}
			g_aEffect[nCnt].bUse = true;
			break;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
void SetEffectDamage(int nIdy, float fAttackPower, float fDamageH, float fDamageV, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fRadius, int nLife, EFFECTTYPE nType)
{
	VERTEX_3D *pVtx;	// ���_���̃|�C���^

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++, pVtx += 4)
	{
		if (g_aEffect[nCnt].bUse == false)
		{
			g_aEffect[nCnt].pos = pos;
			g_aEffect[nCnt].Initpos = pos;
			g_aEffect[nCnt].Destpos = pos;
			g_aEffect[nCnt].move = move;
			g_aEffect[nCnt].rot = rot;
			g_aEffect[nCnt].col = col;
			g_aEffect[nCnt].fRadius = fRadius;
			g_aEffect[nCnt].nType = nType;
			g_aEffect[nCnt].nLife = nLife;
			g_aEffect[nCnt].fChangeRadius = 0;
			g_aEffect[nCnt].nPatternAnim = 0;
			g_aEffect[nCnt].nCounterAnim = 0;
			g_aEffect[nCnt].nRandAnim = rand() % 8;
			g_aEffect[nCnt].nIdy = nIdy;								// �ԍ�
			g_aEffect[nCnt].fAttackPower = fAttackPower;						// �_���[�W
			g_aEffect[nCnt].fDamageH = fDamageH;							// ���������_���[�W
			g_aEffect[nCnt].fDamageV = fDamageV;							// ���������_���[�W

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-(g_aEffect[nCnt].fRadius / 2), (g_aEffect[nCnt].fRadius / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3((g_aEffect[nCnt].fRadius / 2), (g_aEffect[nCnt].fRadius / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-(g_aEffect[nCnt].fRadius / 2), -(g_aEffect[nCnt].fRadius / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3((g_aEffect[nCnt].fRadius / 2), -(g_aEffect[nCnt].fRadius / 2), 0.0f);
			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aEffect[nCnt].col;
			pVtx[1].col = g_aEffect[nCnt].col;
			pVtx[2].col = g_aEffect[nCnt].col;
			pVtx[3].col = g_aEffect[nCnt].col;
			if (g_aEffect[nCnt].nType == EFFECTTYPE_SMOKE || g_aEffect[nCnt].nType == EFFECTTYPE_WATERFALL_0
				|| g_aEffect[nCnt].nType == EFFECTTYPE_WATERFALL_1 || g_aEffect[nCnt].nType == EFFECTTYPE_FIRE||
				g_aEffect[nCnt].nType == EFFECTTYPE_WALK|| g_aEffect[nCnt].nType == EFFECTTYPE_BOMB||
				g_aEffect[nCnt].nType == EFFECTTYPE_DIRTY)
			{
				g_aEffect[nCnt].nPatternAnim = rand() % 8;
				// �e�N�X�`���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 8) *0.125f, (g_aEffect[nCnt].nPatternAnim / 8)*0.125f*g_aEffect[nCnt].nRandAnim);
				pVtx[1].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 8)*0.125f + 0.125f, (g_aEffect[nCnt].nPatternAnim / 8)*0.125f*g_aEffect[nCnt].nRandAnim);
				pVtx[2].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 8)*0.125f, (g_aEffect[nCnt].nPatternAnim / 8)*0.125f*g_aEffect[nCnt].nRandAnim + 0.125f);
				pVtx[3].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 8)*0.125f + 0.125f, (g_aEffect[nCnt].nPatternAnim / 8)*0.125f*g_aEffect[nCnt].nRandAnim + 0.125f);
			}
			if (g_aEffect[nCnt].nType == EFFECTTYPE_SUNDER )
			{
				g_aEffect[nCnt].nPatternAnim = rand() % 4;
				pVtx[0].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 4) *0.25f, (g_aEffect[nCnt].nPatternAnim / 4)*1.0f);
				pVtx[1].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 4)*0.25f + 0.25f, (g_aEffect[nCnt].nPatternAnim / 4)*1.0f);
				pVtx[2].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 4)*0.25f, (g_aEffect[nCnt].nPatternAnim / 4)*1.0f + 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_aEffect[nCnt].nPatternAnim % 4)*0.25f + 0.25f, (g_aEffect[nCnt].nPatternAnim / 4)*1.0f + 1.0f);
			}
			g_aEffect[nCnt].bUse = true;
			break;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();

}
//==============================================================================================================================
// �����_�������̎擾
//==============================================================================================================================
float SetRandomEffect(void)
{
	float nDirection = 0;
	int nData;

	// �G�t�F�N�g�̕���
	nData = rand() % 2;
	if (nData == 0)
	{// �E��
		nDirection = float(rand() % 314);
	}
	else if (nData == 1)
	{// ����
		nDirection = float(rand() % 314) * -1;
	}
	nDirection /= 100;	// �����_��߂�

	return nDirection;
}
//==============================================================================================================================
// �G�t�F�N�g�̎擾
//==============================================================================================================================
Effect *GetEffect(void)
{
	return &g_aEffect[0];
}
//==============================================================================================================================
// �q�b�g
//==============================================================================================================================
void HitEffect(D3DXVECTOR3 pos)
{
	for (int nCntEffect = 0; nCntEffect < 5; nCntEffect++)
	{// �Ή�
		float nDirection = SetRandomEffect();
		float nDirectio2 = SetRandomEffect();
		float nDirectio3 = SetRandomEffect();
		SetEffect(pos,
			D3DXVECTOR3(sinf(nDirection) * (float(rand() % 50 / 10.0f) + 3), cosf(nDirectio2) * (float(rand() % 50 / 10.0f) + 3), cosf(nDirectio3) * (float(rand() % 30 / 10.0f) + 3)), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, float(rand() % 100 / 100.0f), 0.0f, 0.8f), float(rand() % 20) + 10, 30, EFFECTTYPE_HITEXPLOSION);
		SetEffect(pos,
			D3DXVECTOR3(sinf(nDirectio2) *(float(rand() % 50 / 10.0f) + 3), cosf(nDirectio3) * (float(rand() % 30 / 10.0f) + 3), cosf(nDirection) * (float(rand() % 50 / 10.0f) + 3)), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.8f, float(rand() % 100 / 100.0f), 0.0f, 0.8f), float(rand() % 30) + 10, 30, EFFECTTYPE_HITEXPLOSION);
	}
	for (int nCntEffect = 0; nCntEffect < 1; nCntEffect++)
	{// �Ռ���
		SetEffect(pos,
			D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.8f, 0.5f, 0.0f, 0.8f), 10, 30, EFFECTTYPE_IMPACT);
	}
}
