#pragma once
#include <Windows.h>

/// <summary>
/// �Q�[���S�̂��Ǘ����郉�C�u�����N���X�B
/// �Q�[���̃G���g���[�|�C���g�Ƃ��ċ@�\
/// </summary>
class GameXLib
{
public:
	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns></returns>
	static GameXLib& GetInstance()
	{
		static GameXLib instance;
		return instance;
	}

	/// <summary>
	/// ���s����
	/// </summary>
	/// <param name="instance">�A�v���P�[�V�����̃C���X�^���X�n���h��</param>
	/// <param name="nShowCmd">�E�B���h�E�̕\�����</param>
	/// <param name="screenWidth">�N���C�A���g�̈�̕��i�s�N�Z���j</param>
	/// <param name="screenHeight">�N���C�A���g�̈�̍����i�s�N�Z���j</param>
	/// <param name="windowTitle">�E�B���h�E�̃^�C�g��</param>
	/// <returns>����</returns>
	bool Execute(
		_In_ HINSTANCE instance,
		_In_ int nShowCmd,
		_In_ LONG screenWidth,
		_In_ LONG screenHeight,
		_In_ LPCWSTR windowTitle
	);

	/// <summary>
	/// �t���[�����[�N�̏������i�E�B���h�E�� DirectX �̃Z�b�g�A�b�v�j
	/// </summary>
	/// <param name="instance">�A�v���P�[�V�����̃C���X�^���X�n���h��</param>
	/// <param name="nShowCmd">�E�B���h�E�̕\�����</param>
	/// <param name="screenWidth">�N���C�A���g�̈�̕��i�s�N�Z���j</param>
	/// <param name="screenHeight">�N���C�A���g�̈�̍����i�s�N�Z���j</param>
	/// <param name="windowTitle">�E�B���h�E�̃^�C�g��</param>
	/// <returns>����</returns>
	bool Initialize(
		_In_ HINSTANCE instance,
		_In_ int nShowCmd,
		_In_ LONG screenWidth,
		_In_ LONG screenHeight,
		_In_ LPCWSTR windowTitle
	);

	/// <summary>
	/// �t���[�����[�N�̏I������
	/// </summary>
	/// <param name="instance">�A�v���P�[�V�����̃C���X�^���X�n���h��</param>
	void Uninitialize(
		_In_ HINSTANCE instance);

	/// <summary>
	/// �Q�[�����[�v
	/// </summary>
	/// <returns></returns>
	int Run();

private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameXLib();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameXLib() = default;

	/// <summary>
	/// �}�l�[�W���[�̓o�^
	/// </summary>
	void RegisterServices();

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
private:
	HWND hwnd = nullptr; // �E�B���h�E�n���h��
	bool isShowFrameRate = true; // �t���[�����[�g��\�������邩
	const LPCWSTR CLASS_NAME = L"GameProject"; // window��
	const UINT DEFAULT_FRAMERATE = 60; // ���t���b�V�����[�g
	const BOOL FULSCREEN_NO = false;
};