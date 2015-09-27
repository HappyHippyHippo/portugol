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
