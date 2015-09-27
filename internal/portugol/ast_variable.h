#pragma once

#include <portugol/ast.h>

typedef struct ASTVariable
{
    ASTType type;
    ASTSourcePos pos;

    char* name;
} ASTVariable;

ASTNode*
ast_variable(char* name,
             ASTSourcePos pos);
