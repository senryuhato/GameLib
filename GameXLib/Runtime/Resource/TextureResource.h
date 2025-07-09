#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <dxgiformat.h>

class TextureResource
{
public:
	// ファイルからShaderResourceViewの作成
	HRESULT LoadTextureFromFile(ID3D11Device* device,const wchar_t* filename);
	// ダミーテクスチャの作成
	HRESULT MakeDummyTexture(ID3D11Device* device,DWORD value/*0xAABBGGRR*/,UINT dimension);
	// セット
	void Set(ID3D11DeviceContext* immediate_context,UINT slot);
public:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView = nullptr; // シェーダーリソース
	D3D11_TEXTURE2D_DESC texture2dDesc; // テクスチャ情報
};

class LoadTextureResource
{
public:
	// ファイルからShaderResourceViewの作成
	LoadTextureResource(ID3D11Device* device,const wchar_t* filename);
public:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView = nullptr; // シェーダーリソース
	D3D11_TEXTURE2D_DESC texture2dDesc; // テクスチャ情報

};

class DummyTextureResource
{
public:
	// ダミーテクスチャの作成
	DummyTextureResource(ID3D11Device* device,DWORD value/*0xAABBGGRR*/,UINT dimension);
public:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView = nullptr; // シェーダーリソース
	D3D11_TEXTURE2D_DESC texture2dDesc; // テクスチャ情報

};

class RenderTargetTextureResource
{
public:
	RenderTargetTextureResource(ID3D11Device* device,u_int width,u_int height,DXGI_FORMAT format);

public:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView = nullptr; // シェーダーリソース
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
	D3D11_TEXTURE2D_DESC texture2dDesc; // テクスチャ情報
};

class DepthStencilTextureResource
{
public:
	DepthStencilTextureResource(ID3D11Device* device,u_int width,u_int height,DXGI_FORMAT format);

public:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView = nullptr; // シェーダーリソース
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView = nullptr;
	D3D11_TEXTURE2D_DESC texture2dDesc; // テクスチャ情報
};