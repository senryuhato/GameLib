#pragma once
#include <windows.h>

// ���𑜓x�^�C�}�[
class HighResolutionTimer
{
public:
	HighResolutionTimer()
	{
		LONGLONG counts_per_sec;
		::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&counts_per_sec));
		secondsPerCount = 1.0 / static_cast<double>(counts_per_sec);

		::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&thisTime));
		baseTime = thisTime;
		lastTime = thisTime;
	}

	// Reset()���Ăяo����Ă���o�߂������v���Ԃ�Ԃ��܂��B
	float TimeStamp() const  // in seconds
	{
		// ��~���Ă���ꍇ�A��~���Ă���o�߂������Ԃ��J�E���g���܂���B
		// ����ɁA�ȑO���łɒ�~���Ă����ꍇ stopTime - baseTime �ɂ�
		// pausedTime�@���܂܂�Ă��邽�� mStopTime ���� pausedTime ��
		// ���Z���邱�ƂŏC�����܂��B
		//
		//                     |<--pausedTime-->|
		// ----*---------------*-----------------*------------*------------*------> time
		//  baseTime       stopTime        start_time     stopTime    thisTime

		if (stopped)
		{
			return static_cast<float>(((stopTime - pausedTime) - baseTime) * secondsPerCount);
		}

		// thisTime - mBaseTime �̊Ԃɂ� pausedTime ���܂܂�Ă��܂��B
		// ���̂��� thisTime ���� pausedTime �����Z���邱�ƂŏC�����܂��B
		//
		//  (thisTime - pausedTime) - baseTime 
		//
		//                     |<--pausedTime-->|
		// ----*---------------*-----------------*------------*------> time
		//  baseTime       stopTime        start_time     thisTime
		else
		{
			return static_cast<float>(((thisTime - pausedTime) - baseTime) * secondsPerCount);
		}
	}

	float TimeInterval() const  // in seconds
	{
		return static_cast<float>(deltaTime);
	}

	void Reset() // Call before message loop.
	{
		::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&thisTime));
		baseTime = thisTime;
		lastTime = thisTime;

		stopTime = 0;
		stopped = false;
	}

	void Start() // Call when unpaused.
	{
		LONGLONG startTime;
		::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));

		// �X�g�b�v����X�^�[�g�̊Ԃ̌o�ߎ��Ԃ�ݐς��܂��B
		//
		//                     |<-------d------->|
		// ----*---------------*-----------------*------------> time
		//  baseTime       stopTime        start_time     
		if (stopped)
		{
			pausedTime += (startTime - stopTime);
			lastTime = startTime;
			stopTime = 0;
			stopped = false;
		}
	}

	void Stop() // Call when paused.
	{
		if (!stopped)
		{
			::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&stopTime));
			stopped = true;
		}
	}

	void Tick() // Call every frame.
	{
		if (stopped)
		{
			deltaTime = 0.0;
			return;
		}

		::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&thisTime));
		// ���݂ƑO�̃t���[���Ƃ̎��ԍ�
		deltaTime = (thisTime - lastTime) * secondsPerCount;

		// ���̃t���[���̏���
		lastTime = thisTime;

		// �񕉂̋����l�BDXSDK��CDXUTTimer�́A�v���Z�b�T�͏ȓd�̓��[�h�ɓ��邩�A
		// �ʂ̂��̂ɃV���b�t�����ꂽ��ɁAmDeltaTime �͕��̒l�ɂȂ�\��������
		// ���Ƃ����y����Ă��܂��B
		if (deltaTime < 0.0)
		{
			deltaTime = 0.0;
		}
	}

private:
	double secondsPerCount = 0.0;
	double deltaTime = 0.0;

	LONGLONG baseTime = 0LL;
	LONGLONG pausedTime = 0LL;
	LONGLONG stopTime = 0LL;
	LONGLONG lastTime = 0LL;
	LONGLONG thisTime = 0LL;

	bool stopped{ false };
};