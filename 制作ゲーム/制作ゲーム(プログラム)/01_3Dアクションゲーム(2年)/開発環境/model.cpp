////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���f������ [model.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "model.h"
#include "input.h"
#include "camera.h"
#include "line.h"
#include "player.h"
#include "fade.h"
#include "game.h"
#include "light.h"
#include "player.h"
#include "shadow.h"
#include "event.h"
#include "effect.h"
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define MAX_SPEED	(1.0f)	// �ړ���
#define DOWN_SPEED	(0.15f)	// ������
#define MAX_HEIGHT	(100)	// ��̏��
#define MIN_HEIGHT	(-50)	// ���̏��
#define EXPLOSION_COUNTER (120)	// �����J�E���^�[
//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
Model g_aModel[MAX_MODEL];
ModelData g_aModelData[MAX_MODEL_TYPE];

//==============================================================================================================================
// ����������
//==============================================================================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ʒu�E�����̏����ݒ�
	for (int nCntMat = 0; nCntMat < MAX_MODEL; nCntMat++)
	{
		g_aModel[nCntMat].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[nCntMat].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[nCntMat].Initpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[nCntMat].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aModel[nCntMat].nType = MODELTYPE_KINGYO;
		g_aModel[nCntMat].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[nCntMat].Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[nCntMat].Destrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[nCntMat].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[nCntMat].bCollision = true;
		g_aModel[nCntMat].bHit = false;
		g_aModel[nCntMat].nIdy = 0;
		g_aModel[nCntMat].bCatch = false;
		g_aModel[nCntMat].nCounter = 0;
		g_aModel[nCntMat].bFlag = false;
		g_aModel[nCntMat].fCounter = 0.0f;
		for (int nCntCollision = 0; nCntCollision < MAX_MODEL_COLLISION; nCntCollision++)
		{
			g_aModel[nCntMat].nIdyLine[nCntCollision] = 0;
		}
		g_aModel[nCntMat].bUse = false;
	}
	DeleteLine(LINETYPE_MODEL);
}

