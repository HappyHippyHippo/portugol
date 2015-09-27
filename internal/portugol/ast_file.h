#pragma once

#include <portugol/ast.h>

ASTNode*
ast_file(void);

Variant
ast_file_execute(ASTNode* node,
                 Runtime* runtime);

void
ast_file_print(ASTNode* node,
               int level);

void
ast_file_destroy(ASTNode** node);
