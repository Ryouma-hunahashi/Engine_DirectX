#include "Input.h"
#include "Application.h"
#include <Windows.h>
#include <d3d11.h>
#include "DirectX.h"

using namespace Applib;

bool Input::Initialize(HWND _hWnd, HINSTANCE _hInstance)
{
#pragma region CreateDevice
    // インプットデバイス作成
    result = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&input, NULL);
    if (FAILED(result)) { return false; }

    // キーボードデバイス作成
    result = input->CreateDevice(GUID_SysKeyboard, &lpkeyboard, NULL);
    if (FAILED(result)) { return false; }

    // マウスデバイス作成
    result = input->CreateDevice(GUID_SysMouse, &lpMouse, NULL);
    if (FAILED(result)) { return false; }
#pragma endregion

#pragma region SetDataFormat
    // キーボードフォーマット設定
    result = lpkeyboard->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(result)) { return false; }

    // マウスフォーマット設定
    result = lpMouse->SetDataFormat(&c_dfDIMouse);
    if (FAILED(result)) { return false; }
#pragma endregion

#pragma region SetCooperative
    // キーボード協調モード設定
    result = lpkeyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    if (FAILED(result)) { return false; }

    // マウス協調モード設定
    result = lpMouse->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    if (FAILED(result)) { return false; }
#pragma endregion

#pragma region Acquire
    // 入力デバイス開始
    lpkeyboard->Acquire();
    lpMouse->Acquire();
#pragma endregion

    return true;
}

void Input::Update()
{
    // 現在の状態を一次変数に保存
    XINPUT_STATE tempController[static_cast<int>(PlayerNumber::MAX)];
    ZeroMemory(&tempController, sizeof(tempController));

    // 状態を取得
    DWORD dwResult = XInputGetState(0, tempController);
    // コントローラー接続した時
    if (dwResult == ERROR_SUCCESS)
    {
        // コントローラー状態にする
        inputType = HIDType::CONTROLLER;
        // 1フレーム前の入力保存
        oldController[0] = controller[0];

        // 現在の入力保存する
        controller[0] = tempController[0];

    }
    else
    {
        // キーボード状態にする
        inputType = HIDType::KEYBOARDMOSUE;

        // １フレーム前のデータを保存
        memcpy_s(mOldKeyBuffer, sizeof(mOldKeyBuffer), mKeyBuffer, sizeof(mKeyBuffer));

        HRESULT hr;

        // キーボードの状態を取得する
        hr = lpkeyboard->GetDeviceState(sizeof(mKeyBuffer), &mKeyBuffer);

        if (FAILED(hr))
        {
            lpkeyboard->Acquire();
            lpkeyboard->GetDeviceState(sizeof(mKeyBuffer), &mKeyBuffer);
        }

        oldkeymouseState = keymouseState;

        hr = lpMouse->GetDeviceState(sizeof(keymouseState), &keymouseState);

        if (FAILED(hr))
        {
            lpMouse->Acquire();
            lpMouse->GetDeviceState(sizeof(keymouseState), &keymouseState);
        }
    }
}

bool Input::isKeyTrigger(InputControllerType _inputtype) const noexcept
{
    if (inputType != HIDType::CONTROLLER) { return false; }

    int buttonMask = tableController.at(_inputtype);
    
    bool nowCheck = controller[0].Gamepad.wButtons & buttonMask;
    bool oldCheck = oldController[0].Gamepad.wButtons & buttonMask;

    return nowCheck && !oldCheck;
}

bool Input::isKeyTrigger(InputKeyboardType _inputtype) const noexcept
{
    if (inputType != HIDType::KEYBOARDMOSUE) { return false; }

    auto itKey = tableKeyboard.find(_inputtype);

    if (itKey == tableKeyboard.end()) { return false; }

    bool nowCheck = mKeyBuffer[itKey->second] & 0x80;
    bool oldCheck = mOldKeyBuffer[itKey->second] & 0x80;

    return nowCheck && !oldCheck;
}

bool Input::isKeyTrigger(InputMouseType _inputtype) const noexcept
{
    if (inputType != HIDType::KEYBOARDMOSUE) { return false; }

    auto itKey = tableMouse.find(_inputtype);

    bool nowCheck = keymouseState.rgbButtons[itKey->second] & 0x80;
    bool oldCheck = oldkeymouseState.rgbButtons[itKey->second] & 0x80;

    return nowCheck && !oldCheck;
}

