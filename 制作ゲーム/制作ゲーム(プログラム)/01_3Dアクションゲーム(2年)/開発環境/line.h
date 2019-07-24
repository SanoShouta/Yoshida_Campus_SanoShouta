////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ����p���C���̏��� [line.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _LINE_H_
#define _LINE_H_

#include "main.h"
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef enum
{
	LINETYPE_PLAYER = 0,
	LINETYPE_ENEMY ,
	LINETYPE_MODEL ,
	LINETYPE_MAX
}LINETYPE;
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 posOld;	// �O��̈ʒu
	D3DXVECTOR3 posStart;	// �ŏ��̈ʒu
	D3DXVECTOR3 posEnd;	// �Ō�̈ʒu
	D3DXCOLOR col;		// �F
	D3DXVECTOR3 move;	// ����
	D3DXVECTOR3 rot;	// ����
	D3DXMATRIX mtxWorld;// ���[���h�}�g���b�N�X
	LINETYPE nType;		// ���
	bool bUse;			// �g�p����Ă��邩�ǂ���
}Line;

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void InitLine(void);
void UninitLine(void);
void UpdateLine(void);
void DrawLine(void);
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 posStart, D3DXVECTOR3 posEnd, D3DXCOLOR col, LINETYPE nType);
int CollisionLine(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMin,D3DXVECTOR3 vtxMax, LINETYPE nType);
void SetPositionLine(int nIdyLine, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void DeleteLine(LINETYPE nType);
#endif
