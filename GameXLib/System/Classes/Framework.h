#pragma once
#include "HighResolutionTimer.h"
#include "../../ImGui/Classes/ImGuiManager.h"
#include "../../Graphics/Classes/GraphicsManager.h"

/// <summary>
/// ゲームの基盤を提供するフレームワーククラス
/// </summary>
class Framework
{
public:
	/// <summary>
	/// ゲームループ
	/// </summary>
	/// <returns></returns>
	int Run(HWND hwnd);

	/// <summary>
	/// ウィンドウメッセージを処理するメンバ関数（クラス内のメッセージ処理）
	/// </summary>
	/// <param name="hwnd">ウィンドウハンドル</param>
	/// <param name="msg">受け取ったメッセージ</param>
	/// <param name="wParam">メッセージの追加情報（1つ目のパラメータ）</param>
	/// <param name="lParam">メッセージの追加情報（2つ目のパラメータ）</param>
	/// <returns>メッセージを処理した結果（通常は `DefWindowProc` の戻り値を返す）</returns>
	LRESULT CALLBACK HandleMessage(
		_In_ HWND hwnd,
		_In_ UINT msg,
		_In_ WPARAM wparam,
		_In_ LPARAM lParam);

private:
	/// <summary>
    /// FPS計算
    /// </summary>
	void CalculateFrameStats(HWND hwnd);

private:
	HighResolutionTimer highResolutionTimer; // // フレームワーク用タイマー
};
