#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>

/// <summary>
/// �T�[�r�X���P�[�^�[�p�^�[�������������N���X
/// </summary>
class SystemServiceLocator
{
public:
    /// <summary>
    /// �T�[�r�X��o�^����B
    /// </summary>
    /// <typeparam name="T">�o�^����T�[�r�X�̌^</typeparam>
    /// <param name="service">�o�^����T�[�r�X�̃C���X�^���X�ishared_ptr�j</param>
    template<typename T>
    static void RegisterService(std::shared_ptr<T> service)
    {
        services[std::type_index(typeid(T))] = service;
    }

    /// <summary>
    /// �V�����T�[�r�X��o�^�i���ɓo�^����Ă���ꍇ�͓o�^���Ȃ��j
    /// </summary>
    /// <typeparam name="T">�o�^����T�[�r�X�̌^</typeparam>
    /// <param name="service">�o�^����T�[�r�X�̃C���X�^���X�ishared_ptr�j</param>
    /// <returns>����</returns>
    template<typename T>
    static bool RegisterServiceIfNotExists(std::shared_ptr<T> service)
    {
        std::shared_ptr<T> obj = GetService<T>();
        if (obj)
        {
            return false;
        }
        RegisterService<T>(service);
        return true;
    }

    /// <summary>
    /// �o�^���ꂽ�T�[�r�X���擾����B(���N���X�^�Ŏ擾���ă_�E���L���X�g)
    /// </summary>
    /// <typeparam name="T">�擾����T�[�r�X�̌^</typeparam>
    /// <returns>�w�肵���^�̃T�[�r�X�C���X�^���X�ishared_ptr�j</returns>
    template<typename T>
    static std::shared_ptr<T> GetService()
    {
        return std::static_pointer_cast<T>(services[std::type_index(typeid(T))]);
    }

private:
    // �o�^���ꂽ�T�[�r�X��ێ�����R���e�i�B
    static std::unordered_map<std::type_index, std::shared_ptr<void>> services;
};