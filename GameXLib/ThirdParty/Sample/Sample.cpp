#pragma region Framework
//#include "Framework.h"
//#include "Graphics.h"
//#include "ImGuiFunction.h"
//#include <sstream>
//
//#include "../Library/Math/ViewProjection.h"
//#include "Objects\SkinnedMesh.h"
//
//void Framework::Run()
//{
//	// DX11�̏�����
//	graphics.Initialize(hwnd);
//	// ImGui�̏�����
//#ifdef USE_IMGUI
//	ImGuiFunction::Initialize(hwnd, graphics.device.Get(), graphics.immediate_context.Get());
//#endif
//
//	// �J����
//	View view;
//	view.Set(
//		{ 10.0f, 2.0f, -10.0f },
//		{ 0.0f, 0.0f, 0.0f },
//		{ 0.0f, 1.0f, 0.0f });
//	Projection projection;
//	float aspect_ratio{ graphics.viewport.Width / graphics.viewport.Height };
//	projection.SetPerspective(DirectX::XMConvertToRadians(30), aspect_ratio, 0.1f, 1000.0f);
//
//	// ���b�V��
//	SkinnedMesh SkinnedMesh(graphics.device.Get(),"Assets/MNK_Mesh.fbx");
//
//	// ��������Q�[�����[�v
//	while (DispatchWindowMessage())
//	{
//		// 1�t���[��
//		high_resolution_timer.Tick();
//		CalculateFrameStats();
//
//
//#ifdef USE_IMGUI
//		ImGuiFunction::NewFrame();
//#endif
//
//#ifdef USE_IMGUI
//		ImGui::Begin("Framework");
//		ImGui::End();
//#endif
//		
//		
//
//
//
//
//
//
//
//
//		// �`�揈��
//#ifdef USE_IMGUI
//		ImGuiFunction::Render();
//#endif
//
//
//		// �`�揀��
//		graphics.BeginRender();
//
//
//
//		graphics.EndRender();
//	}
//
//	// �O���t�B�b�N�̏I������
//	ImGuiFunction::Uninitialize();
//	graphics.UnInitialize();
//}
//
//LRESULT CALLBACK Framework::HandleMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//#ifdef USE_IMGUI
//	ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
//#endif
//
//	switch (msg)
//	{
//	case WM_PAINT:
//	{
//		PAINTSTRUCT ps{};
//		BeginPaint(hwnd, &ps);
//
//		EndPaint(hwnd, &ps);
//	}
//	break;
//
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	case WM_CREATE:
//		break;
//	case WM_KEYDOWN:
//		if (wparam == VK_ESCAPE)
//		{
//			PostMessage(hwnd, WM_CLOSE, 0, 0);
//		}
//		break;
//	case WM_ENTERSIZEMOVE:
//		high_resolution_timer.Stop();
//		break;
//	case WM_EXITSIZEMOVE:
//		high_resolution_timer.Start();
//		break;
//	default:
//		return DefWindowProc(hwnd, msg, wparam, lparam);
//	}
//	return 0;
//}
//
////�E�B���h�E���b�Z�[�W���f�B�X�p�b�`�Bfalse���Ԃ��Ă�����A�Q�[���I���B
//bool Framework::DispatchWindowMessage()
//{
//	MSG msg = { 0 };
//	while (WM_QUIT != msg.message) {
//		//�E�B���h�E����̃��b�Z�[�W���󂯎��B
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//		else {
//			//�E�B���h�E���b�Z�[�W����ɂȂ����B
//			break;
//		}
//	}
//	return msg.message != WM_QUIT;
//}
//
//void Framework::CalculateFrameStats()
//{
//	// CalculateFrameStats �t���[�����[�g�v�Z
//	// 1�b������̕��ς̃t���[�������v�Z���A
//	// �����̌��ʂ̓E�B���h�E�̃L���v�V�����o�[�ɒǉ�����܂��B
//	// 1�t���[���������_�����O����̂ɂ����镽�ώ��Ԃ��Z�o���܂��B
//	static int frames = 0;
//	static float time_tlapsed = 0.0f;
//
//	// 1�b�Ԃ�FPS���Z�o
//	if ((++frames, high_resolution_timer.TimeStamp() - time_tlapsed) >= 1.0f)
//	{
//		float fps = static_cast<float>(frames); // fps = frameCnt / 1
//		float mspf = 1000.0f / fps;
//		std::ostringstream outs;
//		outs.precision(6);
//		outs << "FPS : " << fps << " / " << "Frame Time : " << mspf << " (ms)";
//		SetWindowTextA(hwnd, outs.str().c_str());
//
//		// ���̕��ςɃ��Z�b�g���܂��B
//		frames = 0;
//		time_tlapsed += 1.0f;
//	}
//}
#pragma endregion
