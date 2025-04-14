#pragma once
#include "../GameXLib/Runtime/Scene/Scene.h"

/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene : public Scene
{
public:
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;

	/// <summary>
    /// �`�揈��
    /// </summary>
	void Render() override;

	/// <summary>
    /// GUI�`��
    /// </summary>
	void ShowGUI() override;
};