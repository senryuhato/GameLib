#include <crtdbg.h>
#include <time.h>
#include <sstream>
#include <map>
#include <DirectXMath.h>
#include "../GameXLib\Runtime\Scene\Scene.h"
#include "../GameXLib/Runtime/System/Misc.h"
#include "WinMain.h"
#include "SystemInstance.h"
#include "Scene\TitleScene.h"
#include "Scene\MainScene.h"

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

/// <summary>
/// �[�x�X�e���V���X�e�[�g
/// </summary>
Microsoft::WRL::ComPtr<ID3D11DepthStencilState> defaultDepthStencilState;

/// <summary>
/// ���X�^���C�U�[�X�e�[�g
/// </summary>
Microsoft::WRL::ComPtr<ID3D11RasterizerState> defaultRasterizerState[2];

enum BLEND_MODE
{
	NONE = 0,
	ALPHA,
	ADD,
	SUBTRACT,
	REPLACE,
	MULTIPLY,
	LIGHTEN,
	DARKEN,
	SCREEN,
	// �ő�
	MODE_MAX,
};

/// <summary>
/// �u�����h�X�e�[�g
/// </summary>
Microsoft::WRL::ComPtr<ID3D11BlendState> defaultBlendState[BLEND_MODE::MODE_MAX];

/// <summary>
/// �T���v���[�X�e�[�g
/// </summary>
Microsoft::WRL::ComPtr<ID3D11SamplerState> defaultSamplerState[3];

/// <summary>
/// ViewProjection
/// </summary>
DirectX::XMFLOAT4X4 viewProjection;

/// <summary>
/// ���C�g�ʒu
/// </summary>
DirectX::XMFLOAT4 lightDirection;

/// <summary>
/// �J�����ʒu
/// </summary>
DirectX::XMFLOAT4 cameraPosition;

/// <summary>
/// ���W
/// </summary>
DirectX::XMFLOAT4X4 worldTransform;
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

				// �X�e�[�g�̍쐬
				CreateState();

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

					// �X�e�[�g�ݒ�
					immediateContext->PSSetSamplers(0, 3, defaultSamplerState[0].GetAddressOf());
					immediateContext->OMSetBlendState(defaultBlendState[BLEND_MODE::ALPHA].Get(), nullptr, 0xFFFFFFFF);
					immediateContext->RSSetState(defaultRasterizerState[0].Get());
					immediateContext->OMSetDepthStencilState(defaultDepthStencilState.Get(), 1);
					immediateContext->RSSetState(defaultRasterizerState[0].Get());

					// �J�����쐬
					CreateCamera();

					// ���[���h���W�ݒ�
					CreateWorldTransform();

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

#pragma region ���[���h���W�ݒ�
/// <summary>
/// ���[���h���W�ݒ�
/// </summary>
void CreateWorldTransform()
{
	// ���ϊ�
	const DirectX::XMFLOAT4X4 coordinateSystemTransforms[]{
	  { -1, 0, 0, 0, 0, 1,  0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }, // 0:RHS Y-UP 
	  {  1, 0, 0, 0, 0, 1,  0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }, // 1:LHS Y-UP 
	  { -1, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 1 }, // 2:RHS Z-UP 
	  {  1, 0, 0, 0, 0, 0,  1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },  // 3:LHS Z-UP 
	};

	// ��
	const float scale_factor = 1.0f;
	DirectX::XMMATRIX coordinate{ DirectX::XMLoadFloat4x4(&coordinateSystemTransforms[1]) * DirectX::XMMatrixScaling(scale_factor, scale_factor, scale_factor) };

	// XYZ�̉�]�ݒ�
	constexpr float roll = DirectX::XMConvertToRadians(360);
	constexpr float pitch = DirectX::XMConvertToRadians(360);
	constexpr float yaw = DirectX::XMConvertToRadians(360);

	// �X�P�[�����O�s��
	DirectX::XMMATRIX scale{ DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f) };
	// ��]�s��
	DirectX::XMMATRIX rotation{ DirectX::XMMatrixRotationRollPitchYaw(roll, pitch, yaw) };
	// ���s�ړ��s��
	DirectX::XMMATRIX translation{ DirectX::XMMatrixTranslation(0,0,0) };

	// ���[���h�s��
	DirectX::XMStoreFloat4x4(&worldTransform, coordinate * scale * rotation * translation);
}
#pragma endregion

