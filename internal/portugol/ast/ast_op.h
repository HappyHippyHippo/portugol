#pragma once

#include <portugol/ast/ast_op.h>

/// @brief
typedef struct AST_Op
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
        (*get_return_type)(struct AST_Op* node);

        /// @brief
        ///
        /// @param node
        /// @param result
        /// @return
        Variant*
        (*execute)(struct AST_Op* node,
                   Variant* result);

        /// @brief
        ///
        /// @param node
        /// @param level
        /// @param prefix
        /// @return
        void
        (*output)(struct AST_Op* node,
                  const size_t level,
                  const char* prefix);

        /// @brief
        ///
        /// @param node
        void
        (*destroy)(struct AST_Op** node);
    } vtable;

    /// @brief
    AST_Node* op1;

    /// @brief
    AST_Node* op2;
} AST_Op;

/// @brief
///
/// @param pos
/// @param op1
/// @param op2
/// @param type
/// @return
AST_Node*
ast_op(const AST_Pos pos,
       AST_Node* op1,
       AST_Node* op2,
       AST_Type type);

/// @brief
///
/// @param node
/// @return
VType
ast_op_get_return_type(AST_Op* node);

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_op_execute(AST_Op* node,
               Variant* result);

/// @brief
///
/// @param node
/// @param level
/// @param prefix
void
ast_op_output(AST_Op* node,
              const size_t level,
              const char* prefix);

/// @brief
///
/// @param node
void
ast_op_destroy(AST_Op** node);
