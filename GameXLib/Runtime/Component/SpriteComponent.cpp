#include "SpriteComponent.h"
#include <DirectXMath.h>
#include <cstdio>
#include <memory>

// 頂点
struct Vertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT2 texcoord;
	DirectX::XMFLOAT3 lightDirection;
};

// 入力レイアウト
D3D11_INPUT_ELEMENT_DESC layout[] =
{
	{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
	{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
	{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
	{"LIGHT",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
};

// CSOファイル読み込み関数
bool LoadCSOFile(
	ID3D11Device *device,
    const char* csoVsName,
	const char* csoPsName,
    ID3D11VertexShader **vertexShader,
	ID3D11InputLayout **inputLayout,
	ID3D11PixelShader **pixelShader)
{
	FILE* fp = nullptr;
	errno_t error;
	error = fopen_s(&fp,csoVsName,"rb");
	if(error != 0)
	{
		assert("CSO File not found");
	}

	fseek(fp,0,SEEK_END);
	long csoSZ= ftell(fp);
	fseek(fp,0,SEEK_SET);

	std::unique_ptr<unsigned char[]> csoData = std::make_unique<unsigned char[]>(csoSZ);
	fread(csoData.get(),csoSZ,1,fp);
	fclose(fp);

	HRESULT hr = device->CreateVertexShader(csoData.get(),csoSZ,nullptr,vertexShader);
	assert(SUCCEEDED(hr));

	UINT numElement = ARRAYSIZE(layout);
	hr = device->CreateInputLayout(layout,numElement,csoData.get(),csoSZ,inputLayout);
	assert(SUCCEEDED(hr));

	fp = nullptr;
	error = fopen_s(&fp,csoPsName,"rb");
	if(error != 0)
	{
		assert("CSO File not found");
	}

	fseek(fp,0,SEEK_END);
	long csoSZ= ftell(fp);
	fseek(fp,0,SEEK_SET);

	csoData = std::make_unique<unsigned char[]>(csoSZ);
	fread(csoData.get(),csoSZ,1,fp);
	fclose(fp);

	HRESULT hr = device->CreatePixelShader(csoData.get(),csoSZ,nullptr,pixelShader);
	assert(SUCCEEDED(hr));

	return true;
}


SpriteComponent::SpriteComponent(ID3D11Device* device, const wchar_t* textureFileName)
{
	Vertex vertices[] =
	{
		{DirectX::XMFLOAT3(-0.5,+0.5,0),DirectX::XMFLOAT4(1,1,1,1)},
		{DirectX::XMFLOAT3(+0.5,+0.5,0),DirectX::XMFLOAT4(1,0,0,1)},
		{DirectX::XMFLOAT3(-0.5,-0.5,0),DirectX::XMFLOAT4(0,1,0,1)},
		{DirectX::XMFLOAT3(+0.5,-0.5,0),DirectX::XMFLOAT4(0,0,1,1)},
	};

	HRESULT	hr;

	// 頂点バッファ作成
	D3D11_BUFFER_DESC bd = {};
	// ZeroMemory(&bd, sizeof(bd));
	// D3D11_USAGE_DEFAULT; //GPU (読み取り専用) と CPU (書き込み専用) の両方からアクセス可能
	bd.Usage = D3D11_USAGE_DYNAMIC;
	// 又は sizeof(Vertex) * 4
	bd.ByteWidth = sizeof(vertices);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// 0;CPU アクセスが必要ない場合は 0 //CPU がその内容を変更できる
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// サブリソース
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData,sizeof(InitData));
	InitData.pSysMem = vertices;

	hr = device->CreateBuffer(&bd,&InitData,&vertexBuffer);
	if(FAILED(hr))
	{
		assert(0 && "頂点バッファ作成失敗");
	}

	
}

void SpriteComponent::Render()
{
	// 描画位置
	// サイズ
	// テクスチャ位置
	// テクスチャサイズ
	// 中心地
	// 回転
	// 色



	float x,y;//描画位置
	float dw,float dh;
	float sx,float sy;//テクスチャの位置
	float sw,float sh;// テクスチャの範囲

	float angle;
	DirectX::XMFLOAT3 L;
	DirectX::XMFLOAT4 col;

	Vertex vertices[] = {
		{{x,y,.0f},col,{sx,sy},L},
		{{x + dw,y,.0f},col,{sx + sw,sy},L},
		{{x,y + dh,.0f},col,{sx,sy + sh},L},
		{{x + dw,y + dh,.0f},col,{sx + sw,sy + sh},L},
	};

	for(int n = 0; n < 4; n++)
	{
		vertices[n].position.x = (vertices[n].position.x - x - dw /2) * cos(DirectX::XMConvertToRadians(angle)) - (vertices[n].position.y - y - dh /2)* sin(DirectX::XMConvertToRadians(angle)) + x + dw / 2;
		vertices[n].position.y = (vertices[n].position.x - x - dw /2) * sin(DirectX::XMConvertToRadians(angle)) + (vertices[n].position.y - y - dh /2) * cos(DirectX::XMConvertToRadians(angle)) + y + dh / 2;


	}
}