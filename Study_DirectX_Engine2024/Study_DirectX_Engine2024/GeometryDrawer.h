#pragma once

#include <Windows.h>
#include <DirectXMath.h>
#include <memory>
#include "Shader.h"
#include "Mesh.h"

// ��{�I�Ȑ}�`�`����s�����[�e�B���e�B�N���X
class GeometryDrawer
{
public:
    // �������֐�
    static void Init();
    // �I�������֐�
    static void Uninit();

    // �V�F�[�_�[�ݒ�֐�
    static void SetVertexShader(VertexShader* _vs);
    static void SetPixelShader(PixelShader* _ps);

    // �ϊ��s��ݒ�֐�
    static void SetWorld(DirectX::XMFLOAT4X4 _world);
    static void SetView(DirectX::XMFLOAT4X4 _view);
    static void SetProjection(DirectX::XMFLOAT4X4 _proj);

    // �`��p�����[�^�ݒ�֐�
    static void SetColor(DirectX::XMFLOAT4 _color);
    static void SetLightDirection(DirectX::XMFLOAT3 _dir);
    static void EnableLight(bool _enable);

    // ���̒ǉ��֐�
    static void AddLine(DirectX::XMFLOAT3 _start, DirectX::XMFLOAT3 _end);
    static void AddLine(
        DirectX::XMFLOAT3 _startPos, DirectX::XMFLOAT4 _startColor,
        DirectX::XMFLOAT3 _endPos, DirectX::XMFLOAT4 _endColor);

    // �`��֐�
    static void DrawLines();
    static void DrawBox();
    static void DrawSphere();

private:
    // �V�F�[�_�[�쐬�֐�
    static void CreateVertexShader();
    static void CreatePixelShader();

    // ���b�V���쐬�֐�
    static void CreateLineMesh();
    static void CreateBoxMesh();
    static void CreateSphereMesh();

    // ���_�\����
    struct Vertex
    {
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT4 color;
        DirectX::XMFLOAT3 normal;
    };

    // �����f�[�^�\����
    struct InternalData
    {
        static const int MAX_LINES = 10000*2;
        std::shared_ptr<VertexShader> defaultVS;
        std::shared_ptr<PixelShader> defaultPS;
        VertexShader* currentVS;
        PixelShader* currentPS;
        DirectX::XMFLOAT4X4 matrices[3]; // World, View, Projection
        DirectX::XMFLOAT4 parameters[2]; // Color, LightDirection
        Vertex lineVertices[MAX_LINES]; // 1���C��2���_
        UINT lineCount;
        std::shared_ptr<Mesh> lineMesh;
        std::shared_ptr<Mesh> boxMesh;
        std::shared_ptr<Mesh> sphereMesh;
    };

    static InternalData m_data;
};