#include "TimeManager.h"
#include "HighResolutionTimer.h"
#include "../System/ServiceLocator.h"

#pragma region �X�V����
/// <summary>
/// �X�V����
/// </summary>
void TimeManager::Update()
{
	std::shared_ptr<HighResolutionTimer> highResolutionTimer = ServiceLocator::GetService<HighResolutionTimer>(ServiceNames::HIGH_RESOLUTION_TIMER);
	float elapsedTime = highResolutionTimer->TimeInterval();
	// 1�t���[��������̍ő�b���w��
	const float limitElapsedTime = 1.0f / 5;
	this->elapsedTime = elapsedTime > limitElapsedTime ? limitElapsedTime : elapsedTime;
}
#pragma endregion
