#include "../System/Misc.h"
#include "..\..\ThirdParty\DirectXTex\WICTextureLoader11.h"
#include "TextureResource.h"
#include <memory>

// ファイルからShaderResourceViewの作成
HRESULT TextureResource::LoadTextureFromFile(ID3D11Device* device,const wchar_t* filename)
{
	HRESULT hr{S_OK};

	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	hr = DirectX::CreateWICTextureFromFile(device,filename,resource.GetAddressOf(),shaderResourceView.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2d;
	hr = resource.Get()->QueryInterface<ID3D11Texture2D>(texture2d.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));
	texture2d->GetDesc(&texture2dDesc);
	return hr;
}

// ダミーテクスチャの作成
HRESULT TextureResource::MakeDummyTexture(ID3D11Device* device,DWORD value/*0xAABBGGRR*/,UINT dimension)
{
	HRESULT hr{S_OK};

	D3D11_TEXTURE2D_DESC texture2dDesc{};
	texture2dDesc.Width = dimension;
	texture2dDesc.Height = dimension;
	texture2dDesc.MipLevels = 1;
	texture2dDesc.ArraySize = 1;
	texture2dDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texture2dDesc.SampleDesc.Count = 1;
	texture2dDesc.SampleDesc.Quality = 0;
	texture2dDesc.Usage = D3D11_USAGE_DEFAULT;
	texture2dDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	size_t texels = dimension * dimension;
	std::unique_ptr<DWORD[]> sysmem{std::make_unique< DWORD[]>(texels)};
	for(size_t i = 0; i < texels; ++i) sysmem[i] = value;

	D3D11_SUBRESOURCE_DATA subResourceData{};
	subResourceData.pSysMem = sysmem.get();
	subResourceData.SysMemPitch = sizeof(DWORD) * dimension;
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2d;
	hr = device->CreateTexture2D(&texture2dDesc,&subResourceData,&texture2d);
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc{};
	shaderResourceViewDesc.Format = texture2dDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;
	hr = device->CreateShaderResourceView(texture2d.Get(),&shaderResourceViewDesc,shaderResourceView.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));

	return hr;
}

// セット
void TextureResource::Set(ID3D11DeviceContext* immediate_context,UINT slot)
{
	if(shaderResourceView)
	{
		immediate_context->PSSetShaderResources(slot,1,shaderResourceView.GetAddressOf());
		immediate_context->DSSetShaderResources(slot,1,shaderResourceView.GetAddressOf());
		immediate_context->HSSetShaderResources(slot,1,shaderResourceView.GetAddressOf());
	}
}

// ファイルからShaderResourceViewの作成
LoadTextureResource::LoadTextureResource(ID3D11Device* device,const wchar_t* filename)
{
	HRESULT hr{S_OK};

	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	hr = DirectX::CreateWICTextureFromFile(device,filename,resource.GetAddressOf(),shaderResourceView.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2d;
	hr = resource.Get()->QueryInterface<ID3D11Texture2D>(texture2d.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));
	texture2d->GetDesc(&texture2dDesc);
}

// ダミーテクスチャの作成
DummyTextureResource::DummyTextureResource(ID3D11Device* device,DWORD value/*0xAABBGGRR*/,UINT dimension)
{
	HRESULT hr{S_OK};

	D3D11_TEXTURE2D_DESC texture2d_desc{};
	texture2d_desc.Width = dimension;
	texture2d_desc.Height = dimension;
	texture2d_desc.MipLevels = 1;
	texture2d_desc.ArraySize = 1;
	texture2d_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texture2d_desc.SampleDesc.Count = 1;
	texture2d_desc.SampleDesc.Quality = 0;
	texture2d_desc.Usage = D3D11_USAGE_DEFAULT;
	texture2d_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	size_t texels = dimension * dimension;
	std::unique_ptr<DWORD[]> sysmem{std::make_unique< DWORD[]>(texels)};
	for(size_t i = 0; i < texels; ++i) sysmem[i] = value;

	D3D11_SUBRESOURCE_DATA subresource_data{};
	subresource_data.pSysMem = sysmem.get();
	subresource_data.SysMemPitch = sizeof(DWORD) * dimension;
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2d;
	hr = device->CreateTexture2D(&texture2d_desc,&subresource_data,&texture2d);
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));

	D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_desc{};
	shader_resource_view_desc.Format = texture2d_desc.Format;
	shader_resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shader_resource_view_desc.Texture2D.MipLevels = 1;
	hr = device->CreateShaderResourceView(texture2d.Get(),&shader_resource_view_desc,shaderResourceView.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));
}

RenderTargetTextureResource::RenderTargetTextureResource(ID3D11Device* device,u_int width,u_int height,DXGI_FORMAT format)
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture2D;
	HRESULT hr = S_OK;
	//	テクスチャ作成
	ZeroMemory(&texture2dDesc,sizeof(texture2dDesc));
	texture2dDesc.Width = width;
	texture2dDesc.Height = height;
	texture2dDesc.MipLevels = 1;
	texture2dDesc.ArraySize = 1;
	texture2dDesc.Format = format;
	texture2dDesc.SampleDesc.Count = 1;
	texture2dDesc.Usage = D3D11_USAGE_DEFAULT;
	texture2dDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	texture2dDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	hr = device->CreateTexture2D(&texture2dDesc,NULL,Texture2D.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));

	//	レンダーターゲットビュー作成
	D3D11_RENDER_TARGET_VIEW_DESC rtvd;
	ZeroMemory(&rtvd,sizeof(rtvd));
	rtvd.Format = format;
	rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvd.Texture2D.MipSlice = 0;
	hr = device->CreateRenderTargetView(Texture2D.Get(),&rtvd,renderTargetView.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));

	//	シェーダーリソースビュー作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd,sizeof(srvd));
	srvd.Format = format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MostDetailedMip = 0;
	srvd.Texture2D.MipLevels = 1;
	hr = device->CreateShaderResourceView(Texture2D.Get(),&srvd,shaderResourceView.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));
}

DepthStencilTextureResource::DepthStencilTextureResource(ID3D11Device* device,u_int width,u_int height,DXGI_FORMAT format)
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture2D;
	HRESULT hr = S_OK;
	//	テクスチャ作成
	ZeroMemory(&texture2dDesc,sizeof(texture2dDesc));
	texture2dDesc.Width = width;
	texture2dDesc.Height = height;
	texture2dDesc.MipLevels = 1;
	texture2dDesc.ArraySize = 1;
	texture2dDesc.Format = format;
	texture2dDesc.SampleDesc.Count = 1;
	texture2dDesc.SampleDesc.Quality = 0;
	texture2dDesc.Usage = D3D11_USAGE_DEFAULT;
	texture2dDesc.CPUAccessFlags = 0;
	texture2dDesc.MiscFlags = 0;
	texture2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	hr = device->CreateTexture2D(&texture2dDesc,NULL,Texture2D.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));

	// 深度ステンシルビュー設定
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd,sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0;
	hr = device->CreateDepthStencilView(Texture2D.Get(),&dsvd,depthStencilView.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));

	//	シェーダーリソースビュー作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd,sizeof(srvd));
	srvd.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MostDetailedMip = 0;
	srvd.Texture2D.MipLevels = 1;
	hr = device->CreateShaderResourceView(Texture2D.Get(),&srvd,shaderResourceView.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));
}
