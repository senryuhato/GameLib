#include "../../ThirdParty/DirectXTex/WICTextureLoader11.h"
#include "../System/Misc.h"
#include "ResourceManager.h"

#pragma region 画像データ読み込み
/// <summary>
/// 画像データ読み込み
/// </summary>
/// <param name="device">デバイス</param>
/// <param name="filename">ファイル名</param>
/// <param name="shaderResourceView">シェーダーリソースビュー</param>
void ResourceManager::LoadTextureFromFile(ID3D11Device* device, const wchar_t* filename, ID3D11ShaderResourceView** shaderResourceView)
{
	HRESULT hr = S_OK;
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;

	// 画像リソース検索
	std::map<std::wstring,Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>::iterator it = textures.find(filename);
	if (it != textures.end())
	{
		// 画像リソース取得
		shaderResourceView = it->second.GetAddressOf();
	}
	else
	{
		// 画像読み込み
		hr = DirectX::CreateWICTextureFromFile(device, filename, resource.GetAddressOf(), shaderResourceView);
		_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
		// 画像リソース登録
		textures.insert(std::make_pair(filename, *shaderResourceView));
	}
}
#pragma endregion

