#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/portugol/ast_function.h>

AST_FunctionParam
ast_function_param(VariantType type,
                   char* name)
{
    AST_FunctionParam param;

    param.type = type;
    if ((param.name = malloc(strlen(name) + 1)) != NULL)
        strcpy(param.name, name);

    return param;
}

AST_FunctionParam*
ast_function_param_push(AST_FunctionParam param,
                        AST_FunctionParam* list,
                        int count)
{
    if (list == NULL)
    {
        if ((list = malloc(sizeof(AST_FunctionParam))) != NULL)
            list[0] = param;
    }
    else
    {
        AST_FunctionParam* aux;
        if ((aux = realloc(list, sizeof(AST_FunctionParam) * (count + 1))) != NULL)
        {
            list = aux;
            list[count] = param;
        }
    }

    return list;
}

AST_Node*
ast_function(char* name,
             AST_FunctionParam* params,
             int param_count,
             VariantType return_type,
             AST_Node* scope,
             AST_SourcePos pos)
{
    if (name == NULL || scope == NULL)
        return NULL;

    AST_Function* node = NULL;
    if ((node = malloc(sizeof(AST_Function))) != NULL)
    {
        if ((node->name = malloc(strlen(name) + 1)) == NULL)
        {
            free(node);
            return NULL;
        }

        node->type        = AST_FUNCTION;
        node->pos         = pos;

        node->params      = params;
        node->param_count = param_count;

        node->return_type = return_type;
        node->scope       = scope;
        strcpy(node->name, name);
    }

    return (AST_Node*) node;
}

AST_Node*
ast_program(AST_Node* scope,
            AST_SourcePos pos)
{
    return ast_function("programa", NULL, 0, VINT32, scope, pos);
}

Variant
ast_function_execute(AST_Node* node,
                     Runtime* runtime)
{
    if (node == NULL || runtime == NULL)
        return variant_init_int32(0);

    // TODO : register the function in the heap

    return variant_init_int32(0);
}

void
ast_function_print(AST_Node* node,
                   int level,
                   char* prefix)
{
    if (node == NULL)
        return;

    printf("function(%s) -> ", ((AST_Function*) node)->name);
    switch (((AST_Function*) node)->return_type)
    {
        case VBOOLEAN:  printf("boolean\n");  break;
        case VINT32:    printf("int32\n");    break;
        case VFLOAT32:  printf("float32\n");  break;
        case VTEXT:     printf("text\n");     break;
        case VFUNCTION: printf("function\n"); break;
        default:        printf("unknown\n");  break;
    }

    for (int idx = 0; idx < ((AST_Function*) node)->param_count; ++idx) {
        for (int i = 0; i < level - 1; ++i)
            printf("    ");
         printf("param %d > ", idx);

        switch (((AST_Function*) node)->params[idx].type)
        {
            case VBOOLEAN:  printf("boolean");  break;
            case VINT32:    printf("int32");    break;
            case VFLOAT32:  printf("float32");  break;
            case VTEXT:     printf("text");     break;
            case VFUNCTION: printf("function"); break;
            default:        printf("unknown");  break;
        }
        printf(": %s\n", ((AST_Function*) node)->params[idx].name);
    }

    ast_print(((AST_Function*) node)->scope, level + 1, "");
}

void
ast_function_destroy(AST_Node** node)
{
    if (node == NULL || *node == NULL)
        return;

    AST_Function* aux = *(AST_Function**) node;
    ast_destroy(&aux->scope);

    free(aux->name);
    free(aux->params);
    free(aux);
    *node = NULL;
}
