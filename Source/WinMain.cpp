#include <crtdbg.h>
#include <time.h>
#include <sstream>
#include <map>
#include "WinMain.h"
#include "..\GameXLib\Runtime\Scene\Scene.h"
#include "SystemInstance.h"
#include "TitleScene.h"
#include "MainScene.h"

#pragma region �萔
/// <summary>
/// window��
/// </summary>
static const LPCWSTR CLASS_NAME = L"GameProject";

/// <summary>
/// ���t���b�V�����[�g
/// </summary>
static const UINT DEFAULT_FRAMERATE = 60;

/// <summary>
/// �E�B���h�E��
/// </summary>
static const wchar_t* WINDOW_TITLE = L"�Q�[���v���W�F�N�g";

/// <summary>
/// ��ʕ�
/// </summary>
static const int SCREEN_WIDTH = 1280;

/// <summary>
/// ��ʍ���
/// </summary>
static const int SCREEN_HEIGHT = 720;

/// <summary>
/// �f�t�H���g�t���[�����[�g
/// </summary>
static const int FRAMERATE = 60;

/// <summary>
/// �����t���X�N���[�����[�h
/// </summary>
const BOOL FULSCREEN_MODE = false;

/// <summary>
/// �N���A�J���[
/// </summary>
const FLOAT REFRESH_COLOR[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

/// <summary>
/// ��������(ON)
/// </summary>
const UINT SYNC_INTERVAL_VALID = 1;

/// <summary>
/// ��������(OFF)
/// </summary>
const UINT SYNC_INTERVAL_INVALID = 0;

/// <summary>
/// �^�C�g���V�[���L�[
/// </summary>
static const std::string TITLE_SCENE = "TitleScene";

/// <summary>
/// ���C���V�[���L�[
/// </summary>
static const std::string MAIN_SCENE = "MainScene";
#pragma endregion

#pragma region �ϐ�
/// <summary>
/// �E�B���h�E�n���h��
/// </summary>
HWND hwnd = nullptr;

/// <summary>
/// �t���[�����[�g��\�������邩
/// </summary>
bool isShowFrameRate = true;

/// <summary>
/// �V�X�e���ێ��N���X
/// </summary>
SystemInstance systemInstace;

/// <summary>
/// ���݂̃V�[���̃L�[
/// </summary>
std::string currentSceneKey;

/// <summary>
/// ���̃V�[���̃L�[(�V�[���̕ύX���ȊO��Empty)
/// </summary>
std::string nextSceneKey;

/// <summary>
/// �V�[�����X�g
/// </summary>
std::map<std::string, std::unique_ptr<Scene>> scenes;

/// <summary>
/// ��������
/// </summary>
const UINT syncInterval = SYNC_INTERVAL_VALID;

Microsoft::WRL::ComPtr<ID3D11DepthStencilState> defaultDepthStencilState;
Microsoft::WRL::ComPtr<ID3D11RasterizerState> defaultRasterizerState[2];
Microsoft::WRL::ComPtr<ID3D11BlendState> defaultBlendState;
Microsoft::WRL::ComPtr<ID3D11SamplerState> defaultSamplerState[3];
#pragma endregion

#pragma region C++/CLI Windows �A�v���P�[�V�����̃G���g���|�C���g
/// <summary>
/// C++/CLI �ł� Windows �A�v���P�[�V�����̃G���g���|�C���g�B
/// </summary>
/// <param name="hInstance">���݂̃C���X�^���X�n���h��</param>
/// <param name="hPrevInstance">�ȑO�̃C���X�^���X�n���h���i��� NULL�j</param>
/// <param name="lpCmdLine">�R�}���h���C������</param>
/// <param name="nShowCmd">�E�B���h�E�̕\�����</param>
/// <returns>�v���O�����̏I���R�[�h�i�ʏ�� 0�j</returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// �f�o�b�O���[�h���Ƀ��������[�N���o��L�����B
#if defined(DEBUG) | defined(_DEBUG)
	// `_CRTDBG_ALLOC_MEM_DF` : ���������蓖�Ẵf�o�b�O����L�����B
	// `_CRTDBG_LEAK_CHECK_DF` : �v���O�����I�����Ƀ��������[�N���`�F�b�N�B
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(####);���g�p����ƁA�w�肳�ꂽ�A���P�[�V�����ԍ��Ńu���[�N�\�B
#endif

	// �����̃V�[�h�l��ݒ�B
	srand(static_cast<unsigned int>(time(nullptr)));

	// �E�B���h�E�N���X�̓o�^
	if (RegisterDefaultWindowClass(hInstance, CLASS_NAME, WindowProcedure))
	{
		// �E�B���h�E�̍쐬
		hwnd = CreateDefaultWindow(hInstance, CLASS_NAME, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE);
		if (hwnd)
		{
			// �E�B���h�E�̕\����Ԑݒ�(�\���Ɣ�\��)
			ShowWindow(hwnd, nShowCmd);

			// DirectX11������
			if (systemInstace.graphicsManager.Initialize(hwnd, DEFAULT_FRAMERATE, FULSCREEN_MODE))
			{
				// Imgui������
				systemInstace.imguiManager.Initialize(hwnd, systemInstace.graphicsManager.GetDevice(), systemInstace.graphicsManager.GetDeviceContext());

				// �V�[���o�^
				RegisterSceneIfNotExists<TitleScene>(TITLE_SCENE);
				RegisterSceneIfNotExists<MainScene>(MAIN_SCENE);
				// �ŏ��̃V�[���ݒ�
				LoadScene(TITLE_SCENE);

				// �J�[�\���ݒ�
				SetShowMouseCursor(true);

				// �^�C�}�[���Z�b�g
				systemInstace.highResolutionTimer.Reset();

				//{
				//	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
				//	depth_stencil_desc.DepthEnable = TRUE;
				//	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				//	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
				//	depth_stencil_desc.StencilEnable = FALSE;
				//	depth_stencil_desc.StencilReadMask = 0xFF;
				//	depth_stencil_desc.StencilWriteMask = 0xFF;
				//	depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				//	depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
				//	depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				//	depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
				//	depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				//	depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
				//	depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				//	depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
				//	hr = device->CreateDepthStencilState(&depth_stencil_desc, default_depth_stencil_state.GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
				//}

				//{
				//	D3D11_RASTERIZER_DESC rasterizer_desc = {};
				//	rasterizer_desc.FillMode = D3D11_FILL_SOLID;
				//	rasterizer_desc.CullMode = D3D11_CULL_BACK;
				//	rasterizer_desc.FrontCounterClockwise = FALSE;
				//	rasterizer_desc.DepthBias = 0;
				//	rasterizer_desc.DepthBiasClamp = 0;
				//	rasterizer_desc.SlopeScaledDepthBias = 0;
				//	rasterizer_desc.DepthClipEnable = TRUE;
				//	rasterizer_desc.ScissorEnable = FALSE;
				//	rasterizer_desc.MultisampleEnable = TRUE;
				//	rasterizer_desc.AntialiasedLineEnable = FALSE;
				//	hr = device->CreateRasterizerState(&rasterizer_desc, default_rasterizer_state[0].GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

				//	rasterizer_desc.FrontCounterClockwise = TRUE;
				//	hr = device->CreateRasterizerState(&rasterizer_desc, default_rasterizer_state[1].GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
				//}

				//{
				//	D3D11_BLEND_DESC blend_desc = {};
				//	blend_desc.AlphaToCoverageEnable = FALSE;
				//	blend_desc.IndependentBlendEnable = FALSE;
				//	blend_desc.RenderTarget[0].BlendEnable = TRUE;
				//	blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
				//	blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
				//	blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
				//	blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
				//	blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
				//	blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
				//	blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
				//	hr = device->CreateBlendState(&blend_desc, default_blend_state.GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
				//}

				//{
				//	D3D11_SAMPLER_DESC sampler_desc;
				//	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
				//	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
				//	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
				//	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
				//	sampler_desc.MipLODBias = 0;
				//	sampler_desc.MaxAnisotropy = 16;
				//	sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
				//	sampler_desc.BorderColor[0] = 0.0f;
				//	sampler_desc.BorderColor[1] = 0.0f;
				//	sampler_desc.BorderColor[2] = 0.0f;
				//	sampler_desc.BorderColor[3] = 0.0f;
				//	sampler_desc.MinLOD = 0;
				//	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
				//	hr = device->CreateSamplerState(&sampler_desc, default_sampler_state[0].GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

				//	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				//	hr = device->CreateSamplerState(&sampler_desc, default_sampler_state[1].GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

				//	sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
				//	hr = device->CreateSamplerState(&sampler_desc, default_sampler_state[2].GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
				//}

				//{
				//	D3D11_BUFFER_DESC buffer_desc{};
				//	buffer_desc.ByteWidth = sizeof(scene_constants);
				//	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
				//	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				//	buffer_desc.CPUAccessFlags = 0;
				//	buffer_desc.MiscFlags = 0;
				//	buffer_desc.StructureByteStride = 0;
				//	hr = device->CreateBuffer(&buffer_desc, nullptr, constant_buffers[0].GetAddressOf());
				//	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
				//}




				// �Q�[�����[�v
				while (DispatchWindowMessage())
				{
					// �^�C�}�[�X�V
					systemInstace.highResolutionTimer.Tick();
					// �w�b�_�[��FPS��\�����邩
					if (isShowFrameRate)
					{
						// �w�b�_�[��FPS��\������
						CalculateFrameStats(systemInstace.highResolutionTimer.TimeStamp());
					}
					// �t���[���ԕb��
					float elapsedTime = systemInstace.highResolutionTimer.TimeInterval();
					// 1�t���[��������̍ő�b���w��
					const float limitElapsedTime = 1.0f / 5;
					elapsedTime = elapsedTime > limitElapsedTime ? limitElapsedTime : elapsedTime;

					// �Q�[���X�V
					// �V�[�����ݒ肳��Ă��邩
					if (!currentSceneKey.empty())
					{
						// ���̃V�[�����w�肳��Ă���ꍇ
						if (!nextSceneKey.empty())
						{
							// �V�[���؂�ւ�
							scenes[currentSceneKey]->Uninitializr();
							currentSceneKey = nextSceneKey;
							scenes[nextSceneKey]->Initialize();
						}
						// �V�[���X�V
						scenes[currentSceneKey]->Update();
					}

					// �Q�[���`��
					ID3D11DeviceContext* immediateContext = systemInstace.graphicsManager.GetDeviceContext();
					ID3D11RenderTargetView* renderTargetView = systemInstace.graphicsManager.GetRenderTargetView();
					ID3D11DepthStencilView* depthStencilView = systemInstace.graphicsManager.GetDepthStencilView();
					IDXGISwapChain* swapChain = systemInstace.graphicsManager.GetSwapChain();

					// ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
					immediateContext->ClearRenderTargetView(renderTargetView, REFRESH_COLOR);
					immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
					immediateContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);



					// �Q�[������
					scenes[currentSceneKey]->Render();

					//// UI�\������
					systemInstace.imguiManager.RenderImGuiFrame();

					// �o�b�N�o�b�t�@�ɕ`�悵�������ʂɕ\������B
					swapChain->Present(0, 0);
				}

				// ImGui�I������
				systemInstace.imguiManager.Uninitialize();

				// �`��I������
				systemInstace.graphicsManager.Uninitialize();
			}
			// �E�B���h�E�̍폜
			DestroyWindow(hwnd);
		}
		// �E�B���h�E�N���X�̍폜
		UnregisterClass(CLASS_NAME, hInstance);
	}

	// ����I��
	return 0;
}
#pragma endregion

