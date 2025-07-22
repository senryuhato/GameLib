#include "SceneManager.h"

void SceneManager::Initialize()
{
	// シーン登録
	/*RegisterSceneIfNotExists<TitleScene>(TITLE_SCENE);
	RegisterSceneIfNotExists<MainScene>(MAIN_SCENE);*/
	// 最初のシーン設定
	LoadScene(TITLE_SCENE);
}

void SceneManager::Update()
{
	// シーンが設定されているか
	if(!currentSceneKey.empty())
	{
		// 次のシーンが指定されている場合
		if(!nextSceneKey.empty())
		{
			// シーン切り替え
			scenes[currentSceneKey]->Uninitializr();
			currentSceneKey = nextSceneKey;
			scenes[nextSceneKey]->Initialize();
		}
		// シーン更新
		scenes[currentSceneKey]->Update();
	}
}

template<typename T>
void SceneManager::RegisterScene(std::string registerSceneName)
{
	// クラス名をKeyとして上書き登録する
	scenes[registerSceneName] = std::make_unique<T>();
}

template<typename T>
bool SceneManager::RegisterSceneIfNotExists(std::string registerSceneName)
{
	// すでに登録されている場合登録されない
	if(scenes.find(registerSceneName) != scenes.end()) return false;
	// 新規登録
	RegisterScene<T>(registerSceneName);
	return true;
}

void SceneManager::LoadScene(std::string loadSceneName)
{
	if(scenes.find(loadSceneName) != scenes.end())
	{
		// シーンが設定されていない場合、最初の読み込みシーンを設定する
		if(currentSceneKey.empty()) currentSceneKey = loadSceneName;
		nextSceneKey = loadSceneName;
	}
}