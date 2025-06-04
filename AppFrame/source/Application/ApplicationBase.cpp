
#include "ApplicationBase.h"

ApplicationBase	*ApplicationBase::_lpInstance = NULL;


ApplicationBase::ApplicationBase() {
	_lpInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// DX���C�u�����̏�����
	if(AppWindowed()){
		ChangeWindowMode(true);							// �E�B���h�E���[�h�Ɏw�肷��
	}
	SetGraphMode(DispSizeW(), DispSizeH(), 32);

	if (DxLib_Init() == -1)
	{	// �G���[���N�����璼���ɏI��
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// �`����ʂ𗠉�ʂɃZ�b�g

	// ����������
	srand((unsigned int)time(NULL));

	// ���[�h�T�[�o�̏�����
	_serverMode = new ModeServer();

	return true;
}

bool ApplicationBase::Terminate() {
	// DX���C�u�����J��
	DxLib_End();

	return true;
}


bool ApplicationBase::Input() {
	// �L�[�̓��́A�g���K���͂𓾂�
	int keyold = _gKey;
	_gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	_gTrg = (_gKey ^ keyold) & _gKey;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j

	// �L�[���́A�g���K���́A�����[�X���͂𓾂�
	int xKeyold = gKey;
	gKey = GetJoypadInputState(DX_INPUT_PAD1);		// �L�[���͂��擾
	gTrg = (gKey ^ keyold) & gKey;
	gRel = (gKey ^ keyold) & ~gKey;

	// XInput�ł̓��͒l�擾
	int Xkeyold[XINPUT_BUTTON_MAX];
	for (int i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		Xkeyold[i] = xinput_pad.Buttons[i];
	}

	GetJoypadXInputState(DX_INPUT_PAD1, &xinput_pad);			// pad1�̓��͒l���擾

	for (int i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		// XInput�ł̃L�[���́A�g���K���́A�����[�X���͂𓾂�
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