#pragma region �E�B���h�E���b�Z�[�W����������R�[���o�b�N�֐��iWin32 API �p�j
/// <summary>
/// �E�B���h�E���b�Z�[�W����������R�[���o�b�N�֐��iWin32 API �p�j
/// </summary>
/// <param name="hwnd">�E�B���h�E�n���h��</param>
/// <param name="msg">�󂯎�������b�Z�[�W</param>
/// <param name="wParam">���b�Z�[�W�̒ǉ����i1�ڂ̃p�����[�^�j</param>
/// <param name="lParam">���b�Z�[�W�̒ǉ����i2�ڂ̃p�����[�^�j</param>
/// <returns>���b�Z�[�W�������������ʁi�ʏ�� `DefWindowProc` �̖߂�l��Ԃ��j</returns>
LRESULT CALLBACK WindowProcedure(
	_In_ HWND hwnd,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	// ImGui���͏���
	systemInstace.imguiManager.WndProcHandler(hwnd, msg, wParam, lParam);

	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps{};
		BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostMessage(hwnd, WM_CLOSE, 0, 0);
		}
		break;
	case WM_ENTERSIZEMOVE:
		systemInstace.highResolutionTimer.Stop();
		break;
	case WM_EXITSIZEMOVE:
		systemInstace.highResolutionTimer.Start();
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
	return DefWindowProc(hwnd, msg, wParam, lParam);;
}
#pragma endregion

