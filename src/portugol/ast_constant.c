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
        node->type = AST_CONST_BOOLEAN;
        node->pos = pos;
        node->value = variant_init_boolean(value);
    }

    return (ASTNode*)node;
}

ASTNode*
ast_int32(int32_t value,
          ASTSourcePos pos)
{
    ASTConstant* node = NULL;
    if ((node = malloc(sizeof(ASTConstant))) != NULL)
    {
        node->type = AST_CONST_INT32;
        node->pos = pos;
        node->value = variant_init_int32(value);
    }

    return (ASTNode*)node;
}

ASTNode*
ast_float32(float value,
            ASTSourcePos pos)
{
    ASTConstant* node = NULL;
    if ((node = malloc(sizeof(ASTConstant))) != NULL)
    {
        node->type = AST_CONST_FLOAT32;
        node->pos = pos;
        node->value = variant_init_float32(value);
    }

    return (ASTNode*)node;
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
        node->type = AST_CONST_TEXT;
        node->pos = pos;
        node->value = variant_init_text(value);
    }

    return (ASTNode*)node;
}
