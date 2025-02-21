#pragma once
#include <d3d11.h>
#include <wrl.h>

// ���_�V�F�[�_�[
class VertexShader
{
public:
	// �R���X�g���N�^
	VertexShader(ID3D11Device* device,
		const char* vs_cso_file_path,
		D3D11_INPUT_ELEMENT_DESC* input_element_desc,
		UINT num_elements);

	// �V�F�[�_�[�ݒ�
	void Set(ID3D11DeviceContext* immediate_context)
	{
		immediate_context->VSSetShader(shader_object.Get(), nullptr, 0);
		immediate_context->IASetInputLayout(input_layout.Get());
	}
public:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> shader_object; // ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout; // �C���v�b�g���C�A�E�g
};

// �s�N�Z���V�F�[�_�[
class PixelShader
{
public:
	// �R���X�g���N�^
	PixelShader(ID3D11Device* device, const char* ps_cso_file_path);

	// �V�F�[�_�[�ݒ�
	void Set(ID3D11DeviceContext* immediate_context)
	{
		immediate_context->PSSetShader(shader_object.Get(), nullptr, 0);
	}
public:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> shader_object; // ���_�V�F�[�_�[
};
