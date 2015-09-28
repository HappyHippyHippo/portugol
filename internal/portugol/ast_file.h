#pragma once

#include <portugol/ast.h>

AST_Node*
ast_file(void);

Variant
ast_file_execute(AST_Node* node,
                 Runtime* runtime);

void
ast_file_print(AST_Node* node,
               int level,
               char* prefix);

void
ast_file_destroy(AST_Node** node);
