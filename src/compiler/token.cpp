#include <compiler/token.hpp>

#include <regex>

std::string
Token::toString(void) const
{
    switch (type)
    {
        case Token::Type::VALUE_TRUE:
        case Token::Type::VALUE_FALSE:
            return value;
        case Token::Type::IDENTIFIER:
            return "id(" + value + ")";
        case Token::Type::VALUE_INT8:
        case Token::Type::VALUE_INT16:
        case Token::Type::VALUE_INT32:
        case Token::Type::VALUE_INT64:
        case Token::Type::VALUE_UINT8:
        case Token::Type::VALUE_UINT16:
        case Token::Type::VALUE_UINT32:
        case Token::Type::VALUE_UINT64:
        case Token::Type::VALUE_INTEGER:
            return "integer(" + value + ")";
        case Token::Type::VALUE_FLOAT32:
        case Token::Type::VALUE_FLOAT64:
        case Token::Type::VALUE_FLOAT:
            return "float(" + value + ")";
        case Token::Type::VALUE_TEXT:
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
        case Token::Type::RESERVED_IMPORT:
            return "RESERVED_IMPORT";
        case Token::Type::RESERVED_PROGRAM:
            return "RESERVED_PROGRAM";
        case Token::Type::RESERVED_END_PROGRAM:
            return "RESERVED_PROGRAM";
        case Token::Type::RESERVED_FUNCTION:
            return "RESERVED_FUNCTION";
        case Token::Type::RESERVED_END_FUNCTION:
            return "RESERVED_END_FUNCTION";
        case Token::Type::RESERVED_SCOPE:
            return "RESERVED_SCOPE";
        case Token::Type::RESERVED_END_SCOPE:
            return "RESERVED_END_SCOPE";
        case Token::Type::RESERVED_RETURN:
            return "RESERVED_RETURN";
        case Token::Type::RESERVED_CONSTANT:
            return "RESERVED_CONSTANT";
        case Token::Type::RESERVED_VARIABLE:
            return "RESERVED_VARIABLE";
        case Token::Type::RESERVED_BOOLEAN:
            return "RESERVED_BOOLEAN";
        case Token::Type::RESERVED_INT8:
            return "RESERVED_INT8";
        case Token::Type::RESERVED_INT16:
            return "RESERVED_INT16";
        case Token::Type::RESERVED_INT32:
            return "RESERVED_INT32";
        case Token::Type::RESERVED_INT64:
            return "RESERVED_INT64";
        case Token::Type::RESERVED_UINT8:
            return "RESERVED_UINT8";
        case Token::Type::RESERVED_UINT16:
            return "RESERVED_UINT16";
        case Token::Type::RESERVED_UINT32:
            return "RESERVED_UINT32";
        case Token::Type::RESERVED_UINT64:
            return "RESERVED_UINT64";
        case Token::Type::RESERVED_INTEGER:
            return "RESERVED_INTEGER";
        case Token::Type::RESERVED_FLOAT32:
            return "RESERVED_FLOAT32";
        case Token::Type::RESERVED_FLOAT64:
            return "RESERVED_FLOAT64";
        case Token::Type::RESERVED_FLOAT:
            return "RESERVED_FLOAT";
        case Token::Type::RESERVED_TEXT:
            return "RESERVED_TEXT";
        case Token::Type::RESERVED_LIST:
            return "RESERVED_LIST";
        case Token::Type::SYMBOL_OPEN_PARENTHESIS:
            return "SYMBOL_OPEN_PARENTHESIS";
        case Token::Type::SYMBOL_CLOSE_PARENTHESIS:
            return "SYMBOL_CLOSE_PARENTHESIS";
        case Token::Type::SYMBOL_OPEN_BRACKETS:
            return "SYMBOL_OPEN_BRACKETS";
        case Token::Type::SYMBOL_CLOSE_BRACKETS:
            return "SYMBOL_CLOSE_BRACKETS";
        case Token::Type::SYMBOL_MEMBER:
            return "SYMBOL_MEMBER";
        case Token::Type::SYMBOL_SEPERATOR:
            return "SYMBOL_SEPERATOR";
        case Token::Type::OPERATOR_ASSIGN:
            return "OPERATOR_ASSIGN";
        case Token::Type::OPERATOR_ADD:
            return "OPERATOR_ADD";
        case Token::Type::OPERATOR_SUBTRACT:
            return "OPERATOR_SUBTRACT";
        case Token::Type::OPERATOR_MULTIPLY:
            return "OPERATOR_MULTIPLY";
        case Token::Type::OPERATOR_DIVIDE:
            return "OPERATOR_DIVIDE";
        case Token::Type::VALUE_TRUE:
            return "VALUE_TRUE";
        case Token::Type::VALUE_FALSE:
            return "VALUE_FALSE";
        case Token::Type::VALUE_INT8:
            return "VALUE_INT8";
        case Token::Type::VALUE_INT16:
            return "VALUE_INT16";
        case Token::Type::VALUE_INT32:
            return "VALUE_INT32";
        case Token::Type::VALUE_INT64:
            return "VALUE_INT64";
        case Token::Type::VALUE_UINT8:
            return "VALUE_UINT8";
        case Token::Type::VALUE_UINT16:
            return "VALUE_UINT16";
        case Token::Type::VALUE_UINT32:
            return "VALUE_UINT32";
        case Token::Type::VALUE_UINT64:
            return "VALUE_UINT64";
        case Token::Type::VALUE_INTEGER:
            return "VALUE_INTEGER";
        case Token::Type::VALUE_FLOAT32:
            return "VALUE_FLOAT32";
        case Token::Type::VALUE_FLOAT64:
            return "VALUE_FLOAT64";
        case Token::Type::VALUE_FLOAT:
            return "VALUE_FLOAT";
        case Token::Type::VALUE_TEXT:
            return "VALUE_TEXT";
        case Token::Type::IDENTIFIER:
            return "IDENTIFIER";
        default:
            break;
    }

    return "UNKNOWN";
} /* end of : std::string
              Token::getTypeString(const Token::Type type) */

