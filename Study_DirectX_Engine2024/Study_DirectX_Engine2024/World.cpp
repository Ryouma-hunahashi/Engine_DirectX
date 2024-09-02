#include "World.h"

World::World(int _Width, int _Height, int _depth)
	:width(_Width), height(_Height), depth(_depth)
{
	blocks.reserve(width * height * depth);

	// �ex, z���W�ɑ΂��Ēn�`�𐶐�
	for (int x = 0; x < width; x++)
	{
		for (int z = 0; z < depth; z++)
		{
			int terrainHeight = height / 2; // �Œ�̍�����ݒ�i�n�ʂ̍����𒆊Ԃɐݒ�j

			// ���肵�������܂Ńu���b�N��z�u
			for (int y = 0; y <= terrainHeight; ++y)
			{
				//SetBlockAt(x, y, z, BlockType::DIRT); // �����܂ő��u���b�N��z�u
				BlockType type = (y == terrainHeight) ? BlockType::DIRT : BlockType::DIRT;
				DirectX::XMFLOAT3 position(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
				blocks.emplace_back(type, position);
			}
		}
	}
}

void World::Update(float _deltaTime)
{
	for (auto object : gameObjects)
	{
		object->Update(_deltaTime);
	}
}

void World::Draw() const
{
	for (const auto& block : blocks)
	{
		block.Draw();
	}
	for (const auto& object : gameObjects)
	{
		object->Draw();
	}
}

Block* World::GetBlockAt(int _x, int _y, int _z)
{
	if (_x >= 0 && _x < width && _y >= 0 && _y < height && _z >= 0 && _z < depth) 
	{
		return &blocks[_x + _y * width + _z * width * height];
	}

	return nullptr;
}

void World::SetBlockAt(int _x, int _y, int _z, BlockType _type)
{
	Block* block = GetBlockAt(_x, _y, _z);
	if (block)
	{
		block->SetType(_type);
	}
}

void World::AddGameObject(GameObject* _object)
{
	gameObjects.push_back(_object);
}

void World::RemoveGameObject(GameObject* _object)
{
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), _object), gameObjects.end());
}
