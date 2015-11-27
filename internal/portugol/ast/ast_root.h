#pragma once

#include <portugol/ast/ast_root.h>

/// @brief
typedef struct AST_Root
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
        (*get_return_type)(struct AST_Root* node);

        /// @brief
        ///
        /// @param node
        /// @param result
        /// @return
        Variant*
        (*execute)(struct AST_Root* node,
                   Variant* result);

        /// @brief
        ///
        /// @param node
        /// @param level
        /// @param prefix
        /// @return
        void
        (*output)(struct AST_Root* node,
                  const size_t level,
                  const char* prefix);

        /// @brief
        ///
        /// @param node
        void
        (*destroy)(struct AST_Root** node);
    } vtable;

    /// @brief
    struct
    {
        /// @brief
        AST_Node** list;

        /// @brief
        size_t count;
    } files;
} AST_Root;

/// @brief
void
ast_root_init(void);

/// @brief
void
ast_root_uninit(void);

/// @brief
///
/// @param node
/// @return
VType
ast_root_get_return_type(AST_Root* node);

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_root_execute_ex(AST_Root* node,
                    Variant* result);

/// @brief
///
/// @param node
/// @param level
/// @param prefix
void
ast_root_output_ex(AST_Root* node,
                   const size_t level,
                   const char* prefix);

/// @brief
///
/// @param node
void
ast_root_destroy(AST_Root** node);
