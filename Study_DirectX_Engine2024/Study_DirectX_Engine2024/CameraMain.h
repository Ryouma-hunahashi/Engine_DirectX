#pragma once
#include "CameraBase.h"
class CameraMain : public CameraBase
{
public:
	CameraMain() = default;
	~CameraMain() = default;

	void Init();

	void Rotate(float _dx, float _dy);

	void MoveForward(float _distance);

	void MoveRight(float _distance);

	void UpdateViewMatrix() override;

	void Update(float _deltaTime);

private:
	float yaw;   // ���E��]�p�x�i���[�j
	float pitch; // �㉺��]�p�x�i�s�b�`�j
	float moveSpeed;    // �ړ����x
	float rotationSpeed; // ��]���x
	DirectX::XMFLOAT3 look;  // �J�����̌���

};

