#pragma once

/// <summary>
/// ���ԊǗ�
/// </summary>
class TimeManager
{
public:
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �t���[���ԕb���̎擾
	/// </summary>
	/// <returns></returns>
	float GetElapsedTime() { return elapsedTime; }
private:
	// �t���[���ԕb��
	float elapsedTime = 0.0f;
};