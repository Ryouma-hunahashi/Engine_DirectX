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
    // �}�E�X�̓����Ɋ�Â��ă��[�ƃs�b�`���X�V
    yaw += _dx * rotationSpeed;
    pitch += _dy * rotationSpeed;

    // �s�b�`�p�𐧌��i�㉺�̌���������h�~�j
    if (pitch > DirectX::XM_PIDIV2) pitch = DirectX::XM_PIDIV2;
    if (pitch < -DirectX::XM_PIDIV2) pitch = -DirectX::XM_PIDIV2;

    // �J�����̌����ilook�j���X�V
    look.x = cosf(pitch) * cosf(yaw);
    look.y = sinf(pitch);
    look.z = cosf(pitch) * sinf(yaw);

    // ���K��
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
    // �J�����̈ʒu�x�N�g���A�����x�N�g���A������x�N�g�����g�p���ăr���[�s����v�Z
    DirectX::XMVECTOR posVec = DirectX::XMLoadFloat3(&position);
    DirectX::XMVECTOR lookVec = DirectX::XMLoadFloat3(&look);
    DirectX::XMVECTOR upVec = DirectX::XMLoadFloat3(&up);

    // LookToLH�́A�J�����ʒu�iposVec�j�A�J�����̌�������ilookVec�j�A�J�����̏�����iupVec�j����r���[�s����v�Z���܂�
    DirectX::XMMATRIX view = DirectX::XMMatrixLookToLH(posVec, lookVec, upVec);
    DirectX::XMStoreFloat4x4(&viewMatrix, view);
}

void CameraMain::Update(float _deltaTime)
{
    // �J�����̈ړ����x
    float speed = 5.0f * _deltaTime;

    // �O�i�E��ނ̏���
    if (Applib::Input::Get()->isKeyPress(Applib::InputKeyboardType::W)) {
        position.z += speed;
    }
    if (Applib::Input::Get()->isKeyPress(Applib::InputKeyboardType::S)) {
        position.z -= speed;
    }

    // ���E�ړ��̏���
    if (Applib::Input::Get()->isKeyPress(Applib::InputKeyboardType::A)) {
        position.x -= speed;
    }
    if (Applib::Input::Get()->isKeyPress(Applib::InputKeyboardType::D)) {
        position.x += speed;
    }

    // �}�E�X�̈ړ��Ɋ�Â��J�����̌����ύX
    POINT mouseDelta = Applib::Input::Get()->GetMouseVelocity();

    /* error this->nullptr */
    //rotation.y += mouseDelta.x * 0.1f * _deltaTime; // ��]�̑����𒲐�
    //rotation.x -= mouseDelta.y * 0.1f * _deltaTime;

    // �J�����̃r���[�s����X�V
    //UpdateViewMatrix();
}
