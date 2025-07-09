#pragma once
#include "../../GameXLib/Runtime/Graphics/GraphicsManager.h"
#include "..\..\GameXLib\Runtime\UI\ImGuiManager.h"
#include "..\Scene\SceneManager.h"

// システム保持クラス
class GameInstance
{
public:
	// DirectX11
	GraphicsManager* graphicsManager = nullptr;
	// ImGuiマネージャー
	ImGuiManager* imguiManager = nullptr;
	// シーン管理クラス
	SceneManager* sceneManager = nullptr;
	// 1フレーム当たりの秒数
	float elapsedTime = 0;
};