#pragma once
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �Q�[������ [game.h]
// Author :Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _GAME_H_
#define _GAME_H_

#define GAME_TIME	(180)	// �^�C��

#include "main.h"
// �Q�[���̏��
typedef enum
{
	GAMESTATE_NONE = 0,	// �������Ă��Ȃ����
	GAMESTATE_START ,	// �n�܂�̏��
	GAMESTATE_GAME,	// �ʏ���
	GAMESTATE_END,	// �I���
	GAMESTATE_MAX,
}GAMESTATE;

typedef enum
{
	GAMESTAGE1 = 0,
	GAMESTAGEMAX
}GAMESTAGE;

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);
int GetGameStateCounter(void);
void ReleaseGamePause(void);

void SetPlayerFileData(int nIdy, char *cFilename);						// �v���C���[�t�@�C���f�[�^
void SetObjectFileData(void);						// �I�u�W�F�N�g�t�@�C���f�[�^
void SetStagePos(char *cFilename);					// �X�e�[�W�̈ʒu�f�[�^
bool GetPause(void);
bool GetPauseView(void);
void SetSpecalUse(bool bSpesal);

int GetTimeGame(void);
bool GetTakoyaki(void);
void SetTakoyaki(bool bSet);
bool GetChoco(void);
void SetChoco(bool bSet);
bool GetFish(void);
void SetFish(bool bSet);

void PrintStagePos(void);
#endif
