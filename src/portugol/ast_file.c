#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/portugol/ast.h>

AST_Node*
ast_file(void)
{
    AST_SourcePos pos;
    memset(&pos, 0, sizeof(AST_SourcePos));

    AST_Node* file = ast_scope(pos);
    file->type = AST_FILE;

    return file;
}

Variant
ast_file_execute(AST_Node* node,
                 Runtime* runtime)
{
    // TODO : store decl ate heap
    // TODO : execute program function
    return ast_scope_execute(node, runtime);
}

void
ast_file_print(AST_Node* node,
               int level,
               char* prefix)
{
    printf("-------------------- AST Tree ---------------------\n");
    printf("file\n");
    for (size_t idx = 0; idx < ((AST_Scope*) node)->instr.count; ++idx)
        ast_print(((AST_Scope*) node)->instr.list[idx], level + 1, "");
    printf("---------------------------------------------------\n");
}

void
ast_file_destroy(AST_Node** node)
{
    ast_scope_destroy(node);
}
