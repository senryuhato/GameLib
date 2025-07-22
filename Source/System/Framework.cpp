#include "Framework.h"
#include <sstream>
#include "..\..\GameXLib\Misc\GameWindow.h"

void Framework::Excute(HWND hwnd)
{
	// カーソル設定
	GameWindow::SetShowMouseCursor(true);
	// 入力クラス初期化
	input = std::make_shared<Input>(hwnd);

	// DirectX11初期化
	if(graphicsManager.Initialize(hwnd,DEFAULT_FRAMERATE,FULSCREEN_MODE))
	{
		// Imgui初期化
		imguiManager.Initialize(hwnd,graphicsManager.GetDevice(),graphicsManager.GetDeviceContext());

		// シーン初期化
		sceneManager.Initialize();

		// タイマーリセット
		highResolutionTimer.Reset();

		// ゲームループ
		while(GameWindow::DispatchWindowMessage())
		{
			// タイマー更新
			highResolutionTimer.Tick();
			// ヘッダーにFPSを表示する
			CalculateFrameStats(hwnd,highResolutionTimer.TimeStamp(),true);
			// 入力更新
			input->Update();
			// シーン管理クラス更新処理
			sceneManager.Update();

			// GUI描画
			imguiManager.RenderImGuiFrame();
		}
		// ImGui終了処理
		imguiManager.Uninitialize();
		// 描画終了処理
		graphicsManager.Uninitialize();
	}
}

LRESULT Framework::HandleMessage(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	// ImGui入力処理
	imguiManager.WndProcHandler(hwnd,msg,wParam,lParam);

	switch(msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps{};
		BeginPaint(hwnd,&ps);
		EndPaint(hwnd,&ps);
	}
	break;
	case WM_DESTROY:
	PostQuitMessage(0);
	break;
	case WM_CREATE:
	break;
	case WM_KEYDOWN:
	if(wParam == VK_ESCAPE)
	{
		PostMessage(hwnd,WM_CLOSE,0,0);
	}
	break;
	case WM_ENTERSIZEMOVE:
	highResolutionTimer.Stop();
	break;
	case WM_EXITSIZEMOVE:
	highResolutionTimer.Start();
	break;
	default:
	return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

void Framework::CalculateFrameStats(HWND hwnd,float timeStamp,bool isShowWindowTitle = false)
{
	// CalculateFrameStats フレームレート計算
	// 1秒当たりの平均のフレーム数を計算し、
	// これらの結果はウィンドウのキャプションバーに追加されます。
	// 1フレームをレンダリングするのにかかる平均時間を算出します。
	static int frames = 0;
	static float time_tlapsed = 0.0f;

	// 1秒間のFPSを算出
	if((++frames,timeStamp - time_tlapsed) >= 1.0f)
	{
		float fps = static_cast<float>(frames); // fps = frameCnt / 1
		// ウィンドウタイトルを表示する
		if(isShowWindowTitle)
		{
			float mspf = 1000.0f / fps;
			std::ostringstream outs;
			outs.precision(6);
			outs << "FPS : " << fps << " / " << "Frame Time : " << mspf << " (ms)";
			SetWindowTextA(hwnd,outs.str().c_str());
		}
		// 次の平均にリセットします。
		frames = 0;
		time_tlapsed += 1.0f;
	}
}