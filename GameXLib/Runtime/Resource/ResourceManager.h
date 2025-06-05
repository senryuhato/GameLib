#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <map>
#include <string>

/// <summary>
/// リソースマネージャー
/// </summary>
class ResourceManager
{
public:
	/// <summary>
	/// 画像データ読み込み
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="filename">ファイル名</param>
	/// <param name="shaderResourceView">シェーダーリソースビュー</param>
	void LoadTextureFromFile(ID3D11Device* device, const wchar_t* filename, ID3D11ShaderResourceView** shaderResourceView);

private:
	/// <summary>
	/// 画像リソース
	/// </summary>
	std::map<std::wstring, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> textures;
};
