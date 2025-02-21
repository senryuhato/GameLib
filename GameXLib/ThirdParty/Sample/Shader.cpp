#include "../../Runtime/System/Misc.h"
#include "Shader.h"
#include <filesystem>
#include <stdio.h>
#include <memory>

// コンストラクタ
VertexShader::VertexShader(ID3D11Device* device,
	const char* vs_cso_file_path,
	D3D11_INPUT_ELEMENT_DESC* input_element_desc,
	UINT num_elements)
{
	FILE* fp{ nullptr };
	fopen_s(&fp, vs_cso_file_path, "rb");
	_ASSERT_EXPR_A(fp, "CSO File not found");

	fseek(fp, 0, SEEK_END);
	long cso_sz{ ftell(fp) };
	fseek(fp, 0, SEEK_SET);

	std::unique_ptr<unsigned char[]> cso_data{ std::make_unique<unsigned char[]>(cso_sz) };
	fread(cso_data.get(), cso_sz, 1, fp);
	fclose(fp);

	HRESULT hr{ S_OK };
	hr = device->CreateVertexShader(cso_data.get(), cso_sz, nullptr, shader_object.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));

	hr = device->CreateInputLayout(input_element_desc, num_elements, cso_data.get(), cso_sz, input_layout.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
}

// コンストラクタ
PixelShader::PixelShader(ID3D11Device* device, const char* ps_cso_file_path)
{
	FILE* fp{ nullptr };
	fopen_s(&fp, ps_cso_file_path, "rb");
	_ASSERT_EXPR_A(fp, "CSO File not found");

	fseek(fp, 0, SEEK_END);
	long cso_sz{ ftell(fp) };
	fseek(fp, 0, SEEK_SET);

	std::unique_ptr<unsigned char[]> cso_data{ std::make_unique<unsigned char[]>(cso_sz) };
	fread(cso_data.get(), cso_sz, 1, fp);
	fclose(fp);

	HRESULT hr{ S_OK };
	hr = device->CreatePixelShader(cso_data.get(), cso_sz, nullptr, shader_object.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
}