#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <internal/portugol/ast/ast_import.h>
#include <internal/portugol/runtime.h>
#include <internal/mem.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

AST_Node*
ast_import(const AST_Pos pos,
           const char* name)
{
    AST_Import* node = NULL;

    if (name)
    {
        /* allocate memory to the ast node */
        if ((node = mem_malloc(sizeof(AST_Import))) == NULL)
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
        node->type = AST_IMPORT;
        node->pos = pos;
        node->vtable.get_return_type = ast_import_get_return_type;
        node->vtable.execute = ast_import_execute;
        node->vtable.output = ast_import_output;
        node->vtable.destroy = ast_import_destroy;

        /* store the import name */
#ifdef _MSC_VER
        strcpy_s(node->name, length + 1, name);
#else
        strcpy(node->name, name);
#endif /* _MSC_VER */
    }

    return (AST_Node*) node;
} /* end of : AST_Node*
              ast_import(const AST_Pos pos,
                         const char* name) */

/*******************************************************************************
 * INTERNAL FUNCTIONS
 ******************************************************************************/

VType
ast_import_get_return_type(AST_Import* node)
{
    return VUNKNOWN;
} /* end of : VType
              ast_import_get_return_type(AST_Import* node) */

Variant*
ast_import_execute(AST_Import* node,
                   Variant* result)
{
    if (   node
        && result
        && !runtime_is_returning())
    {
        // do nothing ... already done ...
    }

    return result;
} /* end of : Variant*
              ast_import_execute(AST_Import* node,
                                 Variant* result) */

void
ast_import_output(AST_Import* node,
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
        printf("%simport(%s)\n", prefix, node->name);
    }
} /* end of : void
              ast_import_output(AST_Import* node,
                                const size_t level,
                                const char* prefix) */

void
ast_import_destroy(AST_Import** node)
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
              ast_import_destroy(AST_Import** node) */
