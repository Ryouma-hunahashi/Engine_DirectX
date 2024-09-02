#pragma once
#include "GameObject.h"

enum class BlockType
{
	AIR,
	DIRT,
	MAX
};

class Block : public GameObject
{
public:
	// コンストラクタ
	Block(BlockType _type, const DirectX::XMFLOAT3& _position);

	BlockType GetType() const;
	void SetType(BlockType _type);

	// 更新処理
	void Update(float _deltaTime) override;
	// 描画処理
	void Draw() const override;

	bool IsSolid() const;

private:
	BlockType type;

public:
	Block() = default;
	~Block() = default;
};

