#include <Windows.h>
#include <crtdbg.h>
#include <time.h>

#include "GameXLib.h"

#pragma region コンストラクタ
/// <summary>
/// GameLib クラスのコンストラクタ。
/// デバッグ環境ではメモリリーク検出を有効化し、
/// 乱数の初期化を行う。
/// </summary>
GameXLib::GameXLib()
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
}
#pragma endregion

#pragma region 指定されたウィンドウプロシージャを持つウィンドウクラスを登録します
/// <summary>
/// 指定されたウィンドウプロシージャを持つウィンドウクラスを登録します。
/// </summary>
/// <param name="instance">現在のアプリケーションのインスタンスハンドル。</param>
/// <param name="applicationName">ウィンドウクラスの名前（LPCWSTR 型）。</param>
/// <param name="windowProcedure">ウィンドウプロシージャの関数ポインタ。</param>
/// <returns>ウィンドウクラスの登録が成功した場合は true、それ以外の場合は false。</returns>
bool GameXLib::RegisterWindowClassProcedure(_In_ HINSTANCE instance, _In_ LPCWSTR applicationName, _In_ WNDPROC windowProcedure)
{
	// ウィンドウクラスのパラメーターを設定
	WNDCLASSEX wcex{};
	// 構造体のサイズを設定。
	wcex.cbSize = sizeof(WNDCLASSEX);
	// ウィンドウのスタイル。
	// CS_HREDRAW: ウィンドウの幅が変更された際に再描画。
	// CS_VREDRAW: ウィンドウの高さが変更された際に再描画。
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	// ウィンドウプロシージャ（メッセージ処理関数）を指定。
	wcex.lpfnWndProc = windowProcedure;
	// クラスメモリの追加バイト数（通常は 0）。
	wcex.cbClsExtra = 0;
	// ウィンドウごとの追加メモリのバイト数（通常は 0）。
	wcex.cbWndExtra = 0;
	// ウィンドウクラスが属するアプリケーションのインスタンスハンドル。
	wcex.hInstance = instance;
	// ウィンドウのアイコンを設定（NULL の場合はデフォルトアイコン）。
	wcex.hIcon = NULL;
	// マウスカーソルのデフォルト設定（通常は矢印カーソル）。
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	// ウィンドウの背景色を設定。
	// (HBRUSH)(COLOR_WINDOW + 1) でシステムの標準背景色を使用。
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// メニューのリソース名（NULL の場合はメニューなし）。
	wcex.lpszMenuName = NULL;
	// ウィンドウクラス名を設定。
	wcex.lpszClassName = applicationName;
	// 小さいアイコン（タスクバーのサムネイル用）。NULL の場合はデフォルト。
	wcex.hIconSm = 0;

	// ウィンドウクラスの登録。
	if (!RegisterClassExW(&wcex))
	{
		MessageBox(NULL, L"ウィンドウクラスの登録に失敗しました。", L"エラー", MB_ICONERROR);
		return false; // 失敗時に false を返す
	}
	return true; // 成功時に true を返す
}
#pragma endregion