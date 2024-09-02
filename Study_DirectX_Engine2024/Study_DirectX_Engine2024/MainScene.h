#pragma once
#include "SceneBase.h"
#include "World.h"

class MainScene : public SceneBase
{
public:
	MainScene();
	virtual ~MainScene();

	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float _deltaTime) override;
	// �`�揈��
	void Draw() override;
	// �I������
	void Finalize() override;

private:
#pragma region Variables
	World world;

#pragma endregion

};

