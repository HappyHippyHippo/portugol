#include <stdio.h>
#include <stdlib.h>

#include <internal/portugol/ast_if.h>

AST_Node*
ast_if(AST_Node* expr,
       AST_Node* chk_true,
       AST_Node* chk_false,
       AST_SourcePos pos)
{
    AST_If* node = NULL;
    if ((node = malloc(sizeof(AST_If))) != NULL)
    {
        node->type      = AST_IF;
        node->pos       = pos;

        node->expr      = expr;
        node->chk_true  = chk_true;
        node->chk_false = chk_false;
    }

    return (AST_Node*) node;
}

Variant
ast_if_execute(AST_Node* node,
               Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    AST_If* aux = (AST_If*) node;
    Variant expr = ast_execute(aux->expr, runtime);
    variant_cast(&expr, VBOOLEAN);

    runtime_push_scope_named(runtime, "se");

    if (expr.value.boolean)
        ast_execute(aux->chk_true, runtime);
    else
        if (aux->chk_false)
            ast_execute(aux->chk_false, runtime);

    return runtime_pop_scope(runtime);
}

void
ast_if_print(AST_Node* node,
             int level)
{
    if (node == NULL)
        return;

    printf("+if\n");
    ast_print(((AST_If*) node)->expr, level + 1);
    ast_print(((AST_If*) node)->chk_true, level + 1);
    if (((AST_If*) node)->chk_false)
        ast_print(((AST_If*) node)->chk_false, level + 1);
}

void
ast_if_destroy(AST_Node** node)
{
    if (node == NULL || *node == NULL)
        return;

    AST_If* aux = *(AST_If**) node;
    ast_destroy(&aux->expr);
    ast_destroy(&aux->chk_true);
    ast_destroy(&aux->chk_false);

    free(aux);
    *node = NULL;
}
