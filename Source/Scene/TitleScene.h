#pragma once
#include "Scene.h"

// タイトルシーン
class TitleScene : public Scene
{
public:
	/// @brief 初期化処理
	void Initialize() override;

	/// @brief 更新処理
	void Update() override;

	/// @brief 描画処理
	void Render() override;

	/// @brief GUI描画
	void ShowGUI() override;
};