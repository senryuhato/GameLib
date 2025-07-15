#include <sal.h>
#include <Windows.h>

// ヘッダータイトル
static const wchar_t* WINDOW_TITLE = L"ゲームプロジェクト";

// 画面幅
static const int SCREEN_WIDTH = 1280;

// 画面高さ
static const int SCREEN_HEIGHT = 720;

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
	// デフォルトのメッセージ
	return DefWindowProc(hwnd,msg,wParam,lParam);
}

/// @brief C++/CLI での Windows アプリケーションのエントリポイント。
/// @param hInstance 現在のインスタンスハンドル
/// @param hPrevInstance 以前のインスタンスハンドル（常に NULL）
/// @param lpCmdLine コマンドライン引数
/// @param nShowCmd ウィンドウの表示状態
/// @return プログラムの終了コード（通常は 0）
int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_  HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{
	return 0;
}
