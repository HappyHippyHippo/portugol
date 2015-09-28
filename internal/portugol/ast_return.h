#pragma once

#include <portugol/ast.h>

typedef struct AST_Return
{
    AST_Type type;
    AST_SourcePos pos;

    AST_Node* expr;
} AST_Return;

AST_Node*
ast_return(AST_Node* expr,
           AST_SourcePos pos);

Variant
ast_return_execute(AST_Node* node,
                   Runtime* runtime);

void
ast_return_print(AST_Node* node,
                 int level);

void
ast_return_destroy(AST_Node** node);
