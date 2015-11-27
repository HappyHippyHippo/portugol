#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <internal/portugol/ast/ast_while.h>
#include <internal/portugol/runtime.h>
#include <internal/mem.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

AST_Node*
ast_while(const AST_Pos pos,
          AST_Node* expr,
          AST_Node* scope)
{
    AST_While* node = NULL;

    if (   expr
        && scope)
    {
        /* allocate memory to the ast node */
        if ((node = mem_malloc(sizeof(AST_While))) == NULL)
        {
            // TODO : report no memory failure
            return NULL;
        }

        /* initialize the allocated ast node */
        node->type = AST_WHILE;
        node->pos = pos;
        node->vtable.get_return_type = ast_while_get_return_type;
        node->vtable.execute = ast_while_execute;
        node->vtable.output = ast_while_output;
        node->vtable.destroy = ast_while_destroy;

        /* store the while control structure expression and scope */
        node->expr = expr;
        node->scope = scope;
    }

    return (AST_Node*) node;
} /* end of : AST_Node*
              ast_while(const AST_Pos pos,
                        AST_Node* expr,
                        AST_Node* scope) */

/*******************************************************************************
 * INTERNAL FUNCTIONS
 ******************************************************************************/

VType
ast_while_get_return_type(AST_While* node)
{
    if (node)
    {
        return VBOOLEAN;
    }

    return VUNKNOWN;
} /* end of : VType
              ast_while_get_return_type(AST_While* node) */

Variant*
ast_while_execute(AST_While* node,
                  Variant* result)
{
    if (   node
        && result
        && !runtime_is_returning())
    {
        /* execute the while control structure conditional expression */
        ast_execute(node->expr, result);
        variant_cast(result, VBOOLEAN);

        /* while control structure cycle */
        while (result->value.vboolean)
        {
            /* execute the while control structure scope */
            Variant op;
            ast_execute(node->scope, &op);
            variant_uninit(&op);

            /* re.execute the while control structure conditional expression */
            ast_execute(node->expr, result);
            variant_cast(result, VBOOLEAN);
        }
    }

    return result;
} /* end of : Variant*
              ast_while_execute(AST_While* node,
                                Variant* result) */

void
ast_while_output(AST_While* node,
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
        printf("%swhile\n", prefix);
        ast_output(node->expr, level + 1, "expr > ");
        ast_output(node->scope, level + 1, "scope > ");
    }
} /* end of : void
              ast_while_output(AST_While* node,
                               const size_t level,
                               const char* prefix) */

void
ast_while_destroy(AST_While** node)
{
    if (   node
        && *node)
    {
        /* destroy the while control structure expression and scopes */
        ast_destroy(&(*node)->expr);
        ast_destroy(&(*node)->scope);

        /* release the allocated memory */
        mem_free(*node);
        *node = NULL;
    }
} /* end of : void
              ast_while_destroy(AST_While** node) */
