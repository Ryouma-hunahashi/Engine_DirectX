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
	m_ScreenWidth = _width;		// ���T�C�Y���Z�b�g
	m_ScreenHeight = _height;	// �c�T�C�Y���Z�b�g
	
	// �E�B���h�E�N���X�̏��ݒ�
	ZeroMemory(&m_wc, sizeof(&m_wc));
	m_wc.style = CS_HREDRAW | CS_VREDRAW;				// �E�B���h�E�X�^�C��
	m_wc.cbSize = sizeof(WNDCLASSEX);					// WNDCLASSEX�\���̂̃T�C�Y
	m_wc.hInstance = m_hInstance;						// �C���X�^���X�n���h��
	m_wc.lpszClassName = "ClassName";					// Window�N���X�̖��O
	m_wc.lpszMenuName = "";								// ���j���[�̖��O
	m_wc.lpfnWndProc = DefWindowProc;					// WndProc�̃A�h���X ����Ŋ֐����쐬���A�ύX����
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


}

void Mylib::Application::Loop()
{
	// �^�C���̏�����

	// DirectX�̏�����
	DirectX::GetInstance().InitDirectX(m_hWnd, m_ScreenHeight, m_ScreenWidth);
	// ���[�v����
	for (;;)
	{

	}

}

void Mylib::Application::Terminaion()
{
}
