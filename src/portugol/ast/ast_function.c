#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <internal/portugol/ast/ast_function.h>
#include <internal/portugol/runtime.h>
#include <internal/mem.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

AST_ParamList*
ast_param_list(void)
{
    AST_ParamList* list = NULL;

    /* allocate memory to the parameter list structure */
    if ((list = mem_malloc(sizeof(AST_ParamList))) == NULL)
    {
        // TODO : report no memory failure
        return NULL;
    }

    /* initialize the allocated paramter list */
    list->list = NULL;
    list->count = 0;

    return list;
} /* end of : AST_ParamList*
              ast_param_list(void) */

size_t
ast_param_list_count(AST_ParamList* list)
{
    if (list)
    {
        return list->count;
    }

    return 0;
} /* end of : size_t
              ast_param_list_count(AST_ParamList* list) */

AST_ParamList*
ast_param_list_add(AST_ParamList* list,
                   AST_Pos pos,
                   VType type,
                   const char* name)
{
    if (list)
    {
        /* check if the parameters list is not empty */
        if (list->list)
        {
            /* reallocate/resize the allocated memory of the parameter list */
            AST_Param* aux;
            if ((aux = mem_realloc(list->list, sizeof(AST_Param) * (list->count + 1))) == NULL)
            {
                // TODO : report no memory failure
                return NULL;
            }

            /* store the position of the reallocated list */
            list->list = aux;
        }
        else
        {
            /* allocate memory to the parameters list */
            if ((list->list = mem_malloc(sizeof(AST_Param))) == NULL)
            {
                // TODO : report no memory failure
                return NULL;
            }
        }

        /* allocate memory to store the parameter name */
        size_t length = strlen(name);
        if ((list->list[list->count].name = mem_malloc(length + 1)) == NULL)
        {
            // TODO : report no memory failure
            return NULL;
        }

        /* store the parameter in the parameters list */
        list->list[list->count].pos = pos;
        list->list[list->count].type = type;
#ifdef _MSC_VER
        strcpy_s(list->list[list->count].name, length + 1, name);
#else
        strcpy(list->list[list->count].name, name);
#endif /* _MSC_VER */
        list->count++;
    }

    return list;
} /* end of : AST_ParamList*
              ast_param_list_add(AST_ParamList* list,
                                 AST_Pos pos,
                                 VType type,
                                 const char* name) */

AST_Node*
ast_function(AST_Pos pos,
             const char* name,
             AST_ParamList* params,
             VType return_type,
             AST_Node* scope)
{
    AST_Function* node = NULL;

    if (   name
        && params
        && scope)
    {
        /* allocate memory to the ast node */
        if ((node = mem_malloc(sizeof(AST_Function))) == NULL)
        {
            // TODO : report no memory failure
            return NULL;
        }

        /* allocate memory to store the function name */
        size_t length = strlen(name);
        if ((node->name = mem_malloc(length + 1)) == NULL)
        {
            mem_free(node);

            // TODO : report no memory failure
            return NULL;
        }

        /* initialize the allocated ast node */
        node->type = AST_FUNCTION;
        node->pos = pos;
        node->vtable.get_return_type = ast_function_get_return_type;
        node->vtable.execute = ast_function_execute;
        node->vtable.output = ast_function_output;
        node->vtable.destroy = ast_function_destroy;

        /* store the function node parameters */
#ifdef _MSC_VER
        strcpy_s(node->name, length + 1, name);
#else
        strcpy(node->name, name);
#endif /* _MSC_VER */
        node->params = params;
        node->return_type = return_type;
        node->scope = scope;
    }

    return (AST_Node*) node;
} /* end of : AST_Node*
              ast_function(AST_Pos pos,
                           const char* name,
                           AST_ParamList* params,
                           VType return_type,
                           AST_Node* scope) */

AST_ArgList*
ast_arg_list(void)
{
    AST_ArgList* list = NULL;

    /* allocate memory to the argument list structure */
    if ((list = mem_malloc(sizeof(AST_ArgList))) == NULL)
    {
        // TODO : report no memory failure
        return NULL;
    }

    /* initialize the allocated argument list */
    list->list = NULL;
    list->count = 0;

    return list;
} /* end of : AST_ArgList*
              ast_arg_list(void) */

size_t
ast_arg_list_count(AST_ArgList* list)
{
    if (list)
    {
        return list->count;
    }

    return 0;
} /* end of : size_t
              ast_arg_list_count(AST_ArgList* list) */

