#pragma once

#include <map>
#include <memory>
#include <string>

/// @brief
class I18n
{
public:
    /// @brief
    ~I18n(void);

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
    /// @param key
    /// @return
    static std::string
    get(const std::string key);

protected:
    /// @brief
    I18n(void);

    /// @brief
    static void
    _destroySingleton(void);

protected:
    /// @brief
    static std::unique_ptr<I18n> m_singleton;

    /// @brief
    std::map<std::string, std::string> m_strings;
}; /* end of : class I18n */
