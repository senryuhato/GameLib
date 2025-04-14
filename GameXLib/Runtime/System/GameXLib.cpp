#include <sstream>
#include "GameXLib.h"
#include "ServiceLocator.h"
#include "../Framework/Framework.h"
#include "../Timer/HighResolutionTimer.h"
#include "../UI/ImGuiManager.h"
#include "../Graphics/GraphicsManager.h"

#pragma region コンストラクタ
/// <summary>
/// コンストラクタ
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


	// マネージャーの登録
	// すでに登録されている場合は登録しない
	// フレームワーク
	ServiceLocator::RegisterServiceIfNotExists<Framework>(ServiceNames::FRAMEWORK);

	//// 各種マネージャーの登録
	//// すでに登録されている場合は登録しない
	//// ゲームループ
	//
	//// DirectX
	//ServiceLocator::RegisterServiceIfNotExists<GraphicsManager>(ServiceNames::GRAPHICS_MANAGER);
	//// ImGui
	//ServiceLocator::RegisterServiceIfNotExists<BaseImGuiManager>(ServiceNames::BASE_IMGUI_MANAGER);
	//// タイマー
	//ServiceLocator::RegisterServiceIfNotExists<HighResolutionTimer>(ServiceNames::HIGH_RESOLUTION_TIMER);
}
#pragma endregion

#pragma region 実行処理
/// <summary>
/// 実行処理
/// </summary>
/// <param name="instance">アプリケーションのインスタンスハンドル</param>
/// <param name="nShowCmd">ウィンドウの表示状態</param>
/// <param name="screenWidth">クライアント領域の幅（ピクセル）</param>
/// <param name="screenHeight">クライアント領域の高さ（ピクセル）</param>
/// <param name="windowTitle">ウィンドウのタイトル</param>
/// <param name="defaultFramerate">垂直同期時の目標フレームレート（デフォルト: 60）</param>
/// <returns>結果</returns>
bool GameXLib::Execute(
	_In_ HINSTANCE instance,
	_In_ int nShowCmd,
	_In_ LONG screenWidth,
	_In_ LONG screenHeight,
	_In_ LPCWSTR windowTitle,
	_In_ UINT defaultFramerate,
	_In_ BOOL isUseImGui
)
{
	// 初期化
	if (!Initialize(instance, nShowCmd, screenWidth, screenHeight, windowTitle, defaultFramerate))
	{
		return false;
	}
	//// ゲーム処理
	//Run();
	//// 終了処理
	//Uninitialize(instance);
	return true;
}
#pragma endregion

#pragma region フレームワークの初期化（ウィンドウと DirectX のセットアップ）
/// <summary>
/// フレームワークの初期化（ウィンドウと DirectX のセットアップ）
/// </summary>
/// <param name="instance">アプリケーションのインスタンスハンドル</param>
/// <param name="nShowCmd">ウィンドウの表示状態</param>
/// <param name="screenWidth">クライアント領域の幅（ピクセル）</param>
/// <param name="screenHeight">クライアント領域の高さ（ピクセル）</param>
/// <param name="windowTitle">ウィンドウのタイトル</param>
/// <param name="defaultFramerate">垂直同期時の目標フレームレート</param>
/// <returns>結果</returns>
bool GameXLib::Initialize(
	_In_ HINSTANCE instance,
	_In_ int nShowCmd,
	_In_ LONG screenWidth,
	_In_ LONG screenHeight,
	_In_ LPCWSTR windowTitle,
	_In_ UINT defaultFramerate
)
{
	//// 初期化
	//Uninitialize(instance);


	bool isSuccess = true;

	// ウィンドウクラスの登録
	if (!RegisterDefaultWindowClass(instance, CLASS_NAME, WindowProcedure))
	{
		isSuccess = false;
	}

	if (isSuccess)
	{
		// ウィンドウの作成
		hwnd = CreateDefaultWindow(instance, CLASS_NAME, screenWidth, screenHeight, windowTitle);
		if (!hwnd)
		{
			isSuccess = false;
		}
		else
		{
			// ウィンドウの表示状態設定(表示と非表示)
			ShowWindow(hwnd, nShowCmd);
		}
	}

	//// DirectXの初期化
	//std::shared_ptr<GraphicsManager> graphicsManager = ServiceLocator::GetService<GraphicsManager>("GraphicsManager");
	//if (!isSuccess || !graphicsManager || !graphicsManager->Initialize(hwnd, DEFAULT_FRAMERATE, FULSCREEN_NO))
	//{
	//	isSuccess = false;
	//}

	//// ImGuiの初期化
	//std::shared_ptr<BaseImGuiManager> baseImguiManager = ServiceLocator::GetService<BaseImGuiManager>(ServiceNames::BASE_IMGUI_MANAGER);
	//if (!isSuccess || !baseImguiManager || !baseImguiManager->Initialize(hwnd, graphicsManager->GetDevice(), graphicsManager->GetDeviceContext()))
	//{
	//	isSuccess = false;
	//}

	if (!isSuccess)
	{
		Uninitialize(instance);
		return false;
	}

	return true;
}
#pragma endregion

