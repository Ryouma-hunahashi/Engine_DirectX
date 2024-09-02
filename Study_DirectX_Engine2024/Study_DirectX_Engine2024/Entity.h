#pragma once
#include "GameObject.h"
class Entity : public GameObject
{
public:
	// コンストラクタ
	Entity(const DirectX::XMFLOAT3& _position);

	// 更新処理
	void Update(float _deltaTime) override;
	// 描画処理
	void Draw() const override;

protected:
	DirectX::XMFLOAT3 velocity;

};

