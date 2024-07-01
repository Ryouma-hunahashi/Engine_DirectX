#include "Application.h"
#include "DirectX.h"

using namespace Mylib;

HINSTANCE	Application::m_hInstance;
HWND		Application::m_hWnd;
WNDCLASSEX	Application::m_wc;
int			Application::m_ScreenWidth;
int			Application::m_ScreenHeight;

Mylib::Application::Application(int _width, int _height)
{
	m_ScreenWidth = _width;		// 横サイズをセット
	m_ScreenHeight = _height;	// 縦サイズをセット
	
	// ウィンドウクラスの情報設定
	ZeroMemory(&m_wc, sizeof(&m_wc));
	m_wc.style = CS_HREDRAW | CS_VREDRAW;				// ウィンドウスタイル
	m_wc.cbSize = sizeof(WNDCLASSEX);					// WNDCLASSEX構造体のサイズ
	m_wc.hInstance = m_hInstance;						// インスタンスハンドル
	m_wc.lpszClassName = "ClassName";					// Windowクラスの名前
	m_wc.lpszMenuName = "";								// メニューの名前
	m_wc.lpfnWndProc = DefWindowProc;					// WndProcのアドレス ※後で関数を作成し、変更する
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


}

void Mylib::Application::Loop()
{
	// タイムの初期化

	// DirectXの初期化
	DirectX::GetInstance().InitDirectX(m_hWnd, m_ScreenHeight, m_ScreenWidth);
	// ループ処理
	for (;;)
	{

	}

}

void Mylib::Application::Terminaion()
{
}
