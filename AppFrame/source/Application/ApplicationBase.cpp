
#include "ApplicationBase.h"

ApplicationBase	*ApplicationBase::_lpInstance = NULL;


ApplicationBase::ApplicationBase() {
	_lpInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// DXライブラリの初期化
	if(AppWindowed()){
		ChangeWindowMode(true);							// ウィンドウモードに指定する
	}
	SetGraphMode(DispSizeW(), DispSizeH(), 32);

	if (DxLib_Init() == -1)
	{	// エラーが起きたら直ちに終了
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// 描画先画面を裏画面にセット

	// 乱数初期化
	srand((unsigned int)time(NULL));

	// モードサーバの初期化
	_serverMode = new ModeServer();

	return true;
}

bool ApplicationBase::Terminate() {
	// DXライブラリ開放
	DxLib_End();

	return true;
}


bool ApplicationBase::Input() {
	// キーの入力、トリガ入力を得る
	int keyold = _gKey;
	_gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	_gTrg = (_gKey ^ keyold) & _gKey;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）

	// キー入力、トリガ入力、リリース入力を得る
	int xKeyold = gKey;
	gKey = GetJoypadInputState(DX_INPUT_PAD1);		// キー入力を取得
	gTrg = (gKey ^ keyold) & gKey;
	gRel = (gKey ^ keyold) & ~gKey;

	// XInputでの入力値取得
	int Xkeyold[XINPUT_BUTTON_MAX];
	for (int i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		Xkeyold[i] = xinput_pad.Buttons[i];
	}

	GetJoypadXInputState(DX_INPUT_PAD1, &xinput_pad);			// pad1の入力値を取得

	for (int i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		// XInputでのキー入力、トリガ入力、リリース入力を得る
		gXKey[i] = xinput_pad.Buttons[i];
		gXTrg[i] = (gXKey[i] ^ Xkeyold[i]) & gXKey[i];
		gXRel[i] = (gXKey[i] ^ Xkeyold[i]) & ~gXKey[i];
	}


	return true;
}

bool ApplicationBase::Process() {
	_serverMode->ProcessInit();
	_serverMode->Process();
	_serverMode->ProcessFinish();
	return true;
}

bool ApplicationBase::Render() {
	_serverMode->RenderInit();
	_serverMode->Render();
	_serverMode->RenderFinish();
	return true;
}
