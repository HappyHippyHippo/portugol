#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <internal/portugol/ast/ast_if.h>
#include <internal/portugol/runtime.h>
#include <internal/mem.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

AST_Node*
ast_if(const AST_Pos pos,
       AST_Node* expr,
       AST_Node* strue,
       AST_Node* sfalse)
{
    AST_If* node = NULL;

    if (   expr
        && strue)
    {
        /* allocate memory to the ast node */
        if ((node = mem_malloc(sizeof(AST_If))) == NULL)
        {
            // TODO : report no memory failure
            return NULL;
        }

        /* initialize the allocated ast node */
        node->type = AST_IF;
        node->pos = pos;
        node->vtable.execute = ast_if_execute;
        node->vtable.output = ast_if_output;
        node->vtable.destroy = ast_if_destroy;

        /* store the if control structure expression, true and false scope */
        node->expr = expr;
        node->strue = strue;
        node->sfalse = sfalse;
    }

    return (AST_Node*) node;
} /* end of : AST_Node*
              ast_if(const AST_Pos pos,
                     AST_Node* expr,
                     AST_Node* strue,
                     AST_Node* sfalse) */

/*******************************************************************************
 * INTERNAL FUNCTIONS
 ******************************************************************************/

VType
ast_if_get_return_type(AST_If* node)
{
    if (node)
    {
        return VBOOLEAN;
    }

    return VUNKNOWN;
} /* end of : VType
              ast_if_get_return_type(AST_If* node) */

Variant*
ast_if_execute(AST_If* node,
               Variant* result)
{
    if (   node
        && result
        && !runtime_is_returning())
    {
        /* execute the if control structure conditional expression */
        ast_execute(node->expr, result);
        variant_cast(result, VBOOLEAN);

        /* check the scope to be executed */
        if (result->value.vboolean)
        {
            /* execute the if control structure true scope */
            Variant op = {0};
            ast_execute(node->strue, &op);
            variant_uninit(&op);
        }
        else
        {
            /* execute the if control structure false scope */
            Variant op = {0};
            ast_execute(node->sfalse, &op);
            variant_uninit(&op);
        }
    }

    return result;
} /* end of : Variant*
              ast_if_execute(AST_If* node,
                             Variant* result) */

void
ast_if_output(AST_If* node,
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
        printf("%sif\n", prefix);
        ast_output(node->expr, level + 1, "expr > ");
        ast_output(node->strue, level + 1, "true > ");
        ast_output(node->sfalse, level + 1, "false > ");
    }
} /* end of : void
              ast_if_output(AST_If* node,
                            const size_t level,
                            const char* prefix) */

void
ast_if_destroy(AST_If** node)
{
    if (   node
        && *node)
    {
        /* destroy the if control structure expression, true and false scopes */
        ast_destroy(&(*node)->expr);
        ast_destroy(&(*node)->strue);
        ast_destroy(&(*node)->sfalse);

        /* release the allocated memory */
        mem_free(*node);
        *node = NULL;
    }
} /* end of : void
              ast_if_destroy(AST_If** node) */
