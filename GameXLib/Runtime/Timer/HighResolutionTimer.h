#pragma once
#include <windows.h>

// 高解像度タイマー
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

	/// @brief 累計経過時間を取得
	/// @return Reset()が呼び出されてから経過した合計時間を返します。
	float TimeStamp() const  // in seconds
	{
		// 停止している場合、停止してから経過した時間をカウントしません。
		// さらに、以前すでに停止していた場合 stopTime - baseTime には
		// pausedTime　が含まれているため mStopTime から pausedTime を
		// 減算することで修正します。
		//
		//                     |<--pausedTime-->|
		// ----*---------------*-----------------*------------*------------*------> time
		//  baseTime       stopTime        start_time     stopTime    thisTime

		if(stopped)
		{
			return static_cast<float>(((stopTime - pausedTime) - baseTime) * secondsPerCount);
		}

		// thisTime - mBaseTime の間には pausedTime が含まれています。
		// そのため thisTime から pausedTime を減算することで修正します。
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

	/// @brief Tick間の時間を取得
	/// @return Tick間秒数
	float TimeInterval() const  // in seconds
	{
		return static_cast<float>(deltaTime);
	}

	/// @brief メッセージ ループの前に呼び出します。
	void Reset()
	{
		::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&thisTime));
		baseTime = thisTime;
		lastTime = thisTime;

		stopTime = 0;
		stopped = false;
	}

	/// @brief 一時停止が解除されたら呼び出します。
	void Start()
	{
		LONGLONG startTime;
		::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));

		// ストップからスタートの間の経過時間を累積します。
		//
		//                     |<-------d------->|
		// ----*---------------*-----------------*------------> time
		//  baseTime       stopTime        start_time     
		if(stopped)
		{
			pausedTime += (startTime - stopTime);
			lastTime = startTime;
			stopTime = 0;
			stopped = false;
		}
	}

	/// @brief 一時停止時に呼び出します。
	void Stop()
	{
		if(!stopped)
		{
			::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&stopTime));
			stopped = true;
		}
	}

	/// @brief すべてのフレームを呼び出します。
	void Tick()
	{
		if(stopped)
		{
			deltaTime = 0.0;
			return;
		}

		::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&thisTime));
		// 現在と前のフレームとの時間差
		deltaTime = (thisTime - lastTime) * secondsPerCount;

		// 次のフレームの準備
		lastTime = thisTime;

		// 非負の強制値。DXSDKのCDXUTTimerは、プロセッサは省電力モードに入るか、
		// 別のものにシャッフルされた後に、mDeltaTime は負の値になる可能性がある
		// ことが言及されています。
		if(deltaTime < 0.0)
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

	bool stopped{false};
};