//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// �v���C���[�ԍ��̕\���̏��� [playerMark.h]
// Author : suzuki
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _PLAYERMARK_H_
#define _PLAYERMARK_H_

#include "main.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �}�N����`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define PLAYERMARK_TEXTURE_0	"data/TEXTURE/CharacterMarker000.png"	// �e�N�X�`��
#define PLAYERMARK_TEXTURE_1	"data/TEXTURE/CharacterMarker001.png"	// �e�N�X�`��
#define PLAYERMARK_TEXTURE_2	"data/TEXTURE/CharacterMarker002.png"	// �e�N�X�`��
#define PLAYERMARK_TEXTURE_3	"data/TEXTURE/CharacterMarker003.png"	// �e�N�X�`��
#define PLAYERMARK_MAX			(4)										// �ő吔
#define PLAYERMARK_WIDTH		(20)									// ��
#define PLAYERMARK_HEIGHT		(20)									// ����
#define PLAYERMARK_COUNTSPEED	(300)									// �\���؂�ւ��̑���

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//�\���̂̒�`
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct
{
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 rot;					// ����
	D3DXMATRIX	mtxWorldPlayerMark;		// ���[���h�}�g���b�N�X
	D3DXCOLOR	col;					// �F
	int			nCntSwitch;				// �\������A���Ȃ���؂�ւ���J�E���g
	float		fWidth;					// ��
	float		fHeight;				// ����
	bool		bUse;					// �g�p���Ă��邩�ǂ���
}PlayerMark;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// �v���g�^�C�v�錾
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void InitPlayerMark(void);
void UninitPlayerMark(void);
void UpdatePlayerMark(void);
void DrawPlayerMark(void);

void SetPlayerMark(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col);
#endif
