﻿#pragma once
#include "../../GameXLib/Runtime/Scene/Scene.h"
#include "../../GameXLib/Runtime/Component/SpriteComponent.h"
#include "../Object/Player.h"
#include <memory>

/// <summary>
/// メインシーン
/// </summary>
class MainScene : public Scene
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

public:
	// テスト画像
	std::shared_ptr<SpriteComponent> testSprite;
	// プレイヤー
	std::shared_ptr<Player> player;
};