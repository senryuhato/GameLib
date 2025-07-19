#include "GameWindow.h"
#include <libloaderapi.h>
#include <Windows.h>
#include <sal.h>

HWND GameWindow::CreateGameWindow(_In_ LPCWSTR applicationName,_In_ LONG screenWidth,_In_ LONG screenHeight,_In_ int nShowCmd,_In_ WNDPROC windowProcedure)
{
	// アプリケーションのインスタンスハンドルの取得
	HINSTANCE hInstance = GetModuleHandle(NULL);

	// ウィンドウクラスの登録
	if(!RegisterDefaultWindowClass(hInstance,CLASS_NAME,windowProcedure))
	{
		return nullptr;
	}

	// ウィンドウの作成
	HWND hwnd = CreateDefaultWindow(hInstance,CLASS_NAME,screenWidth,screenHeight,applicationName,WINDOW_STYLE);
	if(!hwnd)
	{
		// ウィンドウクラスの削除
		UnregisterClass(CLASS_NAME,hInstance);
		return nullptr;
	}
	// ウィンドウの表示状態設定(表示と非表示)
	if(!ShowWindow(hwnd,nShowCmd))
	{
		// ウィンドウの削除
		DestroyWindow(hwnd);
		// ウィンドウクラスの削除
		UnregisterClass(CLASS_NAME,hInstance);
		return nullptr;
	}
	return hwnd;
}

void GameWindow::DestroyGameWindow(HWND hwnd)
{
	// アプリケーションのインスタンスハンドルの取得
	HINSTANCE hInstance = GetModuleHandle(NULL);
	// ウィンドウの削除
	DestroyWindow(hwnd);
	// ウィンドウクラスの削除
	UnregisterClass(CLASS_NAME,hInstance);
}

bool GameWindow::RegisterDefaultWindowClass(
	_In_ HINSTANCE instance,
	_In_ LPCWSTR applicationName,
	_In_ WNDPROC windowProcedure)
{
	// ウィンドウクラスのパラメーターを設定
	WNDCLASSEX wcex{};
	// 構造体のサイズを設定
	wcex.cbSize = sizeof(WNDCLASSEX);
	// ウィンドウのスタイル
	// CS_HREDRAW: ウィンドウの幅が変更された際に再描画
	// CS_VREDRAW: ウィンドウの高さが変更された際に再描画
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	// ウィンドウプロシージャ（メッセージ処理関数）を指定。
	wcex.lpfnWndProc = windowProcedure;
	// クラスメモリの追加バイト数（通常は 0）
	wcex.cbClsExtra = 0;
	// ウィンドウごとの追加メモリのバイト数（通常は 0）
	wcex.cbWndExtra = 0;
	// ウィンドウクラスが属するアプリケーションのインスタンスハンドル
	wcex.hInstance = instance;
	// ウィンドウのアイコンを設定（NULL の場合はデフォルトアイコン）
	wcex.hIcon = nullptr;
	// マウスカーソルのデフォルト設定（通常は矢印カーソル）
	wcex.hCursor = LoadCursor(nullptr,IDC_ARROW);
	// ウィンドウの背景色を設定。
	// (HBRUSH)(COLOR_WINDOW + 1) でシステムの標準背景色を使用
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// メニューのリソース名（NULL の場合はメニューなし）
	wcex.lpszMenuName = nullptr;
	// ウィンドウクラス名を設定
	wcex.lpszClassName = applicationName;
	// 小さいアイコン（タスクバーのサムネイル用）。NULL の場合はデフォルト
	wcex.hIconSm = nullptr;
	// ウィンドウクラスの登録。
	if(!RegisterClassEx(&wcex))
	{
		MessageBox(nullptr,L"ウィンドウクラスの登録に失敗しました。",L"エラー",MB_ICONERROR);
		// 失敗時に false を返す
		return false;
	}
	// 成功時に true を返す
	return true;
}

HWND GameWindow::CreateDefaultWindow(
	_In_ HINSTANCE instance,
	_In_ LPCWSTR className,
	_In_ LONG screenWidth,
	_In_ LONG screenHeight,
	_In_ LPCWSTR windowTitle,
	_In_ DWORD windowStyle)
{
	// クライアント領域のサイズを指定
	RECT clientRect{0,0,screenWidth,screenHeight};

	// クライアント領域が指定のサイズになるようにウィンドウサイズを調整
	AdjustWindowRect(&clientRect,WS_OVERLAPPEDWINDOW,FALSE);

	// ウィンドウを作成し、そのハンドルを返す
	return CreateWindow(
		// 使用するウィンドウクラスの名前
		className,
		// ウィンドウのタイトル
		windowTitle,
		// ウィンドウのスタイル
		windowStyle,
		// 初期X座標（デフォルト）
		CW_USEDEFAULT,
		// 初期Y座標（デフォルト）
		CW_USEDEFAULT,
		// 計算されたウィンドウの幅
		clientRect.right - clientRect.left,
		// 計算されたウィンドウの高さ
		clientRect.bottom - clientRect.top,
		// 親ウィンドウ（なし）
		nullptr,
		// メニュー（なし）
		nullptr,
		// アプリケーションインスタンス
		instance,
		// 追加パラメータ（なし）
		nullptr
	);
}