#pragma region �J�����쐬
/// <summary>
/// �J�����쐬
/// </summary>
void CreateCamera()
{
	// ��ʃT�C�Y�擾
	D3D11_VIEWPORT viewport;
	UINT numViewports{ 1 };
	systemInstace.graphicsManager.GetDeviceContext()->RSGetViewports(&numViewports, &viewport);

	// �A�X�y�N�g��
	float aspectRatio{ viewport.Width / viewport.Height };
	// �������e�쐬
	DirectX::XMMATRIX projection{ DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(30), aspectRatio, 0.1f, 1000.0f) };

	// �J�������ݒ�
	DirectX::XMVECTOR eye{ DirectX::XMVectorSet(0.0f, 0.0f, -250.0f, 1.0f) };
	DirectX::XMVECTOR focus{ DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f) };
	DirectX::XMVECTOR up{ DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) };
	DirectX::XMMATRIX view{ DirectX::XMMatrixLookAtLH(eye, focus, up) };

	// ViewProjection�쐬
	DirectX::XMStoreFloat4x4(&viewProjection, view * projection);
}
#pragma endregion

#pragma region �X�e�[�g�̍쐬
/// <summary>
/// �X�e�[�g�̍쐬
/// </summary>
void CreateState()
{
	HRESULT hr = S_OK;

	// �[�x�X�e���V���X�e�[�g�̍쐬
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	hr = systemInstace.graphicsManager.GetDevice()->CreateDepthStencilState(&depthStencilDesc, defaultDepthStencilState.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));

	// ���X�^���C�U�[�X�e�[�g
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0;
	rasterizerDesc.SlopeScaledDepthBias = 0;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.ScissorEnable = FALSE;
	rasterizerDesc.MultisampleEnable = TRUE;
	rasterizerDesc.AntialiasedLineEnable = FALSE;
	// DirectX��
	rasterizerDesc.FrontCounterClockwise = FALSE;
	hr = systemInstace.graphicsManager.GetDevice()->CreateRasterizerState(&rasterizerDesc, defaultRasterizerState[0].GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
	// OpenGL��
	rasterizerDesc.FrontCounterClockwise = TRUE;
	hr = systemInstace.graphicsManager.GetDevice()->CreateRasterizerState(&rasterizerDesc, defaultRasterizerState[1].GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));

	// �u�����h�X�e�[�g
	CreateBlendState();

	// �T���v���[�X�e�[�g
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	// 
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	hr = systemInstace.graphicsManager.GetDevice()->CreateSamplerState(&samplerDesc, defaultSamplerState[0].GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
	// 
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	hr = systemInstace.graphicsManager.GetDevice()->CreateSamplerState(&samplerDesc, defaultSamplerState[1].GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
	// 
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	hr = systemInstace.graphicsManager.GetDevice()->CreateSamplerState(&samplerDesc, defaultSamplerState[2].GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
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

#pragma region �u�����h�X�e�[�g�̍쐬
/// <summary>
/// �u�����h�X�e�[�g�̍쐬
/// </summary>
void CreateBlendState()
{
	HRESULT hr;

	D3D11_BLEND_DESC bDesc = {};
	bDesc.AlphaToCoverageEnable = FALSE;
	bDesc.IndependentBlendEnable = FALSE;
	bDesc.RenderTarget[0].BlendEnable = TRUE;

	// NONE(�Ȃ�)
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::NONE]);

	// ALPHA()
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::ALPHA]);

	// ADD(���Z)
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::ADD]);

	// SUBTRACT(���Y)
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_SUBTRACT;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::SUBTRACT]);

	// REPLACE
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::REPLACE]);

	// MULTIPLY(��Z)
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_COLOR;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_DEST_ALPHA;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::MULTIPLY]);

	// LIGHTEN
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MAX;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_DEST_ALPHA;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::LIGHTEN]);

	// DARKEN
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MIN;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MIN;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::DARKEN]);

	// SCREEN
	bDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
	bDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	bDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = systemInstace.graphicsManager.GetDevice()->CreateBlendState(&bDesc, &defaultBlendState[BLEND_MODE::SCREEN]);
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
		// �g���E�B���h�E�X�^�C���i�Ȃ��j
		0,
		// �g�p����E�B���h�E�N���X�̖��O
		className,
		// �E�B���h�E�̃^�C�g��
		windowTitle,
		// �E�B���h�E�̃X�^�C��
		windowStyle,
		// ����X���W�i�f�t�H���g�j
		CW_USEDEFAULT,
		// ����Y���W�i�f�t�H���g�j
		CW_USEDEFAULT,
		// �v�Z���ꂽ�E�B���h�E�̕�
		clientRect.right - clientRect.left,
		// �v�Z���ꂽ�E�B���h�E�̍���
		clientRect.bottom - clientRect.top,
		// �e�E�B���h�E�i�Ȃ��j
		nullptr,
		// ���j���[�i�Ȃ��j
		nullptr,
		// �A�v���P�[�V�����C���X�^���X
		instance,
		// �ǉ��p�����[�^�i�Ȃ��j
		nullptr
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
