#pragma once

#include <portugol/ast.h>

typedef struct ASTFor
{
    ASTType type;
    ASTSourcePos pos;

    char* variable;
    ASTNode* start;
    ASTNode* end;
    ASTNode* step;

    ASTNode* scope;
} ASTFor;

ASTNode*
ast_for(char* variable,
        ASTNode* start,
        ASTNode* end,
        ASTNode* step,
        ASTNode* scope,
        ASTSourcePos pos);

Variant
ast_for_execute(ASTNode* node,
                Runtime* runtime);

void
ast_for_print(ASTNode* node,
              int level);

void
ast_for_destroy(ASTNode** node);
