#pragma once

#include <portugol/ast.h>

typedef struct ASTWhile
{
    ASTType type;
    ASTSourcePos pos;

    ASTNode* expr;

    ASTNode* scope;
} ASTWhile;

ASTNode*
ast_while(ASTNode* expr,
          ASTNode* scope,
          ASTSourcePos pos);

Variant
ast_while_execute(ASTNode* node,
                  Runtime* runtime);

void
ast_while_print(ASTNode* node,
                int level);

void
ast_while_destroy(ASTNode** node);
