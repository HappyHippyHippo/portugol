#pragma once

#include <portugol/lex/lex.h>

typedef struct LexParam
{
    AST_Pos pos;
    VType   type;
    char*   name;
} LexParam;

typedef struct LexToken
{
    AST_Pos pos;
    char*   text;
    int     token;
} LexToken;

typedef struct LexVarType
{
    AST_Pos pos;
    char*   text;
    int     type;
} LexVarType;

#ifdef _MSC_VER
#define YY_NO_UNISTD_H
#endif /* _MSC_VER */
