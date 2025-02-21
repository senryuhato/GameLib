#pragma once
#include <d3d11.h>
#include <wrl.h>

// 頂点シェーダー
class VertexShader
{
public:
	// コンストラクタ
	VertexShader(ID3D11Device* device,
		const char* vs_cso_file_path,
		D3D11_INPUT_ELEMENT_DESC* input_element_desc,
		UINT num_elements);

	// シェーダー設定
	void Set(ID3D11DeviceContext* immediate_context)
	{
		immediate_context->VSSetShader(shader_object.Get(), nullptr, 0);
		immediate_context->IASetInputLayout(input_layout.Get());
	}
public:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> shader_object; // 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout; // インプットレイアウト
};

// ピクセルシェーダー
class PixelShader
{
public:
	// コンストラクタ
	PixelShader(ID3D11Device* device, const char* ps_cso_file_path);

	// シェーダー設定
	void Set(ID3D11DeviceContext* immediate_context)
	{
		immediate_context->PSSetShader(shader_object.Get(), nullptr, 0);
	}
public:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> shader_object; // 頂点シェーダー
};
