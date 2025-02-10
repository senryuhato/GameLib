#include "../../System/Private/Misc.h"
#include "../Classes\GraphicsManager.h"

#pragma region DirectX �̏�����
/// <summary>
/// DirectX �̏�����
/// </summary>
/// <param name="hwnd">�E�B���h�E�n���h��</param>
/// <param name="defultFramerate">�ڕW�t���[�����[�g�i�f�t�H���g: 60�j</param>
/// <returns>����</returns>
bool GraphicsManager::Initialize(
	HWND hwnd, 
	UINT defaultFramerate)
{
	// ��ʂ̃T�C�Y���擾����B
	RECT rc;
	GetClientRect(hwnd, &rc);
	frameBufferWidth = rc.right - rc.left;
	frameBufferHeight = rc.bottom - rc.top;

	// �f�o�C�X���X���b�v�`�F�C���̍쐬
	CreateDeviceAndSwapChain(hwnd, frameBufferWidth, frameBufferHeight, defaultFramerate);
	// �t���[���o�b�t�@�pRTV�̍쐬
	CreateRTVForFrameBuffer();
	// �t���[���o�b�t�@�pDSV�̍쐬
	CreateDSVForFrameBuffer(frameBufferWidth, frameBufferHeight);

	// �r���[�|�[�g�̐ݒ�
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<FLOAT>(frameBufferWidth);
	viewport.Height = static_cast<FLOAT>(frameBufferHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	return true;
}
#pragma endregion

#pragma region MyRegion
/// <summary>
/// DirectX �̃��\�[�X�����
/// </summary>
void GraphicsManager::Uninitialize()
{
	// �t���X�N���[���Ȃ�I�����ɃE�B���h�E���[�h�ɖ߂��B(Alt+Enter�Ő؂�ւ����ł���)
	BOOL fullscreen = 0;
	if (swapChain)
	{
		swapChain->GetFullscreenState(&fullscreen, 0);
		if (fullscreen)
		{
			swapChain->SetFullscreenState(FALSE, 0);
		}
	}
}
#pragma endregion

#pragma region �f�o�C�X���X���b�v�`�F�C���̍쐬
/// <summary>
/// �f�o�C�X���X���b�v�`�F�C���̍쐬
/// </summary>
/// <param name="hwnd">�E�B���h�E�n���h��</param>
/// <param name="frameBufferWidth">�t���[���o�b�t�@�̕�</param>
/// <param name="frameBufferHeight">�t���[���o�b�t�@�̍���</param>
/// <param name="defaultFramerate">�ڕW�t���[�����[�g</param>
void GraphicsManager::CreateDeviceAndSwapChain(
	HWND hwnd, 
	UINT frameBufferWidth, 
	UINT frameBufferHeight, 
	UINT defaultFramerate)
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// �@�\���x��
	// �V�F�[�_�[���f��5.0��_11_1�ȏ�łȂ��Ƃ����Ȃ��B
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	// �X���b�v�`�F�C�����쐬���邽�߂̐ݒ�
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	{
		swapChainDesc.BufferDesc.Width = frameBufferWidth; // �𑜓x�i���j
		swapChainDesc.BufferDesc.Height = frameBufferHeight; // �𑜓x�i�����j
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 1�s�N�Z��������̊e�F(RGBA)��8bit(0�`255)�̃e�N�X�`��(�o�b�N�o�b�t�@)���쐬����B
		swapChainDesc.BufferDesc.RefreshRate.Numerator = defaultFramerate; // ���t���b�V�����[�g
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.SampleDesc.Count = 1; // �}���`�T���v�����O�Ȃ�
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferCount = 1; // �o�b�N�o�b�t�@�̐�
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // �����_�����O�^�[�Q�b�g�Ƃ��Ďg��
		swapChainDesc.OutputWindow = hwnd; // DirectX�ŏ��������\������E�B���h�E
		swapChainDesc.Windowed = true; // �E�B���h�E���[�h���A�t���X�N���[���ɂ��邩�B
	}

	D3D_FEATURE_LEVEL featureLevel{};

	// �f�o�C�X���X���b�v�`�F�C���̐���
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,                   // �ǂ̃r�f�I�A�_�v�^���g�p���邩�H����Ȃ��nullptr�ŁAIDXGIAdapter�̃A�h���X��n���B
		D3D_DRIVER_TYPE_HARDWARE,  // �h���C�o�̃^�C�v��n���BD3D_DRIVER_TYPE_HARDWARE �ȊO�͊�{�I�Ƀ\�t�g�E�F�A�����ŁA���ʂȂ��Ƃ�����ꍇ�ɗp����B
		nullptr,                   // ��L��D3D_DRIVER_TYPE_SOFTWARE�ɐݒ肵���ۂɁA���̏������s��DLL�̃n���h����n���B����ȊO���w�肵�Ă���ۂɂ͕K��nullptr��n���B
		createDeviceFlags,         // ���炩�̃t���O���w�肷��B �ڂ�����D3D11_CREATE_DEVICE�񋓌^�Ō����B
		featureLevels,             // D3D_FEATURE_LEVEL�񋓌^�̔z���^����Bnullptr�ɂ��邱�Ƃł���Lfeature�Ɠ����̓��e�̔z�񂪎g�p�����B
		ARRAYSIZE(featureLevels),  // feature_levels�z��̗v�f����n���B
		D3D11_SDK_VERSION,         // SDK�̃o�[�W�����B�K�����̒l�B
		&swapChainDesc,            // �����Őݒ肵���\���̂ɐݒ肳��Ă���p�����[�^��SwapChain���쐬�����B
		swapChain.GetAddressOf(),  // �쐬�����������ꍇ�ɁAswap_chain�̃A�h���X���i�[����|�C���^�ϐ��ւ̃A�h���X�B�����Ŏw�肵���|�C���^�ϐ��o�R��swap_chain�𑀍삷��B
		device.GetAddressOf(),     // �쐬�����������ꍇ�ɁAdevice�̃A�h���X���i�[����|�C���^�ϐ��ւ̃A�h���X�B�����Ŏw�肵���|�C���^�ϐ��o�R��device�𑀍삷��B
		&featureLevel,             // �쐬�ɐ�������D3D_FEATURE_LEVEL���i�[���邽�߂�D3D_FEATURE_LEVEL�񋓌^�ϐ��̃A�h���X��ݒ肷��B
		immediateContext.GetAddressOf() // �쐬�����������ꍇ�ɁAcontext�̃A�h���X���i�[����|�C���^�ϐ��ւ̃A�h���X�B�����Ŏw�肵���|�C���^�ϐ��o�R��icontext�𑀍삷��B
	);

	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
}
#pragma endregion

