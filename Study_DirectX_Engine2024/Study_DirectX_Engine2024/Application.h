#pragma once

//-------------------------------------------
#include <Windows.h>
#include "Time.h"
#include "SceneManager.h"
#include "Input.h"
//-------------------------------------------

//-------------------------------------------
// 
// Applcationクラス
// 
// ウィンドウを生成・立ち上げるためのクラス
// 基本はここから開始することにする
// 
//-------------------------------------------

namespace Applib
{
	class Application
	{
	public:
		// コンストラクタ・デストラクタ
		Application(HINSTANCE _hInstance, int _width, int _height);
		~Application() = default;

		// 更新処理
		void Update(float _time);
		// 描画処理
		void Draw();
		

		// アプリケーション実行(ループ)処理
		void Loop();
		// アプリケーション終了処理
		void Terminaion();

		static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

		// 値取得、値設置
		static HWND GethWnd()	{ return m_hWnd; }			// ウィンドウハンドルを返す
		static int  GetWidth()	{ return m_ScreenWidth; }	// 画面の横サイズを返す
		static int  GetHeight() { return m_ScreenHeight; }	// 画面の縦サイズを返す
		static void SetWidth(int _Width)	{ m_ScreenWidth = _Width; }
		static void SetHeight(int _Height)	{ m_ScreenHeight = _Height; }

	private:

#pragma region Variables

		static WNDCLASSEX		m_wc;			// ウィンドウクラス
		static HWND				m_hWnd;			// ウィンドウハンドル
		static HINSTANCE		m_hInstance;	// インスタンスハンドル
		static int				m_ScreenWidth;	// 画面横サイズ
		static int				m_ScreenHeight;	// 画面縦サイズ
		Timelib::Time			m_time;			// タイムクラス変数
		SceneManager			m_sceneManager;	// シーン変数
		Input					m_input;		// 入力変数

#pragma endregion

	};
}
