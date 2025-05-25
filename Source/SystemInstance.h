#pragma once
#include "../GameXLib/Runtime/Timer/HighResolutionTimer.h"
#include "..\GameXLib\Runtime\UI\ImGuiManager.h"
#include "..\GameXLib\Runtime\Graphics\GraphicsManager.h"

/// <summary>
/// �V�X�e���ێ��N���X
/// </summary>
class SystemInstance
{
public:
	/// <summary>
    /// �Q�[���^�C�}�[
    /// </summary>
	HighResolutionTimer highResolutionTimer;

	/// <summary>
    /// DirectX11
    /// </summary>
	GraphicsManager graphicsManager;

	/// <summary>
	/// ImGui�}�l�[�W���[
	/// </summary>
	ImGuiManager imguiManager;
};
