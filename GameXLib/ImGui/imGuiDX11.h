#pragma once
#include "imgui-docking/imgui.h"
#include "imgui-docking/imgui_internal.h"
#include "imgui-docking/imgui_impl_dx11.h"
#include "imgui-docking/imgui_impl_win32.h"

#include <windows.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#include <DirectXMath.h>

// 4D Vector
struct ImXMFloat4
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		float m[4];
		DirectX::XMFLOAT4 xm;
	};

	ImXMFloat4() = default;

	ImXMFloat4(const ImXMFloat4&) = default;
	ImXMFloat4& operator=(const ImXMFloat4&) = default;

	ImXMFloat4(ImXMFloat4&&) = default;
	ImXMFloat4& operator=(ImXMFloat4&&) = default;

	ImXMFloat4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	ImXMFloat4(DirectX::XMFLOAT4& m) : x(m.x), y(m.y), z(m.z), w(m.w) {}
};

// 3D Vector
struct ImXMFloat3
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float m[3];
		DirectX::XMFLOAT3 xm;
	};

	ImXMFloat3() = default;

	ImXMFloat3(const ImXMFloat3&) = default;
	ImXMFloat3& operator=(const ImXMFloat3&) = default;

	ImXMFloat3(ImXMFloat3&&) = default;
	ImXMFloat3& operator=(ImXMFloat3&&) = default;

	ImXMFloat3(float x, float y, float z) : x(x), y(y), z(z) {}
	ImXMFloat3(DirectX::XMFLOAT3& m) : x(m.x), y(m.y), z(m.z) {}
};

inline void ImGuiDrawTextFloat4x4(DirectX::XMFLOAT4X4& xm)
{
	ImGui::Text("%f,%f,%f,%f,", xm._11, xm._12, xm._13, xm._14);
	ImGui::Text("%f,%f,%f,%f,", xm._21, xm._22, xm._23, xm._24);
	ImGui::Text("%f,%f,%f,%f,", xm._31, xm._32, xm._33, xm._34);
	ImGui::Text("%f,%f,%f,%f,", xm._41, xm._42, xm._43, xm._44);
}