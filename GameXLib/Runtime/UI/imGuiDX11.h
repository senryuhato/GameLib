#pragma once
#include <Windows.h>
#include <DirectXMath.h>
#include "../../ThirdParty/ImGui/imgui-docking/imgui.h"
#include "../../ThirdParty/ImGui/imgui-docking/imgui_internal.h"
#include "../../ThirdParty/ImGui/imgui-docking/imgui_impl_dx11.h"
#include "../../ThirdParty/ImGui/imgui-docking/imgui_impl_win32.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
