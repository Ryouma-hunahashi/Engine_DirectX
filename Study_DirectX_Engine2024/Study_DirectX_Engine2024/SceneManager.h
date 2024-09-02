#pragma once

#include <memory>
#include <stack>
#include "SceneBase.h"
#include "CameraMain.h"

/// <summary>
/// Scene管理クラス
/// </summary>
class SceneManager
{
private:

	// シーンスタック
	std::stack<std::unique_ptr<SceneBase>> sceneStack;
	CameraMain* camera;

public:
	SceneManager() = default;
	~SceneManager() = default;

	// シーンの追加
	void PushScene(std::unique_ptr<SceneBase> _scene)
	{
		if (!sceneStack.empty())
		{
			sceneStack.top()->Finalize(); // 今あるシーンを終了する
		}
		sceneStack.push(std::move(_scene)); // シーンを追加する
		sceneStack.top()->Initialize();	// 追加したシーンの初期化を行う
	}

	// シーンの削除
	void PopScene()
	{
		if (!sceneStack.empty())
		{
			sceneStack.top()->Finalize(); // シーンを終了する
			sceneStack.pop();
		}
		if(!sceneStack.empty())
		{
			sceneStack.top()->Initialize(); // 次のシーンの初期化を行う
		}
	}

	// 更新処理
	void Update(float _deltaTime)
	{

		// スタックの一番最初の更新処理を行う
		if (!sceneStack.empty())
		{
			sceneStack.top()->Update(_deltaTime);
		}
	}

	// 描画処理
	void Draw()
	{

		// スタックの一番最初の描画処理を行う
		if(!sceneStack.empty())
		{
			sceneStack.top()->Draw();
		}
	}

};

