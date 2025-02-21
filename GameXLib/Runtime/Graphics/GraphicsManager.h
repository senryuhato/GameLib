#pragma once
#include <wrl.h>
#include <d3d11.h>

/// <summary>
/// DirectX 11 ��p�����O���t�B�b�N�X�Ǘ��N���X
/// </summary>
class GraphicsManager
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GraphicsManager() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GraphicsManager() { Uninitialize(); }

	/// <summary>
	/// DirectX �̏�����
	/// </summary>
	/// <param name="hwnd">�E�B���h�E�n���h��</param>
	/// <param name="defaultFramerate">�ڕW�t���[�����[�g�i�f�t�H���g: 60�j</param>
	/// <param name="isFullscreen">�t���X�N���[���̐ݒ�B�i�f�t�H���g: false�jtrue:�t���X�N���[���Afalse:�ʏ�</param>
	/// <returns>����</returns>
	bool Initialize(
		HWND hwnd, 
		UINT defaultFramerate = 60,
		BOOL isFullscreen = false);

	/// <summary>
	/// DirectX �̃��\�[�X�����
	/// </summary>
	void Uninitialize();

public:
	/// <summary>
	/// Direct3D �f�o�C�X���擾
	/// </summary>
	/// <returns>ID3D11Device �̃|�C���^</returns>
	ID3D11Device* GetDevice() const { return device.Get(); }

	/// <summary>
	/// �f�o�C�X�R���e�L�X�g���擾
	/// </summary>
	/// <returns>ID3D11DeviceContext �̃|�C���^</returns>
	ID3D11DeviceContext* GetDeviceContext() const { return immediateContext.Get(); }

	/// <summary>
    /// �X���b�v�`�F�C�����擾
    /// </summary>
    /// <returns>IDXGISwapChain �̃|�C���^</returns>
	IDXGISwapChain* GetSwapChain() const { return swapChain.Get(); }

	/// <summary>
	/// �t���[���o�b�t�@�p�����_�[�^�[�Q�b�g�r���[���擾
	/// </summary>
	/// <returns>ID3D11RenderTargetView �̃|�C���^</returns>
	ID3D11RenderTargetView* GetRenderTargetView() const { return renderTargetView.Get(); }

	/// <summary>
	/// �t���[���o�b�t�@�p�f�v�X�X�e���V���r���[���擾
	/// </summary>
	/// <returns>ID3D11DepthStencilView �̃|�C���^</returns>
	ID3D11DepthStencilView* GetDepthStencilView() const { return depthStencilView.Get(); }

private:
	/// <summary>
	/// �f�o�C�X���X���b�v�`�F�C���̍쐬
	/// </summary>
	/// <param name="hwnd">�E�B���h�E�n���h��</param>
	/// <param name="frameBufferWidth">�t���[���o�b�t�@�̕�</param>
	/// <param name="frameBufferHeight">�t���[���o�b�t�@�̍���</param>
	/// <param name="isFullscreen">�t���X�N���[���̐ݒ�Btrue:�t���X�N���[���Afalse:�ʏ�</param>
	void CreateDeviceAndSwapChain(
		HWND hwnd, 
		UINT frameBufferWidth, 
		UINT frameBufferHeight, 
		UINT defaultFramerate,
		BOOL isFullscreen);

	/// <summary>
	/// ���[���o�b�t�@�p�̃����_�[�^�[�Q�b�g�r���[�iRTV�j���쐬
	/// </summary>
	void CreateRTVForFrameBuffer();

	/// <summary>
	/// �t���[���o�b�t�@�p�̐[�x�X�e���V���r���[�iDSV�j���쐬
	/// </summary>
	/// <param name="frameBufferWidth">�t���[���o�b�t�@�̕�</param>
	/// <param name="frameBufferHeight">�t���[���o�b�t�@�̍���</param>
	void CreateDSVForFrameBuffer(
		UINT frameBufferWidth, 
		UINT frameBufferHeight);

private:
	// �X���b�v�`�F�C��
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain = nullptr;
	// Direct3D �f�o�C�X
	Microsoft::WRL::ComPtr<ID3D11Device> device = nullptr;
	// �f�o�C�X�R���e�L�X�g
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediateContext = nullptr;
	// �t���[���o�b�t�@�p�����_�[�^�[�Q�b�g�r���[�@
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  renderTargetView = nullptr;
	// �t���[���o�b�t�@�p�f�v�X�X�e���V���r���[
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  depthStencilView = nullptr;

	//�t���[���o�b�t�@�̕�
	UINT frameBufferWidth = 0; 
	//�t���[���o�b�t�@�̍���
	UINT frameBufferHeight = 0;
	// �����t���[�����[�g
	UINT defaultFramerate = 60;
};