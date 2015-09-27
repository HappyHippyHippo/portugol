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
