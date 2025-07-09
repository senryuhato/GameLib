














//
///// <summary>
///// タイトルシーンキー
///// </summary>
//static const std::string TITLE_SCENE = "TitleScene";
//
///// <summary>
///// メインシーンキー
///// </summary>
//static const std::string MAIN_SCENE = "MainScene";
//#pragma endregion
//
//
///// <summary>
///// フレームレートを表示させるか
///// </summary>
//bool isShowFrameRate = true;
//
////
//
///// <summary>
///// 深度ステンシルステート
///// </summary>
//Microsoft::WRL::ComPtr<ID3D11DepthStencilState> defaultDepthStencilState;
//
///// <summary>
///// ラスタライザーステート
///// </summary>
//Microsoft::WRL::ComPtr<ID3D11RasterizerState> defaultRasterizerState[2];
//
//enum BLEND_MODE
//{
//	NONE = 0,
//	ALPHA,
//	ADD,
//	SUBTRACT,
//	REPLACE,
//	MULTIPLY,
//	LIGHTEN,
//	DARKEN,
//	SCREEN,
//	// 最大
//	MODE_MAX,
//};
//
///// <summary>
///// ブレンドステート
///// </summary>
//Microsoft::WRL::ComPtr<ID3D11BlendState> defaultBlendState[BLEND_MODE::MODE_MAX];
//
///// <summary>
///// サンプラーステート
///// </summary>
//Microsoft::WRL::ComPtr<ID3D11SamplerState> defaultSamplerState[3];
//
///// <summary>
///// ViewProjection
///// </summary>
//DirectX::XMFLOAT4X4 viewProjection;
//
///// <summary>
///// ライト位置
///// </summary>
//DirectX::XMFLOAT4 lightDirection;
//
///// <summary>
///// カメラ位置
///// </summary>
//DirectX::XMFLOAT4 cameraPosition;
//
///// <summary>
///// 座標
///// </summary>
//DirectX::XMFLOAT4X4 worldTransform;
//#pragma endregion

