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
	currentTime = std::chrono::steady_clock::now(); // ���݂̎��Ԃ��擾
	std::chrono::duration<float> elapsed = currentTime - previousTime; // �O�̃t���[������̌o�ߎ��Ԃ��v�Z
	deltaTime = elapsed.count(); // �o�ߎ��Ԃ�b�P�ʂŎ擾
	totalTime += deltaTime; // ���o�ߎ��Ԃ��X�V
	previousTime = currentTime; // ���݂̎��Ԃ�O�̃t���[���̎��ԂƂ��ĕۑ�
	frameCount++; // �t���[�������C���N�������g

	// �t���[�����[�g���v�Z�i1�b��1��X�V�j
	if (totalTime >= 1.0f)
	{
		CalculateFrameRate(); // �t���[�����[�g���v�Z

		// FPS��\������
		char str[32];
		wsprintfA(str, "FPS=%d", frameCount);
		SetWindowTextA(Applib::Application::GethWnd(), str);

		totalTime = 0.0f; // ���o�ߎ��Ԃ����Z�b�g
		frameCount = 0; // �t���[���������Z�b�g
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
		// �t���[�����𑍌o�ߎ��ԂŊ����ăt���[�����[�g���v�Z
		frameRate = static_cast<float>(frameCount) / totalTime;
	}
	else
	{
		// ���o�ߎ��Ԃ�0�̏ꍇ�A�t���[�����[�g��0
		frameRate = 0.0f;
	}
}
