#include "Application.h"
#include "DirectX.h"
#include "Time.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "GeometryDrawer.h"
#include "Sprite.h"
#include <iostream>

using namespace Applib;

HINSTANCE	Application::m_hInstance;
HWND		Application::m_hWnd;
WNDCLASSEX	Application::m_wc;
int			Application::m_ScreenWidth;
int			Application::m_ScreenHeight;
// DirectXのデバイスやコンテキストのポインタ
ID3D11Device* m_device = nullptr;
ID3D11DeviceContext* m_context = nullptr;
IDXGISwapChain* m_swapChain = nullptr;
ID3D11RenderTargetView* m_renderTargetView = nullptr;
ID3D11DepthStencilView* m_depthStenciView = nullptr;

Applib::Application::Application(HINSTANCE _hInstance, int _width, int _height)
{
	m_ScreenWidth = _width;		// 横サイズをセット
	m_ScreenHeight = _height;	// 縦サイズをセット
	m_hInstance = _hInstance;	// インスタンスハンドルをセット
	
	// ウィンドウクラスの情報設定
	ZeroMemory(&m_wc, sizeof(&m_wc));
	m_wc.style = CS_HREDRAW | CS_VREDRAW;				// ウィンドウスタイル
	m_wc.cbSize = sizeof(WNDCLASSEX);					// WNDCLASSEX構造体のサイズ
	m_wc.hInstance = m_hInstance;						// インスタンスハンドル
	m_wc.lpszClassName = "ClassName";					// Windowクラスの名前
	m_wc.lpszMenuName = "";								// メニューの名前
	m_wc.lpfnWndProc = WndProc;							// WndProcのアドレス ※後で関数を作成し、変更する
	m_wc.cbClsExtra = 0;								// 基本0固定
	m_wc.cbWndExtra = 0;								// 基本0固定
	m_wc.hCursor = LoadCursor(NULL,IDC_ARROW);			// マウスカーソル
	m_wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);		// 使用アイコン
	m_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	// 背景色

	// 情報が正しく登録されているか確認する
	if (!RegisterClassEx(&m_wc))
	{
		MessageBox(NULL, "Fail RegisterClassEx", "Error", MB_OK);
		return;
	}

	// ウィンドウのサイズを設定.
	RECT rc = {};
	rc.right = static_cast<LONG>(m_ScreenWidth);
	rc.bottom = static_cast<LONG>(m_ScreenHeight);

	// ウィンドウサイズを調整.
	auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&rc, style, FALSE);

	// ウィンドウを作成する
	m_hWnd = CreateWindowEx(
		0,
		m_wc.lpszClassName,
		NULL,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		m_hInstance,
		nullptr
	);

	// ウィンドウを表示
	ShowWindow(m_hWnd, SW_SHOWNORMAL);

	// ウィンドウを更新
	UpdateWindow(m_hWnd);

	// ウィンドウにフォーカスを設定する
	SetFocus(m_hWnd);

	std::cout << "Init" << std::endl;
}


void Applib::Application::Loop()
{
	HRESULT hr;

	//--- FPS制御
	//timeBeginPeriod(1);
	//DWORD countStartTime = timeGetTime();
	//DWORD preExecTime = countStartTime;

#pragma region Initializes

	// DirectXの初期化
	hr = DirectXManager::GetInstance().InitDirectX(m_hWnd, m_ScreenHeight, m_ScreenWidth,false);
	if (FAILED(hr)) { return; }

	GeometryDrawer::Init();
	Sprite::Init();

	// 入力の初期化
	bool input = m_input.Get()->Initialize(m_hWnd, m_hInstance);
	if (!input)
	{
		MessageBoxA(m_hWnd, "inputが正常に動作していないです", "", NULL);
	}

	//sceneの初期化・追加
	m_sceneManager.PushScene(std::make_unique<TitleScene>());
	m_sceneManager.PushScene(std::make_unique<MainScene>());

	std::cout << " Init End " << std::endl;

#pragma endregion

	MSG message{};

	// ループ処理
	for (;;)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&message, NULL, 0, 0))
			{
				break;
			}
			else
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{
			// 時間の更新
			m_time.Update();

			float deltaTime = m_time.GetDeltaTime();
			// 更新処理
			Update(deltaTime * 0.001f);
			// 描画処理
			Draw();

			
			//std::cout << deltaTime << std::endl;
								
		}
	}

}

void Applib::Application::Update(float _time)
{
	m_input.Get()->Update();
	m_sceneManager.Update(_time);
}

void Applib::Application::Draw()
{
	/* 後で変更する */
	// 背景色（RGBA）
	float backgroundColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 青みがかった色

	m_context = DirectXManager::GetInstance().GetContext();
	m_renderTargetView = DirectXManager::GetInstance().GetTargetView();
	m_depthStenciView = DirectXManager::GetInstance().GetStencilView();

	m_context->ClearRenderTargetView(m_renderTargetView, backgroundColor);
	m_context->ClearDepthStencilView(m_depthStenciView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_sceneManager.Draw();
//
//DirectX::XMFLOAT4X4 fmat;
//DirectX::XMStoreFloat4x4(&fmat, DirectX::XMMatrixIdentity());
//GeometryDrawer::SetWorld(fmat);
//GeometryDrawer::SetView(pCamera->GetView());
//GeometryDrawer::SetProjection(pCamera->GetProj());

	// 網掛け描画
	const int GridSize = 10;
	GeometryDrawer::SetColor(DirectX::XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f));
	for (int i = 1; i <= GridSize; ++i)
	{
		float g = (float)i;
		GeometryDrawer::AddLine(DirectX::XMFLOAT3(g, 0.0f, -GridSize), DirectX::XMFLOAT3(g, 0.0f, GridSize));
		GeometryDrawer::AddLine(DirectX::XMFLOAT3(-g, 0.0f, -GridSize), DirectX::XMFLOAT3(-g, 0.0f, GridSize));
		GeometryDrawer::AddLine(DirectX::XMFLOAT3(-GridSize, 0.0f, g), DirectX::XMFLOAT3(GridSize, 0.0f, g));
		GeometryDrawer::AddLine(DirectX::XMFLOAT3(-GridSize, 0.0f, -g), DirectX::XMFLOAT3(GridSize, 0.0f, -g));
	}
	// 軸描画
	GeometryDrawer::SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	GeometryDrawer::AddLine(DirectX::XMFLOAT3(-GridSize, 0.0f, 0.0f), DirectX::XMFLOAT3(GridSize, 0.0f, 0.0f));
	GeometryDrawer::SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	GeometryDrawer::AddLine(DirectX::XMFLOAT3(0.0f, -GridSize, 0.0f), DirectX::XMFLOAT3(0.0f, GridSize, 0.0f));
	GeometryDrawer::SetColor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	GeometryDrawer::AddLine(DirectX::XMFLOAT3(0.0f, 0.0f, -GridSize), DirectX::XMFLOAT3(0.0f, 0.0f, GridSize));

	GeometryDrawer::DrawLines();

	GeometryDrawer::DrawBox();

	// スワップチェイン
	DirectXManager::GetInstance().SwapDirectX();
}

void Applib::Application::Terminaion()
{
}

LRESULT CALLBACK Applib::Application::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(_hWnd, _message, _wParam, _lParam);
}
