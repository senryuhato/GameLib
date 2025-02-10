#include "..\GameXLib\System\Classes\GameXLib.h"

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
	GameXLib& gameXLib = GameXLib::GetInstance();
	if (gameXLib.Initialize(hInstance, nShowCmd, 1280, 720, L"�Q�[���v���W�F�N�g"))
	{
		return -1;
	}
	gameXLib.Run();
	gameXLib.Uninitialize(hInstance);
	// ����I��
	return 0;
}
#pragma endregion
