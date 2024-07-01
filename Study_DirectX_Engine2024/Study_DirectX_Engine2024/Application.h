#pragma once

//-------------------------------------------
#include <Windows.h>
#include "Time.h"
//-------------------------------------------

//-------------------------------------------
// 
// Applcationクラス
// 
// ウィンドウを生成・立ち上げるためのクラス
// 基本はここから開始することにする
// 
//-------------------------------------------

namespace Mylib
{
	class Application
	{
	public:
		// コンストラクタ・デストラクタ
		Application(int _width, int _height);
		~Application(){}
		

		// アプリケーション実行(ループ)処理
		void Loop();
		// アプリケーション終了処理
		void Terminaion();

		// 値取得、値設置
		static HWND GethWnd()	{ return m_hWnd; }			// ウィンドウハンドルを返す
		static int  GetWidth()	{ return m_ScreenWidth; }	// 画面の横サイズを返す
		static int  GetHeight() { return m_ScreenHeight; }	// 画面の縦サイズを返す
		static void SetWidth(int _Width)	{ m_ScreenWidth = _Width; }
		static void SetHeight(int _Height)	{ m_ScreenHeight = _Height; }

		// 自身の変数
		//static Application instance;

	private:
		// 変数宣言
		static WNDCLASSEX	m_wc;			// ウィンドウクラス
		static HWND			m_hWnd;			// ウィンドウハンドル
		static HINSTANCE	m_hInstance;	// インスタンスハンドル
		static int			m_ScreenWidth;	// 画面横サイズ
		static int			m_ScreenHeight;	// 画面縦サイズ
		static Time			m_time;			// タイムクラス変数


	};
}
