#pragma once

#include <portugol/ast.h>

typedef struct ASTDecl
{
    ASTType type;
    ASTSourcePos pos;

    char* name;
    ASTNode* value;
} ASTDecl;

ASTNode*
ast_decl_boolean(char* name,
                 ASTNode* value,
                 ASTSourcePos pos);

ASTNode*
ast_decl_int32(char* name,
               ASTNode* value,
               ASTSourcePos pos);

ASTNode*
ast_decl_float32(char* name,
                 ASTNode* value,
                 ASTSourcePos pos);

ASTNode*
ast_decl_text(char* name,
              ASTNode* value,
              ASTSourcePos pos);

Variant
ast_decl_execute(ASTNode* node,
                 Runtime* runtime);

void
ast_decl_print(ASTNode* node,
               int level);

void
ast_decl_destroy(ASTNode** node);
