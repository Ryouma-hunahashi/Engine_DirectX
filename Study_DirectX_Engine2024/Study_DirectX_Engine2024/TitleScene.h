#pragma once
#include "SceneBase.h"
class TitleScene : public SceneBase
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	TitleScene();
	virtual ~TitleScene();
	
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

