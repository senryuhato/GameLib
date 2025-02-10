#pragma once
#include <d3d11.h>

/// <summary>
/// ImGui �̏������E�X�V�E�`��E�I���������Ǘ�����N���X
/// </summary>
class ImGuiManager
{
public:
	/// <summary>
	/// ImGui �̏���������
	/// </summary>
	/// <param name="hwnd">�E�B���h�E�n���h��</param>
	/// <param name="device">DirectX 11 �f�o�C�X</param>
	/// <param name="immediateContext">DirectX 11 �f�o�C�X�R���e�L�X�g</param>
	/// <return>����</return>
	bool Initialize(
		HWND hwnd, 
		ID3D11Device* device, 
		ID3D11DeviceContext*
		immediateContext);

	/// <summary>
	/// ImGui �̏I������
	/// </summary>
	void Uninitialize();

	/// <summary>
	/// �V�����t���[���̊J�n
	/// </summary>
	void NewFrame();

	/// <summary>
	/// ImGui �̕`�揈��
	/// </summary>
	void Render();

	/// <summary>
	/// ImGui�̃E�B���h�E���b�Z�[�W���������郁���o�֐�
	/// </summary>
	/// <param name="hwnd">�E�B���h�E�n���h��</param>
	/// <param name="msg">�󂯎�������b�Z�[�W</param>
	/// <param name="wParam">���b�Z�[�W�̒ǉ����i1�ڂ̃p�����[�^�j</param>
	/// <param name="lParam">���b�Z�[�W�̒ǉ����i2�ڂ̃p�����[�^�j</param>
	/// <returns>���b�Z�[�W�������������ʁi�ʏ�� `DefWindowProc` �̖߂�l��Ԃ��j</returns>
	LRESULT WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	// �������t���O
	bool initialized = false;
};
