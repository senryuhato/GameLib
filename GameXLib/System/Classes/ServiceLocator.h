#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>

/// <summary>
/// サービスロケーターパターンを実装したクラス
/// </summary>
class ServiceLocator
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
    /// 登録されたサービスを取得する。(基底クラス型で取得してダウンキャスト)
    /// </summary>
    /// <typeparam name="T">取得するサービスの型</typeparam>
    /// <returns>指定した型のサービスインスタンス（shared_ptr）</returns>
    template<typename T>
    static std::shared_ptr<T> GetService()
    {
        return std::static_pointer_cast<T>(services[std::type_index(typeid(T))]);
    }

    static std::unordered_map<std::type_index, std::shared_ptr<void>> services;

private:
    // 登録されたサービスを保持するコンテナ。
    
};