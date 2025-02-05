#pragma once
/// <summary>
/// ゲームクラス
/// </summary>
class GameXLib
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameXLib();

private:
	/// <summary>
	/// 指定されたウィンドウプロシージャを持つウィンドウクラスを登録します。
	/// </summary>
	/// <param name="instance">現在のアプリケーションのインスタンスハンドル。</param>
	/// <param name="applicationName">ウィンドウクラスの名前（LPCWSTR 型）。</param>
	/// <param name="windowProcedure">ウィンドウプロシージャの関数ポインタ。</param>
	/// <returns>ウィンドウクラスの登録が成功した場合は true、それ以外の場合は false。</returns>
	bool RegisterWindowClassProcedure(_In_ HINSTANCE Instance, _In_ LPCWSTR applicationName, _In_ WNDPROC windowProcedure);
};