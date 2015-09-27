#pragma once

#include <portugol/ast.h>

typedef struct ASTBinaryOp
{
    ASTType type;
    ASTSourcePos pos;

    ASTNode* lparam;
    ASTNode* rparam;
} ASTBinaryOp;

ASTNode*
ast_op_binary(ASTNode* lparam,
              ASTNode* rparam,
              ASTType type,
              ASTSourcePos pos);

Variant
ast_op_binary_execute(ASTNode* node,
                      Runtime* runtime);

void
ast_op_binary_print(ASTNode* node,
                    int level);

void
ast_op_binary_destroy(ASTNode** node);
