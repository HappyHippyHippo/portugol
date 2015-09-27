#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/portugol/ast.h>

ASTNode*
ast_decl_boolean(char* name,
                 ASTNode* value,
                 ASTSourcePos pos)
{
    if (name == NULL)
        return NULL;

    ASTDecl* node;
    if ((node = malloc(sizeof(ASTDecl))) != NULL)
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

    return (ASTNode*) node;
}

ASTNode*
ast_decl_int32(char* name,
               ASTNode* value,
               ASTSourcePos pos)
{
    if (name == NULL)
        return NULL;

    ASTDecl* node;
    if ((node = malloc(sizeof(ASTDecl))) != NULL)
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

    return (ASTNode*) node;
}

ASTNode*
ast_decl_float32(char* name,
                 ASTNode* value,
                 ASTSourcePos pos)
{
    if (name == NULL)
        return NULL;

    ASTDecl* node;
    if ((node = malloc(sizeof(ASTDecl))) != NULL)
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

    return (ASTNode*) node;
}

ASTNode*
ast_decl_text(char* name,
              ASTNode* value,
              ASTSourcePos pos)
{
    if (name == NULL || value == NULL)
        return NULL;

    ASTDecl* node;
    if ((node = malloc(sizeof(ASTDecl))) != NULL)
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

    return (ASTNode*) node;
}

Variant
ast_decl_execute(ASTNode* node,
                 Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    ASTDecl* aux = (ASTDecl*) node;

    Variant value   = ast_execute(aux->value, runtime);
    Variant* stored = runtime_push(runtime, aux->name, value);
    variant_uninit(&value);

    return variant_copy(*stored);
}

void
ast_decl_print(ASTNode* node,
               int level)
{
    if (node == NULL)
        return;

    switch (node->type)
    {
        case AST_DECL_BOOLEAN:
            printf("+decl(%s : boolean)\n", ((ASTDecl*) node)->name);
            ast_print(((ASTDecl*) node)->value, level + 1);
            break;
        case AST_DECL_INT32:
            printf("+decl(%s : int32)\n", ((ASTDecl*) node)->name);
            ast_print(((ASTDecl*) node)->value, level + 1);
            break;
        case AST_DECL_FLOAT32:
            printf("+decl(%s : float32)\n", ((ASTDecl*) node)->name);
            ast_print(((ASTDecl*) node)->value, level + 1);
            break;
        case AST_DECL_TEXT:
            printf("+decl(%s : text)\n", ((ASTDecl*) node)->name);
            ast_print(((ASTDecl*) node)->value, level + 1);
            break;
        default:
            break;
    }
}

void
ast_decl_destroy(ASTNode** node)
{
    if (node == NULL || *node == NULL)
        return;

    ASTDecl* aux = *(ASTDecl**) node;
    free(aux->name);
    ast_destroy(&aux->value);

    free(aux);
    *node = NULL;
}
