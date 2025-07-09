#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <wrl\client.h>

// 2D描画
class Sprite
{
public:
	/// @brief コンストラクタ テクスチャロード
	/// @param device デバイス
	/// @param textureFileName　ファイル名 
	Sprite(ID3D11Device* device,const wchar_t* textureFileName);
public:
	// 頂点構造体
	struct Vertex
	{
		// 頂点位置
		DirectX::XMFLOAT3 position;
		// テクスチャ位置
		DirectX::XMFLOAT2 texcoord;


	};
	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader = nullptr;
	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader = nullptr;
	// インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout = nullptr;
	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer = nullptr;
	// ラスタライザーステート
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState = nullptr;
	// シェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView = nullptr;
	// テクスチャデスク
	//Microsoft::WRL::ComPtr<D3D11_TEXTURE2D_DESC> texture2dDesc = nullptr;
	// サンプラーステート
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState = nullptr;
	// デプスステンシルステート
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState = nullptr;

private:
	/// @brief ステートの作成
	/// @param device デバイス 
	void CreateState(ID3D11Device* device);
};
