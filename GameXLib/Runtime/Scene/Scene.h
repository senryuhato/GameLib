#pragma once

/// <summary>
/// シーンクラス
/// </summary>
class Scene
{
public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize() {}

	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void Uninitializr() {}

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() {}

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Render() {}

	/// <summary>
    /// GUI描画
    /// </summary>
	virtual void ShowGUI() {}
};