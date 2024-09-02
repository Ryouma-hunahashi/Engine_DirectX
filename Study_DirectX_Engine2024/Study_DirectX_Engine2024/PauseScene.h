#pragma once
#include "SceneBase.h"
class PauseScene : public SceneBase
{
public:
	PauseScene();
	~PauseScene();

	// ‰Šú‰»ˆ—
	void Initialize() override;
	// XVˆ—
	void Update(float _deltaTime) override;
	// •`‰æˆ—
	void Draw() override;
	// I—¹ˆ—
	void Finalize() override;

private:
#pragma region Variables

#pragma endregion

};

