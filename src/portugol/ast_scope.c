#include <stdio.h>
#include <stdlib.h>

#include <internal/portugol/ast.h>

ASTNode*
ast_scope(ASTSourcePos pos)
{
    ASTScope* node = NULL;

    if ((node = malloc(sizeof(ASTScope))) != NULL)
    {
        node->type        = AST_SCOPE;
        node->pos         = pos;
        node->instr.size  = 10;
        node->instr.count = 0;
        if ((node->instr.list = malloc(sizeof(ASTScope) * node->instr.size)) == NULL)
        {
            free(node);
            node = NULL;
        }
    }

    return (ASTNode*) node;
}

ASTNode*
ast_scope_push(ASTNode* scope,
               ASTNode* inst)
{
    if (scope == NULL || inst == NULL)
        return scope;

    ASTScope* aux = (ASTScope*)scope;
    if (aux->instr.size == aux->instr.count)
    {
        ASTNode** tmp = realloc(aux->instr.list, sizeof(ASTNode*) * (aux->instr.size + 10));
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
ast_scope_execute(ASTNode* node,
                  Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    ASTScope* aux = (ASTScope*) node;
    for (int idx = 0; idx < aux->instr.count; ++idx)
    {
        Variant result = ast_execute(aux->instr.list[idx], runtime);
        variant_uninit(&result);
    }

    return variant_init_int32(0);
}

void
ast_scope_print(ASTNode* node,
                int level)
{
    if (node == NULL)
        return;

    printf("+scope\n");
    for (size_t idx = 0; idx < ((ASTScope*) node)->instr.count; ++idx)
        ast_print(((ASTScope*)node)->instr.list[idx], level + 1);
}

void
ast_scope_destroy(ASTNode** node)
{
    if (node == NULL || *node == NULL)
        return;

    ASTScope* aux = *(ASTScope**) node;
    for (size_t idx = 0; idx < aux->instr.count; ++idx)
        ast_destroy(&aux->instr.list[idx]);

    free(aux->instr.list);
    free(aux);
    *node = NULL;
}