//==============================================================================================================================
// �I������
//==============================================================================================================================
void UninitModel(void)
{
	for (int nCntMat = 0; nCntMat < g_aModelData[0].nNumModel; nCntMat++)
	{
		// ���b�V���̊J��
		if (g_aModelData[nCntMat].pMesh != NULL)
		{
			g_aModelData[nCntMat].pMesh->Release();
			g_aModelData[nCntMat].pMesh = NULL;
		}
		// �}�e���A���̊J��
		if (g_aModelData[nCntMat].pBuffMat != NULL)
		{
			g_aModelData[nCntMat].pBuffMat->Release();
			g_aModelData[nCntMat].pBuffMat = NULL;
		}
		// �e�N�X�`���̊J��
		for (int nCntMatTex = 0; nCntMatTex < int(g_aModelData[nCntMat].nNumMat); nCntMatTex++)
		{
				if (g_aModelData[nCntMat].pTextuer[nCntMatTex] != NULL)
				{
					g_aModelData[nCntMat].pTextuer[nCntMatTex]->Release();
					delete g_aModelData[nCntMat].pTextuer[nCntMatTex];
					g_aModelData[nCntMat].pTextuer[nCntMatTex] = NULL;
				}
		}
	}
	for (int nCntMat = 0; nCntMat < MAX_MODEL; nCntMat++)
	{
		// �}�e���A���̊J��
		if (g_aModel[nCntMat].pBuffMat != NULL)
		{
			g_aModel[nCntMat].pBuffMat->Release();
			g_aModel[nCntMat].pBuffMat = NULL;
		}
	}
}
//==============================================================================================================================
// �X�V����
//==============================================================================================================================
void UpdateModel(void)
{
	Player *pPlayer = GetPlayer();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{
			g_aModel[nCntModel].pos += g_aModel[nCntModel].move;

			if (g_aModel[nCntModel].nType == MODELTYPE_POLE)
			{// ����������
				for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
				{// �������ɂ���
					if (g_aModel[nCntModel].pos.z <= pPlayer[nCntPlayer].pos.z&&
						g_aModel[nCntModel].pos.x -50<= pPlayer[nCntPlayer].pos.x + pPlayer[nCntPlayer].fRadiusWidth&&
						g_aModel[nCntModel].pos.x +50>= pPlayer[nCntPlayer].pos.x - pPlayer[nCntPlayer].fRadiusWidth)
					{
						g_aModel[nCntModel].col.a = 0.3f;
						break;
					}
					else
					{
						g_aModel[nCntModel].col.a = 1.0f;
					}
				}
			}

			if ((g_aModel[nCntModel].move.x > 0.0f || g_aModel[nCntModel].move.x < 0.0f ||
				g_aModel[nCntModel].move.z > 0.0f || g_aModel[nCntModel].move.z < 0.0f||
				g_aModel[nCntModel].move.y > 0.0f || g_aModel[nCntModel].move.y < 0.0f)&&!g_aModel[nCntModel].bHit)
			{
				for (int nCntCollision = 0; nCntCollision < MAX_MODEL_COLLISION; nCntCollision++)
				{
					if (g_aModelData[g_aModel[nCntModel].nType].bCollison[nCntCollision] == true)
					{
						if (g_aModel[nCntModel].nIdy >= 4)
						{
							if (CollisionPlayerEffect(g_aModel[nCntModel].pos,
								D3DXVECTOR3(g_aModel[nCntModel].mtxWorld._41, g_aModel[nCntModel].mtxWorld._42, g_aModel[nCntModel].mtxWorld._43),
								g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] + g_aModelData[g_aModel[nCntModel].nType].fWidthCollision[nCntCollision],
								15.0f,
								6.0f,
								10.5f))
							{
							}
						}
						else
						{
							if (CollisionPlayer(D3DXVECTOR3(g_aModel[nCntModel].mtxWorld._41, g_aModel[nCntModel].mtxWorld._42, g_aModel[nCntModel].mtxWorld._43),
								D3DXVECTOR3(g_aModel[nCntModel].mtxWorld._41, g_aModel[nCntModel].mtxWorld._42, g_aModel[nCntModel].mtxWorld._43),
								g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] + g_aModelData[g_aModel[nCntModel].nType].fWidthCollision[nCntCollision],
								5.0f,
								2.0f,
								3.0f, g_aModel[nCntModel].nIdy))
							{
								g_aModel[nCntModel].bHit = true;
								g_aModel[nCntModel].move *= -1;
								g_aModel[nCntModel].move.y = 5;
								if (g_aModel[nCntModel].nType == MODELTYPE_FISH)
								{
									g_aModel[nCntModel].move = D3DXVECTOR3(g_aModel[nCntModel].move.x * 2, 7, g_aModel[nCntModel].move.z * 2);
								}
								break;
							}
						}
					}
				}
			}
			if (g_aModel[nCntModel].bHit)
			{
				g_aModel[nCntModel].rot += D3DXVECTOR3(0.1f,0.1f,0.1f);
				g_aModel[nCntModel].move.x += (0 - g_aModel[nCntModel].move.x)*0.1f;
				g_aModel[nCntModel].move.z += (0 - g_aModel[nCntModel].move.z)*0.1f;
				g_aModel[nCntModel].move.y -= 0.4f;
				if (g_aModel[nCntModel].nType == MODELTYPE_FISH)
				{
					g_aModel[nCntModel].move.y += 0.2f;
					SetEffectDamage(4, 0.0f,
						3.0f
						, 1.0f,
						g_aModel[nCntModel].pos,
						D3DXVECTOR3(sinf(g_aModel[nCntModel].rot.x) * 5.0f, cosf(g_aModel[nCntModel].rot.y) * 5.0f, cosf(g_aModel[nCntModel].rot.z) * 5.0f),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						float(rand() % 50 + 10), 0, EFFECTTYPE_WATER);

				}
			}

			if (g_aModelData[g_aModel[nCntModel].nType].bCatch)
			{// �������z�Ȃ�
				Shadow *pShadow = GetShadow();
				pShadow[g_aModel[nCntModel].nIdyShadow].pos.y = 1.0f;

				pShadow[g_aModel[nCntModel].nIdyShadow].pos.x = g_aModel[nCntModel].pos.x;
				pShadow[g_aModel[nCntModel].nIdyShadow].pos.z = g_aModel[nCntModel].pos.z;
				if (g_aModel[nCntModel].pos.y <= -100|| g_aModel[nCntModel].pos.x >= 1500|| g_aModel[nCntModel].pos.x <= -1500||
					g_aModel[nCntModel].pos.z >= 1500 || g_aModel[nCntModel].pos.z <= -500)
				{
					g_aModel[nCntModel].bUse = false;
					DeleteShadow(g_aModel[nCntModel].nIdyShadow);
				}
			}
			if (g_aModel[nCntModel].nType == MODELTYPE_METEO)
			{// 覐΂Ȃ�
				SetEffect(g_aModel[nCntModel].pos,
					D3DXVECTOR3(sinf(SetRandomEffect()) * (rand() % 5),
						cosf(SetRandomEffect()) * (rand() % 5), cosf(SetRandomEffect()) * (rand() % 5)),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, float(rand() % 100) / 100.0f, 0.0f, 1.0f),
					float(rand() % 200) + 10, 0, EFFECTTYPE_FIRE);
					SetEffect(g_aModel[nCntModel].pos,
						D3DXVECTOR3(sinf(SetRandomEffect()) * (rand() % 3),
							cosf(SetRandomEffect()) * (rand() % 5), cosf(SetRandomEffect()) * (rand() % 3)),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.1f,0.1f,0.1f,1.0f),
						float(rand() % 50) + 10, 0, EFFECTTYPE_DIRTY);

				if (g_aModel[nCntModel].pos.y <= -5&&g_aModel[nCntModel].pos.x <= 600&& g_aModel[nCntModel].pos.x >= -600)
				{// �~�܂�
					g_aModel[nCntModel].move.y = 0;
					g_aModel[nCntModel].move.x = 0;
					g_aModel[nCntModel].bFlag = true;
				}
				if (g_aModel[nCntModel].bFlag)
				{
					g_aModel[nCntModel].nCounter++;
					if (g_aModel[nCntModel].nCounter >= EXPLOSION_COUNTER)
					{
						PlaySound(SOUND_EXPLOSION);
						for (int nCnta = 0; nCnta < 2; nCnta++)
						{
							for (int nCntEffect = 0; nCntEffect < 1; nCntEffect++)
							{// �Ռ���
								SetEffect(g_aModel[nCntModel].pos,
									D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXCOLOR(0.8f, 0.5f, 0.0f, 1.5f), float(rand() % 100), 30, EFFECTTYPE_IMPACT);
							}
							for (int nCnt = 0; nCnt < 50; nCnt++)
							{// ����
								SetEffectDamage(4, 20.0f
									, 6.0f
									, 10.0f,
									g_aModel[nCntModel].pos
									+ D3DXVECTOR3(sinf(SetRandomEffect()) *(rand() % 100), cosf(SetRandomEffect()) *(rand() % 100), cosf(SetRandomEffect()) *(rand() % 100)),
									D3DXVECTOR3(sinf(SetRandomEffect()) *(rand() % 3), cosf(SetRandomEffect()) *(rand() % 3), cosf(SetRandomEffect()) *(rand() % 3)),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, float(rand() % 100) / 100.0f, 0.0f, 1.0f),
									float(rand() % 170) + 50.0f, 0, EFFECTTYPE_BOMB);
							}
						}
						g_aModel[nCntModel].bUse = false;
						DeleteShadow(g_aModel[nCntModel].nIdyShadow);
					}
				}
			}
			// ���C���ړ�
			if (g_aModel[nCntModel].bCollision == true)
			{
				for (int nCntCollision = 0; nCntCollision < MAX_MODEL_COLLISION; nCntCollision++)
				{
					if (g_aModelData[g_aModel[nCntModel].nType].bCollison[nCntCollision] == true)
					{
						SetPositionLine(g_aModel[nCntModel].nIdyLine[nCntCollision],
							g_aModel[nCntModel].pos + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision], g_aModel[nCntModel].rot);
					}
				}
			}
		}
	}
}
//==============================================================================================================================
// ���f���̂����蔻��
//==============================================================================================================================
int CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 rot, float fRadius)
{
	int nCollision = 0;
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{
			for (int nCntCollision = 0; nCntCollision < MAX_MODEL_COLLISION; nCntCollision++)
			{
				if (g_aModelData[g_aModel[nCntModel].nType].bCollison[nCntCollision] == true)
				{
					// �G�Ɠ�������̂̋���
					float fPosX = (g_aModel[nCntModel].mtxWorld._41 + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].x - pPos->x);
					float fPosY = (g_aModel[nCntModel].mtxWorld._42 + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].y- pPos->y);
					float fPosZ = (g_aModel[nCntModel].mtxWorld._43 + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].z- pPos->z);
					float fRadiusA = fPosX*fPosX + fPosY*fPosY + fPosZ*fPosZ;
					float fRadiusB = 0;
					fRadiusB = (g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] + fRadius)* (g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] + fRadius);

					if (fRadiusB > fRadiusA&&
						-fRadiusB < fRadiusA)
					{
						float fAngle2 = atan2f(pPos->x - (g_aModel[nCntModel].mtxWorld._41 + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].x) , pPos->z - (g_aModel[nCntModel].mtxWorld._43 + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].z ));
						pPos->x = g_aModel[nCntModel].mtxWorld._41 + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].x + sinf(fAngle2)* (g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] + fRadius/2);
						pPos->z = g_aModel[nCntModel].mtxWorld._43 + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].z + cosf(fAngle2)* (g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] + fRadius/2);
						pMove->x = 0;
						pMove->z = 0;
						nCollision = 1;
						break;

					}
				}
			}
		}
	}
	return nCollision;
}

