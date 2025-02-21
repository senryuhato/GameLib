#pragma once
#include <d3d11.h>
#include <wrl.h>

class TextureResource
{
public:
	// ファイルからShaderResourceViewの作成
	HRESULT LoadTextureFromFile(ID3D11Device* device, const wchar_t* filename);
	// ダミーテクスチャの作成
	HRESULT MakeDummyTexture(ID3D11Device* device, DWORD value/*0xAABBGGRR*/, UINT dimension);
	// セット
	void Set(ID3D11DeviceContext* immediate_context, UINT slot);
public:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_view = nullptr; // シェーダーリソース
	D3D11_TEXTURE2D_DESC texture2d_desc; // テクスチャ情報
};

class LoadTextureResource
{
public:
	// ファイルからShaderResourceViewの作成
	LoadTextureResource(ID3D11Device* device, const wchar_t* filename);
public:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_view = nullptr; // シェーダーリソース
	D3D11_TEXTURE2D_DESC texture2d_desc; // テクスチャ情報

};

class DummyTextureResource
{
public:
	// ダミーテクスチャの作成
	DummyTextureResource(ID3D11Device* device, DWORD value/*0xAABBGGRR*/, UINT dimension);
public:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_view = nullptr; // シェーダーリソース
	D3D11_TEXTURE2D_DESC texture2d_desc; // テクスチャ情報

};

class RenderTargetTextureResource
{
public:
	RenderTargetTextureResource(ID3D11Device* device, u_int width, u_int height, DXGI_FORMAT format);

public:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_view = nullptr; // シェーダーリソース
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view = nullptr;
	D3D11_TEXTURE2D_DESC texture2d_desc; // テクスチャ情報
};

class DepthStencilTextureResource
{
public:
	DepthStencilTextureResource(ID3D11Device* device, u_int width, u_int height, DXGI_FORMAT format);

public:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_view = nullptr; // シェーダーリソース
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view = nullptr;
	D3D11_TEXTURE2D_DESC texture2d_desc; // テクスチャ情報
};