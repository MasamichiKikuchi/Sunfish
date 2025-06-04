#pragma once
#include "appframe.h"
#define	XINPUT_BUTTON_MAX	(16)	// XInputのボタン数
// モード
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
	// キーボード＆ゲームパッド1のどちらでも使える場合
	int gKey;
	int gTrg;
	int gRel;

	// ゲームパッド1用の場合
	XINPUT_STATE xinput_pad;

	// XInput用
	int gXKey[XINPUT_BUTTON_MAX];
	int gXTrg[XINPUT_BUTTON_MAX];
	int gXRel[XINPUT_BUTTON_MAX];



};