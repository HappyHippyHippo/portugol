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
    AST_WHILE,
    AST_FOR,
    AST_FUNCTION,
    AST_FUNCTION_CALL,
    AST_RETURN
} AST_Type;

typedef struct AST_SourcePos
{
    int lstart;
    int cstart;
    int lend;
    int cend;
} AST_SourcePos;

typedef struct
{
    AST_Type type;
    AST_SourcePos pos;
} AST_Node;

extern AST_Node* ast;
extern int ast_error;

Variant
ast_execute(AST_Node* node,
            Runtime* runtime);

void
ast_print(AST_Node* node,
          int level,
          char* prefix);

void
ast_destroy(AST_Node** node);

// TODO : Semantic analyzer
/*
VariantType
ast_return_type(AST_Node* node);

int
ast_validate(AST_Node* node);
*/
