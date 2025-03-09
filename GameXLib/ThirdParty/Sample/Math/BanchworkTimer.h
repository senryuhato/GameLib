#pragma once
#include <windows.h>

// ŽžŠÔŒv‘ª
class BenchmarkTimer
{
public:
	BenchmarkTimer()
	{
		QueryPerformanceFrequency(&ticks_per_second);
		QueryPerformanceCounter(&start_ticks);
		QueryPerformanceCounter(&current_ticks);
	}
	~BenchmarkTimer() = default;
	BenchmarkTimer(const BenchmarkTimer&) = delete;
	BenchmarkTimer& operator=(const BenchmarkTimer&) = delete;
	BenchmarkTimer(BenchmarkTimer&&) noexcept = delete;
	BenchmarkTimer& operator=(BenchmarkTimer&&) noexcept = delete;

	void Begin()
	{
		QueryPerformanceCounter(&start_ticks);
	}
	float End()
	{
		QueryPerformanceCounter(&current_ticks);
		return static_cast<float>(current_ticks.QuadPart - start_ticks.QuadPart) / static_cast<float>(ticks_per_second.QuadPart);
	}

private:
	LARGE_INTEGER ticks_per_second;
	LARGE_INTEGER start_ticks;
	LARGE_INTEGER current_ticks;
};
