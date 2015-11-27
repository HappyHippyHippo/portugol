#pragma once

#include <portugol/ast/ast_const.h>

/// @brief
typedef struct AST_Const
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
        (*get_return_type)(struct AST_Const* node);

        /// @brief
        ///
        /// @param node
        /// @param result
        /// @return
        Variant*
        (*execute)(struct AST_Const* node,
                   Variant* result);

        /// @brief
        ///
        /// @param node
        /// @param level
        /// @param prefix
        /// @return
        void
        (*output)(struct AST_Const* node,
                  const size_t level,
                  const char* prefix);

        /// @brief
        ///
        /// @param node
        void
        (*destroy)(struct AST_Const** node);
    } vtable;

    /// @brief
    Variant value;
} AST_Const;

/// @brief
///
/// @param node
/// @return
VType
ast_const_get_return_type(AST_Const* node);

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_const_execute(AST_Const* node,
                  Variant* result);

/// @brief
///
/// @param node
/// @param level
/// @param prefix
void
ast_const_output(AST_Const* node,
                 const size_t level,
                 const char* prefix);

/// @brief
///
/// @param node
void
ast_const_destroy(AST_Const** node);
