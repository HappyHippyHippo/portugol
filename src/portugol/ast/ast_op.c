#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <internal/portugol/ast/ast_op.h>
#include <internal/portugol/ast/ast_variable.h>
#include <internal/portugol/runtime.h>
#include <internal/mem.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

AST_Node*
ast_op_add(const AST_Pos pos,
           AST_Node* op1,
           AST_Node* op2)
{
    return ast_op(pos, op1, op2, AST_OP_ADD);
} /* end of : AST_Node*
              ast_op_add(const AST_Pos pos,
                         AST_Node* op1,
                         AST_Node* op2) */

AST_Node*
ast_op_subtract(const AST_Pos pos,
                AST_Node* op1,
                AST_Node* op2)
{
    return ast_op(pos, op1, op2, AST_OP_SUBTRACT);
} /* end of : AST_Node*
              ast_op_subtract(const AST_Pos pos,
                              AST_Node* op1,
                              AST_Node* op2) */

AST_Node*
ast_op_multiply(const AST_Pos pos,
                AST_Node* op1,
                AST_Node* op2)
{
    return ast_op(pos, op1, op2, AST_OP_MULTIPLY);
} /* end of : AST_Node*
              ast_op_multiply(const AST_Pos pos,
                              AST_Node* op1,
                              AST_Node* op2) */

AST_Node*
ast_op_divide(const AST_Pos pos,
              AST_Node* op1,
              AST_Node* op2)
{
    return ast_op(pos, op1, op2, AST_OP_DIVIDE);
} /* end of : AST_Node*
              ast_op_divide(const AST_Pos pos,
                            AST_Node* op1,
                            AST_Node* op2) */

AST_Node*
ast_op_remainder(const AST_Pos pos,
                 AST_Node* op1,
                 AST_Node* op2)
{
    return ast_op(pos, op1, op2, AST_OP_REMAINDER);
} /* end of : AST_Node*
              ast_op_remainder(const AST_Pos pos,
                               AST_Node* op1,
                               AST_Node* op2) */

AST_Node*
ast_op_equal(const AST_Pos pos,
             AST_Node* op1,
             AST_Node* op2)
{
    return ast_op(pos, op1, op2, AST_OP_EQUAL);
} /* end of : AST_Node*
              ast_op_equal(const AST_Pos pos,
                           AST_Node* op1,
                           AST_Node* op2) */

AST_Node*
ast_op_inequal(const AST_Pos pos,
               AST_Node* op1,
               AST_Node* op2)
{
    return ast_op(pos, op1, op2, AST_OP_INEQUAL);
} /* end of : AST_Node*
              ast_op_inequal(const AST_Pos pos,
                             AST_Node* op1,
                             AST_Node* op2) */

AST_Node*
ast_op_greater(const AST_Pos pos,
               AST_Node* op1,
               AST_Node* op2)
{
    return ast_op(pos, op1, op2, AST_OP_GREATER);
} /* end of : AST_Node*
              ast_op_greater(const AST_Pos pos,
                             AST_Node* op1,
                             AST_Node* op2) */

AST_Node*
ast_op_greater_or_equal(const AST_Pos pos,
                        AST_Node* op1,
                        AST_Node* op2)
{
    return ast_op(pos, op1, op2, AST_OP_GREATER_OR_EQUAL);
} /* end of : AST_Node*
              ast_op_greater_or_equal(const AST_Pos pos,
                                      AST_Node* op1,
                                      AST_Node* op2) */

AST_Node*
ast_op_lesser(const AST_Pos pos,
              AST_Node* op1,
              AST_Node* op2)
{
    return ast_op(pos, op1, op2, AST_OP_LESSER);
} /* end of : AST_Node*
              ast_op_lesser(const AST_Pos pos,
                            AST_Node* op1,
                            AST_Node* op2) */

AST_Node*
ast_op_lesser_or_equal(const AST_Pos pos,
                       AST_Node* op1,
                       AST_Node* op2)
{
    return ast_op(pos, op1, op2, AST_OP_LESSER_OR_EQUAL);
} /* end of : AST_Node*
              ast_op_lesser_or_equal(const AST_Pos pos,
                                     AST_Node* op1,
                                     AST_Node* op2) */

