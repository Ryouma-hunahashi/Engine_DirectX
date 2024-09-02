#include "Entity.h"

Entity::Entity(const DirectX::XMFLOAT3& _position)
	:GameObject(_position),velocity(0.0f,0.0f,0.0f)
{
}

void Entity::Update(float _deltaTime)
{
	position.x += velocity.x * _deltaTime;
	position.y += velocity.y * _deltaTime;
	position.z += velocity.z * _deltaTime;
}

void Entity::Draw() const
{
}
