#include "../Classes/Framework.h"
#include "../Classes/SystemServiceLocator.h"
#include "../Classes/HighResolutionTimer.h"

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
	std::shared_ptr<HighResolutionTimer> highResolutionTimer = SystemServiceLocator::GetService<HighResolutionTimer>();

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

