#pragma once
#include <d3d11.h>

/// <summary>
/// ImGui の初期化・更新・描画・終了処理を管理するクラス
/// </summary>
class ImGuiManager
{
public:
	/// <summary>
	/// ImGui の初期化処理
	/// </summary>
	/// <param name="hwnd">ウィンドウハンドル</param>
	/// <param name="device">DirectX 11 デバイス</param>
	/// <param name="immediateContext">DirectX 11 デバイスコンテキスト</param>
	/// <return>結果</return>
	bool Initialize(
		HWND hwnd, 
		ID3D11Device* device, 
		ID3D11DeviceContext*
		immediateContext);

	/// <summary>
	/// ImGui の終了処理
	/// </summary>
	void Uninitialize();

	/// <summary>
	/// 新しいフレームの開始
	/// </summary>
	void NewFrame();

	/// <summary>
	/// ImGui の描画処理
	/// </summary>
	void Render();

	/// <summary>
	/// ImGuiのウィンドウメッセージを処理するメンバ関数
	/// </summary>
	/// <param name="hwnd">ウィンドウハンドル</param>
	/// <param name="msg">受け取ったメッセージ</param>
	/// <param name="wParam">メッセージの追加情報（1つ目のパラメータ）</param>
	/// <param name="lParam">メッセージの追加情報（2つ目のパラメータ）</param>
	/// <returns>メッセージを処理した結果（通常は `DefWindowProc` の戻り値を返す）</returns>
	LRESULT WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	// 初期化フラグ
	bool initialized = false;
};
