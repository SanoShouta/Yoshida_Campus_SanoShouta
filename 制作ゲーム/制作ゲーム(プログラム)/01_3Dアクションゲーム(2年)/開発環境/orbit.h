////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �O���̏��� [orbit.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ORBIT_H_
#define _ORBIT_H_

#include "main.h"
#include "player.h"
//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define MAX_ORBIT	(1000)
#define MAX_ORBIT_LENGTH	(100)
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef enum
{
	ORBITTYPE_0 = 0,
	ORBITTYPE_1,
	ORBITTYPE_2,
	ORBITTYPE_PLAYER,
	ORBITTYPE_MAX,
}ORBITTYPE;
typedef enum
{
	ORBIT_PLAYER = 0,
	ORBIT_MAX,
}ORBIT_PLAYER_ENEMY;
typedef struct
{
	D3DXMATRIX mtxWorld;// ���[���h�}�g���b�N�X
	D3DXMATRIX mtxStart;// ���[���h�}�g���b�N�X
	D3DXMATRIX mtxEnd;	// ���[���h�}�g���b�N�X
	D3DXMATRIX mtxStartOld;// ���[���h�}�g���b�N�X
	D3DXMATRIX mtxEndOld;	// ���[���h�}�g���b�N�X
	D3DXMATRIX playerWorld;// �v���C���[
	D3DXMATRIX playerWorldOld;// �v���C���[
	ORBITTYPE nType;	// ���
	D3DXCOLOR col;		// �F
	D3DXVECTOR3 Start;	// �n�_
	D3DXVECTOR3 End;	// ����
	D3DXVECTOR3 InitStart;	// �n�_
	D3DXVECTOR3 InitEnd;	// ����
	PlayerMotionType nMotionType;
	int nLength;		// ����
	int nCntTrueTime;	// �\������
	bool bUse;			// �g�p����Ă��邩�ǂ���
}Orbit;

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void InitOrbit(void);
void UninitOrbit(void);
void UpdateOrbit(void);
void DrawOrbit(void);
void SetOrbit(D3DXMATRIX nIdxmtx, D3DXMATRIX nIdxmtxOld, int nLength, D3DXVECTOR3 Start, D3DXVECTOR3 End, ORBITTYPE nType, PlayerMotionType nMotionType);
void SetPosOrbit(PlayerMotionType nMotionType);

#endif
