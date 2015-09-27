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

Variant
ast_variable_execute(ASTNode* node,
                     Runtime* runtime);

void
ast_variable_print(ASTNode* node,
                   int level);

void
ast_variable_destroy(ASTNode** node);
