#pragma once
#include <Windows.h>

/// <summary>
/// �Q�[���̊�Ղ�񋟂���t���[�����[�N�N���X
/// </summary>
class Framework
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Framework();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Framework() = default;

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() {}

	/// <summary>
	/// �I������
	/// </summary>
	void Uninitialize() {}

	/// <summary>
	/// �Q�[�����[�v
	/// </summary>
	void Run();

	/// <summary>
	/// �E�B���h�E���b�Z�[�W���������郁���o�֐��i�N���X���̃��b�Z�[�W�����j
	/// </summary>
	/// <param name="hwnd">�E�B���h�E�n���h��</param>
	/// <param name="msg">�󂯎�������b�Z�[�W</param>
	/// <param name="wParam">���b�Z�[�W�̒ǉ����i1�ڂ̃p�����[�^�j</param>
	/// <param name="lParam">���b�Z�[�W�̒ǉ����i2�ڂ̃p�����[�^�j</param>
	/// <returns>���b�Z�[�W�������������ʁi�ʏ�� `DefWindowProc` �̖߂�l��Ԃ��j</returns>
	LRESULT CALLBACK HandleMessage(
		_In_ HWND hwnd,
		_In_ UINT msg,
		_In_ WPARAM wparam,
		_In_ LPARAM lParam);
};
