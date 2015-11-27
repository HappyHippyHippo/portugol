#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <internal/portugol/ast/ast_node.h>
#include <internal/portugol/ast/ast_scope.h>
#include <internal/portugol/runtime.h>
#include <internal/mem.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

AST_Node*
ast_scope(void)
{
    return ast_scope_create(AST_SCOPE,
                            NULL);
} /* end of : AST_Node*
              ast_scope(void) */

AST_Node*
ast_file(const char* name)
{
    return ast_scope_create(AST_FILE,
                            name);
} /* end of : AST_Node*
              ast_file(const char* name) */

size_t
ast_count_instrs(AST_Node* node)
{
    if (node)
    {
        return ((AST_Scope*) node)->instrs.count;
    }

    return 0;
} /* end of : size_t
              ast_count_instrs(AST_Node* node) */

AST_Node*
ast_push_instr(AST_Node* node,
               AST_Node* instr)
{
    if (   node
        && instr)
    {
        AST_Scope* scope = (AST_Scope*) node;

        /* check if the scope instruction list is not empty */
        if (scope->instrs.list)
        {
            /* reallocate/resize the allocated memory of the scope instruction list */
            AST_Node** aux;
            if ((aux = mem_realloc(scope->instrs.list, sizeof(AST_Node*) * (scope->instrs.count + 1))) == NULL)
            {
                // TODO : report no memory failure
                return node;
            }

            /* store the position of the reallocated list */
            scope->instrs.list = aux;

            /* update the position of the scope node */
            node->pos = instr->pos;
        }
        else
        {
            /* allocate memory to the scope instruction list */
            if ((scope->instrs.list = mem_malloc(sizeof(AST_Node*))) == NULL)
            {
                // TODO : report no memory failure
                return node;
            }

            /* update the position of the scope node */
            if (   (instr->pos.line.start < node->pos.line.start)
                || (   instr->pos.line.start == node->pos.line.start
                    && instr->pos.column.start < node->pos.column.start));
            {
                node->pos.line.start = instr->pos.line.start;
                node->pos.column.start = instr->pos.column.start;
            }

            if (   (instr->pos.line.stop > node->pos.line.stop)
                || (   instr->pos.line.stop == node->pos.line.stop
                    && instr->pos.column.stop > node->pos.column.stop));
            {
                node->pos.line.stop = instr->pos.line.stop;
                node->pos.column.stop = instr->pos.column.stop;
            }
        }

        /* store the request instruction in the scope instruction list */
        scope->instrs.list[scope->instrs.count] = instr;
        scope->instrs.count++;
    }

    return node;
} /* end of : AST_Node*
              ast_push_instr(AST_Node* node,
                             AST_Node* instr) */

/*******************************************************************************
 * INTERNAL FUNCTIONS
 ******************************************************************************/

AST_Node*
ast_scope_create(AST_Type type,
                 const char* name)
{
    AST_Scope* node = NULL;

    /* allocate memory to the ast node */
    if ((node = mem_malloc(sizeof(AST_Scope))) == NULL)
    {
        // TODO : report no memory failure
        return NULL;
    }

    size_t length = name ? strlen(name) : 0;
    if (   name
        && ((node->name = mem_malloc(length + 1)) == NULL))
    {
        mem_free(node);

        // TODO : report no memory failure
        return NULL;
    }

    /* initialize the allocated ast node */
    node->type = type;
    node->pos.line.start = 0;
    node->pos.column.start = 0;
    node->pos.line.stop = 0;
    node->pos.column.stop = 0;
    node->vtable.get_return_type = ast_scope_get_return_type;
    node->vtable.execute = ast_scope_execute;
    node->vtable.output = ast_scope_output;
    node->vtable.destroy = ast_scope_destroy;

    /* initialize the scope instruction list */
    node->instrs.list = NULL;
    node->instrs.count = 0;

    if (name)
    {
#ifdef _MSC_VER
        strcpy_s(node->name, length + 1, name);
#else
        strcpy(node->name, name);
#endif /* _MSC_VER */
    }

    return (AST_Node*) node;
} /* end of : AST_Node*
              ast_scope_create(AST_Type type,
                               const char* name) */

VType
ast_scope_get_return_type(AST_Scope* node)
{
    return VUNKNOWN;
} /* end of : VType
              ast_scope_get_return_type(AST_Scope* node) */

Variant*
ast_scope_execute(AST_Scope* node,
                  Variant* result)
{
    if (   node
        && result
        && !runtime_is_returning())
    {
        /* check if is to create a runtime scope */
        if (node->type == AST_SCOPE)
        {
            runtime_stack_push_scope();
        }

        /* scope stored instructions execution cycle */
        for (size_t i = 0; i < node->instrs.count && !runtime_is_returning(); ++i)
        {
            ast_execute(node->instrs.list[i], result);
        }

        /* check if is to pop the created runtime scope */
        if (node->type == AST_SCOPE)
        {
            runtime_stack_pop();
        }
    }

    return result;
} /* end of : Variant*
              ast_scope_execute(AST_Scope* node,
                                Variant* result) */

void
ast_scope_output(AST_Scope* node,
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
            case AST_SCOPE: printf("%sscope\n", prefix);                 break;
            case AST_FILE:  printf("%sfile (%s)\n", prefix, node->name); break;
            default:                                                     break;
        }

        /* scope stored instructions presentation */
        for (size_t i = 0; i < node->instrs.count; ++i)
        {
            ast_output(node->instrs.list[i], level + 1, "");
        }
    }
} /* end of: void
             ast_scope_output(AST_Scope* node,
                              const size_t level,
                              const char* prefix) */

void
ast_scope_destroy(AST_Scope** node)
{
    if (   node
        || *node)
    {
        /* destroy the scope stored instructions */
        for (size_t i = 0; i < (*node)->instrs.count; ++i)
        {
            ast_destroy(&(*node)->instrs.list[i]);
        }
        mem_free((*node)->instrs.list);

        /* release the allocated memory */
        if ((*node)->name)
            mem_free((*node)->name);
        mem_free(*node);
        *node = NULL;
    }
} /* end of : void
              ast_scope_destroy(AST_Scope** node) */
