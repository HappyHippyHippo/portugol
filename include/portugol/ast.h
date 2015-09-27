#pragma once

#include <portugol/runtime.h>
#include <portugol/variant.h>

typedef enum
{
    AST_CONST_BOOLEAN,
    AST_CONST_INT32,
    AST_CONST_FLOAT32,
    AST_CONST_TEXT,
    AST_DECL_BOOLEAN,
    AST_DECL_INT32,
    AST_DECL_FLOAT32,
    AST_DECL_TEXT,
    AST_VARIABLE,
    AST_OP_ADD,
    AST_OP_SUBTRACT,
    AST_OP_MULTIPLY,
    AST_OP_DIVIDE,
    AST_OP_REMAINDER,
    AST_OP_EQUAL,
    AST_OP_INEQUAL,
    AST_OP_GREATER,
    AST_OP_GREATER_OR_EQUAL,
    AST_OP_LESSER,
    AST_OP_LESSER_OR_EQUAL,
    AST_OP_POSITIVE,
    AST_OP_NEGATIVE,
    AST_OP_ASSIGN,
    AST_OP_AND,
    AST_OP_OR,
    AST_OP_XOR,
    AST_OP_NOT,
    AST_SCOPE,
    AST_FILE,
    AST_IF,
} ASTType;

typedef struct ASTSourcePos
{
    int lstart;
    int cstart;
    int lend;
    int cend;
} ASTSourcePos;

typedef struct
{
    ASTType type;
    ASTSourcePos pos;
} ASTNode;

extern ASTNode* ast;

Variant
ast_execute(ASTNode* node,
            Runtime* runtime);

void
ast_print(ASTNode* node,
          int level);

void
ast_destroy(ASTNode** node);
