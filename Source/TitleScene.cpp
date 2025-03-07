#include <windows.h>
#include "TitleScene.h"
#include "..\GameXLib\Runtime\UI\ImGuiManager.h"
#include "..\GameXLib\Runtime\UI\imGuiDX11.h"
#include "..\GameXLib\Runtime\System\ServiceLocator.h"

#pragma region 初期化処理
/// <summary>
/// 初期化処理
/// </summary>
void TitleScene::Initialize()
{

}
#pragma endregion

#pragma region 更新処理
/// <summary>
/// 更新処理
/// </summary>
void TitleScene::Update()
{
	std::shared_ptr<BaseImGuiManager> baseImGuiManager = ServiceLocator::GetService<BaseImGuiManager>(ServiceNames::BASE_IMGUI_MANAGER);
	// UI表示処理
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

#pragma region 描画処理
/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Render()
{

}
#pragma endregion

#pragma region GUI描画
/// <summary>
/// GUI描画
/// </summary>
void TitleScene::ShowGUI()
{
	ImGui::Begin("Title");
	ImGui::End();
}
#pragma endregion
