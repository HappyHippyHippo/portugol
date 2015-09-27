#include <stdlib.h>
#include <string.h>

#include <internal/portugol/ast.h>

ASTNode*
ast_variable(char* name,
             ASTSourcePos pos)
{
    if (name == NULL)
        return NULL;

    ASTVariable* node;
    if ((node = malloc(sizeof(ASTVariable))) != NULL)
    {
        if ((node->name = malloc(strlen(name) + 1)) == NULL)
        {
            free(node);
            return NULL;
        }

        node->type = AST_VARIABLE;
        node->pos = pos;
        strcpy(node->name, name);
    }

    return (ASTNode*)node;
}
