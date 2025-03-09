#include "../GameXLib/Runtime/System/GameXLib.h"
#include "../GameXLib/Runtime/System/ServiceLocator.h"
#include "../GameXLib/Runtime/UI/ImGuiManager.h"
#include "../GameXLib/Runtime/Scene/SceneManager.h"
#include "../Source/TitleScene.h"
#include "../Source/MainScene.h"
#include "ConfigConstant.h"

#pragma region C++/CLI Windows アプリケーションのエントリポイント
/// <summary>
/// C++/CLI での Windows アプリケーションのエントリポイント。
/// </summary>
/// <param name="hInstance">現在のインスタンスハンドル</param>
/// <param name="hPrevInstance">以前のインスタンスハンドル（常に NULL）</param>
/// <param name="lpCmdLine">コマンドライン引数</param>
/// <param name="nShowCmd">ウィンドウの表示状態</param>
/// <returns>プログラムの終了コード（通常は 0）</returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
#if 1 // ImGuiが不要の場合、削除することで表示されなくなる
	// ImGuiの登録
	ServiceLocator::RegisterService<ImGuiManager>(ServiceNames::BASE_IMGUI_MANAGER);
#endif
	// シーンの登録
	ServiceLocator::RegisterService<SceneManager>(ServiceNames::SCENE_MANAGER);
	std::shared_ptr<SceneManager> sceneManager = ServiceLocator::GetService<SceneManager>(ServiceNames::SCENE_MANAGER);
	// シーン登録
	sceneManager->RegisterSceneIfNotExists<TitleScene>(SceneNames::TITLE);
	sceneManager->RegisterSceneIfNotExists<MainScene>(SceneNames::MAIN);
	// 最初のシーン設定
	sceneManager->LoadScene(SceneNames::FIRST_SCENE);

#if 1 // 個別設定
	// カーソル設定
	sceneManager->SetShowMouseCursor(true);
#endif
	
	// ゲーム実行
	GameXLib& gameXLib = GameXLib::GetInstance();
	gameXLib.Execute(hInstance, nShowCmd,
		Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, 
		Config::WINDOW_TITLE, Config::FRAMERATE);
	// 正常終了
	return 0;
}
#pragma endregion