/// <summary>
/// �V�[���o�^
/// </summary>
/// <typeparam name="T">�o�^����V�[���̌^</typeparam>
/// <param name="registerSceneName">�o�^����V�[����</param>
template<typename T>
void RegisterScene(std::string registerSceneName)
{
	// �N���X����Key�Ƃ��ď㏑���o�^����
	scenes[registerSceneName] = std::make_unique<T>();
}

/// <summary>
/// �V�[���o�^�i���ɓo�^����Ă���ꍇ�͓o�^���Ȃ��j
/// </summary>
/// <typeparam name="T">�o�^����V�[���̌^</typeparam>
/// <param name="registerSceneName">�o�^����V�[����</param>
/// <returns>����</returns>
template<typename T>
bool RegisterSceneIfNotExists(std::string registerSceneName)
{
	// ���łɓo�^����Ă���ꍇ�o�^����Ȃ�
	if (scenes.find(registerSceneName) != scenes.end()) return false;
	// �V�K�o�^
	RegisterScene<T>(registerSceneName);
	return true;
}

#pragma region �V�[���ύX
/// <summary>
/// �V�[���ύX
/// </summary>
/// <param name="loadSceneName">�ύX�V�[����</param>
void LoadScene(std::string loadSceneName)
{
	if (scenes.find(loadSceneName) != scenes.end())
	{
		// �V�[�����ݒ肳��Ă��Ȃ��ꍇ�A�ŏ��̓ǂݍ��݃V�[����ݒ肷��
		if (currentSceneKey.empty()) currentSceneKey = loadSceneName;
		nextSceneKey = loadSceneName;
	}
}
#pragma endregion

