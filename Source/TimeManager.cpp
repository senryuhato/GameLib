#include "TimeManager.h"
#include "../GameXLib/System/Classes/SystemServiceLocator.h"
#include "../GameXLib/System/Classes/HighResolutionTimer.h"

#pragma region �X�V����
/// <summary>
/// �X�V����
/// </summary>
void TimeManager::Update()
{
	std::shared_ptr<HighResolutionTimer> highResolutionTimer = SystemServiceLocator::GetService<HighResolutionTimer>();
	float elapsedTime = highResolutionTimer->TimeInterval();
	// 1�t���[��������̍ő�b���w��
	const float limitElapsedTime = 1.0f / 5;
	this->elapsedTime = elapsedTime > limitElapsedTime ? limitElapsedTime : elapsedTime;
}
#pragma endregion
