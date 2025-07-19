#pragma once
#include <Windows.h>

class Framework
{
public:
	/// @brief ゲーム処理実行
	/// @param hwnd ウィンドウハンドル
	void Excute(HWND hwnd);

	/// @brief ウィンドウメッセージを処理するメンバ関数
	/// @param hwnd ウィンドウハンドル
	/// @param msg 受け取ったメッセージ
	/// @param wparam メッセージの追加情報（1つ目のパラメータ）
	/// @param lparam メッセージの追加情報（2つ目のパラメータ）
	/// @return メッセージを処理した結果（通常は `DefWindowProc` の戻り値を返す）
	LRESULT HandleMessage(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam);
};