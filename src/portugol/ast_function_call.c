#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/portugol/ast_function_call.h>

AST_Node**
ast_function_call_arg_push(AST_Node* node,
                           AST_Node** list,
                           int count)
{
    if (list == NULL)
    {
        if ((list = malloc(sizeof(AST_Node*))) != NULL)
            list[0] = node;
    }
    else
    {
        AST_Node** aux;
        if ((aux = realloc(list, sizeof(AST_Node*) * (count + 1))) != NULL)
        {
            list = aux;
            list[count] = node;
        }
    }

    return list;
}

AST_Node*
ast_function_call(char* name,
                  AST_Node** args,
                  int arg_count,
                  AST_SourcePos pos)
{
    if (name == NULL)
        return NULL;

    AST_FunctionCall* node = NULL;
    if ((node = malloc(sizeof(AST_FunctionCall))) != NULL)
    {
        if ((node->name = malloc(strlen(name) + 1)) == NULL)
        {
            free(node);
            return NULL;
        }

        node->type      = AST_FUNCTION_CALL;
        node->pos       = pos;

        node->args      = args;
        node->arg_count = arg_count;

        strcpy(node->name, name);
    }

    return (AST_Node*) node;
}

Variant
ast_function_call_execute(AST_Node* node,
                          Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    // TODO : retrieve the function from heap
    // TODO : execute the funciton code

    return variant_init_int32(0);
}

void
ast_function_call_print(AST_Node* node,
                        int level,
                        char* prefix)
{
    if (node == NULL)
        return;

    printf("function_call(%s)\n", ((AST_FunctionCall*) node)->name);
    for (int idx = 0; idx < ((AST_FunctionCall*) node)->arg_count; ++idx)
        ast_print(((AST_FunctionCall*) node)->args[idx], level + 1, "arg > ");
}

void
ast_function_call_destroy(AST_Node** node)
{
    if (node == NULL || *node == NULL)
        return;

    AST_FunctionCall* aux = *(AST_FunctionCall**) node;

    free(aux->name);
    free(aux->args);
    free(aux);
    *node = NULL;
}
