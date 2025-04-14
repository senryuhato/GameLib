#include "Framework.h"
#include "../System/ServiceLocator.h"
#include "../Timer/HighResolutionTimer.h"
#include "../Timer/TimeManager.h"
#include "../Scene/SceneManager.h"

#pragma region ����������
/// <summary>
/// �R���X�g���N�^
/// </summary>
Framework::Framework()
{
	//// �e��}�l�[�W���[�̓o�^
	//// ���łɓo�^����Ă���ꍇ�͓o�^���Ȃ�
	//// �^�C�}�[
	//ServiceLocator::RegisterServiceIfNotExists<TimeManager>(ServiceNames::TIME_MANAGER);
	//// �V�[���Ǘ�
	//ServiceLocator::RegisterServiceIfNotExists<SceneManager>(ServiceNames::SCENE_MANAGER);
}
#pragma endregion

#pragma region �Q�[�����[�v
/// <summary>
/// �Q�[�����[�v
/// </summary>
void Framework::Run()
{
	//// �^�C�}�[�X�V
	//std::shared_ptr<TimeManager> timeManager = ServiceLocator::GetService<TimeManager>(ServiceNames::TIME_MANAGER);
	//if (timeManager)
	//{
	//	timeManager->Update();
	//}
	//
	//// �V�[���X�V
	//std::shared_ptr<SceneManager> sceneManager = ServiceLocator::GetService<SceneManager>(ServiceNames::SCENE_MANAGER);
	//if (sceneManager)
	//{
	//	sceneManager->Update();
	//	sceneManager->Render();
	//}
}
#pragma endregion

#pragma region �E�B���h�E���b�Z�[�W���������郁���o�֐��i�N���X���̃��b�Z�[�W�����j
/// <summary>
/// �E�B���h�E���b�Z�[�W���������郁���o�֐��i�N���X���̃��b�Z�[�W�����j
/// </summary>
/// <param name="hwnd">�E�B���h�E�n���h��</param>
/// <param name="msg">�󂯎�������b�Z�[�W</param>
/// <param name="wParam">���b�Z�[�W�̒ǉ����i1�ڂ̃p�����[�^�j</param>
/// <param name="lParam">���b�Z�[�W�̒ǉ����i2�ڂ̃p�����[�^�j</param>
/// <returns>���b�Z�[�W�������������ʁi�ʏ�� `DefWindowProc` �̖߂�l��Ԃ��j</returns>
LRESULT CALLBACK Framework::HandleMessage(
	_In_ HWND hwnd,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	// �^�C�}�[
	std::shared_ptr<HighResolutionTimer> highResolutionTimer = ServiceLocator::GetService<HighResolutionTimer>(ServiceNames::HIGH_RESOLUTION_TIMER);

	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps{};
		BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostMessage(hwnd, WM_CLOSE, 0, 0);
		}
		break;
	case WM_ENTERSIZEMOVE:
		if(highResolutionTimer) highResolutionTimer->Stop();
		break;
	case WM_EXITSIZEMOVE:
		if(highResolutionTimer) highResolutionTimer->Start();
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
#pragma endregion
