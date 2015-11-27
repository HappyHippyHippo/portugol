#pragma once

#include <portugol/ast/ast_while.h>

/// @brief
typedef struct AST_While
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
        (*get_return_type)(struct AST_While* node);

        /// @brief
        ///
        /// @param node
        /// @param result
        /// @return
        Variant*
        (*execute)(struct AST_While* node,
                   Variant* result);

        /// @brief
        ///
        /// @param node
        /// @param level
        /// @param prefix
        /// @return
        void
        (*output)(struct AST_While* node,
                  const size_t level,
                  const char* prefix);

        /// @brief
        ///
        /// @param node
        void
        (*destroy)(struct AST_While** node);
    } vtable;

    /// @brief
    AST_Node* expr;

    /// @brief
    AST_Node* scope;
} AST_While;

/// @brief
///
/// @param node
/// @return
VType
ast_while_get_return_type(AST_While* node);

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_while_execute(AST_While* node,
                  Variant* result);

/// @brief
///
/// @param node
/// @param level
/// @param prefix
void
ast_while_output(AST_While* node,
                 const size_t level,
                 const char* prefix);

/// @brief
///
/// @param node
void
ast_while_destroy(AST_While** node);
