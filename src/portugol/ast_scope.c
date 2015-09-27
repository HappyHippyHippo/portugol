#include <stdio.h>
#include <stdlib.h>

#include <internal/portugol/ast.h>

ASTNode*
ast_scope_push(ASTNode* scope,
               ASTNode* decl)
{
    if (scope == NULL || decl == NULL)
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

    aux->instr.list[aux->instr.count] = decl;
    ++aux->instr.count;

    return scope;
}

ASTNode*
ast_file(void)
{
    ASTScope* node = NULL;

    if ((node = malloc(sizeof(ASTScope))) != NULL)
    {
        node->type = AST_FILE;
        node->instr.size = 10;
        node->instr.count = 0;
        if ((node->instr.list = malloc(sizeof(ASTScope) * node->instr.size)) == NULL)
        {
            free(node);
            node = NULL;
        }
    }

    return (ASTNode*)node;
}
