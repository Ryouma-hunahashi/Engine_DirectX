#include "CameraMain.h"
#include "Input.h"

void CameraMain::Init()
{
	yaw = 0.0f;
	pitch = 0.0f;
	moveSpeed = 5.0f;
	rotationSpeed = 0.005f;
}

void CameraMain::Rotate(float _dx, float _dy)
{
    // マウスの動きに基づいてヨーとピッチを更新
    yaw += _dx * rotationSpeed;
    pitch += _dy * rotationSpeed;

    // ピッチ角を制限（上下の向きすぎを防止）
    if (pitch > DirectX::XM_PIDIV2) pitch = DirectX::XM_PIDIV2;
    if (pitch < -DirectX::XM_PIDIV2) pitch = -DirectX::XM_PIDIV2;

    // カメラの向き（look）を更新
    look.x = cosf(pitch) * cosf(yaw);
    look.y = sinf(pitch);
    look.z = cosf(pitch) * sinf(yaw);

    // 正規化
    DirectX::XMVECTOR lookVec = DirectX::XMLoadFloat3(&look);
    lookVec = DirectX::XMVector3Normalize(lookVec);
    DirectX::XMStoreFloat3(&look, lookVec);
}

void CameraMain::MoveForward(float _distance)
{
}

void CameraMain::MoveRight(float _distance)
{
}

void CameraMain::UpdateViewMatrix()
{
    // カメラの位置ベクトル、向きベクトル、上方向ベクトルを使用してビュー行列を計算
    DirectX::XMVECTOR posVec = DirectX::XMLoadFloat3(&position);
    DirectX::XMVECTOR lookVec = DirectX::XMLoadFloat3(&look);
    DirectX::XMVECTOR upVec = DirectX::XMLoadFloat3(&up);

    // LookToLHは、カメラ位置（posVec）、カメラの見る方向（lookVec）、カメラの上方向（upVec）からビュー行列を計算します
    DirectX::XMMATRIX view = DirectX::XMMatrixLookToLH(posVec, lookVec, upVec);
    DirectX::XMStoreFloat4x4(&viewMatrix, view);
}

void CameraMain::Update(float _deltaTime)
{
    // カメラの移動速度
    float speed = 5.0f * _deltaTime;

    // 前進・後退の処理
    if (Applib::Input::Get()->isKeyPress(Applib::InputKeyboardType::W)) {
        position.z += speed;
    }
    if (Applib::Input::Get()->isKeyPress(Applib::InputKeyboardType::S)) {
        position.z -= speed;
    }

    // 左右移動の処理
    if (Applib::Input::Get()->isKeyPress(Applib::InputKeyboardType::A)) {
        position.x -= speed;
    }
    if (Applib::Input::Get()->isKeyPress(Applib::InputKeyboardType::D)) {
        position.x += speed;
    }

    // マウスの移動に基づくカメラの向き変更
    POINT mouseDelta = Applib::Input::Get()->GetMouseVelocity();

    /* error this->nullptr */
    //rotation.y += mouseDelta.x * 0.1f * _deltaTime; // 回転の速さを調整
    //rotation.x -= mouseDelta.y * 0.1f * _deltaTime;

    // カメラのビュー行列を更新
    //UpdateViewMatrix();
}
