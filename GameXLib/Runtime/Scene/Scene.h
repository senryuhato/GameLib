#pragma once

/// <summary>
/// �V�[���N���X
/// </summary>
class Scene
{
public:
	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize() {}

	/// <summary>
	/// �I������
	/// </summary>
	virtual void Uninitializr() {}

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update() {}

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Render() {}
};