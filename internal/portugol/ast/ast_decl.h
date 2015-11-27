#pragma once

#include <portugol/ast/ast_decl.h>

/// @brief
typedef struct AST_Decl
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
        (*get_return_type)(struct AST_Decl* node);

        /// @brief
        ///
        /// @param node
        /// @param result
        /// @return
        Variant*
        (*execute)(struct AST_Decl* node,
                   Variant* result);

        /// @brief
        ///
        /// @param node
        /// @param level
        /// @param prefix
        /// @return
        void
        (*output)(struct AST_Decl* node,
                  const size_t level,
                  const char* prefix);

        /// @brief
        ///
        /// @param node
        void
        (*destroy)(struct AST_Decl** node);
    } vtable;

    /// @brief
    char* name;

    /// @brief
    AST_Node* value;
} AST_Decl;

/// @brief
///
/// @param pos
/// @param name
/// @param value
/// @param type
/// @return
AST_Node*
ast_decl(const AST_Pos pos,
         const char* name,
         AST_Node* value,
         AST_Type type);

/// @brief
///
/// @param node
/// @return
VType
ast_decl_get_return_type(AST_Decl* node);

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_decl_execute(AST_Decl* node,
                 Variant* result);

/// @brief
///
/// @param node
/// @param level
/// @param prefix
void
ast_decl_output(AST_Decl* node,
                const size_t level,
                const char* prefix);

/// @brief
///
/// @param node
void
ast_decl_destroy(AST_Decl** node);
