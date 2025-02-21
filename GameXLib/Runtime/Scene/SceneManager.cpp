#include "SceneManager.h"
#include "../Graphics/GraphicsManager.h"
#include "../UI/ImGuiManager.h"
#include "../System/ServiceLocator.h"

#pragma region �X�V����
/// <summary>
/// �X�V����
/// </summary>
void SceneManager::Update()
{
	// �V�[�����ݒ肳��Ă��邩
	if (currentSceneKey.empty()) return;
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
#pragma endregion

#pragma region �`�揈��
/// <summary>
/// �`�揈��
/// </summary>
void SceneManager::Render()
{
	// �V�[�����ݒ肳��Ă��邩
	if (currentSceneKey.empty()) return;

	std::shared_ptr<GraphicsManager> graphicsManager = ServiceLocator::GetService<GraphicsManager>();
	ID3D11DeviceContext* immediateContext = graphicsManager->GetDeviceContext();
	ID3D11RenderTargetView* renderTargetView = graphicsManager->GetRenderTargetView();
	ID3D11DepthStencilView* depthStencilView = graphicsManager->GetDepthStencilView();
	IDXGISwapChain* swapChain = graphicsManager->GetSwapChain();

	// ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
	immediateContext->ClearRenderTargetView(renderTargetView, refreshColor);
	immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	immediateContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	std::shared_ptr<ImGuiManager> imGuiManager = ServiceLocator::GetService<ImGuiManager>();
	// UI�\������
	imGuiManager->NewFrame();

	// �Q�[������
	scenes[currentSceneKey]->Render();

	// UI�\��
	imGuiManager->Render();
	// �o�b�N�o�b�t�@�ɕ`�悵�������ʂɕ\������B
	swapChain->Present(SYNC_INTERVAL_VALID, 0);
}
#pragma endregion

#pragma region �V�[���ύX
/// <summary>
/// �V�[���ύX
/// </summary>
/// <param name="loadSceneName">�ύX�V�[����</param>
void SceneManager::LoadScene(std::string loadSceneName)
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
void SceneManager::SetShowMouseCursor(bool isShow)
{
	// �J�[�\���́A�\���J�E���g�� 0 �ȏ�̏ꍇ�ɂ̂ݕ\��
	int count = ShowCursor(isShow);
	while (isShow ? count < 0 : count >= 0)
	{
		count = ShowCursor(isShow);
	}
}
#pragma endregion