#pragma once
#include <Windows.h>
#include <string>
#include <map>
#include <memory>
#include "Scene.h"

/// <summary>
/// シーン管理クラス
/// </summary>
class SceneManager
{
public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize() {}

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Render();

	/// <summary>
	/// シーン変更
	/// </summary>
	/// <param name="loadSceneName">変更シーン名</param>
	void LoadScene(std::string loadSceneName);

	/// <summary>
	/// シーン登録
	/// </summary>
	/// <typeparam name="T">登録するシーンの型</typeparam>
	/// <param name="registerSceneName">登録するシーン名</param>
	template<typename T>
	void RegisterScene(std::string registerSceneName)
	{
		// クラス名をKeyとして上書き登録する
		scenes[registerSceneName] = std::make_unique<T>();
	}

	/// <summary>
	/// シーン登録（既に登録されている場合は登録しない）
	/// </summary>
	/// <typeparam name="T">登録するシーンの型</typeparam>
	/// <param name="registerSceneName">登録するシーン名</param>
	/// <returns>結果</returns>
	template<typename T>
	bool RegisterSceneIfNotExists(std::string registerSceneName)
	{
		// すでに登録されている場合登録されない
		if (scenes.find(registerSceneName) != scenes.end()) return false;
		// 新規登録
		RegisterScene<T>(registerSceneName);
		return true;
	}

	/// <summary>
    /// マウスカーソルの表示非表示の設定
    /// </summary>
    /// <param name="isShow">true:表示,false:非表示</param>
	void SetShowMouseCursor(bool isShow);

protected:
	// 現在のシーンのキー
	std::string currentSceneKey;
    // 次のシーンのキー(シーンの変更時以外はEmpty)
	std::string nextSceneKey;
	std::map<std::string, std::unique_ptr<Scene>> scenes;
	// クリアカラー
	FLOAT refreshColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	// 定数
	const UINT SYNC_INTERVAL_VALID = 1;
	const UINT SYNC_INTERVAL_INVALID = 0;
};