AST_ArgList*
ast_arg_list_add(AST_ArgList* list,
                 AST_Node* arg)
{
    if (list)
    {
        /* check if the arguments list is not empty */
        if (list->list)
        {
            /* reallocate/resize the allocated memory of the argument list */
            AST_Node** aux;
            if ((aux = mem_realloc(list->list, sizeof(AST_Node*) * (list->count + 1))) == NULL)
            {
                // TODO : report no memory failure
                return NULL;
            }

            /* store the position of the reallocated list */
            list->list = aux;
        }
        else
        {
            /* allocate memory to the arguments list */
            if ((list->list = mem_malloc(sizeof(AST_Node*))) == NULL)
            {
                // TODO : report no memory failure
                return NULL;
            }
        }

        /* store the argument in the arguments list */
        list->list[list->count] = arg;
        list->count++;
    }

    return list;
} /* end of : AST_ArgList*
              ast_arg_list_add(AST_ArgList* list,
                               AST_Node* arg) */

AST_Node*
ast_function_call(AST_Pos pos,
                  const char* name,
                  AST_ArgList* args)
{
    AST_FunctionCall* node = NULL;

    if (   name
        && args)
    {
        /* allocate memory to the ast node */
        if ((node = mem_malloc(sizeof(AST_Function))) == NULL)
        {
            // TODO : report no memory failure
            return NULL;
        }

        /* allocate memory to store the function name */
        size_t length = strlen(name);
        if ((node->name = mem_malloc(length + 1)) == NULL)
        {
            mem_free(node);

            // TODO : report no memory failure
            return NULL;
        }

        /* initialize the allocated ast node */
        node->type = AST_FUNCTION_CALL;
        node->pos = pos;
        node->vtable.get_return_type = ast_function_call_get_return_type;
        node->vtable.execute = ast_function_call_execute;
        node->vtable.output = ast_function_call_output;
        node->vtable.destroy = ast_function_call_destroy;

        /* store the function call node parameters */
#ifdef _MSC_VER
        strcpy_s(node->name, length + 1, name);
#else
        strcpy(node->name, name);
#endif /* _MSC_VER */
        node->args = args;
    }

    return (AST_Node*) node;
} /* end of : AST_Node*
              ast_function_call(AST_Pos pos,
                                const char* name,
                                AST_ArgList* args) */

/*******************************************************************************
 * INTERNAL FUNCTIONS
 ******************************************************************************/

VType
ast_function_get_return_type(AST_Function* node)
{
    if (node)
    {
        return node->return_type;
    }

    return VUNKNOWN;
} /* end of : VType
              ast_function_get_return_type(AST_Function* node) */

Variant*
ast_function_execute(AST_Function* node,
                     Variant* result)
{
    if (   node
        && result
        && !runtime_is_returning())
    {
        /* store the function pointer to the result variant */
        variant_assign_function(result, node);

        /* allocate memory in the runtime to store the function */
        Variant* store = runtime_add_function(node->name);
        if (store)
        {
            /* assign the functino pointer to the allocated memory */
            variant_assign(store, result);
        }
    }

    return result;
} /* end of : Variant*
              ast_function_execute(AST_Function* node,
                                   Variant* result) */

Variant*
ast_function_called(AST_Function* node,
                    Variant* result)
{
    if (   node
        && result)
    {
        /* execute the function scope */
        ast_execute(node->scope, result);
    }

    return result;
} /* end of : Variant*
              ast_function_called(AST_Function* node,
                                  Variant* result) */

void
ast_function_output(AST_Function* node,
                    const size_t level,
                    const char* prefix)
{
    if (node)
    {
        /* output the node position */
        printf("[%03d.%03d -> %03d.%03d] ",
               node->pos.line.start,
               node->pos.column.start,
               node->pos.line.stop,
               node->pos.column.stop);

        /* level space */
        for (size_t i = 0; i < level; ++i)
        {
            printf("  ");
        }

        /* present the node information */
        printf("%sfunction(%s)", prefix, node->name);

        switch (node->return_type)
        {
            case VBOOLEAN:  printf(" <- boolean\n");  break;
            case VINT32:    printf(" <- int32\n");    break;
            case VFLOAT32:  printf(" <- float32\n");  break;
            case VTEXT:     printf(" <- text\n");     break;
            case VPOINTER:  printf(" <- pointer\n");  break;
            case VFUNCTION: printf(" <- function\n"); break;
            default:        printf("\n");             break;
        }

        /* present the function parameters */
        for (size_t i = 0; i < node->params->count; ++i)
        {
            /* output the node position */
            printf("[%03d.%03d -> %03d.%03d] ",
                   node->params->list[i].pos.line.start,
                   node->params->list[i].pos.column.start,
                   node->params->list[i].pos.line.stop,
                   node->params->list[i].pos.column.stop);

            /* level space */
            for (size_t i = 0; i < level + 1; ++i)
            {
                printf("  ");
            }

            /* present the function parameter */
            switch (node->params->list[i].type)
            {
                case VBOOLEAN  : printf("param > boolean(%s)\n",  node->params->list[i].name); break;
                case VINT32    : printf("param > int32(%s)\n",    node->params->list[i].name); break;
                case VFLOAT32  : printf("param > float32(%s)\n",  node->params->list[i].name); break;
                case VTEXT     : printf("param > text(%s)\n",     node->params->list[i].name); break;
                case VPOINTER  : printf("param > pointer(%s)\n",  node->params->list[i].name); break;
                case VFUNCTION : printf("param > function(%s)\n", node->params->list[i].name); break;
                default:                                                                       break;
            }
        }

        /* present the function scope */
        ast_output(node->scope, level + 1, "");
    }
} /* end of : void
              ast_function_output(AST_Function* node,
                                  const size_t level,
                                  const char* prefix) */

