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
ast_scope_push(ASTNode* scope,
               ASTNode* decl);

ASTNode*
ast_file(void);
