#pragma once

// シーンクラス
class Scene
{
public:
	/// @brief コンストラクタ 
	Scene(){}

	/// @brief 初期化処理
	virtual void Initialize() {}

	/// @brief 終了処理
	virtual void Uninitializr() {}

	/// @brief 更新処理
	virtual void Update() {}

	/// @brief 描画処理
	virtual void Render() {}

	/// @brief GUI描画
	virtual void ShowGUI() {}
};
