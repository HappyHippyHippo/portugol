#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <internal/portugol/ast/ast_variable.h>
#include <internal/portugol/runtime.h>
#include <internal/mem.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

AST_Node*
ast_variable(const AST_Pos pos,
             const char* name)
{
    AST_Variable* node = NULL;

    if (name)
    {
        /* allocate memory to the ast node */
        if ((node = mem_malloc(sizeof(AST_Variable))) == NULL)
        {
            // TODO : report no memory failure
            return NULL;
        }

        /* allocate memory to the variable name declaration node */
        if ((node->name = mem_malloc(strlen(name) + 1)) == NULL)
        {
            mem_free(node);

            // TODO : report no memory failure
            return NULL;
        }

        /* initialize the allocated ast node */
        node->type = AST_VARIABLE;
        node->pos = pos;
        node->vtable.get_return_type = ast_variable_get_return_type;
        node->vtable.execute = ast_variable_execute;
        node->vtable.output = ast_variable_output;
        node->vtable.destroy = ast_variable_destroy;

        /* store the declaration name and default expression */
#ifdef _MSC_VER
        strcpy_s(node->name, strlen(name) + 1, name);
#else
        strcpy(node->name, name);
#endif /* _MSC_VER */
    }

    return (AST_Node*) node;
} /* end of : AST_Node*
              ast_variable(const AST_Pos pos,
                           const char* name) */

/*******************************************************************************
 * INTERNAL FUNCTIONS
 ******************************************************************************/

VType
ast_variable_get_return_type(AST_Variable* node)
{
    if (node)
    {
        /* retrieve the value from the runtime */
        Variant* store = runtime_get(node->name);
        if (store)
            return store->type;
    }

    return VUNKNOWN;
} /* end of : VType
              ast_variable_get_return_type(AST_Variable* node) */

Variant*
ast_variable_execute(AST_Variable* node,
                     Variant* result)
{
    if (   node
        && result
        && !runtime_is_returning())
    {
        /* retrieve the variant from the runtime */
        Variant* store = runtime_get(node->name);
        if (store)
        {
            /* copy the value to the result variant */
            variant_assign(result, store);
        }
    }

    return result;
} /* end of : Variant*
              ast_variable_execute(AST_Variable* node,
                                   Variant* result) */

void
ast_variable_output(AST_Variable* node,
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
        printf("%svar(%s)\n", prefix, node->name);
    }
} /* end of : void
              ast_variable_output(AST_Variable* node,
                                  const size_t level,
                                  const char* prefix) */

void
ast_variable_destroy(AST_Variable** node)
{
    if (   node
        && *node)
    {
        /* release the allocated memory */
        mem_free((*node)->name);
        mem_free(*node);
        *node = NULL;
    }
} /* end of : void
              ast_variable_destroy(AST_Variable** node) */