bool Input::isKeyPress(InputControllerType _inputtype) const noexcept
{
    if (inputType != HIDType::CONTROLLER) { return false; }

    int buttonMask = tableController.at(_inputtype);

    bool isButton = (controller[0].Gamepad.wButtons & buttonMask) != 0;

    return isButton;
}

bool Input::isKeyPress(InputKeyboardType _inputtype) const noexcept
{
    if (inputType != HIDType::KEYBOARDMOSUE) { return false; }

    auto it = tableKeyboard.find(_inputtype);
    if (it == tableKeyboard.end()) { return false; }

    bool isPressed = mKeyBuffer[it->second] & 0x80;

    return isPressed;
}

bool Input::isKeyPress(InputMouseType _inputtype) const noexcept
{
    if (inputType != HIDType::KEYBOARDMOSUE) { return false; }

    auto it = tableMouse.find(_inputtype);
    if (it == tableMouse.end()) { return false; }

    bool isPressed = keymouseState.rgbButtons[it->second] & 0x80;

    return isPressed;
}

DirectX::XMFLOAT2 Input::GetVertical(PadTrigger _triggertype)
{
    // コントローラーの座標を保存する変数
    DirectX::XMFLOAT2 padThumb = { 0,0 };

    switch (_triggertype)
    {
    case PadTrigger::LTrigger: // 左トリガーの場合
        padThumb.x = controller->Gamepad.sThumbLX;
        padThumb.y = controller->Gamepad.sThumbLY;
        break;
    case PadTrigger::RTrigger: // 右トリガーの場合
        padThumb.x = controller->Gamepad.sThumbRX;
        padThumb.y = controller->Gamepad.sThumbRY;
        break;
    }

    padThumb.x = 0;

    return padThumb;
}

DirectX::XMFLOAT2 Input::GetHorizontal(PadTrigger _triggertype)
{
    // コントローラーの座標を保存する変数
    DirectX::XMFLOAT2 padThumb = { 0,0 };

    switch (_triggertype)
    {
    case PadTrigger::LTrigger: // 左トリガーの場合
        padThumb.x = controller->Gamepad.sThumbLX;
        padThumb.y = controller->Gamepad.sThumbLY;
        break;
    case PadTrigger::RTrigger: // 右トリガーの場合
        padThumb.x = controller->Gamepad.sThumbRX;
        padThumb.y = controller->Gamepad.sThumbRY;
        break;
    }

    padThumb.y = 0;

    return padThumb;
}

DirectX::XMFLOAT3 Input::GetMousePos()
{
    POINT p;
    // マウスカーソルの位置を取得する
    GetCursorPos(&p);
    // スクリーン上の座標に変換する
    ScreenToClient(Applib::Application::GethWnd(), &p);

    // スクリーン座標をビューボート座標に変換する
    D3D11_VIEWPORT viewport;
    UINT numViewports = 1;
    ID3D11DeviceContext* context = DirectXManager::GetInstance().GetContext();
    context->RSGetViewports(&numViewports, &viewport);

    float screenX = (2.0f * p.x / viewport.Width) - 1.0f;
    float screenY = 1.0f - (2.0f * p.y / viewport.Height); // 上下を反転

    // クリッピング空間の座標を設定
    DirectX::XMFLOAT3 screenPos(screenX, screenY, 1.0f); // Z=1.0f（遠い平面）

    // 逆ビュー・プロジェクション行列を計算
    DirectX::XMMATRIX invViewProj = DirectX::XMMatrixIdentity();
    //invViewProj = DirectX::XMMatrixInverse(nullptr, viewMatrix * projectionMatrix);

    // クリッピング空間の座標を4次元ベクトルに変換
    DirectX::XMVECTOR screenPosVec = DirectX::XMLoadFloat3(&screenPos);
    DirectX::XMVECTOR worldPosVec = DirectX::XMVector3TransformCoord(screenPosVec, invViewProj);

    // 3D空間の座標に変換
    DirectX::XMFLOAT3 worldPos;
    DirectX::XMStoreFloat3(&worldPos, worldPosVec);

    return worldPos;
}

POINT Input::GetMouseVelocity()
{
    POINT mouseVel;

    //現在のマウスの座標を取得する
    mouseVel.x = keymouseState.lX;
    mouseVel.y = keymouseState.lY;

    return mouseVel;
}
