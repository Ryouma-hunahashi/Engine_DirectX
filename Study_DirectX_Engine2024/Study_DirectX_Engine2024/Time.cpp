#include "Time.h"

#include "Application.h"
#include <WinUser.h>


Timelib::Time::Time()
	:deltaTime(0.0f), totalTime(0.0f), frameCount(0), frameRate(0.0f)
{
	Reset();
}

void Timelib::Time::Reset()
{
	previousTime = std::chrono::steady_clock::now();
	totalTime = 0.0f;
	frameCount = 0;
	frameRate = 0.0f;
}

void Timelib::Time::Update()
{
	currentTime = std::chrono::steady_clock::now(); // 現在の時間を取得
	std::chrono::duration<float> elapsed = currentTime - previousTime; // 前のフレームからの経過時間を計算
	deltaTime = elapsed.count(); // 経過時間を秒単位で取得
	totalTime += deltaTime; // 総経過時間を更新
	previousTime = currentTime; // 現在の時間を前のフレームの時間として保存
	frameCount++; // フレーム数をインクリメント

	// フレームレートを計算（1秒に1回更新）
	if (totalTime >= 1.0f)
	{
		CalculateFrameRate(); // フレームレートを計算

		// FPSを表示する
		char str[32];
		wsprintfA(str, "FPS=%d", frameCount);
		SetWindowTextA(Applib::Application::GethWnd(), str);

		totalTime = 0.0f; // 総経過時間をリセット
		frameCount = 0; // フレーム数をリセット
	}
}

float Timelib::Time::GetDeltaTime() const
{
	return deltaTime;
}

float Timelib::Time::GetTotalTime() const
{
	return totalTime;
}

float Timelib::Time::GetFrameRate() const
{
	return frameRate;
}

void Timelib::Time::CalculateFrameRate()
{
	if (totalTime > 0.0f)
	{
		// フレーム数を総経過時間で割ってフレームレートを計算
		frameRate = static_cast<float>(frameCount) / totalTime;
	}
	else
	{
		// 総経過時間が0の場合、フレームレートは0
		frameRate = 0.0f;
	}
}
