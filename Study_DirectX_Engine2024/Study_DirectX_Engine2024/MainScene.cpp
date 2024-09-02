#include "MainScene.h"
#include "World.h"
#include "GeometryDrawer.h"
#include "CameraMain.h"

MainScene::MainScene() : world(100,50,100)
{
}

MainScene::~MainScene()
{
}

void MainScene::Initialize()
{
}

void MainScene::Update(float _deltaTime)
{
	world.Update(_deltaTime);
	
}

void MainScene::Draw()
{
	world.Draw();


	GeometryDrawer::SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	GeometryDrawer::DrawBox();
}

void MainScene::Finalize()
{
}
