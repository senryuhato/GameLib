#include <crtdbg.h>
#include <time.h>
#include <sstream>
#include <map>
#include <DirectXMath.h>
#include "../GameXLib\Runtime\Scene\Scene.h"
#include "../GameXLib/Runtime/System/Misc.h"
#include "WinMain.h"
#include "SystemInstance.h"
#include "Scene\TitleScene.h"
#include "Scene\MainScene.h"

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

/// <summary>
/// 深度ステンシルステート
/// </summary>
Microsoft::WRL::ComPtr<ID3D11DepthStencilState> defaultDepthStencilState;

/// <summary>
/// ラスタライザーステート
/// </summary>
Microsoft::WRL::ComPtr<ID3D11RasterizerState> defaultRasterizerState[2];

enum BLEND_MODE
{
	NONE = 0,
	ALPHA,
	ADD,
	SUBTRACT,
	REPLACE,
	MULTIPLY,
	LIGHTEN,
	DARKEN,
	SCREEN,
	// 最大
	MODE_MAX,
};

/// <summary>
/// ブレンドステート
/// </summary>
Microsoft::WRL::ComPtr<ID3D11BlendState> defaultBlendState[BLEND_MODE::MODE_MAX];

/// <summary>
/// サンプラーステート
/// </summary>
Microsoft::WRL::ComPtr<ID3D11SamplerState> defaultSamplerState[3];

/// <summary>
/// ViewProjection
/// </summary>
DirectX::XMFLOAT4X4 viewProjection;

/// <summary>
/// ライト位置
/// </summary>
DirectX::XMFLOAT4 lightDirection;

/// <summary>
/// カメラ位置
/// </summary>
DirectX::XMFLOAT4 cameraPosition;

/// <summary>
/// 座標
/// </summary>
DirectX::XMFLOAT4X4 worldTransform;
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

				// ステートの作成
				CreateState();

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




					// ステート設定
					immediateContext->PSSetSamplers(0, 3, defaultSamplerState[0].GetAddressOf());
					immediateContext->OMSetBlendState(defaultBlendState[BLEND_MODE::ALPHA].Get(), nullptr, 0xFFFFFFFF);
					immediateContext->RSSetState(defaultRasterizerState[0].Get());
					immediateContext->OMSetDepthStencilState(defaultDepthStencilState.Get(), 1);
					immediateContext->RSSetState(defaultRasterizerState[0].Get());

					// カメラ作成
					CreateCamera();

					// ワールド座標設定
					CreateWorldTransform();







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

#pragma region ワールド座標設定
/// <summary>
/// ワールド座標設定
/// </summary>
void CreateWorldTransform()
{
	// 軸変換
	const DirectX::XMFLOAT4X4 coordinateSystemTransforms[]{
	  { -1, 0, 0, 0, 0, 1,  0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }, // 0:RHS Y-UP 
	  {  1, 0, 0, 0, 0, 1,  0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }, // 1:LHS Y-UP 
	  { -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 1 }, // 2:RHS Z-UP 
	  {  1, 0, 0, 0, 0, 0,  1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },  // 3:LHS Z-UP 
	};

	// 軸
	const float scale_factor = 1.0f;
	DirectX::XMMATRIX coordinate{ DirectX::XMLoadFloat4x4(&coordinateSystemTransforms[1]) * DirectX::XMMatrixScaling(scale_factor, scale_factor, scale_factor) };

	// XYZの回転設定
	constexpr float roll = DirectX::XMConvertToRadians(360);
	constexpr float pitch = DirectX::XMConvertToRadians(360);
	constexpr float yaw = DirectX::XMConvertToRadians(360);

	// スケーリング行列
	DirectX::XMMATRIX scale{ DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f) };
	// 回転行列
	DirectX::XMMATRIX rotation{ DirectX::XMMatrixRotationRollPitchYaw(roll, pitch, yaw) };
	// 平行移動行列
	DirectX::XMMATRIX translation{ DirectX::XMMatrixTranslation(0,0,0) };

	// ワールド行列
	DirectX::XMStoreFloat4x4(&worldTransform, coordinate * scale * rotation * translation);
}
#pragma endregion