#pragma region �}�E�X�J�[�\���̕\����\���̐ݒ�
/// <summary>
/// �}�E�X�J�[�\���̕\����\���̐ݒ�
/// </summary>
/// <param name="isShow">true:�\��,false:��\��</param>
void SetShowMouseCursor(bool isShow)
{
	// �J�[�\���́A�\���J�E���g�� 0 �ȏ�̏ꍇ�ɂ̂ݕ\��
	int count = ShowCursor(isShow);
	while (isShow ? count < 0 : count >= 0)
	{
		count = ShowCursor(isShow);
	}
}
#pragma endregion

#pragma region �f�t�H���g�ݒ�ŃE�B���h�E�N���X��o�^���܂�
/// <summary>
/// �f�t�H���g�ݒ�ŃE�B���h�E�N���X��o�^���܂��B
/// �w�肳�ꂽ�E�B���h�E�v���V�[�W�������A�W���I�Ȑݒ�̃E�B���h�E�N���X��o�^���܂��B
/// �w�i�F�A�J�[�\���A�X�^�C���Ȃǂ̃p�����[�^�͌Œ肳��Ă��܂��B
/// </summary>
/// <param name="instance">�A�v���P�[�V�����̃C���X�^���X�n���h��</param>
/// <param name="applicationName">�o�^����E�B���h�E�N���X�̖��O</param>
/// <param name="windowProcedure">�E�B���h�E�v���V�[�W���i���b�Z�[�W�����֐��j</param>
/// <returns>true:���� false:���s</returns>
bool RegisterDefaultWindowClass(
	_In_ HINSTANCE instance,
	_In_ LPCWSTR applicationName,
	_In_ WNDPROC windowProcedure)
{
	// �E�B���h�E�N���X�̃p�����[�^�[��ݒ�
	WNDCLASSEX wcex{};
	// �\���̂̃T�C�Y��ݒ�
	wcex.cbSize = sizeof(WNDCLASSEX);
	// �E�B���h�E�̃X�^�C��
	// CS_HREDRAW: �E�B���h�E�̕����ύX���ꂽ�ۂɍĕ`��
	// CS_VREDRAW: �E�B���h�E�̍������ύX���ꂽ�ۂɍĕ`��
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	// �E�B���h�E�v���V�[�W���i���b�Z�[�W�����֐��j���w��B
	wcex.lpfnWndProc = windowProcedure;
	// �N���X�������̒ǉ��o�C�g���i�ʏ�� 0�j
	wcex.cbClsExtra = 0;
	// �E�B���h�E���Ƃ̒ǉ��������̃o�C�g���i�ʏ�� 0�j
	wcex.cbWndExtra = 0;
	// �E�B���h�E�N���X��������A�v���P�[�V�����̃C���X�^���X�n���h��
	wcex.hInstance = instance;
	// �E�B���h�E�̃A�C�R����ݒ�iNULL �̏ꍇ�̓f�t�H���g�A�C�R���j
	wcex.hIcon = nullptr;
	// �}�E�X�J�[�\���̃f�t�H���g�ݒ�i�ʏ�͖��J�[�\���j
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	// �E�B���h�E�̔w�i�F��ݒ�B
	// (HBRUSH)(COLOR_WINDOW + 1) �ŃV�X�e���̕W���w�i�F���g�p
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// ���j���[�̃��\�[�X���iNULL �̏ꍇ�̓��j���[�Ȃ��j
	wcex.lpszMenuName = nullptr;
	// �E�B���h�E�N���X����ݒ�
	wcex.lpszClassName = applicationName;
	// �������A�C�R���i�^�X�N�o�[�̃T���l�C���p�j�BNULL �̏ꍇ�̓f�t�H���g
	wcex.hIconSm = nullptr;

	// �E�B���h�E�N���X�̓o�^�B
	if (!RegisterClassExW(&wcex))
	{
		MessageBox(nullptr, L"�E�B���h�E�N���X�̓o�^�Ɏ��s���܂����B", L"�G���[", MB_ICONERROR);
		return false; // ���s���� false ��Ԃ�
	}
	return true; // �������� true ��Ԃ�
}
#pragma endregion

