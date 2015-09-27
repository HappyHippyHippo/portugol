#pragma once

#include <portugol/ast.h>

typedef struct ParseAST {
    ASTSourcePos pos;
    ASTNode*     result;
} ParseAST;

typedef struct ParseInt32 {
    ASTSourcePos pos;
    int32_t      result;
} ParseInt32;

typedef struct ParseFloat32 {
    ASTSourcePos pos;
    float        result;
} ParseFloat32;

typedef struct ParseText {
    ASTSourcePos pos;
    char*        result;
} ParseText;

typedef struct ParseToken {
    ASTSourcePos pos;
    int          result;
} ParseToken;

typedef struct ParseScopeStack {
    ASTNode*                scope;
    struct ParseScopeStack* prev;
} ParseScopeStack;

extern ParseScopeStack* ast_scope_stack;

ASTNode*
ast_parse_scope_get(void);

ASTNode*
ast_parse_scope_push(ASTNode* scope);

ASTNode*
ast_parse_scope_pop(void);
