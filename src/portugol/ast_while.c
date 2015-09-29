#include <stdio.h>
#include <stdlib.h>

#include <internal/portugol/ast_while.h>

AST_Node*
ast_while(AST_Node* expr,
          AST_Node* scope,
          AST_SourcePos pos)
{
    AST_While* node = NULL;
    if ((node = malloc(sizeof(AST_While))) != NULL)
    {
        node->type  = AST_WHILE;
        node->pos   = pos;

        node->expr  = expr;
        node->scope = scope;
    }

    return (AST_Node*) node;
}

Variant
ast_while_execute(AST_Node* node,
                  Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    AST_While* aux = (AST_While*) node;

    Variant expr = ast_execute(aux->expr, runtime);
    variant_cast(&expr, VBOOLEAN);
    while (expr.value.boolean)
    {
        runtime_scope_push_named(runtime, 0, "enquanto");
        ast_execute(aux->scope, runtime);
        runtime_scope_pop(runtime);

        expr = ast_execute(aux->expr, runtime);
        variant_cast(&expr, VBOOLEAN);
    }

    return expr;
}

void
ast_while_print(AST_Node* node,
                int level,
                char* prefif)
{
    if (node == NULL)
        return;

    AST_While* aux = (AST_While*) node;

    printf("while\n");
    ast_print(aux->expr, level + 1, "comp > ");
    ast_print(aux->scope, level + 1, "");
}

void
ast_while_destroy(AST_Node** node)
{
    if (node == NULL || *node == NULL)
        return;

    AST_While* aux = *(AST_While**) node;

    ast_destroy(&aux->expr);
    ast_destroy(&aux->scope);
    free(aux);

    *node = NULL;
}
