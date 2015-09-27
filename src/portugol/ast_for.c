#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/portugol/ast_for.h>

ASTNode*
ast_for(char* variable,
        ASTNode* start,
        ASTNode* end,
        ASTNode* step,
        ASTNode* scope,
        ASTSourcePos pos)
{
    ASTFor* node = NULL;
    if ((node = malloc(sizeof(ASTFor))) != NULL)
    {
        if ((node->variable = malloc(strlen(variable) + 1)) == NULL)
        {
            free(node);
            return NULL;
        }

        node->type  = AST_FOR;
        node->pos   = pos;

        node->start = start;
        node->end   = end;
        node->step  = step;
        node->scope = scope;
        strcpy(node->variable, variable);
    }

    return (ASTNode*) node;
}

Variant
ast_for_execute(ASTNode* node,
                Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    ASTFor* aux = (ASTFor*) node;
    Variant start = ast_execute(aux->start, runtime);
    Variant end   = ast_execute(aux->end, runtime);
    Variant step  = ast_execute(aux->step, runtime);

    Variant inc = variant_op_greater(step, variant_init_int32(0));

    if (inc.value.boolean)
    {
        Variant* it = runtime_push(runtime, aux->variable, start);
        Variant comp = variant_op_greater_or_equal(*it, end);

        while (comp.value.boolean == 0)
        {
            runtime_push_scope_named(runtime, "para");
            ast_execute(aux->scope, runtime);
            runtime_pop_scope(runtime);

            variant_set(it, variant_op_add(*it, step));
            comp = variant_op_greater_or_equal(*it, end);
        }
    }
    else
    {
        Variant* it = runtime_push(runtime, aux->variable, start);
        Variant comp = variant_op_lesser_or_equal(*it, end);

        while (comp.value.boolean == 0)
        {
            runtime_push_scope_named(runtime, "para");
            ast_execute(aux->scope, runtime);
            runtime_pop_scope(runtime);

            variant_set(it, variant_op_add(*it, step));
            comp = variant_op_lesser_or_equal(*it, end);
        }
    }

    Variant it = runtime_pop(runtime);
    variant_uninit(&it);

    variant_uninit(&start);
    variant_uninit(&end);
    variant_uninit(&step);

    return variant_init_int32(0);
}

void
ast_for_print(ASTNode* node,
                int level)
{
    if (node == NULL)
        return;

    printf("+for(%s)\n", ((ASTFor*) node)->variable);
    ast_print(((ASTFor*) node)->start, level + 1);
    ast_print(((ASTFor*) node)->end,   level + 1);
    ast_print(((ASTFor*) node)->step,  level + 1);
    ast_print(((ASTFor*) node)->scope, level + 1);
}

void
ast_for_destroy(ASTNode** node)
{
    if (node == NULL || *node == NULL)
        return;

    ASTFor* aux = *(ASTFor**) node;
    ast_destroy(&aux->start);
    ast_destroy(&aux->end);
    ast_destroy(&aux->step);
    ast_destroy(&aux->scope);

    free(aux->variable);
    free(aux);
    *node = NULL;
}
