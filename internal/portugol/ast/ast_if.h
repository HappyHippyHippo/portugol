#pragma once

#include <portugol/ast/ast_if.h>

/// @brief
typedef struct AST_If
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
        (*get_return_type)(struct AST_If* node);

        /// @brief
        ///
        /// @param node
        /// @param result
        /// @return
        Variant*
        (*execute)(struct AST_If* node,
                   Variant* result);

        /// @brief
        ///
        /// @param node
        /// @param level
        /// @param prefix
        /// @return
        void
        (*output)(struct AST_If* node,
                  const size_t level,
                  const char* prefix);

        /// @brief
        ///
        /// @param node
        void
        (*destroy)(struct AST_If** node);
    } vtable;

    /// @brief
    AST_Node* expr;

    /// @brief
    AST_Node* strue;

    /// @brief
    AST_Node* sfalse;
} AST_If;

/// @brief
///
/// @param node
/// @return
VType
ast_if_get_return_type(AST_If* node);

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_if_execute(AST_If* node,
               Variant* result);

/// @brief
///
/// @param node
/// @param level
/// @param prefix
void
ast_if_output(AST_If* node,
              const size_t level,
              const char* prefix);

/// @brief
///
/// @param node
void
ast_if_destroy(AST_If** node);
