#pragma once
#include <Windows.h>
#include <string>

/// <summary>
/// ���[���h���W�ݒ�
/// </summary>
void CreateWorldTransform();

/// <summary>
/// �J�����쐬
/// </summary>
void CreateCamera();

/// <summary>
/// �X�e�[�g�̍쐬
/// </summary>
void CreateState();

/// <summary>
/// �f�t�H���g�ݒ�ŃE�B���h�E���쐬���܂��B
/// �w�肳�ꂽ�E�B���h�E�N���X���g�p���A�W���I�Ȑݒ�̃E�B���h�E���쐬���܂��B
/// �N���C�A���g�̈�̃T�C�Y���w�肵�A����ɍ����E�B���h�E�T�C�Y�������������܂��B
/// </summary>
/// <param name="instance">�A�v���P�[�V�����̃C���X�^���X�n���h��</param>
/// <param name="className">�E�B���h�E�N���X�̖��O</param>
/// <param name="screenWidth">�N���C�A���g�̈�̕��i�s�N�Z���j</param>
/// <param name="screenHeight">�N���C�A���g�̈�̍����i�s�N�Z���j</param>
/// <param name="windowTitle">�E�B���h�E�̃^�C�g��</param>
/// <param name="windowStyle">�B���h�E�̃X�^�C���i�f�t�H���g�� WS_OVERLAPPEDWINDOW ���� WS_THICKFRAME �����O�j</param>
/// <returns>�쐬���ꂽ�E�B���h�E�̃n���h���i���s���� nullptr�j</returns>
HWND CreateDefaultWindow(
	_In_ HINSTANCE instance,
	_In_ LPCWSTR className,
	_In_ LONG screenWidth,
	_In_ LONG screenHeight,
	_In_ LPCWSTR windowTitle,
	_In_ DWORD windowStyle = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_VISIBLE);

/// <summary>
/// �u�����h�X�e�[�g�̍쐬
/// </summary>
void CreateBlendState();

/// <summary>
/// �V�[���o�^
/// </summary>
/// <typeparam name="T">�o�^����V�[���̌^</typeparam>
/// <param name="registerSceneName">�o�^����V�[����</param>
template<typename T>
void RegisterScene(std::string registerSceneName);

/// <summary>
/// �V�[���o�^�i���ɓo�^����Ă���ꍇ�͓o�^���Ȃ��j
/// </summary>
/// <typeparam name="T">�o�^����V�[���̌^</typeparam>
/// <param name="registerSceneName">�o�^����V�[����</param>
/// <returns>����</returns>
template<typename T>
bool RegisterSceneIfNotExists(std::string registerSceneName);

/// <summary>
/// �V�[���ύX
/// </summary>
/// <param name="loadSceneName">�ύX�V�[����</param>
void LoadScene(std::string loadSceneName);

/// <summary>
/// �}�E�X�J�[�\���̕\����\���̐ݒ�
/// </summary>
/// <param name="isShow">true:�\��,false:��\��</param>
void SetShowMouseCursor(bool isShow);

/// <summary>
/// �E�B���h�E���b�Z�[�W����������R�[���o�b�N�֐��iWin32 API �p�j
/// </summary>
/// <param name="hwnd">�E�B���h�E�n���h��</param>
/// <param name="msg">�󂯎�������b�Z�[�W</param>
/// <param name="wParam">���b�Z�[�W�̒ǉ����i1�ڂ̃p�����[�^�j</param>
/// <param name="lParam">���b�Z�[�W�̒ǉ����i2�ڂ̃p�����[�^�j</param>
/// <returns>���b�Z�[�W�������������ʁi�ʏ�� `DefWindowProc` �̖߂�l��Ԃ��j</returns>
static LRESULT CALLBACK WindowProcedure(
	_In_ HWND hwnd,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam);

/// <summary>
/// �f�t�H���g�ݒ�ŃE�B���h�E�N���X��o�^���܂��B
/// �w�肳�ꂽ�E�B���h�E�v���V�[�W�������A�W���I�Ȑݒ�̃E�B���h�E�N���X��o�^���܂��B
/// �w�i�F�A�J�[�\���A�X�^�C���Ȃǂ̃p�����[�^�͌Œ肳��Ă��܂��B
/// </summary>
/// <param name="instance">�A�v���P�[�V�����̃C���X�^���X�n���h��</param>
/// <param name="applicationName">�o�^����E�B���h�E�N���X�̖��O</param>
/// <param name="windowProcedure">�E�B���h�E�v���V�[�W���i���b�Z�[�W�����֐��j</param>
/// <returns>true:���� false:���s</returns>
bool RegisterDefaultWindowClass(
	_In_ HINSTANCE instance,
	_In_ LPCWSTR applicationName,
	_In_ WNDPROC windowProcedure);

/// <summary>
/// �E�B���h�E���b�Z�[�W���f�B�X�p�b�`�B
/// false���Ԃ��Ă�����A�Q�[���I���B
/// </summary>
/// <returns></returns>
bool DispatchWindowMessage();

/// <summary>
/// FPS�v�Z
/// </summary>
/// <param name="timeStamp">�o�߂������v����</param>
void CalculateFrameStats(float timeStamp);
