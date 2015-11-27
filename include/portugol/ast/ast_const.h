#pragma once

#include <portugol/ast/ast_node.h>

/// @brief
///
/// @param pos
/// @param value
/// @return
AST_Node*
ast_boolean(const AST_Pos pos,
            const int8_t value);

/// @brief
///
/// @param pos
/// @param value
/// @return
AST_Node*
ast_int32(const AST_Pos pos,
          const int32_t value);

/// @brief
///
/// @param pos
/// @param value
/// @return
AST_Node*
ast_float32(const AST_Pos pos,
            const float value);

/// @brief
///
/// @param pos
/// @param value
/// @return
AST_Node*
ast_text(const AST_Pos pos,
         const char* value);
