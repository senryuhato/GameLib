#pragma once
#include <string>

#pragma region 設定
namespace Config
{
	// ウィンドウ名
	static const wchar_t* WINDOW_TITLE = L"ゲームプロジェクト";
	// 画面幅
	static const int SCREEN_WIDTH = 1280;
	// 画面高さ
	static const int SCREEN_HEIGHT = 720;
	// デフォルトフレームレート
	static const int FRAMERATE = 60;
}
#pragma endregion

#pragma region シーン名
namespace SceneNames
{
    static const std::string FIRST_SCENE = "TitleScene";
	static const std::string TITLE_SCENE = "TitleScene";
	static const std::string MAIN_SCENE = "MainScene";
}
#pragma endregion
