#pragma once

#include <portugol/ast.h>

typedef struct ParseAST {
    AST_SourcePos pos;
    AST_Node*     result;
} ParseAST;

typedef struct ParseBool {
    AST_SourcePos pos;
    int          result;
} ParseBool;

typedef struct ParseInt32 {
    AST_SourcePos pos;
    int32_t      result;
} ParseInt32;

typedef struct ParseFloat32 {
    AST_SourcePos pos;
    float        result;
} ParseFloat32;

typedef struct ParseText {
    AST_SourcePos pos;
    char*        result;
} ParseText;

typedef struct ParseToken {
    AST_SourcePos pos;
    int          result;
} ParseToken;

typedef struct ParseFParam {
    AST_SourcePos     pos;
    AST_FunctionParam result;
} ParseFParam;

typedef struct ParseFParams {
    AST_SourcePos      pos;
    AST_FunctionParam* result;
    int                count;
} ParseFParams;

typedef struct ParseFArgs {
    AST_SourcePos pos;
    AST_Node**    result;
    int           count;
} ParseFArgs;

typedef struct ParseScopeStack {
    AST_Node*               scope;
    struct ParseScopeStack* prev;
} ParseScopeStack;

extern ParseScopeStack* ast_scope_stack;

AST_Node*
ast_parse_scope_get(void);

AST_Node*
ast_parse_scope_push(AST_Node* scope);

AST_Node*
ast_parse_scope_pop(void);
