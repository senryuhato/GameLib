#include <windows.h>
#include "MainScene.h"
#include "../GameXLib/Runtime/UI/ImGui.h"
#include "..\GameXLib\Runtime\UI\ImGuiManager.h"


#pragma region ����������
/// <summary>
/// ����������
/// </summary>
void MainScene::Initialize()
{

}
#pragma endregion

#pragma region �X�V����
/// <summary>
/// �X�V����
/// </summary>
void MainScene::Update()
{
	//std::shared_ptr<BaseImGuiManager> baseImGuiManager = ServiceLocator::GetService<BaseImGuiManager>(ServiceNames::BASE_IMGUI_MANAGER);
	//// UI�\������
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

#pragma region �`�揈��
/// <summary>
/// �`�揈��
/// </summary>
void MainScene::Render()
{

}
#pragma endregion

#pragma region GUI�`��
/// <summary>
/// GUI�`��
/// </summary>
void MainScene::ShowGUI()
{
	ImGui::Begin("Main");
	ImGui::End();
}
#pragma endregion