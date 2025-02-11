#include "GameFramework.h"
#include "../GameXLib/Graphics/Classes/GraphicsManager.h"
#include "../GameXLib/System/Classes/SystemServiceLocator.h"
#include "TimeManager.h"
#include "GameServiceLocator.h"

#pragma region ����������
/// <summary>
/// ����������
/// </summary>
void GameFramework::Initialize()
{
	// �^�C�}�[
	GameServiceLocator::RegisterServiceIfNotExists(std::make_shared<TimeManager>());
}
#pragma endregion

#pragma region �Q�[�����[�v
/// <summary>
/// �Q�[�����[�v
/// </summary>
void GameFramework::Run()
{
	std::shared_ptr<TimeManager> timeManager = GameServiceLocator::GetService<TimeManager>();
	// �^�C�}�[�X�V
	timeManager->Update();
	Update();
	Render();
}
#pragma endregion

#pragma region �X�V����
/// <summary>
/// �X�V����
/// </summary>
void GameFramework::Update()
{

}
#pragma endregion

#pragma region �`�揈��
/// <summary>
/// �`�揈��
/// </summary>
void GameFramework::Render()
{
	std::shared_ptr<GraphicsManager> graphicsManager = SystemServiceLocator::GetService<GraphicsManager>();
	ID3D11DeviceContext* immediateContext = graphicsManager->GetDeviceContext();
	ID3D11RenderTargetView* renderTargetView = graphicsManager->GetRenderTargetView();
	ID3D11DepthStencilView* depthStencilView = graphicsManager->GetDepthStencilView();
	IDXGISwapChain* swapChain = graphicsManager->GetSwapChain();

	// ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
	immediateContext->ClearRenderTargetView(renderTargetView, refreshColor);
	immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	immediateContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	// �Q�[������


	// �o�b�N�o�b�t�@�ɕ`�悵�������ʂɕ\������B
	swapChain->Present(SYNC_INTERVAL_VALID, 0);
}
#pragma endregion





