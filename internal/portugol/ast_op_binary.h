#pragma once

#include <portugol/ast.h>

typedef struct AST_BinaryOp
{
    AST_Type type;
    AST_SourcePos pos;

    AST_Node* lparam;
    AST_Node* rparam;
} AST_BinaryOp;

AST_Node*
ast_op_binary(AST_Node* lparam,
              AST_Node* rparam,
              AST_Type type,
              AST_SourcePos pos);

Variant
ast_op_binary_execute(AST_Node* node,
                      Runtime* runtime);

void
ast_op_binary_print(AST_Node* node,
                    int level);

void
ast_op_binary_destroy(AST_Node** node);
