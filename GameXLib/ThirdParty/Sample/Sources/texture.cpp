//#include "../../Library/DirectX/WICTextureLoader11.h" 
//
//using namespace DirectX;
//
//#include <wrl.h> 
//using namespace Microsoft::WRL;
//
//#include <string> 
//#include <map> 
//#include <memory>
//using namespace std;
//
//#include "texture.h"
//#include "../../Library/Misc.h"
//
//static map<wstring, ComPtr<ID3D11ShaderResourceView>> resources;
//HRESULT load_texture_from_file(ID3D11Device* device, const wchar_t* filename, ID3D11ShaderResourceView** shader_resource_view, D3D11_TEXTURE2D_DESC* texture2d_desc)
//{
//	HRESULT hr{ S_OK };
//	ComPtr<ID3D11Resource> resource;
//
//	auto it = resources.find(filename);
//	if (it != resources.end())
//	{
//		*shader_resource_view = it->second.Get();
//		(*shader_resource_view)->AddRef();
//		(*shader_resource_view)->GetResource(resource.GetAddressOf());
//	}
//	else
//	{
//		hr = CreateWICTextureFromFile(device, filename, resource.GetAddressOf(), shader_resource_view);
//		_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
//		resources.insert(make_pair(filename, *shader_resource_view));
//	}
//
//	ComPtr<ID3D11Texture2D> texture2d;
//	hr = resource.Get()->QueryInterface<ID3D11Texture2D>(texture2d.GetAddressOf());
//	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
//	texture2d->GetDesc(texture2d_desc);
//
//	return hr;
//}
//
//void release_all_textures()
//{
//	resources.clear();
//}
//
//HRESULT create_vs_from_cso(ID3D11Device* device, const char* cso_name, ID3D11VertexShader** vertex_shader, ID3D11InputLayout** input_layout, D3D11_INPUT_ELEMENT_DESC* input_element_desc, UINT num_elements)
//{
//	FILE* fp{ nullptr };
//	fopen_s(&fp, cso_name, "rb");
//	_ASSERT_EXPR_A(fp, "CSO File not found");
//
//	fseek(fp, 0, SEEK_END);
//	long cso_sz{ ftell(fp) };
//	fseek(fp, 0, SEEK_SET);
//	unique_ptr<unsigned char[]> cso_data{ make_unique<unsigned char[]>(cso_sz) };
//	fread(cso_data.get(), cso_sz, 1, fp);
//	fclose(fp);
//
//	HRESULT hr{ S_OK };
//	hr = device->CreateVertexShader(cso_data.get(), cso_sz, nullptr, vertex_shader);
//	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
//
//	if (input_layout)
//	{
//		hr = device->CreateInputLayout(input_element_desc, num_elements, cso_data.get(), cso_sz, input_layout);
//		_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
//	}
//
//	return hr;
//}
//
//HRESULT create_ps_from_cso(ID3D11Device* device, const char* cso_name, ID3D11PixelShader** pixel_shader)
//{
//	FILE* fp{ nullptr };
//	fopen_s(&fp, cso_name, "rb");
//	_ASSERT_EXPR_A(fp, "CSO File not found");
//
//	fseek(fp, 0, SEEK_END);
//	long cso_sz{ ftell(fp) };
//	fseek(fp, 0, SEEK_SET);
//
//	unique_ptr<unsigned char[]> cso_data{ make_unique<unsigned char[]>(cso_sz) };
//	fread(cso_data.get(), cso_sz, 1, fp);
//	fclose(fp);
//
//	HRESULT hr{ S_OK };
//	hr = device->CreatePixelShader(cso_data.get(), cso_sz, nullptr, pixel_shader);
//	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
//
//	return hr;
//}
//
//HRESULT make_dummy_texture(ID3D11Device* device, ID3D11ShaderResourceView** shader_resource_view, DWORD value/*0xAABBGGRR*/, UINT dimension)
//{
//	HRESULT hr{ S_OK };
//
//	D3D11_TEXTURE2D_DESC texture2d_desc{};
//	texture2d_desc.Width = dimension;
//	texture2d_desc.Height = dimension;
//	texture2d_desc.MipLevels = 1;
//	texture2d_desc.ArraySize = 1;
//	texture2d_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	texture2d_desc.SampleDesc.Count = 1;
//	texture2d_desc.SampleDesc.Quality = 0;
//	texture2d_desc.Usage = D3D11_USAGE_DEFAULT;
//	texture2d_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
//
//	size_t texels = dimension * dimension;
//	unique_ptr<DWORD[]> sysmem{ make_unique< DWORD[]>(texels) };
//	for (size_t i = 0; i < texels; ++i) sysmem[i] = value;
//
//	D3D11_SUBRESOURCE_DATA subresource_data{};
//	subresource_data.pSysMem = sysmem.get();
//	subresource_data.SysMemPitch = sizeof(DWORD) * dimension;
//	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
//
//	ComPtr<ID3D11Texture2D> texture2d;
//	hr = device->CreateTexture2D(&texture2d_desc, &subresource_data, &texture2d);
//	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
//
//	D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_desc{};
//	shader_resource_view_desc.Format = texture2d_desc.Format;
//	shader_resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//	shader_resource_view_desc.Texture2D.MipLevels = 1;
//	hr = device->CreateShaderResourceView(texture2d.Get(), &shader_resource_view_desc, shader_resource_view);
//	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
//
//	return hr;
//}
