#pragma once

#include <vector>
#include "GameObject.h"
#include "Block.h"

class World
{
public:
	// コンストラクタ
	World(int _Width, int _Height, int _depth);

	// 更新処理
	void Update(float _deltaTime);
	// 描画処理
	void Draw() const;

	// 指定座標のブロック取得
	Block* GetBlockAt(int _x, int _y, int _z);
	// 指定座標にブロック設定
	void SetBlockAt(int _x, int _y, int _z, BlockType _type);
	// オブジェクト追加	
	void AddGameObject(GameObject* _object);
	// オブジェクト削除
	void RemoveGameObject(GameObject* _object);

private:
	int width, height, depth;
	std::vector<Block> blocks;
	std::vector<GameObject*> gameObjects;

};

