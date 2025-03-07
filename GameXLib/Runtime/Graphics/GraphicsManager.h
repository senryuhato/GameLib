#pragma once
#include <wrl.h>
#include <d3d11.h>

/// <summary>
/// DirectX 11 を用いたグラフィックス管理クラス
/// </summary>
class GraphicsManager
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GraphicsManager() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GraphicsManager() { Uninitialize(); }

	/// <summary>
	/// DirectX の初期化
	/// </summary>
	/// <param name="hwnd">ウィンドウハンドル</param>
	/// <param name="defaultFramerate">目標フレームレート（デフォルト: 60）</param>
	/// <param name="isFullscreen">フルスクリーンの設定。（デフォルト: false）true:フルスクリーン、false:通常</param>
	/// <returns>結果</returns>
	bool Initialize(
		HWND hwnd, 
		UINT defaultFramerate = 60,
		BOOL isFullscreen = false);

	/// <summary>
	/// DirectX のリソースを解放
	/// </summary>
	void Uninitialize();

public:
	/// <summary>
	/// Direct3D デバイスを取得
	/// </summary>
	/// <returns>ID3D11Device のポインタ</returns>
	ID3D11Device* GetDevice() const { return device.Get(); }

	/// <summary>
	/// デバイスコンテキストを取得
	/// </summary>
	/// <returns>ID3D11DeviceContext のポインタ</returns>
	ID3D11DeviceContext* GetDeviceContext() const { return immediateContext.Get(); }

	/// <summary>
    /// スワップチェインを取得
    /// </summary>
    /// <returns>IDXGISwapChain のポインタ</returns>
	IDXGISwapChain* GetSwapChain() const { return swapChain.Get(); }

	/// <summary>
	/// フレームバッファ用レンダーターゲットビューを取得
	/// </summary>
	/// <returns>ID3D11RenderTargetView のポインタ</returns>
	ID3D11RenderTargetView* GetRenderTargetView() const { return renderTargetView.Get(); }

	/// <summary>
	/// フレームバッファ用デプスステンシルビューを取得
	/// </summary>
	/// <returns>ID3D11DepthStencilView のポインタ</returns>
	ID3D11DepthStencilView* GetDepthStencilView() const { return depthStencilView.Get(); }

private:
	/// <summary>
	/// デバイス＆スワップチェインの作成
	/// </summary>
	/// <param name="hwnd">ウィンドウハンドル</param>
	/// <param name="frameBufferWidth">フレームバッファの幅</param>
	/// <param name="frameBufferHeight">フレームバッファの高さ</param>
	/// <param name="isFullscreen">フルスクリーンの設定。true:フルスクリーン、false:通常</param>
	void CreateDeviceAndSwapChain(
		HWND hwnd, 
		UINT frameBufferWidth, 
		UINT frameBufferHeight, 
		UINT defaultFramerate,
		BOOL isFullscreen);

	/// <summary>
	/// レームバッファ用のレンダーターゲットビュー（RTV）を作成
	/// </summary>
	void CreateRTVForFrameBuffer();

	/// <summary>
	/// フレームバッファ用の深度ステンシルビュー（DSV）を作成
	/// </summary>
	/// <param name="frameBufferWidth">フレームバッファの幅</param>
	/// <param name="frameBufferHeight">フレームバッファの高さ</param>
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
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  renderTargetView = nullptr;
	// フレームバッファ用デプスステンシルビュー
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  depthStencilView = nullptr;

	//フレームバッファの幅
	UINT frameBufferWidth = 0; 
	//フレームバッファの高さ
	UINT frameBufferHeight = 0;
	// 初期フレームレート
	UINT defaultFramerate = 60;
};