#pragma region カメラ作成
/// <summary>
/// カメラ作成
/// </summary>
void CreateCamera()
{
	// 画面サイズ取得
	D3D11_VIEWPORT viewport;
	UINT numViewports{ 1 };
	systemInstace.graphicsManager.GetDeviceContext()->RSGetViewports(&numViewports, &viewport);

	// アスペクト比
	float aspectRatio{ viewport.Width / viewport.Height };
	// 透視投影作成
	DirectX::XMMATRIX projection{ DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(30), aspectRatio, 0.1f, 1000.0f) };

	// カメラ情報設定
	DirectX::XMVECTOR eye{ DirectX::XMVectorSet(0.0f, 0.0f, -250.0f, 1.0f) };
	DirectX::XMVECTOR focus{ DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f) };
	DirectX::XMVECTOR up{ DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) };
	DirectX::XMMATRIX view{ DirectX::XMMatrixLookAtLH(eye, focus, up) };

	// ViewProjection作成
	DirectX::XMStoreFloat4x4(&viewProjection, view * projection);
}
#pragma endregion

#pragma region ステートの作成
/// <summary>
/// ステートの作成
/// </summary>
void CreateState()
{
	HRESULT hr = S_OK;

	// 深度ステンシルステートの作成
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	hr = systemInstace.graphicsManager.GetDevice()->CreateDepthStencilState(&depthStencilDesc, defaultDepthStencilState.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));

	// ラスタライザーステート
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0;
	rasterizerDesc.SlopeScaledDepthBias = 0;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.ScissorEnable = FALSE;
	rasterizerDesc.MultisampleEnable = TRUE;
	rasterizerDesc.AntialiasedLineEnable = FALSE;
	// DirectX軸
	rasterizerDesc.FrontCounterClockwise = FALSE;
	hr = systemInstace.graphicsManager.GetDevice()->CreateRasterizerState(&rasterizerDesc, defaultRasterizerState[0].GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
	// OpenGL軸
	rasterizerDesc.FrontCounterClockwise = TRUE;
	hr = systemInstace.graphicsManager.GetDevice()->CreateRasterizerState(&rasterizerDesc, defaultRasterizerState[1].GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));

	// ブレンドステート
	CreateBlendState();

	// サンプラーステート
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	// 
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	hr = systemInstace.graphicsManager.GetDevice()->CreateSamplerState(&samplerDesc, defaultSamplerState[0].GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
	// 
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	hr = systemInstace.graphicsManager.GetDevice()->CreateSamplerState(&samplerDesc, defaultSamplerState[1].GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
	// 
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	hr = systemInstace.graphicsManager.GetDevice()->CreateSamplerState(&samplerDesc, defaultSamplerState[2].GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
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

#pragma region ブレンドステートの作成
/// <summary>
/// ブレンドステートの作成
/// </summary>
void CreateBlendState()
{
	HRESULT hr;

	D3D11_BLEND_DESC bDesc = {};
	bDesc.AlphaToCoverageEnable = FALSE;
	bDesc.IndependentBlendEnable = FALSE;
	bDesc.RenderTarget[0].BlendEnable = TRUE;

	// NONE(なし)
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::NONE]);

	// ALPHA()
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::ALPHA]);

	// ADD(加算)
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::ADD]);

	// SUBTRACT(減産)
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_SUBTRACT;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::SUBTRACT]);

	// REPLACE
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::REPLACE]);

	// MULTIPLY(乗算)
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_COLOR;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_DEST_ALPHA;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::MULTIPLY]);

	// LIGHTEN
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MAX;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_DEST_ALPHA;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::LIGHTEN]);

	// DARKEN
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MIN;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MIN;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::DARKEN]);

	// SCREEN
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::SCREEN]);
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
		// 拡張ウィンドウスタイル（なし）
		0,
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
