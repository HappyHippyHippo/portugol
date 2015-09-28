#pragma once

#include <portugol/ast.h>

typedef struct AST_Decl
{
    AST_Type type;
    AST_SourcePos pos;

    char* name;
    AST_Node* value;
} AST_Decl;

AST_Node*
ast_decl_boolean(char* name,
                 AST_Node* value,
                 AST_SourcePos pos);

AST_Node*
ast_decl_int32(char* name,
               AST_Node* value,
               AST_SourcePos pos);

AST_Node*
ast_decl_float32(char* name,
                 AST_Node* value,
                 AST_SourcePos pos);

AST_Node*
ast_decl_text(char* name,
              AST_Node* value,
              AST_SourcePos pos);

Variant
ast_decl_execute(AST_Node* node,
                 Runtime* runtime);

void
ast_decl_print(AST_Node* node,
               int level);

void
ast_decl_destroy(AST_Node** node);
