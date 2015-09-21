#pragma once

#include <string>

#include <portugol/code/code_chunk.hpp>

namespace portugol
{
    namespace code
    {
        class Environment;

        /// @brief
        class CodeString : public CodeChunk
        {
            friend class Environment;

        public:
            /// @brief
            ~CodeString(void);

        protected:
            /// @brief
            ///
            /// @param source
            /// @param code
            CodeString(const std::string source,
                       const std::string code);

            /// @brief
            ///
            /// @param code
            /// @return
            CodeString&
            _readString(const std::string code);
        }; /* end of : class CodeString : public CodeChunk */
    } // end of : namespace code
} // end of : namespace portugol
