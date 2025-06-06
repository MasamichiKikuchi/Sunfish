
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"

bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }
	
		
	return true;
}

bool ModeTitle::Terminate() {

	base::Terminate();
	return true;
}

bool ModeTitle::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();
	XINPUT_STATE input = ApplicationMain::GetInstance()->GetXinputPad();
	auto gTrg = ApplicationMain::GetInstance()->GetXTrg();
	
	if (input.Buttons[XINPUT_BUTTON_A] && gTrg[XINPUT_BUTTON_A]) {
		// このモードを削除予約
		ModeServer::GetInstance()->Del(this);
		// 次のモードを登録
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
	}

	return true;
}

bool ModeTitle::Render() {
	base::Render();
	DrawFormatString(100, 100, GetColor(255, 0, 0), "タイトル");
	DrawString(0, 64, "Button", GetColor(255, 0, 0));
	/*for (int i = 0; i < 16; i++)
	{
		DrawFormatString(64 + i % 8 * 64, 64 + i / 8 * 16, GetColor(255, 0, 0),"%2d:%d", i, input.Buttons[i]);
	}*/

	return true;
}