#pragma region �f�t�H���g�ݒ�ŃE�B���h�E���쐬���܂�
/// <summary>
/// �f�t�H���g�ݒ�ŃE�B���h�E���쐬���܂��B
/// �w�肳�ꂽ�E�B���h�E�N���X���g�p���A�W���I�Ȑݒ�̃E�B���h�E���쐬���܂��B
/// �N���C�A���g�̈�̃T�C�Y���w�肵�A����ɍ����E�B���h�E�T�C�Y�������������܂��B
/// </summary>
/// <param name="instance">�A�v���P�[�V�����̃C���X�^���X�n���h��</param>
/// <param name="className">�E�B���h�E�N���X�̖��O</param>
/// <param name="screenWidth">�N���C�A���g�̈�̕��i�s�N�Z���j</param>
/// <param name="screenHeight">�N���C�A���g�̈�̍����i�s�N�Z���j</param>
/// <param name="windowTitle">�E�B���h�E�̃^�C�g��</param>
/// <param name="windowStyle">�E�B���h�E�̃X�^�C���i�f�t�H���g�� WS_OVERLAPPEDWINDOW ���� WS_THICKFRAME �����O�j</param>
/// <returns>�쐬���ꂽ�E�B���h�E�̃n���h���i���s���� nullptr�j</returns>
HWND CreateDefaultWindow(
	_In_ HINSTANCE instance,
	_In_ LPCWSTR className,
	_In_ LONG screenWidth,
	_In_ LONG screenHeight,
	_In_ LPCWSTR windowTitle,
	_In_ DWORD windowStyle)
{
	// �N���C�A���g�̈�̃T�C�Y���w��
	RECT clientRect{ 0, 0, screenWidth, screenHeight };

	// �N���C�A���g�̈悪�w��̃T�C�Y�ɂȂ�悤�ɃE�B���h�E�T�C�Y�𒲐�
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E���쐬���A���̃n���h����Ԃ�
	return CreateWindowExW(
		0,                  // �g���E�B���h�E�X�^�C���i�Ȃ��j
		className,          // �g�p����E�B���h�E�N���X�̖��O
		windowTitle,        // �E�B���h�E�̃^�C�g��
		windowStyle,        // �E�B���h�E�̃X�^�C��
		CW_USEDEFAULT,      // ����X���W�i�f�t�H���g�j
		CW_USEDEFAULT,      // ����Y���W�i�f�t�H���g�j
		clientRect.right - clientRect.left, // �v�Z���ꂽ�E�B���h�E�̕�
		clientRect.bottom - clientRect.top, // �v�Z���ꂽ�E�B���h�E�̍���
		nullptr,            // �e�E�B���h�E�i�Ȃ��j
		nullptr,            // ���j���[�i�Ȃ��j
		instance,           // �A�v���P�[�V�����C���X�^���X
		nullptr             // �ǉ��p�����[�^�i�Ȃ��j
	);
}
#pragma endregion

