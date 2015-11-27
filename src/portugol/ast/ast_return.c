#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <internal/portugol/ast/ast_return.h>
#include <internal/portugol/runtime.h>
#include <internal/mem.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

AST_Node*
ast_return(const AST_Pos pos,
           AST_Node* value)
{
    AST_Return* node = NULL;

    if (value)
    {
        /* allocate memory to the ast node */
        if ((node = mem_malloc(sizeof(AST_Return))) == NULL)
        {
            // TODO : report no memory failure
            return NULL;
        }

        /* initialize the allocated ast node */
        node->type = AST_RETURN;
        node->pos = pos;
        node->vtable.get_return_type = ast_return_get_return_type;
        node->vtable.execute = ast_return_execute;
        node->vtable.output = ast_return_output;
        node->vtable.destroy = ast_return_destroy;

        /* store the return expression node */
        node->value = value;
    }

    return (AST_Node*) node;
} /* end of : AST_Node*
              ast_return(const AST_Pos pos,
                         AST_Node* value) */

/*******************************************************************************
 * INTERNAL FUNCTIONS
 ******************************************************************************/

VType
ast_return_get_return_type(AST_Return* node)
{
    if (node)
    {
        return ast_get_return_type(node->value);
    }

    return VUNKNOWN;
} /* end of : VType
              ast_return_get_return_type(AST_Return* node) */

Variant*
ast_return_execute(AST_Return* node,
                   Variant* result)
{
    if (   node
        && result
        && !runtime_is_returning())
    {
        /* execute the return expression */
        ast_execute(node->value, result);

        /* retrieve the function result variant and store the calculated value */
        Variant* call_result = runtime_get_function_scope();
        if (call_result)
        {
            variant_assign(call_result, result);
        }

        /* flag the runtime to return the function scope */
        runtime_set_returning();
    }

    return result;
} /* end of : Variant*
              ast_return_execute(AST_Return* node,
                                 Variant* result) */

void
ast_return_output(AST_Return* node,
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
        printf("%sreturn\n", prefix);
        ast_output(node->value, level + 1, "expr > ");
    }
} /* end of : void
              ast_return_output(AST_Return* node,
                                const size_t level,
                                const char* prefix) */

void
ast_return_destroy(AST_Return** node)
{
    if (   node
        && *node)
    {
        /* destroy the return expression node */
        ast_destroy(&(*node)->value);

        /* release the allocated memory */
        mem_free(*node);
        *node = NULL;
    }
} /* end of : void
              ast_return_destroy(AST_Return** node) */
