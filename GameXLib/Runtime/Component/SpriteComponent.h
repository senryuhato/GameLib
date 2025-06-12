#pragma once
#include <d3d11.h>

/// @brief 2D描画
class SpriteComponent
{
public:
	/// @brief コンストラクタ データ読み込み
	/// @param device デバイス
	/// @param textureFileName 読み込みファイル
	SpriteComponent(ID3D11Device* device, const wchar_t* textureFileName);

	/// @brief 描画処理
	/// @param position 位置
	/// @param scale スケール
	/// @param texturePosition 画像位置
	/// @param textureSize 画像サイズ
	/// @param center 中心点
	/// @param angle 回転
	/// @param color 色
	void Render(
		const DirectX::XMFLOAT2& position,
		const DirectX::XMFLOAT2& scale,
		const DirectX::XMFLOAT2& texturePosition,
		const DirectX::XMFLOAT2& textureSize,
		const DirectX::XMFLOAT2& center,
		float angle,
		const DirectX::XMFLOAT4& color);

private:
	// 頂点バッファ
	ID3D11Buffer* vertexBuffer;
	// シェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
};