AST_Node*
ast_op_and(const AST_Pos pos,
           AST_Node* op1,
           AST_Node* op2)
{
    return ast_op(pos, op1, op2, AST_OP_AND);
} /* end of : AST_Node*
              ast_op_and(const AST_Pos pos,
                         AST_Node* op1,
                         AST_Node* op2) */

AST_Node*
ast_op_or(const AST_Pos pos,
          AST_Node* op1,
          AST_Node* op2)
{
    return ast_op(pos, op1, op2, AST_OP_OR);
} /* end of : AST_Node*
              ast_op_or(const AST_Pos pos,
                        AST_Node* op1,
                        AST_Node* op2) */

AST_Node*
ast_op_xor(const AST_Pos pos,
           AST_Node* op1,
           AST_Node* op2)
{
    return ast_op(pos, op1, op2, AST_OP_XOR);
} /* end of : AST_Node*
              ast_op_xor(const AST_Pos pos,
                         AST_Node* op1,
                         AST_Node* op2) */

AST_Node*
ast_op_negate(const AST_Pos pos,
              AST_Node* op)
{
    return ast_op(pos, op, NULL, AST_OP_NEGATE);
} /* end of : AST_Node*
              ast_op_negate(const AST_Pos pos,
                            AST_Node* op) */

AST_Node*
ast_op_negative(const AST_Pos pos,
                AST_Node* op)
{
    return ast_op(pos, op, NULL, AST_OP_NEGATIVE);
} /* end of : AST_Node*
              ast_op_negative(const AST_Pos pos,
                              AST_Node* op) */

AST_Node*
ast_op_assign(const AST_Pos pos,
              AST_Node* op1,
              AST_Node* op2)
{
    return ast_op(pos, op1, op2, AST_OP_ASSIGN);
} /* end of : AST_Node*
              ast_op_assign(const AST_Pos pos,
                            AST_Node* op1,
                            AST_Node* op2) */

/*******************************************************************************
 * INTERNAL FUNCTIONS
 ******************************************************************************/

AST_Node*
ast_op(const AST_Pos pos,
       AST_Node* op1,
       AST_Node* op2,
       AST_Type type)
{
    AST_Op* node = NULL;

    if (   op1
        && (   op2
            || (   type == AST_OP_NEGATE
                || type == AST_OP_NEGATIVE)))
    {
        /* allocate memory to the ast node */
        if ((node = mem_malloc(sizeof(AST_Op))) == NULL)
        {
            // TODO : report no memory failure
            return NULL;
        }

        /* initialize the allocated ast node */
        node->type = type;
        node->pos = pos;
        node->vtable.get_return_type = ast_op_get_return_type;
        node->vtable.execute = ast_op_execute;
        node->vtable.output = ast_op_output;
        node->vtable.destroy = ast_op_destroy;

        /* store the ast node operators of the  */
        node->op1 = op1;
        node->op2 = op2;
    }

    return (AST_Node*) node;
} /* end of : AST_Node*
              ast_op(const AST_Pos pos,
                     AST_Node* op1,
                     AST_Node* op2,
                     AST_Type type) */

VType
ast_op_get_return_type(AST_Op* node)
{
    if (node)
    {
        if (node->type != AST_OP_ASSIGN)
        {
            /* retrieve the type of the two operators */
            VType op1_type = ast_get_return_type(node->op1);
            VType op2_type = ast_get_return_type(node->op2);

            /* return the supra type of the two operators */
            return op1_type > op2_type ? op1_type : op2_type;
        }
        else
        {
            return ast_get_return_type(node->op1);
        }
    }

    return VUNKNOWN;
} /* end of : VType
              ast_op_get_return_type(AST_Op* node) */

