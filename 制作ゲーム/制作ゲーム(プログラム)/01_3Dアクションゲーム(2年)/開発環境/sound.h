////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �T�E���h���� [sound.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//******************************************************************************************************************************
// �T�E���h�t�@�C��
//******************************************************************************************************************************
typedef enum
{
	SOUND_LABEL_TITLEBGM = 0,	// �^�C�g��
	SOUND_LABEL_SELECTBGM,		// �Z���N�g
	SOUND_LABEL_CHARASELECTBGM,	// �L�����Z���N�g
	SOUND_LABEL_GAMEBGM000,		// �Q�[��000
	SOUND_LABEL_GAMEBGM001,		// �Q�[��001
	SOUND_LABEL_RESULTBGM,		// ���U���g
	SOUND_LABEL_HIT000,		// �q�b�g000
	SOUND_LABEL_HIT001,		// �q�b�g001
	SOUND_LABEL_JUMP,		// �W�����v
	SOUND_LABEL_LAND,		// ���n
	SOUND_LABEL_MOVE,		// �ړ�
	SOUND_LABEL_GAMEEND000,		// �Q�[���I��000
	SOUND_LABEL_GAMESETTING000,		// �Q�[���Z�b�e�B���O000
	SOUND_LABEL_GAMESTART000,		// �Q�[���X�^�[�g000
	SOUND_LABEL_GAMESTART001,		// �Q�[���X�^�[�g001
	SOUND_LABEL_TIMEUP000,		// �^�C���A�b�v000
	SOUND_LABEL_PAUSE000,		// �|�[�Y000
	SOUND_LABEL_SYSTEMSELECT000,		// �|�[�Y000
	//���{�b�g�@SE
	SOUND_ROBOT_GARD,      //���{�b�g�@�K�[�h
	SOUND_ROBOT_BUTOBI,    //���{�b�g�@�Ԃ����
	SOUND_ROBOT_KAIHI,     //���{�b�g�@���
	SOUND_ROBOT_ATTACK000,    //���{�b�g�@�U�� 000
	SOUND_ROBOT_ATTACK001,    //���{�b�g�@�U�� 001
	SOUND_ROBOT_ATTACK002,    //���{�b�g�@�U�� 002
	SOUND_ROBOT_ATTACK003,    //���{�b�g�@�U�� 003
	SOUND_ROBOT_ATTACK004,    //���{�b�g�@�U�� 004
	SOUND_ROBOT_ATTACK005,    //���{�b�g�@�U�� 005
	SOUND_ROBOT_HUNOU,     //���{�b�g�@�퓬�s�\
	SOUND_ROBOT_NAGERU,    //���{�b�g�@������
	SOUND_ROBOT_DAMEJI,    //���{�b�g�@��_���[�W
	SOUND_ROBOT_IDOU,    //���{�b�g�@�ړ�
	SOUND_ROBOT_JANP,    //���{�b�g�@�W�����v
	//�͓��@SE
	SOUND_KAPA_GARD,        //�͓��@�K�[�h
	SOUND_KAPA_BUTOBI,      //�͓��@�Ԃ����
	SOUND_KAPA_KAIHI,       //�͓��@���
	SOUND_KAPA_ATTACK000,      //�͓��@�U�� 000
	SOUND_KAPA_ATTACK001,      //�͓��@�U�� 001
	SOUND_KAPA_ATTACK002,      //�͓��@�U�� 002
	SOUND_KAPA_ATTACK003,      //�͓��@�U�� 003
	SOUND_KAPA_ATTACK004,      //�͓��@�U�� 004
	SOUND_KAPA_ATTACK005,      //�͓��@�U�� 005
	SOUND_KAPA_HUNOU000,       //�͓��@�퓬�s�\
	SOUND_KAPA_HUNOU001,       //�͓��@�퓬�s�\
	SOUND_KAPA_NAGERU,      //�͓��@������
	SOUND_KAPA_DAMEJI000,      //�͓��@��_���[�W
	SOUND_KAPA_DAMEJI001,      //�͓��@��_���[�W
	SOUND_KAPA_DAMEJI002,      //�͓��@��_���[�W
	SOUND_KAPA_VICTORY,   //�͓��@������
	SOUND_KAPA_IDOU,   //�͓��@�ړ�
	//�l��
	SOUND_HUMAN_GARD000,       //�l�ԁ@�K�[�h
	SOUND_HUMAN_GARD001,       //�l�ԁ@�K�[�h
	SOUND_HUMAN_BUTOBI,     //�l�ԁ@�Ԃ����
	SOUND_HUMAN_KAIHI,      //�l�ԁ@���
	SOUND_HUMAN_ATTACK000,     //�l�ԁ@�U�� 000
	SOUND_HUMAN_ATTACK001,     //�l�ԁ@�U�� 001
	SOUND_HUMAN_ATTACK002,     //�l�ԁ@�U�� 002
	SOUND_HUMAN_ATTACK003,     //�l�ԁ@�U�� 003
	SOUND_HUMAN_ATTACK004,     //�l�ԁ@�U�� 004
	SOUND_HUMAN_ATTACK005,     //�l�ԁ@�U�� 005
	SOUND_HUMAN_ATTACK006,     //�l�ԁ@�U�� 006
	SOUND_HUMAN_ATTACK007,     //�l�ԁ@�U�� 007
	SOUND_HUMAN_ATTACK008,     //�l�ԁ@�U�� 008
	SOUND_HUMAN_ATTACK009,     //�l�ԁ@�U�� 009
	SOUND_HUMAN_HUNOU,      //�l�ԁ@�퓬�s�\
	SOUND_HUMAN_NAGERU,     //�l�ԁ@������
	SOUND_HUMAN_DAMEJI,     //�l�ԁ@��_���[�W
	SOUND_HUMAN_VICTORY,  //�l�ԁ@�������@

	//�V��
	SOUND_TENGU_GARD,       //�V��@�K�[�h
	SOUND_TENGU_BUTOBI,     //�V��@�Ԃ����
	SOUND_TENGU_KAIHI,      //�V��@���
	SOUND_TENGU_ATTACK000,     //�V��@�U�� 000
	SOUND_TENGU_ATTACK001,     //�V��@�U�� 001
	SOUND_TENGU_ATTACK002,     //�V��@�U�� 002
	SOUND_TENGU_ATTACK003,     //�V��@�U�� 003
	SOUND_TENGU_ATTACK004,     //�V��@�U�� 004
	SOUND_TENGU_ATTACK005,     //�V��@�U�� 005
	SOUND_TENGU_HUNOU000,      //�V��@�퓬�s�\ 000
	SOUND_TENGU_HUNOU001,      //�V��@�퓬�s�\ 001
	SOUND_TENGU_NAGERU,     //�V��@������
	SOUND_TENGU_DAMEJI,     //�V��@��_��
	SOUND_TENGU_VICTORY,    //�V��@�������@
	////�ρ@SE
	SOUND_FOX_GARD,         //�ρ@�K�[�h
	SOUND_FOX_BUTOBI,       //�ρ@�Ԃ����
	SOUND_FOX_KAIHI,        //�ρ@���
	SOUND_FOX_ATTACK000,       //�ρ@�U��000
	SOUND_FOX_ATTACK001,       //�ρ@�U��001
	SOUND_FOX_ATTACK002,       //�ρ@�U��002
	SOUND_FOX_ATTACK003,       //�ρ@�U��003
	SOUND_FOX_ATTACK004,       //�ρ@�U��004
	SOUND_FOX_ATTACK005,       //�ρ@�U��005
	SOUND_FOX_HUNOU,        //�ρ@�퓬�s�\
	SOUND_FOX_NAGERU,       //�ρ@������
	SOUND_FOX_DAMEJI,       //�ρ@��_���[�W
	SOUND_FOX_VICTORY,     //�ρ@������
	// �퓬�n
	SOUND_EFFECT_WIND000,	// ���P
	SOUND_EFFECT_WIND001,	// ��2
	SOUND_EFFECT_SRASH000,	// �Ђ�����000
	SOUND_EFFECT_SRASH001,	// �Ђ�����001
	SOUND_EFFECT_SRASH002,	// �Ђ�����002
	SOUND_EFFECT_FLAME000,	//�Ή�����000
	SOUND_EFFECT_FLAME001,	//�Ή�����001
	SOUND_EFFECT_BOMB000,	// ����
	SOUND_EFFECT_BOMB001,	// ����
	SOUND_EFFECT_GUARD,	// �K�[�h
	SOUND_EFFECT_GUARD_CRASH,	// �K�[�h�N���b�V��
	// ����
	SOUND_TAIKO_1,	// ����
	SOUND_TAIKO_2,	// ����
	SOUND_TAIKO_3,	// ����
	SOUND_TAIKO_4,	// ����
	// ����
	SOUND_KANSEI_1,	// ����
	SOUND_KANSEI_2,// ����
	// �V�X�e��
	SOUND_SELECTMOVE,// �J�[�\���ړ�
	SOUND_DECISION,	// ����
	SOUND_DECISION_1,	// ����
	SOUND_CUTIN,		// �J�b�g�C��
	SOUND_SPECIALROGO,	// SPECIAL���S
	SOUND_CHARACTOR_SELECT,// �L�����N�^�[�I��
	SOUND_CHARACTOR_READY,	// ����
	SOUND_ALERT,	// �x����
	SOUND_SUNDER,	// ��
	SOUND_RAIN,// �J
	SOUND_FLOOD,// �×�
	SOUND_LIFE,		// ���C�t�A�b�v
	SOUND_ATTACK,	// �p���[�A�b�v
	SOUND_SPEED,	// �X�s�[�h�A�b�v
	SOUND_METEO,	// ���e�I
	SOUND_EXPLOSION,// ����
		SOUND_GUST,// �˕�
		SOUND_TIMELIMIT,// �^�C��
	SOUND_LABEL_MAX
}SOUND_LABEL;

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);	// �Đ�
void StopSound(SOUND_LABEL label);		// Uninit�œ������O�Ŏ~�߂�
void StopSound(void);
void ChangeVolume(SOUND_LABEL label, float fVolume);
void CheckPos(D3DXVECTOR3 pos);
#endif
