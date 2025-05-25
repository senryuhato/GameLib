#include <crtdbg.h>
#include <time.h>
#include <sstream>
#include <map>
#include "WinMain.h"
#include "..\GameXLib\Runtime\Scene\Scene.h"
#include "SystemInstance.h"
#include "TitleScene.h"
#include "MainScene.h"

#pragma region 定数
/// <summary>
/// window名
/// </summary>
static const LPCWSTR CLASS_NAME = L"GameProject";

/// <summary>
/// リフレッシュレート
/// </summary>
static const UINT DEFAULT_FRAMERATE = 60;

/// <summary>
/// ウィンドウ名
/// </summary>
static const wchar_t* WINDOW_TITLE = L"ゲームプロジェクト";

/// <summary>
/// 画面幅
/// </summary>
static const int SCREEN_WIDTH = 1280;

/// <summary>
/// 画面高さ
/// </summary>
static const int SCREEN_HEIGHT = 720;

/// <summary>
/// デフォルトフレームレート
/// </summary>
static const int FRAMERATE = 60;

/// <summary>
/// 初期フルスクリーンモード
/// </summary>
const BOOL FULSCREEN_MODE = false;

/// <summary>
/// クリアカラー
/// </summary>
const FLOAT REFRESH_COLOR[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

/// <summary>
/// 垂直同期(ON)
/// </summary>
const UINT SYNC_INTERVAL_VALID = 1;

/// <summary>
/// 垂直同期(OFF)
/// </summary>
const UINT SYNC_INTERVAL_INVALID = 0;

/// <summary>
/// タイトルシーンキー
/// </summary>
static const std::string TITLE_SCENE = "TitleScene";

/// <summary>
/// メインシーンキー
/// </summary>
static const std::string MAIN_SCENE = "MainScene";
#pragma endregion

#pragma region 変数
/// <summary>
/// ウィンドウハンドル
/// </summary>
HWND hwnd = nullptr;

/// <summary>
/// フレームレートを表示させるか
/// </summary>
bool isShowFrameRate = true;

/// <summary>
/// システム保持クラス
/// </summary>
SystemInstance systemInstace;

/// <summary>
/// 現在のシーンのキー
/// </summary>
std::string currentSceneKey;

/// <summary>
/// 次のシーンのキー(シーンの変更時以外はEmpty)
/// </summary>
std::string nextSceneKey;

/// <summary>
/// シーンリスト
/// </summary>
std::map<std::string, std::unique_ptr<Scene>> scenes;

/// <summary>
/// 垂直同期
/// </summary>
const UINT syncInterval = SYNC_INTERVAL_VALID;

Microsoft::WRL::ComPtr<ID3D11DepthStencilState> defaultDepthStencilState;
Microsoft::WRL::ComPtr<ID3D11RasterizerState> defaultRasterizerState[2];
Microsoft::WRL::ComPtr<ID3D11BlendState> defaultBlendState;
Microsoft::WRL::ComPtr<ID3D11SamplerState> defaultSamplerState[3];
#pragma endregion

#pragma region C++/CLI Windows アプリケーションのエントリポイント
/// <summary>
/// C++/CLI での Windows アプリケーションのエントリポイント。
/// </summary>
/// <param name="hInstance">現在のインスタンスハンドル</param>
/// <param name="hPrevInstance">以前のインスタンスハンドル（常に NULL）</param>
/// <param name="lpCmdLine">コマンドライン引数</param>
/// <param name="nShowCmd">ウィンドウの表示状態</param>
/// <returns>プログラムの終了コード（通常は 0）</returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
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

	// ウィンドウクラスの登録
	if (RegisterDefaultWindowClass(hInstance, CLASS_NAME, WindowProcedure))
	{
		// ウィンドウの作成
		hwnd = CreateDefaultWindow(hInstance, CLASS_NAME, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE);
		if (hwnd)
		{
			// ウィンドウの表示状態設定(表示と非表示)
			ShowWindow(hwnd, nShowCmd);

			// DirectX11初期化
			if (systemInstace.graphicsManager.Initialize(hwnd, DEFAULT_FRAMERATE, FULSCREEN_MODE))
			{
				// Imgui初期化
				systemInstace.imguiManager.Initialize(hwnd, systemInstace.graphicsManager.GetDevice(), systemInstace.graphicsManager.GetDeviceContext());

				// シーン登録
				RegisterSceneIfNotExists<TitleScene>(TITLE_SCENE);
				RegisterSceneIfNotExists<MainScene>(MAIN_SCENE);
				// 最初のシーン設定
				LoadScene(TITLE_SCENE);

				// カーソル設定
				SetShowMouseCursor(true);

				// タイマーリセット
				systemInstace.highResolutionTimer.Reset();

				//{
				//	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
				//	depth_stencil_desc.DepthEnable = TRUE;
				//	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				//	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
				//	depth_stencil_desc.StencilEnable = FALSE;
				//	depth_stencil_desc.StencilReadMask = 0xFF;
				//	depth_stencil_desc.StencilWriteMask = 0xFF;
				//	depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				//	depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
				//	depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				//	depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
				//	depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				//	depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
				//	depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				//	depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
				//	hr = device->CreateDepthStencilState(&depth_stencil_desc, default_depth_stencil_state.GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
				//}

				//{
				//	D3D11_RASTERIZER_DESC rasterizer_desc = {};
				//	rasterizer_desc.FillMode = D3D11_FILL_SOLID;
				//	rasterizer_desc.CullMode = D3D11_CULL_BACK;
				//	rasterizer_desc.FrontCounterClockwise = FALSE;
				//	rasterizer_desc.DepthBias = 0;
				//	rasterizer_desc.DepthBiasClamp = 0;
				//	rasterizer_desc.SlopeScaledDepthBias = 0;
				//	rasterizer_desc.DepthClipEnable = TRUE;
				//	rasterizer_desc.ScissorEnable = FALSE;
				//	rasterizer_desc.MultisampleEnable = TRUE;
				//	rasterizer_desc.AntialiasedLineEnable = FALSE;
				//	hr = device->CreateRasterizerState(&rasterizer_desc, default_rasterizer_state[0].GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

				//	rasterizer_desc.FrontCounterClockwise = TRUE;
				//	hr = device->CreateRasterizerState(&rasterizer_desc, default_rasterizer_state[1].GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
				//}

				//{
				//	D3D11_BLEND_DESC blend_desc = {};
				//	blend_desc.AlphaToCoverageEnable = FALSE;
				//	blend_desc.IndependentBlendEnable = FALSE;
				//	blend_desc.RenderTarget[0].BlendEnable = TRUE;
				//	blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
				//	blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
				//	blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
				//	blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
				//	blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
				//	blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
				//	blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
				//	hr = device->CreateBlendState(&blend_desc, default_blend_state.GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
				//}

				//{
				//	D3D11_SAMPLER_DESC sampler_desc;
				//	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
				//	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
				//	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
				//	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
				//	sampler_desc.MipLODBias = 0;
				//	sampler_desc.MaxAnisotropy = 16;
				//	sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
				//	sampler_desc.BorderColor[0] = 0.0f;
				//	sampler_desc.BorderColor[1] = 0.0f;
				//	sampler_desc.BorderColor[2] = 0.0f;
				//	sampler_desc.BorderColor[3] = 0.0f;
				//	sampler_desc.MinLOD = 0;
				//	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
				//	hr = device->CreateSamplerState(&sampler_desc, default_sampler_state[0].GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

				//	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				//	hr = device->CreateSamplerState(&sampler_desc, default_sampler_state[1].GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

				//	sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
				//	hr = device->CreateSamplerState(&sampler_desc, default_sampler_state[2].GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
				//}

				//{
				//	D3D11_BUFFER_DESC buffer_desc{};
				//	buffer_desc.ByteWidth = sizeof(scene_constants);
				//	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
				//	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				//	buffer_desc.CPUAccessFlags = 0;
				//	buffer_desc.MiscFlags = 0;
				//	buffer_desc.StructureByteStride = 0;
				//	hr = device->CreateBuffer(&buffer_desc, nullptr, constant_buffers[0].GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
				//}




				// ゲームループ
				while (DispatchWindowMessage())
				{
					// タイマー更新
					systemInstace.highResolutionTimer.Tick();
					// ヘッダーにFPSを表示するか
					if (isShowFrameRate)
					{
						// ヘッダーにFPSを表示する
						CalculateFrameStats(systemInstace.highResolutionTimer.TimeStamp());
					}
					// フレーム間秒数
					float elapsedTime = systemInstace.highResolutionTimer.TimeInterval();
					// 1フレーム当たりの最大秒数指定
					const float limitElapsedTime = 1.0f / 5;
					elapsedTime = elapsedTime > limitElapsedTime ? limitElapsedTime : elapsedTime;

					// ゲーム更新
					// シーンが設定されているか
					if (!currentSceneKey.empty())
					{
						// 次のシーンが指定されている場合
						if (!nextSceneKey.empty())
						{
							// シーン切り替え
							scenes[currentSceneKey]->Uninitializr();
							currentSceneKey = nextSceneKey;
							scenes[nextSceneKey]->Initialize();
						}
						// シーン更新
						scenes[currentSceneKey]->Update();
					}

					// ゲーム描画
					ID3D11DeviceContext* immediateContext = systemInstace.graphicsManager.GetDeviceContext();
					ID3D11RenderTargetView* renderTargetView = systemInstace.graphicsManager.GetRenderTargetView();
					ID3D11DepthStencilView* depthStencilView = systemInstace.graphicsManager.GetDepthStencilView();
					IDXGISwapChain* swapChain = systemInstace.graphicsManager.GetSwapChain();

					// 画面クリア＆レンダーターゲット設定
					immediateContext->ClearRenderTargetView(renderTargetView, REFRESH_COLOR);
					immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
					immediateContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);



					// ゲーム処理
					scenes[currentSceneKey]->Render();

					//// UI表示処理
					systemInstace.imguiManager.RenderImGuiFrame();

					// バックバッファに描画した画を画面に表示する。
					swapChain->Present(0, 0);
				}

				// ImGui終了処理
				systemInstace.imguiManager.Uninitialize();

				// 描画終了処理
				systemInstace.graphicsManager.Uninitialize();
			}
			// ウィンドウの削除
			DestroyWindow(hwnd);
		}
		// ウィンドウクラスの削除
		UnregisterClass(CLASS_NAME, hInstance);
	}

	// 正常終了
	return 0;
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
LRESULT CALLBACK WindowProcedure(
	_In_ HWND hwnd,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	// ImGui入力処理
	systemInstace.imguiManager.WndProcHandler(hwnd, msg, wParam, lParam);

	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps{};
		BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostMessage(hwnd, WM_CLOSE, 0, 0);
		}
		break;
	case WM_ENTERSIZEMOVE:
		systemInstace.highResolutionTimer.Stop();
		break;
	case WM_EXITSIZEMOVE:
		systemInstace.highResolutionTimer.Start();
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
	return DefWindowProc(hwnd, msg, wParam, lParam);;
}
#pragma endregion

