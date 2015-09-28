#include <stdio.h>
#include <stdlib.h>

#include <internal/portugol/ast.h>

AST_Node*
ast_return(AST_Node* expr,
           AST_SourcePos pos)
{
    if (expr == NULL)
        return NULL;

    AST_Return* node;
    if ((node = malloc(sizeof(AST_Return))) != NULL)
    {
        node->type = AST_RETURN;
        node->pos  = pos;
        node->expr = expr;
    }

    return (AST_Node*) node;
}

Variant
ast_return_execute(AST_Node* node,
                   Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    return ast_execute(((AST_Return*) node)->expr, runtime);
}

void
ast_return_print(AST_Node* node,
                 int level)
{
    if (node == NULL)
        return;

    printf("return\n");
    ast_print(((AST_Return*) node)->expr, level + 1);
}

void
ast_return_destroy(AST_Node** node)
{
    if (node == NULL || *node == NULL)
        return;

    AST_Return* aux = *(AST_Return**) node;
    ast_destroy(&aux->expr);

    free(aux);
    *node = NULL;
}
