#pragma once

#include <portugol/ast.h>

typedef struct ASTConstant
{
    ASTType type;
    ASTSourcePos pos;

    Variant value;
} ASTConstant;

ASTNode*
ast_boolean(int value,
            ASTSourcePos pos);

ASTNode*
ast_int32(int32_t value,
          ASTSourcePos pos);

ASTNode*
ast_float32(float value,
            ASTSourcePos pos);

ASTNode*
ast_text(char* value,
         ASTSourcePos pos);

Variant
ast_constant_execute(ASTNode* node,
                     Runtime* runtime);

void
ast_constant_print(ASTNode* node,
                   int level);

void
ast_constant_destroy(ASTNode** node);
