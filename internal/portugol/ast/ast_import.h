#pragma once

#include <portugol/ast/ast_import.h>

/// @brief
typedef struct AST_Import
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
        (*get_return_type)(struct AST_Import* node);

        /// @brief
        ///
        /// @param node
        /// @param result
        /// @return
        Variant*
        (*execute)(struct AST_Import* node,
                   Variant* result);

        /// @brief
        ///
        /// @param node
        /// @param level
        /// @param prefix
        /// @return
        void
        (*output)(struct AST_Import* node,
                  const size_t level,
                  const char* prefix);

        /// @brief
        ///
        /// @param node
        void
        (*destroy)(struct AST_Import** node);
    } vtable;

    /// @brief
    char* name;
} AST_Import;

/// @brief
///
/// @param node
/// @return
VType
ast_import_get_return_type(AST_Import* node);

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_import_execute(AST_Import* node,
                   Variant* result);

/// @brief
///
/// @param node
/// @param level
/// @param prefix
void
ast_import_output(AST_Import* node,
                  const size_t level,
                  const char* prefix);

/// @brief
///
/// @param node
void
ast_import_destroy(AST_Import** node);