//#pragma region C++/CLI Windows アプリケーションのエントリポイント
/// <summary>
/// C++/CLI での Windows アプリケーションのエントリポイント。
/// </summary>
/// <param name="hInstance">現在のインスタンスハンドル</param>
/// <param name="hPrevInstance">以前のインスタンスハンドル（常に NULL）</param>
/// <param name="lpCmdLine">コマンドライン引数</param>
/// <param name="nShowCmd">ウィンドウの表示状態</param>
/// <returns>プログラムの終了コード（通常は 0）</returns>
//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
//{
//	
//
//	// ウィンドウクラスの登録
//	if (RegisterDefaultWindowClass(hInstance, CLASS_NAME, WindowProcedure))
//	{
//		// ウィンドウの作成
//		hwnd = CreateDefaultWindow(hInstance, CLASS_NAME, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE);
//		if (hwnd)
//		{
//			// ウィンドウの表示状態設定(表示と非表示)
//			ShowWindow(hwnd, nShowCmd);
//
//			bool isCreated = false;
//			// DirectX11初期化
//			if (systemInstace.graphicsManager.Initialize(hwnd, DEFAULT_FRAMERATE, FULSCREEN_MODE))
//			{
//				// Imgui初期化
//				systemInstace.imguiManager.Initialize(hwnd, systemInstace.graphicsManager.GetDevice(), systemInstace.graphicsManager.GetDeviceContext());
//
//				// シーン登録
//				RegisterSceneIfNotExists<TitleScene>(TITLE_SCENE);
//				RegisterSceneIfNotExists<MainScene>(MAIN_SCENE);
//				// 最初のシーン設定
//				LoadScene(TITLE_SCENE);
//
//				// カーソル設定
//				SetShowMouseCursor(true);
//
//				// タイマーリセット
//				systemInstace.highResolutionTimer.Reset();
//
//				// ステートの作成
//				CreateState();
//
//				// ゲームループ
//				while (DispatchWindowMessage())
//				{
//					// タイマー更新
//					systemInstace.highResolutionTimer.Tick();
//					// ヘッダーにFPSを表示するか
//					if (isShowFrameRate)
//					{
//						// ヘッダーにFPSを表示する
//						CalculateFrameStats(systemInstace.highResolutionTimer.TimeStamp());
//					}
//					// フレーム間秒数
//					float elapsedTime = systemInstace.highResolutionTimer.TimeInterval();
//					// 1フレーム当たりの最大秒数指定
//					const float limitElapsedTime = 1.0f / 5;
//					elapsedTime = elapsedTime > limitElapsedTime ? limitElapsedTime : elapsedTime;
//
//					// ゲーム更新
//					
//					
//					
//					
//					
//					
//					
//					
//					
//					
//					
//					
//					
//					
//					// ゲーム描画
//					ID3D11DeviceContext* immediateContext = systemInstace.graphicsManager.GetDeviceContext();
//					ID3D11RenderTargetView* renderTargetView = systemInstace.graphicsManager.GetRenderTargetView();
//					ID3D11DepthStencilView* depthStencilView = systemInstace.graphicsManager.GetDepthStencilView();
//					IDXGISwapChain* swapChain = systemInstace.graphicsManager.GetSwapChain();
//
//					// 画面クリア＆レンダーターゲット設定
//					immediateContext->ClearRenderTargetView(renderTargetView, REFRESH_COLOR);
//					immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
//					immediateContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
//
//
//
//
//					// ステート設定
//					immediateContext->PSSetSamplers(0, 3, defaultSamplerState[0].GetAddressOf());
//					immediateContext->OMSetBlendState(defaultBlendState[BLEND_MODE::ALPHA].Get(), nullptr, 0xFFFFFFFF);
//					immediateContext->RSSetState(defaultRasterizerState[0].Get());
//					immediateContext->OMSetDepthStencilState(defaultDepthStencilState.Get(), 1);
//					immediateContext->RSSetState(defaultRasterizerState[0].Get());
//
//					// カメラ作成
//					CreateCamera();
//
//					// ワールド座標設定
//					CreateWorldTransform();
//
//					// ゲーム処理
//					scenes[currentSceneKey]->Render();
//
//					//// UI表示処理
//					systemInstace.imguiManager.RenderImGuiFrame();
//
//					// バックバッファに描画した画を画面に表示する。
//					swapChain->Present(0, 0);
//				}
//
//
//
//
//
//
//				// ImGui終了処理
//				systemInstace.imguiManager.Uninitialize();
//
//				// 描画終了処理
//				systemInstace.graphicsManager.Uninitialize();
//			}
//			// ウィンドウの削除
//			DestroyWindow(hwnd);
//		}
//		// ウィンドウクラスの削除
//		UnregisterClass(CLASS_NAME, hInstance);
//	}
//
//	// 正常終了
//	return 0;
//}
//#pragma endregion

//#pragma region ワールド座標設定
///// <summary>
///// ワールド座標設定
///// </summary>
//void CreateWorldTransform()
//{
//	// 軸変換
//	const DirectX::XMFLOAT4X4 coordinateSystemTransforms[]{
//		{-1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}, // 0:RHS Y-UP 
//	  {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}, // 1:LHS Y-UP 
//	  {-1,0,0,0,0,0,-1,0,0,1,0,0,0,0,0,1}, // 2:RHS Z-UP 
//	  {1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1},  // 3:LHS Z-UP 
//	};
//
//	// 軸
//	const float scale_factor = 1.0f;
//	DirectX::XMMATRIX coordinate{DirectX::XMLoadFloat4x4(&coordinateSystemTransforms[1]) * DirectX::XMMatrixScaling(scale_factor,scale_factor,scale_factor)};
//
//	// XYZの回転設定
//	constexpr float roll = DirectX::XMConvertToRadians(360);
//	constexpr float pitch = DirectX::XMConvertToRadians(360);
//	constexpr float yaw = DirectX::XMConvertToRadians(360);
//
//	// スケーリング行列
//	DirectX::XMMATRIX scale{DirectX::XMMatrixScaling(0.1f,0.1f,0.1f)};
//	// 回転行列
//	DirectX::XMMATRIX rotation{DirectX::XMMatrixRotationRollPitchYaw(roll,pitch,yaw)};
//	// 平行移動行列
//	DirectX::XMMATRIX translation{DirectX::XMMatrixTranslation(0,0,0)};
//
//	// ワールド行列
//	DirectX::XMStoreFloat4x4(&worldTransform,coordinate * scale * rotation * translation);
//}
//#pragma endregion

