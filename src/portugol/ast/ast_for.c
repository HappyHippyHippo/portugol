#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <internal/portugol/ast/ast_for.h>
#include <internal/portugol/runtime.h>
#include <internal/mem.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

AST_Node*
ast_for(const AST_Pos pos,
        const char* var,
        AST_Node* start,
        AST_Node* stop,
        AST_Node* step,
        AST_Node* scope)
{
    AST_For* node = NULL;

    if (   var
        && start
        && stop
        && scope)
    {
        /* allocate memory to the ast node */
        if ((node = mem_malloc(sizeof(AST_For))) == NULL)
        {
            // TODO : report no memory failure
            return NULL;
        }

        /* allocate memory to store the control variable name */
        size_t length = strlen(var);
        if ((node->var = mem_malloc(length + 1)) == NULL)
        {
            mem_free(node);

            // TODO : report no memory failure
            return NULL;
        }

        /* initialize the allocated ast node */
        node->type = AST_FOR;
        node->pos = pos;
        node->vtable.get_return_type = ast_for_get_return_type;
        node->vtable.execute = ast_for_execute;
        node->vtable.output = ast_for_output;
        node->vtable.destroy = ast_for_destroy;

        /* store the for control structure paramters */
#ifdef _MSC_VER
        strcpy_s(node->var, length + 1, var);
#else
        strcpy(node->var, var);
#endif /* _MSC_VER */
        node->start = start;
        node->stop = stop;
        node->step = step;
        node->scope = scope;
    }

    return (AST_Node*) node;
} /* end of : AST_Node*
              ast_for(const AST_Pos pos,
                      const char* var,
                      AST_Node* start,
                      AST_Node* stop,
                      AST_Node* step,
                      AST_Node* scope) */

/*******************************************************************************
 * INTERNAL FUNCTIONS
 ******************************************************************************/

VType
ast_for_get_return_type(AST_For* node)
{
    if (node)
    {
        return VBOOLEAN;
    }

    return VUNKNOWN;
} /* end of : VType
              ast_for_get_return_type(AST_For* node) */

Variant*
ast_for_execute(AST_For* node,
                Variant* result)
{
    if (   node
        && result
        && !runtime_is_returning())
    {
        /* push the for control scope into the runtime */
        runtime_stack_push_scope();

        /* calculate the stop value of the for control structure */
        Variant stop = {0};
        ast_execute(node->stop, &stop);

        /* calculate the start value of the for control structure */
        Variant* var = runtime_add(node->var, VINT32);
        ast_execute(node->start, var);

        /* check if there is a step value to be used */
        Variant step = {0};
        if (node->step)
        {
            /* calculate the step value */
            ast_execute(node->step, &step);
        }
        else
        {
            /* determine the relation betwwen the start and the stop values */
            Variant check = {0};
            variant_lesser(&check, var, &stop);

            /* check if is to use a increment or a decrement step value */
            if (check.value.vboolean)
            {
                variant_assign_int32(&step, 1);
            }
            else
            {
                variant_assign_int32(&step, -1);
            }

            variant_uninit(&check);
        }

        /* checking if the step is a increment or a decrement */
        Variant check = {0}, check_result = {0};
        variant_greater(&check_result, &step, variant_init_int32(&check, 0));
        if (check_result.value.vboolean)
        {
            /* increment while control structure cycle */
            while (result->value.vboolean)
            {
                /* execute the while control structure scope */
                Variant op;
                ast_execute(node->scope, &op);
                variant_uninit(&op);

                /* increment the control variable */
                /* re-calculate the stop value of the for control structure */
                /* check if the control structure cycle is to be stopped */
                variant_lesser_or_equal(result,
                                        variant_add(var, var, &step),
                                        ast_execute(node->stop, &stop));
            }
        }
        else
        {
            /* decrement while control structure cycle */
            while (result->value.vboolean)
            {
                /* execute the while control structure scope */
                Variant op;
                ast_execute(node->scope, &op);
                variant_uninit(&op);

                /* increment the control variable */
                /* re-calculate the stop value of the for control structure */
                /* check if the control structure cycle is to be stopped */
                variant_greater_or_equal(result,
                                         variant_add(var, var, &step),
                                         ast_execute(node->stop, &stop));
            }
        }

        /* vairant cleaning */
        variant_uninit(&stop);
        variant_uninit(&step);
        variant_uninit(&check);
        variant_uninit(&check_result);

        /* pop the for scope from the runtime */
        runtime_stack_pop();
    }

    return result;
} /* end of : Variant*
              ast_for_execute(AST_For* node,
                             Variant* result) */

void
ast_for_output(AST_For* node,
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
        printf("%sfor(%s)\n", prefix, node->var);
        ast_output(node->start, level + 1, "start > ");
        ast_output(node->stop, level + 1, "stop > ");
        ast_output(node->step, level + 1, "step > ");
        ast_output(node->scope, level + 1, "scope > ");
    }
} /* end of : void
              ast_for_output(AST_For* node,
                            const size_t level,
                            const char* prefix) */

void
ast_for_destroy(AST_For** node)
{
    if (   node
        && *node)
    {
        /* destroy the for control structure parameters */
        ast_destroy(&(*node)->start);
        ast_destroy(&(*node)->stop);
        ast_destroy(&(*node)->step);
        ast_destroy(&(*node)->scope);

        /* release the allocated memory */
        mem_free((*node)->var);
        mem_free(*node);
        *node = NULL;
    }
} /* end of : void
              ast_for_destroy(AST_For** node) */
