#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/portugol/ast.h>

ASTNode*
ast_variable(char* name,
             ASTSourcePos pos)
{
    if (name == NULL)
        return NULL;

    ASTVariable* node;
    if ((node = malloc(sizeof(ASTVariable))) != NULL)
    {
        if ((node->name = malloc(strlen(name) + 1)) == NULL)
        {
            free(node);
            return NULL;
        }

        node->type = AST_VARIABLE;
        node->pos  = pos;
        strcpy(node->name, name);
    }

    return (ASTNode*) node;
}

Variant
ast_variable_execute(ASTNode* node,
                     Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    ASTVariable* aux = (ASTVariable*) node;
    return variant_copy(*runtime_get(runtime, aux->name));
}

void
ast_variable_print(ASTNode* node,
                   int level)
{
    if (node == NULL)
        return;

    printf("var(%s)\n", ((ASTVariable*) node)->name);
}

void
ast_variable_destroy(ASTNode** node)
{
    if (node == NULL || *node == NULL)
        return;

    ASTVariable* aux = *(ASTVariable**) node;
    free(aux->name);
    free(aux);
    *node = NULL;
}
