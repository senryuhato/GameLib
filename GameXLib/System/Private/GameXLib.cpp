#include <Windows.h>
#include <crtdbg.h>
#include <time.h>

#include "GameXLib.h"

#pragma region �R���X�g���N�^
/// <summary>
/// GameLib �N���X�̃R���X�g���N�^�B
/// �f�o�b�O���ł̓��������[�N���o��L�������A
/// �����̏��������s���B
/// </summary>
GameXLib::GameXLib()
{
	// �f�o�b�O���[�h���Ƀ��������[�N���o��L�����B
#if defined(DEBUG) | defined(_DEBUG)
	// `_CRTDBG_ALLOC_MEM_DF` : ���������蓖�Ẵf�o�b�O����L�����B
	// `_CRTDBG_LEAK_CHECK_DF` : �v���O�����I�����Ƀ��������[�N���`�F�b�N�B
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(####);���g�p����ƁA�w�肳�ꂽ�A���P�[�V�����ԍ��Ńu���[�N�\�B
#endif

	// �����̃V�[�h�l��ݒ�B
	srand(static_cast<unsigned int>(time(nullptr)));
}
#pragma endregion

#pragma region �w�肳�ꂽ�E�B���h�E�v���V�[�W�������E�B���h�E�N���X��o�^���܂�
/// <summary>
/// �w�肳�ꂽ�E�B���h�E�v���V�[�W�������E�B���h�E�N���X��o�^���܂��B
/// </summary>
/// <param name="instance">���݂̃A�v���P�[�V�����̃C���X�^���X�n���h���B</param>
/// <param name="applicationName">�E�B���h�E�N���X�̖��O�iLPCWSTR �^�j�B</param>
/// <param name="windowProcedure">�E�B���h�E�v���V�[�W���̊֐��|�C���^�B</param>
/// <returns>�E�B���h�E�N���X�̓o�^�����������ꍇ�� true�A����ȊO�̏ꍇ�� false�B</returns>
bool GameXLib::RegisterWindowClassProcedure(_In_ HINSTANCE instance, _In_ LPCWSTR applicationName, _In_ WNDPROC windowProcedure)
{
	// �E�B���h�E�N���X�̃p�����[�^�[��ݒ�
	WNDCLASSEX wcex{};
	// �\���̂̃T�C�Y��ݒ�B
	wcex.cbSize = sizeof(WNDCLASSEX);
	// �E�B���h�E�̃X�^�C���B
	// CS_HREDRAW: �E�B���h�E�̕����ύX���ꂽ�ۂɍĕ`��B
	// CS_VREDRAW: �E�B���h�E�̍������ύX���ꂽ�ۂɍĕ`��B
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	// �E�B���h�E�v���V�[�W���i���b�Z�[�W�����֐��j���w��B
	wcex.lpfnWndProc = windowProcedure;
	// �N���X�������̒ǉ��o�C�g���i�ʏ�� 0�j�B
	wcex.cbClsExtra = 0;
	// �E�B���h�E���Ƃ̒ǉ��������̃o�C�g���i�ʏ�� 0�j�B
	wcex.cbWndExtra = 0;
	// �E�B���h�E�N���X��������A�v���P�[�V�����̃C���X�^���X�n���h���B
	wcex.hInstance = instance;
	// �E�B���h�E�̃A�C�R����ݒ�iNULL �̏ꍇ�̓f�t�H���g�A�C�R���j�B
	wcex.hIcon = NULL;
	// �}�E�X�J�[�\���̃f�t�H���g�ݒ�i�ʏ�͖��J�[�\���j�B
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	// �E�B���h�E�̔w�i�F��ݒ�B
	// (HBRUSH)(COLOR_WINDOW + 1) �ŃV�X�e���̕W���w�i�F���g�p�B
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// ���j���[�̃��\�[�X���iNULL �̏ꍇ�̓��j���[�Ȃ��j�B
	wcex.lpszMenuName = NULL;
	// �E�B���h�E�N���X����ݒ�B
	wcex.lpszClassName = applicationName;
	// �������A�C�R���i�^�X�N�o�[�̃T���l�C���p�j�BNULL �̏ꍇ�̓f�t�H���g�B
	wcex.hIconSm = 0;

	// �E�B���h�E�N���X�̓o�^�B
	if (!RegisterClassExW(&wcex))
	{
		MessageBox(NULL, L"�E�B���h�E�N���X�̓o�^�Ɏ��s���܂����B", L"�G���[", MB_ICONERROR);
		return false; // ���s���� false ��Ԃ�
	}
	return true; // �������� true ��Ԃ�
}
#pragma endregion