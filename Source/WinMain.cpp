#include "../GameXLib/Runtime/System/GameXLib.h"
#include "../GameXLib/Runtime/System/ServiceLocator.h"
#include "../GameXLib/Runtime/Scene/SceneManager.h"
#include "../Source/TitleScene.h"
#include "../Source/MainScene.h"

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
	// �V�[���̓o�^
	ServiceLocator::RegisterService<SceneManager>(std::make_shared<SceneManager>());
	std::shared_ptr<SceneManager> sceneManager = ServiceLocator::GetService<SceneManager>();
	// �V�[���o�^
	sceneManager->RegisterSceneIfNotExists<TitleScene>("TitleScene");
	sceneManager->RegisterSceneIfNotExists<MainScene>("MainScene");
	// �ŏ��̃V�[���ݒ�
	sceneManager->LoadScene("TitleScene");
	// �J�[�\���ݒ�
	sceneManager->SetShowMouseCursor(true);
	
	// �Q�[�����s
	GameXLib& gameXLib = GameXLib::GetInstance();
	gameXLib.Execute(hInstance, nShowCmd, 1280, 720, L"�Q�[���v���W�F�N�g");
	// ����I��
	return 0;
}
#pragma endregion
