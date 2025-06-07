
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

// 前方ベクトル（Z+）をクォータニオンで回転して取得
VECTOR ModeGame::GetForwardVector(const Quaternion& q)
{
	MATRIX mat = QuaternionToMatrix(q);
	return VGet(mat.m[2][0], mat.m[2][1], mat.m[2][2]);
}

// 初期化
void ModeGame::InitPlayer(Player& player)
{
	player.position = VGet(0.0f, 0.0f, 0.0f);
	player.rotation = QuaternionIdentity();
	player.moveSpeed = 0.5f;
	player.rotSpeed = 0.05f;
	player.modelHandle = MV1LoadModel("resource/Player/manbo.mv1");
}

// 更新処理
void ModeGame::UpdatePlayer(Player& player)
{
	// 入力による回転
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		player.rotation = QuaternionMultiply(
			QuaternionFromAxisAngle(VGet(0, 1, 0), -player.rotSpeed), player.rotation);
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		player.rotation = QuaternionMultiply(
			QuaternionFromAxisAngle(VGet(0, 1, 0), player.rotSpeed), player.rotation);
	}
	if (CheckHitKey(KEY_INPUT_UP)) {
		player.rotation = QuaternionMultiply(
			QuaternionFromAxisAngle(VGet(1, 0, 0), -player.rotSpeed), player.rotation);
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		player.rotation = QuaternionMultiply(
			QuaternionFromAxisAngle(VGet(1, 0, 0), player.rotSpeed), player.rotation);
	}
	if (CheckHitKey(KEY_INPUT_Z)) {
		player.rotation = QuaternionMultiply(
			QuaternionFromAxisAngle(VGet(0, 0, 1), -player.rotSpeed), player.rotation);
	}
	if (CheckHitKey(KEY_INPUT_X)) {
		player.rotation = QuaternionMultiply(
			QuaternionFromAxisAngle(VGet(0, 0, 1), player.rotSpeed), player.rotation);
	}

	// 移動処理（前進）
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		VECTOR forward = GetForwardVector(player.rotation);
		player.position = VAdd(player.position, VScale(forward, player.moveSpeed));
	}

	// 行列に変換して位置情報反映
	MATRIX rotMat = QuaternionToMatrix(player.rotation);
	rotMat.m[3][0] = player.position.x;
	rotMat.m[3][1] = player.position.y;
	rotMat.m[3][2] = player.position.z;

	MV1SetMatrix(player.modelHandle, rotMat);
}

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	InitPlayer(player);

	// カメラの設定（わかりやすい位置に）
	_cam._vPos = VGet(0, 200.0f, -500.f);
	_cam._vTarget = VGet(position.x, position.y, position.z);
	_cam._clipNear = 2.f;
	_cam._clipFar = 1000000.f;
	// カメラ情報
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

	UpdatePlayer(player);

	_cam._vPos = VGet(position.x, position.y, position.z - 1000); ;
	_cam._vTarget = VGet(position.x, position.y, position.z);

	return true;
}

bool ModeGame::Render() {
	base::Render();

	// ３Ｄ空間上にカプセルを描画する
	DrawCapsule3D(VGet(320.0f, 0.0f, 0.0f), VGet(320.0f, 300.0f, 0.0f), 40.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
	DrawCapsule3D(VGet(-320.0f, 0.0f, 0.0f), VGet(-320.0f, 300.0f, 0.0f), 40.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);

	// ライト設定
	SetUseLighting(false);

	// 平行ライト
	SetGlobalAmbientLight(GetColorF(0.f, 0.f, 0.f, 0.f));
	ChangeLightTypeDir(VGet(-1, -1, 0));

	// カメラ設定更新
	SetCameraPositionAndTarget_UpVecY(_cam._vPos, _cam._vTarget);
	SetCameraNearFar(_cam._clipNear, _cam._clipFar);

	// 位置
	//向きからY軸回転を算出
	/*VECTOR vRot = { 0, DEG2RAD(90),0};
	MV1SetRotationXYZ(handle, vRot);*/


	//MV1SetPosition(player.modelHandle, VGet(player.position.x, player.position.y, player.position.z));
	MV1DrawModel(player.modelHandle);


	// 0,0,0を中心に線を引く
	{
		float linelength = 1000.f;
		VECTOR v = { 0, 0, 0 };
		DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}

	DrawFormatString(100, 100, GetColor(255, 0, 0), "ゲーム");

	return true;
}

