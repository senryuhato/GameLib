#include "Framework.h"
#include <memory>
#include <sal.h>
#include <Windows.h>
#include "..\..\GameXLib\Misc\GameWindow.h"

// ヘッダータイトル
static const wchar_t* WINDOW_TITLE = L"ゲームプロジェクト";

// 画面幅
static const int SCREEN_WIDTH = 1280;

// 画面高さ
static const int SCREEN_HEIGHT = 720;

std::unique_ptr<Framework> framework;

/// @brief ウィンドウメッセージを処理するコールバック関数（Win32 API 用）
/// @param hwnd ウィンドウハンドル
/// @param msg 受け取ったメッセージ
/// @param wParam メッセージの追加情報（1つ目のパラメータ）
/// @param lParam メッセージの追加情報（2つ目のパラメータ）
/// @return メッセージを処理した結果（通常は `DefWindowProc` の戻り値を返す）
LRESULT CALLBACK WindowProcedure(
	_In_ HWND hwnd,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	if(framework)
	{
		return framework->HandleMessage(hwnd,msg,wParam,lParam);
	} else
	{
		return DefWindowProc(hwnd,msg,wParam,lParam);
	}
}

/// @brief C++/CLI での Windows アプリケーションのエントリポイント。
/// @param hInstance 現在のインスタンスハンドル
/// @param hPrevInstance 以前のインスタンスハンドル（常に NULL）
/// @param lpCmdLine コマンドライン引数
/// @param nShowCmd ウィンドウの表示状態
/// @return プログラムの終了コード（通常は 0）
int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_  HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{
	// デバッグモード時にメモリリーク検出を有効化。
	#if defined(DEBUG) | defined(_DEBUG)
		// `_CRTDBG_ALLOC_MEM_DF` : メモリ割り当てのデバッグ情報を有効化。
		// `_CRTDBG_LEAK_CHECK_DF` : プログラム終了時にメモリリークをチェック。
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(####);を使用すると、指定されたアロケーション番号でブレーク可能。
	#endif

	// 乱数のシード値を設定。
	srand(static_cast<unsigned int>(time(nullptr)));

	// ウィンドウ初期化
	HWND hwnd = GameWindow::CreateGameWindow(WINDOW_TITLE,SCREEN_WIDTH,SCREEN_HEIGHT,nShowCmd,WindowProcedure);
	if(hwnd)
	{
		// インスタンス生成
		framework = std::make_unique<Framework>();
		// ウィンドウ終了処理
		GameWindow::DestroyGameWindow(hwnd);
	}
	return 0;
}
