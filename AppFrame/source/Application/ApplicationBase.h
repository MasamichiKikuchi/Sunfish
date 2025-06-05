
#include "dxlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Mode//ModeServer.h"

#define	XINPUT_BUTTON_MAX	(16)	// XInput�̃{�^����

class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();

	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();

	virtual bool AppWindowed() { return true; }
	virtual int DispSizeW() { return 640; }
	virtual int DispSizeH() { return 480; }

	static	ApplicationBase	*GetInstance() { return _lpInstance; }
	virtual int GetKey() { return _gKey; }
	virtual int GetTrg() { return gTrg; }

	virtual XINPUT_STATE GetXinputPad() { return xinput_pad; }
	virtual int* GetXTrg() { return gXTrg; }

	static	ApplicationBase* _lpInstance;

	int		_gKey, _gTrg;

	ModeServer* _serverMode;

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


protected:
	

};
