#undef UNICODE

// インクルード
#include "Application.h"

#define SCREENWIDTH	 (980)
#define SCREENHEIGHT (540)

using namespace Mylib;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	AllocConsole();
	Application app(SCREENWIDTH, SCREENHEIGHT);
	app.Loop();

	return 0;
}