#include <regex>
#include <sstream>

#include <portugol/code/code_chunk.hpp>
#include <portugol/code/environment.hpp>
#include <portugol/code/tree/constant.hpp>
#include <portugol/code/tree/function.hpp>
#include <portugol/code/tree/operator.hpp>
#include <portugol/code/tree/return.hpp>

namespace portugol
{
    namespace code
    {
        CodeChunk::CodeChunk(const std::string source)
        {
            m_source = source;
        } /* end of : CodeChunk::CodeChunk(const std::string source) */

        CodeChunk::~CodeChunk(void)
        {

        } /* end of : CodeChunk::~CodeChunk(void) */

        std::vector<std::string>
        CodeChunk::getCode(void) const
        {
            return m_code;
        } /* end of : std::vector<std::string>
                      CodeChunk::getCode(void) const */

        CodeChunk&
        CodeChunk::_tokenize(void)
        {
            std::size_t nline{ 0 };
            for (auto it = m_code.begin(), end = m_code.end();
                 it != end;
                 ++it, ++nline)
            {
                std::vector<Token> instruction;

                std::string line{ *it };
                auto comment = line.find('#');
                if (comment != std::string::npos)
                    line = line.substr(0, comment);

                std::size_t position{ 0 };
                std::size_t length{ line.length() };

                while (position < length)
                {
                    while (   position < length
                           && iswspace(line[0]))
                    {
                        line = line.substr(1);
                        ++position;
                    }

                    if (position < length)
                    {
                        Token token;

                        if (   line[0] >= 0
                            || line[0] <= 127)
                        {
                            std::regex reg{ Token::getRegex() };
                            std::regex_search(line, reg);
                            std::sregex_iterator it{ line.begin(), line.end(), reg };
                            std::sregex_iterator it_end;

                            if (it != it_end)
                            {
                                token.type   = Token::getTypeValue(it->str());
                                token.source = m_source;
                                token.line   = nline;
                                token.column = position;
                                token.value  = it->str();
                                token.atom   = nullptr;

                                line = line.substr(token.value.length());
                                position += token.value.length();

                                std::size_t pos;
                                while ((pos = token.value.find("\\\"")) != std::string::npos)
                                    token.value.replace(pos, 2, "\"");

                                instruction.push_back(token);
                            }
                            else
                                throw std::string{ "Unrecognizable token at line" };
                        }
                        else
                            throw std::string{ "Unrecognizable character at line" };
                    }
                }

                if (instruction.size() > 0)
                    m_tokens.push_back(instruction);
            }

            return *this;
        } /* end of : CodeChunk&
                      CodeChunk::_tokenize(void) */

        CodeChunk&
        CodeChunk::_syntax(void)
        {
            tree::Node* global{ nullptr };
            std::size_t ninstruction{ 0 };
            while (ninstruction < m_tokens.size())
            {
                global = nullptr;

                if (m_tokens[ninstruction][0].type == Token::Type::PROGRAM)
                {
                    if (m_tokens[ninstruction].size() > 1)
                        throw std::string{ "Unexpected extra tokens after program token" };

                    global = new tree::Function("programa", Value::Type::INT32, nullptr);
                    ++ninstruction;

                    bool cycle{ true };
                    while (cycle)
                    {
                        if (ninstruction == m_tokens.size())
                            throw std::string{ "Unexpected end of file" };

                        switch (m_tokens[ninstruction][0].type)
                        {
                            case Token::Type::END_PROGRAM:
                            {
                                if (m_tokens[ninstruction].size() > 1)
                                    throw std::string{ "Unexpected extra tokens after end program token" };

                                cycle = false;
                                ++ninstruction;

                                break;
                            }
                            case Token::Type::RETURN:
                            {
                                if (m_tokens[ninstruction].size() == 0)
                                    throw std::string{ "Missing the result instruction expression" };

                                tree::Return* instruction = new tree::Return(nullptr, Value::Type::INT32, global);
                                instruction->setResult(_syntaxExpression(std::vector<Token>{ m_tokens[ninstruction].begin() + 1, m_tokens[ninstruction].end() }, instruction));
                                ((tree::Function*) global)->pushInstruction(instruction);

                                ++ninstruction;
                                break;
                            }
                            default:
                                throw std::string{ "Unable to parse the local function instruction" };
                        }
                    }
                }

                if (global != nullptr)
                    _pushInstruction(global);
                else
                    throw std::string{ "Unable to parse the global instruction" };
            }

            return *this;
        } /* end of : CodeChunk&
                      CodeChunk::_syntax(void) */

