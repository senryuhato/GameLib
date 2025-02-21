#pragma once
#include "../Misc.h"
#include <d3d11.h>
#include <wrl.h>
#include <vector>

template<class BufferType>
class ConstantBuffer
{
public:
	// コンストラクタ
	ConstantBuffer(ID3D11Device* device)
	{
		// 定数バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.ByteWidth = sizeof(BufferType);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;

		HRESULT hr = device->CreateBuffer(&bd, NULL, buffer.GetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
	}
	// バッファの更新
	void UpdateBuffer(ID3D11DeviceContext* immediate_context)
	{
		immediate_context->UpdateSubresource(buffer.Get(), 0, NULL, &data, 0, 0);
	}

public:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer; // コンスタントバッファ
	BufferType data; // バッファのCpuデータ
};

class MeshBuffer
{
public:
	/* bind_flags :
	D3D11_BIND_VERTEX_BUFFER
	D3D11_BIND_INDEX_BUFFER*/
	MeshBuffer(ID3D11Device* device, UINT bind_flags, uint32_t stride, const void* data, size_t data_size)
	{
		HRESULT hr{ S_OK };
		D3D11_BUFFER_DESC buffer_desc{};
		D3D11_SUBRESOURCE_DATA subresource_data{};
		buffer_desc.ByteWidth = static_cast<UINT>(stride * data_size);
		buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		buffer_desc.BindFlags = bind_flags;
		buffer_desc.CPUAccessFlags = 0;
		buffer_desc.MiscFlags = 0;
		buffer_desc.StructureByteStride = 0;
		subresource_data.pSysMem = data;
		subresource_data.SysMemPitch = 0;
		subresource_data.SysMemSlicePitch = 0;
		hr = device->CreateBuffer(&buffer_desc, &subresource_data, buffer.ReleaseAndGetAddressOf());
		_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
	}

public:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer; // バッファ
};