#pragma region フレームワークの終了処理
/// <summary>
/// フレームワークの終了処理
/// </summary>
/// <param name="instance">アプリケーションのインスタンスハンドル</param>
void GameXLib::Uninitialize(
	_In_ HINSTANCE instance)
{
	//// ImGuiの終了処理
	//std::shared_ptr<ImGuiManager> baseImguiManager = ServiceLocator::GetService<ImGuiManager>(ServiceNames::BASE_IMGUI_MANAGER);
	//if (baseImguiManager)
	//{
	//	baseImguiManager->Uninitialize();
	//}
	//// DirectXの解放
	//std::shared_ptr<GraphicsManager> graphicsManager = ServiceLocator::GetService<GraphicsManager>(ServiceNames::GRAPHICS_MANAGER);
	//if (graphicsManager)
	//{
	//	graphicsManager->Uninitialize();
	//}

	// ウィンドウの削除
	DestroyWindow(hwnd);
	// ウィンドウクラスの削除
	UnregisterClass(CLASS_NAME, instance);
}
#pragma endregion

#pragma region ゲームループ
/// <summary>
/// ゲームループ
/// </summary>
/// <returns>結果</returns>
int GameXLib::Run()
{
	//std::shared_ptr<Framework> framework = ServiceLocator::GetService<Framework>(ServiceNames::FRAMEWORK);
	//std::shared_ptr<HighResolutionTimer> highResolutionTimer = ServiceLocator::GetService<HighResolutionTimer>(ServiceNames::HIGH_RESOLUTION_TIMER);

	//if (framework && highResolutionTimer)
	//{
	//	// タイマーリセット
	//	highResolutionTimer->Reset();
	//	// ゲーム初期化処理
	//	framework->Initialize();
	//	// ゲームループ
	//	while (DispatchWindowMessage())
	//	{
	//		// タイマー更新
	//		highResolutionTimer->Tick();
	//		// ヘッダーにFPSを表示するか
	//		if (isShowFrameRate)
	//		{
	//			// ヘッダーにFPSを表示する
	//			CalculateFrameStats(highResolutionTimer->TimeStamp());
	//		}
	//		// ゲーム処理
	//		framework->Run();
	//	}
	//	// ゲーム終了処理
	//	framework->Uninitialize();
	//	return 0;
	//}
	return -1;
}
#pragma endregion

