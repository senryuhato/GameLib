#pragma once
#include <d3d11.h>
#include <functional>
#include <vector>

// ImGuiのウィンドウメッセージ処理
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

/// @brief ImGui の初期化・更新・描画・終了処理を管理するクラス
class ImGuiManager
{
public:
	/// @brief ImGuiの初期化処理
	/// @param hwnd ウィンドウハンドル
	/// @param device DirectX 11 デバイス
	/// @param immediateContext DirectX 11 デバイスコンテキスト
	/// @return 結果
	bool Initialize(
		HWND hwnd, 
		ID3D11Device* device, 
		ID3D11DeviceContext*
		immediateContext);

	/// @brief ImGuiの終了処理
	void Uninitialize();

	/// @brief Imguiの全般処理
	void RenderImGuiFrame();

	/// @brief 関数ポインターを登録する
	/// @param func 登録する関数
	void RegisterImGuiFunction(std::function<void()> func)
	{
		drawFunctions.push_back(func);
	}

	/// @brief ImGuiのウィンドウメッセージを処理するメンバ関数
	/// @param hwnd ウィンドウハンドル
	/// @param msg 受け取ったメッセージ
	/// @param wParam メッセージの追加情報（1つ目のパラメータ）
	/// @param lParam メッセージの追加情報（2つ目のパラメータ）
	/// @return メッセージを処理した結果（通常は `DefWindowProc` の戻り値を返す）
	LRESULT WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	// 新しいフレームの開始
	void NewFrame();

	// ImGuiの描画処理
	void Render();

private:
	// 初期化フラグ
	bool initialized = false;
	// ImGui表示処理配列
	std::vector<std::function<void()>> drawFunctions;
};