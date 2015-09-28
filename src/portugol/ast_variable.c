#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/portugol/ast.h>

AST_Node*
ast_variable(char* name,
             AST_SourcePos pos)
{
    if (name == NULL)
        return NULL;

    AST_Variable* node;
    if ((node = malloc(sizeof(AST_Variable))) != NULL)
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

    return (AST_Node*) node;
}

Variant
ast_variable_execute(AST_Node* node,
                     Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    AST_Variable* aux = (AST_Variable*) node;
    return variant_copy(*runtime_get(runtime, aux->name));
}

void
ast_variable_print(AST_Node* node,
                   int level,
                   char* prefix)
{
    if (node == NULL)
        return;

    printf("var(%s)\n", ((AST_Variable*) node)->name);
}

void
ast_variable_destroy(AST_Node** node)
{
    if (node == NULL || *node == NULL)
        return;

    AST_Variable* aux = *(AST_Variable**) node;
    free(aux->name);
    free(aux);
    *node = NULL;
}
