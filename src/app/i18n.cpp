#include <app/i18n.hpp>

#include <hypnos/hypnos.hpp>
using namespace hyp;

#include <fstream>

std::unique_ptr<I18n> I18n::m_singleton{ nullptr };

I18n::I18n(void)
{
    atexit(I18n::_destroySingleton);
} /* end of : I18n::I18n(void) */

I18n::~I18n(void)
{

} /* end of : I18n::~I18n(void) */

bool
I18n::load(const std::string file,
           const bool clear)
{
    char buffer[1024];

    if (!m_singleton.get())
        m_singleton.reset(new I18n());

    if (clear)
        m_singleton->m_strings.clear();

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

                    m_singleton->m_strings[key] = value;
                }
            }
        }
    }
    else
        return false;

    return true;
} /* end of : bool
              I18n::load(const std::string file,
                         const bool clear) */

std::string
I18n::get(const std::string key)
{
    if (!m_singleton.get())
        m_singleton.reset(new I18n());

    auto it = m_singleton->m_strings.find(key);
    if (it == m_singleton->m_strings.end())
        return "<" + key + ">";

    return it->second;
} /* end of : std::string
              I18n::get(const std::string key) */

void
I18n::_destroySingleton(void)
{
    if (m_singleton != nullptr)
        m_singleton.reset();
} /* end of : void
              I18n::_destroySingleton(void) */