/// <summary>
/// シーン登録
/// </summary>
/// <typeparam name="T">登録するシーンの型</typeparam>
/// <param name="registerSceneName">登録するシーン名</param>
template<typename T>
void RegisterScene(std::string registerSceneName)
{
	// クラス名をKeyとして上書き登録する
	scenes[registerSceneName] = std::make_unique<T>();
}

/// <summary>
/// シーン登録（既に登録されている場合は登録しない）
/// </summary>
/// <typeparam name="T">登録するシーンの型</typeparam>
/// <param name="registerSceneName">登録するシーン名</param>
/// <returns>結果</returns>
template<typename T>
bool RegisterSceneIfNotExists(std::string registerSceneName)
{
	// すでに登録されている場合登録されない
	if (scenes.find(registerSceneName) != scenes.end()) return false;
	// 新規登録
	RegisterScene<T>(registerSceneName);
	return true;
}

#pragma region シーン変更
/// <summary>
/// シーン変更
/// </summary>
/// <param name="loadSceneName">変更シーン名</param>
void LoadScene(std::string loadSceneName)
{
	if (scenes.find(loadSceneName) != scenes.end())
	{
		// シーンが設定されていない場合、最初の読み込みシーンを設定する
		if (currentSceneKey.empty()) currentSceneKey = loadSceneName;
		nextSceneKey = loadSceneName;
	}
}
#pragma endregion

#pragma region マウスカーソルの表示非表示の設定
/// <summary>
/// マウスカーソルの表示非表示の設定
/// </summary>
/// <param name="isShow">true:表示,false:非表示</param>
void SetShowMouseCursor(bool isShow)
{
	// カーソルは、表示カウントが 0 以上の場合にのみ表示
	int count = ShowCursor(isShow);
	while (isShow ? count < 0 : count >= 0)
	{
		count = ShowCursor(isShow);
	}
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
/// <param name="windowStyle">ウィンドウのスタイル（デフォルトは WS_OVERLAPPEDWINDOW から WS_THICKFRAME を除外）</param>
/// <returns>作成されたウィンドウのハンドル（失敗時は nullptr）</returns>
HWND CreateDefaultWindow(
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

#pragma region ウィンドウメッセージをディスパッチ
/// <summary>
/// ウィンドウメッセージをディスパッチ。
/// falseが返ってきたら、ゲーム終了。
/// </summary>
/// <returns>結果</returns>
bool DispatchWindowMessage()
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
void CalculateFrameStats(float timeStamp)
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
