#include "Sprite.h"
#include <cassert>
#include <Windows.h>

Sprite::Sprite(ID3D11Device* device,const wchar_t* textureFileName)
{
	// 入力レイアウトの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,4 * 7,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	UINT numElements = ARRAYSIZE(layout);

	HRESULT	hr = S_OK;

	//	頂点バッファ作成
	D3D11_BUFFER_DESC bd = {};
	//GPU (読み取り専用)とCPU(書き込み専用) の両方からアクセス可能
	bd.Usage = D3D11_USAGE_DYNAMIC;
	// 頂点バッファのサイズ
	bd.ByteWidth = sizeof(Vertex) * 4;
	// 頂点バッファ
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// GPU→読み取りのみ　CPU→書き込みのみ
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	// 頂点バッファ作成
	hr = device->CreateBuffer(&bd,nullptr,&vertexBuffer);
	if(FAILED(hr))
	{
		assert(0 && "頂点バッファ作成失敗");
		return;
	}

	// ステートの作成
	CreateState(device);
}

void Sprite::CreateState(ID3D11Device* device)
{
	HRESULT	hr = S_OK;

	//	ラスタライザステートの設定
	D3D11_RASTERIZER_DESC rsDesc = {};
	rsDesc.FillMode = D3D11_FILL_SOLID;
	rsDesc.CullMode = D3D11_CULL_NONE;// カリング
	rsDesc.FrontCounterClockwise = false;
	rsDesc.DepthBias = 0;
	rsDesc.DepthBiasClamp = 0;
	rsDesc.SlopeScaledDepthBias = 0;
	rsDesc.DepthClipEnable = false;
	rsDesc.ScissorEnable = false;
	rsDesc.MultisampleEnable = false;
	rsDesc.AntialiasedLineEnable = false;
	// ラスタライザステート作成
	hr = device->CreateRasterizerState(&rsDesc,&rasterizerState);
	if(FAILED(hr))
	{
		assert(!"ラスタライザステートの作成に失敗(Sprite)");
		return;
	}

	//	サンプラーステートの作成
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc,sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = device->CreateSamplerState(&samplerDesc,&samplerState);
	if(FAILED(hr))
	{
		assert(0 && "サンプラーステート作成失敗");
	}

	// 深層ステンシルステート
	D3D11_DEPTH_STENCIL_DESC dssDesc = {};
	// 深度テスト無効
	dssDesc.DepthEnable = FALSE;
	// ついでにステンシルも無効
	dssDesc.StencilEnable = FALSE;
	hr = device->CreateDepthStencilState(&dssDesc,&depthStencilState);
	if(FAILED(hr))
	{
		assert(0 && "深度ステンシルState作成失敗");
	}
}