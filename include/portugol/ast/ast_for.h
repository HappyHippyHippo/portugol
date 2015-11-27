#pragma once

#include <portugol/ast/ast_node.h>

/// @brief
///
/// @param pos
/// @param var
/// @param start
/// @param stop
/// @param step
/// @param scope
/// @return
AST_Node*
ast_for(const AST_Pos pos,
        const char* var,
        AST_Node* start,
        AST_Node* stop,
        AST_Node* step,
        AST_Node* scope);
