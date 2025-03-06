#pragma once
#include <d3d11.h>
#include <vector>
#include <functional>

/// <summary>
/// ImGui �̏������E�X�V�E�`��E�I���������Ǘ������{�N���X
/// </summary>
class BaseImGuiManager
{
public:
	/// <summary>
	/// ImGui�̏���������
	/// </summary>
	/// <param name="hwnd">�E�B���h�E�n���h��</param>
	/// <param name="device">DirectX 11 �f�o�C�X</param>
	/// <param name="immediateContext">DirectX 11 �f�o�C�X�R���e�L�X�g</param>
	/// <return>����</return>
	virtual bool Initialize(
		HWND hwnd,
		ID3D11Device* device,
		ID3D11DeviceContext*
		immediateContext)
	{
		return true;
	}

	/// <summary>
	/// ImGui�̏I������
	/// </summary>
	virtual void Uninitialize() {}

	/// <summary>
	/// Imgui�̑S�ʏ���
	/// </summary>
	virtual void RenderImGuiFrame() {}

	/// <summary>
	/// �֐��|�C���^�[��o�^����
	/// </summary>
	/// <param name="func">�o�^����֐�</param>
	virtual void RegisterImGuiFunction(std::function<void()> func) {}

	/// <summary>
	/// ImGui�̃E�B���h�E���b�Z�[�W���������郁���o�֐�
	/// </summary>
	/// <param name="hwnd">�E�B���h�E�n���h��</param>
	/// <param name="msg">�󂯎�������b�Z�[�W</param>
	/// <param name="wParam">���b�Z�[�W�̒ǉ����i1�ڂ̃p�����[�^�j</param>
	/// <param name="lParam">���b�Z�[�W�̒ǉ����i2�ڂ̃p�����[�^�j</param>
	/// <returns>���b�Z�[�W�������������ʁi�ʏ�� `DefWindowProc` �̖߂�l��Ԃ��j</returns>
	virtual LRESULT WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{ 
		return 0; 
	}
};

/// <summary>
/// ImGui �̏������E�X�V�E�`��E�I���������Ǘ�����N���X
/// </summary>
class ImGuiManager : public BaseImGuiManager
{
public:
	/// <summary>
	/// ImGui�̏���������
	/// </summary>
	/// <param name="hwnd">�E�B���h�E�n���h��</param>
	/// <param name="device">DirectX 11 �f�o�C�X</param>
	/// <param name="immediateContext">DirectX 11 �f�o�C�X�R���e�L�X�g</param>
	/// <return>����</return>
	bool Initialize(
		HWND hwnd, 
		ID3D11Device* device, 
		ID3D11DeviceContext*
		immediateContext) override;

	/// <summary>
	/// ImGui�̏I������
	/// </summary>
	void Uninitialize() override;

	/// <summary>
	/// Imgui�̑S�ʏ���
	/// </summary>
	void RenderImGuiFrame() override;

	/// <summary>
	/// �֐��|�C���^�[��o�^����
	/// </summary>
	/// <param name="func">�o�^����֐�</param>
	void RegisterImGuiFunction(std::function<void()> func) override
	{
		drawFunctions.push_back(func);
	}

	/// <summary>
	/// ImGui�̃E�B���h�E���b�Z�[�W���������郁���o�֐�
	/// </summary>
	/// <param name="hwnd">�E�B���h�E�n���h��</param>
	/// <param name="msg">�󂯎�������b�Z�[�W</param>
	/// <param name="wParam">���b�Z�[�W�̒ǉ����i1�ڂ̃p�����[�^�j</param>
	/// <param name="lParam">���b�Z�[�W�̒ǉ����i2�ڂ̃p�����[�^�j</param>
	/// <returns>���b�Z�[�W�������������ʁi�ʏ�� `DefWindowProc` �̖߂�l��Ԃ��j</returns>
	LRESULT WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

private:
	// �������t���O
	bool initialized = false;
	// ImGui�\�������z��
	std::vector<std::function<void()>> drawFunctions;

private:
	/// <summary>
	/// �V�����t���[���̊J�n
	/// </summary>
	void NewFrame();

	/// <summary>
	/// ImGui�̕`�揈��
	/// </summary>
	void Render();
};