#pragma once
#include <Windows.h>
#include <string>

/// <summary>
/// ワールド座標設定
/// </summary>
void CreateWorldTransform();

/// <summary>
/// カメラ作成
/// </summary>
void CreateCamera();

/// <summary>
/// ステートの作成
/// </summary>
void CreateState();

/// <summary>
/// デフォルト設定でウィンドウを作成します。
/// 指定されたウィンドウクラスを使用し、標準的な設定のウィンドウを作成します。
/// クライアント領域のサイズを指定し、それに合うウィンドウサイズを自動調整します。
/// </summary>
/// <param name="instance">アプリケーションのインスタンスハンドル</param>
/// <param name="className">ウィンドウクラスの名前</param>
/// <param name="screenWidth">クライアント領域の幅（ピクセル）</param>
/// <param name="screenHeight">クライアント領域の高さ（ピクセル）</param>
/// <param name="windowTitle">ウィンドウのタイトル</param>
/// <param name="windowStyle">ィンドウのスタイル（デフォルトは WS_OVERLAPPEDWINDOW から WS_THICKFRAME を除外）</param>
/// <returns>作成されたウィンドウのハンドル（失敗時は nullptr）</returns>
HWND CreateDefaultWindow(
	_In_ HINSTANCE instance,
	_In_ LPCWSTR className,
	_In_ LONG screenWidth,
	_In_ LONG screenHeight,
	_In_ LPCWSTR windowTitle,
	_In_ DWORD windowStyle = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_VISIBLE);

/// <summary>
/// ブレンドステートの作成
/// </summary>
void CreateBlendState();

/// <summary>
/// シーン登録
/// </summary>
/// <typeparam name="T">登録するシーンの型</typeparam>
/// <param name="registerSceneName">登録するシーン名</param>
template<typename T>
void RegisterScene(std::string registerSceneName);

/// <summary>
/// シーン登録（既に登録されている場合は登録しない）
/// </summary>
/// <typeparam name="T">登録するシーンの型</typeparam>
/// <param name="registerSceneName">登録するシーン名</param>
/// <returns>結果</returns>
template<typename T>
bool RegisterSceneIfNotExists(std::string registerSceneName);

/// <summary>
/// シーン変更
/// </summary>
/// <param name="loadSceneName">変更シーン名</param>
void LoadScene(std::string loadSceneName);

/// <summary>
/// マウスカーソルの表示非表示の設定
/// </summary>
/// <param name="isShow">true:表示,false:非表示</param>
void SetShowMouseCursor(bool isShow);

/// <summary>
/// ウィンドウメッセージを処理するコールバック関数（Win32 API 用）
/// </summary>
/// <param name="hwnd">ウィンドウハンドル</param>
/// <param name="msg">受け取ったメッセージ</param>
/// <param name="wParam">メッセージの追加情報（1つ目のパラメータ）</param>
/// <param name="lParam">メッセージの追加情報（2つ目のパラメータ）</param>
/// <returns>メッセージを処理した結果（通常は `DefWindowProc` の戻り値を返す）</returns>
static LRESULT CALLBACK WindowProcedure(
	_In_ HWND hwnd,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam);

/// <summary>
/// デフォルト設定でウィンドウクラスを登録します。
/// 指定されたウィンドウプロシージャを持つ、標準的な設定のウィンドウクラスを登録します。
/// 背景色、カーソル、スタイルなどのパラメータは固定されています。
/// </summary>
/// <param name="instance">アプリケーションのインスタンスハンドル</param>
/// <param name="applicationName">登録するウィンドウクラスの名前</param>
/// <param name="windowProcedure">ウィンドウプロシージャ（メッセージ処理関数）</param>
/// <returns>true:成功 false:失敗</returns>
bool RegisterDefaultWindowClass(
	_In_ HINSTANCE instance,
	_In_ LPCWSTR applicationName,
	_In_ WNDPROC windowProcedure);

/// <summary>
/// ウィンドウメッセージをディスパッチ。
/// falseが返ってきたら、ゲーム終了。
/// </summary>
/// <returns></returns>
bool DispatchWindowMessage();

/// <summary>
/// FPS計算
/// </summary>
/// <param name="timeStamp">経過した合計時間</param>
void CalculateFrameStats(float timeStamp);
