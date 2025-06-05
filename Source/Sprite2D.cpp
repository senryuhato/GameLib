#include "Sprite2D.h"

Sprite2D::Sprite2D(ID3D11Device* device, const wchar_t* texture_file_name, const wchar_t* normal_texture_name)
{
	vertex vertices[] =
	{
		{ DirectX::XMFLOAT3(-0.5, +0.5, 0), DirectX::XMFLOAT4(1, 1, 1, 1) },
		{ DirectX::XMFLOAT3(+0.5, +0.5, 0), DirectX::XMFLOAT4(1, 0, 0, 1) },
		{ DirectX::XMFLOAT3(-0.5, -0.5, 0), DirectX::XMFLOAT4(0, 1, 0, 1) },
		{ DirectX::XMFLOAT3(+0.5, -0.5, 0), DirectX::XMFLOAT4(0, 0, 1, 1) },
	};

	HRESULT	hr;

	//	頂点バッファ作成
	D3D11_BUFFER_DESC bd = {};
	//ZeroMemory(&bd, sizeof(bd));
	//D3D11_USAGE_DEFAULT; //GPU (読み取り専用) と CPU (書き込み専用) の両方からアクセス可能
	bd.Usage = D3D11_USAGE_DYNAMIC;
	//	又は sizeof(Vertex) * 4
	bd.ByteWidth = sizeof(vertices);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//0;CPU アクセスが必要ない場合は 0 //CPU がその内容を変更できる
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// サブリソース
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;

	hr = device->CreateBuffer(&bd, &InitData, &vertexBuffer);
	if (FAILED(hr))		assert(0 && "頂点バッファ作成失敗");

	// 入力レイアウト
	D3D11_INPUT_ELEMENT_DESC	layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::XMFLOAT3),D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, sizeof(DirectX::XMFLOAT3) + sizeof(DirectX::XMFLOAT4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "LIGHT",    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, sizeof(DirectX::XMFLOAT3) + sizeof(DirectX::XMFLOAT4) + sizeof(DirectX::XMFLOAT2), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },                                                                                               D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//{ "LIGHT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	};
	UINT numElement = ARRAYSIZE(layout);

	////	頂点シェーダー/入力レイアウトの生成
	//if (!ResourceManager::LoadVertexShaders(device,
	//	"sprite_vs.cso", layout, numElement,
	//	&vertex_shader, &input_layout))
	//{
	//	assert(0 && "頂点シェーダーor入力レイアウト作成失敗");
	//}

	////	ピクセルシェーダー作成
	//if (!ResourceManager::LoadPixelShaders(device, "sprite_ps.cso", &pixel_shader))
	//{
	//	assert(0 && "ピクセルシェーダー作成失敗");
	//}

	////	サンプラーステートの作成
	//D3D11_SAMPLER_DESC sd;
	//ZeroMemory(&sd, sizeof(sd));
	//sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	//sd.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	//sd.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	//sd.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	//sd.MaxAnisotropy = 16;
	//sd.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	//sd.MaxLOD = D3D11_FLOAT32_MAX;
	//hr = device->CreateSamplerState(&sd, &sampler_state);
	//if (FAILED(hr))	assert(0 && "サンプラーステート作成失敗");

	//// 深層ステンシル
	////D3D11_DEPTH_STENCIL_DESC dssDesc = {};
	////dssDesc.DepthEnable = FALSE;				//	深度テスト無効
	////dssDesc.StencilEnable = FALSE;				//	ついでにステンシルも無効
	////hr = device->CreateDepthStencilState(&dssDesc, &depth_stencil_state);
	////if (FAILED(hr))		assert(0 && "深度ステンシルState作成失敗");

	//D3D11_DEPTH_STENCIL_DESC dssDesc = {};
	//dssDesc.DepthEnable = TRUE;
	//dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	//dssDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	//dssDesc.StencilEnable = FALSE;
	//dssDesc.StencilReadMask = 0xFF;
	//dssDesc.StencilWriteMask = 0xFF;
	//dssDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	//dssDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	//dssDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//dssDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	//dssDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	//dssDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	//dssDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//dssDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	//hr = device->CreateDepthStencilState(&dssDesc, &depth_stencil_state);
}

