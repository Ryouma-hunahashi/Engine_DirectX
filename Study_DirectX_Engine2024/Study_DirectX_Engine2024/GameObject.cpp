#include "GameObject.h"

GameObject::GameObject(const DirectX::XMFLOAT3& _position)
	:position(_position)
{
}

void GameObject::SetPosition(const DirectX::XMFLOAT3& _position)
{
	this->position = _position;
}

DirectX::XMFLOAT3 GameObject::GetPosition() const
{
	return position;
}
