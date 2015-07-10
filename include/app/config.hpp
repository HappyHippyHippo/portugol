#pragma once

#include <map>
#include <memory>
#include <string>

/// @brief
class Config
{
public:
    /// @brief
    ///
    /// @param config
    Config(const Config& config) = delete;

    /// @brief
    ///
    /// @param factory
    Config(Config&& config) = delete;
    
    /// @brief
    ~Config(void);

    /// @brief
    ///
    /// @param config
    Config&
    operator=(const Config& config) = delete;

    /// @brief
    ///
    /// @param factory
    Config&
    operator=(Config&& config) = delete;

    /// @brief
    ///
    /// @param file
    /// @param clear
    /// @return
    static bool
    load(const std::string file,
         const bool clear = false);

    /// @brief
    ///
    /// @param file
    static void
    store(const std::string file);

    /// @brief
    ///
    /// @param key
    /// @return
    static bool
    getBool(const std::string key);

    /// @brief
    ///
    /// @param key
    /// @return
    static int
    getInt(const std::string key);

    /// @brief
    ///
    /// @param key
    /// @return
    static float
    getFloat(const std::string key);

    /// @brief
    ///
    /// @param key
    /// @return
    static std::string
    getString(const std::string key);

    /// @brief
    ///
    /// @param key
    /// @param value
    static void
    set(const std::string key,
        const bool value);

    /// @brief
    ///
    /// @param key
    /// @param value
    static void
    set(const std::string key,
        const int value);

    /// @brief
    ///
    /// @param key
    /// @param value
    static void
    set(const std::string key,
        const float value);

    /// @brief
    ///
    /// @param key
    /// @param value
    static void
    set(const std::string key,
        const std::string value);

protected:
    /// @brief
    Config(void);

    /// @brief
    static void
    _destroySingleton(void);

protected:
    /// @brief
    typedef struct
    {
        /// @brief
        std::string value;

        /// @brief
        bool updated;
    } Entry;

protected:
    /// @brief
    static std::unique_ptr<Config> m_singleton;
    
    /// @brief
    std::map<std::string, Entry> m_configs;
}; /* end of : class Config */
