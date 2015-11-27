#pragma once

#include <portugol/ast/ast_node.h>

/// @brief
///
/// @param pos
/// @param name
/// @param value
/// @return
AST_Node*
ast_decl_boolean(const AST_Pos pos,
                 const char* name,
                 AST_Node* value);

/// @brief
///
/// @param pos
/// @param name
/// @param value
/// @return
AST_Node*
ast_decl_int32(const AST_Pos pos,
               const char* name,
               AST_Node* value);

/// @brief
///
/// @param pos
/// @param name
/// @param value
/// @return
AST_Node*
ast_decl_float32(const AST_Pos pos,
                 const char* name,
                 AST_Node* value);

/// @brief
///
/// @param pos
/// @param name
/// @param value
/// @return
AST_Node*
ast_decl_text(const AST_Pos pos,
              const char* name,
              AST_Node* value);
