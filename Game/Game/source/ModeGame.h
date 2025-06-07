
#include "appframe.h"

#include <string>

// カメラ
class Camera 
{
	public:
	VECTOR	_vPos;					// 位置
	VECTOR	_vTarget;				// 距離
	VECTOR	_vC_Dir;				// 向き
	float	_clipNear, _clipFar;	// クリップ
};

// モード
class ModeGame : public ModeBase
{
	struct Quaternion
	{
		float w, x, y, z;
	};

	Quaternion QuaternionIdentity()
	{
		return { 1.0f, 0.0f, 0.0f, 0.0f };
	}

	Quaternion QuaternionFromAxisAngle(VECTOR axis, float angle) {
		axis = VNorm(axis); // 単位ベクトル化
		float sinHalf = sinf(angle / 2.0f);
		return {
			cosf(angle / 2.0f),
			axis.x * sinHalf,
			axis.y * sinHalf,
			axis.z * sinHalf
		};
	}

	MATRIX QuaternionToMatrix(const Quaternion& q) {
		float ww = q.w * q.w;
		float xx = q.x * q.x;
		float yy = q.y * q.y;
		float zz = q.z * q.z;

		float wx = q.w * q.x;
		float wy = q.w * q.y;
		float wz = q.w * q.z;

		float xy = q.x * q.y;
		float xz = q.x * q.z;
		float yz = q.y * q.z;

		MATRIX mat;

		mat.m[0][0] = 1 - 2 * (yy + zz);
		mat.m[0][1] = 2 * (xy - wz);
		mat.m[0][2] = 2 * (xz + wy);
		mat.m[0][3] = 0;

		mat.m[1][0] = 2 * (xy + wz);
		mat.m[1][1] = 1 - 2 * (xx + zz);
		mat.m[1][2] = 2 * (yz - wx);
		mat.m[1][3] = 0;

		mat.m[2][0] = 2 * (xz - wy);
		mat.m[2][1] = 2 * (yz + wx);
		mat.m[2][2] = 1 - 2 * (xx + yy);
		mat.m[2][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		return mat;
	}

	Quaternion QuaternionMultiply(const Quaternion& q1, const Quaternion& q2)
	{
		return
		{
			q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
			q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
			q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
			q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w
		};
	}

	// プレイヤー構造体
	struct Player
	{
		VECTOR position;
		Quaternion rotation;
		float moveSpeed;
		float rotSpeed;
		int modelHandle;
	};

	typedef ModeBase base;
	public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
	VECTOR GetForwardVector(const Quaternion& q);
	void InitPlayer(Player& player);
	void UpdatePlayer(Player& player);

	// 3Dモデル描画用
	int handle;
	VECTOR vPos;    // 位置
	VECTOR vDir;	// 向き

	VECTOR position;

	// カメラ
	Camera	_cam;

	// プレイヤー情報
	Player player;

protected:

}; 

