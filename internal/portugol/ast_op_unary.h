#pragma once

#include <portugol/ast.h>

typedef struct ASTUnaryOp
{
    ASTType type;
    ASTSourcePos pos;

    ASTNode* param;
} ASTUnaryOp;

ASTNode*
ast_op_unary(ASTNode* param,
             ASTType type,
             ASTSourcePos pos);

Variant
ast_op_unary_execute(ASTNode* node,
                     Runtime* runtime);

void
ast_op_unary_print(ASTNode* node,
                   int level);

void
ast_op_unary_destroy(ASTNode** node);
