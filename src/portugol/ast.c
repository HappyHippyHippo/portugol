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
            return ast_constant_execute(node, runtime);
        case AST_DECL_BOOLEAN:
        case AST_DECL_INT32:
        case AST_DECL_FLOAT32:
        case AST_DECL_TEXT:
            return ast_decl_execute(node, runtime);
        case AST_VARIABLE:
            return ast_variable_execute(node, runtime);
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
            return ast_op_binary_execute(node, runtime);
        case AST_OP_POSITIVE:
        case AST_OP_NEGATIVE:
        case AST_OP_NOT:
            return ast_op_unary_execute(node, runtime);
        case AST_IF:
            return ast_if_execute(node, runtime);
        case AST_WHILE:
            return ast_while_execute(node, runtime);
        case AST_FOR:
            return ast_for_execute(node, runtime);
        case AST_SCOPE:
            return ast_scope_execute(node, runtime);
        case AST_FILE:
            return ast_file_execute(node, runtime);
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
        case AST_CONST_INT32:
        case AST_CONST_FLOAT32:
        case AST_CONST_TEXT:
            ast_constant_print(node, level + 1);                    break;
        case AST_DECL_BOOLEAN:
        case AST_DECL_INT32:
        case AST_DECL_FLOAT32:
        case AST_DECL_TEXT:
            ast_decl_print(node, level + 1);                        break;
        case AST_VARIABLE:
            ast_variable_print(node, level + 1);                    break;
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
            ast_op_binary_print(node, level + 1);                   break;
        case AST_OP_POSITIVE:
        case AST_OP_NEGATIVE:
        case AST_OP_NOT:
            ast_op_unary_print(node, level + 1);                    break;
        case AST_IF:
            ast_if_print(node, level + 1);                          break;
        case AST_WHILE:
            ast_while_print(node, level + 1);                       break;
        case AST_FOR:
            ast_for_print(node, level + 1);                         break;
        case AST_SCOPE:
            ast_scope_print(node, level + 1);                       break;
        case AST_FILE:
            ast_file_print(node, level + 1);                        break;
       default:
            printf(">> Unknown node : %d\n", node->type);
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
            ast_constant_destroy(node);                             break;
        case AST_DECL_BOOLEAN:
        case AST_DECL_INT32:
        case AST_DECL_FLOAT32:
        case AST_DECL_TEXT:
            ast_decl_destroy(node);                                 break;
        case AST_VARIABLE:
            ast_variable_destroy(node);                             break;
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
            ast_op_binary_destroy(node);                            break;
        case AST_OP_POSITIVE:
        case AST_OP_NEGATIVE:
        case AST_OP_NOT:
            ast_op_unary_destroy(node);                             break;
        case AST_IF:
            ast_if_destroy(node);                                   break;
        case AST_WHILE:
            ast_while_destroy(node);                                break;
        case AST_FOR:
            ast_for_destroy(node);                                  break;
        case AST_SCOPE:
            ast_scope_destroy(node);                                break;
        case AST_FILE:
            ast_file_destroy(node);                                 break;
       default:
            printf("trying to destroy an unknown node : %d\n", (*node)->type);
            break;
    }
}
