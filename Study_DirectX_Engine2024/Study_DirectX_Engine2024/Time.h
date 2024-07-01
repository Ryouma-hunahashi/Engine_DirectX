#pragma once

// -------------------------------------------
// 
// Timeクラス
// 主にFPS固定するときや
// 現在の時間を取得するときに使用する
// 
// -------------------------------------------

// timeGetTime周りの使用
#pragma comment(lib, "winmm.lib")


namespace Mylib
{
	class Time
	{
	private:
		Time();
		~Time();
	};
}
