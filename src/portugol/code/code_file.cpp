#include <fstream>

#include <portugol/code/code_file.hpp>

namespace portugol
{
    namespace code
    {
        CodeFile::CodeFile(const std::string path)
            : CodeChunk{ path }
        {
            _readFile();
            _tokenize();
            _syntax();
        } /* end of : CodeFile::CodeFile(const std::string path) */

        CodeFile::~CodeFile(void)
        {

        } /* end of : CodeFile::~CodeFile(void) */

        CodeFile&
        CodeFile::_readFile(void)
        {
            std::fstream stream{ m_source };
            if (stream.fail())
                throw std::string{ "Unable to open source file" };

            std::string line{ "" };
            while (stream.good())
            {
                char c;

                stream.get(c);
                if (stream.good())
                {
                    if (c != '\n')
                        line += c;
                    else {
                        m_code.push_back(line);
                        line = "";
                    }
                }
            }
            m_code.push_back(line);
            stream.close();

            return *this;
        } /* end of : CodeFile&
                      CodeFile::_readFile(void) */
    } // end of : namespace code
} // end of : namespace portugol
