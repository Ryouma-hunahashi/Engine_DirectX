#pragma once
#include "SceneBase.h"
class PauseScene : public SceneBase
{
public:
	PauseScene();
	~PauseScene();

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

#pragma endregion

};