void Sprite2D::Render(ID3D11DeviceContext* context,
	float dx, float dy,//Coordinate of sprite's left-top corner in screen space 
	float dw, float dh,//  Size of sprite in screen space  
	float sx, float sy, // Coordinate of sprite's left-top corner in texture space   
	float sw, float sh,  // Size of sprite in texture space 
	float angle, // Raotation angle(Rotation centre is sprite's centre), Unit is degree 
	float r, float g, float b, float a, // Color of sprite's each vertices  
	DirectX::XMFLOAT3 light
)
{
	//DirectX::XMFLOAT4 col = { r,g,b,a };

	//float x, y;

	///*x = dx * cos(DirectX::XMConvertToRadians(angle)) - dy * sin(DirectX::XMConvertToRadians(angle) + dx);
	//y = dx * sin(DirectX::XMConvertToRadians(angle)) + dy * cos(DirectX::XMConvertToRadians(angle) + dy);*/

	//x = dx, y = dy;

	//DirectX::XMFLOAT3 L = light;
	////static DirectX::XMFLOAT3 L = { -1.0f, -0.3f, -1.0f };

	//vertex vertices[] = {
	//	{ {x,    y,    .0f},       col, {sx,    sy} ,L},
	//	{ { x + dw, y,    .0f },   col, {sx + sw, sy} ,L},
	//	{ { x,    y + dh, .0f },   col, {sx,    sy + sh},L },
	//	{ { x + dw, y + dh, .0f }, col, {sx + sw, sy + sh} ,L},
	//};
	//vertex vertices1[] = {
	//	{ { x,    y,    .0f }, col },
	//	{ { x + dw, y,    .0f }, col },
	//	{ { x,    y + dh, .0f }, col },
	//	{ { x + dw, y + dh, .0f }, col },
	//};
	//for (int n = 0; n < 4; n++)
	//{
	//	/*vertices[n].position.x = vertices1[n].position.x * cos(DirectX::XMConvertToRadians(angle)) - vertices1[n].position.y * sin(DirectX::XMConvertToRadians(angle));
	//	vertices[n].position.y = vertices1[n].position.x * sin(DirectX::XMConvertToRadians(angle)) + vertices1[n].position.y * cos(DirectX::XMConvertToRadians(angle));*/


	//	/*vertices[n].position.x = (vertices1[n].position.x - dx) * cos(DirectX::XMConvertToRadians(angle)) - (vertices1[n].position.y - dy)* sin(DirectX::XMConvertToRadians(angle)) + dx;
	//	vertices[n].position.y = (vertices1[n].position.x - dx) * sin(DirectX::XMConvertToRadians(angle)) + (vertices1[n].position.y - dy) * cos(DirectX::XMConvertToRadians(angle)) + dy;*/

	//	vertices[n].position.x = (vertices[n].position.x - dx - dw / 2) * cos(DirectX::XMConvertToRadians(angle)) - (vertices[n].position.y - dy - dh / 2) * sin(DirectX::XMConvertToRadians(angle)) + dx + dw / 2;
	//	vertices[n].position.y = (vertices[n].position.x - dx - dw / 2) * sin(DirectX::XMConvertToRadians(angle)) + (vertices[n].position.y - dy - dh / 2) * cos(DirectX::XMConvertToRadians(angle)) + dy + dh / 2;


	//}


	//vertex verticesNDC[4];
	//for (int n = 0; n < 4; n++)
	//{
	//	verticesNDC[n].light_direction = vertices[n].light_direction;


	//	//	NDC変換
	//	verticesNDC[n].position.x = (vertices[n].position.x / SCREEN_WIDTH) * 2.0f - 1.0f;
	//	verticesNDC[n].position.y = -(vertices[n].position.y / SCREEN_HEIGHT) * 2.0f + 1.0f;
	//	verticesNDC[n].position.z = 1.0f;
	//	verticesNDC[n].color = vertices[n].color;



	//	//verticesNDC[n].position.x = dx * cos(DirectX::XMConvertToRadians(angle)) - dy * sin(DirectX::XMConvertToRadians(angle) /*+ dw / 2*/);
	//	//verticesNDC[n].position.y = dx * sin(DirectX::XMConvertToRadians(angle)) + dy * cos(DirectX::XMConvertToRadians(angle) /*+ dh / 2*/);

	//	//	UV座標正規化
	//	verticesNDC[n].texcoord.x = vertices[n].texcoord.x / texture2d_desc->Width;
	//	verticesNDC[n].texcoord.y = vertices[n].texcoord.y / texture2d_desc->Height;

	//}

	//D3D11_MAPPED_SUBRESOURCE sub_resource;
	//context->Map(vertex_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub_resource);
	//memcpy(sub_resource.pData, verticesNDC, sizeof(verticesNDC));
	//context->Unmap(vertex_buffer, 0);


	//// 頂点バッファのバインド
	//UINT stride = sizeof(vertex);
	//UINT offset = 0;
	//context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);

	//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//context->IASetInputLayout(input_layout);

	//context->RSSetState(rasterizer_state);

	//context->VSSetShader(vertex_shader, NULL, 0);

	//context->PSSetShader(pixel_shader, NULL, 0);

	//context->PSSetShaderResources(0, 1, &shader_resource_view);

	//if (normal_shader_resource_view)
	//{
	//	context->PSSetShaderResources(1, 1, &normal_shader_resource_view);
	//}
	//context->PSSetSamplers(0, 1, &sampler_state);

	//context->OMSetDepthStencilState(depth_stencil_state, 0);

	////context->OMSetBlendState(blend_state, nullptr, 0xFFFFFFFF);

	//context->Draw(4, 0);
};

