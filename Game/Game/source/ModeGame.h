
#include "appframe.h"

#include <string>

// �J����
class Camera {
public:
	VECTOR	_vPos;					// �ʒu
	VECTOR	_vTarget;				// ����
	VECTOR	_vC_Dir;				// ����
	float	_clipNear, _clipFar;	// �N���b�v
};

// ���[�h
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();



	
	// 3D���f���`��p
	int handle;
	VECTOR vPos;    // �ʒu
	VECTOR vDir;	// ����

	VECTOR position;

	// �J����
	Camera	_cam;

protected:

}; 