//#pragma region カメラ作成
///// <summary>
///// カメラ作成
///// </summary>
//void CreateCamera()
//{
//	// 画面サイズ取得
//	D3D11_VIEWPORT viewport;
//	UINT numViewports{ 1 };
//	systemInstace.graphicsManager.GetDeviceContext()->RSGetViewports(&numViewports, &viewport);
//
//	// アスペクト比
//	float aspectRatio{ viewport.Width / viewport.Height };
//	// 透視投影作成
//	DirectX::XMMATRIX projection{ DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(30), aspectRatio, 0.1f, 1000.0f) };
//
//	// カメラ情報設定
//	DirectX::XMVECTOR eye{ DirectX::XMVectorSet(0.0f, 0.0f, -250.0f, 1.0f) };
//	DirectX::XMVECTOR focus{ DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f) };
//	DirectX::XMVECTOR up{ DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) };
//	DirectX::XMMATRIX view{ DirectX::XMMatrixLookAtLH(eye, focus, up) };
//
//	// ViewProjection作成
//	DirectX::XMStoreFloat4x4(&viewProjection, view * projection);
//}
//#pragma endregion
//
//#pragma region ステートの作成
///// <summary>
///// ステートの作成
///// </summary>
//void CreateState()
//{
//	HRESULT hr = S_OK;
//
//	// 深度ステンシルステートの作成
//	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
//	depthStencilDesc.DepthEnable = TRUE;
//	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
//	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
//	depthStencilDesc.StencilEnable = FALSE;
//	depthStencilDesc.StencilReadMask = 0xFF;
//	depthStencilDesc.StencilWriteMask = 0xFF;
//	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
//	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
//	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
//	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
//	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
//	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
//	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
//	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
//	hr = systemInstace.graphicsManager.GetDevice()->CreateDepthStencilState(&depthStencilDesc, defaultDepthStencilState.GetAddressOf());
//	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
//
//	// ラスタライザーステート
//	D3D11_RASTERIZER_DESC rasterizerDesc = {};
//	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
//	rasterizerDesc.CullMode = D3D11_CULL_BACK;
//	rasterizerDesc.DepthBias = 0;
//	rasterizerDesc.DepthBiasClamp = 0;
//	rasterizerDesc.SlopeScaledDepthBias = 0;
//	rasterizerDesc.DepthClipEnable = TRUE;
//	rasterizerDesc.ScissorEnable = FALSE;
//	rasterizerDesc.MultisampleEnable = TRUE;
//	rasterizerDesc.AntialiasedLineEnable = FALSE;
//	// DirectX軸
//	rasterizerDesc.FrontCounterClockwise = FALSE;
//	hr = systemInstace.graphicsManager.GetDevice()->CreateRasterizerState(&rasterizerDesc, defaultRasterizerState[0].GetAddressOf());
//	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
//	// OpenGL軸
//	rasterizerDesc.FrontCounterClockwise = TRUE;
//	hr = systemInstace.graphicsManager.GetDevice()->CreateRasterizerState(&rasterizerDesc, defaultRasterizerState[1].GetAddressOf());
//	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
//
//	// ブレンドステート
//	CreateBlendState();
//
//	// サンプラーステート
//	D3D11_SAMPLER_DESC samplerDesc;
//	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
//	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
//	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
//	samplerDesc.MipLODBias = 0;
//	samplerDesc.MaxAnisotropy = 16;
//	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
//	samplerDesc.BorderColor[0] = 0.0f;
//	samplerDesc.BorderColor[1] = 0.0f;
//	samplerDesc.BorderColor[2] = 0.0f;
//	samplerDesc.BorderColor[3] = 0.0f;
//	samplerDesc.MinLOD = 0;
//	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
//	// 
//	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
//	hr = systemInstace.graphicsManager.GetDevice()->CreateSamplerState(&samplerDesc, defaultSamplerState[0].GetAddressOf());
//	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
//	// 
//	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
//	hr = systemInstace.graphicsManager.GetDevice()->CreateSamplerState(&samplerDesc, defaultSamplerState[1].GetAddressOf());
//	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
//	// 
//	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
//	hr = systemInstace.graphicsManager.GetDevice()->CreateSamplerState(&samplerDesc, defaultSamplerState[2].GetAddressOf());
//	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
//}
//#pragma endregion
//
//#pragma region ブレンドステートの作成
///// <summary>
///// ブレンドステートの作成
///// </summary>
//void CreateBlendState()
//{
//	HRESULT hr;
//
//	D3D11_BLEND_DESC bDesc = {};
//	bDesc.AlphaToCoverageEnable = FALSE;
//	bDesc.IndependentBlendEnable = FALSE;
//	bDesc.RenderTarget[0].BlendEnable = TRUE;
//
//	// NONE(なし)
//	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
//	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
//	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
//	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
//	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
//	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
//	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
//
//	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::NONE]);
//
//	// ALPHA()
//	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
//	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
//	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
//	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
//	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
//	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
//	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
//
//	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::ALPHA]);
//
//	// ADD(加算)
//	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
//	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
//	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
//	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
//	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
//	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
//	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
//
//	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::ADD]);
//
//	// SUBTRACT(減産)
//	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
//	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
//	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_SUBTRACT;
//	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
//	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
//	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
//	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
//
//	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::SUBTRACT]);
//
//	// REPLACE
//	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
//	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
//	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
//	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
//	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
//	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
//	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
//
//	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::REPLACE]);
//
//	// MULTIPLY(乗算)
//	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
//	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_COLOR;
//	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
//	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_DEST_ALPHA;
//	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
//	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
//	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
//
//	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::MULTIPLY]);
//
//	// LIGHTEN
//	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
//	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
//	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MAX;
//	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_DEST_ALPHA;
//	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
//	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
//	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
//
//	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::LIGHTEN]);
//
//	// DARKEN
//	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
//	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
//	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MIN;
//	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
//	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
//	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MIN;
//	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
//
//	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::DARKEN]);
//
//	// SCREEN
//	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
//	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
//	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
//	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
//	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
//	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
//	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
//
//	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::SCREEN]);
//}
//#pragma endregion

