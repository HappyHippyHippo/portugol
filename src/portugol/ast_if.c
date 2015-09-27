#include <stdio.h>
#include <stdlib.h>

#include <internal/portugol/ast_if.h>

ASTNode*
ast_if(ASTNode* expr,
       ASTNode* chk_true,
       ASTNode* chk_false,
       ASTSourcePos pos)
{
    ASTIf* node = NULL;
    if ((node = malloc(sizeof(ASTIf))) != NULL)
    {
        node->type      = AST_IF;
        node->pos       = pos;

        node->expr      = expr;
        node->chk_true  = chk_true;
        node->chk_false = chk_false;
    }

    return (ASTNode*) node;
}

Variant
ast_if_execute(ASTNode* node,
               Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    ASTIf* aux = (ASTIf*) node;
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
ast_if_print(ASTNode* node,
             int level)
{
    if (node == NULL)
        return;

    printf("+if\n");
    ast_print(((ASTIf*) node)->expr, level + 1);
    ast_print(((ASTIf*) node)->chk_true, level + 1);
    if (((ASTIf*) node)->chk_false)
        ast_print(((ASTIf*) node)->chk_false, level + 1);
}

void
ast_if_destroy(ASTNode** node)
{
    if (node == NULL || *node == NULL)
        return;

    ASTIf* aux = *(ASTIf**) node;
    ast_destroy(&aux->expr);
    ast_destroy(&aux->chk_true);
    ast_destroy(&aux->chk_false);

    free(aux);
    *node = NULL;
}
