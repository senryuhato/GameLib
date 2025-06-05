#pragma once
#include "../../GameXLib/Runtime/Scene/Scene.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public Scene
{
public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
    /// 描画処理
    /// </summary>
	void Render() override;

	/// <summary>
    /// GUI描画
    /// </summary>
	void ShowGUI() override;
};