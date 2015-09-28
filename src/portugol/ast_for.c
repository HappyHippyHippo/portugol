#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/portugol/ast_for.h>

AST_Node*
ast_for(char* variable,
        AST_Node* start,
        AST_Node* end,
        AST_Node* step,
        AST_Node* scope,
        AST_SourcePos pos)
{
    AST_For* node = NULL;
    if ((node = malloc(sizeof(AST_For))) != NULL)
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

    return (AST_Node*) node;
}

Variant
ast_for_execute(AST_Node* node,
                Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    AST_For* aux = (AST_For*) node;
    Variant start = ast_execute(aux->start, runtime);
    Variant end   = ast_execute(aux->end, runtime);
    Variant step  = ast_execute(aux->step, runtime);

    Variant inc = variant_op_greater(step, variant_init_int32(0));

    if (inc.value.boolean)
    {
        Variant* it = runtime_stack_push(runtime, aux->variable, start);
        Variant comp = variant_op_greater_or_equal(*it, end);

        while (comp.value.boolean == 0)
        {
            runtime_scope_push_named(runtime, 0, "para");
            ast_execute(aux->scope, runtime);
            runtime_scope_pop(runtime);

            variant_set(it, variant_op_add(*it, step));
            comp = variant_op_greater_or_equal(*it, end);
        }
    }
    else
    {
        Variant* it = runtime_stack_push(runtime, aux->variable, start);
        Variant comp = variant_op_lesser_or_equal(*it, end);

        while (comp.value.boolean == 0)
        {
            runtime_scope_push_named(runtime, 0, "para");
            ast_execute(aux->scope, runtime);
            runtime_scope_pop(runtime);

            variant_set(it, variant_op_add(*it, step));
            comp = variant_op_lesser_or_equal(*it, end);
        }
    }

    Variant it = runtime_stack_pop(runtime);
    variant_uninit(&it);

    variant_uninit(&start);
    variant_uninit(&end);
    variant_uninit(&step);

    return variant_init_int32(0);
}

void
ast_for_print(AST_Node* node,
                int level,
                char* prefix)
{
    if (node == NULL)
        return;

    printf("for(%s)\n", ((AST_For*) node)->variable);
    ast_print(((AST_For*) node)->start, level + 1, "start value > ");
    ast_print(((AST_For*) node)->end,   level + 1, "end value   > ");
    ast_print(((AST_For*) node)->step,  level + 1, "step value  > ");
    ast_print(((AST_For*) node)->scope, level + 1, "");
}

void
ast_for_destroy(AST_Node** node)
{
    if (node == NULL || *node == NULL)
        return;

    AST_For* aux = *(AST_For**) node;
    ast_destroy(&aux->start);
    ast_destroy(&aux->end);
    ast_destroy(&aux->step);
    ast_destroy(&aux->scope);

    free(aux->variable);
    free(aux);
    *node = NULL;
}
