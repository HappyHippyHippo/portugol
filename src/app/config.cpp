#include <globals.hpp>
#include <app/config.hpp>

#include <hypnos/hypnos.hpp>
using namespace hyp;

#include <fstream>

std::unique_ptr<Config> Config::m_singleton{ nullptr };

Config::Config(void)
{
    atexit(Config::_destroySingleton);
} /* end of : Config::Config(void) */

Config::~Config(void)
{

} /* end of : Config::~Config(void) */

bool
Config::load(const std::string file,
             const bool clear)
{
    char buffer[1024];

    if (!m_singleton.get())
        m_singleton.reset(new Config());

    if (clear)
        m_singleton->m_configs.clear();

    std::ifstream stream{ file };
    if (stream.good())
    {
        while (!stream.eof())
        {
            stream.getline(buffer, 1024);
            if (!stream.eof())
            {
                std::string line{ buffer };
                line = trim(line);

                std::size_t pos;
                if (   line != ""
                    && line[0] != '#'
                    && (pos = line.find_first_of('=')) != std::string::npos)
                {
                    std::string key  { line.substr(0, pos - 1) };
                    std::string value{ line.substr(pos + 1) };

                    key = trim(key);
                    value = trim(value);

                    auto it = m_singleton->m_configs.find(key);
                    if (it != m_singleton->m_configs.end())
                    {
                        it->second.value = value;
                        it->second.updated = true;
                    }
                    else
                        m_singleton->m_configs[key] = { value,
                                                        false };
                }
            }
        }
    }
    else
        return false;

    return true;
} /* end of : bool
              Config::load(const std::string file,
                           const bool clear) */

void
Config::store(const std::string file)
{
    if (!m_singleton.get())
        m_singleton.reset(new Config());

    std::ofstream stream{ file };

    for (auto it = m_singleton->m_configs.begin(), end = m_singleton->m_configs.end();
        it != end;
        ++it)
    {
        if (it->second.updated)
            stream << it->first << " = " << it->second.value << std::endl;
    }
} /* end of: void
             Config::store(const std::string file) */

bool
Config::getBool(const std::string key)
{
    int value;

    if (!m_singleton.get())
        m_singleton.reset(new Config());

    auto it = m_singleton->m_configs.find(key);
    if (it == m_singleton->m_configs.end()
#ifdef _MSC_VER
        || sscanf_s(it->second.value.c_str(),
                    "%d",
                    &value) == 0)
#else
        || sscanf(it->second.value.c_str(),
                  "%d",
                  &value) == 0)
#endif
        return false;

    return value != 0;
} /* end of : bool
              Config::getBool(const std::string key) */

int
Config::getInt(const std::string key)
{
    int value;

    if (!m_singleton.get())
        m_singleton.reset(new Config());

    auto it = m_singleton->m_configs.find(key);
    if (it == m_singleton->m_configs.end()
#ifdef _MSC_VER
        || sscanf_s(it->second.value.c_str(),
                    "%d",
                    &value) == 0)
#else
        || sscanf(it->second.value.c_str(),
                  "%d",
                  &value) == 0)
#endif
        return 0;

    return value;
} /* end of : int
              Config::getInt(const std::string key) */

float
Config::getFloat(const std::string key)
{
    float value;

    if (!m_singleton.get())
        m_singleton.reset(new Config());

    auto it = m_singleton->m_configs.find(key);
    if (it == m_singleton->m_configs.end()
#ifdef _MSC_VER
        || sscanf_s(it->second.value.c_str(),
                    "%f",
                    &value) == 0)
#else
        || sscanf(it->second.value.c_str(),
                  "%f",
                  &value) == 0)
#endif
        return 0;

    return value;
} /* end of : float
              Config::getFloat(const std::string key) */

std::string
Config::getString(const std::string key)
{
    if (!m_singleton.get())
        m_singleton.reset(new Config());

    auto it = m_singleton->m_configs.find(key);
    if (it == m_singleton->m_configs.end())
        return "";

    return it->second.value;
} /* end of : std::string
              Config::getString(const std::string key) */

void
Config::set(const std::string key,
            const bool value)
{
    char buffer[2];

    if (!m_singleton.get())
        m_singleton.reset(new Config());

#ifdef _MSC_VER
    sprintf_s(buffer, 2, "%d", value);
#else
    sprintf(buffer, "%d", value);
#endif // _MSC_VER
    m_singleton->m_configs[key].value = buffer;
    m_singleton->m_configs[key].updated = true;
} /* end of : void
              Config::set(const std::string key,
                          const bool value) */

void
Config::set(const std::string key,
            const int value)
{
    char buffer[64];

    if (!m_singleton.get())
        m_singleton.reset(new Config());

#ifdef _MSC_VER
    sprintf_s(buffer, 64, "%d", value);
#else
    sprintf(buffer, "%d", value);
#endif // _MSC_VER
    m_singleton->m_configs[key].value = buffer;
    m_singleton->m_configs[key].updated = true;
} /* end of : void
              Config::set(const std::string key,
                          const int value) */

void
Config::set(const std::string key,
            const float value)
{
    char buffer[64];

    if (!m_singleton.get())
        m_singleton.reset(new Config());

#ifdef _MSC_VER
    sprintf_s(buffer, 64, "%f", value);
#else
    sprintf(buffer, "%f", value);
#endif // _MSC_VER
    m_singleton->m_configs[key].value = buffer;
    m_singleton->m_configs[key].updated = true;
} /* end of : void
              Config::set(const std::string key,
                          const float value) */

void
Config::set(const std::string key,
            const std::string value)
{
    if (!m_singleton.get())
        m_singleton.reset(new Config());

    m_singleton->m_configs[key].value = value;
    m_singleton->m_configs[key].updated = true;
} /* end of : void
              Config::set(const std::string key,
                          const std::string value) */

void
Config::_destroySingleton(void)
{
    if (m_singleton != nullptr)
        m_singleton.reset();
} /* end of : void
              Config::_destroySingleton(void) */
