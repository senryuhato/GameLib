#include "../../GameXLib/Runtime/UI/ImGui.h"
#include "MainScene.h"

void MainScene::Initialize()
{
	// プレイヤー初期化
	player = std::make_shared<Player>();
	// 敵初期化
	enemy = std::make_shared<Enemy>();
}

void MainScene::Update()
{
}

void MainScene::Render()
{

}

void MainScene::ShowGUI()
{
	ImGui::Begin("Main");
	ImGui::End();
}