//==============================================================================================================================
// ���f���̂����蔻��
//==============================================================================================================================
int CollisionModelGetInfo(D3DXVECTOR3 *pPos, float fRadiusWidth, float fRadiusHeight, Model **pModel)
{
	int nCollision = 0;
	*pModel = NULL;
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true && g_aModel[nCntModel].bCollision == true&&g_aModelData[g_aModel[nCntModel].nType].bGetInfo)
		{
			for (int nCntCollision = 0; nCntCollision < MAX_MODEL_COLLISION; nCntCollision++)
			{
				if (g_aModelData[g_aModel[nCntModel].nType].bCollison[nCntCollision] == true)
				{
					if (g_aModel[nCntModel].pos.y + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].y <= pPos->y + fRadiusHeight&&
						g_aModel[nCntModel].pos.y + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].y + g_aModelData[g_aModel[nCntModel].nType].fHeightCollision[nCntCollision] >= pPos->y- fRadiusHeight)
					{// Y���͈͓�
						if (g_aModel[nCntModel].pos.x + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].x - g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] - g_aModelData[g_aModel[nCntModel].nType].fWidthCollision[nCntCollision] / 2 < pPos->x + fRadiusWidth&&	// ��
							g_aModel[nCntModel].pos.x + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].x + g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] + g_aModelData[g_aModel[nCntModel].nType].fWidthCollision[nCntCollision] / 2 > pPos->x - fRadiusWidth)		// �E
						{// X���͈͓�
							if (g_aModel[nCntModel].pos.z + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].z - g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] - g_aModelData[g_aModel[nCntModel].nType].fDepthCollision[nCntCollision] / 2 <= pPos->z + fRadiusWidth&&	// ��O
								g_aModel[nCntModel].pos.z + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].z + g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] + g_aModelData[g_aModel[nCntModel].nType].fDepthCollision[nCntCollision] / 2 >= pPos->z - fRadiusWidth)		// ��
							{// Z���͈͓�
								*pModel = &g_aModel[nCntModel];
								nCollision = 1;
							}
						}
					}
				}

			}
		}
	}
	return nCollision;
}
//==============================================================================================================================
// ���f���̂����蔻��
//==============================================================================================================================
int CollisionModelMinMax(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fRadiusWidth, float fRadiusHeight, Model **pModel)
{
	int nCollision = 0;
	*pModel = NULL;
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true && g_aModel[nCntModel].bCollision == true)
		{
			for (int nCntCollision = 0; nCntCollision < MAX_MODEL_COLLISION; nCntCollision++)
			{
				if (g_aModelData[g_aModel[nCntModel].nType].bCollison[nCntCollision] == true)
				{
					if (g_aModel[nCntModel].pos.y + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].y <= pPos->y + fRadiusHeight&&
						g_aModel[nCntModel].pos.y + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].y + g_aModelData[g_aModel[nCntModel].nType].fHeightCollision[nCntCollision] >= pPos->y +5)
					{// Y���͈͓�
						if (g_aModel[nCntModel].pos.x + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].x - g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] -g_aModelData[g_aModel[nCntModel].nType].fWidthCollision[nCntCollision] / 2 < pPos->x + fRadiusWidth&&	// ��
							g_aModel[nCntModel].pos.x + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].x + g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] +g_aModelData[g_aModel[nCntModel].nType].fWidthCollision[nCntCollision] / 2 > pPos->x - fRadiusWidth)		// �E
						{// X���͈͓�
							if (g_aModel[nCntModel].pos.z + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].z - g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision]-g_aModelData[g_aModel[nCntModel].nType].fDepthCollision[nCntCollision]/2 < pPos->z + fRadiusWidth&&
								g_aModel[nCntModel].pos.z + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].z - g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] - g_aModelData[g_aModel[nCntModel].nType].fDepthCollision[nCntCollision]/2 >= pPosOld->z + fRadiusWidth)
							{// �O
								pPos->z = g_aModel[nCntModel].pos.z + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].z - g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] - g_aModelData[g_aModel[nCntModel].nType].fDepthCollision[nCntCollision]/2 - fRadiusWidth;
								nCollision = 1; // ��������
								pMove->z = 0;
								*pModel = &g_aModel[nCntModel];
								break;
							}
							if (g_aModel[nCntModel].pos.z + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].z + g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision]+ g_aModelData[g_aModel[nCntModel].nType].fDepthCollision[nCntCollision]/2 > pPos->z - fRadiusWidth&&
								g_aModel[nCntModel].pos.z + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].z + g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision]+ g_aModelData[g_aModel[nCntModel].nType].fDepthCollision[nCntCollision]/2 <= pPosOld->z - fRadiusWidth)
							{// ��
								pPos->z = g_aModel[nCntModel].pos.z + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].z + g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] + g_aModelData[g_aModel[nCntModel].nType].fDepthCollision[nCntCollision]/2 + fRadiusWidth;
								nCollision = 1; // ��������
								pMove->z = 0;
								*pModel = &g_aModel[nCntModel];
								break;
							}
						}
						if (g_aModel[nCntModel].pos.z + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].z - g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision]- g_aModelData[g_aModel[nCntModel].nType].fDepthCollision[nCntCollision]/2 <= pPos->z + fRadiusWidth&&	// ��O
							g_aModel[nCntModel].pos.z + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].z + g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision]+ g_aModelData[g_aModel[nCntModel].nType].fDepthCollision[nCntCollision]/2 >= pPos->z - fRadiusWidth)		// ��
						{// Z���͈͓�
							if (g_aModel[nCntModel].pos.x + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].x - g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] - g_aModelData[g_aModel[nCntModel].nType].fWidthCollision[nCntCollision] / 2 < pPos->x + fRadiusWidth&&
								g_aModel[nCntModel].pos.x + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].x - g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] - g_aModelData[g_aModel[nCntModel].nType].fWidthCollision[nCntCollision] / 2 >= pPosOld->x + fRadiusWidth)
							{// ��
								pPos->x = g_aModel[nCntModel].pos.x + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].x - g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] - g_aModelData[g_aModel[nCntModel].nType].fWidthCollision[nCntCollision] / 2 - fRadiusWidth;
								nCollision = 1; // ��������
								*pModel = &g_aModel[nCntModel];
								break;
							}
							if (g_aModel[nCntModel].pos.x + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].x + g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] + g_aModelData[g_aModel[nCntModel].nType].fWidthCollision[nCntCollision] / 2> pPos->x - fRadiusWidth&&
								g_aModel[nCntModel].pos.x + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].x + g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] + g_aModelData[g_aModel[nCntModel].nType].fWidthCollision[nCntCollision] / 2 <= pPosOld->x - fRadiusWidth)
							{// �E
								pPos->x = g_aModel[nCntModel].pos.x + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].x + g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] + g_aModelData[g_aModel[nCntModel].nType].fWidthCollision[nCntCollision] / 2 + fRadiusWidth;
								nCollision = 1; // ��������
								*pModel = &g_aModel[nCntModel];
								break;
							}
						}
					}
					if (g_aModel[nCntModel].pos.x + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].x - g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] - g_aModelData[g_aModel[nCntModel].nType].fWidthCollision[nCntCollision] / 2 <= pPos->x + fRadiusWidth&&	// ��
						g_aModel[nCntModel].pos.x + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].x + g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] + g_aModelData[g_aModel[nCntModel].nType].fWidthCollision[nCntCollision] / 2 >= pPos->x - fRadiusWidth&&		// �E
						g_aModel[nCntModel].pos.z + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].z - g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision]- g_aModelData[g_aModel[nCntModel].nType].fDepthCollision[nCntCollision]/2 <= pPos->z + fRadiusWidth&&	// ��O
						g_aModel[nCntModel].pos.z + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].z + g_aModelData[g_aModel[nCntModel].nType].fRadiusCollision[nCntCollision] + g_aModelData[g_aModel[nCntModel].nType].fDepthCollision[nCntCollision]/2 >= pPos->z - fRadiusWidth)		// ��
					{// X Z ���͈͓�
						if (g_aModel[nCntModel].pos.y + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].y < pPos->y + fRadiusHeight&&
							g_aModel[nCntModel].pos.y + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].y  >= pPosOld->y + fRadiusHeight)
						{// ��
							pPos->y = g_aModel[nCntModel].pos.y + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].y- fRadiusHeight;
							pMove->y = 0;
							//bCollision = true; // ��������
							*pModel = &g_aModel[nCntModel];
							break;
						}
						if (g_aModel[nCntModel].pos.y + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].y + g_aModelData[g_aModel[nCntModel].nType].fHeightCollision[nCntCollision] > pPos->y &&
							g_aModel[nCntModel].pos.y + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].y + g_aModelData[g_aModel[nCntModel].nType].fHeightCollision[nCntCollision] <= pPosOld->y)
						{// ��
							pPos->y = g_aModel[nCntModel].pos.y + g_aModelData[g_aModel[nCntModel].nType].CollisionPos[nCntCollision].y + g_aModelData[g_aModel[nCntModel].nType].fHeightCollision[nCntCollision];
							pMove->y = 0;
							nCollision = 2; // ��������
							*pModel = &g_aModel[nCntModel];
							break;
						}
					}
				}
			}
		}
	}
	return nCollision;
}

