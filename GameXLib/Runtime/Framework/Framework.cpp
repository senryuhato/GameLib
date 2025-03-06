#include "Framework.h"
#include "../System/ServiceLocator.h"
#include "../Timer/HighResolutionTimer.h"
#include "../Timer/TimeManager.h"
#include "../Scene/SceneManager.h"

#pragma region 初期化処理
/// <summary>
/// コンストラクタ
/// </summary>
Framework::Framework()
{
	// マネージャーの登録
	RegisterServices();
}
#pragma endregion

#pragma region ゲームループ
/// <summary>
/// ゲームループ
/// </summary>
void Framework::Run()
{
	// タイマー更新
	std::shared_ptr<TimeManager> timeManager = ServiceLocator::GetService<TimeManager>(ServiceNames::TIME_MANAGER);
	if (timeManager)
	{
		timeManager->Update();
	}
	
	// シーン更新
	std::shared_ptr<SceneManager> sceneManager = ServiceLocator::GetService<SceneManager>(ServiceNames::SCENE_MANAGER);
	if (sceneManager)
	{
		sceneManager->Update();
		sceneManager->Render();
	}

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
	// タイマー
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

#pragma region マネージャーの登録
/// <summary>
/// マネージャーの登録
/// </summary>
void Framework::RegisterServices()
{
	// 各種マネージャーの登録
	// すでに登録されている場合は登録しない
	// タイマー
	ServiceLocator::RegisterServiceIfNotExists<TimeManager>(ServiceNames::TIME_MANAGER);
	// シーン管理
	ServiceLocator::RegisterServiceIfNotExists<SceneManager>(ServiceNames::SCENE_MANAGER);
}
#pragma endregion