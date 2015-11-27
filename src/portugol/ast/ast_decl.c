#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <internal/portugol/ast/ast_decl.h>
#include <internal/portugol/runtime.h>
#include <internal/mem.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

AST_Node*
ast_decl_boolean(const AST_Pos pos,
                 const char* name,
                 AST_Node* value)
{
    return ast_decl(pos, name, value, AST_DECL_BOOLEAN);
} /* end of : AST_Node*
              ast_decl_boolean(const AST_Pos pos,
                               const char* name,
                               AST_Node* value) */

AST_Node*
ast_decl_int32(const AST_Pos pos,
               const char* name,
               AST_Node* value)
{
    return ast_decl(pos, name, value, AST_DECL_INT32);
} /* end of : AST_Node*
              ast_decl_int32(const AST_Pos pos,
                             const char* name,
                             AST_Node* value) */

AST_Node*
ast_decl_float32(const AST_Pos pos,
                 const char* name,
                 AST_Node* value)
{
    return ast_decl(pos, name, value, AST_DECL_FLOAT32);
} /* end of : AST_Node*
              ast_decl_float32(const AST_Pos pos,
                               const char* name,
                               AST_Node* value) */

AST_Node*
ast_decl_text(const AST_Pos pos,
              const char* name,
              AST_Node* value)
{
    return ast_decl(pos, name, value, AST_DECL_TEXT);
} /* end of : AST_Node*
              ast_decl_text(const AST_Pos pos,
                            const char* name,
                            AST_Node* value) */

/*******************************************************************************
 * INTERNAL FUNCTIONS
 ******************************************************************************/

AST_Node*
ast_decl(const AST_Pos pos,
         const char* name,
         AST_Node* value,
         AST_Type type)
{
    AST_Decl* node = NULL;

    if (   name
        && value)
    {
        /* allocate memory to the ast node */
        if ((node = mem_malloc(sizeof(AST_Decl))) == NULL)
        {
            // TODO : report no memory failure
            return NULL;
        }

        /* allocate memory to the variable name declaration node */
        size_t length = strlen(name);
        if ((node->name = mem_malloc(length + 1)) == NULL)
        {
            mem_free(node);

            // TODO : report no memory failure
            return NULL;
        }

        /* initialize the allocated ast node */
        node->type = type;
        node->pos = pos;
        node->vtable.get_return_type = ast_decl_get_return_type;
        node->vtable.execute = ast_decl_execute;
        node->vtable.output = ast_decl_output;
        node->vtable.destroy = ast_decl_destroy;

        /* store the declaration name and default expression */
#ifdef _MSC_VER
        strcpy_s(node->name, length + 1, name);
#else
        strcpy(node->name, name);
#endif /* _MSC_VER */
        node->value = value;
    }

    return (AST_Node*) node;
} /* end of : AST_Node*
              ast_decl(const AST_Pos pos,
                       const char* name,
                       AST_Node* value,
                       AST_Type type) */

VType
ast_decl_get_return_type(AST_Decl* node)
{
    if (node)
    {
        /* demux the type of node */
        switch (node->type)
        {
            case AST_DECL_BOOLEAN: return VBOOLEAN;
            case AST_DECL_INT32:   return VINT32;
            case AST_DECL_FLOAT32: return VFLOAT32;
            case AST_DECL_TEXT:    return VTEXT;
            default:          break;
        }
    }

    return VUNKNOWN;
} /* end of : VType
              ast_decl_get_return_type(AST_Decl* node) */

Variant*
ast_decl_execute(AST_Decl* node,
                 Variant* result)
{
    if (   node
        && result
        && !runtime_is_returning())
    {
        /* retrieve the declaration default value */
        ast_execute(node->value, result);

        /* cast the default value to the declaration type */
        switch (node->type)
        {
            case AST_DECL_BOOLEAN : variant_cast(result, VBOOLEAN); break;
            case AST_DECL_INT32 :   variant_cast(result, VINT32);   break;
            case AST_DECL_FLOAT32 : variant_cast(result, VFLOAT32); break;
            case AST_DECL_TEXT :    variant_cast(result, VTEXT);    break;
            default:                                                break;
        }

        /* allocate memory in the runtime for the declaration */
        Variant* store = runtime_add(node->name, result->type);
        if (store)
        {
            /* assign the calculated value to the allocated memory */
            variant_assign(store, result);
        }
    }

    return result;
} /* end of : Variant*
              ast_decl_execute(AST_Decl* node,
                               Variant* result) */

void
ast_decl_output(AST_Decl* node,
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
            case AST_DECL_BOOLEAN: printf("%sdeclare > %s(bool)\n",    prefix, node->name); break;
            case AST_DECL_INT32:   printf("%sdeclare > %s(int32)\n",   prefix, node->name); break;
            case AST_DECL_FLOAT32: printf("%sdeclare > %s(float32)\n", prefix, node->name); break;
            case AST_DECL_TEXT:    printf("%sdeclare > %s(text)\n",    prefix, node->name); break;
            default:                                                              break;
        }

        /* present the declaration assigning expression */
        ast_output(node->value, level + 1, "value > ");
    }
} /* end of : void
              ast_decl_output(AST_Decl* node,
                              const size_t level,
                              const char* prefix) */

void
ast_decl_destroy(AST_Decl** node)
{
    if (   node
        && *node)
    {
        /* destroy the stored default value ast node */
        ast_destroy(&(*node)->value);

        /* release the allocated memory */
        mem_free((*node)->name);
        mem_free(*node);
        *node = NULL;
    }
} /* end of : void
              ast_decl_destroy(AST_Decl** node) */
