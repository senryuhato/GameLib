#pragma once

/// <summary>
/// 時間管理
/// </summary>
class TimeManager
{
public:
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// フレーム間秒数の取得
	/// </summary>
	/// <returns></returns>
	float GetElapsedTime() { return elapsedTime; }
private:
	// フレーム間秒数
	float elapsedTime = 0.0f;
};