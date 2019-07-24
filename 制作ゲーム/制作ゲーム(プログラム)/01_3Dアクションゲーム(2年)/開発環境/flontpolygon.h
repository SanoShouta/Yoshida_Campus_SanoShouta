//=============================================================================
//
// �|���S������ [flontpolygon.h]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#ifndef _FLONTPOLYGON_H_
#define _FLONTPOLYGON_H_

#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_FLONTPOLYGON	(128)		//�w�i�̍ő吔

//=============================================================================
// �|���S���̎��
//=============================================================================
typedef enum
{
	FLONTTYPE_CHOTIN = 0,
	FLONTTYPE_CYARACTOR,
	FLONTTYPE_COMMENT,
	FLONTTYPE_READY,		// �o�g���J�n��������
	FLONTTYPE_NOMAL,
	FLONTTYPE_UI,
	FLONTTYPE_FACE_HUMAN,
	FLONTTYPE_FACE_TENGU,
	FLONTTYPE_FACE_KAPPA,
	FLONTTYPE_FACE_FOX,
	FLONTTYPE_FACE_ROBOT,
	FLONTTYPE_NARRATION,
	FLONTTYPE_MAX
}FLONTTYPE;

//�R�����g�̎��
typedef enum
{
	COMMENTTYPE_BTTLE = 0,
	COMMENTTYPE_QUESTION,
	COMMENTTYPE_TITLE,
	COMMENTTYPE_MAX
}COMMENTTYPE;
typedef enum
{
	FLONT_TEXTYPE_CHOTIN = 0,
	FLONT_TEXTYPE_CHARACTOR,
	FLONT_TEXTYPE_HUKIDASHI,
	FLONT_TEXTYPE_READY,
	FLONT_TEXTYPE_TITLE,
	FLONT_TEXTYPE_UI,
	FLONT_TEXTYPE_FASE,
	FLONT_TEXTYPE_SETTING,
	FLONT_TEXTYPE_START,
	FLONT_TEXTYPE_GAMEEND,
	FLONT_TEXTYPE_FG,
	FLONT_TEXTYPE_BG,
	FLONT_TEXTYPE_TIMEUP,
	FLONT_TEXTYPE_MAX
}FLONT_TEXTYPE;

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3		pos;			//���S���W
	float			fWidth;			//��
	float			fHight;			//����
	float			fUv;			//UV�l
	int				nTexNum;		//�e�N�X�`���̔ԍ�
	FLONTTYPE		type;			//�^�C�v
	D3DXCOLOR		col;			//�F
	bool			bUse;			//�g�p���Ă��邩�ǂ���
}FlontPolygon;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitFlontPolygon(void);
void UninitFlontPolygon(void);
void UpdateFlontPolygon(void);
void DrawFlontPolygon(void);

int SetFlontPolygon(int nTexNum, D3DXVECTOR3 pos, float fWidth, float fHight, FLONTTYPE type);

void SetTexture(int nIdx, int nNumComment);
void ReleaseAllFlontPolygon();
void DeleteFlontPolygon(int nIdx);
FlontPolygon * GetFlontPolygon(void);
#endif