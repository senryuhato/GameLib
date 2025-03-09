#include "../GameXLib/Runtime/System/GameXLib.h"
#include "../GameXLib/Runtime/System/ServiceLocator.h"
#include "../GameXLib/Runtime/UI/ImGuiManager.h"
#include "../GameXLib/Runtime/Scene/SceneManager.h"
#include "../Source/TitleScene.h"
#include "../Source/MainScene.h"
#include "ConfigConstant.h"

#pragma region C++/CLI Windows �A�v���P�[�V�����̃G���g���|�C���g
/// <summary>
/// C++/CLI �ł� Windows �A�v���P�[�V�����̃G���g���|�C���g�B
/// </summary>
/// <param name="hInstance">���݂̃C���X�^���X�n���h��</param>
/// <param name="hPrevInstance">�ȑO�̃C���X�^���X�n���h���i��� NULL�j</param>
/// <param name="lpCmdLine">�R�}���h���C������</param>
/// <param name="nShowCmd">�E�B���h�E�̕\�����</param>
/// <returns>�v���O�����̏I���R�[�h�i�ʏ�� 0�j</returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
#if 1 // ImGui���s�v�̏ꍇ�A�폜���邱�Ƃŕ\������Ȃ��Ȃ�
	// ImGui�̓o�^
	ServiceLocator::RegisterService<ImGuiManager>(ServiceNames::BASE_IMGUI_MANAGER);
#endif
	// �V�[���̓o�^
	ServiceLocator::RegisterService<SceneManager>(ServiceNames::SCENE_MANAGER);
	std::shared_ptr<SceneManager> sceneManager = ServiceLocator::GetService<SceneManager>(ServiceNames::SCENE_MANAGER);
	// �V�[���o�^
	sceneManager->RegisterSceneIfNotExists<TitleScene>(SceneNames::TITLE);
	sceneManager->RegisterSceneIfNotExists<MainScene>(SceneNames::MAIN);
	// �ŏ��̃V�[���ݒ�
	sceneManager->LoadScene(SceneNames::FIRST_SCENE);

#if 1 // �ʐݒ�
	// �J�[�\���ݒ�
	sceneManager->SetShowMouseCursor(true);
#endif
	
	// �Q�[�����s
	GameXLib& gameXLib = GameXLib::GetInstance();
	gameXLib.Execute(hInstance, nShowCmd,
		Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, 
		Config::WINDOW_TITLE, Config::FRAMERATE);
	// ����I��
	return 0;
}
#pragma endregion
