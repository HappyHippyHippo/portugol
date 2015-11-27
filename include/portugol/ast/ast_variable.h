#pragma once

#include <portugol/ast/ast_node.h>

/// @brief
///
/// @param pos
/// @param name
/// @return
AST_Node*
ast_variable(const AST_Pos pos,
             const char* name);
