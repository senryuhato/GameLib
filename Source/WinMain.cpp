#include "../GameXLib/Runtime/System/GameXLib.h"
#include "../GameXLib/Runtime/System/ServiceLocator.h"
#include "../GameXLib/Runtime/Scene/SceneManager.h"
#include "../Source/TitleScene.h"
#include "../Source/MainScene.h"

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
	// シーンの登録
	ServiceLocator::RegisterService<SceneManager>(std::make_shared<SceneManager>());
	std::shared_ptr<SceneManager> sceneManager = ServiceLocator::GetService<SceneManager>();
	// シーン登録
	sceneManager->RegisterSceneIfNotExists<TitleScene>("TitleScene");
	sceneManager->RegisterSceneIfNotExists<MainScene>("MainScene");
	// 最初のシーン設定
	sceneManager->LoadScene("TitleScene");
	// カーソル設定
	sceneManager->SetShowMouseCursor(true);
	
	// ゲーム実行
	GameXLib& gameXLib = GameXLib::GetInstance();
	gameXLib.Execute(hInstance, nShowCmd, 1280, 720, L"ゲームプロジェクト");
	// 正常終了
	return 0;
}
#pragma endregion
