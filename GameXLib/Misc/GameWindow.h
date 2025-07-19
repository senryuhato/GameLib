#pragma once
#include <Windows.h>

class GameWindow
{
public:
	/// @brief ゲーム用ウィンドウ作成
    /// @param applicationName ウィンドウタイトル名
    /// @param screenWidth ウィンドウの横幅
    /// @param screenHeight ウィンドウの縦幅
    /// @param nShowCmd ウィンドウの表示状態(最大化,最小化,通常の起動状態を設定できる)
    /// @param windowProcedure ウィンドウプロシージャ（メッセージ処理関数）
    /// @return ウィンドウハンドル
	static HWND CreateGameWindow(_In_ LPCWSTR applicationName,_In_ LONG screenWidth,_In_ LONG screenHeight,_In_ int nShowCmd,_In_ WNDPROC windowProcedure);

	/// @brief ゲーム用ウィンドウ破棄
	/// @param hwnd ウィンドウハンドル
	static void DestroyGameWindow(HWND hwnd);

private:
	/// @brief デフォルト設定でウィンドウクラスを登録します。
	/// 指定されたウィンドウプロシージャを持つ、標準的な設定のウィンドウクラスを登録します。
	/// 背景色、カーソル、スタイルなどのパラメータは固定されています。
	/// @param instance アプリケーションのインスタンスハンドル
	/// @param applicationName 登録するウィンドウクラスの名前
	/// @param windowProcedure ウィンドウプロシージャ（メッセージ処理関数）
	/// @return true:成功 false:失敗
	static bool RegisterDefaultWindowClass(
	  _In_ HINSTANCE instance,
	  _In_ LPCWSTR applicationName,
	  _In_ WNDPROC windowProcedure);

	/// @brief デフォルト設定でウィンドウを作成します。
	/// 指定されたウィンドウクラスを使用し、標準的な設定のウィンドウを作成します。
	/// クライアント領域のサイズを指定し、それに合うウィンドウサイズを自動調整します。
	/// @param instance アプリケーションのインスタンスハンドル
	/// @param className ウィンドウクラスの名前
	/// @param screenWidth クライアント領域の幅（ピクセル）
	/// @param screenHeight クライアント領域の高さ（ピクセル）
	/// @param windowTitle ウィンドウのタイトル
	/// @param windowStyle ウィンドウのスタイル（デフォルトは WS_OVERLAPPEDWINDOW から WS_THICKFRAME を除外）
	/// @return 作成されたウィンドウのハンドル（失敗時は nullptr）
	static HWND CreateDefaultWindow(
		_In_ HINSTANCE instance,
		_In_ LPCWSTR className,
		_In_ LONG screenWidth,
		_In_ LONG screenHeight,
		_In_ LPCWSTR windowTitle,
		_In_ DWORD windowStyle);

private:
	// window名
	inline static const LPCWSTR CLASS_NAME = L"GameProject";
	// ウィンドウスタイル
	static const DWORD WINDOW_STYLE = WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE;
};