//==============================================================================================================================
// �`�揈��
//==============================================================================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;		// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;				// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;					// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXCOLOR col = GetEventColor();
	Shader shader = GetShader();
	// �e�N�j�b�N�̐ݒ�
	shader.pShader->SetTechnique("StandardShader");
	// �V�F�[�_�J�n
	shader.pShader->Begin(0, 0);

	// ���e�X�g��ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);					// ���l��0
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ���傫��

	for (int nCntMat = 0; nCntMat < MAX_MODEL; nCntMat++)
	{
		if (g_aModel[nCntMat].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aModel[nCntMat].mtxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCntMat].rot.y, g_aModel[nCntMat].rot.x, g_aModel[nCntMat].rot.z);
			D3DXMatrixMultiply(&g_aModel[nCntMat].mtxWorld, &g_aModel[nCntMat].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntMat].pos.x, g_aModel[nCntMat].pos.y, g_aModel[nCntMat].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCntMat].mtxWorld, &g_aModel[nCntMat].mtxWorld, &mtxTrans);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntMat].mtxWorld);
			// �r���[�}�g���b�N�X��ݒ�
			D3DXMATRIX matrix = g_aModel[nCntMat].mtxWorld * GetCamera()->mtxView * GetCamera()->mtxProjection;
			shader.pShader->SetMatrix("g_fMatrix", &matrix);
			// �F�̐ݒ�
			D3DXCOLOR Allcol = D3DXCOLOR( g_aModel[nCntMat].col.r * col.r, g_aModel[nCntMat].col.g * col.g, g_aModel[nCntMat].col.b * col.b, g_aModel[nCntMat].col.a * col.a);
			shader.pShader->SetVector("g_fColor", &D3DXVECTOR4(Allcol.r, Allcol.g, Allcol.b, Allcol.a)); // �F�ݒ�
			//shader.pShader->SetVector("g_fLightDir", &D3DXVECTOR4(-0.89f + sinf(GetCamera()->rot.y) , +0.1f-cosf(GetCamera()->rot.y), 0.94f + cosf(GetCamera()->rot.y), 0)); // <-�ЂƂ܂�[0]�Ԗڂ̃��C�g�̕����R�s�y���܂���

			// �p�X�̕`��J�n
			shader.pShader->BeginPass(0);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aModel[nCntMat].pBuffMat->GetBufferPointer();

			for (int nCntMat2 = 0; nCntMat2 < (int)g_aModelData[g_aModel[nCntMat].nType].nNumMat; nCntMat2++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat2].MatD3D);
				if (g_aModel[nCntMat].nType == MODELTYPE_TREE)
				{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_aModelData[g_aModel[nCntMat].nType].pTextuer[nCntMat2]);
				}
				else
				{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_aModelData[g_aModel[nCntMat].nType].pTextuer[nCntMat2] );

				}
				// �����v�e�N�X�`���̐ݒ�(1�ԂɃ����v�e�N�X�`����ݒ�)
				pDevice->SetTexture(1, shader.pTexture);

				// ���f��(�p�[�c)�̕`��
				g_aModelData[g_aModel[nCntMat].nType].pMesh->DrawSubset(nCntMat2);
				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
			// �p�X�̕`��I��
			shader.pShader->EndPass();

		}
	}
	// ���e�X�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// ���e�X�g�𖳌���
	// �V�F�[�_�I��
	shader.pShader->End();

}

