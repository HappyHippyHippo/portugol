#pragma once

#include <portugol/ast/ast_node.h>

/// @brief
///
/// @param pos
/// @param expr
/// @param scope
/// @return
AST_Node*
ast_while(const AST_Pos pos,
          AST_Node* expr,
          AST_Node* scope);
