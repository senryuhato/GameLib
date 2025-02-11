#include "TimeManager.h"
#include "../GameXLib/System/Classes/SystemServiceLocator.h"
#include "../GameXLib/System/Classes/HighResolutionTimer.h"

#pragma region 更新処理
/// <summary>
/// 更新処理
/// </summary>
void TimeManager::Update()
{
	std::shared_ptr<HighResolutionTimer> highResolutionTimer = SystemServiceLocator::GetService<HighResolutionTimer>();
	float elapsedTime = highResolutionTimer->TimeInterval();
	// 1フレーム当たりの最大秒数指定
	const float limitElapsedTime = 1.0f / 5;
	this->elapsedTime = elapsedTime > limitElapsedTime ? limitElapsedTime : elapsedTime;
}
#pragma endregion
