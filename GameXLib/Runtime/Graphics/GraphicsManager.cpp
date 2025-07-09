#include "../System/Misc.h"
#include "GraphicsManager.h"

bool GraphicsManager::Initialize(
	HWND hwnd,
	UINT defaultFramerate,
	BOOL isFullscreen)
{
	// フレームレートの設定
	this->defaultFramerate = defaultFramerate;
	// 画面のサイズを取得する。
	RECT rc;
	GetClientRect(hwnd, &rc);
	frameBufferWidth = rc.right - rc.left;
	frameBufferHeight = rc.bottom - rc.top;

	// デバイス＆スワップチェインの作成
	CreateDeviceAndSwapChain(hwnd, frameBufferWidth, frameBufferHeight, defaultFramerate, isFullscreen);
	// フレームバッファ用RTVの作成
	CreateRTVForFrameBuffer();
	// フレームバッファ用DSVの作成
	CreateDSVForFrameBuffer(frameBufferWidth, frameBufferHeight);

	// ビューポートの設定
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<FLOAT>(frameBufferWidth);
	viewport.Height = static_cast<FLOAT>(frameBufferHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	immediateContext->RSSetViewports(1, &viewport);

	return true;
}

void GraphicsManager::Uninitialize()
{
	// フルスクリーンなら終了時にウィンドウモードに戻す。(Alt+Enterで切り替えができる)
	BOOL fullscreen = 0;
	if (swapChain)
	{
		swapChain->GetFullscreenState(&fullscreen, 0);
		if (fullscreen)
		{
			swapChain->SetFullscreenState(FALSE, 0);
		}
	}
}

void GraphicsManager::CreateDeviceAndSwapChain(
	HWND hwnd,
	UINT frameBufferWidth,
	UINT frameBufferHeight,
	UINT defaultFramerate,
	BOOL isFullscreen)
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// 機能レベル
	// シェーダーモデル5.0は_11_1以上でないといけない。
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_12_1, // DirectX 12.1
	    D3D_FEATURE_LEVEL_12_0, // DirectX 12.0
	    D3D_FEATURE_LEVEL_11_1, // DirectX 11.1
	    D3D_FEATURE_LEVEL_11_0, // DirectX 11.0
	};

	// スワップチェインを作成するための設定
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	{
		swapChainDesc.BufferDesc.Width = frameBufferWidth; // 解像度（幅）
		swapChainDesc.BufferDesc.Height = frameBufferHeight; // 解像度（高さ）
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 1ピクセルあたりの各色(RGBA)を8bit(0～255)のテクスチャ(バックバッファ)を作成する。
		swapChainDesc.BufferDesc.RefreshRate.Numerator = defaultFramerate; // リフレッシュレート
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.SampleDesc.Count = 1; // マルチサンプリングなし
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferCount = 1; // バックバッファの数
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // レンダリングターゲットとして使う
		swapChainDesc.OutputWindow = hwnd; // DirectXで書いた画を表示するウィンドウ
		swapChainDesc.Windowed = !isFullscreen; // ウィンドウモードか、フルスクリーンにするか。
	}

	D3D_FEATURE_LEVEL featureLevel{};

	// デバイス＆スワップチェインの生成
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,                   // どのビデオアダプタを使用するか？既定ならばnullptrで、IDXGIAdapterのアドレスを渡す。
		D3D_DRIVER_TYPE_HARDWARE,  // ドライバのタイプを渡す。D3D_DRIVER_TYPE_HARDWARE 以外は基本的にソフトウェア実装で、特別なことをする場合に用いる。
		nullptr,                   // 上記をD3D_DRIVER_TYPE_SOFTWAREに設定した際に、その処理を行うDLLのハンドルを渡す。それ以外を指定している際には必ずnullptrを渡す。
		createDeviceFlags,         // 何らかのフラグを指定する。 詳しくはD3D11_CREATE_DEVICE列挙型で検索。
		featureLevels,             // D3D_FEATURE_LEVEL列挙型の配列を与える。nullptrにすることでも上記featureと同等の内容の配列が使用される。
		ARRAYSIZE(featureLevels),  // feature_levels配列の要素数を渡す。
		D3D11_SDK_VERSION,         // SDKのバージョン。必ずこの値。
		&swapChainDesc,            // ここで設定した構造体に設定されているパラメータでSwapChainが作成される。
		swapChain.GetAddressOf(),  // 作成が成功した場合に、swap_chainのアドレスを格納するポインタ変数へのアドレス。ここで指定したポインタ変数経由でswap_chainを操作する。
		device.GetAddressOf(),     // 作成が成功した場合に、deviceのアドレスを格納するポインタ変数へのアドレス。ここで指定したポインタ変数経由でdeviceを操作する。
		&featureLevel,             // 作成に成功したD3D_FEATURE_LEVELを格納するためのD3D_FEATURE_LEVEL列挙型変数のアドレスを設定する。
		immediateContext.GetAddressOf() // 作成が成功した場合に、contextのアドレスを格納するポインタ変数へのアドレス。ここで指定したポインタ変数経由でicontextを操作する。
	);

	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
}

void GraphicsManager::CreateRTVForFrameBuffer()
{
	HRESULT hr = S_OK;

	// スワップチェーンからバックバッファテクスチャを取得する。
	// ※スワップチェーンに内包されているバックバッファテクスチャは'色'を書き込むテクスチャ。
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(backBuffer.GetAddressOf()));
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));

	// バックバッファテクスチャへの書き込みの窓口となるレンダーターゲットビューを生成する。
	hr = device->CreateRenderTargetView(backBuffer.Get(), nullptr, renderTargetView.GetAddressOf());

	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
}
#pragma endregion

void GraphicsManager::CreateDSVForFrameBuffer(
	UINT frameBufferWidth,
	UINT frameBufferHeight)
{
	HRESULT hr = S_OK;

	// 深度ステンシル情報を書き込むためのテクスチャを作成する。
	D3D11_TEXTURE2D_DESC texture2dDesc{};
	texture2dDesc.Width = frameBufferWidth;
	texture2dDesc.Height = frameBufferHeight;
	texture2dDesc.MipLevels = 1;
	texture2dDesc.ArraySize = 1;
	texture2dDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;	// 1ピクセルあたり、深度情報を24Bit / ステンシル情報を8bitのテクスチャを作成する。
	texture2dDesc.SampleDesc.Count = 1;
	texture2dDesc.SampleDesc.Quality = 0;
	texture2dDesc.Usage = D3D11_USAGE_DEFAULT;
	texture2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;		// 深度ステンシル用のテクスチャを作成する。
	texture2dDesc.CPUAccessFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer{};
	hr = device->CreateTexture2D(&texture2dDesc, nullptr, depthStencilBuffer.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));

	// 深度ステンシルテクスチャへの書き込みに窓口になる深度ステンシルビューを作成する。
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = texture2dDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	hr = device->CreateDepthStencilView(depthStencilBuffer.Get(), &depthStencilViewDesc, depthStencilView.GetAddressOf());

	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
}