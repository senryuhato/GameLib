#pragma once

#include	<d3d11.h>

class ResourceManager
{
private:
	static const int RESOURCE_MAX = 128;

	struct ShaderResourceViewData
	{
		wchar_t						filename[256];
		ID3D11ShaderResourceView* shader_resource_view;
		D3D11_TEXTURE2D_DESC		texDesc;
		int							count;

		ShaderResourceViewData() : shader_resource_view(nullptr), count(0)
		{
			ZeroMemory(filename, sizeof(filename));
		}

		void Release(bool bForce = false)
		{
			if (count <= 0)	return;
			if (--count <= 0)	bForce = true;
			if (bForce)
			{
				shader_resource_view->Release();
				ZeroMemory(this, sizeof(ShaderResourceViewData));	//	”O‚Ìˆ×‚ÉŠ®‘SÁ‹‚µ‚Ü‚·
			}
		}
	};

	struct VertexShadersData
	{
		char						filename[256];
		ID3D11VertexShader* vertex_shader;
		ID3D11InputLayout* input_layout;
		int							count;

		VertexShadersData() : vertex_shader(nullptr), input_layout(nullptr), count(0)
		{
			ZeroMemory(filename, sizeof(filename));
		}

		void Release(bool bForce = false)
		{
			if (count <= 0)	return;
			if (--count <= 0)	bForce = true;
			if (bForce)
			{
				vertex_shader->Release();
				input_layout->Release();
				ZeroMemory(this, sizeof(VertexShadersData));	//	”O‚Ìˆ×‚ÉŠ®‘SÁ‹‚µ‚Ü‚·
			}
		}

	};

	struct PixelShadersData
	{
		char						filename[256];
		ID3D11PixelShader* pixel_shader;
		int							count;

		PixelShadersData() : pixel_shader(nullptr), count(0)
		{
			ZeroMemory(filename, sizeof(filename));
		}
		void Release(bool bForce = false)
		{
			if (count <= 0)	return;
			if (--count <= 0)	bForce = true;
			if (bForce)
			{
				pixel_shader->Release();
				ZeroMemory(this, sizeof(PixelShadersData));	//	”O‚Ìˆ×‚ÉŠ®‘SÁ‹‚µ‚Ü‚·
			}
		}
	};

	static ShaderResourceViewData	srvData[RESOURCE_MAX];
	static VertexShadersData		vsData[RESOURCE_MAX];
	static PixelShadersData			psData[RESOURCE_MAX];


	ResourceManager() {}
	~ResourceManager() { Release(); }

public:
	static void Release()
	{
		for (int n = 0; n < RESOURCE_MAX; n++)
		{
			srvData[n].Release(true);
			vsData[n].Release(true);
			psData[n].Release(true);
		}
	}

	static bool LoadShaderResourceView(ID3D11Device* device, const wchar_t* filename,
		ID3D11ShaderResourceView** srv, D3D11_TEXTURE2D_DESC** texDesc);

	static void ReleaseShaderResourceView(ID3D11ShaderResourceView* srv);


	static bool LoadVertexShaders(ID3D11Device* device, const char* filename,
		D3D11_INPUT_ELEMENT_DESC* elementDescs, int numElement,
		ID3D11VertexShader** vs, ID3D11InputLayout** il);

	static void ReleaseVertexShaders(ID3D11VertexShader* vs, ID3D11InputLayout* il);


	static bool LoadPixelShaders(ID3D11Device* device, const char* filename, ID3D11PixelShader** ps);
	static void ReleasePixelShaders(ID3D11PixelShader* ps);

};
