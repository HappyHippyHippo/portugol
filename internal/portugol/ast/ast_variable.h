#pragma once

#include <portugol/ast/ast_const.h>

/// @brief
typedef struct AST_Variable
{
    /// @brief
    AST_Type type;

    /// @brief
    AST_Pos pos;

    /// @brief
    struct
    {
        /// @brief
        ///
        /// @param node
        /// @return
        VType
        (*get_return_type)(struct AST_Variable* node);

        /// @brief
        ///
        /// @param node
        /// @param result
        /// @return
        Variant*
        (*execute)(struct AST_Variable* node,
                   Variant* result);

        /// @brief
        ///
        /// @param node
        /// @param level
        /// @param prefix
        /// @return
        void
        (*output)(struct AST_Variable* node,
                  const size_t level,
                  const char* prefix);

        /// @brief
        ///
        /// @param node
        void
        (*destroy)(struct AST_Variable** node);
    } vtable;

    /// @brief
    char* name;
} AST_Variable;

/// @brief
///
/// @param node
/// @return
VType
ast_variable_get_return_type(AST_Variable* node);

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_variable_execute(AST_Variable* node,
                     Variant* result);

/// @brief
///
/// @param node
/// @param level
/// @param prefix
void
ast_variable_output(AST_Variable* node,
                    const size_t level,
                    const char* prefix);

/// @brief
///
/// @param node
void
ast_variable_destroy(AST_Variable** node);
