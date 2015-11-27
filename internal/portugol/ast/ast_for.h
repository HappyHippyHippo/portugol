#pragma once

#include <portugol/ast/ast_for.h>

/// @brief
typedef struct AST_For
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
        (*get_return_type)(struct AST_For* node);

        /// @brief
        ///
        /// @param node
        /// @param result
        /// @return
        Variant*
        (*execute)(struct AST_For* node,
                   Variant* result);

        /// @brief
        ///
        /// @param node
        /// @param level
        /// @param prefix
        /// @return
        void
        (*output)(struct AST_For* node,
                  const size_t level,
                  const char* prefix);

        /// @brief
        ///
        /// @param node
        void
        (*destroy)(struct AST_For** node);
    } vtable;

    /// @brief
    char* var;

    /// @brief
    AST_Node* start;

    /// @brief
    AST_Node* stop;

    /// @brief
    AST_Node* step;

    /// @brief
    AST_Node* scope;
} AST_For;

/// @brief
///
/// @param node
/// @return
VType
ast_for_get_return_type(AST_For* node);

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_for_execute(AST_For* node,
                Variant* result);

/// @brief
///
/// @param node
/// @param level
/// @param prefix
void
ast_for_output(AST_For* node,
               const size_t level,
               const char* prefix);

/// @brief
///
/// @param node
void
ast_for_destroy(AST_For** node);
