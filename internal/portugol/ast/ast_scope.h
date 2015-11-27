#pragma once

#include <portugol/ast/ast_op.h>

/// @brief
typedef struct AST_Scope
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
        (*get_return_type)(struct AST_Scope* node);

        /// @brief
        ///
        /// @param node
        /// @param result
        /// @return
        Variant*
        (*execute)(struct AST_Scope* node,
                   Variant* result);

        /// @brief
        ///
        /// @param node
        /// @param level
        /// @param prefix
        /// @return
        void
        (*output)(struct AST_Scope* node,
                  const size_t level,
                  const char* prefix);

        /// @brief
        ///
        /// @param node
        void
        (*destroy)(struct AST_Scope** node);
    } vtable;

    /// @brief
    char* name;

    /// @brief
    struct
    {
        /// @brief
        AST_Node** list;

        /// @brief
        size_t count;
    } instrs;
} AST_Scope;

/// @brief
///
/// @param type
/// @param name
/// @return
AST_Node*
ast_scope_create(AST_Type type,
                 const char* name);

/// @brief
///
/// @param node
/// @return
VType
ast_scope_get_return_type(AST_Scope* node);

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_scope_execute(AST_Scope* node,
                  Variant* result);

/// @brief
///
/// @param node
/// @param level
/// @param prefix
void
ast_scope_output(AST_Scope* node,
                 const size_t level,
                 const char* prefix);

/// @brief
///
/// @param node
void
ast_scope_destroy(AST_Scope** node);
