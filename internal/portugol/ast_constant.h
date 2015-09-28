#pragma once

#include <portugol/ast.h>

typedef struct AST_Constant
{
    AST_Type type;
    AST_SourcePos pos;

    Variant value;
} AST_Constant;

AST_Node*
ast_boolean(int value,
            AST_SourcePos pos);

AST_Node*
ast_int32(int32_t value,
          AST_SourcePos pos);

AST_Node*
ast_float32(float value,
            AST_SourcePos pos);

AST_Node*
ast_text(char* value,
         AST_SourcePos pos);

Variant
ast_constant_execute(AST_Node* node,
                     Runtime* runtime);

void
ast_constant_print(AST_Node* node,
                   int level,
                   char* prefix);

void
ast_constant_destroy(AST_Node** node);
