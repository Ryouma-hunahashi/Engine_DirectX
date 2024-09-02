#include "World.h"

World::World(int _Width, int _Height, int _depth)
	:width(_Width), height(_Height), depth(_depth)
{
	blocks.reserve(width * height * depth);

	// 各x, z座標に対して地形を生成
	for (int x = 0; x < width; x++)
	{
		for (int z = 0; z < depth; z++)
		{
			int terrainHeight = height / 2; // 固定の高さを設定（地面の高さを中間に設定）

			// 決定した高さまでブロックを配置
			for (int y = 0; y <= terrainHeight; ++y)
			{
				//SetBlockAt(x, y, z, BlockType::DIRT); // 高さまで草ブロックを配置
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
