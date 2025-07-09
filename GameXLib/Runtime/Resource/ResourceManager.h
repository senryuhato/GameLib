#pragma once
#include <d3d11.h>
#include <map>
#include <string>
#include <wrl\client.h>

/// @brief リソースマネージャー
class ResourceManager
{
public:
	/// @brief 画像データ読み込み
	/// @param device デバイス
	/// @param filename ファイル名
	/// @param shaderResourceView シェーダーリソースビュー
	void LoadTextureFromFile(ID3D11Device* device, const wchar_t* filename, ID3D11ShaderResourceView** shaderResourceView);

private:
	// 画像リソース
	std::map<std::wstring, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> textures;
};