#pragma region ウィンドウメッセージをディスパッチ
/// <summary>
/// ウィンドウメッセージをディスパッチ。
/// falseが返ってきたら、ゲーム終了。
/// </summary>
/// <returns>結果</returns>
bool GameXLib::DispatchWindowMessage()
{
	MSG msg = { 0 };
	//ウィンドウからのメッセージを受け取る。
	while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
	{
		if (msg.message == WM_QUIT) return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//ウィンドウメッセージが空になった。
	return true;
}
#pragma endregion

#pragma region FPS計算
/// <summary>
/// FPS計算
/// </summary>
/// <param name="timeStamp">経過した合計時間</param>
void GameXLib::CalculateFrameStats(float timeStamp)
{
	// CalculateFrameStats フレームレート計算
	// 1秒当たりの平均のフレーム数を計算し、
	// これらの結果はウィンドウのキャプションバーに追加されます。
	// 1フレームをレンダリングするのにかかる平均時間を算出します。
	static int frames = 0;
	static float time_tlapsed = 0.0f;

	// 1秒間のFPSを算出
	if ((++frames, timeStamp - time_tlapsed) >= 1.0f)
	{
		float fps = static_cast<float>(frames); // fps = frameCnt / 1
		float mspf = 1000.0f / fps;
		std::ostringstream outs;
		outs.precision(6);
		outs << "FPS : " << fps << " / " << "Frame Time : " << mspf << " (ms)";
		SetWindowTextA(hwnd, outs.str().c_str());

		// 次の平均にリセットします。
		frames = 0;
		time_tlapsed += 1.0f;
	}
}
#pragma endregion

#pragma region ウィンドウメッセージを処理するコールバック関数（Win32 API 用）
/// <summary>
/// ウィンドウメッセージを処理するコールバック関数（Win32 API 用）
/// </summary>
/// <param name="hwnd">ウィンドウハンドル</param>
/// <param name="msg">受け取ったメッセージ</param>
/// <param name="wParam">メッセージの追加情報（1つ目のパラメータ）</param>
/// <param name="lParam">メッセージの追加情報（2つ目のパラメータ）</param>
/// <returns>メッセージを処理した結果（通常は `DefWindowProc` の戻り値を返す）</returns>
LRESULT CALLBACK GameXLib::WindowProcedure(
	_In_ HWND hwnd,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	//// サービスロケータから imguiManager と framework を取得
	//std::shared_ptr<BaseImGuiManager> baseImguiManager = ServiceLocator::GetService<BaseImGuiManager>(ServiceNames::BASE_IMGUI_MANAGER);
	//std::shared_ptr<Framework> framework = ServiceLocator::GetService<Framework>(ServiceNames::FRAMEWORK);

	//if (baseImguiManager)
	//{
	//	baseImguiManager->WndProcHandler(hwnd, msg, wParam, lParam);
	//}

	//if (framework)
	//{
	//	return framework->HandleMessage(hwnd, msg, wParam, lParam);
	//}
	return DefWindowProc(hwnd, msg, wParam, lParam);;
}
#pragma endregion

#pragma region デフォルト設定でウィンドウクラスを登録します
/// <summary>
/// デフォルト設定でウィンドウクラスを登録します。
/// 指定されたウィンドウプロシージャを持つ、標準的な設定のウィンドウクラスを登録します。
/// 背景色、カーソル、スタイルなどのパラメータは固定されています。
/// </summary>
/// <param name="instance">アプリケーションのインスタンスハンドル</param>
/// <param name="applicationName">登録するウィンドウクラスの名前</param>
/// <param name="windowProcedure">ウィンドウプロシージャ（メッセージ処理関数）</param>
/// <returns>true:成功 false:失敗</returns>
bool GameXLib::RegisterDefaultWindowClass(
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
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
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
	if (!RegisterClassExW(&wcex))
	{
		MessageBox(nullptr, L"ウィンドウクラスの登録に失敗しました。", L"エラー", MB_ICONERROR);
		return false; // 失敗時に false を返す
	}
	return true; // 成功時に true を返す
}
#pragma endregion

#pragma region デフォルト設定でウィンドウを作成します
/// <summary>
/// デフォルト設定でウィンドウを作成します。
/// 指定されたウィンドウクラスを使用し、標準的な設定のウィンドウを作成します。
/// クライアント領域のサイズを指定し、それに合うウィンドウサイズを自動調整します。
/// </summary>
/// <param name="instance">アプリケーションのインスタンスハンドル</param>
/// <param name="className">ウィンドウクラスの名前</param>
/// <param name="screenWidth">クライアント領域の幅（ピクセル）</param>
/// <param name="screenHeight">クライアント領域の高さ（ピクセル）</param>
/// <param name="windowTitle">ウィンドウのタイトル</param>
/// <param name="windowStyle">ィンドウのスタイル（デフォルトは WS_OVERLAPPEDWINDOW から WS_THICKFRAME を除外）</param>
/// <returns>作成されたウィンドウのハンドル（失敗時は nullptr）</returns>
HWND GameXLib::CreateDefaultWindow(
	_In_ HINSTANCE instance,
	_In_ LPCWSTR className,
	_In_ LONG screenWidth,
	_In_ LONG screenHeight,
	_In_ LPCWSTR windowTitle,
	_In_ DWORD windowStyle)
{
	// クライアント領域のサイズを指定
	RECT clientRect{ 0, 0, screenWidth, screenHeight };

	// クライアント領域が指定のサイズになるようにウィンドウサイズを調整
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

	// ウィンドウを作成し、そのハンドルを返す
	return CreateWindowExW(
		0,                  // 拡張ウィンドウスタイル（なし）
		className,          // 使用するウィンドウクラスの名前
		windowTitle,        // ウィンドウのタイトル
		windowStyle,        // ウィンドウのスタイル
		CW_USEDEFAULT,      // 初期X座標（デフォルト）
		CW_USEDEFAULT,      // 初期Y座標（デフォルト）
		clientRect.right - clientRect.left, // 計算されたウィンドウの幅
		clientRect.bottom - clientRect.top, // 計算されたウィンドウの高さ
		nullptr,            // 親ウィンドウ（なし）
		nullptr,            // メニュー（なし）
		instance,           // アプリケーションインスタンス
		nullptr             // 追加パラメータ（なし）
	);
}
#pragma endregion