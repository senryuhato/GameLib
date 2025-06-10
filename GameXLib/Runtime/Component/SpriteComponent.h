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
	void Render();

public:
	// 位置
	DirectX::XMFLOAT2 position;
	// スケール
	DirectX::XMFLOAT2 scale;
	// 画像位置
	DirectX::XMFLOAT2 texturePosition;
	// 画像サイズ
	DirectX::XMFLOAT2 textureSize;
	// 中心点
	DirectX::XMFLOAT2 center;
	// 回転
	float angle;
	// 色
	DirectX::XMFLOAT4 color;

private:
	// 頂点バッファ
	ID3D11Buffer* vertexBuffer;
};
