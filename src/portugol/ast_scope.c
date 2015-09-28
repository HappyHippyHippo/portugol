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
        node->instr.size  = 10;
        node->instr.count = 0;
        if ((node->instr.list = malloc(sizeof(AST_Scope) * node->instr.size)) == NULL)
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
    if (aux->instr.size == aux->instr.count)
    {
        AST_Node** tmp = realloc(aux->instr.list, sizeof(AST_Node*) * (aux->instr.size + 10));
        if (!tmp)
            return NULL;

        aux->instr.size += 10;
        aux->instr.list = tmp;
    }

    aux->instr.list[aux->instr.count] = inst;
    ++aux->instr.count;

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
    for (int idx = 0; idx < aux->instr.count; ++idx)
    {
        Variant result = ast_execute(aux->instr.list[idx], runtime);
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

    printf("scope\n");
    for (size_t idx = 0; idx < ((AST_Scope*) node)->instr.count; ++idx)
        ast_print(((AST_Scope*)node)->instr.list[idx], level + 1, "");
}

void
ast_scope_destroy(AST_Node** node)
{
    if (node == NULL || *node == NULL)
        return;

    AST_Scope* aux = *(AST_Scope**) node;
    for (size_t idx = 0; idx < aux->instr.count; ++idx)
        ast_destroy(&aux->instr.list[idx]);

    free(aux->instr.list);
    free(aux);
    *node = NULL;
}
