#pragma once
#include "../../GameXLib/Runtime/UI/ImGuiManager.h"
#include "..\..\GameXLib\Runtime\Graphics\GraphicsManager.h"
#include "..\..\GameXLib\Runtime\Timer\HighResolutionTimer.h"
#include "GameInstance.h"
#include <Windows.h>

// フレームワーククラス(ゲーム処理)
class Framework
{
public:
	/// @brief コンストラクタ
	/// @param hwnd ウィンドウハンドル
	Framework(HWND hwnd);

	/// @brief ゲーム処理実行
	void Excute();

	/// @brief ウィンドウメッセージを処理するメンバ関数
	/// @param hwnd ウィンドウハンドル
	/// @param msg 受け取ったメッセージ
	/// @param wparam メッセージの追加情報（1つ目のパラメータ）
	/// @param lparam メッセージの追加情報（2つ目のパラメータ）
	/// @return メッセージを処理した結果（通常は `DefWindowProc` の戻り値を返す）
	LRESULT HandleMessage(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam);

private:
	/// @brief ImGui描画設定
	void ShowImGui();

	/// @brief フルスクリーン表示
	/// @param isFullscreen true:フルスクリーン
	void SetFullscreenState(bool isFullscreen);

	/// @brief FPS計算
    /// @param hwnd ウィンドウハンドル
    /// @param timeStamp 経過した合計時間
	/// @param isShowWindowTitle タイトルウィンドウにFPを表示するか。
	void CalculateFrameStats(HWND hwnd,float timeStamp, bool isShowWindowTitle);

private:
	// ウィンドウハンドル
	HWND hwnd;
	// IMGUI生成クラス
	ImGuiManager imguiManager;
	// ゲームタイマー
	HighResolutionTimer highResolutionTimer;
	// DirectX11
	GraphicsManager graphicsManager;
	// シーン管理クラス
	SceneManager sceneManager;
	// 1フレーム当たりの秒数
	float elapsedTime = 0;
	// FPS
	float fps = 0;

	// 1フレーム当たりの最大秒数指定
	const float limitElapsedTime = 1.0f / 5;
	// 初期フルスクリーンモード
	const BOOL FULSCREEN_MODE = false;
	// リフレッシュレート
	const UINT DEFAULT_FRAMERATE = 60;
	// クリアカラー
	const FLOAT REFRESH_COLOR[4] = {0.2f,0.2f,0.2f,1.0f};
	// 垂直同期(ON) モニターのリフレッシュレートに依存。フルスクリーンの場合、指定のフレッシュレート
	const UINT SYNC_INTERVAL_VALID = 1;
	// 垂直同期(OFF) 即時描画
	const UINT SYNC_INTERVAL_INVALID = 0;
};
