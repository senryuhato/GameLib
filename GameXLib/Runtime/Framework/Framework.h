#pragma once
#include <Windows.h>

/// <summary>
/// ゲームの基盤を提供するフレームワーククラス
/// </summary>
class Framework
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Framework();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Framework() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() {}

	/// <summary>
	/// 終了処理
	/// </summary>
	void Uninitialize() {}

	/// <summary>
	/// ゲームループ
	/// </summary>
	void Run();

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
};
