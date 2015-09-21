#include <portugol/code/code_string.hpp>

namespace portugol
{
    namespace code
    {
        CodeString::CodeString(const std::string source,
                               const std::string code)
            : CodeChunk{ source }
        {
            _readString(code);
            _tokenize();
            _syntax();
        } /* end of : CodeString::CodeString(const std::string source,
                                             const std::string string) */

        CodeString::~CodeString(void)
        {

        } /* end of : CodeString::~CodeString(void) */

        CodeString&
        CodeString::_readString(const std::string code)
        {
            std::string::size_type prev{ 0 }, pos{ 0 };
            std::string seperator{ "\n" };
            std::string line{ "" };

            while((pos = code.find(seperator, pos)) != std::string::npos)
            {
                line = code.substr(prev, pos - prev);
                m_code.push_back(line);

                prev = ++pos;
            }

            line = code.substr(prev, pos - prev);
            m_code.push_back(line);

            return *this;
        } /* end of : CodeString&
                      CodeString::_readString(const std::string code) */
    } // end of : namespace code
} // end of : namespace portugol
