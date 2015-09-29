#include <stdio.h>
#include <stdlib.h>

#include <internal/portugol/ast.h>

AST_Node*
ast_scope(AST_SourcePos pos)
{
    AST_Scope* node = NULL;

    if ((node = malloc(sizeof(AST_Scope))) != NULL)
    {
        node->type        = AST_SCOPE;
        node->pos         = pos;
        node->inst.size  = 10;
        node->inst.count = 0;
        if ((node->inst.list = malloc(sizeof(AST_Scope) * node->inst.size)) == NULL)
        {
            free(node);
            node = NULL;
        }
    }

    return (AST_Node*) node;
}

AST_Node*
ast_scope_push(AST_Node* scope,
               AST_Node* inst)
{
    if (scope == NULL || inst == NULL)
        return scope;

    AST_Scope* aux = (AST_Scope*)scope;
    if (aux->inst.size == aux->inst.count)
    {
        AST_Node** tmp = realloc(aux->inst.list, sizeof(AST_Node*) * (aux->inst.size + 10));
        if (!tmp)
            return NULL;

        aux->inst.size += 10;
        aux->inst.list = tmp;
    }

    aux->inst.list[aux->inst.count] = inst;
    ++aux->inst.count;

    scope->pos.lend = inst->pos.lend;
    scope->pos.cend = inst->pos.cend;

    return scope;
}

Variant
ast_scope_execute(AST_Node* node,
                  Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    AST_Scope* aux = (AST_Scope*) node;

    for (int idx = 0; idx < aux->inst.count && !runtime_scope_is_returning(runtime); ++idx)
    {
        Variant result = ast_execute(aux->inst.list[idx], runtime);
        variant_uninit(&result);
    }

    return variant_init_int32(0);
}

void
ast_scope_print(AST_Node* node,
                int level,
                char* prefix)
{
    if (node == NULL)
        return;

    AST_Scope* aux = (AST_Scope*) node;

    printf("scope\n");
    for (size_t idx = 0; idx < aux->inst.count; ++idx)
        ast_print(aux->inst.list[idx], level + 1, "");
}

void
ast_scope_destroy(AST_Node** node)
{
    if (node == NULL || *node == NULL)
        return;

    AST_Scope* aux = *(AST_Scope**) node;

    for (size_t idx = 0; idx < aux->inst.count; ++idx)
        ast_destroy(&aux->inst.list[idx]);
    free(aux->inst.list);
    free(aux);

    *node = NULL;
}
