#pragma once
#include "SceneBase.h"
class LoadingScene : public SceneBase
{
public:
	LoadingScene();
	~LoadingScene();

	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float _deltaTime) override;
	// �`�揈��
	void Draw() override;
	// �I������
	void Finalize() override;

private:
#pragma region 

#pragma endregion

};

