#include <stdio.h>
#include <stdlib.h>

#include <internal/portugol/ast.h>

AST_Node*
ast_boolean(int value,
            AST_SourcePos pos)
{
    AST_Constant* node = NULL;
    if ((node = malloc(sizeof(AST_Constant))) != NULL)
    {
        node->type  = AST_CONST_BOOLEAN;
        node->pos   = pos;
        node->value = variant_init_boolean(value);
    }

    return (AST_Node*) node;
}

AST_Node*
ast_int32(int32_t value,
          AST_SourcePos pos)
{
    AST_Constant* node = NULL;
    if ((node = malloc(sizeof(AST_Constant))) != NULL)
    {
        node->type  = AST_CONST_INT32;
        node->pos   = pos;
        node->value = variant_init_int32(value);
    }

    return (AST_Node*) node;
}

AST_Node*
ast_float32(float value,
            AST_SourcePos pos)
{
    AST_Constant* node = NULL;
    if ((node = malloc(sizeof(AST_Constant))) != NULL)
    {
        node->type  = AST_CONST_FLOAT32;
        node->pos   = pos;
        node->value = variant_init_float32(value);
    }

    return (AST_Node*) node;
}

AST_Node*
ast_text(char* value,
         AST_SourcePos pos)
{
    if (value == NULL)
        return NULL;

    AST_Constant* node = NULL;
    if ((node = malloc(sizeof(AST_Constant))) != NULL)
    {
        node->type  = AST_CONST_TEXT;
        node->pos   = pos;
        node->value = variant_init_text(value);
    }

    return (AST_Node*) node;
}

Variant
ast_constant_execute(AST_Node* node,
                     Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    return variant_copy(((AST_Constant*) node)->value);
}

void
ast_constant_print(AST_Node* node,
                   int level,
                   char* prefix)
{
    if (node == NULL)
        return;

    AST_Constant* aux = (AST_Constant*) node;

    variant_print(aux->value);
    printf("\n");
}

void
ast_constant_destroy(AST_Node** node)
{
    if (node == NULL || *node == NULL)
        return;

    AST_Constant* aux = *(AST_Constant**) node;

    variant_uninit(&aux->value);
    free(aux);

    *node = NULL;
}
