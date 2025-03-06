#pragma once
#include <d3d11.h>
#include <vector>
#include <functional>

/// <summary>
/// ImGui の初期化・更新・描画・終了処理を管理する基本クラス
/// </summary>
class BaseImGuiManager
{
public:
	/// <summary>
	/// ImGuiの初期化処理
	/// </summary>
	/// <param name="hwnd">ウィンドウハンドル</param>
	/// <param name="device">DirectX 11 デバイス</param>
	/// <param name="immediateContext">DirectX 11 デバイスコンテキスト</param>
	/// <return>結果</return>
	virtual bool Initialize(
		HWND hwnd,
		ID3D11Device* device,
		ID3D11DeviceContext*
		immediateContext)
	{
		return true;
	}

	/// <summary>
	/// ImGuiの終了処理
	/// </summary>
	virtual void Uninitialize() {}

	/// <summary>
	/// Imguiの全般処理
	/// </summary>
	virtual void RenderImGuiFrame() {}

	/// <summary>
	/// 関数ポインターを登録する
	/// </summary>
	/// <param name="func">登録する関数</param>
	virtual void RegisterImGuiFunction(std::function<void()> func) {}

	/// <summary>
	/// ImGuiのウィンドウメッセージを処理するメンバ関数
	/// </summary>
	/// <param name="hwnd">ウィンドウハンドル</param>
	/// <param name="msg">受け取ったメッセージ</param>
	/// <param name="wParam">メッセージの追加情報（1つ目のパラメータ）</param>
	/// <param name="lParam">メッセージの追加情報（2つ目のパラメータ）</param>
	/// <returns>メッセージを処理した結果（通常は `DefWindowProc` の戻り値を返す）</returns>
	virtual LRESULT WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{ 
		return 0; 
	}
};

/// <summary>
/// ImGui の初期化・更新・描画・終了処理を管理するクラス
/// </summary>
class ImGuiManager : public BaseImGuiManager
{
public:
	/// <summary>
	/// ImGuiの初期化処理
	/// </summary>
	/// <param name="hwnd">ウィンドウハンドル</param>
	/// <param name="device">DirectX 11 デバイス</param>
	/// <param name="immediateContext">DirectX 11 デバイスコンテキスト</param>
	/// <return>結果</return>
	bool Initialize(
		HWND hwnd, 
		ID3D11Device* device, 
		ID3D11DeviceContext*
		immediateContext) override;

	/// <summary>
	/// ImGuiの終了処理
	/// </summary>
	void Uninitialize() override;

	/// <summary>
	/// Imguiの全般処理
	/// </summary>
	void RenderImGuiFrame() override;

	/// <summary>
	/// 関数ポインターを登録する
	/// </summary>
	/// <param name="func">登録する関数</param>
	void RegisterImGuiFunction(std::function<void()> func) override
	{
		drawFunctions.push_back(func);
	}

	/// <summary>
	/// ImGuiのウィンドウメッセージを処理するメンバ関数
	/// </summary>
	/// <param name="hwnd">ウィンドウハンドル</param>
	/// <param name="msg">受け取ったメッセージ</param>
	/// <param name="wParam">メッセージの追加情報（1つ目のパラメータ）</param>
	/// <param name="lParam">メッセージの追加情報（2つ目のパラメータ）</param>
	/// <returns>メッセージを処理した結果（通常は `DefWindowProc` の戻り値を返す）</returns>
	LRESULT WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

private:
	// 初期化フラグ
	bool initialized = false;
	// ImGui表示処理配列
	std::vector<std::function<void()>> drawFunctions;

private:
	/// <summary>
	/// 新しいフレームの開始
	/// </summary>
	void NewFrame();

	/// <summary>
	/// ImGuiの描画処理
	/// </summary>
	void Render();
};