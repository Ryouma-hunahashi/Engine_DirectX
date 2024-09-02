#pragma once

#include <vector>
#include "GameObject.h"
#include "Block.h"

class World
{
public:
	// �R���X�g���N�^
	World(int _Width, int _Height, int _depth);

	// �X�V����
	void Update(float _deltaTime);
	// �`�揈��
	void Draw() const;

	// �w����W�̃u���b�N�擾
	Block* GetBlockAt(int _x, int _y, int _z);
	// �w����W�Ƀu���b�N�ݒ�
	void SetBlockAt(int _x, int _y, int _z, BlockType _type);
	// �I�u�W�F�N�g�ǉ�	
	void AddGameObject(GameObject* _object);
	// �I�u�W�F�N�g�폜
	void RemoveGameObject(GameObject* _object);

private:
	int width, height, depth;
	std::vector<Block> blocks;
	std::vector<GameObject*> gameObjects;

};

