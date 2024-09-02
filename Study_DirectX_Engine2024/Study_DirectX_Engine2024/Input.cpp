#include "Input.h"
#include "Application.h"
#include <Windows.h>
#include <d3d11.h>
#include "DirectX.h"

using namespace Applib;

bool Input::Initialize(HWND _hWnd, HINSTANCE _hInstance)
{
#pragma region CreateDevice
    // �C���v�b�g�f�o�C�X�쐬
    result = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&input, NULL);
    if (FAILED(result)) { return false; }

    // �L�[�{�[�h�f�o�C�X�쐬
    result = input->CreateDevice(GUID_SysKeyboard, &lpkeyboard, NULL);
    if (FAILED(result)) { return false; }

    // �}�E�X�f�o�C�X�쐬
    result = input->CreateDevice(GUID_SysMouse, &lpMouse, NULL);
    if (FAILED(result)) { return false; }
#pragma endregion

#pragma region SetDataFormat
    // �L�[�{�[�h�t�H�[�}�b�g�ݒ�
    result = lpkeyboard->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(result)) { return false; }

    // �}�E�X�t�H�[�}�b�g�ݒ�
    result = lpMouse->SetDataFormat(&c_dfDIMouse);
    if (FAILED(result)) { return false; }
#pragma endregion

#pragma region SetCooperative
    // �L�[�{�[�h�������[�h�ݒ�
    result = lpkeyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    if (FAILED(result)) { return false; }

    // �}�E�X�������[�h�ݒ�
    result = lpMouse->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    if (FAILED(result)) { return false; }
#pragma endregion

#pragma region Acquire
    // ���̓f�o�C�X�J�n
    lpkeyboard->Acquire();
    lpMouse->Acquire();
#pragma endregion

    return true;
}

void Input::Update()
{
    // ���݂̏�Ԃ��ꎟ�ϐ��ɕۑ�
    XINPUT_STATE tempController[static_cast<int>(PlayerNumber::MAX)];
    ZeroMemory(&tempController, sizeof(tempController));

    // ��Ԃ��擾
    DWORD dwResult = XInputGetState(0, tempController);
    // �R���g���[���[�ڑ�������
    if (dwResult == ERROR_SUCCESS)
    {
        // �R���g���[���[��Ԃɂ���
        inputType = HIDType::CONTROLLER;
        // 1�t���[���O�̓��͕ۑ�
        oldController[0] = controller[0];

        // ���݂̓��͕ۑ�����
        controller[0] = tempController[0];

    }
    else
    {
        // �L�[�{�[�h��Ԃɂ���
        inputType = HIDType::KEYBOARDMOSUE;

        // �P�t���[���O�̃f�[�^��ۑ�
        memcpy_s(mOldKeyBuffer, sizeof(mOldKeyBuffer), mKeyBuffer, sizeof(mKeyBuffer));

        HRESULT hr;

        // �L�[�{�[�h�̏�Ԃ��擾����
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
    // �R���g���[���[�̍��W��ۑ�����ϐ�
    DirectX::XMFLOAT2 padThumb = { 0,0 };

    switch (_triggertype)
    {
    case PadTrigger::LTrigger: // ���g���K�[�̏ꍇ
        padThumb.x = controller->Gamepad.sThumbLX;
        padThumb.y = controller->Gamepad.sThumbLY;
        break;
    case PadTrigger::RTrigger: // �E�g���K�[�̏ꍇ
        padThumb.x = controller->Gamepad.sThumbRX;
        padThumb.y = controller->Gamepad.sThumbRY;
        break;
    }

    padThumb.x = 0;

    return padThumb;
}

DirectX::XMFLOAT2 Input::GetHorizontal(PadTrigger _triggertype)
{
    // �R���g���[���[�̍��W��ۑ�����ϐ�
    DirectX::XMFLOAT2 padThumb = { 0,0 };

    switch (_triggertype)
    {
    case PadTrigger::LTrigger: // ���g���K�[�̏ꍇ
        padThumb.x = controller->Gamepad.sThumbLX;
        padThumb.y = controller->Gamepad.sThumbLY;
        break;
    case PadTrigger::RTrigger: // �E�g���K�[�̏ꍇ
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
    // �}�E�X�J�[�\���̈ʒu���擾����
    GetCursorPos(&p);
    // �X�N���[����̍��W�ɕϊ�����
    ScreenToClient(Applib::Application::GethWnd(), &p);

    // �X�N���[�����W���r���[�{�[�g���W�ɕϊ�����
    D3D11_VIEWPORT viewport;
    UINT numViewports = 1;
    ID3D11DeviceContext* context = DirectXManager::GetInstance().GetContext();
    context->RSGetViewports(&numViewports, &viewport);

    float screenX = (2.0f * p.x / viewport.Width) - 1.0f;
    float screenY = 1.0f - (2.0f * p.y / viewport.Height); // �㉺�𔽓]

    // �N���b�s���O��Ԃ̍��W��ݒ�
    DirectX::XMFLOAT3 screenPos(screenX, screenY, 1.0f); // Z=1.0f�i�������ʁj

    // �t�r���[�E�v���W�F�N�V�����s����v�Z
    DirectX::XMMATRIX invViewProj = DirectX::XMMatrixIdentity();
    //invViewProj = DirectX::XMMatrixInverse(nullptr, viewMatrix * projectionMatrix);

    // �N���b�s���O��Ԃ̍��W��4�����x�N�g���ɕϊ�
    DirectX::XMVECTOR screenPosVec = DirectX::XMLoadFloat3(&screenPos);
    DirectX::XMVECTOR worldPosVec = DirectX::XMVector3TransformCoord(screenPosVec, invViewProj);

    // 3D��Ԃ̍��W�ɕϊ�
    DirectX::XMFLOAT3 worldPos;
    DirectX::XMStoreFloat3(&worldPos, worldPosVec);

    return worldPos;
}

POINT Input::GetMouseVelocity()
{
    POINT mouseVel;

    //���݂̃}�E�X�̍��W���擾����
    mouseVel.x = keymouseState.lX;
    mouseVel.y = keymouseState.lY;

    return mouseVel;
}