//==============================================================================================================================
// ���f���̐ݒ�
//==============================================================================================================================
int SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE nType)
{
	int nCntMat;
	for (nCntMat = 0; nCntMat < MAX_MODEL; nCntMat++)
	{
		if (g_aModel[nCntMat].bUse == false)
		{
			g_aModel[nCntMat].pos = pos;
			g_aModel[nCntMat].Initpos = pos;
			g_aModel[nCntMat].rot = rot;
			g_aModel[nCntMat].nType = nType;
			g_aModel[nCntMat].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aModel[nCntMat].bHit = false;
			g_aModel[nCntMat].bCatch = false;
			g_aModel[nCntMat].pBuffMat = g_aModelData[g_aModel[nCntMat].nType].pBuffMat;
			g_aModel[nCntMat].nCounter = 0;
			g_aModel[nCntMat].bFlag = false;
			g_aModel[nCntMat].fCounter = 0.0f;

			if (g_aModelData[g_aModel[nCntMat].nType].bCatch)
			{// �������z�Ȃ�
				g_aModel[nCntMat].nIdyShadow = SetShadow(g_aModel[nCntMat].pos+ D3DXVECTOR3(0,5.0f,0.0f), D3DXVECTOR3(0, 0, 0),
					g_aModelData[g_aModel[nCntMat].nType].fRadiusCollision[0]+ g_aModelData[g_aModel[nCntMat].nType].fWidthCollision[0], g_aModelData[g_aModel[nCntMat].nType].fRadiusCollision[0]+ g_aModelData[g_aModel[nCntMat].nType].fDepthCollision[0]);
			}
			if (g_aModel[nCntMat].bCollision == true)
			{
				for (int nCntCollision = 0; nCntCollision < MAX_MODEL_COLLISION; nCntCollision++)
				{
					if (g_aModelData[g_aModel[nCntMat].nType].bCollison[nCntCollision] == true)
					{
						g_aModel[nCntMat].nIdyLine[nCntCollision] = CollisionLine(g_aModel[nCntMat].pos + g_aModelData[g_aModel[nCntMat].nType].CollisionPos[nCntCollision],
							D3DXVECTOR3(-g_aModelData[g_aModel[nCntMat].nType].fRadiusCollision[nCntCollision] - g_aModelData[g_aModel[nCntMat].nType].fWidthCollision[nCntCollision]/2, 0.0f, -g_aModelData[g_aModel[nCntMat].nType].fRadiusCollision[nCntCollision]- g_aModelData[g_aModel[nCntMat].nType].fDepthCollision[nCntCollision]/2),
							D3DXVECTOR3(g_aModelData[g_aModel[nCntMat].nType].fRadiusCollision[nCntCollision] + g_aModelData[g_aModel[nCntMat].nType].fWidthCollision[nCntCollision]/2, g_aModelData[g_aModel[nCntMat].nType].fHeightCollision[nCntCollision], g_aModelData[g_aModel[nCntMat].nType].fRadiusCollision[nCntCollision]+ g_aModelData[g_aModel[nCntMat].nType].fDepthCollision[nCntCollision]/2),LINETYPE_MODEL);

					}
				}
			}

			g_aModel[nCntMat].bUse = true;
			break;
		}
	}
	return nCntMat;
}
//==============================================================================================================================
// �����蔻��̐���
//==============================================================================================================================
void SetCollisionModel(D3DXVECTOR3 pos, float fRadiusCollision, float fWidthCollision, float fDepthCollision,float fHeightCollision, MODELTYPE nType)
{
	for (int nCntCollision = 0; nCntCollision < MAX_MODEL_COLLISION; nCntCollision++)
	{
		if (g_aModelData[nType].bCollison[nCntCollision] == false)
		{
			g_aModelData[nType].CollisionPos[nCntCollision] = pos;
			g_aModelData[nType].fRadiusCollision[nCntCollision] = fRadiusCollision;
			g_aModelData[nType].fWidthCollision[nCntCollision] = fWidthCollision;
			g_aModelData[nType].fDepthCollision[nCntCollision] = fDepthCollision;
			g_aModelData[nType].fHeightCollision[nCntCollision] = fHeightCollision;
			g_aModelData[nType].bCollison[nCntCollision] = true;
			break;
		}
	}

}
//==============================================================================================================================
// ���f���̎擾
//==============================================================================================================================
Model *GetModel(void)
{
	return &g_aModel[0];
}
ModelData *GetModelData(void)
{
	return &g_aModelData[0];
}
