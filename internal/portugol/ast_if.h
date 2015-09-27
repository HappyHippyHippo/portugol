#pragma once

#include <portugol/ast.h>

typedef struct ASTIf
{
    ASTType type;
    ASTSourcePos pos;

    ASTNode* expr;

    ASTNode* chk_true;
    ASTNode* chk_false;
} ASTIf;

ASTNode*
ast_if(ASTNode* expr,
       ASTNode* chk_true,
       ASTNode* chk_false,
       ASTSourcePos pos);

Variant
ast_if_execute(ASTNode* node,
               Runtime* runtime);

void
ast_if_print(ASTNode* node,
             int level);

void
ast_if_destroy(ASTNode** node);
