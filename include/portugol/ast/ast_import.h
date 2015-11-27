#pragma once

#include <portugol/ast/ast_node.h>

/// @brief
///
/// @param pos
/// @param name
/// @return
AST_Node*
ast_import(const AST_Pos pos,
           const char* name);
