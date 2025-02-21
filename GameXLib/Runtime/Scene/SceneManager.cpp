#include "SceneManager.h"
#include "../Graphics/GraphicsManager.h"
#include "../UI/ImGuiManager.h"
#include "../System/ServiceLocator.h"

#pragma region 更新処理
/// <summary>
/// 更新処理
/// </summary>
void SceneManager::Update()
{
	// シーンが設定されているか
	if (currentSceneKey.empty()) return;
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
#pragma endregion

#pragma region 描画処理
/// <summary>
/// 描画処理
/// </summary>
void SceneManager::Render()
{
	// シーンが設定されているか
	if (currentSceneKey.empty()) return;

	std::shared_ptr<GraphicsManager> graphicsManager = ServiceLocator::GetService<GraphicsManager>();
	ID3D11DeviceContext* immediateContext = graphicsManager->GetDeviceContext();
	ID3D11RenderTargetView* renderTargetView = graphicsManager->GetRenderTargetView();
	ID3D11DepthStencilView* depthStencilView = graphicsManager->GetDepthStencilView();
	IDXGISwapChain* swapChain = graphicsManager->GetSwapChain();

	// 画面クリア＆レンダーターゲット設定
	immediateContext->ClearRenderTargetView(renderTargetView, refreshColor);
	immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	immediateContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	std::shared_ptr<ImGuiManager> imGuiManager = ServiceLocator::GetService<ImGuiManager>();
	// UI表示処理
	imGuiManager->NewFrame();

	// ゲーム処理
	scenes[currentSceneKey]->Render();

	// UI表示
	imGuiManager->Render();
	// バックバッファに描画した画を画面に表示する。
	swapChain->Present(SYNC_INTERVAL_VALID, 0);
}
#pragma endregion

#pragma region シーン変更
/// <summary>
/// シーン変更
/// </summary>
/// <param name="loadSceneName">変更シーン名</param>
void SceneManager::LoadScene(std::string loadSceneName)
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
void SceneManager::SetShowMouseCursor(bool isShow)
{
	// カーソルは、表示カウントが 0 以上の場合にのみ表示
	int count = ShowCursor(isShow);
	while (isShow ? count < 0 : count >= 0)
	{
		count = ShowCursor(isShow);
	}
}
#pragma endregion