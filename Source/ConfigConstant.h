#pragma once
#include <string>

#pragma region 設定
namespace Config
{
	// ウィンドウ名
	const wchar_t* WINDOW_TITLE = L"ゲームプロジェクト";
	// 画面幅
	const int SCREEN_WIDTH = 1280;
	// 画面高さ
	const int SCREEN_HEIGHT = 720;
	// デフォルトフレームレート
	const int FRAMERATE = 60;
}
#pragma endregion

#pragma region シーン名
namespace SceneNames
{
	const std::string FIRST_SCENE = "TitleScene";
	const std::string TITLE = "TitleScene";
	const std::string MAIN = "MainScene";
}
#pragma endregion
