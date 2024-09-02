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
// DirectX�̃f�o�C�X��R���e�L�X�g�̃|�C���^
ID3D11Device* m_device = nullptr;
ID3D11DeviceContext* m_context = nullptr;
IDXGISwapChain* m_swapChain = nullptr;
ID3D11RenderTargetView* m_renderTargetView = nullptr;
ID3D11DepthStencilView* m_depthStenciView = nullptr;

Applib::Application::Application(HINSTANCE _hInstance, int _width, int _height)
{
	m_ScreenWidth = _width;		// ���T�C�Y���Z�b�g
	m_ScreenHeight = _height;	// �c�T�C�Y���Z�b�g
	m_hInstance = _hInstance;	// �C���X�^���X�n���h�����Z�b�g
	
	// �E�B���h�E�N���X�̏��ݒ�
	ZeroMemory(&m_wc, sizeof(&m_wc));
	m_wc.style = CS_HREDRAW | CS_VREDRAW;				// �E�B���h�E�X�^�C��
	m_wc.cbSize = sizeof(WNDCLASSEX);					// WNDCLASSEX�\���̂̃T�C�Y
	m_wc.hInstance = m_hInstance;						// �C���X�^���X�n���h��
	m_wc.lpszClassName = "ClassName";					// Window�N���X�̖��O
	m_wc.lpszMenuName = "";								// ���j���[�̖��O
	m_wc.lpfnWndProc = WndProc;							// WndProc�̃A�h���X ����Ŋ֐����쐬���A�ύX����
	m_wc.cbClsExtra = 0;								// ��{0�Œ�
	m_wc.cbWndExtra = 0;								// ��{0�Œ�
	m_wc.hCursor = LoadCursor(NULL,IDC_ARROW);			// �}�E�X�J�[�\��
	m_wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);		// �g�p�A�C�R��
	m_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	// �w�i�F

	// ��񂪐������o�^����Ă��邩�m�F����
	if (!RegisterClassEx(&m_wc))
	{
		MessageBox(NULL, "Fail RegisterClassEx", "Error", MB_OK);
		return;
	}

	// �E�B���h�E�̃T�C�Y��ݒ�.
	RECT rc = {};
	rc.right = static_cast<LONG>(m_ScreenWidth);
	rc.bottom = static_cast<LONG>(m_ScreenHeight);

	// �E�B���h�E�T�C�Y�𒲐�.
	auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&rc, style, FALSE);

	// �E�B���h�E���쐬����
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

	// �E�B���h�E��\��
	ShowWindow(m_hWnd, SW_SHOWNORMAL);

	// �E�B���h�E���X�V
	UpdateWindow(m_hWnd);

	// �E�B���h�E�Ƀt�H�[�J�X��ݒ肷��
	SetFocus(m_hWnd);

	std::cout << "Init" << std::endl;
}


void Applib::Application::Loop()
{
	HRESULT hr;

	//--- FPS����
	//timeBeginPeriod(1);
	//DWORD countStartTime = timeGetTime();
	//DWORD preExecTime = countStartTime;

#pragma region Initializes

	// DirectX�̏�����
	hr = DirectXManager::GetInstance().InitDirectX(m_hWnd, m_ScreenHeight, m_ScreenWidth,false);
	if (FAILED(hr)) { return; }

	GeometryDrawer::Init();
	Sprite::Init();

	// ���͂̏�����
	bool input = m_input.Get()->Initialize(m_hWnd, m_hInstance);
	if (!input)
	{
		MessageBoxA(m_hWnd, "input������ɓ��삵�Ă��Ȃ��ł�", "", NULL);
	}

	//scene�̏������E�ǉ�
	m_sceneManager.PushScene(std::make_unique<TitleScene>());
	m_sceneManager.PushScene(std::make_unique<MainScene>());

	std::cout << " Init End " << std::endl;

#pragma endregion

	MSG message{};

	// ���[�v����
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
			// ���Ԃ̍X�V
			m_time.Update();

			float deltaTime = m_time.GetDeltaTime();
			// �X�V����
			Update(deltaTime * 0.001f);
			// �`�揈��
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
	/* ��ŕύX���� */
	// �w�i�F�iRGBA�j
	float backgroundColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // �݂��������F

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

	// �Ԋ|���`��
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
	// ���`��
	GeometryDrawer::SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	GeometryDrawer::AddLine(DirectX::XMFLOAT3(-GridSize, 0.0f, 0.0f), DirectX::XMFLOAT3(GridSize, 0.0f, 0.0f));
	GeometryDrawer::SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	GeometryDrawer::AddLine(DirectX::XMFLOAT3(0.0f, -GridSize, 0.0f), DirectX::XMFLOAT3(0.0f, GridSize, 0.0f));
	GeometryDrawer::SetColor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	GeometryDrawer::AddLine(DirectX::XMFLOAT3(0.0f, 0.0f, -GridSize), DirectX::XMFLOAT3(0.0f, 0.0f, GridSize));

	GeometryDrawer::DrawLines();

	GeometryDrawer::DrawBox();

	// �X���b�v�`�F�C��
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
