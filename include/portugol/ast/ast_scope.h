#pragma once

#include <portugol/ast/ast_node.h>

/// @brief
///
/// @return
AST_Node*
ast_scope(void);

/// @brief
///
/// @param name
/// @return
AST_Node*
ast_file(const char* name);

/// @brief
///
/// @param node
/// @return
size_t
ast_count_instrs(AST_Node* node);

/// @brief
///
/// @param node
/// @param instr
/// @return
AST_Node*
ast_push_instr(AST_Node* node,
               AST_Node* instr);
