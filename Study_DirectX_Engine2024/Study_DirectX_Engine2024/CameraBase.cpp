#include "CameraBase.h"

CameraBase::CameraBase()
{
}

CameraBase::~CameraBase()
{
}

void CameraBase::SetPosition(float _x, float _y, float _z)
{
}

void CameraBase::SetDirection(float _x, float _y, float _z)
{
}

DirectX::XMFLOAT3 CameraBase::GetPosition() const
{
	return position;
}

DirectX::XMFLOAT3 CameraBase::Getdirection() const
{
	return direction;
}

DirectX::XMFLOAT4X4 CameraBase::GetViewMatrix() const
{
	return viewMatrix;
}
