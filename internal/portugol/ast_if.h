#pragma once

#include <portugol/ast.h>

typedef struct AST_If
{
    AST_Type type;
    AST_SourcePos pos;

    AST_Node* expr;

    AST_Node* chk_true;
    AST_Node* chk_false;
} AST_If;

AST_Node*
ast_if(AST_Node* expr,
       AST_Node* chk_true,
       AST_Node* chk_false,
       AST_SourcePos pos);

Variant
ast_if_execute(AST_Node* node,
               Runtime* runtime);

void
ast_if_print(AST_Node* node,
             int level);

void
ast_if_destroy(AST_Node** node);
