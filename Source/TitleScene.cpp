#include <windows.h>
#include "TitleScene.h"
#include "..\GameXLib\Runtime\UI\ImGuiManager.h"
#include "..\GameXLib\Runtime\UI\imGuiDX11.h"
#include "..\GameXLib\Runtime\System\ServiceLocator.h"

#pragma region ����������
/// <summary>
/// ����������
/// </summary>
void TitleScene::Initialize()
{

}
#pragma endregion

#pragma region �X�V����
/// <summary>
/// �X�V����
/// </summary>
void TitleScene::Update()
{
	std::shared_ptr<BaseImGuiManager> baseImGuiManager = ServiceLocator::GetService<BaseImGuiManager>(ServiceNames::BASE_IMGUI_MANAGER);
	// UI�\������
	if (baseImGuiManager)
	{
		baseImGuiManager->RegisterImGuiFunction(std::bind(&TitleScene::ShowGUI, this));
	}
	if (GetAsyncKeyState('1') & 1)
	{
		int a = 0;
		a++;
	}
}
#pragma endregion

#pragma region �`�揈��
/// <summary>
/// �`�揈��
/// </summary>
void TitleScene::Render()
{

}
#pragma endregion

#pragma region GUI�`��
/// <summary>
/// GUI�`��
/// </summary>
void TitleScene::ShowGUI()
{
	ImGui::Begin("Title");
	ImGui::End();
}
#pragma endregion
