#pragma once

// -------------------------------------------
// 
// Time�N���X
// ���FPS�Œ肷��Ƃ���
// ���݂̎��Ԃ��擾����Ƃ��Ɏg�p����
// 
// -------------------------------------------

// timeGetTime����̎g�p
#pragma comment(lib, "winmm.lib")
#include <chrono>

namespace Mylib
{
	class Time
	{
	public:
		Time();

		// ���ԃ��Z�b�g
		void Reset();
		// ���ԍX�V
		void Update();
		
		// �o�ߎ��Ԏ擾
		float GetDeltaTime() const;
		// ���o�ߎ��Ԏ擾
		float GetTotalTime() const;
		// �t���[�����[�g�擾
		float GetFrameRate() const;

	private:
		// �O��̃t���[������
		std::chrono::steady_clock::time_point previousTime;
		// ���݂̃t���[������
		std::chrono::steady_clock::time_point currentTime;
		// �t���[���̌o�ߎ���
		float deltaTime;
		// �t���[���̑��o�ߎ���
		float totalTime;
		// �t���[����
		unsigned int frameCount;
		// �t���[�����[�g
		float frameRate;

		// �t���[�����[�g�v�Z
		void CalculateFrameRate();

	};
}
