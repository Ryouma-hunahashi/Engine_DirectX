#pragma once

//-------------------------------------------
#include <Windows.h>
#include "Time.h"
//-------------------------------------------

//-------------------------------------------
// 
// Applcation�N���X
// 
// �E�B���h�E�𐶐��E�����グ�邽�߂̃N���X
// ��{�͂�������J�n���邱�Ƃɂ���
// 
//-------------------------------------------

namespace Mylib
{
	class Application
	{
	public:
		// �R���X�g���N�^�E�f�X�g���N�^
		Application(int _width, int _height);
		~Application(){}
		

		// �A�v���P�[�V�������s(���[�v)����
		void Loop();
		// �A�v���P�[�V�����I������
		void Terminaion();

		// �l�擾�A�l�ݒu
		static HWND GethWnd()	{ return m_hWnd; }			// �E�B���h�E�n���h����Ԃ�
		static int  GetWidth()	{ return m_ScreenWidth; }	// ��ʂ̉��T�C�Y��Ԃ�
		static int  GetHeight() { return m_ScreenHeight; }	// ��ʂ̏c�T�C�Y��Ԃ�
		static void SetWidth(int _Width)	{ m_ScreenWidth = _Width; }
		static void SetHeight(int _Height)	{ m_ScreenHeight = _Height; }

		// ���g�̕ϐ�
		//static Application instance;

	private:
		// �ϐ��錾
		static WNDCLASSEX	m_wc;			// �E�B���h�E�N���X
		static HWND			m_hWnd;			// �E�B���h�E�n���h��
		static HINSTANCE	m_hInstance;	// �C���X�^���X�n���h��
		static int			m_ScreenWidth;	// ��ʉ��T�C�Y
		static int			m_ScreenHeight;	// ��ʏc�T�C�Y
		static Time			m_time;			// �^�C���N���X�ϐ�


	};
}