Token::Type
Token::getTypeValue(const std::string string)
{
    if (string == "importar")            return Token::Type::RESERVED_IMPORT;
    if (string == "programa")            return Token::Type::RESERVED_PROGRAM;
    if (string == "fim_programa")        return Token::Type::RESERVED_END_PROGRAM;
    if (string == "funcao")                return Token::Type::RESERVED_FUNCTION;
    if (string == "fim_funcao")            return Token::Type::RESERVED_END_FUNCTION;
    if (string == "escorpo")            return Token::Type::RESERVED_SCOPE;
    if (string == "fim_escorpo")        return Token::Type::RESERVED_END_SCOPE;
    if (string == "retorna")            return Token::Type::RESERVED_RETURN;
    if (string == "constante")            return Token::Type::RESERVED_CONSTANT;
    if (string == "variavel")            return Token::Type::RESERVED_VARIABLE;
    if (string == "booleano")            return Token::Type::RESERVED_BOOLEAN;
    if (string == "inteiro8")            return Token::Type::RESERVED_INT8;
    if (string == "inteiro16")            return Token::Type::RESERVED_INT16;
    if (string == "inteiro32")            return Token::Type::RESERVED_INT32;
    if (string == "inteiro64")            return Token::Type::RESERVED_INT64;
    if (string == "inteirop8")            return Token::Type::RESERVED_UINT8;
    if (string == "inteirop16")            return Token::Type::RESERVED_UINT16;
    if (string == "inteirop32")            return Token::Type::RESERVED_UINT32;
    if (string == "inteirop64")            return Token::Type::RESERVED_UINT64;
    if (string == "inteiro")            return Token::Type::RESERVED_INTEGER;
    if (string == "flutuante32")        return Token::Type::RESERVED_FLOAT32;
    if (string == "flutuante64")        return Token::Type::RESERVED_FLOAT64;
    if (string == "flutuante")            return Token::Type::RESERVED_FLOAT;
    if (string == "texto")                return Token::Type::RESERVED_TEXT;
    if (string == "lista")                return Token::Type::RESERVED_LIST;
    if (string == "(")                    return Token::Type::SYMBOL_OPEN_PARENTHESIS;
    if (string == ")")                    return Token::Type::SYMBOL_CLOSE_PARENTHESIS;
    if (string == "[")                    return Token::Type::SYMBOL_OPEN_BRACKETS;
    if (string == "]")                    return Token::Type::SYMBOL_CLOSE_BRACKETS;
    if (string == ".")                    return Token::Type::SYMBOL_MEMBER;
    if (string == ",")                    return Token::Type::SYMBOL_SEPERATOR;
    if (string == "<-")                    return Token::Type::OPERATOR_ASSIGN;
    if (string == "+")                    return Token::Type::OPERATOR_ADD;
    if (string == "-")                    return Token::Type::OPERATOR_SUBTRACT;
    if (string == "*")                    return Token::Type::OPERATOR_MULTIPLY;
    if (string == "/")                    return Token::Type::OPERATOR_DIVIDE;
    if (string == "verdadeiro")            return Token::Type::VALUE_TRUE;
    if (string == "falso")                return Token::Type::VALUE_FALSE;

    std::regex reg_float("^\\d+\\.\\d+");
    std::regex_search(string, reg_float);
    std::sregex_iterator it_float(string.begin(), string.end(), reg_float);
    std::sregex_iterator it_end;

    if (it_float != it_end)
        return Token::Type::VALUE_FLOAT;
    else
    {
        std::regex reg_integer("^\\d+");
        std::regex_search(string, reg_integer);
        std::sregex_iterator it_integer(string.begin(), string.end(), reg_integer);

        if (it_integer != it_end)
            return Token::Type::VALUE_INTEGER;
    }

    std::regex reg_text("^\".+\"");
    std::regex_search(string, reg_text);
    std::sregex_iterator it_text(string.begin(), string.end(), reg_text);

    if (it_text != it_end)
        return Token::Type::VALUE_TEXT;

    std::regex reg_identifier("^[a-zA-Z_]\\w*");
    std::regex_search(string, reg_identifier);
    std::sregex_iterator it_identifier(string.begin(), string.end(), reg_identifier);

    if (it_identifier != it_end)
        return Token::Type::IDENTIFIER;

    return Token::Type::UNKNOWN;
} /* Token::Type
     Token::getTypeValue(const std::string string) */

std::string
Token::getRegex(void)
{
    std::string reg_exp = "";
    
    std::vector<std::string> symbols;

    symbols.push_back("\\(");
    symbols.push_back("\\)");
    symbols.push_back("\\[");
    symbols.push_back("\\]");
    symbols.push_back("\\.");
    symbols.push_back("\\,");
    symbols.push_back("\\<\\-");
    symbols.push_back("\\+");
    symbols.push_back("\\-");
    symbols.push_back("\\*");
    symbols.push_back("\\/");

    for (auto it = symbols.begin(), end = symbols.end();
        it != end;
        ++it)
    {
        if (reg_exp.length())
            reg_exp += "|";
        reg_exp += *it;
    }

    // add number
    reg_exp += "|\\d+\\.\\d+";
    reg_exp += "|\\d+";

    // add text
    reg_exp += "|\\\".+\\\"";

    // add identifier
    reg_exp += "|[a-zA-Z_]\\w*";

    return "(" + reg_exp + ")";
} /* end of : std::string
              Token::getRegex(void) */
