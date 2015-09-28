#pragma once

#include <portugol/ast.h>

typedef struct AST_Variable
{
    AST_Type type;
    AST_SourcePos pos;

    char* name;
} AST_Variable;

AST_Node*
ast_variable(char* name,
             AST_SourcePos pos);

Variant
ast_variable_execute(AST_Node* node,
                     Runtime* runtime);

void
ast_variable_print(AST_Node* node,
                   int level,
                   char* prefix);

void
ast_variable_destroy(AST_Node** node);
