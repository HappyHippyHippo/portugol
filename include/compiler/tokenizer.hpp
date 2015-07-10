#pragma once

#include <string>
#include <vector>

#include <compiler/token.hpp>

/// @brief
class Tokenizer
{
public:
    /// @brief
    Tokenizer(void);

    /// @brief
    virtual
    ~Tokenizer(void);

    /// @brief
    ///
    /// @param source
    /// @return
    bool
    tokenize(std::string source);

    /// @brief
    ///
    /// @return
    std::vector<Token>
    getTokens(void) const;

    /// @brief
    ///
    /// @return
    int
    getErrorPosition(void) const;

protected:
    /// @brief
    void
    discard_spaces(void);

    /// @brief
    ///
    /// @param token
    /// @return
    bool
    read_token(Token* token);

protected:
    /// @brief
    std::vector<Token> m_list;

    /// @brief
    std::string m_source;

    /// @brief
    std::size_t m_length;

    /// @brief
    std::size_t m_position;

    /// @brief
    std::size_t m_error_position;
}; // end of : class Tokenizer
