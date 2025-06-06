
#include "appframe.h"

#include <string>

// カメラ
class Camera {
public:
	VECTOR	_vPos;					// 位置
	VECTOR	_vTarget;				// 距離
	VECTOR	_vC_Dir;				// 向き
	float	_clipNear, _clipFar;	// クリップ
};

// モード
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();



	
	// 3Dモデル描画用
	int handle;
	VECTOR vPos;    // 位置
	VECTOR vDir;	// 向き

	VECTOR position;

	// カメラ
	Camera	_cam;

protected:

}; 

