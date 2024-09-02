#pragma once

#include <memory>
#include <stack>
#include "SceneBase.h"
#include "CameraMain.h"

/// <summary>
/// Scene�Ǘ��N���X
/// </summary>
class SceneManager
{
private:

	// �V�[���X�^�b�N
	std::stack<std::unique_ptr<SceneBase>> sceneStack;
	CameraMain* camera;

public:
	SceneManager() = default;
	~SceneManager() = default;

	// �V�[���̒ǉ�
	void PushScene(std::unique_ptr<SceneBase> _scene)
	{
		if (!sceneStack.empty())
		{
			sceneStack.top()->Finalize(); // ������V�[�����I������
		}
		sceneStack.push(std::move(_scene)); // �V�[����ǉ�����
		sceneStack.top()->Initialize();	// �ǉ������V�[���̏��������s��
	}

	// �V�[���̍폜
	void PopScene()
	{
		if (!sceneStack.empty())
		{
			sceneStack.top()->Finalize(); // �V�[�����I������
			sceneStack.pop();
		}
		if(!sceneStack.empty())
		{
			sceneStack.top()->Initialize(); // ���̃V�[���̏��������s��
		}
	}

	// �X�V����
	void Update(float _deltaTime)
	{

		// �X�^�b�N�̈�ԍŏ��̍X�V�������s��
		if (!sceneStack.empty())
		{
			sceneStack.top()->Update(_deltaTime);
		}
	}

	// �`�揈��
	void Draw()
	{

		// �X�^�b�N�̈�ԍŏ��̕`�揈�����s��
		if(!sceneStack.empty())
		{
			sceneStack.top()->Draw();
		}
	}

};

