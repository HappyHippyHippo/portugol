#include <stdio.h>
#include <stdlib.h>

#include <internal/portugol/ast.h>

ASTNode*
ast_op_unary(ASTNode* param,
             ASTType type,
             ASTSourcePos pos)
{
    if (param == NULL)
        return NULL;

    ASTUnaryOp* node = NULL;
    if ((node = malloc(sizeof(ASTUnaryOp))) != NULL)
    {
        node->type = type;
        node->pos = pos;
        node->param = param;
    }

    return (ASTNode*)node;
}

ASTNode*
ast_op_binary(ASTNode* lparam,
              ASTNode* rparam,
              ASTType type,
              ASTSourcePos pos)
{
    if (lparam == NULL || rparam == NULL)
        return NULL;

    ASTBinaryOp* node = NULL;
    if ((node = malloc(sizeof(ASTBinaryOp))) != NULL)
    {
        node->type = type;
        node->pos = pos;
        node->lparam = lparam;
        node->rparam = rparam;
    }

    return (ASTNode*)node;
}
