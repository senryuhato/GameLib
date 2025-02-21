#pragma once
#include <Windows.h>
#include <string>
#include <map>
#include <memory>
#include "Scene.h"

/// <summary>
/// �V�[���Ǘ��N���X
/// </summary>
class SceneManager
{
public:
	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize() {}

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();

	/// <summary>
	/// �V�[���ύX
	/// </summary>
	/// <param name="loadSceneName">�ύX�V�[����</param>
	void LoadScene(std::string loadSceneName);

	/// <summary>
	/// �V�[���o�^
	/// </summary>
	/// <typeparam name="T">�o�^����V�[���̌^</typeparam>
	/// <param name="registerSceneName">�o�^����V�[����</param>
	template<typename T>
	void RegisterScene(std::string registerSceneName)
	{
		// �N���X����Key�Ƃ��ď㏑���o�^����
		scenes[registerSceneName] = std::make_unique<T>();
	}

	/// <summary>
	/// �V�[���o�^�i���ɓo�^����Ă���ꍇ�͓o�^���Ȃ��j
	/// </summary>
	/// <typeparam name="T">�o�^����V�[���̌^</typeparam>
	/// <param name="registerSceneName">�o�^����V�[����</param>
	/// <returns>����</returns>
	template<typename T>
	bool RegisterSceneIfNotExists(std::string registerSceneName)
	{
		// ���łɓo�^����Ă���ꍇ�o�^����Ȃ�
		if (scenes.find(registerSceneName) != scenes.end()) return false;
		// �V�K�o�^
		RegisterScene<T>(registerSceneName);
		return true;
	}

	/// <summary>
    /// �}�E�X�J�[�\���̕\����\���̐ݒ�
    /// </summary>
    /// <param name="isShow">true:�\��,false:��\��</param>
	void SetShowMouseCursor(bool isShow);

protected:
	// ���݂̃V�[���̃L�[
	std::string currentSceneKey;
    // ���̃V�[���̃L�[(�V�[���̕ύX���ȊO��Empty)
	std::string nextSceneKey;
	std::map<std::string, std::unique_ptr<Scene>> scenes;
	// �N���A�J���[
	FLOAT refreshColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	// �萔
	const UINT SYNC_INTERVAL_VALID = 1;
	const UINT SYNC_INTERVAL_INVALID = 0;
};
