#include <stdio.h>
#include <stdlib.h>

#include <internal/portugol/ast.h>

Variant
ast_execute(ASTNode* node,
            Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    switch (node->type)
    {
        case AST_CONST_BOOLEAN:
        case AST_CONST_INT32:
        case AST_CONST_FLOAT32:
        case AST_CONST_TEXT:
        {
            ASTConstant* aux = (ASTConstant*)node;
            return variant_copy(aux->value);
        }
        case AST_DECL_BOOLEAN:
        case AST_DECL_INT32:
        case AST_DECL_FLOAT32:
        case AST_DECL_TEXT:
        {
            ASTDecl* aux = (ASTDecl*)node;

            Variant value = ast_execute(aux->value, runtime);
            Variant* stored = runtime_push(runtime, aux->name, value);
            variant_uninit(&value);

            return variant_copy(*stored);
        }
        case AST_VARIABLE:
        {
            ASTVariable* aux = (ASTVariable*)node;
            return variant_copy(*runtime_get(runtime, aux->name));
        }
        case AST_OP_ADD:
        {
            ASTBinaryOp* aux = (ASTBinaryOp*)node;

            Variant lparam = ast_execute(aux->lparam, runtime);
            Variant rparam = ast_execute(aux->rparam, runtime);
            Variant result = variant_op_add(lparam, rparam);
            variant_uninit(&lparam);
            variant_uninit(&rparam);

            return result;
        }
        case AST_OP_SUBTRACT:
        {
            ASTBinaryOp* aux = (ASTBinaryOp*)node;

            Variant lparam = ast_execute(aux->lparam, runtime);
            Variant rparam = ast_execute(aux->rparam, runtime);
            Variant result = variant_op_subtract(lparam, rparam);
            variant_uninit(&lparam);
            variant_uninit(&rparam);

            return result;
        }
        case AST_OP_MULTIPLY:
        {
            ASTBinaryOp* aux = (ASTBinaryOp*)node;

            Variant lparam = ast_execute(aux->lparam, runtime);
            Variant rparam = ast_execute(aux->rparam, runtime);
            Variant result = variant_op_multiply(lparam, rparam);
            variant_uninit(&lparam);
            variant_uninit(&rparam);

            return result;
        }
        case AST_OP_DIVIDE:
        {
            ASTBinaryOp* aux = (ASTBinaryOp*)node;

            Variant lparam = ast_execute(aux->lparam, runtime);
            Variant rparam = ast_execute(aux->rparam, runtime);
            Variant result = variant_op_divide(lparam, rparam);
            variant_uninit(&lparam);
            variant_uninit(&rparam);

            return result;
        }
        case AST_OP_REMAINDER:
        {
            ASTBinaryOp* aux = (ASTBinaryOp*)node;

            Variant lparam = ast_execute(aux->lparam, runtime);
            Variant rparam = ast_execute(aux->rparam, runtime);
            Variant result = variant_op_remainder(lparam, rparam);
            variant_uninit(&lparam);
            variant_uninit(&rparam);

            return result;
        }
        case AST_OP_EQUAL:
        {
            ASTBinaryOp* aux = (ASTBinaryOp*)node;

            Variant lparam = ast_execute(aux->lparam, runtime);
            Variant rparam = ast_execute(aux->rparam, runtime);
            Variant result = variant_op_equal(lparam, rparam);
            variant_uninit(&lparam);
            variant_uninit(&rparam);

            return result;
        }
        case AST_OP_INEQUAL:
        {
            ASTBinaryOp* aux = (ASTBinaryOp*)node;

            Variant lparam = ast_execute(aux->lparam, runtime);
            Variant rparam = ast_execute(aux->rparam, runtime);
            Variant result = variant_op_inequal(lparam, rparam);
            variant_uninit(&lparam);
            variant_uninit(&rparam);

            return result;
        }
        case AST_OP_GREATER:
        {
            ASTBinaryOp* aux = (ASTBinaryOp*)node;

            Variant lparam = ast_execute(aux->lparam, runtime);
            Variant rparam = ast_execute(aux->rparam, runtime);
            Variant result = variant_op_greater(lparam, rparam);
            variant_uninit(&lparam);
            variant_uninit(&rparam);

            return result;
        }
        case AST_OP_GREATER_OR_EQUAL:
        {
            ASTBinaryOp* aux = (ASTBinaryOp*)node;

            Variant lparam = ast_execute(aux->lparam, runtime);
            Variant rparam = ast_execute(aux->rparam, runtime);
            Variant result = variant_op_greater_or_equal(lparam, rparam);
            variant_uninit(&lparam);
            variant_uninit(&rparam);

            return result;
        }
        case AST_OP_LESSER:
        {
            ASTBinaryOp* aux = (ASTBinaryOp*)node;

            Variant lparam = ast_execute(aux->lparam, runtime);
            Variant rparam = ast_execute(aux->rparam, runtime);
            Variant result = variant_op_lesser(lparam, rparam);
            variant_uninit(&lparam);
            variant_uninit(&rparam);

            return result;
        }
        case AST_OP_LESSER_OR_EQUAL:
        {
            ASTBinaryOp* aux = (ASTBinaryOp*)node;

            Variant lparam = ast_execute(aux->lparam, runtime);
            Variant rparam = ast_execute(aux->rparam, runtime);
            Variant result = variant_op_lesser_or_equal(lparam, rparam);
            variant_uninit(&lparam);
            variant_uninit(&rparam);

            return result;
        }
        case AST_OP_AND:
        {
            ASTBinaryOp* aux = (ASTBinaryOp*)node;

            Variant lparam = ast_execute(aux->lparam, runtime);
            Variant rparam = ast_execute(aux->rparam, runtime);
            Variant result = variant_op_and(lparam, rparam);
            variant_uninit(&lparam);
            variant_uninit(&rparam);

            return result;
        }
        case AST_OP_OR:
        {
            ASTBinaryOp* aux = (ASTBinaryOp*)node;

            Variant lparam = ast_execute(aux->lparam, runtime);
            Variant rparam = ast_execute(aux->rparam, runtime);
            Variant result = variant_op_or(lparam, rparam);
            variant_uninit(&lparam);
            variant_uninit(&rparam);

            return result;
        }
        case AST_OP_XOR:
        {
            ASTBinaryOp* aux = (ASTBinaryOp*)node;

            Variant lparam = ast_execute(aux->lparam, runtime);
            Variant rparam = ast_execute(aux->rparam, runtime);
            Variant result = variant_op_xor(lparam, rparam);
            variant_uninit(&lparam);
            variant_uninit(&rparam);

            return result;
        }
        case AST_OP_POSITIVE:
        {
            ASTUnaryOp* aux = (ASTUnaryOp*)node;

            Variant param = ast_execute(aux->param, runtime);
            Variant result = variant_op_negative(param);
            variant_uninit(&param);

            return result;
        }
        case AST_OP_NEGATIVE:
        {
            ASTUnaryOp* aux = (ASTUnaryOp*)node;

            Variant param = ast_execute(aux->param, runtime);
            Variant result = variant_op_negative(param);
            variant_uninit(&param);

            return result;

        }
        case AST_OP_NOT:
        {
            ASTUnaryOp* aux = (ASTUnaryOp*)node;

            Variant param = ast_execute(aux->param, runtime);
            Variant result = variant_op_not(param);
            variant_uninit(&param);

            return result;
        }
        case AST_OP_ASSIGN:
        {
            ASTBinaryOp* aux = (ASTBinaryOp*)node;

            Variant result = ast_execute(aux->rparam, runtime);
            Variant* stored = runtime_get(runtime, ((ASTVariable*) aux->lparam)->name);
            variant_set(stored, result);

            return result;
        }
        case AST_FILE:
        {
            ASTScope* aux = (ASTScope*)node;
            for (int idx = 0; idx < aux->instr.count; ++idx)
            {
                Variant result = ast_execute(aux->instr.list[idx], runtime);
                switch (result.type)
                {
                    case VBOOLEAN:
                        printf("instruction %3d result >> %d\n", idx, result.value.boolean);
                        break;
                    case VINT32:
                        printf("instruction %3d result >> %d\n", idx, result.value.int32);
                        break;
                    case VFLOAT32:
                        printf("instruction %3d result >> %f\n", idx, result.value.float32);
                        break;
                    case VTEXT:
                        printf("instruction %3d result >> %s\n", idx, result.value.text);
                        break;
                }
                variant_uninit(&result);
            }
            return variant_init_int32(0);
        }
       default:
            printf("trying to execute an unknown node : %d\n", node->type);
            break;
    }

    return variant_init_int32(0);
}

