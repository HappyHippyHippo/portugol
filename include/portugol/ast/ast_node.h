#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <portugol/variant.h>

/// @brief
typedef enum
{
    /// @brief
    AST_UNKNOWN,

    /// @brief
    AST_ROOT,

    /// @brief
    AST_BOOLEAN,

    /// @brief
    AST_INT32,

    /// @brief
    AST_FLOAT32,

    /// @brief
    AST_TEXT,

    /// @brief
    AST_DECL_BOOLEAN,

    /// @brief
    AST_DECL_INT32,

    /// @brief
    AST_DECL_FLOAT32,

    /// @brief
    AST_DECL_TEXT,

    /// @brief
    AST_VARIABLE,

    /// @brief
    AST_OP_ADD,

    /// @brief
    AST_OP_SUBTRACT,

    /// @brief
    AST_OP_MULTIPLY,

    /// @brief
    AST_OP_DIVIDE,

    /// @brief
    AST_OP_REMAINDER,

    /// @brief
    AST_OP_EQUAL,

    /// @brief
    AST_OP_INEQUAL,

    /// @brief
    AST_OP_GREATER,

    /// @brief
    AST_OP_GREATER_OR_EQUAL,

    /// @brief
    AST_OP_LESSER,

    /// @brief
    AST_OP_LESSER_OR_EQUAL,

    /// @brief
    AST_OP_AND,

    /// @brief
    AST_OP_OR,

    /// @brief
    AST_OP_XOR,

    /// @brief
    AST_OP_NEGATE,

    /// @brief
    AST_OP_NEGATIVE,

    /// @brief
    AST_OP_ASSIGN,

    /// @brief
    AST_SCOPE,

    /// @brief
    AST_FILE,

    /// @brief
    AST_IMPORT,

    /// @brief
    AST_FUNCTION,

    /// @brief
    AST_FUNCTION_CALL,

    /// @brief
    AST_RETURN,

    /// @brief
    AST_IF,

    /// @brief
    AST_WHILE,

    /// @brief
    AST_FOR
} AST_Type;

/// @brief
typedef struct AST_Node AST_Node;

/// @brief
typedef struct AST_Pos
{
    /// @brief
    struct
    {
        /// @brief
        size_t start;

        /// @brief
        size_t stop;
    } line;

    /// @brief
    struct
    {
        /// @brief
        size_t start;

        /// @brief
        size_t stop;
    } column;
} AST_Pos;

/// @brief
///
/// @param node
/// @return
AST_Type
ast_get_type(AST_Node* node);

/// @brief
///
/// @param node
/// @return
AST_Pos
ast_get_position(AST_Node* node);

/// @brief
///
/// @param node
/// @return
VType
ast_get_return_type(AST_Node* node);

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_execute(AST_Node* node,
            Variant* result);

/// @brief
///
/// @param node
/// @param level
/// @param prefix
void
ast_output(AST_Node* node,
           const size_t level,
           const char* prefix);

/// @brief
///
/// @param node
void
ast_destroy(AST_Node** node);
