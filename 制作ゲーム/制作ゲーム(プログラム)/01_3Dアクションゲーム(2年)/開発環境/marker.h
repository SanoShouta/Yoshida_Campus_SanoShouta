//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �L�����N�^�[�I������ [marker.h]
// Author : asuma
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _MARKER_H_		//2�d�C���N���[�h�h�~�̃}�N����`
#define _MARKER_H_
#include "player.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �}�N����`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define MARKER_WIDTH		(40)							// ��
#define MARKER_HEIGHT		(40)							// ����
#define MARKER_MAX			(4)								// �ő吔
#define MAX_MARKERTOP		(4)								// ���_��
#define MARKER_TEXTURENAME0	"data/TEXTURE/Marker000.png"	// �ǂݍ��ރe�N�X�`���̖��O
#define MARKER_TEXTURENAME1	"data/TEXTURE/Marker001.png"	// �ǂݍ��ރe�N�X�`���̖��O
#define MARKER_TEXTURENAME2	"data/TEXTURE/Marker002.png"	// �ǂݍ��ރe�N�X�`���̖��O
#define MARKER_TEXTURENAME3	"data/TEXTURE/Marker003.png"	// �ǂݍ��ރe�N�X�`���̖��O

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �\���̂̒�`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct
{// �J�[�\��
	D3DXVECTOR3 pos;				// ���݂̈ʒu
	D3DXVECTOR3 posOld;				// �O��̈ʒu
	D3DXVECTOR3 move;				// �ړ���
	float		fWidth;				// ��
	float		fHeight;			// ����
	PLAYERTYPE	type;
	bool		bUse;				// �u���Ă��邩�ǂ���
}MARKER;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �v���g�^�C�v�錾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitMarker(void);
void UninitMarker(void);
void UpdateMarker(void);
void DrawMarker(void);
MARKER *GetMarker(void);
int GetNumMarker(void);
void SetColSel(bool bColSel, int nIdy, int nColId);
bool GetColSel(int nIdy, int nColId);
#endif