//void Sprite::textout(ID3D11DeviceContext* immediate_context, std::string s, float x, float y, float w, float h, float r, float g, float b, float a)
//{
//	float sw = static_cast<float>(texture2d_desc->Width / 16);
//	float sh = static_cast<float>(texture2d_desc->Height / 16);
//	float cursor = 0;
//	for (auto c : s)
//	{
//		LONG sx = c % 0x0F;
//		render(immediate_context, x + cursor, y, w, h, sw * (c & 0x0F), sh * (c >> 4), sw, sh, 0, r, g, b, a);
//		cursor += w;
//	}
//}




//SpriteBatch::SpriteBatch(ID3D11Device* device, const wchar_t* file_name, size_t max_instance) : MAX_INSTANCES(max_instance)
//{
//	HRESULT hr = S_OK;
//
//	vertex vertices[] =
//	{
//		{ DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT2(0, 0) },
//		{ DirectX::XMFLOAT3(1, 0, 0), DirectX::XMFLOAT2(1, 0) },
//		{ DirectX::XMFLOAT3(0, 1, 0), DirectX::XMFLOAT2(0, 1) },
//		{ DirectX::XMFLOAT3(1, 1, 0), DirectX::XMFLOAT2(1, 1) },
//	};
//
//	D3D11_BUFFER_DESC bd = {};
//	bd.Usage = D3D11_USAGE_IMMUTABLE;
//	bd.ByteWidth = sizeof(vertices);
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bd.CPUAccessFlags = 0;
//	bd.MiscFlags = 0;
//	bd.StructureByteStride = 0;
//	D3D11_SUBRESOURCE_DATA subresource_data = {};
//	subresource_data.pSysMem = vertices;
//	subresource_data.SysMemPitch = 0; //Not use for vertex buffers.
//	subresource_data.SysMemSlicePitch = 0; //Not use for vertex buffers.
//	hr = device->CreateBuffer(&bd, &subresource_data, &vertex_buffer);
//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
//
//	D3D11_INPUT_ELEMENT_DESC	layout[] =
//	{
//		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                                                     D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "NDC_TRANSFORM", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
//		{ "NDC_TRANSFORM", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
//		{ "NDC_TRANSFORM", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
//		{ "NDC_TRANSFORM", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
//		{ "TEXCOORD_TRANSFORM", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
//		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
//	};
//	UINT numElement = ARRAYSIZE(layout);
//
//	//	頂点シェーダー/入力レイアウトの生成
//	if (!ResourceManager::LoadVertexShaders(device,
//		"sprite_batch_vs.cso", layout, numElement,
//		&vertex_shader, &input_layout))
//	{
//		assert(0 && "頂点シェーダーor入力レイアウト作成失敗");
//	}
//
//	if (!ResourceManager::LoadPixelShaders(device, "sprite_batch_ps.cso", &pixel_shader))
//	{
//		assert(0 && "ピクセルシェーダー作成失敗");
//	}
//
//	//	インスタンス生成
//	instance* instances = new instance[MAX_INSTANCES];
//	{
//		D3D11_BUFFER_DESC buffer_desc = {};
//		D3D11_SUBRESOURCE_DATA subresource_data = {};
//
//		buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
//		buffer_desc.ByteWidth = sizeof(instance) * (UINT)MAX_INSTANCES;
//		buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//		buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//		buffer_desc.MiscFlags = 0;
//		buffer_desc.StructureByteStride = 0;
//
//		subresource_data.pSysMem = instances;
//		subresource_data.SysMemPitch = 0; //Not use for vertex buffers.mm 
//		subresource_data.SysMemSlicePitch = 0; //Not use for vertex buffers.
//		hr = device->CreateBuffer(&buffer_desc, &subresource_data, &instance_buffer);
//		_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
//	}
//	delete[] instances;
//
//	D3D11_RASTERIZER_DESC rasterizer_desc = {};
//	rasterizer_desc.FillMode = D3D11_FILL_SOLID; //D3D11_FILL_WIREFRAME, D3D11_FILL_SOLID
//	rasterizer_desc.CullMode = D3D11_CULL_NONE; //D3D11_CULL_NONE, D3D11_CULL_FRONT, D3D11_CULL_BACK   
//	rasterizer_desc.FrontCounterClockwise = FALSE;
//	rasterizer_desc.DepthBias = 0;
//	rasterizer_desc.DepthBiasClamp = 0;
//	rasterizer_desc.SlopeScaledDepthBias = 0;
//	rasterizer_desc.DepthClipEnable = FALSE;
//	rasterizer_desc.ScissorEnable = FALSE;
//	rasterizer_desc.MultisampleEnable = FALSE;
//	rasterizer_desc.AntialiasedLineEnable = FALSE;
//	hr = device->CreateRasterizerState(&rasterizer_desc, &rasterizer_state);
//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
//
//	//	テクスチャ読み込み
//	if (!ResourceManager::LoadShaderResourceView(
//		device, file_name, &shader_resource_view, &texture2d_desc))
//	{
//		assert(0 && "テクスチャ読み込み失敗");
//	}
//
//	D3D11_SAMPLER_DESC sampler_desc = {};
//	sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC; //UNIT.06
//	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
//	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
//	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
//	sampler_desc.MipLODBias = 0;
//	sampler_desc.MaxAnisotropy = 16;
//	sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
//	memcpy(sampler_desc.BorderColor, &DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), sizeof(DirectX::XMFLOAT4));
//	sampler_desc.MinLOD = 0;
//	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
//	hr = device->CreateSamplerState(&sampler_desc, &sampler_state);
//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
//
//	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc = {};
//	depth_stencil_desc.DepthEnable = FALSE;
//	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
//	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
//	depth_stencil_desc.StencilEnable = FALSE;
//	depth_stencil_desc.StencilReadMask = 0xFF;
//	depth_stencil_desc.StencilWriteMask = 0xFF;
//	depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
//	depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
//	depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
//	depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
//	depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
//	depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
//	depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
//	depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
//	hr = device->CreateDepthStencilState(&depth_stencil_desc, &depth_stencil_state);
//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
//
//}
//
//
//void SpriteBatch::begin(ID3D11DeviceContext* context)
//{
//	HRESULT hr = S_OK;
//	UINT strides[2] = { sizeof(vertex), sizeof(instance) };
//	UINT offsets[2] = { 0, 0 };
//
//	ID3D11Buffer* vbs[2] = { vertex_buffer, instance_buffer };
//
//	context->IASetVertexBuffers(0, 2, vbs, strides, offsets);
//	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//	context->IASetInputLayout(input_layout);
//	context->OMSetDepthStencilState(depth_stencil_state, 1);
//	context->RSSetState(rasterizer_state);
//	context->VSSetShader(vertex_shader, nullptr, 0);
//	context->PSSetShader(pixel_shader, nullptr, 0);
//	context->PSSetShaderResources(0, 1, &shader_resource_view);
//	context->PSSetSamplers(0, 1, &sampler_state);
//
//	UINT num_viewports = 1;
//	context->RSGetViewports(&num_viewports, &viewport);
//
//	D3D11_MAP map = D3D11_MAP_WRITE_DISCARD;
//	D3D11_MAPPED_SUBRESOURCE mapped_buffer;
//
//	hr = context->Map(instance_buffer, 0, map, 0, &mapped_buffer);
//	_ASSERT_EXPR(SUCCEEDED(hr), HrTrace(hr));
//	instances = static_cast<instance*>(mapped_buffer.pData);
//
//	count_instance = 0;
//}
//
//void SpriteBatch::render(ID3D11DeviceContext* context, float dx, float dy, float dw, float dh, float sx, float sy, float sw, float sh, float angle/*degree*/, float r, float g, float b, float a)
//{
//	_ASSERT_EXPR(count_instance < MAX_INSTANCES, L"Number of instances must be less than MAX_INSTANCES.");
//
//	float cx = dw * 0.5f, cy = dh * 0.5f; /*Center of Rotation*/
//
//	FLOAT c = cosf(angle * 0.01745f);
//	FLOAT s = sinf(angle * 0.01745f);
//	FLOAT w = 2.0f / viewport.Width;
//	FLOAT h = -2.0f / viewport.Height;
//	instances[count_instance].ndc_transform._11 = w * dw * c;
//	instances[count_instance].ndc_transform._21 = h * dw * s;
//	instances[count_instance].ndc_transform._31 = 0.0f;
//	instances[count_instance].ndc_transform._41 = 0.0f;
//	instances[count_instance].ndc_transform._12 = w * dh * -s;
//	instances[count_instance].ndc_transform._22 = h * dh * c;
//	instances[count_instance].ndc_transform._32 = 0.0f;
//	instances[count_instance].ndc_transform._42 = 0.0f;
//	instances[count_instance].ndc_transform._13 = 0.0f;
//	instances[count_instance].ndc_transform._23 = 0.0f;
//	instances[count_instance].ndc_transform._33 = 1.0f;
//	instances[count_instance].ndc_transform._43 = 0.0f;
//	instances[count_instance].ndc_transform._14 = w * (-cx * c + -cy * -s + cx + dx) - 1.0f;
//	instances[count_instance].ndc_transform._24 = h * (-cx * s + -cy * c + cy + dy) + 1.0f;
//	instances[count_instance].ndc_transform._34 = 0.0f;
//	instances[count_instance].ndc_transform._44 = 1.0f;
//
//	float tw = static_cast<float>(texture2d_desc->Width);
//	float th = static_cast<float>(texture2d_desc->Height);
//	instances[count_instance].texcoord_transform = DirectX::XMFLOAT4(sx / tw, sy / th, sw / tw, sh / th);
//	instances[count_instance].color = DirectX::XMFLOAT4(r, g, b, a);
//
//	count_instance++;
//
//}
//
//void SpriteBatch::end(ID3D11DeviceContext* context)
//{
//	context->Unmap(instance_buffer, 0);
//
//	context->DrawInstanced(4, count_instance, 0, 0);
//}