#pragma region �E�B���h�E���b�Z�[�W���f�B�X�p�b�`
/// <summary>
/// �E�B���h�E���b�Z�[�W���f�B�X�p�b�`�B
/// false���Ԃ��Ă�����A�Q�[���I���B
/// </summary>
/// <returns>����</returns>
bool DispatchWindowMessage()
{
	MSG msg = { 0 };
	//�E�B���h�E����̃��b�Z�[�W���󂯎��B
	while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
	{
		if (msg.message == WM_QUIT) return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//�E�B���h�E���b�Z�[�W����ɂȂ����B
	return true;
}
#pragma endregion

#pragma region FPS�v�Z
/// <summary>
/// FPS�v�Z
/// </summary>
/// <param name="timeStamp">�o�߂������v����</param>
void CalculateFrameStats(float timeStamp)
{
	// CalculateFrameStats �t���[�����[�g�v�Z
	// 1�b������̕��ς̃t���[�������v�Z���A
	// �����̌��ʂ̓E�B���h�E�̃L���v�V�����o�[�ɒǉ�����܂��B
	// 1�t���[���������_�����O����̂ɂ����镽�ώ��Ԃ��Z�o���܂��B
	static int frames = 0;
	static float time_tlapsed = 0.0f;

	// 1�b�Ԃ�FPS���Z�o
	if ((++frames, timeStamp - time_tlapsed) >= 1.0f)
	{
		float fps = static_cast<float>(frames); // fps = frameCnt / 1
		float mspf = 1000.0f / fps;
		std::ostringstream outs;
		outs.precision(6);
		outs << "FPS : " << fps << " / " << "Frame Time : " << mspf << " (ms)";
		SetWindowTextA(hwnd, outs.str().c_str());

		// ���̕��ςɃ��Z�b�g���܂��B
		frames = 0;
		time_tlapsed += 1.0f;
	}
}
#pragma endregion
