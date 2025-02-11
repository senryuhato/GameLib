#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>

/// <summary>
/// サービスロケーターパターンを実装したクラス
/// </summary>
class SystemServiceLocator
{
public:
    /// <summary>
    /// サービスを登録する。
    /// </summary>
    /// <typeparam name="T">登録するサービスの型</typeparam>
    /// <param name="service">登録するサービスのインスタンス（shared_ptr）</param>
    template<typename T>
    static void RegisterService(std::shared_ptr<T> service)
    {
        services[std::type_index(typeid(T))] = service;
    }

    /// <summary>
    /// 新しいサービスを登録（既に登録されている場合は登録しない）
    /// </summary>
    /// <typeparam name="T">登録するサービスの型</typeparam>
    /// <param name="service">登録するサービスのインスタンス（shared_ptr）</param>
    /// <returns>結果</returns>
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
    /// 登録されたサービスを取得する。(基底クラス型で取得してダウンキャスト)
    /// </summary>
    /// <typeparam name="T">取得するサービスの型</typeparam>
    /// <returns>指定した型のサービスインスタンス（shared_ptr）</returns>
    template<typename T>
    static std::shared_ptr<T> GetService()
    {
        return std::static_pointer_cast<T>(services[std::type_index(typeid(T))]);
    }

private:
    // 登録されたサービスを保持するコンテナ。
    static std::unordered_map<std::type_index, std::shared_ptr<void>> services;
};