#pragma once

#include <portugol/ast.h>

typedef struct ASTScope
{
    ASTType type;
    ASTSourcePos pos;

    struct
    {
        ASTNode** list;
        size_t size;
        size_t count;
    } instr;
} ASTScope;

ASTNode*
ast_scope(ASTSourcePos pos);

ASTNode*
ast_scope_push(ASTNode* scope,
               ASTNode* inst);

Variant
ast_scope_execute(ASTNode* node,
                  Runtime* runtime);

void
ast_scope_print(ASTNode* node,
                int level);

void
ast_scope_destroy(ASTNode** node);
