#pragma once

#include <portugol/ast.h>

typedef struct AST_FunctionParam
{
    VariantType type;
    char*       name;
} AST_FunctionParam;

typedef struct AST_Function
{
    AST_Type type;
    AST_SourcePos pos;

    char* name;

    AST_FunctionParam* params;
    int param_count;

    VariantType return_type;

    AST_Node* scope;
} AST_Function;

AST_FunctionParam
ast_function_param(VariantType type,
                   char* name);

AST_FunctionParam*
ast_function_param_push(AST_FunctionParam param,
                        AST_FunctionParam* list,
                        int count);

AST_Node*
ast_function(char* name,
             AST_FunctionParam* params,
             int param_count,
             VariantType return_type,
             AST_Node* scope,
             AST_SourcePos pos);

AST_Node*
ast_program(AST_Node* scope,
            AST_SourcePos pos);

Variant
ast_function_execute(AST_Node* node,
                     Runtime* runtime);

void
ast_function_print(AST_Node* node,
                   int level);

void
ast_function_destroy(AST_Node** node);