//#pragma once
//#include <Windows.h>
//#include <string>
//
///// <summary>
///// ワールド座標設定
///// </summary>
//void CreateWorldTransform();
//
///// <summary>
///// カメラ作成
///// </summary>
//void CreateCamera();
//
///// <summary>
///// ステートの作成
///// </summary>
//void CreateState();
//
///// <summary>
///// デフォルト設定でウィンドウを作成します。
///// 指定されたウィンドウクラスを使用し、標準的な設定のウィンドウを作成します。
///// クライアント領域のサイズを指定し、それに合うウィンドウサイズを自動調整します。
///// </summary>
///// <param name="instance">アプリケーションのインスタンスハンドル</param>
///// <param name="className">ウィンドウクラスの名前</param>
///// <param name="screenWidth">クライアント領域の幅（ピクセル）</param>
///// <param name="screenHeight">クライアント領域の高さ（ピクセル）</param>
///// <param name="windowTitle">ウィンドウのタイトル</param>
///// <param name="windowStyle">ィンドウのスタイル（デフォルトは WS_OVERLAPPEDWINDOW から WS_THICKFRAME を除外）</param>
///// <returns>作成されたウィンドウのハンドル（失敗時は nullptr）</returns>
//HWND CreateDefaultWindow(
//	_In_ HINSTANCE instance,
//	_In_ LPCWSTR className,
//	_In_ LONG screenWidth,
//	_In_ LONG screenHeight,
//	_In_ LPCWSTR windowTitle,
//	_In_ DWORD windowStyle = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_VISIBLE);
//
///// <summary>
///// ブレンドステートの作成
///// </summary>
//void CreateBlendState();
//
///// <summary>
///// シーン登録
///// </summary>
///// <typeparam name="T">登録するシーンの型</typeparam>
///// <param name="registerSceneName">登録するシーン名</param>
//template<typename T>
//void RegisterScene(std::string registerSceneName);
//
///// <summary>
///// シーン登録（既に登録されている場合は登録しない）
///// </summary>
///// <typeparam name="T">登録するシーンの型</typeparam>
///// <param name="registerSceneName">登録するシーン名</param>
///// <returns>結果</returns>
//template<typename T>
//bool RegisterSceneIfNotExists(std::string registerSceneName);
//
///// <summary>
///// シーン変更
///// </summary>
///// <param name="loadSceneName">変更シーン名</param>
//void LoadScene(std::string loadSceneName);
//
///// <summary>
///// マウスカーソルの表示非表示の設定
///// </summary>
///// <param name="isShow">true:表示,false:非表示</param>
//void SetShowMouseCursor(bool isShow);
//
///// <summary>
///// ウィンドウメッセージを処理するコールバック関数（Win32 API 用）
///// </summary>
///// <param name="hwnd">ウィンドウハンドル</param>
///// <param name="msg">受け取ったメッセージ</param>
///// <param name="wParam">メッセージの追加情報（1つ目のパラメータ）</param>
///// <param name="lParam">メッセージの追加情報（2つ目のパラメータ）</param>
///// <returns>メッセージを処理した結果（通常は `DefWindowProc` の戻り値を返す）</returns>
//static LRESULT CALLBACK WindowProcedure(
//	_In_ HWND hwnd,
//	_In_ UINT msg,
//	_In_ WPARAM wParam,
//	_In_ LPARAM lParam);
//
///// <summary>
///// デフォルト設定でウィンドウクラスを登録します。
///// 指定されたウィンドウプロシージャを持つ、標準的な設定のウィンドウクラスを登録します。
///// 背景色、カーソル、スタイルなどのパラメータは固定されています。
///// </summary>
///// <param name="instance">アプリケーションのインスタンスハンドル</param>
///// <param name="applicationName">登録するウィンドウクラスの名前</param>
///// <param name="windowProcedure">ウィンドウプロシージャ（メッセージ処理関数）</param>
///// <returns>true:成功 false:失敗</returns>
//bool RegisterDefaultWindowClass(
//	_In_ HINSTANCE instance,
//	_In_ LPCWSTR applicationName,
//	_In_ WNDPROC windowProcedure);
//
///// <summary>
///// ウィンドウメッセージをディスパッチ。
///// falseが返ってきたら、ゲーム終了。
///// </summary>
///// <returns></returns>
//bool DispatchWindowMessage();
//
///// <summary>
///// FPS計算
///// </summary>
///// <param name="timeStamp">経過した合計時間</param>
//void CalculateFrameStats(float timeStamp);


