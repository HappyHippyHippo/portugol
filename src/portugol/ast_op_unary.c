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
        node->type  = type;
        node->pos   = pos;
        node->param = param;
    }

    return (ASTNode*) node;
}

Variant
ast_op_unary_execute(ASTNode* node,
                     Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    ASTUnaryOp* aux = (ASTUnaryOp*) node;
    Variant param   = ast_execute(aux->param, runtime);

    Variant result;
    switch (node->type)
    {
        case AST_OP_POSITIVE:
            result = variant_op_negative(param);
            break;
        case AST_OP_NEGATIVE:
            result = variant_op_negative(param);
            break;
        case AST_OP_NOT:
            result = variant_op_not(param);
            break;
        default:
            break;
    }

    variant_uninit(&param);

    return result;
}

void
ast_op_unary_print(ASTNode* node,
                   int level)
{
    if (node == NULL)
        return;

    switch (node->type)
    {
        case AST_OP_POSITIVE:
            printf("+positive\n");
            ast_print(((ASTUnaryOp*) node)->param, level + 1);
            break;
        case AST_OP_NEGATIVE:
            printf("+negative\n");
            ast_print(((ASTUnaryOp*) node)->param, level + 1);
            break;
        case AST_OP_NOT:
            printf("+not\n");
            ast_print(((ASTUnaryOp*) node)->param, level + 1);
            break;
        default:
            break;
    }
}

void
ast_op_unary_destroy(ASTNode** node)
{
    if (node == NULL || *node == NULL)
        return;

    ASTUnaryOp* aux = *(ASTUnaryOp**) node;
    ast_destroy(&aux->param);

    free(aux);
    *node = NULL;
}
