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
	// �R���X�g���N�^
	Block(BlockType _type, const DirectX::XMFLOAT3& _position);

	BlockType GetType() const;
	void SetType(BlockType _type);

	// �X�V����
	void Update(float _deltaTime) override;
	// �`�揈��
	void Draw() const override;

	bool IsSolid() const;

private:
	BlockType type;

public:
	Block() = default;
	~Block() = default;
};

