#include <d3d11.h>
#include <wrl.h>

// �u�����h���[�h
enum class BLEND_MODE
{
	NONE,
	ALPHA, 
	ADD,
	SUBTRACT, 
	REPLACE, 
	MULTIPLY,
	LIGHTEN,
	DARKEN,
	SCREEN,
	ALPHA_TO_COVERAGE,
	END
};

// �u�����h�X�e�[�g
class BlendState
{
public:
	// �R���X�g���N�^
	BlendState(ID3D11Device* device, const D3D11_BLEND_DESC* bd);
	BlendState(ID3D11Device* device, BLEND_MODE mode);

	// �V�F�[�_�[�ݒ�
	void Set(ID3D11DeviceContext* immediate_context)
	{
		immediate_context->OMSetBlendState(state_object.Get(), 0, 0xFFFFFFFF);
	}
public:
	Microsoft::WRL::ComPtr <ID3D11BlendState> state_object = nullptr; // �I�u�W�F�N�g
};

// ���X�^���C�U�X�e�[�g
class RasterizerState
{
public:
	// �R���X�g���N�^
	RasterizerState(ID3D11Device* device, const D3D11_RASTERIZER_DESC* rd);
	RasterizerState(ID3D11Device* device,
		D3D11_FILL_MODE fill_mode = D3D11_FILL_SOLID, 
		D3D11_CULL_MODE cull_mode = D3D11_CULL_BACK,
		bool front_counter_clockwise = false,
		bool antialiasing = false,
		bool depth_clip_enable = true);

	// �V�F�[�_�[�ݒ�
	void Set(ID3D11DeviceContext* immediate_context)
	{
		immediate_context->RSSetState(state_object.Get());
	}
public:
	Microsoft::WRL::ComPtr <ID3D11RasterizerState> state_object = nullptr; // �I�u�W�F�N�g
};

// �f�v�X�X�e���V���X�e�[�g
class DepthStencilState
{
public:
	// �R���X�g���N�^
	DepthStencilState(ID3D11Device* device, const D3D11_DEPTH_STENCIL_DESC* dd);
	DepthStencilState(ID3D11Device* device, 
		BOOL depth_enable = TRUE,
		D3D11_DEPTH_WRITE_MASK depth_write_mask = D3D11_DEPTH_WRITE_MASK_ALL,
		D3D11_COMPARISON_FUNC depth_func = D3D11_COMPARISON_LESS);

	// �V�F�[�_�[�ݒ�
	void Set(ID3D11DeviceContext* immediate_context)
	{
		immediate_context->OMSetDepthStencilState(state_object.Get(), 1);
	}
public:
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> state_object; // �I�u�W�F�N�g
};

// �T���v���[�X�e�[�g
class SamplerState
{
public:
	// �R���X�g���N�^
	SamplerState(ID3D11Device* device, const D3D11_SAMPLER_DESC* sd);
	SamplerState(ID3D11Device* device, 
		D3D11_FILTER filter = D3D11_FILTER_ANISOTROPIC,
		D3D11_TEXTURE_ADDRESS_MODE address_mode = D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_COMPARISON_FUNC comparison_func = D3D11_COMPARISON_NEVER,
		FLOAT color[4] = { 0 });
	// �V�F�[�_�[�ݒ�
	void Set(ID3D11DeviceContext* immediate_context, UINT slot)
	{
		immediate_context->PSSetSamplers(slot, 1, state_object.GetAddressOf());
	}

public:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> state_object = nullptr;  // �I�u�W�F�N�g
};
