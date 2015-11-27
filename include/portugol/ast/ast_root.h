#pragma once

#include <portugol/ast/ast_node.h>

/// @brief
///
/// @param file
/// @return
AST_Node*
ast_root_load(char* file);

/// @brief
///
/// @param node
/// @return
AST_Node*
ast_root_push(AST_Node* node);

/// @brief
void
ast_root_clear(void);

/// @brief
///
/// @param result
/// @return
Variant*
ast_root_execute(Variant* result);

/// @brief
void
ast_root_output(void);
