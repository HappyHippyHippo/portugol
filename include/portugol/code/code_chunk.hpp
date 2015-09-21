#pragma once

#include <memory>
#include <vector>

#include <portugol/code/token.hpp>
#include <portugol/code/tree/node.hpp>

namespace portugol
{
    namespace code
    {
        /// @brief
        class CodeChunk
        {
        public:
            /// @brief
            virtual
            ~CodeChunk(void);

            /// @brief
            ///
            /// @return
            std::vector<std::string>
            getCode(void) const;
        protected:
            /// @brief
            ///
            /// @param
            CodeChunk(const std::string source);

            /// @brief
            ///
            /// @return
            CodeChunk&
            _tokenize(void);

            /// @brief
            ///
            /// @return
            CodeChunk&
            _syntax(void);

            /// @brief
            ///
            /// @param tokens
            /// @param parent
            /// @return
            tree::Node*
            _syntaxExpression(std::vector<Token> tokens,
                              tree::Node* parent);

            /// @brief
            ///
            /// @param node
            /// @return
            CodeChunk&
            _pushInstruction(tree::Node* node);

        protected:
            /// @brief
            std::string m_source;

            /// @brief
            std::vector<std::string> m_code;

            /// @brief
            std::vector<std::vector<Token>> m_tokens;

            /// @brief
            std::vector<std::unique_ptr<tree::Node>> m_instructions;
        }; /* end of : class CodeChunk */
    } // end of : namespace code
} // end of : namespace portugol