void
ast_function_destroy(AST_Function** node)
{
    if (   node
        && *node)
    {
        /* destroy the functiom parameters list */
        for (size_t i = 0; i < (*node)->params->count; ++i)
        {
            mem_free((*node)->params->list[i].name);
        }
        mem_free((*node)->params->list);

        /* destroy the function scope node */
        ast_destroy(&(*node)->scope);

        /* release the allocated memory */
        mem_free((*node)->name);
        mem_free(*node);
        *node = NULL;
    }
} /* end of : void
              ast_function_destroy(AST_Function** node) */

VType
ast_function_call_get_return_type(AST_FunctionCall* node)
{
    if (node)
    {
        /* retrieve the function pointer from the runtime */
        Variant* fvariant = runtime_get(node->name);
        AST_Function* function = (AST_Function*) fvariant->value.vfunction;

        return function->return_type;
    }

    return VUNKNOWN;
} /* end of : VType
              ast_function_call_get_return_type(AST_FunctionCall* node) */

Variant*
ast_function_call_execute(AST_FunctionCall* node,
                          Variant* result)
{
    if (   node
        && result
        && !runtime_is_returning())
    {
        /* retrieve the function pointer from the runtime */
        Variant* fvariant = runtime_get(node->name);
        AST_Function* function = (AST_Function*) fvariant->value.vfunction;

        /* push the function scope into the runtime */
        Variant* call_result = runtime_stack_push_function("*function", function->return_type);

        /* function parameters scope insertion cycle */
        for (size_t fparam = 0; fparam < function->params->count; ++fparam)
        {
            Variant arg = {0};

            /* check if there is a argument to be calculated */
            if (fparam < node->args->count)
            {
                ast_execute(node->args->list[fparam], &arg);
            }

            /* cast the argument to the paramter expected type */
            variant_cast(&arg, function->params->list[fparam].type);

            /* create the runtime variant and copy the argument value into it */
            Variant* store = runtime_add(function->params->list[fparam].name, function->params->list[fparam].type);
            if (store)
            {
                variant_assign(store, &arg);
            }

            /* clear the argument variant */
            variant_uninit(&arg);
        }

        /* call the function scope execution */
        ast_function_called(function, result);

        /* store the function call result */
        variant_assign(result, call_result);

        /* pop the function scope from the runtime */
        runtime_stack_pop();
    }

    return result;
} /* end of : Variant*
              ast_function_call_execute(AST_FunctionCall* node,
                                        Variant* result) */

void
ast_function_call_output(AST_FunctionCall* node,
                         const size_t level,
                         const char* prefix)
{
    if (node)
    {
        /* output the node position */
        printf("[%03d.%03d -> %03d.%03d] ",
               node->pos.line.start,
               node->pos.column.start,
               node->pos.line.stop,
               node->pos.column.stop);

        /* level space */
        for (size_t i = 0; i < level; ++i)
        {
            printf("  ");
        }

        /* present the node information */
        printf("%sfunction call(%s)\n", prefix, node->name);

        /* present the function call arguments */
        for (size_t i = 0; i < node->args->count; ++i)
        {
            /* present the function argument expression */
            ast_output(node->args->list[i], level + 1, "argument > ");
        }
    }
} /* end of : void
              ast_function_call_output(AST_FunctionCall* node,
                                       const size_t level,
                                       const char* prefix) */

void
ast_function_call_destroy(AST_FunctionCall** node)
{
    if (   node
        && *node)
    {
        /* destroy the functiom call argument list */
        for (size_t i = 0; i < (*node)->args->count; ++i)
        {
            ast_destroy(&(*node)->args->list[i]);
        }
        mem_free((*node)->args->list);

        /* release the allocated memory */
        mem_free((*node)->name);
        mem_free(*node);
        *node = NULL;
    }
} /* end of : void
              ast_function_call_destroy(AST_FunctionCall** node) */
