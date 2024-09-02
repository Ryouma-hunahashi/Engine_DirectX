#pragma once
#include "SceneBase.h"
class TitleScene : public SceneBase
{
public:
	// コンストラクタ・デストラクタ
	TitleScene();
	virtual ~TitleScene();
	
	// 初期化処理
	void Initialize() override;
	// 更新処理
	void Update(float _deltaTime) override;
	// 描画処理
	void Draw() override;
	// 終了処理
	void Finalize() override;

private:
#pragma region Variables

#pragma endregion

};

