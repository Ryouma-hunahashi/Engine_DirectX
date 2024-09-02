#pragma once
#include "GameObject.h"

enum class ItemType
{
	SWORD,PICKALE,SHOVEL,
	MAX
};

class Item : public GameObject
{
public:
	// コンストラクタ
	Item(ItemType _type, int _quantity, const DirectX::XMFLOAT3& _position);

	ItemType GetType() const;
	void SetType(ItemType _type);

	int GetQuantity() const;
	void SetQuantity(int _quatity);

	void Update(float _deltaTime) override;
	void Draw() const override;

private:
	ItemType type;
	int quantity;
};

