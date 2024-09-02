#include "Item.h"

Item::Item(ItemType _type, int _quantity, const DirectX::XMFLOAT3& _position)
	: GameObject(_position), type(_type), quantity(_quantity)
{
}

ItemType Item::GetType() const
{
	return type;
}

void Item::SetType(ItemType _type)
{
	this->type = _type;
}

int Item::GetQuantity() const
{
	return quantity;
}

void Item::SetQuantity(int _quatity)
{
	this->quantity = quantity;
}

void Item::Update(float _deltaTime)
{
}

void Item::Draw() const
{
}
