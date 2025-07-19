#pragma once
#include <d3d11.h>
#include <wrl.h>

// DirectX 11 を用いたグラフィックス管理クラス
class GraphicsManager
{
public:
	/// @brief 処理なし
	GraphicsManager() = default;

	/// @brief リソース解放
	~GraphicsManager()
	{
		Uninitialize();
	}

	/// @brief DirectX の初期化
	/// @param hwnd ウィンドウハンドル
	/// @param defaultFramerate 目標フレームレート(デフォルト: 60)
	/// @param isFullscreen フルスクリーンの設定。true:フルスクリーン、false:通常
	/// @return 結果
	bool Initialize(
		HWND hwnd,
		UINT defaultFramerate = 60,
		BOOL isFullscreen = false);

	/// @brief DirectX のリソースを解放
	void Uninitialize();

public:
	/// @brief Direct3D デバイスを取得
	/// @return ID3D11Device のポインタ
	ID3D11Device* GetDevice() const {
		return device.Get();
	}

	/// @brief デバイスコンテキストを取得
	/// @return ID3D11DeviceContextのポインタ
	ID3D11DeviceContext* GetDeviceContext() const {
		return immediateContext.Get();
	}

	/// @brief スワップチェインを取得
	/// @return IDXGISwapChainのポインタ
	IDXGISwapChain* GetSwapChain() const {
		return swapChain.Get();
	}

	/// @brief フレームバッファ用レンダーターゲットビューを取得
	/// @return ID3D11RenderTargetViewのポインタ
	ID3D11RenderTargetView* GetRenderTargetView() const {
		return renderTargetView.Get();
	}

	/// @brief フレームバッファ用デプスステンシルビューを取得
	/// @return ID3D11DepthStencilView のポインタ
	ID3D11DepthStencilView* GetDepthStencilView() const {
		return depthStencilView.Get();
	}

private:
	/// @brief デバイス＆スワップチェインの作成
	/// 
	/// @param hwnd ウィンドウハンドル
	/// @param frameBufferWidth フレームバッファの幅
	/// @param frameBufferHeight フレームバッファの高さ
	/// @param defaultFramerate 目標フレームレート
	/// @param isFullscreen フルスクリーンの設定。true:フルスクリーン、false:通常
	void CreateDeviceAndSwapChain(
		HWND hwnd,
		UINT frameBufferWidth,
		UINT frameBufferHeight,
		UINT defaultFramerate,
		BOOL isFullscreen);

	/// @brief レームバッファ用のレンダーターゲットビュー（RTV）を作成
	void CreateRTVForFrameBuffer();

	/// @brief フレームバッファ用の深度ステンシルビュー（DSV）を作成
	/// @param frameBufferWidth フレームバッファの幅
	/// @param frameBufferHeight フレームバッファの高さ
	void CreateDSVForFrameBuffer(
		UINT frameBufferWidth,
		UINT frameBufferHeight);

private:
	// スワップチェイン
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain = nullptr;
	// Direct3D デバイス
	Microsoft::WRL::ComPtr<ID3D11Device> device = nullptr;
	// デバイスコンテキスト
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediateContext = nullptr;
	// フレームバッファ用レンダーターゲットビュー　
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
	// フレームバッファ用デプスステンシルビュー
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView = nullptr;

	//フレームバッファの幅
	UINT frameBufferWidth = 0;
	//フレームバッファの高さ
	UINT frameBufferHeight = 0;
	// 初期フレームレート
	UINT defaultFramerate = 60;
};