#pragma once

#include <string>

#include <portugol/code/tree/node.hpp>

namespace portugol
{
    namespace code
    {
        /// @brief
        class Token
        {
        public:
            /// @brief
            enum class Type
            {
                /// @brief
                UNKNOWN,

                /// @brief
                ATOM,

                /// @brief
                VAL_TRUE,

                /// @brief
                VAL_FALSE,

                /// @brief
                VAL_INT32,

                /// @brief
                VAL_FLOAT32,

                /// @brief
                VAL_TEXT,

                /// @brief
                IDENTIFIER,

                /// @brief
                BOOLEAN,

                /// @brief
                INT32,

                /// @brief
                FLOAT32,

                /// @brief
                TEXT,

                /// @brief
                OP_ADD,

                /// @brief
                OP_SUBTRACT,

                /// @brief
                OP_MULTIPLY,

                /// @brief
                OP_DIVIDE,

                /// @brief
                OP_REMAINDER,

                /// @brief
                OP_ASSIGN,

                /// @brief
                OPEN_PARENTHESIS,

                /// @brief
                CLOSE_PARENTHESIS,

                /// @brief
                COMA,

                /// @brief
                PROGRAM,

                /// @brief
                RETURN,

                /// @brief
                END_PROGRAM
            }; /* end of : enum class Type */

        public:
            /// @brief
            ///
            /// @param type
            /// @return
            static std::string
            getTypeString(const Token::Type type);

            /// @brief
            ///
            /// @param string
            /// @return
            static Token::Type
            getTypeValue(const std::string string);

            /// @brief
            ///
            /// @return
            static std::string
            getRegex(void);

        public:
            /// @brief
            Token(void);

            /// @brief
            ~Token(void);

            /// @brief
            ///
            /// @return
            std::string
            toString(void) const;

        public:
            /// @brief
            Type type;

            /// @brief
            std::string source;

            /// @brief
            std::size_t line;

            /// @brief
            std::size_t column;

            /// @brief
            std::string value;

            /// @brief
            tree::Node* atom;
        }; /* end of : class Token */
    } // end of : namespace code
} // end of : namespace portugol
