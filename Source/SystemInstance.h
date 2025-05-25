#pragma once
#include "../GameXLib/Runtime/Timer/HighResolutionTimer.h"
#include "..\GameXLib\Runtime\UI\ImGuiManager.h"
#include "..\GameXLib\Runtime\Graphics\GraphicsManager.h"

/// <summary>
/// システム保持クラス
/// </summary>
class SystemInstance
{
public:
	/// <summary>
    /// ゲームタイマー
    /// </summary>
	HighResolutionTimer highResolutionTimer;

	/// <summary>
    /// DirectX11
    /// </summary>
	GraphicsManager graphicsManager;

	/// <summary>
	/// ImGuiマネージャー
	/// </summary>
	ImGuiManager imguiManager;
};
