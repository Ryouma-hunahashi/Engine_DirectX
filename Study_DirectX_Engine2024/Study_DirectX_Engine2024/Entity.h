#pragma once
#include "GameObject.h"
class Entity : public GameObject
{
public:
	// �R���X�g���N�^
	Entity(const DirectX::XMFLOAT3& _position);

	// �X�V����
	void Update(float _deltaTime) override;
	// �`�揈��
	void Draw() const override;

protected:
	DirectX::XMFLOAT3 velocity;

};

