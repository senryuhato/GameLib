#include "GameXLib.h"
#include <crtdbg.h>
#include <cstdlib>
#include <ctime>
#include <libloaderapi.h>
#include <sal.h>
#include <time.h>
#include <Windows.h>

namespace GameXLib
{
// window名
static const LPCWSTR CLASS_NAME = L"GameProject";
// ウィンドウスタイル
static const DWORD WINDOW_STYLE = WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE;

HWND Initialize(_In_ LPCWSTR applicationName,_In_ LONG screenWidth,_In_ LONG screenHeight,_In_ int nShowCmd,_In_ WNDPROC windowProcedure)
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

	// アプリケーションのインスタンスハンドルの取得
	HINSTANCE hInstance = GetModuleHandle(NULL);

	// ウィンドウクラスの登録
	if(!GameXLib::RegisterDefaultWindowClass(hInstance,CLASS_NAME,windowProcedure))
	{
		return nullptr;
	}

	// ウィンドウの作成
	HWND hwnd = GameXLib::CreateDefaultWindow(hInstance,CLASS_NAME,screenWidth,screenHeight,applicationName,WINDOW_STYLE);
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

void UnInitialize(HWND hwnd)
{
	// アプリケーションのインスタンスハンドルの取得
	HINSTANCE hInstance = GetModuleHandle(NULL);
	// ウィンドウの削除
	DestroyWindow(hwnd);
	// ウィンドウクラスの削除
	UnregisterClass(CLASS_NAME,hInstance);
}

bool DispatchWindowMessage()
{
	MSG msg = {0};
	//ウィンドウからのメッセージを受け取る。
	while(PeekMessage(&msg,NULL,0U,0U,PM_REMOVE))
	{
		if(msg.message == WM_QUIT) return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//ウィンドウメッセージが空になった。
	return true;
}

void SetShowMouseCursor(bool isShow)
{
	// カーソルは、表示カウントが 0 以上の場合にのみ表示
	int count = ShowCursor(isShow);
	while(isShow ? count < 0 : count >= 0)
	{
		count = ShowCursor(isShow);
	}
}

bool RegisterDefaultWindowClass(
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

HWND CreateDefaultWindow(
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
}