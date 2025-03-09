#pragma once
#include <DirectXMath.h>

class View
{
public:
	// セット
	void Set(DirectX::XMFLOAT3 eye, DirectX::XMFLOAT3 focus, DirectX::XMFLOAT3 up)
	{
		this->eye = eye;
		this->focus = focus;
		this->up = up;
		UpdateMatrix();
	}
	// 更新
	void UpdateMatrix()
	{
		Cheak();
		DirectX::XMStoreFloat4x4(&matrix, DirectX::XMMatrixLookAtLH(
			DirectX::XMLoadFloat3(&this->eye),
			DirectX::XMLoadFloat3(&this->focus),
			DirectX::XMLoadFloat3(&this->up)));
	}

public:
	DirectX::XMFLOAT3 eye{ 0.0f,0.0f, 10.0f }; // 位置
	DirectX::XMFLOAT3 focus{ 0.0f,0.0f,0.0f }; // 焦点
	DirectX::XMFLOAT3 up{ 0.0f,1.0f,0.0f }; // 上ベクトル

	template<class T>
	void serialize(T& archive)
	{
		archive(eye, focus, up);
	}

	DirectX::XMFLOAT4X4 matrix{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }; // 行列

private:
	void Cheak() { if (eye.x == focus.x && eye.y == focus.y && eye.z == focus.z) eye.z += 0.0001f; }
};

// 投影
class Projection
{
public:
	// 透視投影
	void SetPerspective(float fov, float aspect, float near_plane, float fur_plane)
	{
		DirectX::XMMATRIX new_matrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, near_plane, fur_plane);
		DirectX::XMStoreFloat4x4(&matrix, new_matrix);
	}

	// 正投影
	void SetOrthographic(float width, float height, float near_plane, float fur_plane)
	{
		DirectX::XMMATRIX new_matrix = DirectX::XMMatrixOrthographicLH(width, height, near_plane, fur_plane);
		DirectX::XMStoreFloat4x4(&matrix, new_matrix);
	}

public:
	DirectX::XMFLOAT4X4 matrix{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }; // 行列

	template<class T>
	void serialize(T& archive)
	{
		archive(matrix);
	}
};

// 透視投影
class PerspectiveProjection : public Projection
{
public:
	union
	{
		struct
		{
			float fov; // 視野角
			float aspect; // 縦横比
			float near_plane; // ニアクリップ面
			float fur_plane; // ファークリップ面
		};
		DirectX::XMFLOAT4 xm{};
	};

	union ProjectionData
	{
		struct
		{
			float fov;        // 視野角
			float aspect;     // 縦横比
			float near_plane; // ニアクリップ面
			float fur_plane;  // ファークリップ面
		};
		DirectX::XMFLOAT4 xm;

		ProjectionData() : fov(0.0f), aspect(0.0f), near_plane(0.0f), fur_plane(0.0f) {}
		ProjectionData(float fov, float aspect, float near_plane, float fur_plane) : fov(fov), aspect(aspect), near_plane(near_plane), fur_plane(fur_plane) {}
		ProjectionData(const DirectX::XMFLOAT4& m) : xm(m) {}
	} projection_data;

	PerspectiveProjection() : projection_data() {}
	PerspectiveProjection(float fov, float aspect, float near_plane, float fur_plane) : projection_data(fov, aspect, near_plane, fur_plane) {}
	PerspectiveProjection(const DirectX::XMFLOAT4& m) : projection_data(m) {}

	DirectX::XMFLOAT4X4 projection_matrix{}; // 行列
	void UpdateMatrix()
	{
		DirectX::XMMATRIX matrix = DirectX::XMMatrixPerspectiveFovLH(projection_data.fov, projection_data.aspect, projection_data.near_plane, projection_data.fur_plane);
		DirectX::XMStoreFloat4x4(&projection_matrix, matrix);
	}
	void Set(float fov, float aspect, float near_plane, float fur_plane)
	{
		this->projection_data.fov = fov;
		this->projection_data.aspect = aspect;
		this->projection_data.near_plane = near_plane;
		this->projection_data.fur_plane = fur_plane;
		UpdateMatrix();
	}
	void Set(DirectX::XMFLOAT4& xm)
	{
		projection_data.fov = xm.x;
		projection_data.aspect = xm.y;
		projection_data.near_plane = xm.z;
		projection_data.fur_plane = xm.w;
		UpdateMatrix();
	}
};

// 正投影
class OrthographicProjection : public Projection
{
public:
	union ProjectionUnion
	{
		struct
		{
			float width;      // 横
			float height;     // 縦
			float near_plane; // ニアクリップ面
			float fur_plane;  // ファークリップ面
		};
		DirectX::XMFLOAT4 xm;

		ProjectionUnion() : width(0.0f), height(0.0f), near_plane(0.0f), fur_plane(0.0f) {}
		ProjectionUnion(float x, float y, float z, float w) : width(x), height(y), near_plane(z), fur_plane(w) {}
		ProjectionUnion(const DirectX::XMFLOAT4& m) : xm(m) {}
	} projection_data;


	OrthographicProjection() : projection_data() {}
	OrthographicProjection(float x, float y, float z, float w) : projection_data(x, y, z, w) {}
	OrthographicProjection(const DirectX::XMFLOAT4& m) : projection_data(m) {}

	DirectX::XMFLOAT4X4 projection_matrix{}; // 行列

	void UpdateMatrix()
	{
		DirectX::XMMATRIX matrix = DirectX::XMMatrixOrthographicLH(projection_data.width, projection_data.height, projection_data.near_plane, projection_data.fur_plane);
		DirectX::XMStoreFloat4x4(&projection_matrix, matrix);

	}
	void Set(float width, float height, float near_plane, float fur_plane)
	{
		this->projection_data.width = width;
		this->projection_data.height = height;
		this->projection_data.near_plane = near_plane;
		this->projection_data.fur_plane = fur_plane;
		UpdateMatrix();
	}
	void Set(DirectX::XMFLOAT4& xm)
	{
		projection_data.width = xm.x;
		projection_data.height = xm.y;
		projection_data.near_plane = xm.z;
		projection_data.fur_plane = xm.w;
		UpdateMatrix();
	}
};
