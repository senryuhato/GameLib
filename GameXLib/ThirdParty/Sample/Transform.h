#pragma once
#include <DirectXMath.h>

class Transform
{
public:
	DirectX::XMFLOAT3 position = { 0 ,0,0 };
	DirectX::XMFLOAT4 rotation = { 0.0f, 0.0f, 0.0f, 1.0f };
	DirectX::XMFLOAT3 scale = { 1.0f, 1.0f, 1.0f };

	template<class T>
	void serialize(T& archive)
	{
		archive(
			CEREAL_NVP(position),
			CEREAL_NVP(rotation),
			CEREAL_NVP(scale));
	}

	DirectX::XMFLOAT4X4 world = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	DirectX::XMFLOAT4X4 local_world = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	Transform* parent = nullptr;

public:
	// ˆÊ’uXV
	void calculate_world_transform_quaternion()
	{
		DirectX::XMMATRIX S, R, T, W;
		S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
		R = DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(&rotation));
		T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		W = S * R * T;

		DirectX::XMStoreFloat4x4(&local_world, W);
		DirectX::XMStoreFloat4x4(&world, W * DirectX::XMLoadFloat4x4(&parent->local_world));
	}

	// ‰ñ“]•ÏŠ·
	const DirectX::XMFLOAT4 euler(const DirectX::XMFLOAT3& angle)
	{
		DirectX::XMFLOAT4 quaternion = {};

		DirectX::XMVECTOR axis_x = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), angle.x);
		DirectX::XMVECTOR axis_y = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), angle.y);
		DirectX::XMVECTOR axis_z = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), angle.z);

		DirectX::XMStoreFloat4(&quaternion, DirectX::XMQuaternionMultiply(DirectX::XMQuaternionMultiply(axis_z, axis_x), axis_y));

		return quaternion;
	}
};


