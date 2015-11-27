#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <internal/portugol/ast/ast_import.h>
#include <internal/portugol/ast/ast_node.h>
#include <internal/portugol/ast/ast_scope.h>
#include <internal/portugol/ast/ast_root.h>
#include <internal/portugol/lex/lex.h>
#include <internal/portugol/runtime.h>
#include <internal/mem.h>

extern int yyparse();
extern int yyset_in(FILE*);

AST_Root* _ast_root = NULL;

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

AST_Node*
ast_root_load(char* file)
{
    AST_Node* result = NULL;

    ast_filepath = file;
    ast_lex = NULL;
    ast_error = 0;

    /* load code from source file */
#ifdef _MSC_VER
    FILE* fp = NULL;
    fopen_s(&fp, file, "r");
#else
    FILE* fp = fopen(file, "r");
#endif /* _MSC_VER */

    if (fp)
    {
        /* parse the file content */
        yyset_in(fp);
        yyparse();
        fclose(fp);

        /* check for error */
        if (!ast_error)
        {
            /* store the file node to be inserted in the root node */
            result = ast_lex;

            /* file import search cycle */
            AST_Scope* fscope = (AST_Scope*) result;
            for (size_t i = 0; i < fscope->instrs.count; ++i)
            {
                /* check if the iterated node is a import node */
                if (fscope->instrs.list[i]->type == AST_IMPORT)
                {
                    /* load the requested file */
                    ast_root_load(((AST_Import *) fscope->instrs.list[i])->name);
                }
            }

            /* store the file node in the root node */
            ast_root_push(result);
        }
    }

    return result;
} /* end of : AST_Node*
              ast_root_load(char* file) */

AST_Node*
ast_root_push(AST_Node* node)
{
    if (node)
    {
        /* check if the root node singleton is created */
        ast_root_init();

        /* check if the node list is not empty */
        if (_ast_root->files.list)
        {
            /* reallocate/resize the allocated memory of the node list */
            AST_Node** aux = NULL;
            if ((aux = mem_realloc(_ast_root->files.list, sizeof(AST_Node*) * (_ast_root->files.count + 1))) == NULL)
            {
                // TODO : report no memory failure
                return NULL;
            }

            /* store the position of the reallocated list */
            _ast_root->files.list = aux;
        }
        else
        {
            /* allocate memory to the node list */
            if ((_ast_root->files.list = mem_malloc(sizeof(AST_Node*))) == NULL)
            {
                // TODO : report no memory failure
                return NULL;
            }
        }

        /* insert the node in the root node list */
        _ast_root->files.list[_ast_root->files.count] = node;
        _ast_root->files.count++;
    }

    return node;
} /* end of : AST_Node*
              ast_root_push(AST_Node* node) */

Variant*
ast_root_execute(Variant* result)
{
    if (result)
    {
        /* check if the root node singleton is created */
        ast_root_init();

        /* files execution cycle */
        runtime_clear();
        for (size_t i = 0; i < _ast_root->files.count; ++i)
        {
            /* execute the file node */
            ast_execute(_ast_root->files.list[i], result);
        }

        /* add program entry function call */
        AST_Pos pos = {{0, 0}, {0, 0}};
        AST_Node* pentry = ast_function_call(pos, "programa", ast_arg_list());
        ast_execute(pentry, result);

        /* destroy the program entry point call node */
        ast_destroy(&pentry);
    }

    return result;
} /* end of : Variant*
              ast_root_execute(Variant* result) */

void
ast_root_output(void)
{
    /* check if the root node singleton is created */
    ast_root_init();

    /* node output cycle */
    for (size_t i = 0; i < _ast_root->files.count; ++i)
    {
        ast_output(_ast_root->files.list[i], 0, "");
    }
} /* end of : void
              ast_root_output(void) */

void
ast_root_init(void)
{
    if (!_ast_root)
    {
        /* allocate memory to the ast node */
        if ((_ast_root = mem_malloc(sizeof(AST_Root))) == NULL)
        {
            // TODO : report no memory failure
            return ;
        }

        /* initialize the allocated ast root node */
        _ast_root->type = AST_ROOT;
        _ast_root->pos.line.start = 0;
        _ast_root->pos.line.stop = 0;
        _ast_root->pos.column.start = 0;
        _ast_root->pos.column.stop = 0;
        _ast_root->vtable.get_return_type = ast_root_get_return_type;
        _ast_root->vtable.execute = ast_root_execute_ex;
        _ast_root->vtable.output = ast_root_output_ex;
        _ast_root->vtable.destroy = ast_root_destroy;

        /* initialize the root list */
        _ast_root->files.list = NULL;
        _ast_root->files.count = 0;
    }
} /* end of : void
              ast_root_init(void) */

void
ast_root_uninit(void)
{
    if (_ast_root)
    {
        /* node destruction cycle */
        for (size_t i = 0; i < _ast_root->files.count; ++i)
        {
            ast_destroy(&_ast_root->files.list[i]);
        }
        mem_free(_ast_root->files.list);

        /* release the memory for the ast root node */
        mem_free(_ast_root);
        _ast_root = NULL;
    }
} /* end of : void
              ast_root_uninit(void) */

VType
ast_root_get_return_type(AST_Root* node)
{
    return VUNKNOWN;
} /* end of : VType
              ast_root_get_return_type(AST_Root* node) */

Variant*
ast_root_execute_ex(AST_Root* node,
                    Variant* result)
{
    return ast_root_execute(result);
} /* end of : Variant*
              ast_root_execute_ex(AST_Root* node,
                                  Variant* result) */

void
ast_root_output_ex(AST_Root* node,
                   const size_t level,
                   const char* prefix)
{
    ast_root_output();
} /* end of : void
              ast_root_output_ex(AST_Root* node,
                                 const size_t level,
                                 const char* prefix) */

void
ast_root_destroy(AST_Root** node)
{
    ast_root_uninit();
} /* end of : void
              ast_root_destroy(AST_Root** node) */
