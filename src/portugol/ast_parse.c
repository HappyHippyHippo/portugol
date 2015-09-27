#include <stdio.h>
#include <stdlib.h>

#include <internal/portugol/ast.h>
#include <internal/portugol/ast_parse.h>

ASTNode* ast = NULL;
ParseScopeStack* ast_scope_stack = NULL;

ASTNode*
ast_parse_scope_get(void)
{
    if (ast == NULL)
    {
        if ((ast_scope_stack = malloc(sizeof(ParseScopeStack))) == NULL)
            return NULL;

        if ((ast = ast_file()) == NULL)
        {
            free(ast_scope_stack);
            return NULL;
        }

        ast_scope_stack->scope = ast;
        ast_scope_stack->prev = NULL;
    }

    return ast_scope_stack->scope;
}

ASTNode*
ast_parse_scope_push(ASTNode* scope)
{
    if (ast_scope_stack == NULL)
        ast_parse_scope_get();

    ParseScopeStack* parse_scope;
    if ((parse_scope = malloc(sizeof(ParseScopeStack))) == NULL)
        return NULL;

    parse_scope->scope = scope;
    parse_scope->prev = ast_scope_stack;
    ast_scope_stack = parse_scope;

    return ast_scope_stack->scope;
}

ASTNode*
ast_parse_scope_pop(void)
{
    ASTNode* scope = ast_scope_stack->scope;

    if (ast_scope_stack->scope != ast)
    {
        ParseScopeStack* del = ast_scope_stack;
        scope = del->scope;
        ast_scope_stack = ast_scope_stack->prev;
        free(del);
    }

    return scope;
}
