#pragma once
#include <unordered_map>
#include <memory>

namespace ServiceNames
{
    // �V�X�e���T�[�r�X�n
    const std::string FRAMEWORK = "Framework";
    const std::string GRAPHICS_MANAGER = "GraphicsManager";
    const std::string BASE_IMGUI_MANAGER = "BaseImGuiManager";
    const std::string HIGH_RESOLUTION_TIMER = "HighResolutionTimer";
    const std::string TIME_MANAGER = "TimeManager";
    const std::string SCENE_MANAGER = "SceneManager";
}

/// <summary>
/// �T�[�r�X���P�[�^�[�p�^�[�������������N���X
/// </summary>
class ServiceLocator
{
public:
    /// <summary>
    /// �T�[�r�X��o�^����B
    /// </summary>
    /// <typeparam name="T">�o�^����T�[�r�X�̌^</typeparam>
    /// <param name="serviceName">�o�^����T�[�r�X��</param>
    /// <param name="service">�o�^����T�[�r�X�̃C���X�^���X�ishared_ptr�j</param>
    template<typename T>
    static void RegisterService(std::string serviceName, std::shared_ptr<T> service = std::make_shared<T>())
    {
        // �N���X����Key�Ƃ��ď㏑���o�^����
        services[serviceName] = service;
    }

    /// <summary>
    /// �V�����T�[�r�X��o�^�i���ɓo�^����Ă���ꍇ�͓o�^���Ȃ��j
    /// </summary>
    /// <typeparam name="T">�o�^����T�[�r�X�̌^</typeparam>
    /// <param name="serviceName">�o�^����T�[�r�X��</param>
    /// <param name="service">�o�^����T�[�r�X�̃C���X�^���X�ishared_ptr�j</param>
    /// <returns>����</returns>
    template<typename T>
    static bool RegisterServiceIfNotExists(std::string serviceName, std::shared_ptr<T> service = std::make_shared<T>())
    {
        // ���łɓo�^����Ă���ꍇ�A�o�^���s��Ȃ�
        if (services.find(serviceName) != services.end()) return false;
        // �V�K�o�^
        RegisterService(serviceName, service);
        return true;
    }

    /// <summary>
    /// �o�^���ꂽ�T�[�r�X���擾����B(���N���X�^�Ŏ擾���ă_�E���L���X�g)
    /// </summary>
    /// <typeparam name="T">�擾����T�[�r�X�̌^</typeparam>
    /// <param name="serviceName">�擾����T�[�r�X��</param>
    /// <returns>�w�肵���^�̃T�[�r�X�C���X�^���X�ishared_ptr�j</returns>
    template<typename T>
    static std::shared_ptr<T> GetService(std::string serviceName)
    {
        // �l���ݒ肳��Ă���ꍇ
        auto it = services.find(serviceName);
        if (it != services.end())
        {
            // �N���X����Key�Ƃ��Ď擾����
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

private:
    // �o�^���ꂽ�T�[�r�X��ێ�����R���e�i�B
    static std::unordered_map<std::string, std::shared_ptr<void>> services;
};