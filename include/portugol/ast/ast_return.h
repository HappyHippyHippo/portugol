#pragma once

#include <portugol/ast/ast_node.h>

/// @brief
///
/// @param pos
/// @param value
/// @return
AST_Node*
ast_return(const AST_Pos pos,
           AST_Node* value);
