#include <stdio.h>
#include <stdlib.h>

#include <internal/portugol/ast.h>

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
        node->type   = type;
        node->pos    = pos;
        node->lparam = lparam;
        node->rparam = rparam;
    }

    return (ASTNode*) node;
}

Variant
ast_op_binary_execute(ASTNode* node,
                      Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    if (node->type == AST_OP_ASSIGN)
    {
        ASTBinaryOp* aux = (ASTBinaryOp*) node;

        Variant result  = ast_execute(aux->rparam, runtime);
        Variant* stored = runtime_get(runtime, ((ASTVariable*) aux->lparam)->name);
        variant_set(stored, result);

        return result;
    }

    ASTBinaryOp* aux = (ASTBinaryOp*) node;
    Variant lparam = ast_execute(aux->lparam, runtime);
    Variant rparam = ast_execute(aux->rparam, runtime);

    Variant result;
    switch (node->type)
    {
        case AST_OP_ADD:
            result = variant_op_add(lparam, rparam);
            break;
        case AST_OP_SUBTRACT:
            result = variant_op_subtract(lparam, rparam);
            break;
        case AST_OP_MULTIPLY:
            result = variant_op_multiply(lparam, rparam);
            break;
        case AST_OP_DIVIDE:
            result = variant_op_divide(lparam, rparam);
            break;
        case AST_OP_REMAINDER:
            result = variant_op_remainder(lparam, rparam);
            break;
        case AST_OP_EQUAL:
            result = variant_op_equal(lparam, rparam);
            break;
        case AST_OP_INEQUAL:
            result = variant_op_inequal(lparam, rparam);
            break;
        case AST_OP_GREATER:
            result = variant_op_greater(lparam, rparam);
            break;
        case AST_OP_GREATER_OR_EQUAL:
            result = variant_op_greater_or_equal(lparam, rparam);
            break;
        case AST_OP_LESSER:
            result = variant_op_lesser(lparam, rparam);
            break;
        case AST_OP_LESSER_OR_EQUAL:
            result = variant_op_lesser_or_equal(lparam, rparam);
            break;
        case AST_OP_AND:
            result = variant_op_and(lparam, rparam);
            break;
        case AST_OP_OR:
            result = variant_op_or(lparam, rparam);
            break;
        case AST_OP_XOR:
            result = variant_op_xor(lparam, rparam);
            break;
        default:
            break;
    }

    variant_uninit(&lparam);
    variant_uninit(&rparam);

    return result;
}

void
ast_op_binary_print(ASTNode* node,
                    int level)
{
    if (node == NULL)
        return;

    switch (node->type)
    {
        case AST_OP_ADD:
            printf("+add\n");
            ast_print(((ASTBinaryOp*) node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*) node)->rparam, level + 1);
            break;
        case AST_OP_SUBTRACT:
            printf("+subtract\n");
            ast_print(((ASTBinaryOp*) node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*) node)->rparam, level + 1);
            break;
        case AST_OP_MULTIPLY:
            printf("+multiply\n");
            ast_print(((ASTBinaryOp*) node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*) node)->rparam, level + 1);
            break;
        case AST_OP_DIVIDE:
            printf("+divide\n");
            ast_print(((ASTBinaryOp*) node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*) node)->rparam, level + 1);
            break;
        case AST_OP_REMAINDER:
            printf("+remainder\n");
            ast_print(((ASTBinaryOp*) node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*) node)->rparam, level + 1);
            break;
        case AST_OP_EQUAL:
            printf("+equal\n");
            ast_print(((ASTBinaryOp*) node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*) node)->rparam, level + 1);
            break;
        case AST_OP_INEQUAL:
            printf("+inequal\n");
            ast_print(((ASTBinaryOp*) node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*) node)->rparam, level + 1);
            break;
        case AST_OP_GREATER:
            printf("+greater\n");
            ast_print(((ASTBinaryOp*) node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*) node)->rparam, level + 1);
            break;
        case AST_OP_GREATER_OR_EQUAL:
            printf("+greater_or_equal\n");
            ast_print(((ASTBinaryOp*) node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*) node)->rparam, level + 1);
            break;
        case AST_OP_LESSER:
            printf("+lesser\n");
            ast_print(((ASTBinaryOp*) node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*) node)->rparam, level + 1);
            break;
        case AST_OP_LESSER_OR_EQUAL:
            printf("+lesser_or_equal\n");
            ast_print(((ASTBinaryOp*) node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*) node)->rparam, level + 1);
            break;
        case AST_OP_AND:
            printf("+and\n");
            ast_print(((ASTBinaryOp*) node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*) node)->rparam, level + 1);
            break;
        case AST_OP_OR:
            printf("+or\n");
            ast_print(((ASTBinaryOp*) node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*) node)->rparam, level + 1);
            break;
        case AST_OP_XOR:
            printf("+xor\n");
            ast_print(((ASTBinaryOp*) node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*) node)->rparam, level + 1);
            break;
        case AST_OP_ASSIGN:
            printf("+assign(%s)\n", ((ASTVariable*) (((ASTBinaryOp*) node)->lparam))->name);
            ast_print(((ASTBinaryOp*) node)->rparam, level + 1);
            break;
        default:
            break;
    }
}

void
ast_op_binary_destroy(ASTNode** node)
{
    if (node == NULL || *node == NULL)
        return;

    ASTBinaryOp* aux = *(ASTBinaryOp**) node;
    ast_destroy(&aux->lparam);
    ast_destroy(&aux->rparam);

    free(aux);
    *node = NULL;
}
