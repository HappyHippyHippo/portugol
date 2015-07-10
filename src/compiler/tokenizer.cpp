#include <compiler/tokenizer.hpp>

#include <algorithm>
#include <regex>
#include <iostream>

Tokenizer::Tokenizer(void)
{

} /* end of : Tokenizer::Tokenizer(void) */

Tokenizer::~Tokenizer(void)
{

} /* end of : Tokenizer::~Tokenizer(void) */

bool
Tokenizer::tokenize(std::string source)
{
    m_list.clear();
    m_source         = source;
    m_length         = source.length();
    m_position       = 0;
    m_error_position = m_length;

    while (   m_error_position == m_length
           && m_position < m_length)
    {
        Token token;

        discard_spaces();
        if (m_position < m_length)
        {
            if (read_token(&token))
                m_list.push_back(token);
            else
                m_error_position = m_position;
        }
    }

    return  m_error_position == m_length;
} /* end of : bool
              Tokenizer::tokenize(std::string source) */

std::vector<Token>
Tokenizer::getTokens(void) const
{
    return m_list;
} /* end of : std::vector<Token>
              Tokenizer::getTokens(void) const */

int
Tokenizer::getErrorPosition(void) const
{
    return m_error_position;
} /* end of : int
              Tokenizer::getErrorPosition(void) const */

void
Tokenizer::discard_spaces(void)
{
    while (   m_position < m_length
           && iswspace(m_source[0]))
    {
        m_source = m_source.substr(1);
        ++m_position;
    }
} /* end of : void
              Tokenizer::discard_spaces(void) */

bool
Tokenizer::read_token(Token* token)
{
    if (   m_source[0] < 0
        || m_source[0] > 127)
    {
        return false;
    }

    std::regex reg(Token::getRegex());
    std::regex_search(m_source, reg);
    std::sregex_iterator it(m_source.begin(), m_source.end(), reg);
    std::sregex_iterator it_end;

    if (it == it_end)
        return false;

    token->value = it->str();
    token->type = Token::getTypeValue(token->value);

    m_source = m_source.substr(token->value.length());
    m_position += token->value.length();

    std::size_t pos;
    while ((pos = token->value.find("\\\"")) != std::string::npos)
        token->value.replace(pos, 2, "\"");

    return true;
} /* end of : bool
              Tokenizer::read_token(Token* token) */
