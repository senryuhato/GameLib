#pragma once
#include <string>

#pragma region �ݒ�
namespace Config
{
	// �E�B���h�E��
	const wchar_t* WINDOW_TITLE = L"�Q�[���v���W�F�N�g";
	// ��ʕ�
	const int SCREEN_WIDTH = 1280;
	// ��ʍ���
	const int SCREEN_HEIGHT = 720;
	// �f�t�H���g�t���[�����[�g
	const int FRAMERATE = 60;
}
#pragma endregion

#pragma region �V�[����
namespace SceneNames
{
	const std::string FIRST_SCENE = "TitleScene";
	const std::string TITLE = "TitleScene";
	const std::string MAIN = "MainScene";
}
#pragma endregion
