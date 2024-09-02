#pragma once
#include "SceneBase.h"
#include "World.h"

class MainScene : public SceneBase
{
public:
	MainScene();
	virtual ~MainScene();

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
	World world;

#pragma endregion

};

