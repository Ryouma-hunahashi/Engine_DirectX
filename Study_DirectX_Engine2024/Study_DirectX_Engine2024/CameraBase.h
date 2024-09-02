#pragma once

#include <DirectXMath.h>

class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();

	// 位置設定
	void SetPosition(float _x, float _y, float _z);
	// 向き設定
	void SetDirection(float _x, float _y, float _z);
	// 位置取得
	DirectX::XMFLOAT3 GetPosition() const;
	// 向き取得
	DirectX::XMFLOAT3 Getdirection() const;
	
	// ビュー行列の更新処理
	virtual void UpdateViewMatrix() = 0; 
	// ビュー行列取得
	DirectX::XMFLOAT4X4 GetViewMatrix() const;

protected:
	DirectX::XMFLOAT3 position;		// 位置
	DirectX::XMFLOAT3 rotation;		// 回転
	DirectX::XMFLOAT3 direction;	// 向き
	DirectX::XMFLOAT3 up;			// 上方向
	DirectX::XMFLOAT4X4 viewMatrix;	// ビュー行列

};

