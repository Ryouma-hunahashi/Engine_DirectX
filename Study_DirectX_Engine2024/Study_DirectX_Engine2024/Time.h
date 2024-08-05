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
#include <chrono>

namespace Mylib
{
	class Time
	{
	public:
		Time();

		// 時間リセット
		void Reset();
		// 時間更新
		void Update();
		
		// 経過時間取得
		float GetDeltaTime() const;
		// 総経過時間取得
		float GetTotalTime() const;
		// フレームレート取得
		float GetFrameRate() const;

	private:
		// 前回のフレーム時間
		std::chrono::steady_clock::time_point previousTime;
		// 現在のフレーム時間
		std::chrono::steady_clock::time_point currentTime;
		// フレームの経過時間
		float deltaTime;
		// フレームの総経過時間
		float totalTime;
		// フレーム数
		unsigned int frameCount;
		// フレームレート
		float frameRate;

		// フレームレート計算
		void CalculateFrameRate();

	};
}
