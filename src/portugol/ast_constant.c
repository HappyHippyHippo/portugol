#include <stdio.h>
#include <stdlib.h>

#include <internal/portugol/ast.h>

ASTNode*
ast_boolean(int value,
            ASTSourcePos pos)
{
    ASTConstant* node = NULL;
    if ((node = malloc(sizeof(ASTConstant))) != NULL)
    {
        node->type  = AST_CONST_BOOLEAN;
        node->pos   = pos;
        node->value = variant_init_boolean(value);
    }

    return (ASTNode*) node;
}

ASTNode*
ast_int32(int32_t value,
          ASTSourcePos pos)
{
    ASTConstant* node = NULL;
    if ((node = malloc(sizeof(ASTConstant))) != NULL)
    {
        node->type  = AST_CONST_INT32;
        node->pos   = pos;
        node->value = variant_init_int32(value);
    }

    return (ASTNode*) node;
}

ASTNode*
ast_float32(float value,
            ASTSourcePos pos)
{
    ASTConstant* node = NULL;
    if ((node = malloc(sizeof(ASTConstant))) != NULL)
    {
        node->type  = AST_CONST_FLOAT32;
        node->pos   = pos;
        node->value = variant_init_float32(value);
    }

    return (ASTNode*) node;
}

ASTNode*
ast_text(char* value,
         ASTSourcePos pos)
{
    if (value == NULL)
        return NULL;

    ASTConstant* node = NULL;
    if ((node = malloc(sizeof(ASTConstant))) != NULL)
    {
        node->type  = AST_CONST_TEXT;
        node->pos   = pos;
        node->value = variant_init_text(value);
    }

    return (ASTNode*) node;
}

Variant
ast_constant_execute(ASTNode* node,
                     Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    return variant_copy(((ASTConstant*) node)->value);
}

void
ast_constant_print(ASTNode* node,
                   int level)
{
    if (node == NULL)
        return;

    switch (node->type)
    {
        case AST_CONST_BOOLEAN:
            printf("boolean(%d)\n", ((ASTConstant*) node)->value.value.boolean);
            break;
        case AST_CONST_INT32:
            printf("int32(%d)\n",   ((ASTConstant*) node)->value.value.int32);
            break;
        case AST_CONST_FLOAT32:
            printf("float32(%f)\n", ((ASTConstant*) node)->value.value.float32);
            break;
        case AST_CONST_TEXT:
            printf("text(%s)\n",    ((ASTConstant*) node)->value.value.text);
            break;
        default:
            break;
    }
}

void
ast_constant_destroy(ASTNode** node)
{
    if (node == NULL || *node == NULL)
        return;

    ASTConstant* aux = *(ASTConstant**) node;
    variant_uninit(&aux->value);

    free(aux);
    *node = NULL;
}
