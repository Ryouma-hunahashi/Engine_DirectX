#undef UNICODE
#define _CRT_SECURE_NO_WARNINGS

// インクルード
#include "Application.h"
#include <iostream>
#include <stdio.h>

#define SCREENWIDTH	 (980)
#define SCREENHEIGHT (540)

using namespace Applib;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	if (AllocConsole())
	{
		std::freopen("CONOUT$", "w", stdout); // 標準出力をコンソールにリダイレクト
	}
	else
	{
		std::cerr << "Failed to allocate console" << std::endl;
	}
	Application app(hInstance, SCREENWIDTH, SCREENHEIGHT);
	app.Loop();

	return 0;
}