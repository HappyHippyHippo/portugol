#include <portugol/ast/ast_function.h>

/// @brief
typedef struct AST_Param
{
    /// @brief
    AST_Pos pos;

    /// @brief
    VType type;

    /// @brief
    char* name;
} AST_Param;

/// @brief
struct AST_ParamList
{
    /// @brief
    AST_Param* list;

    /// @brief
    size_t count;
};

/// @brief
typedef struct AST_Function
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
        (*get_return_type)(struct AST_Function* node);

        /// @brief
        ///
        /// @param node
        /// @param result
        /// @return
        Variant*
        (*execute)(struct AST_Function* node,
                   Variant* result);

        /// @brief
        ///
        /// @param node
        /// @param level
        /// @param prefix
        /// @return
        void
        (*output)(struct AST_Function* node,
                  const size_t level,
                  const char* prefix);

        /// @brief
        ///
        /// @param node
        void
        (*destroy)(struct AST_Function** node);
    } vtable;

    /// @brief
    char* name;

    /// @brief
    AST_ParamList* params;

    /// @brief
    VType return_type;

    /// @brief
    AST_Node* scope;
} AST_Function;

/// @brief
///
/// @param node
/// @return
VType
ast_function_get_return_type(AST_Function* node);

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_function_execute(AST_Function* node,
                     Variant* result);

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_function_called(AST_Function* node,
                    Variant* result);

/// @brief
///
/// @param node
/// @param level
/// @param prefix
void
ast_function_output(AST_Function* node,
                    const size_t level,
                    const char* prefix);

/// @brief
///
/// @param node
void
ast_function_destroy(AST_Function** node);

/// @brief
struct AST_ArgList
{
    /// @brief
    AST_Node** list;

    /// @brief
    size_t count;
};

/// @brief
typedef struct AST_FunctionCall
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
        (*get_return_type)(struct AST_FunctionCall* node);

        /// @brief
        ///
        /// @param node
        /// @param result
        /// @return
        Variant*
        (*execute)(struct AST_FunctionCall* node,
                   Variant* result);

        /// @brief
        ///
        /// @param node
        /// @param level
        /// @param prefix
        /// @return
        void
        (*output)(struct AST_FunctionCall* node,
                  const size_t level,
                  const char* prefix);

        /// @brief
        ///
        /// @param node
        void
        (*destroy)(struct AST_FunctionCall** node);
    } vtable;

    /// @brief
    char* name;

    /// @brief
    AST_ArgList* args;
} AST_FunctionCall;

/// @brief
///
/// @param node
/// @return
VType
ast_function_call_get_return_type(AST_FunctionCall* node);

/// @brief
///
/// @param node
/// @param result
/// @return
Variant*
ast_function_call_execute(AST_FunctionCall* node,
                          Variant* result);

/// @brief
///
/// @param node
/// @param level
/// @param prefix
void
ast_function_call_output(AST_FunctionCall* node,
                         const size_t level,
                         const char* prefix);

/// @brief
///
/// @param node
void
ast_function_call_destroy(AST_FunctionCall** node);
