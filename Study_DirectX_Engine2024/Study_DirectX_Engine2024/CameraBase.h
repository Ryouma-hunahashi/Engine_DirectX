#pragma once

#include <DirectXMath.h>

class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();

	// �ʒu�ݒ�
	void SetPosition(float _x, float _y, float _z);
	// �����ݒ�
	void SetDirection(float _x, float _y, float _z);
	// �ʒu�擾
	DirectX::XMFLOAT3 GetPosition() const;
	// �����擾
	DirectX::XMFLOAT3 Getdirection() const;
	
	// �r���[�s��̍X�V����
	virtual void UpdateViewMatrix() = 0; 
	// �r���[�s��擾
	DirectX::XMFLOAT4X4 GetViewMatrix() const;

protected:
	DirectX::XMFLOAT3 position;		// �ʒu
	DirectX::XMFLOAT3 rotation;		// ��]
	DirectX::XMFLOAT3 direction;	// ����
	DirectX::XMFLOAT3 up;			// �����
	DirectX::XMFLOAT4X4 viewMatrix;	// �r���[�s��

};

