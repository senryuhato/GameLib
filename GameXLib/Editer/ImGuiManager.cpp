#include "..\ThirdParty\ImGui\imgui-docking\imgui.h"
#include "..\ThirdParty\ImGui\imgui-docking\imgui_impl_dx11.h"
#include "..\ThirdParty\ImGui\imgui-docking\imgui_impl_win32.h"
#include "ImGuiManager.h"

bool ImGuiManager::Initialize(
	HWND hwnd,
	ID3D11Device* device,
	ID3D11DeviceContext* immediateContext)
{
	if(initialized) Uninitialize();
	initialized = true;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	//io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Consola.ttf", 14.0f, nullptr, io.Fonts->GetGlyphRangesJapanese()); // Font設定
	io.Fonts->AddFontFromFileTTF("Resources\\System\\Fonts\\ipag.ttf",12.0f,nullptr,io.Fonts->GetGlyphRangesJapanese());// Font設定

	#if 1 // ドッキング																												 
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	#endif
	ImGuiStyle& style = ImGui::GetStyle();
	if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	bool isResult = ImGui_ImplWin32_Init(hwnd);
	if(isResult)
	{
		isResult = ImGui_ImplDX11_Init(device,immediateContext);
	}
	if(!isResult)
	{
		return false;
	}
	ImGui::StyleColorsDark();
	return true;
}

void ImGuiManager::Uninitialize()
{
	if(!initialized) return;
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	initialized = false;
}

void ImGuiManager::RenderImGuiFrame()
{
	if(!initialized) return;
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

LRESULT ImGuiManager::WndProcHandler(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(!initialized) return 0;
	return ImGui_ImplWin32_WndProcHandler(hwnd,msg,wParam,lParam);
}

void ImGuiManager::NewFrame()
{
	// 現在の状況だとウィンドウサイズを変更したとき位置がずれる
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::Render()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}