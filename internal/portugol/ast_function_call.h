#pragma once

#include <portugol/ast.h>

typedef struct AST_FunctionCall
{
    AST_Type type;
    AST_SourcePos pos;

    char* name;

    AST_Node** args;
    int arg_count;
} AST_FunctionCall;

AST_Node**
ast_function_call_arg_push(AST_Node* node,
                           AST_Node** list,
                           int count);

AST_Node*
ast_function_call(char* name,
                  AST_Node** args,
                  int arg_count,
                  AST_SourcePos pos);

Variant
ast_function_call_execute(AST_Node* node,
                          Runtime* runtime);

void
ast_function_call_print(AST_Node* node,
                        int level);

void
ast_function_call_destroy(AST_Node** node);
