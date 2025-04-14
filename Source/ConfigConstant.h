#pragma once
#include <string>

#pragma region �ݒ�
namespace Config
{
	// �E�B���h�E��
	static const wchar_t* WINDOW_TITLE = L"�Q�[���v���W�F�N�g";
	// ��ʕ�
	static const int SCREEN_WIDTH = 1280;
	// ��ʍ���
	static const int SCREEN_HEIGHT = 720;
	// �f�t�H���g�t���[�����[�g
	static const int FRAMERATE = 60;
}
#pragma endregion

#pragma region �V�[����
namespace SceneNames
{
    static const std::string FIRST_SCENE = "TitleScene";
	static const std::string TITLE_SCENE = "TitleScene";
	static const std::string MAIN_SCENE = "MainScene";
}
#pragma endregion
