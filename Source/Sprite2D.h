#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

/// <summary>
/// 2D
/// </summary>
class Sprite2D
{
private:
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* inputLayout;
	ID3D11Buffer* vertexBuffer;

	ID3D11RasterizerState* rasterizer_state;
	ID3D11ShaderResourceView* shader_resource_view;
	ID3D11ShaderResourceView* normal_shader_resource_view;
	D3D11_TEXTURE2D_DESC* texture2d_desc;
	D3D11_TEXTURE2D_DESC* normal_texture2d_desc;
	ID3D11SamplerState* sampler_state;
	ID3D11DepthStencilState* depth_stencil_state;

	struct vertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT2 texcoord;
		DirectX::XMFLOAT3 light_direction;
	};
public:
	Sprite2D(ID3D11Device*, const wchar_t* texture_file_name, const wchar_t* normal_texture_name);
	void Render(ID3D11DeviceContext*,
		float dx, float dy,//Coordinate of sprite's left-top corner in screen space 
		float dw, float dh,//  Size of sprite in screen space  
		float sx, float sy, // sx, sy : Coordinate of sprite's left-top corner in texture space    
		float sw, float sh,  // sw, sh : Size of sprite in texture space 
		float angle, // Raotation angle(Rotation centre is sprite's centre), Unit is degree 
		float r, float g, float b, float a // Color of sprite's each vertices  
		, DirectX::XMFLOAT3 light = { 0.0f, 0.0f,-1.0f }/*{ -1.0f, -0.3f, -1.0f }*/
	);
};


//class SpriteBatch
//{
//private:
//	ID3D11VertexShader* vertex_shader;
//	ID3D11PixelShader* pixel_shader;
//	ID3D11InputLayout* input_layout;
//	ID3D11Buffer* vertex_buffer;
//	ID3D11RasterizerState* rasterizer_state;
//	ID3D11ShaderResourceView* shader_resource_view;
//	D3D11_TEXTURE2D_DESC* texture2d_desc;
//	ID3D11SamplerState* sampler_state;
//	ID3D11DepthStencilState* depth_stencil_state;
//
//	const size_t MAX_INSTANCES = 256;
//	struct instance
//	{
//		DirectX::XMFLOAT4X4 ndc_transform;
//		DirectX::XMFLOAT4 texcoord_transform;
//		DirectX::XMFLOAT4 color;
//	};
//
//	ID3D11Buffer* instance_buffer;
//public:
//	struct vertex
//	{
//		DirectX::XMFLOAT3 position;
//		DirectX::XMFLOAT2 texcoord;
//	};
//
//	SpriteBatch(ID3D11Device* device, const wchar_t* file_name, size_t max_instance = 256);
//
//	void begin(ID3D11DeviceContext* context);
//	void render(ID3D11DeviceContext* context, float dx, float dy, float dw, float dh, float sx, float sy, float sw, float sh, float angle/*degree*/, float r, float g, float b, float a);
//	void end(ID3D11DeviceContext* context);
//private:
//	D3D11_VIEWPORT viewport;
//
//	UINT count_instance = 0;
//	instance* instances = nullptr;
//};
