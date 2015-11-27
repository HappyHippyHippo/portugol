#pragma once

#include <portugol/ast/ast_return.h>

/// @brief
typedef struct AST_Return
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
        (*get_return_type)(struct AST_Return* node);

        /// @brief
        ///
        /// @param node
        /// @param result
        /// @return
        Variant*
        (*execute)(struct AST_Return* node,
                   Variant* result);

        /// @brief
        ///
        /// @param node
        /// @param level
        /// @param prefix
        /// @return
        void
        (*output)(struct AST_Return* node,
                  const size_t level,
                  const char* prefix);

        /// @brief
        ///
        /// @param node
        void
        (*destroy)(struct AST_Return** node);
    } vtable;

    /// @brief
    AST_Node* value;
} AST_Return;

/// @brief
///
/// @param node
/// @return
VType
ast_return_get_return_type(AST_Return* node);

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_return_execute(AST_Return* node,
                   Variant* result);

/// @brief
///
/// @param node
/// @param level
/// @param prefix
void
ast_return_output(AST_Return* node,
                  const size_t level,
                  const char* prefix);

/// @brief
///
/// @param node
void
ast_return_destroy(AST_Return** node);
