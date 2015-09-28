#pragma once

#include <portugol/ast.h>

typedef struct AST_While
{
    AST_Type type;
    AST_SourcePos pos;

    AST_Node* expr;

    AST_Node* scope;
} AST_While;

AST_Node*
ast_while(AST_Node* expr,
          AST_Node* scope,
          AST_SourcePos pos);

Variant
ast_while_execute(AST_Node* node,
                  Runtime* runtime);

void
ast_while_print(AST_Node* node,
                int level,
                char* prefix);

void
ast_while_destroy(AST_Node** node);
