#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <internal/portugol/ast/ast_const.h>
#include <internal/portugol/runtime.h>
#include <internal/mem.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

AST_Node*
ast_boolean(const AST_Pos pos,
            const int8_t value)
{
    AST_Const* node = NULL;

    /* allocate memory to the ast node */
    if ((node = mem_malloc(sizeof(AST_Const))) == NULL)
    {
        // TODO : report no memory failure
        return NULL;
    }

    /* initialize the allocated ast node */
    node->type = AST_BOOLEAN;
    node->pos = pos;
    node->vtable.get_return_type = ast_const_get_return_type;
    node->vtable.execute = ast_const_execute;
    node->vtable.output = ast_const_output;
    node->vtable.destroy = ast_const_destroy;

    /* set node constant value */
    variant_init_boolean(&node->value, value != 0);

    return (AST_Node*) node;
} /* end of : AST_Node*
              ast_boolean(const AST_Pos pos,
                          const int8_t value) */

AST_Node*
ast_int32(const AST_Pos pos,
          const int32_t value)
{
    AST_Const* node = NULL;

    /* allocate memory to the ast node */
    if ((node = mem_malloc(sizeof(AST_Const))) == NULL)
    {
        // TODO : report no memory failure
        return NULL;
    }

    /* initialize the allocated ast node */
    node->type = AST_INT32;
    node->pos = pos;
    node->vtable.get_return_type = ast_const_get_return_type;
    node->vtable.execute = ast_const_execute;
    node->vtable.output = ast_const_output;
    node->vtable.destroy = ast_const_destroy;

    /* set node constant value */
    variant_init_int32(&node->value, value);

    return (AST_Node*) node;
} /* end of : AST_Node*
              ast_int32(const AST_Pos pos,
                        const int32_t value) */

AST_Node*
ast_float32(const AST_Pos pos,
            const float value)
{
    AST_Const* node = NULL;

    /* allocate memory to the ast node */
    if ((node = mem_malloc(sizeof(AST_Const))) == NULL)
    {
        // TODO : report no memory failure
        return NULL;
    }

    /* initialize the allocated ast node */
    node->type = AST_FLOAT32;
    node->pos = pos;
    node->vtable.get_return_type = ast_const_get_return_type;
    node->vtable.execute = ast_const_execute;
    node->vtable.output = ast_const_output;
    node->vtable.destroy = ast_const_destroy;

    /* set node constant value */
    variant_init_float32(&node->value, value);

    return (AST_Node*) node;
} /* end of : AST_Node*
              ast_float32(const AST_Pos pos,
                          const float value) */

AST_Node*
ast_text(const AST_Pos pos,
         const char* value)
{
    AST_Const* node = NULL;

    /* allocate memory to the ast node */
    if ((node = mem_malloc(sizeof(AST_Const))) == NULL)
    {
        // TODO : report no memory failure
        return NULL;
    }

    /* initialize the allocated ast node */
    node->type = AST_TEXT;
    node->pos = pos;
    node->vtable.get_return_type = ast_const_get_return_type;
    node->vtable.execute = ast_const_execute;
    node->vtable.output = ast_const_output;
    node->vtable.destroy = ast_const_destroy;

    /* set node constant value */
    variant_init_text(&node->value, value);

    return (AST_Node*) node;
} /* end of : AST_Node*
              ast_text(const AST_Pos pos,
                       const char* value) */

/*******************************************************************************
 * INTERNAL FUNCTIONS
 ******************************************************************************/

VType
ast_const_get_return_type(AST_Const* node)
{
    if (node)
    {
        /* demux the type of node */
        switch (node->type)
        {
            case AST_BOOLEAN: return VBOOLEAN;
            case AST_INT32:   return VINT32;
            case AST_FLOAT32: return VFLOAT32;
            case AST_TEXT:    return VTEXT;
            default:          break;
        }
    }

    return VUNKNOWN;
} /* end of : VType
              ast_const_get_return_type(AST_Const* node) */

Variant*
ast_const_execute(AST_Const* node,
                  Variant* result)
{
    if (   node
        && result
        && !runtime_is_returning())
    {
        variant_assign(result, &node->value);
    }

    return result;
} /* end of : Variant*
              ast_const_execute(AST_Const* node,
                                Variant* result) */

void
ast_const_output(AST_Const* node,
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
        switch (node->value.type)
        {
            case VBOOLEAN: printf("%sbool(%s)\n",    prefix, node->value.value.vboolean ? "true" : "false"); break;
            case VINT32:   printf("%sint32(%d)\n",   prefix, node->value.value.vint32);                      break;
            case VFLOAT32: printf("%sfloat32(%f)\n", prefix, node->value.value.vfloat32);                    break;
            case VTEXT:    printf("%stext(%s)\n",    prefix, node->value.value.vtext);                       break;
            default:                                                                                         break;
        }
    }
} /* end of : void
              ast_const_output(AST_Const* node,
                               const size_t level,
                               const char* prefix) */

void
ast_const_destroy(AST_Const** node)
{
    if (   node
        && *node)
    {
        /* uninitialize the stored variant */
        variant_uninit(&(*node)->value);

        /* release the allocated memory */
        mem_free(*node);
        *node = NULL;
    }
} /* end of : void
              ast_const_destroy(AST_Const** node) */