#pragma region ���[���o�b�t�@�p�̃����_�[�^�[�Q�b�g�r���[�iRTV�j���쐬
/// <summary>
/// ���[���o�b�t�@�p�̃����_�[�^�[�Q�b�g�r���[�iRTV�j���쐬
/// </summary>
void GraphicsManager::CreateRTVForFrameBuffer()
{
	HRESULT hr= S_OK;

	// �X���b�v�`�F�[������o�b�N�o�b�t�@�e�N�X�`�����擾����B
	// ���X���b�v�`�F�[���ɓ����Ă���o�b�N�o�b�t�@�e�N�X�`����'�F'���������ރe�N�X�`���B
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(backBuffer.GetAddressOf()));
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));

	// �o�b�N�o�b�t�@�e�N�X�`���ւ̏������݂̑����ƂȂ郌���_�[�^�[�Q�b�g�r���[�𐶐�����B
	hr = device->CreateRenderTargetView(backBuffer.Get(), nullptr, renderTargetView.GetAddressOf());

	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
}
#pragma endregion

#pragma region �t���[���o�b�t�@�p�̐[�x�X�e���V���r���[�iDSV�j���쐬
/// <summary>
/// �t���[���o�b�t�@�p�̐[�x�X�e���V���r���[�iDSV�j���쐬
/// </summary>
/// <param name="frameBufferWidth">�t���[���o�b�t�@�̕�</param>
/// <param name="frameBufferHeight">�t���[���o�b�t�@�̍���</param>
void GraphicsManager::CreateDSVForFrameBuffer(
	UINT frameBufferWidth, 
	UINT frameBufferHeight)
{
	HRESULT hr = S_OK;

	// �[�x�X�e���V�������������ނ��߂̃e�N�X�`�����쐬����B
	D3D11_TEXTURE2D_DESC texture2dDesc{};
	texture2dDesc.Width = frameBufferWidth;
	texture2dDesc.Height = frameBufferHeight;
	texture2dDesc.MipLevels = 1;
	texture2dDesc.ArraySize = 1;
	texture2dDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;	// 1�s�N�Z��������A�[�x����24Bit / �X�e���V������8bit�̃e�N�X�`�����쐬����B
	texture2dDesc.SampleDesc.Count = 1;
	texture2dDesc.SampleDesc.Quality = 0;
	texture2dDesc.Usage = D3D11_USAGE_DEFAULT;
	texture2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;		// �[�x�X�e���V���p�̃e�N�X�`�����쐬����B
	texture2dDesc.CPUAccessFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer{};
	hr = device->CreateTexture2D(&texture2dDesc, nullptr, depthStencilBuffer.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));

	// �[�x�X�e���V���e�N�X�`���ւ̏������݂ɑ����ɂȂ�[�x�X�e���V���r���[���쐬����B
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = texture2dDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	hr = device->CreateDepthStencilView(depthStencilBuffer.Get(), &depthStencilViewDesc, depthStencilView.GetAddressOf());

	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
}
#pragma endregion


