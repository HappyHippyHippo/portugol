#pragma once

#include <portugol/ast.h>

typedef struct AST_Scope
{
    AST_Type type;
    AST_SourcePos pos;

    struct
    {
        AST_Node** list;
        size_t size;
        size_t count;
    } inst;
} AST_Scope;

AST_Node*
ast_scope(AST_SourcePos pos);

AST_Node*
ast_scope_push(AST_Node* scope,
               AST_Node* inst);

Variant
ast_scope_execute(AST_Node* node,
                  Runtime* runtime);

void
ast_scope_print(AST_Node* node,
                int level,
                char* prefix);

void
ast_scope_destroy(AST_Node** node);