Variant*
ast_op_execute(AST_Op* node,
               Variant* result)
{
    if (   node
        && result
        && !runtime_is_returning())
    {
        /* initialize the operands result variants */
        Variant op1_result = {0}, op2_result = {0};

        /* calculate the operands values */
        ast_execute(node->op1, &op1_result);
        ast_execute(node->op2, &op2_result);

        /* execute the operation */
        switch (node->type)
        {
            case AST_OP_ADD:              variant_add             (result, &op1_result, &op2_result); break;
            case AST_OP_SUBTRACT:         variant_subtract        (result, &op1_result, &op2_result); break;
            case AST_OP_MULTIPLY:         variant_multiply        (result, &op1_result, &op2_result); break;
            case AST_OP_DIVIDE:           variant_divide          (result, &op1_result, &op2_result); break;
            case AST_OP_REMAINDER:        variant_remainder       (result, &op1_result, &op2_result); break;
            case AST_OP_EQUAL:            variant_equal           (result, &op1_result, &op2_result); break;
            case AST_OP_INEQUAL:          variant_inequal         (result, &op1_result, &op2_result); break;
            case AST_OP_GREATER:          variant_greater         (result, &op1_result, &op2_result); break;
            case AST_OP_GREATER_OR_EQUAL: variant_greater_or_equal(result, &op1_result, &op2_result); break;
            case AST_OP_LESSER:           variant_lesser          (result, &op1_result, &op2_result); break;
            case AST_OP_LESSER_OR_EQUAL:  variant_lesser_or_equal (result, &op1_result, &op2_result); break;
            case AST_OP_AND:              variant_and             (result, &op1_result, &op2_result); break;
            case AST_OP_OR:               variant_or              (result, &op1_result, &op2_result); break;
            case AST_OP_XOR:              variant_xor             (result, &op1_result, &op2_result); break;
            case AST_OP_NEGATE:           variant_negate          (result, &op1_result);              break;
            case AST_OP_NEGATIVE:         variant_negative        (result, &op1_result);              break;
            case AST_OP_ASSIGN:
            {
                /* execute the expression to be assigned */
                ast_execute(node->op2, result);

                /* retreive the variable from the runtime and
                   assign the value to the store */
                Variant* store = runtime_get(((AST_Variable*) node->op1)->name);
                variant_assign(store, variant_cast(result, store->type));
                break;
            }
            default:                                                                                  break;
        }

        /* uninialize the operands result variants */
        variant_uninit(&op1_result);
        variant_uninit(&op2_result);
    }

    return result;
} /* end of : Variant*
              ast_op_execute(AST_Op* node,
                             Variant* result) */

void
ast_op_output(AST_Op* node,
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
        switch (node->type)
        {
            case AST_OP_ADD:              printf("%sadd >\n", prefix);              break;
            case AST_OP_SUBTRACT:         printf("%ssubtract >\n", prefix);         break;
            case AST_OP_MULTIPLY:         printf("%smultiply >\n", prefix);         break;
            case AST_OP_DIVIDE:           printf("%sdivide >\n", prefix);           break;
            case AST_OP_REMAINDER:        printf("%sremainder >\n", prefix);        break;
            case AST_OP_EQUAL:            printf("%sequal >\n", prefix);            break;
            case AST_OP_INEQUAL:          printf("%sinequal >\n", prefix);          break;
            case AST_OP_GREATER:          printf("%sgreater >\n", prefix);          break;
            case AST_OP_GREATER_OR_EQUAL: printf("%sgreater or equal >\n", prefix); break;
            case AST_OP_LESSER:           printf("%slesser >\n", prefix);           break;
            case AST_OP_LESSER_OR_EQUAL:  printf("%slesser or equal >\n", prefix);  break;
            case AST_OP_AND:              printf("%sand >\n", prefix);              break;
            case AST_OP_OR:               printf("%sor >\n", prefix);               break;
            case AST_OP_XOR:              printf("%sxor >\n", prefix);              break;
            case AST_OP_NEGATE:           printf("%snegate >\n", prefix);           break;
            case AST_OP_NEGATIVE:         printf("%snegative >\n", prefix);         break;
            case AST_OP_ASSIGN:           printf("%sassign >\n", prefix);           break;
            default:                                                                break;
        }

        if (node->op2)
        {
            ast_output(node->op1, level + 1, "left > ");
            ast_output(node->op2, level + 1, "right > ");
        }
        else
        {
            ast_output(node->op1, level + 1, "op > ");
        }
    }
} /* end of : void
              ast_op_output(AST_Op* node,
                            const size_t level,
                            const char* prefix) */

void
ast_op_destroy(AST_Op** node)
{
    if (   node
        && *node)
    {
        /* destroy the stored operators ast nodes */
        ast_destroy(&(*node)->op1);
        ast_destroy(&(*node)->op2);

        /* release the allocated memory */
        mem_free(*node);
        *node = NULL;
    }
} /* end of : void
              ast_op_destroy(AST_Op** node) */
