#pragma once

#include <string>

#include <portugol/code/code_chunk.hpp>

namespace portugol
{
    namespace code
    {
        class Environment;

        /// @brief
        class CodeFile : public CodeChunk
        {
            friend class Environment;

        public:
            /// @brief
            ~CodeFile(void);

        protected:
            /// @brief
            ///
            /// @param path
            CodeFile(const std::string path);

            /// @brief
            ///
            /// @return
            CodeFile&
            _readFile(void);
        }; /* end of : class CodeFile : public CodeChunk */
    } // end of : namespace code
} // end of : namespace portugol
