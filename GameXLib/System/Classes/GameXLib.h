#pragma once
/// <summary>
/// �Q�[���N���X
/// </summary>
class GameXLib
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameXLib();

private:
	/// <summary>
	/// �w�肳�ꂽ�E�B���h�E�v���V�[�W�������E�B���h�E�N���X��o�^���܂��B
	/// </summary>
	/// <param name="instance">���݂̃A�v���P�[�V�����̃C���X�^���X�n���h���B</param>
	/// <param name="applicationName">�E�B���h�E�N���X�̖��O�iLPCWSTR �^�j�B</param>
	/// <param name="windowProcedure">�E�B���h�E�v���V�[�W���̊֐��|�C���^�B</param>
	/// <returns>�E�B���h�E�N���X�̓o�^�����������ꍇ�� true�A����ȊO�̏ꍇ�� false�B</returns>
	bool RegisterWindowClassProcedure(_In_ HINSTANCE Instance, _In_ LPCWSTR applicationName, _In_ WNDPROC windowProcedure);
};