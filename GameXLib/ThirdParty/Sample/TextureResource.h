//#pragma once
//#include <d3d11.h>
//#include <wrl.h>
//
//class TextureResource
//{
//public:
//	// �t�@�C������ShaderResourceView�̍쐬
//	HRESULT LoadTextureFromFile(ID3D11Device* device, const wchar_t* filename);
//	// �_�~�[�e�N�X�`���̍쐬
//	HRESULT MakeDummyTexture(ID3D11Device* device, DWORD value/*0xAABBGGRR*/, UINT dimension);
//	// �Z�b�g
//	void Set(ID3D11DeviceContext* immediate_context, UINT slot);
//public:
//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_view = nullptr; // �V�F�[�_�[���\�[�X
//	D3D11_TEXTURE2D_DESC texture2d_desc; // �e�N�X�`�����
//};
//
//class LoadTextureResource
//{
//public:
//	// �t�@�C������ShaderResourceView�̍쐬
//	LoadTextureResource(ID3D11Device* device, const wchar_t* filename);
//public:
//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_view = nullptr; // �V�F�[�_�[���\�[�X
//	D3D11_TEXTURE2D_DESC texture2d_desc; // �e�N�X�`�����
//
//};
//
//class DummyTextureResource
//{
//public:
//	// �_�~�[�e�N�X�`���̍쐬
//	DummyTextureResource(ID3D11Device* device, DWORD value/*0xAABBGGRR*/, UINT dimension);
//public:
//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_view = nullptr; // �V�F�[�_�[���\�[�X
//	D3D11_TEXTURE2D_DESC texture2d_desc; // �e�N�X�`�����
//
//};
//
//class RenderTargetTextureResource
//{
//public:
//	RenderTargetTextureResource(ID3D11Device* device, u_int width, u_int height, DXGI_FORMAT format);
//
//public:
//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_view = nullptr; // �V�F�[�_�[���\�[�X
//	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view = nullptr;
//	D3D11_TEXTURE2D_DESC texture2d_desc; // �e�N�X�`�����
//};
//
//class DepthStencilTextureResource
//{
//public:
//	DepthStencilTextureResource(ID3D11Device* device, u_int width, u_int height, DXGI_FORMAT format);
//
//public:
//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_view = nullptr; // �V�F�[�_�[���\�[�X
//	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view = nullptr;
//	D3D11_TEXTURE2D_DESC texture2d_desc; // �e�N�X�`�����
//};