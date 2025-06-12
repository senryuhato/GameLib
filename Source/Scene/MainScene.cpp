#include <windows.h>
#include "MainScene.h"
#include "../../GameXLib/Runtime/UI/ImGui.h"
#include "../..\GameXLib\Runtime\UI\ImGuiManager.h"

#pragma region 初期化処理
/// <summary>
/// 初期化処理
/// </summary>
void MainScene::Initialize()
{
	// 画像読み込み
	//testSprite = std::make_shared<SpriteComponent>();

	// プレイヤー初期化
	player = std::make_shared<Player>();
}
#pragma endregion

#pragma region 更新処理
/// <summary>
/// 更新処理
/// </summary>
void MainScene::Update()
{
	//std::shared_ptr<BaseImGuiManager> baseImGuiManager = ServiceLocator::GetService<BaseImGuiManager>(ServiceNames::BASE_IMGUI_MANAGER);
	//// UI表示処理
	//if (baseImGuiManager)
	//{
	//	baseImGuiManager->RegisterImGuiFunction(std::bind(&MainScene::ShowGUI, this));
	//}
	//if (GetAsyncKeyState('1') & 1)
	//{
	//	std::shared_ptr<SceneManager> sceneManager = ServiceLocator::GetService<SceneManager>(ServiceNames::SCENE_MANAGER);
	//	if (sceneManager)
	//	{
	//		sceneManager->LoadScene(SceneNames::TITLE_SCENE);
	//	}
	//}
}
#pragma endregion

#pragma region 描画処理
/// <summary>
/// 描画処理
/// </summary>
void MainScene::Render()
{

}
#pragma endregion

#pragma region GUI描画
/// <summary>
/// GUI描画
/// </summary>
void MainScene::ShowGUI()
{
	ImGui::Begin("Main");
	ImGui::End();
}
#pragma endregion