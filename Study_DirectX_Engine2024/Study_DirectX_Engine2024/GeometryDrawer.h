#pragma once

#include <Windows.h>
#include <DirectXMath.h>
#include <memory>
#include "Shader.h"
#include "Mesh.h"

// 基本的な図形描画を行うユーティリティクラス
class GeometryDrawer
{
public:
    // 初期化関数
    static void Init();
    // 終了処理関数
    static void Uninit();

    // シェーダー設定関数
    static void SetVertexShader(VertexShader* _vs);
    static void SetPixelShader(PixelShader* _ps);

    // 変換行列設定関数
    static void SetWorld(DirectX::XMFLOAT4X4 _world);
    static void SetView(DirectX::XMFLOAT4X4 _view);
    static void SetProjection(DirectX::XMFLOAT4X4 _proj);

    // 描画パラメータ設定関数
    static void SetColor(DirectX::XMFLOAT4 _color);
    static void SetLightDirection(DirectX::XMFLOAT3 _dir);
    static void EnableLight(bool _enable);

    // 線の追加関数
    static void AddLine(DirectX::XMFLOAT3 _start, DirectX::XMFLOAT3 _end);
    static void AddLine(
        DirectX::XMFLOAT3 _startPos, DirectX::XMFLOAT4 _startColor,
        DirectX::XMFLOAT3 _endPos, DirectX::XMFLOAT4 _endColor);

    // 描画関数
    static void DrawLines();
    static void DrawBox();
    static void DrawSphere();

private:
    // シェーダー作成関数
    static void CreateVertexShader();
    static void CreatePixelShader();

    // メッシュ作成関数
    static void CreateLineMesh();
    static void CreateBoxMesh();
    static void CreateSphereMesh();

    // 頂点構造体
    struct Vertex
    {
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT4 color;
        DirectX::XMFLOAT3 normal;
    };

    // 内部データ構造体
    struct InternalData
    {
        static const int MAX_LINES = 10000*2;
        std::shared_ptr<VertexShader> defaultVS;
        std::shared_ptr<PixelShader> defaultPS;
        VertexShader* currentVS;
        PixelShader* currentPS;
        DirectX::XMFLOAT4X4 matrices[3]; // World, View, Projection
        DirectX::XMFLOAT4 parameters[2]; // Color, LightDirection
        Vertex lineVertices[MAX_LINES]; // 1ライン2頂点
        UINT lineCount;
        std::shared_ptr<Mesh> lineMesh;
        std::shared_ptr<Mesh> boxMesh;
        std::shared_ptr<Mesh> sphereMesh;
    };

    static InternalData m_data;
};