#include <regex>
#include <vector>

#include <portugol/code/token.hpp>

namespace portugol
{
    namespace code
    {
        Token::Token(void)
            : type{ Token::Type::UNKNOWN }
            , line{ 0 }
            , column{ 0 }
            , atom{ nullptr }
        {

        } /* end of : Token::Token(void) */

        Token::~Token(void)
        {

        } /* end of : Token::~Token(void) */

        std::string
        Token::toString(void) const
        {
            switch (type)
            {
                case Token::Type::VAL_TRUE:
                case Token::Type::VAL_FALSE:
                    return value;
                case Token::Type::IDENTIFIER:
                    return "id(" + value + ")";
                case Token::Type::VAL_INT32:
                    return "int32(" + value + ")";
                case Token::Type::VAL_FLOAT32:
                    return "float32(" + value + ")";
                case Token::Type::VAL_TEXT:
                    return "text(" + value + ")";
                case Token::Type::UNKNOWN:
                    return "unknown(" + value + ")";
                default:
                    return Token::getTypeString(type);
            }
        } /* end of : std::string
                      Token::toString(void) const */

        std::string
        Token::getTypeString(const Token::Type type)
        {
            switch(type)
            {
                case Token::Type::UNKNOWN:
                    return "UNKNOWN";
                case Token::Type::VAL_TRUE:
                    return "TRUE";
                case Token::Type::VAL_FALSE:
                    return "FALSE";
                case Token::Type::VAL_INT32:
                    return "VAL_INT32";
                case Token::Type::VAL_FLOAT32:
                    return "VAL_FLOAT32";
                case Token::Type::VAL_TEXT:
                    return "VAL_TEXT";
                case Token::Type::BOOLEAN:
                    return "BOOLEAN";
                case Token::Type::INT32:
                    return "INT32";
                case Token::Type::FLOAT32:
                    return "FLOAT32";
                case Token::Type::TEXT:
                    return "TEXT";
                case Token::Type::OP_ADD:
                    return "OP_ADD";
                case Token::Type::OP_SUBTRACT:
                    return "OP_SUBTRACT";
                case Token::Type::OP_MULTIPLY:
                    return "OP_MULTIPLY";
                case Token::Type::OP_DIVIDE:
                    return "OP_DIVIDE";
                case Token::Type::OP_REMAINDER:
                    return "OP_REMAINDER";
                case Token::Type::OP_ASSIGN:
                    return "OP_ASSIGN";
                case Token::Type::OPEN_PARENTHESIS:
                    return "OPEN_PARENTHESIS";
                case Token::Type::CLOSE_PARENTHESIS:
                    return "CLOSE_PARENTHESIS";
                case Token::Type::COMA:
                    return "COMA";
                case Token::Type::PROGRAM:
                    return "PROGRAM";
                case Token::Type::RETURN:
                    return "RETURN";
                case Token::Type::END_PROGRAM:
                    return "END_PROGRAM";
                default:
                    break;
            }

            return "UNKNOWN";
         } /* end of : std::string
                      Token::getTypeString(const Token::Type type) */

        Token::Type
        Token::getTypeValue(const std::string string)
        {
            if (string == "programa")               return Token::Type::PROGRAM;
            if (string == "retorna")                return Token::Type::RETURN;
            if (string == "fim_programa")           return Token::Type::END_PROGRAM;
            if (string == "verdadeiro")             return Token::Type::VAL_TRUE;
            if (string == "falso")                  return Token::Type::VAL_FALSE;

            if (string == "+")                      return Token::Type::OP_ADD;
            if (string == "-")                      return Token::Type::OP_SUBTRACT;
            if (string == "*")                      return Token::Type::OP_MULTIPLY;
            if (string == "/")                      return Token::Type::OP_DIVIDE;
            if (string == "%")                      return Token::Type::OP_REMAINDER;
            if (string == "resto")                  return Token::Type::OP_REMAINDER;
            if (string == "<-")                     return Token::Type::OP_ASSIGN;

            if (string == "(")                      return Token::Type::OPEN_PARENTHESIS;
            if (string == ")")                      return Token::Type::CLOSE_PARENTHESIS;
            if (string == ":")                      return Token::Type::COMA;

            std::regex reg_float{ "^\\d+\\.\\d+" };
            std::regex_search(string, reg_float);
            std::sregex_iterator it_float{ string.begin(), string.end(), reg_float };
            std::sregex_iterator it_end;

            if (it_float != it_end)
                return Token::Type::VAL_FLOAT32;
            else
            {
                std::regex reg_integer{ "^\\d+" };
                std::regex_search(string, reg_integer);
                std::sregex_iterator it_integer{ string.begin(), string.end(), reg_integer };

                if (it_integer != it_end)
                    return Token::Type::VAL_INT32;
            }

            std::regex reg_text{ "^\".+\"" };
            std::regex_search(string, reg_text);
            std::sregex_iterator it_text{ string.begin(), string.end(), reg_text };

            if (it_text != it_end)
                return Token::Type::VAL_TEXT;

            std::regex reg_identifier{ "^[a-zA-Z_]\\w*" };
            std::regex_search(string, reg_identifier);
            std::sregex_iterator it_identifier{ string.begin(), string.end(), reg_identifier };

            if (it_identifier != it_end)
                return Token::Type::IDENTIFIER;

            return Token::Type::UNKNOWN;
        } /* end of : Token::Type
                      Token::getTypeValue(const std::string string) */

        std::string
        Token::getRegex(void)
        {
            std::string reg_exp{ "" };
            std::vector<std::string> symbols;

            symbols.push_back("\\+");
            symbols.push_back("\\-");
            symbols.push_back("\\*");
            symbols.push_back("\\/");
            symbols.push_back("\\%");
            symbols.push_back("\\<\\-");

            symbols.push_back("\\(");
            symbols.push_back("\\)");
            symbols.push_back("\\:");

            for (auto it = symbols.begin(), end = symbols.end();
                it != end;
                ++it)
            {
                if (reg_exp.length())
                    reg_exp += "|";
                reg_exp += *it;
            }

            reg_exp += "|\\d+\\.\\d+";
            reg_exp += "|\\d+";

            reg_exp += "|\".+\"";

            reg_exp += "|[a-zA-Z_]\\w*";

            return "^(" + reg_exp + ")";
        } /* end of : std::string
                      Token::getRegex(void) */
    } // end of : namespace code
} // end of : namespace portugol
