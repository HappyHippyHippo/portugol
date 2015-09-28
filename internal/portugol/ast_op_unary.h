#pragma once

#include <portugol/ast.h>

typedef struct AST_UnaryOp
{
    AST_Type type;
    AST_SourcePos pos;

    AST_Node* param;
} AST_UnaryOp;

AST_Node*
ast_op_unary(AST_Node* param,
             AST_Type type,
             AST_SourcePos pos);

Variant
ast_op_unary_execute(AST_Node* node,
                     Runtime* runtime);

void
ast_op_unary_print(AST_Node* node,
                   int level);

void
ast_op_unary_destroy(AST_Node** node);
