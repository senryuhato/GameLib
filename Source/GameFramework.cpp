#include "GameFramework.h"
#include "../GameXLib/Graphics/Classes/GraphicsManager.h"
#include "../GameXLib/System/Classes/SystemServiceLocator.h"
#include "TimeManager.h"
#include "GameServiceLocator.h"

#pragma region 初期化処理
/// <summary>
/// 初期化処理
/// </summary>
void GameFramework::Initialize()
{
	// タイマー
	GameServiceLocator::RegisterServiceIfNotExists(std::make_shared<TimeManager>());
}
#pragma endregion

#pragma region ゲームループ
/// <summary>
/// ゲームループ
/// </summary>
void GameFramework::Run()
{
	std::shared_ptr<TimeManager> timeManager = GameServiceLocator::GetService<TimeManager>();
	// タイマー更新
	timeManager->Update();
	Update();
	Render();
}
#pragma endregion

#pragma region 更新処理
/// <summary>
/// 更新処理
/// </summary>
void GameFramework::Update()
{

}
#pragma endregion

#pragma region 描画処理
/// <summary>
/// 描画処理
/// </summary>
void GameFramework::Render()
{
	std::shared_ptr<GraphicsManager> graphicsManager = SystemServiceLocator::GetService<GraphicsManager>();
	ID3D11DeviceContext* immediateContext = graphicsManager->GetDeviceContext();
	ID3D11RenderTargetView* renderTargetView = graphicsManager->GetRenderTargetView();
	ID3D11DepthStencilView* depthStencilView = graphicsManager->GetDepthStencilView();
	IDXGISwapChain* swapChain = graphicsManager->GetSwapChain();

	// 画面クリア＆レンダーターゲット設定
	immediateContext->ClearRenderTargetView(renderTargetView, refreshColor);
	immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	immediateContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	// ゲーム処理


	// バックバッファに描画した画を画面に表示する。
	swapChain->Present(SYNC_INTERVAL_VALID, 0);
}
#pragma endregion





