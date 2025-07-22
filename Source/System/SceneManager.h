#pragma once
#include "Scene.h"
#include <map>
#include <memory>
#include <string>

class SceneManager
{
public:
	/// @brief シーン管理クラス初期化処理 シーン設定
	void Initialize();

	/// @brief シーン管理クラス更新処理
	void Update();

	/// @brief シーン登録
	/// @tparam T 登録するシーンの型
	/// @param registerSceneName 登録するシーン名
	template<typename T>
	void RegisterScene(std::string registerSceneName);

	/// @brief シーン登録（既に登録されている場合は登録しない）
	/// @tparam T 登録するシーンの型
	/// @param registerSceneName 登録するシーン名
	/// @return 結果
	template<typename T>
	bool RegisterSceneIfNotExists(std::string registerSceneName);

	/// @brief シーン変更
	/// @param loadSceneName 変更シーン名
	void LoadScene(std::string loadSceneName);

public:
	// 現在のシーンのキー
	std::string currentSceneKey;
	// 次のシーンのキー(シーンの変更時以外はEmpty)
	std::string nextSceneKey;
	// シーンリスト
	std::map<std::string,std::unique_ptr<Scene>> scenes;

	// タイトルシーンキー
	const std::string TITLE_SCENE = "TitleScene";
	// メインシーンキー
	const std::string MAIN_SCENE = "MainScene";
};
