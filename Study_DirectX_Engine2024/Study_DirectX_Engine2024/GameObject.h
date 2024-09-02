#pragma once

#include <string>
#include <DirectXMath.h>

// ===================================
// 
//		オブジェクトの基底クラス
// 
// ===================================
class GameObject
{
public:
	// コンストラクタ・デストラクタ
	GameObject(const DirectX::XMFLOAT3& _position);

	GameObject() = default;
	virtual ~GameObject() = default;

	// 更新処理
	virtual void Update(float _deltaTime) = 0;
	// 描画処理
	virtual void Draw() const =0;

	void SetPosition(const DirectX::XMFLOAT3& _position);
	DirectX::XMFLOAT3 GetPosition() const;

protected:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scaling;

};

