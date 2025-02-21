#include "TimeManager.h"
#include "HighResolutionTimer.h"
#include "../System/ServiceLocator.h"

#pragma region 更新処理
/// <summary>
/// 更新処理
/// </summary>
void TimeManager::Update()
{
	std::shared_ptr<HighResolutionTimer> highResolutionTimer = ServiceLocator::GetService<HighResolutionTimer>();
	float elapsedTime = highResolutionTimer->TimeInterval();
	// 1フレーム当たりの最大秒数指定
	const float limitElapsedTime = 1.0f / 5;
	this->elapsedTime = elapsedTime > limitElapsedTime ? limitElapsedTime : elapsedTime;
}
#pragma endregion
