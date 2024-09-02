#pragma once

#include <string>
#include <DirectXMath.h>

// ===================================
// 
//		�I�u�W�F�N�g�̊��N���X
// 
// ===================================
class GameObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	GameObject(const DirectX::XMFLOAT3& _position);

	GameObject() = default;
	virtual ~GameObject() = default;

	// �X�V����
	virtual void Update(float _deltaTime) = 0;
	// �`�揈��
	virtual void Draw() const =0;

	void SetPosition(const DirectX::XMFLOAT3& _position);
	DirectX::XMFLOAT3 GetPosition() const;

protected:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scaling;

};

