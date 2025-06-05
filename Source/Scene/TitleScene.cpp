#include <windows.h>
#include "TitleScene.h"
#include "../../GameXLib/Runtime/UI/ImGui.h"
#include "../../GameXLib\Runtime/UI\ImGuiManager.h"

#pragma region ‰Šú‰»ˆ—
/// <summary>
/// ‰Šú‰»ˆ—
/// </summary>
void TitleScene::Initialize()
{

}
#pragma endregion

#pragma region XVˆ—
/// <summary>
/// XVˆ—
/// </summary>
void TitleScene::Update()
{
	//std::shared_ptr<BaseImGuiManager> baseImGuiManager = ServiceLocator::GetService<BaseImGuiManager>(ServiceNames::BASE_IMGUI_MANAGER);
	//// UI•\¦ˆ—
	//if (baseImGuiManager)
	//{
	//	baseImGuiManager->RegisterImGuiFunction(std::bind(&TitleScene::ShowGUI, this));
	//}
	//if (GetAsyncKeyState('1') & 1)
	//{
	//	std::shared_ptr<SceneManager> sceneManager = ServiceLocator::GetService<SceneManager>(ServiceNames::SCENE_MANAGER);
	//	if (sceneManager)
	//	{
	//		sceneManager->LoadScene(SceneNames::MAIN_SCENE);
	//	}
	//}
}
#pragma endregion

#pragma region •`‰æˆ—
/// <summary>
/// •`‰æˆ—
/// </summary>
void TitleScene::Render()
{

}
#pragma endregion

#pragma region GUI•`‰æ
/// <summary>
/// GUI•`‰æ
/// </summary>
void TitleScene::ShowGUI()
{
	ImGui::Begin("Title");
	ImGui::End();
}
#pragma endregion
