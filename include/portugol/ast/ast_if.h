#pragma once

#include <portugol/ast/ast_node.h>

/// @brief
///
/// @param pos
/// @param expr
/// @param strue
/// @param sfalse
/// @return
AST_Node*
ast_if(const AST_Pos pos,
       AST_Node* expr,
       AST_Node* strue,
       AST_Node* sfalse);