void
ast_print(ASTNode* node,
          int level)
{
    if (node == NULL)
        return;

    for (int i = 0; i < level; ++i)
        printf("  ");

    switch (node->type)
    {
        case AST_CONST_BOOLEAN:
            printf("boolean(%d)\n", ((ASTConstant*)node)->value.value.boolean);
            break;
        case AST_CONST_INT32:
            printf("int32(%d)\n", ((ASTConstant*)node)->value.value.int32);
            break;
        case AST_CONST_FLOAT32:
            printf("float32(%f)\n", ((ASTConstant*)node)->value.value.float32);
            break;
        case AST_CONST_TEXT:
            printf("text(%s)\n", ((ASTConstant*)node)->value.value.text);
            break;
        case AST_DECL_BOOLEAN:
            printf("+decl(%s : boolean)\n", ((ASTDecl*)node)->name);
            ast_print(((ASTDecl*)node)->value, level + 1);
            break;
        case AST_DECL_INT32:
            printf("+decl(%s : int32)\n", ((ASTDecl*)node)->name);
            ast_print(((ASTDecl*)node)->value, level + 1);
            break;
        case AST_DECL_FLOAT32:
            printf("+decl(%s : float32)\n", ((ASTDecl*)node)->name);
            ast_print(((ASTDecl*)node)->value, level + 1);
            break;
        case AST_DECL_TEXT:
            printf("+decl(%s : text)\n", ((ASTDecl*)node)->name);
            ast_print(((ASTDecl*)node)->value, level + 1);
            break;
        case AST_VARIABLE:
            printf("var(%s)\n", ((ASTDecl*)node)->name);
            break;
        case AST_OP_ADD:
            printf("+add\n");
            ast_print(((ASTBinaryOp*)node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*)node)->rparam, level + 1);
            break;
        case AST_OP_SUBTRACT:
            printf("+subtract\n");
            ast_print(((ASTBinaryOp*)node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*)node)->rparam, level + 1);
            break;
        case AST_OP_MULTIPLY:
            printf("+multiply\n");
            ast_print(((ASTBinaryOp*)node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*)node)->rparam, level + 1);
            break;
        case AST_OP_DIVIDE:
            printf("+divide\n");
            ast_print(((ASTBinaryOp*)node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*)node)->rparam, level + 1);
            break;
        case AST_OP_REMAINDER:
            printf("+remainder\n");
            ast_print(((ASTBinaryOp*)node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*)node)->rparam, level + 1);
            break;
        case AST_OP_EQUAL:
            printf("+equal\n");
            ast_print(((ASTBinaryOp*)node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*)node)->rparam, level + 1);
            break;
        case AST_OP_INEQUAL:
            printf("+inequal\n");
            ast_print(((ASTBinaryOp*)node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*)node)->rparam, level + 1);
            break;
        case AST_OP_GREATER:
            printf("+greater\n");
            ast_print(((ASTBinaryOp*)node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*)node)->rparam, level + 1);
            break;
        case AST_OP_GREATER_OR_EQUAL:
            printf("+greater_or_equal\n");
            ast_print(((ASTBinaryOp*)node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*)node)->rparam, level + 1);
            break;
        case AST_OP_LESSER:
            printf("+lesser\n");
            ast_print(((ASTBinaryOp*)node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*)node)->rparam, level + 1);
            break;
        case AST_OP_LESSER_OR_EQUAL:
            printf("+lesser_or_equal\n");
            ast_print(((ASTBinaryOp*)node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*)node)->rparam, level + 1);
            break;
        case AST_OP_AND:
            printf("+and\n");
            ast_print(((ASTBinaryOp*)node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*)node)->rparam, level + 1);
            break;
        case AST_OP_OR:
            printf("+or\n");
            ast_print(((ASTBinaryOp*)node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*)node)->rparam, level + 1);
            break;
        case AST_OP_XOR:
            printf("+xor\n");
            ast_print(((ASTBinaryOp*)node)->lparam, level + 1);
            ast_print(((ASTBinaryOp*)node)->rparam, level + 1);
            break;
        case AST_OP_POSITIVE:
            printf("+positive\n");
            ast_print(((ASTUnaryOp*)node)->param, level + 1);
            break;
        case AST_OP_NEGATIVE:
            printf("+negative\n");
            ast_print(((ASTUnaryOp*)node)->param, level + 1);
            break;
        case AST_OP_NOT:
            printf("+not\n");
            ast_print(((ASTUnaryOp*)node)->param, level + 1);
            break;
        case AST_OP_ASSIGN:
            printf("+assign(%s)\n", ((ASTVariable*) (((ASTBinaryOp*)node)->lparam))->name);
            ast_print(((ASTBinaryOp*)node)->rparam, level + 1);
            break;
        case AST_FILE:
        {
            printf("+file\n");
            for (size_t idx = 0; idx < ((ASTScope*)node)->instr.count; ++idx)
                ast_print(((ASTScope*)node)->instr.list[idx], level + 1);
            break;
        }
       default:
            printf(">> Unknown node <<\n");
            break;
    }
}

