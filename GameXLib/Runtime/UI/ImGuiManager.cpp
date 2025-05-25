#include "imGuiDX11.h"
#include "ImGuiManager.h"

#pragma region ImGui �̏���������
/// <summary>
/// ImGui �̏���������
/// </summary>
/// <param name="hwnd">�E�B���h�E�n���h��</param>
/// <param name="device">DirectX 11 �f�o�C�X</param>
/// <param name="immediateContext">DirectX 11 �f�o�C�X�R���e�L�X�g</param>
/// <return>����</return>
bool ImGuiManager::Initialize(
	HWND hwnd, 
	ID3D11Device* device, 
	ID3D11DeviceContext* immediateContext)
{
	if (initialized) Uninitialize();
	initialized = true;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	//io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Consola.ttf", 14.0f, nullptr, io.Fonts->GetGlyphRangesJapanese()); // Font�ݒ�
	io.Fonts->AddFontFromFileTTF("Resources\\System\\Fonts\\ipag.ttf", 12.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());// Font�ݒ�

#if 1 // �h�b�L���O																												 
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
#endif
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	bool isResult = ImGui_ImplWin32_Init(hwnd);
	if (isResult)
	{
		isResult = ImGui_ImplDX11_Init(device, immediateContext);
	}
	if (!isResult)
	{
		return false;
	}
	ImGui::StyleColorsDark();
	return true;
}
#pragma endregion

#pragma region ImGui �̏I������
/// <summary>
/// ImGui �̏I������
/// </summary>
void ImGuiManager::Uninitialize()
{
	if (!initialized) return;
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	initialized = false;
}
#pragma endregion

#pragma region Imgui�̑S�ʏ���
/// <summary>
/// Imgui�̑S�ʏ���
/// </summary>
void ImGuiManager::RenderImGuiFrame()
{
	if (!initialized) return;
	// �`�揀��
	NewFrame();
	// ImGui�\������
	for(auto& func : drawFunctions)
	{
		// �֐��|�C���^���s
		func();
	}
	// �`�揈��
	Render();
	// �N���A����
	drawFunctions.clear();
}
#pragma endregion

#pragma region ImGui�̃E�B���h�E���b�Z�[�W���������郁���o�֐�
/// <summary>
/// ImGui�̃E�B���h�E���b�Z�[�W���������郁���o�֐�
/// </summary>
/// <param name="hwnd">�E�B���h�E�n���h��</param>
/// <param name="msg">�󂯎�������b�Z�[�W</param>
/// <param name="wParam">���b�Z�[�W�̒ǉ����i1�ڂ̃p�����[�^�j</param>
/// <param name="lParam">���b�Z�[�W�̒ǉ����i2�ڂ̃p�����[�^�j</param>
/// <returns>���b�Z�[�W�������������ʁi�ʏ�� `DefWindowProc` �̖߂�l��Ԃ��j</returns>
LRESULT ImGuiManager::WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (!initialized) return 0;
	return ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
}
#pragma endregion

#pragma region �V�����t���[���̊J�n
/// <summary>
/// �V�����t���[���̊J�n
/// </summary>
void ImGuiManager::NewFrame()
{
	// ���݂̏󋵂��ƃE�B���h�E�T�C�Y��ύX�����Ƃ��ʒu�������
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}
#pragma endregion

#pragma region ImGui �̕`�揈��
/// <summary>
/// ImGui �̕`�揈��
/// </summary>
void ImGuiManager::Render()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}
#pragma endregion