#include "../Classes/Framework.h"
#include <sstream>

#pragma region �Q�[�����[�v
/// <summary>
/// �Q�[�����[�v
/// </summary>
/// <param name="hwnd">�E�B���h�E�n���h��</param>
/// <returns>����</returns>
int Framework::Run(HWND hwnd)
{
	MSG msg = { 0 };
	highResolutionTimer.Reset();
	while (WM_QUIT != msg.message) {
		//�E�B���h�E����̃��b�Z�[�W���󂯎��B
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//�E�B���h�E���b�Z�[�W����ɂȂ����B
			highResolutionTimer.Tick();
			CalculateFrameStats(hwnd);
		}
	}
	return static_cast<int>(msg.wParam);
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
		highResolutionTimer.Stop();
		break;
	case WM_EXITSIZEMOVE:
		highResolutionTimer.Start();
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
#pragma endregion

#pragma region FPS�v�Z
/// <summary>
/// FPS�v�Z
/// </summary>
/// <param name="hwnd">�E�B���h�E�n���h��</param>
void Framework::CalculateFrameStats(HWND hwnd)
{
	// CalculateFrameStats �t���[�����[�g�v�Z
	// 1�b������̕��ς̃t���[�������v�Z���A
	// �����̌��ʂ̓E�B���h�E�̃L���v�V�����o�[�ɒǉ�����܂��B
	// 1�t���[���������_�����O����̂ɂ����镽�ώ��Ԃ��Z�o���܂��B
	static int frames = 0;
	static float time_tlapsed = 0.0f;

	// 1�b�Ԃ�FPS���Z�o
	if ((++frames, highResolutionTimer.TimeStamp() - time_tlapsed) >= 1.0f)
	{
		float fps = static_cast<float>(frames); // fps = frameCnt / 1
		float mspf = 1000.0f / fps;
		std::ostringstream outs;
		outs.precision(6);
		outs << "FPS : " << fps << " / " << "Frame Time : " << mspf << " (ms)";
		SetWindowTextA(hwnd, outs.str().c_str());

		// ���̕��ςɃ��Z�b�g���܂��B
		frames = 0;
		time_tlapsed += 1.0f;
	}
}
#pragma endregion
