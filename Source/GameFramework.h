#pragma once
#include "../GameXLib/System/Classes/Framework.h"

/// <summary>
/// ゲームクラス
/// </summary>
class GameFramework : public Framework
{
public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Uninitialize() {}

	/// <summary>
	/// ゲームループ
	/// </summary>
	void Run();

	/// <summary>
    /// 更新処理
    /// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Render();
private:
	// クリアカラー
	FLOAT refreshColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	// 定数
	const UINT SYNC_INTERVAL_VALID = 1;
	const UINT SYNC_INTERVAL_INVALID = 0;
};