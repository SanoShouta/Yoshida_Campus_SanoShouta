////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �J�������� [camera.h]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//******************************************************************************************************************************
// �J�����̍\����
//******************************************************************************************************************************
typedef enum
{
	CAMERASTATE_NONE = 0,
	CAMERASTATE_BTTALEBIGIN,
	CAMERASTATE_BTTALESTART,
	CAMERASTATE_READY,
	CAMERASTATE_SPECIAL,
	CAMERASTATE_MAX,
}CAMERASTATE;
typedef struct
{
	D3DXVECTOR3	posV;			// ���_
	D3DXVECTOR3	posVOld;		// �O��̎��_
	D3DXVECTOR3	posR;			// �����_
	D3DXVECTOR3	vecU;			// ������x�N�g��
	D3DXVECTOR3	rot;			// ��]��
	D3DXVECTOR3 Diffrot;		// �p�x�̍���
	D3DXVECTOR3 Destrot;		// �ړI�̊p�x
	D3DXVECTOR3 posVDiff;		// �ꏊ�̍���
	D3DXVECTOR3 posVDest;		// �ړI�̏ꏊ
	D3DXVECTOR3 posRDiff;		// �ꏊ�̍���
	D3DXVECTOR3 posRDest;		// �ړI�̏ꏊ
	CAMERASTATE nState;			// ���
	int nStateCounter;			// ��ԃJ�E���^�[
	float fLength;				// V����
	float fLengthAdd;			// ������������
	float fHeight;				// V����
	float fLengthR;				// R����
	float fHeightR;				// R����
	float fHeightWall;			// �ǂɓ��������Ƃ��̉��Z�p
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
	D3DXMATRIX mtxViewShader;			// �r���[�}�g���b�N�X
	// �|�[�Y���ɓ��������猳�ɖ߂�
	D3DXVECTOR3	PauseOldposV;			// ���_
	D3DXVECTOR3	PauseOldposR;			// �����_
	D3DXVECTOR3	PauseOldrot;			// ��]��
	D3DVIEWPORT9 viewpoart;		// �r���[�|�[�g

}Camera;

//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nIdxCamera);
Camera *GetCamera(void);
#endif
