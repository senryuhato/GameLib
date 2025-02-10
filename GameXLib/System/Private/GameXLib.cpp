#include <sstream>

#include "../Classes/GameXLib.h"
#include "../Classes/ServiceLocator.h"

#pragma region �R���X�g���N�^
/// <summary>
/// �R���X�g���N�^
/// </summary>
GameXLib::GameXLib()
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
}
#pragma endregion

#pragma region �t���[�����[�N�̏������i�E�B���h�E�� DirectX �̃Z�b�g�A�b�v�j
/// <summary>
/// �t���[�����[�N�̏������i�E�B���h�E�� DirectX �̃Z�b�g�A�b�v�j
/// </summary>
/// <param name="instance">�A�v���P�[�V�����̃C���X�^���X�n���h��</param>
/// <param name="nShowCmd">�E�B���h�E�̕\�����</param>
/// <param name="screenWidth">�N���C�A���g�̈�̕��i�s�N�Z���j</param>
/// <param name="screenHeight">�N���C�A���g�̈�̍����i�s�N�Z���j</param>
/// <param name="windowTitle">�E�B���h�E�̃^�C�g��</param>
/// <returns>����</returns>
bool GameXLib::Initialize(
	_In_ HINSTANCE instance,
	_In_ int nShowCmd,
	_In_ LONG screenWidth,
	_In_ LONG screenHeight,
	_In_ LPCWSTR windowTitle)
{
	// ������
	Uninitialize(instance);
	// �T�[�r�X�̓o�^
	RegisterServices(); 
	bool isSuccess = true;

	// �E�B���h�E�N���X�̓o�^
	if (!RegisterDefaultWindowClass(instance, CLASS_NAME, WindowProcedure))
	{
		isSuccess = false;
	}

	if (isSuccess)
	{
		// �E�B���h�E�̍쐬
		hwnd = CreateDefaultWindow(instance, CLASS_NAME, screenWidth, screenHeight, windowTitle);
		if (!hwnd)
		{
			isSuccess = false;
		}
		else
		{
			// �E�B���h�E�̕\����Ԑݒ�(�\���Ɣ�\��)
			ShowWindow(hwnd, nShowCmd);
		}
	}

	// DirectX�̏�����
	std::shared_ptr<GraphicsManager> graphicsManager = ServiceLocator::GetService<GraphicsManager>();
	if (!isSuccess || !graphicsManager || !graphicsManager->Initialize(hwnd))
	{
		isSuccess = false;
	}

	// ImGui�̏�����
	std::shared_ptr<ImGuiManager> imguiManager = ServiceLocator::GetService<ImGuiManager>();
	if (!isSuccess || !imguiManager || !imguiManager->Initialize(hwnd, graphicsManager->GetDevice(), graphicsManager->GetDeviceContext()))
	{
		isSuccess = false;
	}

	if (!isSuccess)
	{
		Uninitialize(instance);
		return false;
	}

	return true;
}
#pragma endregion

#pragma region �t���[�����[�N�̏I������
/// <summary>
/// �t���[�����[�N�̏I������
/// </summary>
/// <param name="instance">�A�v���P�[�V�����̃C���X�^���X�n���h��</param>
void GameXLib::Uninitialize(
	_In_ HINSTANCE instance)
{
	// ImGui�̏I������
	std::shared_ptr<ImGuiManager> imguiManager = ServiceLocator::GetService<ImGuiManager>();
	if (imguiManager)
	{
		imguiManager->Uninitialize();
	}
	// DirectX�̉��
	std::shared_ptr<GraphicsManager> graphicsManager = ServiceLocator::GetService<GraphicsManager>();
	if (graphicsManager)
	{
		graphicsManager->Uninitialize();
	}

	// �E�B���h�E�̍폜
	DestroyWindow(hwnd);
	// �E�B���h�E�N���X�̍폜
	UnregisterClass(CLASS_NAME, instance);
}
#pragma endregion

#pragma region �Q�[�����[�v
/// <summary>
/// �Q�[�����[�v
/// </summary>
/// <returns></returns>
int GameXLib::Run()
{
	std::shared_ptr<Framework> framework = ServiceLocator::GetService<Framework>();
	if (!framework)
	{
		return framework->Run(hwnd);
	}
	return -1;
}
#pragma endregion

#pragma region �}�l�[�W���[�̓o�^
/// <summary>
/// �}�l�[�W���[�̓o�^
/// </summary>
void GameXLib::RegisterServices()
{
	// �e��}�l�[�W���[�̓o�^
	ServiceLocator::RegisterService(std::make_shared<Framework>());
	ServiceLocator::RegisterService(std::make_shared<GraphicsManager>());
	ServiceLocator::RegisterService(std::make_shared<ImGuiManager>());
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
LRESULT CALLBACK GameXLib::WindowProcedure(
	_In_ HWND hwnd,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	// �T�[�r�X���P�[�^���� imguiManager �� framework ���擾
	std::shared_ptr<ImGuiManager> imguiManager = ServiceLocator::GetService<ImGuiManager>();
	std::shared_ptr<Framework> framework = ServiceLocator::GetService<Framework>();

	if (imguiManager)
	{
		imguiManager->WndProcHandler(hwnd, msg, wParam, lParam);
	}

	if (framework)
	{
		return framework->HandleMessage(hwnd, msg, wParam, lParam);
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);;
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
bool GameXLib::RegisterDefaultWindowClass(
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
/// <param name="windowStyle">�B���h�E�̃X�^�C���i�f�t�H���g�� WS_OVERLAPPEDWINDOW ���� WS_THICKFRAME �����O�j</param>
/// <returns>�쐬���ꂽ�E�B���h�E�̃n���h���i���s���� nullptr�j</returns>
HWND GameXLib::CreateDefaultWindow(
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