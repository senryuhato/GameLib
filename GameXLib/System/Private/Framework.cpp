#include "../Classes/Framework.h"
#include <sstream>

#pragma region ゲームループ
/// <summary>
/// ゲームループ
/// </summary>
/// <param name="hwnd">ウィンドウハンドル</param>
/// <returns>結果</returns>
int Framework::Run(HWND hwnd)
{
	MSG msg = { 0 };
	highResolutionTimer.Reset();
	while (WM_QUIT != msg.message) {
		//ウィンドウからのメッセージを受け取る。
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//ウィンドウメッセージが空になった。
			highResolutionTimer.Tick();
			CalculateFrameStats(hwnd);
		}
	}
	return static_cast<int>(msg.wParam);
}
#pragma endregion

#pragma region ウィンドウメッセージを処理するメンバ関数（クラス内のメッセージ処理）
/// <summary>
/// ウィンドウメッセージを処理するメンバ関数（クラス内のメッセージ処理）
/// </summary>
/// <param name="hwnd">ウィンドウハンドル</param>
/// <param name="msg">受け取ったメッセージ</param>
/// <param name="wParam">メッセージの追加情報（1つ目のパラメータ）</param>
/// <param name="lParam">メッセージの追加情報（2つ目のパラメータ）</param>
/// <returns>メッセージを処理した結果（通常は `DefWindowProc` の戻り値を返す）</returns>
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

#pragma region FPS計算
/// <summary>
/// FPS計算
/// </summary>
/// <param name="hwnd">ウィンドウハンドル</param>
void Framework::CalculateFrameStats(HWND hwnd)
{
	// CalculateFrameStats フレームレート計算
	// 1秒当たりの平均のフレーム数を計算し、
	// これらの結果はウィンドウのキャプションバーに追加されます。
	// 1フレームをレンダリングするのにかかる平均時間を算出します。
	static int frames = 0;
	static float time_tlapsed = 0.0f;

	// 1秒間のFPSを算出
	if ((++frames, highResolutionTimer.TimeStamp() - time_tlapsed) >= 1.0f)
	{
		float fps = static_cast<float>(frames); // fps = frameCnt / 1
		float mspf = 1000.0f / fps;
		std::ostringstream outs;
		outs.precision(6);
		outs << "FPS : " << fps << " / " << "Frame Time : " << mspf << " (ms)";
		SetWindowTextA(hwnd, outs.str().c_str());

		// 次の平均にリセットします。
		frames = 0;
		time_tlapsed += 1.0f;
	}
}
#pragma endregion
