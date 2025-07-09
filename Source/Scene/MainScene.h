#pragma once
#include "../Object/Player.h"
#include "..\Object\Enemy.h"
#include "Scene.h"
#include <memory>

// メインシーン
class MainScene : public Scene
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

public:
	// プレイヤー
	std::shared_ptr<Player> player;
	// 敵
	std::shared_ptr<Enemy> enemy;
};