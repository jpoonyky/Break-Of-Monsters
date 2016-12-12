#include "../IEX/iextreme.h"
#include "Camera.h"
#include	"Player\\Player.h"
Camera::Camera()
{
	Pos = Vector3(0.0f, 0.0f, 0.0f);
	Target = Vector3(0.0f, 0.0f, 0.0f);
	angle = Vector3(0.0f, 0.0f, 0.0f);
	cameraUPvec = Vector3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera()
{

}

void Camera::Init(int mode)
{
	SetProjection(PI / 4, 1.0f, 1400.0f);

	Pos = Vector3(0.0f, 20.0f, 20.0f);
	Target = Vector3(0.0f, 0.0f, 0.0f);
	angle = Vector3(0.0f, 0.0f, 0.0f);
	cameramode = mode;
}

void Camera::TitleCamera(Vector3 t, Vector3 p)
{
	target = t;
	pos = p;
}


void Camera::MainCamera( const Vector3 &p , const Vector3 &f )
{
	target.x = p.x;
	target.y = p.y;
	target.z = p.z;

	pos.x = p.x - f.x * 25;
	pos.y = p.y + 7;
	pos.z = p.z - f.z * 25;
}

void Camera::SubCamera(Vector3 t, Vector3 p)
{

	target.x = t.x-10;
	target.y = t.y-10;
	target.z = t.z-10;

	/*float dx = p.x - pos.x;
	float dz = p.z - pos.z;
	float d = sqrtf(dx*dx + dz*dz);*/

	pos.x = p.x + 10;

}

void Camera::Update(Vector3 t,Vector3 p)
{
	switch (cameramode)
	{
	case 0:
		TitleCamera(t, p);
		break;
	case 1:
		MainCamera(t, p);
		break;
	case 2:
		SubCamera(t, p);
		break;
	case 3:
		TitleCamera(t, p);
		break;
	default:
		MainCamera(t, p);

	}

	Set(pos, target);

}

void Camera::Render()
{
	Activate();
	Clear();
}

void Camera::MainRender()
{
	Activate(cameraUPvec);
	Clear(0xFF87CEEB);
}