        tree::Node*
        CodeChunk::_syntaxExpression(std::vector<Token> tokens,
                                     tree::Node* parent)
        {
            for (auto it = tokens.begin(), it_end = tokens.end();
                 it < it_end;
                 ++it)
            {
                if (!it->atom)
                {
                    switch (it->type)
                    {
                        case Token::Type::VAL_FALSE:
                        {
                            it->atom = new tree::Constant(Value::Type::BOOLEAN, parent);
                            ((tree::Constant*) it->atom)->getValue().setBoolean(false);
                            break;
                        }
                        case Token::Type::VAL_TRUE:
                        {
                            it->atom = new tree::Constant(Value::Type::BOOLEAN, parent);
                            ((tree::Constant*) it->atom)->getValue().setBoolean(true);
                            break;
                        }
                        case Token::Type::VAL_INT32:
                        {
                            int32_t value;
                            std::stringstream sstream{ it->value };
                            sstream >> value;

                            it->atom = new tree::Constant(Value::Type::INT32, parent);
                            ((tree::Constant*) it->atom)->getValue().setInt32(value);
                            break;
                        }
                        case Token::Type::VAL_FLOAT32:
                        {
                            float value;
                            std::stringstream sstream{ it->value };
                            sstream >> value;

                            it->atom = new tree::Constant(Value::Type::FLOAT32, parent);
                            ((tree::Constant*) it->atom)->getValue().setFloat32(value);
                            break;
                        }
                        case Token::Type::VAL_TEXT:
                        {
                            it->atom = new tree::Constant(Value::Type::TEXT, parent);
                            ((tree::Constant*) it->atom)->getValue().setText(it->value);
                            break;
                        }
                    }
                }
            }

            std::size_t depth = 0;
            std::size_t open = 0;
            for (std::size_t it = 0, it_end = tokens.size();
                 it < it_end;
                 )
            {
                switch (tokens[it].type)
                {
                    case Token::Type::OPEN_PARENTHESIS:
                    {
                        if (!depth)
                            open = it;
                        ++depth;
                        ++it;
                        break;
                    }
                    case Token::Type::CLOSE_PARENTHESIS:
                    {
                        if (depth == 1)
                        {
                            tokens[open].type = Token::Type::ATOM;
                            tokens[open].atom = _syntaxExpression(std::vector<Token>{ tokens.begin() + open + 1, tokens.begin() + it }, parent);
                            tokens.erase(tokens.begin() + open + 1, tokens.begin() + it + 1);

                            depth = 0;
                            it_end -= it - open;
                            it = open + 1;
                        }
                        else
                        {
                            --depth;
                            ++it;
                        }
                        break;
                    }
                    default:
                        ++it;
                        break;
                }
            }

            if (depth != 0)
                throw std::string{ "Unexpected end of expression, missing closing parenthesis" };

            for (std::size_t it = 1, it_end = tokens.size() - 1;
                 it < it_end;
                 )
            {
                switch (tokens[it].type)
                {
                    case Token::Type::OP_MULTIPLY:
                    {
                        if (tokens[it - 1].atom == nullptr)
                            throw std::string{ "Multiplication found without left operand" };
                        if (tokens[it + 1].atom == nullptr)
                            throw std::string{ "Multiplication found without right operand" };

                        tokens[it].atom = new tree::MultiplyOperator(tokens[it - 1].atom, tokens[it + 1].atom, parent);

                        tokens.erase(tokens.begin() + it + 1);
                        tokens.erase(tokens.begin() + it - 1);
                        it_end -= 2;

                        break;
                    }
                    case Token::Type::OP_DIVIDE:
                    {
                        if (tokens[it - 1].atom == nullptr)
                            throw std::string{ "Division found without left operand" };
                        if (tokens[it + 1].atom == nullptr)
                            throw std::string{ "Division found without right operand" };

                        tokens[it].atom = new tree::DivideOperator(tokens[it - 1].atom, tokens[it + 1].atom, parent);

                        tokens.erase(tokens.begin() + it + 1);
                        tokens.erase(tokens.begin() + it - 1);
                        it_end -= 2;

                        break;
                    }
                    case Token::Type::OP_REMAINDER:
                    {
                        if (tokens[it - 1].atom == nullptr)
                            throw std::string{ "Remainder found without left operand" };
                        if (tokens[it + 1].atom == nullptr)
                            throw std::string{ "Remainder found without right operand" };

                        tokens[it].atom = new tree::RemainderOperator(tokens[it - 1].atom, tokens[it + 1].atom, parent);

                        tokens.erase(tokens.begin() + it + 1);
                        tokens.erase(tokens.begin() + it - 1);
                        it_end -= 2;

                        break;
                    }
                    default:
                        ++it;
                        break;
                }
            }

            for (std::size_t it = 1, it_end = tokens.size() - 1;
                 it < it_end;
                 )
            {
                switch (tokens[it].type)
                {
                    case Token::Type::OP_ADD:
                    {
                        if (tokens[it - 1].atom == nullptr)
                            throw std::string{ "Addition found without left operand" };
                        if (tokens[it + 1].atom == nullptr)
                            throw std::string{ "Addition found without right operand" };

                        tokens[it].atom = new tree::AddOperator(tokens[it - 1].atom, tokens[it + 1].atom, parent);

                        tokens.erase(tokens.begin() + it + 1);
                        tokens.erase(tokens.begin() + it - 1);
                        it_end -= 2;

                        break;
                    }
                    case Token::Type::OP_SUBTRACT:
                    {
                        if (tokens[it - 1].atom == nullptr)
                            throw std::string{ "Subtraction found without left operand" };
                        if (tokens[it + 1].atom == nullptr)
                            throw std::string{ "Subtraction found without right operand" };

                        tokens[it].atom = new tree::SubtractOperator(tokens[it - 1].atom, tokens[it + 1].atom, parent);

                        tokens.erase(tokens.begin() + it + 1);
                        tokens.erase(tokens.begin() + it - 1);
                        it_end -= 2;

                        break;
                    }
                    default:
                        ++it;
                        break;
                }
            }

            if (tokens.size() != 1)
                throw std::string{ "Unexpected extra token after expression" };

            return tokens[0].atom;
        } /* end of : tree::Node*
                      CodeChunk::_syntaxExpression(std::vector<Token> tokens,
                                                   tree::Node* parent) */

        CodeChunk&
        CodeChunk::_pushInstruction(tree::Node* node)
        {
            m_instructions.push_back(std::unique_ptr<tree::Node>(node));
            return *this;
        } /* end of : CodeChunk&
                      CodeChunk::_pushInstruction(tree::Node* node) */
    } // end of : namespace code
} // end of : namespace portugol
