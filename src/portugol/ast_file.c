#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/portugol/ast.h>

ASTNode*
ast_file(void)
{
    ASTSourcePos pos;
    memset(&pos, 0, sizeof(ASTSourcePos));

    ASTNode* file = ast_scope(pos);
    file->type = AST_FILE;

    return file;
}

Variant
ast_file_execute(ASTNode* node,
                 Runtime* runtime)
{
    return ast_scope_execute(node, runtime);
}

void
ast_file_print(ASTNode* node,
               int level)
{
    printf("-------------------- AST Tree ---------------------\n");
    printf("+file\n");
    for (size_t idx = 0; idx < ((ASTScope*) node)->instr.count; ++idx)
        ast_print(((ASTScope*) node)->instr.list[idx], level + 1);
    printf("---------------------------------------------------\n");
}

void
ast_file_destroy(ASTNode** node)
{
    ast_scope_destroy(node);
}
