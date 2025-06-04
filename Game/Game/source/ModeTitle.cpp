
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"

bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }
	title = LoadGraph("res/title.png");
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

	if (trg & PAD_INPUT_A) {
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Del(this);
		// ���̃��[�h��o�^
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
	}

	return true;
}

bool ModeTitle::Render() {
	base::Render();
	DrawFormatString(400, 400, GetColor(255, 0, 0), "�^�C�g��");
	DrawGraph(0,0, title,true);

	return true;
}
