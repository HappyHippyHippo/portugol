#include <stdio.h>

#include <internal/portugol/ast/ast_system_function.h>

Variant*
ast_system_function_output(struct AST_FunctionCall* node,
                           Variant* result)
{
    if (   node
        && result)
    {
        Variant arg = {0};

        /* check if there is a argument to be calculated */
        if (node->args->count)
        {
            ast_execute(node->args->list[0], &arg);
        }

        /* cast the argument to the paramter expected type */
        variant_cast(&arg, VTEXT);

        /* call the system output function */
        printf("%s", arg.value.vtext);

        /* clear the argument variant */
        variant_uninit(&arg);
    }

    return result;
} /* end of : Variant*
              ast_system_function_output(struct AST_FunctionCall* node,
                                         Variant* result) */
