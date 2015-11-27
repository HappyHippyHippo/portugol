#pragma once

#include <internal/portugol/ast/ast_function.h>

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_system_function_output(struct AST_FunctionCall* node,
                           Variant* result);
