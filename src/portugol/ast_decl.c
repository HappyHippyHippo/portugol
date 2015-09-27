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

        node->type = AST_DECL_BOOLEAN;
        node->pos = pos;
        strcpy(node->name, name);
        node->value = value;
    }

    return (ASTNode*)node;
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

        node->type = AST_DECL_INT32;
        node->pos = pos;
        strcpy(node->name, name);
        node->value = value;
    }

    return (ASTNode*)node;
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

        node->type = AST_DECL_FLOAT32;
        node->pos = pos;
        strcpy(node->name, name);
        node->value = value;
    }

    return (ASTNode*)node;
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

        node->type = AST_DECL_TEXT;
        node->pos = pos;
        strcpy(node->name, name);
        node->value = value;
    }

    return (ASTNode*)node;
}
