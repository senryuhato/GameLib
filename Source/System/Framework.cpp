#include "..\..\GameXLib\ThirdParty\ImGui\imgui-docking\imgui.h"
#include "Framework.h"
#include "GameInstance.h"
#include <d3d11.h>
#include <dxgi.h>
#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <Windows.h>
#include "..\..\GameXLib\GameXLib.h"

Framework::Framework(HWND hwnd): hwnd(hwnd)
{
}

void Framework::Excute()
{
	// カーソル設定
	GameXLib::SetShowMouseCursor(true);

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
		while(GameXLib::DispatchWindowMessage())
		{
			// タイマー更新
			highResolutionTimer.Tick();
			// ヘッダーにFPSを表示する
			CalculateFrameStats(hwnd,highResolutionTimer.TimeStamp(),true);

			// ゲーム描画
			ID3D11DeviceContext* immediateContext = graphicsManager.GetDeviceContext();
			ID3D11RenderTargetView* renderTargetView = graphicsManager.GetRenderTargetView();
			ID3D11DepthStencilView* depthStencilView = graphicsManager.GetDepthStencilView();
			IDXGISwapChain* swapChain = graphicsManager.GetSwapChain();

			// 画面クリア＆レンダーターゲット設定
			immediateContext->ClearRenderTargetView(renderTargetView,REFRESH_COLOR);
			immediateContext->ClearDepthStencilView(depthStencilView,D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,1.0f,0);
			immediateContext->OMSetRenderTargets(1,&renderTargetView,depthStencilView);

			// フレーム間秒数
			elapsedTime = highResolutionTimer.TimeInterval();
			elapsedTime = elapsedTime > limitElapsedTime ? limitElapsedTime : elapsedTime;
			// ゲームインスタンス注入
			gameInstance->elapsedTime = elapsedTime;

			// シーン管理クラス更新処理
			sceneManager.Update();

			// GUI登録
			imguiManager.RegisterImGuiFunction(std::bind(&Framework::ShowImGui,this));
			for(std::pair<const std::string,std::unique_ptr<Scene>>& scene : sceneManager.scenes)
			{
				imguiManager.RegisterImGuiFunction(std::bind(&Scene::ShowGUI,scene.second.get()));
			}

			// GUI描画
			imguiManager.RenderImGuiFrame();

			// 描画
			graphicsManager.GetSwapChain()->Present(SYNC_INTERVAL_INVALID,0);
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

void Framework::ShowImGui()
{
	ImGui::Begin("Main");
	ImGui::Text("%f",fps);
	ImGui::End();
}

void Framework::SetFullscreenState(bool isFullscreen)
{
	graphicsManager.GetSwapChain()->SetFullscreenState(isFullscreen,nullptr);
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
		fps = static_cast<float>(frames); // fps = frameCnt / 1
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