#include <stdio.h>
#include <stdlib.h>

#include <internal/portugol/ast_while.h>

ASTNode*
ast_while(ASTNode* expr,
          ASTNode* scope,
          ASTSourcePos pos)
{
    ASTWhile* node = NULL;
    if ((node = malloc(sizeof(ASTWhile))) != NULL)
    {
        node->type  = AST_WHILE;
        node->pos   = pos;

        node->expr  = expr;
        node->scope = scope;
    }

    return (ASTNode*) node;
}

Variant
ast_while_execute(ASTNode* node,
                  Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    ASTWhile* aux = (ASTWhile*) node;

    Variant expr = ast_execute(aux->expr, runtime);
    variant_cast(&expr, VBOOLEAN);
    while (expr.value.boolean)
    {
        runtime_push_scope_named(runtime, "enquanto");
        ast_execute(aux->scope, runtime);
        runtime_pop_scope(runtime);

        expr = ast_execute(aux->expr, runtime);
        variant_cast(&expr, VBOOLEAN);
    }

    return expr;
}

void
ast_while_print(ASTNode* node,
                int level)
{
    if (node == NULL)
        return;

    printf("+while\n");
    ast_print(((ASTWhile*) node)->expr, level + 1);
    ast_print(((ASTWhile*) node)->scope, level + 1);
}

void
ast_while_destroy(ASTNode** node)
{
    if (node == NULL || *node == NULL)
        return;

    ASTWhile* aux = *(ASTWhile**) node;
    ast_destroy(&aux->expr);
    ast_destroy(&aux->scope);

    free(aux);
    *node = NULL;
}
