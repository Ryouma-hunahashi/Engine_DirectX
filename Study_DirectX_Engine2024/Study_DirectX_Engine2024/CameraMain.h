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
	float yaw;   // 左右回転角度（ヨー）
	float pitch; // 上下回転角度（ピッチ）
	float moveSpeed;    // 移動速度
	float rotationSpeed; // 回転速度
	DirectX::XMFLOAT3 look;  // カメラの向き

};

