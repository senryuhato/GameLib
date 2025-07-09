#include "../System/Misc.h"
#include "RenderState.h"

// コンストラクタ
BlendState::BlendState(ID3D11Device* device,const D3D11_BLEND_DESC* bd)
{
	HRESULT hr = device->CreateBlendState(bd,state_object.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));
}
BlendState::BlendState(ID3D11Device* device,BLEND_MODE mode)
{
	D3D11_BLEND_DESC bd = {};
	switch(mode)
	{
	case BLEND_MODE::NONE:
	bd.AlphaToCoverageEnable = FALSE;
	bd.IndependentBlendEnable = FALSE;
	bd.RenderTarget[0].BlendEnable = FALSE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	break;
	case BLEND_MODE::ALPHA:
	bd.AlphaToCoverageEnable = FALSE;
	bd.IndependentBlendEnable = FALSE;
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	break;
	case BLEND_MODE::ADD:
	bd.AlphaToCoverageEnable = FALSE;
	bd.IndependentBlendEnable = FALSE;
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; //D3D11_BLEND_ONE D3D11_BLEND_SRC_ALPHA
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	break;
	case BLEND_MODE::SUBTRACT:
	bd.AlphaToCoverageEnable = FALSE;
	bd.IndependentBlendEnable = FALSE;
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; //D3D11_BLEND_ZERO
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE; //D3D11_BLEND_INV_SRC_COLOR
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_SUBTRACT; //D3D11_BLEND_OP_ADD
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	break;
	case BLEND_MODE::REPLACE:
	bd.AlphaToCoverageEnable = FALSE;
	bd.IndependentBlendEnable = FALSE;
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	break;
	case BLEND_MODE::MULTIPLY:
	bd.AlphaToCoverageEnable = FALSE;
	bd.IndependentBlendEnable = FALSE;
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO; //D3D11_BLEND_DEST_COLOR
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_COLOR; //D3D11_BLEND_SRC_COLOR
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_DEST_ALPHA;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	break;
	case BLEND_MODE::LIGHTEN:
	bd.AlphaToCoverageEnable = FALSE;
	bd.IndependentBlendEnable = FALSE;
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MAX;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	break;
	case BLEND_MODE::DARKEN:
	bd.AlphaToCoverageEnable = FALSE;
	bd.IndependentBlendEnable = FALSE;
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MIN;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MIN;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	break;
	case BLEND_MODE::SCREEN:
	bd.AlphaToCoverageEnable = FALSE;
	bd.IndependentBlendEnable = FALSE;
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; //D3DBLEND_INVDESTCOLOR
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR; //D3DBLEND_ONE
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	break;
	case BLEND_MODE::ALPHA_TO_COVERAGE:
	bd.AlphaToCoverageEnable = TRUE;
	bd.IndependentBlendEnable = FALSE;
	bd.RenderTarget[0].BlendEnable = FALSE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	break;
	}
	HRESULT hr = device->CreateBlendState(&bd,state_object.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));
}

// コンストラクタ
RasterizerState::RasterizerState(ID3D11Device* device,const D3D11_RASTERIZER_DESC* rd)
{
	HRESULT hr = device->CreateRasterizerState(rd,state_object.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));
}
RasterizerState::RasterizerState(ID3D11Device* device,
	D3D11_FILL_MODE fill_mode,
	D3D11_CULL_MODE cull_mode,
	bool front_counter_clockwise,
	bool antialiasing,
	bool depth_clip_enable)
{
	D3D11_RASTERIZER_DESC rasterizer_desc = {};
	rasterizer_desc.FillMode = fill_mode;
	rasterizer_desc.CullMode = cull_mode;
	rasterizer_desc.FrontCounterClockwise = front_counter_clockwise;
	rasterizer_desc.DepthBias = D3D11_DEFAULT_DEPTH_BIAS;
	rasterizer_desc.DepthBiasClamp = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;
	rasterizer_desc.SlopeScaledDepthBias = D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	rasterizer_desc.DepthClipEnable = static_cast<BOOL>(depth_clip_enable);
	rasterizer_desc.ScissorEnable = FALSE;
	rasterizer_desc.MultisampleEnable = antialiasing && fill_mode == D3D11_FILL_SOLID ? TRUE : FALSE;
	rasterizer_desc.AntialiasedLineEnable = antialiasing ? TRUE : FALSE;
	HRESULT hr = device->CreateRasterizerState(&rasterizer_desc,state_object.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));
}


DepthStencilState::DepthStencilState(ID3D11Device* device,const D3D11_DEPTH_STENCIL_DESC* dd)
{
	HRESULT hr = device->CreateDepthStencilState(dd,state_object.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));
}
DepthStencilState::DepthStencilState(ID3D11Device* device,
	BOOL depth_enable,
	D3D11_DEPTH_WRITE_MASK depth_write_mask,
	D3D11_COMPARISON_FUNC depth_func)
{
	D3D11_DEPTH_STENCIL_DESC dd;
	dd.DepthEnable = depth_enable;
	dd.DepthWriteMask = depth_write_mask;
	dd.DepthFunc = depth_func;
	dd.StencilEnable = FALSE;
	dd.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	dd.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	dd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	HRESULT hr = device->CreateDepthStencilState(&dd,state_object.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));

}

// コンストラクタ
SamplerState::SamplerState(ID3D11Device* device,
	D3D11_FILTER filter,
	D3D11_TEXTURE_ADDRESS_MODE address_mode,
	D3D11_COMPARISON_FUNC comparison_func,
	FLOAT color[4])
{
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd,sizeof(sd));
	sd.Filter = filter;
	sd.AddressU = address_mode;
	sd.AddressV = address_mode;
	sd.AddressW = address_mode;
	sd.ComparisonFunc = comparison_func;
	if(color) {
		memcpy(sd.BorderColor,color,sizeof(FLOAT) * 4);
	}

	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT hr = device->CreateSamplerState(&sd,state_object.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));
}
SamplerState::SamplerState(ID3D11Device* device,const D3D11_SAMPLER_DESC* sd)
{
	HRESULT hr = device->CreateSamplerState(sd,state_object.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr),HRTrace(hr));
}

