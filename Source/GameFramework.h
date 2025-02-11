#pragma once
#include "../GameXLib/System/Classes/Framework.h"

/// <summary>
/// �Q�[���N���X
/// </summary>
class GameFramework : public Framework
{
public:
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �I������
	/// </summary>
	void Uninitialize() {}

	/// <summary>
	/// �Q�[�����[�v
	/// </summary>
	void Run();

	/// <summary>
    /// �X�V����
    /// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();
private:
	// �N���A�J���[
	FLOAT refreshColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	// �萔
	const UINT SYNC_INTERVAL_VALID = 1;
	const UINT SYNC_INTERVAL_INVALID = 0;
};