void
ast_destroy(ASTNode** node)
{
    if (node == NULL || *node == NULL)
        return;

    switch ((*node)->type)
    {
        case AST_CONST_BOOLEAN:
        case AST_CONST_INT32:
        case AST_CONST_FLOAT32:
        case AST_CONST_TEXT:
        {
            ASTConstant* aux = *(ASTConstant**)node;
            variant_uninit(&aux->value);

            free(aux);
            *node = NULL;
            break;
        }
        case AST_OP_ADD:
        case AST_OP_SUBTRACT:
        case AST_OP_MULTIPLY:
        case AST_OP_DIVIDE:
        case AST_OP_REMAINDER:
        case AST_OP_EQUAL:
        case AST_OP_INEQUAL:
        case AST_OP_GREATER:
        case AST_OP_GREATER_OR_EQUAL:
        case AST_OP_LESSER:
        case AST_OP_LESSER_OR_EQUAL:
        case AST_OP_AND:
        case AST_OP_OR:
        case AST_OP_XOR:
        case AST_OP_ASSIGN:
        {
            ASTBinaryOp* aux = *(ASTBinaryOp**)node;
            ast_destroy(&aux->lparam);
            ast_destroy(&aux->rparam);

            free(aux);
            *node = NULL;
            break;
        }
        case AST_OP_POSITIVE:
        case AST_OP_NEGATIVE:
        case AST_OP_NOT:
        {
            ASTUnaryOp* aux = *(ASTUnaryOp**)node;
            ast_destroy(&aux->param);

            free(aux);
            *node = NULL;
            break;
        }
        case AST_DECL_BOOLEAN:
        case AST_DECL_INT32:
        case AST_DECL_FLOAT32:
        case AST_DECL_TEXT:
        {
            ASTDecl* aux = *(ASTDecl**)node;
            free(aux->name);
            ast_destroy(&aux->value);

            free(aux);
            *node = NULL;
            break;
        }
        case AST_VARIABLE:
        {
            ASTVariable* aux = *(ASTVariable**)node;
            free(aux->name);
            free(aux);
            *node = NULL;
            break;
        }
        case AST_FILE:
        {
            ASTScope* aux = *(ASTScope**)node;
            for (size_t idx = 0; idx < aux->instr.count; ++idx)
                ast_destroy(&aux->instr.list[idx]);

            free(aux->instr.list);
            free(aux);
            *node = NULL;
            break;
        }
       default:
            printf("trying toestroy an unknown node\n");
            break;
    }
}
