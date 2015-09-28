#pragma once

#include <portugol/ast.h>

typedef struct AST_For
{
    AST_Type type;
    AST_SourcePos pos;

    char* variable;
    AST_Node* start;
    AST_Node* end;
    AST_Node* step;

    AST_Node* scope;
} AST_For;

AST_Node*
ast_for(char* variable,
        AST_Node* start,
        AST_Node* end,
        AST_Node* step,
        AST_Node* scope,
        AST_SourcePos pos);

Variant
ast_for_execute(AST_Node* node,
                Runtime* runtime);

void
ast_for_print(AST_Node* node,
              int level);

void
ast_for_destroy(AST_Node** node);
