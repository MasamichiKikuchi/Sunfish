#pragma once
#include "appframe.h"
#define	XINPUT_BUTTON_MAX	(16)	// XInput�̃{�^����
// ���[�h
class ModeTitle : public ModeBase
{
	typedef ModeBase base;
public:

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:

	int title;
	// �L�[�{�[�h���Q�[���p�b�h1�̂ǂ���ł��g����ꍇ
	int gKey;
	int gTrg;
	int gRel;

	// �Q�[���p�b�h1�p�̏ꍇ
	XINPUT_STATE xinput_pad;

	// XInput�p
	int gXKey[XINPUT_BUTTON_MAX];
	int gXTrg[XINPUT_BUTTON_MAX];
	int gXRel[XINPUT_BUTTON_MAX];



};