//#pragma once
//
//#include	<d3d11.h>
//
//class ResourceManager
//{
//private:
//	static const int RESOURCE_MAX = 128;
//
//	struct ShaderResourceViewData
//	{
//		wchar_t						filename[256];
//		ID3D11ShaderResourceView* shader_resource_view;
//		D3D11_TEXTURE2D_DESC		texDesc;
//		int							count;
//
//		ShaderResourceViewData(): shader_resource_view(nullptr),count(0)
//		{
//			ZeroMemory(filename,sizeof(filename));
//		}
//
//		void Release(bool bForce = false)
//		{
//			if(count <= 0)	return;
//			if(--count <= 0)	bForce = true;
//			if(bForce)
//			{
//				shader_resource_view->Release();
//				ZeroMemory(this,sizeof(ShaderResourceViewData));	//	念の為に完全消去します
//			}
//		}
//	};
//
//	struct VertexShadersData
//	{
//		char						filename[256];
//		ID3D11VertexShader* vertex_shader;
//		ID3D11InputLayout* input_layout;
//		int							count;
//
//		VertexShadersData(): vertex_shader(nullptr),input_layout(nullptr),count(0)
//		{
//			ZeroMemory(filename,sizeof(filename));
//		}
//
//		void Release(bool bForce = false)
//		{
//			if(count <= 0)	return;
//			if(--count <= 0)	bForce = true;
//			if(bForce)
//			{
//				vertex_shader->Release();
//				input_layout->Release();
//				ZeroMemory(this,sizeof(VertexShadersData));	//	念の為に完全消去します
//			}
//		}
//
//	};
//
//	struct PixelShadersData
//	{
//		char						filename[256];
//		ID3D11PixelShader* pixel_shader;
//		int							count;
//
//		PixelShadersData(): pixel_shader(nullptr),count(0)
//		{
//			ZeroMemory(filename,sizeof(filename));
//		}
//		void Release(bool bForce = false)
//		{
//			if(count <= 0)	return;
//			if(--count <= 0)	bForce = true;
//			if(bForce)
//			{
//				pixel_shader->Release();
//				ZeroMemory(this,sizeof(PixelShadersData));	//	念の為に完全消去します
//			}
//		}
//	};
//
//	static ShaderResourceViewData	srvData[RESOURCE_MAX];
//	static VertexShadersData		vsData[RESOURCE_MAX];
//	static PixelShadersData			psData[RESOURCE_MAX];
//
//
//	ResourceManager() {}
//	~ResourceManager() {
//		Release();
//	}
//
//public:
//	static void Release()
//	{
//		for(int n = 0; n < RESOURCE_MAX; n++)
//		{
//			srvData[n].Release(true);
//			vsData[n].Release(true);
//			psData[n].Release(true);
//		}
//	}
//
//	static bool LoadShaderResourceView(ID3D11Device* device,const wchar_t* filename,
//		ID3D11ShaderResourceView** srv,D3D11_TEXTURE2D_DESC** texDesc);
//
//	static void ReleaseShaderResourceView(ID3D11ShaderResourceView* srv);
//
//
//	static bool LoadVertexShaders(ID3D11Device* device,const char* filename,
//		D3D11_INPUT_ELEMENT_DESC* elementDescs,int numElement,
//		ID3D11VertexShader** vs,ID3D11InputLayout** il);
//
//	static void ReleaseVertexShaders(ID3D11VertexShader* vs,ID3D11InputLayout* il);
//
//
//	static bool LoadPixelShaders(ID3D11Device* device,const char* filename,ID3D11PixelShader** ps);
//	static void ReleasePixelShaders(ID3D11PixelShader* ps);
//
//};

