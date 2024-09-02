#include "Block.h"
#include "GeometryDrawer.h"

Block::Block(BlockType _type, const DirectX::XMFLOAT3& _position)
	: GameObject(_position),type(_type)
{
}



BlockType Block::GetType() const
{
	return type;
}

void Block::SetType(BlockType _type)
{
	this->type = _type;
}

void Block::Update(float _deltaTime)
{
}

void Block::Draw() const
{
	// �e�X�g�Ŏl�p��\��
	//GeometryDrawer::DrawBox();
}

bool Block::IsSolid() const
{
	return type != BlockType::AIR;
}
