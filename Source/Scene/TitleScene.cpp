#include "../../GameXLib/Runtime/UI/ImGui.h"
#include "../../GameXLib\Runtime/UI\ImGuiManager.h"
#include "TitleScene.h"
#include <windows.h>

void TitleScene::Initialize()
{

}

void TitleScene::Update()
{
	//std::shared_ptr<BaseImGuiManager> baseImGuiManager = ServiceLocator::GetService<BaseImGuiManager>(ServiceNames::BASE_IMGUI_MANAGER);
	//// UI表示処理
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

void TitleScene::Render()
{

}

void TitleScene::ShowGUI()
{
	ImGui::Begin("Title");
	ImGui::End();
}