//#include "Resources.h"
//#include <stdio.h>
//#include "../GameXLib/ThirdParty/DirectXTex/WICTextureLoader11.h"
//
//ResourceManager::ShaderResourceViewData	ResourceManager::srvData[ResourceManager::RESOURCE_MAX];
//ResourceManager::VertexShadersData		ResourceManager::vsData[ResourceManager::RESOURCE_MAX];
//ResourceManager::PixelShadersData		ResourceManager::psData[ResourceManager::RESOURCE_MAX];
//
//
////	CSOファイル読み込み関数
//bool	LoadCSOFile(BYTE** data,long* size,const char* filename)
//{
//	FILE* fp;
//	//	ファイルオープン
//	if(fopen_s(&fp,filename,"rb"))	return false;
//
//	//	ファイルサイズ取得
//	fseek(fp,0,SEEK_END);		//	ファイルポインタを終端に移動
//	long sz = ftell(fp);		//	終端位置の保存 = ファイルサイズ
//	fseek(fp,0,SEEK_SET);		//	ファイルポインタを最初に戻す
//
//	//	ファイル読み込み用領域の確保
//	*data = new BYTE[sz];
//	//	ファイル読み込み
//	size_t s = fread_s(*data,sizeof(BYTE) * sz,
//		sizeof(BYTE),sz,fp);
//
//	//	読み込み終了
//	fclose(fp);
//
//	//	エラーチェック
//	if(s != sizeof(BYTE) * sz)	return false;
//
//	*size = sz;			//	ファイルサイズ保存
//	return	true;
//}
//
//bool ResourceManager::LoadShaderResourceView(ID3D11Device* device,const wchar_t* filename,
//	ID3D11ShaderResourceView** srv,D3D11_TEXTURE2D_DESC** texDesc)
//{
//	//	エラーチェック
//	if(!device)		return false;
//	if(!filename)		return false;
//	if(*srv)			return false;
//
//	HRESULT hr;
//	ShaderResourceViewData* find = nullptr;
//	int no = -1;
//
//	//	対象のファイルが既に存在しているかを検索
//	for(int n = 0; n < RESOURCE_MAX; n++)
//	{
//		ShaderResourceViewData* p = &srvData[n];
//
//		//	データの有無確認
//		if(p->count <= 0)
//		{
//			if(no == -1)		no = n;
//			continue;
//		}
//
//		//	文字列比較
//		if(wcscmp(p->filename,filename) != 0)	continue;
//
//		//	一致したから読み込んでる => 発見!
//		find = p;
//
//		break;
//	}
//	//	ファイルが見つからなかったら新規読み込み
//	if(!find)
//	{
//		if(no == -1)	return	false;		//	空きが無い
//
//		find = &srvData[no];
//		//	テクスチャ読み込み
//		ID3D11Resource* resource = nullptr;
//		hr = DirectX::CreateWICTextureFromFile(device,filename,&resource,
//			&find->shader_resource_view);
//		//		→データが読み込めなかったら return false;
//		if(FAILED(hr))	return false;
//
//		//	texture2d_descの取得
//		ID3D11Texture2D* texture2d;
//		hr = resource->QueryInterface(&texture2d);
//		//		→データが読み込めなかったら return false;
//		if(FAILED(hr))
//		{
//			resource->Release();
//			find->shader_resource_view->Release();
//			return false;
//		}
//		//	texture2d_desc保存
//		texture2d->GetDesc(&find->texDesc);
//
//		//	ポインタ変数 解放
//		texture2d->Release();
//		resource->Release();
//
//		//	ファイル名のコピー
//		wcscpy_s(find->filename,256,filename);
//	}
//
//
//	//////////////////////////
//	//	共通部
//	//////////////////////////
//
//	*srv = find->shader_resource_view;	//	ShaderResourceView保存
//	*texDesc = &find->texDesc;				//	texture2d_desc保存
//
//	//	保持数増加
//	find->count++;
//
//
//	return	true;
//}
//
//void ResourceManager::ReleaseShaderResourceView(ID3D11ShaderResourceView* srv)
//{
//	if(!srv)			return;		//	検索対象Unknown　終了します
//	//	Targetの検索開始
//	for(int n = 0; n < RESOURCE_MAX; n++)
//	{
//		ShaderResourceViewData* p = &srvData[n];
//
//		//	未使用データなら、次のデータへ移行します
//		if(p->count == 0)	continue;
//		//	検索対象と不一致なら、次のデータへ移行します
//		if(p->shader_resource_view != srv)	continue;
//
//		//	Targetを発見 Releaseします
//		p->Release();
//		break;
//	}
//}
//bool ResourceManager::LoadVertexShaders(ID3D11Device* device,const char* filename,
//	D3D11_INPUT_ELEMENT_DESC* elementDescs,int numElement,
//	ID3D11VertexShader** vs,ID3D11InputLayout** il)
//{
//	//	エラーチェック
//	if(!device)		return false;
//	if(!filename)		return false;
//	if(*vs)			return false;
//	if(*il)			return false;
//
//	HRESULT hr;
//	VertexShadersData* find = nullptr;
//	int no = -1;
//
//	//	対象のファイルが既に存在しているかを検索
//	for(int n = 0; n < RESOURCE_MAX; n++)
//	{
//		VertexShadersData* p = &vsData[n];
//
//		//	データの有無確認
//		if(p->count == 0)
//		{
//			if(no == -1)	no = n;
//			continue;
//		}
//		//	文字列比較
//		if(strcmp(p->filename,filename) != 0)	continue;
//
//		//	一致したから読み込んでる => 発見!
//		find = p;
//		//	ついでに作るものがあればここで
//		//		→ VertexShadersの場合、特に無し
//		break;
//	}
//
//	//	ファイルが見つからなかったら新規読み込み
//	if(!find)
//	{
//		if(no == -1)	return	false;		//	空きが無い
//
//		find = &vsData[no];
//		//	新規読み込み
//		BYTE* shader_data;
//		long				size;
//		LoadCSOFile(&shader_data,&size,filename);
//		hr = device->CreateVertexShader(shader_data,size,nullptr,&find->vertex_shader);
//		//		→データが読み込めなかったら return false;
//		if(FAILED(hr))	return	false;
//
//		hr = device->CreateInputLayout(elementDescs,numElement,
//			shader_data,size,&find->input_layout);
//		delete[] shader_data;
//		//		→データが読み込めなかったら return false;
//		if(FAILED(hr))
//		{
//			find->vertex_shader->Release();
//			return false;
//		}
//
//		//	ファイル名のコピー
//		strcpy_s(find->filename,256,filename);
//	}
//
//	//////////////////////////
//	//	共通部
//	//////////////////////////
//
//	//	共通して作るものがあればここで作る
//	//		→VertexShadersで特にやる事は無し
//
//	//	データを返す
//	*vs = find->vertex_shader;
//	*il = find->input_layout;
//
//	//	保持数増加
//	find->count++;
//
//	return	true;
//}
//
//void ResourceManager::ReleaseVertexShaders(ID3D11VertexShader* vs,ID3D11InputLayout* il)
//{
//	if(!vs)			return;		//	検索対象Unknown　終了します
//	if(!il)			return;		//	検索対象Unknown　終了します
//
//	//	Targetの検索開始
//	for(int n = 0; n < RESOURCE_MAX; n++)
//	{
//		VertexShadersData* p = &vsData[n];
//
//		//	未使用データなら、次のデータへ移行します
//		if(p->count == 0)	continue;
//		//	検索対象と不一致なら、次のデータへ移行します
//		if(p->vertex_shader != vs)	continue;
//		if(p->input_layout != il)	continue;
//
//		//	Targetを発見 Releaseします
//		p->Release();
//		break;
//	}
//}
//
//bool ResourceManager::LoadPixelShaders(ID3D11Device* device,const char* filename,ID3D11PixelShader** ps)
//{
//	//	エラーチェック
//	if(!device)		return false;
//	if(!filename)		return false;
//	if(*ps)			return false;
//
//	HRESULT hr;
//	PixelShadersData* find = nullptr;
//	int no = -1;
//
//	//	対象のファイルが既に存在しているかを検索
//	for(int n = 0; n < RESOURCE_MAX; n++)
//	{
//		PixelShadersData* p = &psData[n];
//
//		//	データの有無確認
//		if(p->count == 0)
//		{
//			if(no == -1)	no = n;
//			continue;
//		}
//		//	文字列比較
//		if(strcmp(p->filename,filename) != 0)	continue;
//
//		//	一致したから読み込んでる => 発見!
//		find = p;
//		//	ついでに作るものがあればここで
//		//		→ VertexShadersの場合、特に無し
//		break;
//	}
//
//	//	ファイルが見つからなかったら新規読み込み
//	if(!find)
//	{
//		if(no == -1)	return	false;		//	空きが無い
//
//		find = &psData[no];
//		//	新規読み込み
//		BYTE* shader_data;
//		long				size;
//		LoadCSOFile(&shader_data,&size,filename);
//		hr = device->CreatePixelShader(shader_data,size,nullptr,&find->pixel_shader);
//		//		→データが読み込めなかったら return false;
//		if(FAILED(hr))	return	false;
//
//		//	ファイル名のコピー
//		strcpy_s(find->filename,256,filename);
//
//		delete[]	shader_data;
//	}
//
//	//////////////////////////
//	//	共通部
//	//////////////////////////
//
//	//	共通して作るものがあればここで作る
//	//		→VertexShadersで特にやる事は無し
//
//	//	データを返す
//	*ps = find->pixel_shader;
//
//	//	保持数増加
//	find->count++;
//
//	return	true;
//}
//
//void ResourceManager::ReleasePixelShaders(ID3D11PixelShader* ps)
//{
//	if(!ps)			return;		//	検索対象Unknown　終了します
//
//	//	Targetの検索開始
//	for(int n = 0; n < RESOURCE_MAX; n++)
//	{
//		PixelShadersData* p = &psData[n];
//
//		//	未使用データなら、次のデータへ移行します
//		if(p->count == 0)	continue;
//		//	検索対象と不一致なら、次のデータへ移行します
//		if(p->pixel_shader != ps)	continue;
//
//		//	Targetを発見 Releaseします
//		p->Release();
//		break;
//	}
//}
