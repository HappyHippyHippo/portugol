#pragma once

#include <string>

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
        RESERVED_IMPORT,

        /// @brief
        RESERVED_PROGRAM,

        /// @brief
        RESERVED_END_PROGRAM,

        /// @brief
        RESERVED_FUNCTION,

        /// @brief
        RESERVED_END_FUNCTION,

        /// @brief
        RESERVED_SCOPE,

        /// @brief
        RESERVED_END_SCOPE,

        /// @brief
        RESERVED_RETURN,

        /// @brief
        RESERVED_CONSTANT,

        /// @brief
        RESERVED_VARIABLE,

        /// @brief
        RESERVED_BOOLEAN,

        /// @brief
        RESERVED_INT8,

        /// @brief
        RESERVED_INT16,

        /// @brief
        RESERVED_INT32,

        /// @brief
        RESERVED_INT64,

        /// @brief
        RESERVED_UINT8,

        /// @brief
        RESERVED_UINT16,

        /// @brief
        RESERVED_UINT32,

        /// @brief
        RESERVED_UINT64,

        /// @brief
        RESERVED_INTEGER,

        /// @brief
        RESERVED_FLOAT32,

        /// @brief
        RESERVED_FLOAT64,

        /// @brief
        RESERVED_FLOAT,

        /// @brief
        RESERVED_TEXT,

        /// @brief
        RESERVED_LIST,

        /// @brief
        SYMBOL_OPEN_PARENTHESIS,

        /// @brief
        SYMBOL_CLOSE_PARENTHESIS,

        /// @brief
        SYMBOL_OPEN_BRACKETS,

        /// @brief
        SYMBOL_CLOSE_BRACKETS,

        /// @brief
        SYMBOL_MEMBER,

        /// @brief
        SYMBOL_SEPERATOR,

        /// @brief
        OPERATOR_ASSIGN,

        /// @brief
        OPERATOR_ADD,

        /// @brief
        OPERATOR_SUBTRACT,

        /// @brief
        OPERATOR_MULTIPLY,

        /// @brief
        OPERATOR_DIVIDE,

        /// @brief
        VALUE_TRUE,

        /// @brief
        VALUE_FALSE,

        /// @brief
        VALUE_INT8,

        /// @brief
        VALUE_INT16,

        /// @brief
        VALUE_INT32,

        /// @brief
        VALUE_INT64,

        /// @brief
        VALUE_UINT8,

        /// @brief
        VALUE_UINT16,

        /// @brief
        VALUE_UINT32,

        /// @brief
        VALUE_UINT64,

        /// @brief
        VALUE_INTEGER,

        /// @brief
        VALUE_FLOAT32,

        /// @brief
        VALUE_FLOAT64,

        /// @brief
        VALUE_FLOAT,

        /// @brief
        VALUE_TEXT,

        /// @brief
        IDENTIFIER
    };

public:
    /// @brief
    Type type;

    /// @brief
    std::string value;

    /// @brief
    ///
    /// @return
    std::string
    toString(void) const;

    /// @brief
    ///
    /// @param type
    /// @return
    static std::string
    getTypeString(const Type type);

    /// @brief
    ///
    /// @param string
    /// @return
    static Type
    getTypeValue(const std::string string);

    /// @brief
    ///
    /// @return
    static std::string
    getRegex(void);
}; // end of : class Token