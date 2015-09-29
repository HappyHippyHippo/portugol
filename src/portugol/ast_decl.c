#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/portugol/ast.h>

AST_Node*
ast_decl_boolean(char* name,
                 AST_Node* value,
                 AST_SourcePos pos)
{
    if (name == NULL)
        return NULL;

    AST_Decl* node;
    if ((node = malloc(sizeof(AST_Decl))) != NULL)
    {
        if ((node->name = malloc(strlen(name) + 1)) == NULL)
        {
            free(node);
            return NULL;
        }

        node->type  = AST_DECL_BOOLEAN;
        node->pos   = pos;
        node->value = value;
        strcpy(node->name, name);
    }

    return (AST_Node*) node;
}

AST_Node*
ast_decl_int32(char* name,
               AST_Node* value,
               AST_SourcePos pos)
{
    if (name == NULL)
        return NULL;

    AST_Decl* node;
    if ((node = malloc(sizeof(AST_Decl))) != NULL)
    {
        if ((node->name = malloc(strlen(name) + 1)) == NULL)
        {
            free(node);
            return NULL;
        }

        node->type  = AST_DECL_INT32;
        node->pos   = pos;
        node->value = value;
        strcpy(node->name, name);
    }

    return (AST_Node*) node;
}

AST_Node*
ast_decl_float32(char* name,
                 AST_Node* value,
                 AST_SourcePos pos)
{
    if (name == NULL)
        return NULL;

    AST_Decl* node;
    if ((node = malloc(sizeof(AST_Decl))) != NULL)
    {
        if ((node->name = malloc(strlen(name) + 1)) == NULL)
        {
            free(node);
            return NULL;
        }

        node->type  = AST_DECL_FLOAT32;
        node->pos   = pos;
        node->value = value;
        strcpy(node->name, name);
    }

    return (AST_Node*) node;
}

AST_Node*
ast_decl_text(char* name,
              AST_Node* value,
              AST_SourcePos pos)
{
    if (name == NULL || value == NULL)
        return NULL;

    AST_Decl* node;
    if ((node = malloc(sizeof(AST_Decl))) != NULL)
    {
        if ((node->name = malloc(strlen(name) + 1)) == NULL)
        {
            free(node);
            return NULL;
        }

        node->type  = AST_DECL_TEXT;
        node->pos   = pos;
        node->value = value;
        strcpy(node->name, name);
    }

    return (AST_Node*) node;
}

Variant
ast_decl_execute(AST_Node* node,
                 Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    AST_Decl* aux = (AST_Decl*) node;

    Variant value   = ast_execute(aux->value, runtime);
    Variant* stored = runtime_stack_push(runtime, aux->name, value);
    variant_uninit(&value);

    return variant_copy(*stored);
}

void
ast_decl_print(AST_Node* node,
               int level,
               char* prefix)
{
    if (node == NULL)
        return;

    AST_Decl* aux = (AST_Decl*) node;

    switch (aux->type)
    {
        case AST_DECL_BOOLEAN:
            printf("decl(%s : boolean)\n", aux->name);
            ast_print(aux->value, level + 1, "default value >> ");
            break;
        case AST_DECL_INT32:
            printf("decl(%s : int32)\n", aux->name);
            ast_print(aux->value, level + 1, "default value >> ");
            break;
        case AST_DECL_FLOAT32:
            printf("decl(%s : float32)\n", aux->name);
            ast_print(aux->value, level + 1, "default value >> ");
            break;
        case AST_DECL_TEXT:
            printf("decl(%s : text)\n", aux->name);
            ast_print(aux->value, level + 1, "default value >> ");
            break;
        default:
            break;
    }
}

void
ast_decl_destroy(AST_Node** node)
{
    if (node == NULL || *node == NULL)
        return;

    AST_Decl* aux = *(AST_Decl**) node;

    ast_destroy(&aux->value);
    free(aux->name);
    free(aux);

    *node = NULL;
}
