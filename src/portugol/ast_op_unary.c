#include <stdio.h>
#include <stdlib.h>

#include <internal/portugol/ast.h>

AST_Node*
ast_op_unary(AST_Node* param,
             AST_Type type,
             AST_SourcePos pos)
{
    if (param == NULL)
        return NULL;

    AST_UnaryOp* node = NULL;
    if ((node = malloc(sizeof(AST_UnaryOp))) != NULL)
    {
        node->type  = type;
        node->pos   = pos;
        node->param = param;
    }

    return (AST_Node*) node;
}

Variant
ast_op_unary_execute(AST_Node* node,
                     Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    AST_UnaryOp* aux = (AST_UnaryOp*) node;
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
ast_op_unary_print(AST_Node* node,
                   int level)
{
    if (node == NULL)
        return;

    switch (node->type)
    {
        case AST_OP_POSITIVE:
            printf("+positive\n");
            ast_print(((AST_UnaryOp*) node)->param, level + 1);
            break;
        case AST_OP_NEGATIVE:
            printf("+negative\n");
            ast_print(((AST_UnaryOp*) node)->param, level + 1);
            break;
        case AST_OP_NOT:
            printf("+not\n");
            ast_print(((AST_UnaryOp*) node)->param, level + 1);
            break;
        default:
            break;
    }
}

void
ast_op_unary_destroy(AST_Node** node)
{
    if (node == NULL || *node == NULL)
        return;

    AST_UnaryOp* aux = *(AST_UnaryOp**) node;
    ast_destroy(&aux->param);

    free(aux);
    *node = NULL;
}
