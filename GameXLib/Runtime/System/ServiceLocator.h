#pragma once
#include <unordered_map>
#include <memory>

namespace ServiceNames
{
    // システムサービス系
    const std::string FRAMEWORK = "Framework";
    const std::string GRAPHICS_MANAGER = "GraphicsManager";
    const std::string BASE_IMGUI_MANAGER = "BaseImGuiManager";
    const std::string HIGH_RESOLUTION_TIMER = "HighResolutionTimer";
    const std::string TIME_MANAGER = "TimeManager";
    const std::string SCENE_MANAGER = "SceneManager";
}

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
    /// <param name="serviceName">登録するサービス名</param>
    /// <param name="service">登録するサービスのインスタンス（shared_ptr）</param>
    template<typename T>
    static void RegisterService(std::string serviceName, std::shared_ptr<T> service = std::make_shared<T>())
    {
        // クラス名をKeyとして上書き登録する
        services[serviceName] = service;
    }

    /// <summary>
    /// 新しいサービスを登録（既に登録されている場合は登録しない）
    /// </summary>
    /// <typeparam name="T">登録するサービスの型</typeparam>
    /// <param name="serviceName">登録するサービス名</param>
    /// <param name="service">登録するサービスのインスタンス（shared_ptr）</param>
    /// <returns>結果</returns>
    template<typename T>
    static bool RegisterServiceIfNotExists(std::string serviceName, std::shared_ptr<T> service = std::make_shared<T>())
    {
        // すでに登録されている場合、登録を行わない
        if (services.find(serviceName) != services.end()) return false;
        // 新規登録
        RegisterService(serviceName, service);
        return true;
    }

    /// <summary>
    /// 登録されたサービスを取得する。(基底クラス型で取得してダウンキャスト)
    /// </summary>
    /// <typeparam name="T">取得するサービスの型</typeparam>
    /// <param name="serviceName">取得するサービス名</param>
    /// <returns>指定した型のサービスインスタンス（shared_ptr）</returns>
    template<typename T>
    static std::shared_ptr<T> GetService(std::string serviceName)
    {
        // 値が設定されている場合
        auto it = services.find(serviceName);
        if (it != services.end())
        {
            // クラス名をKeyとして取得する
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

private:
    // 登録されたサービスを保持するコンテナ。
    static std::unordered_map<std::string, std::shared_ptr<void>> services;
};