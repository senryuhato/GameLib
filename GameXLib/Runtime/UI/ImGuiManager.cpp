#include "imGuiDX11.h"
#include "ImGuiManager.h"

#pragma region ImGui の初期化処理
/// <summary>
/// ImGui の初期化処理
/// </summary>
/// <param name="hwnd">ウィンドウハンドル</param>
/// <param name="device">DirectX 11 デバイス</param>
/// <param name="immediateContext">DirectX 11 デバイスコンテキスト</param>
/// <return>結果</return>
bool ImGuiManager::Initialize(
	HWND hwnd, 
	ID3D11Device* device, 
	ID3D11DeviceContext* immediateContext)
{
	if (initialized) Uninitialize();
	initialized = true;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	//io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Consola.ttf", 14.0f, nullptr, io.Fonts->GetGlyphRangesJapanese()); // Font設定
	io.Fonts->AddFontFromFileTTF("Resources\\System\\Fonts\\ipag.ttf", 12.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());// Font設定

#if 1 // ドッキング																												 
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
#endif
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	bool isResult = ImGui_ImplWin32_Init(hwnd);
	if (isResult)
	{
		isResult = ImGui_ImplDX11_Init(device, immediateContext);
	}
	if (!isResult)
	{
		return false;
	}
	ImGui::StyleColorsDark();
	return true;
}
#pragma endregion

#pragma region ImGui の終了処理
/// <summary>
/// ImGui の終了処理
/// </summary>
void ImGuiManager::Uninitialize()
{
	if (!initialized) return;
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	initialized = false;
}
#pragma endregion

#pragma region Imguiの全般処理
/// <summary>
/// Imguiの全般処理
/// </summary>
void ImGuiManager::RenderImGuiFrame()
{
	if (!initialized) return;
	// 描画準備
	NewFrame();
	// ImGui表示処理
	for(auto& func : drawFunctions)
	{
		// 関数ポインタ実行
		func();
	}
	// 描画処理
	Render();
	// クリア処理
	drawFunctions.clear();
}
#pragma endregion

#pragma region ImGuiのウィンドウメッセージを処理するメンバ関数
/// <summary>
/// ImGuiのウィンドウメッセージを処理するメンバ関数
/// </summary>
/// <param name="hwnd">ウィンドウハンドル</param>
/// <param name="msg">受け取ったメッセージ</param>
/// <param name="wParam">メッセージの追加情報（1つ目のパラメータ）</param>
/// <param name="lParam">メッセージの追加情報（2つ目のパラメータ）</param>
/// <returns>メッセージを処理した結果（通常は `DefWindowProc` の戻り値を返す）</returns>
LRESULT ImGuiManager::WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (!initialized) return 0;
	return ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
}
#pragma endregion

#pragma region 新しいフレームの開始
/// <summary>
/// 新しいフレームの開始
/// </summary>
void ImGuiManager::NewFrame()
{
	// 現在の状況だとウィンドウサイズを変更したとき位置がずれる
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}
#pragma endregion

#pragma region ImGui の描画処理
/// <summary>
/// ImGui の描画処理
/// </summary>
void ImGuiManager::Render()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}
#pragma endregion