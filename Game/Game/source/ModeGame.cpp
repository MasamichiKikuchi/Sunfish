
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	handle = MV1LoadModel("resource/Player/manbo.mv1");

	position = VGet(0.0f, 0.0f, 0.0f);

	// �J�����̐ݒ�i�킩��₷���ʒu�Ɂj
	_cam._vPos = VGet(0, 200.0f, -500.f);
	_cam._vTarget = VGet(position.x, position.y, position.z);
	_cam._clipNear = 2.f;
	_cam._clipFar = 1000000.f;
	// �J�������
	VECTOR camera_position = VGet(0.0f, 200.0f, -50.0f);
	VECTOR camera_target = VGet(0.0f, 0.0f, 0.0f);
	VECTOR camera_up = VGet(0.0f, 1.0f, 0.0f);

	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();
	return true;
}

bool ModeGame::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	position.z += 1;

	_cam._vPos = VGet(position.x, position.y, position.z - 1000); ;
	_cam._vTarget = VGet(position.x, position.y, position.z);

	return true;
}

bool ModeGame::Render() {
	base::Render();

	// �R�c��ԏ�ɃJ�v�Z����`�悷��
	DrawCapsule3D(VGet(320.0f, 0.0f, 0.0f), VGet(320.0f, 300.0f, 0.0f), 40.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
	DrawCapsule3D(VGet(-320.0f, 0.0f, 0.0f), VGet(-320.0f, 300.0f, 0.0f), 40.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);

	// ���C�g�ݒ�
	SetUseLighting(false);
	
	// ���s���C�g
	SetGlobalAmbientLight(GetColorF(0.f, 0.f, 0.f, 0.f));
	ChangeLightTypeDir(VGet(-1, -1, 0));

	// �J�����ݒ�X�V
	SetCameraPositionAndTarget_UpVecY(_cam._vPos, _cam._vTarget);
	SetCameraNearFar(_cam._clipNear, _cam._clipFar);

	// �ʒu
	//��������Y����]���Z�o
	VECTOR vRot = { 0, DEG2RAD(90),0};
	MV1SetRotationXYZ(handle, vRot);
	MV1SetPosition(handle, VGet(position.x, position.y - 50, position.z));
	MV1DrawModel(handle);

	// 0,0,0�𒆐S�ɐ�������
	{
		float linelength = 1000.f;
		VECTOR v = { 0, 0, 0 };
		DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}

	DrawFormatString(100, 100, GetColor(255, 0, 0), "�Q�[��");

	return true;
}

