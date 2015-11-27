#pragma once

#include <portugol/ast/ast_node.h>

typedef struct AST_ParamList AST_ParamList;
typedef struct AST_ArgList AST_ArgList;

/// @brief
///
/// @return
AST_ParamList*
ast_param_list(void);

/// @brief
///
/// @param list
/// @return
size_t
ast_param_list_count(AST_ParamList* list);

/// @brief
///
/// @param list
/// @param pos
/// @param type
/// @param name
/// @return
AST_ParamList*
ast_param_list_add(AST_ParamList* list,
                   AST_Pos pos,
                   VType type,
                   const char* name);

/// @brief
///
/// @param pos
/// @param name
/// @param params
/// @param return_type
/// @param scope
/// @return
AST_Node*
ast_function(AST_Pos pos,
             const char* name,
             AST_ParamList* params,
             VType return_type,
             AST_Node* scope);

/// @brief
///
/// @return
AST_ArgList*
ast_arg_list(void);

/// @brief
///
/// @param list
/// @return
size_t
ast_arg_list_count(AST_ArgList* list);

/// @brief
///
/// @param list
/// @param arg
/// @return
AST_ArgList*
ast_arg_list_add(AST_ArgList* list,
                 AST_Node* arg);

/// @brief
///
/// @param pos
/// @param name
/// @param args
/// @return
AST_Node*
ast_function_call(AST_Pos pos,
                  const char* name,
                  AST_ArgList* args);
