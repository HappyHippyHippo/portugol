%{
#include <stdio.h>
#include <stdint.h>

#include <internal/portugol/ast.h>

extern int yylex();
extern int yyget_lineno();
void yyerror(const char *s) { printf("ERROR: %s at line %d\n", s, yyget_lineno()); }

%}

%union { ParseAST     ast;
         ParseInt32   int32;
         ParseFloat32 float32;
         ParseText    text;
         ParseToken   token;
         ASTNode*     global;
}

%token <int32>   TOK_VAL_NUMBER
%token <float32> TOK_VAL_FPNUMBER
%token <text>    TOK_VAL_TEXT TOK_IDENTIFIER
%token <token>   TOK_BOOLEAN TOK_INTEGER TOK_FLOAT TOK_TEXT
%token <token>   TOK_EOL TOK_COMA

%token <token>   TOK_OPEN_PAREN TOK_CLOSE_PAREN
%token <token>   TOK_OP_NOT
%token <token>   TOK_OP_MULTIPLY TOK_OP_DIVIDE TOK_OP_REMAINDER
%token <token>   TOK_OP_ADD TOK_OP_SUBTRACT 
%token <token>   TOK_OP_EQUAL TOK_OP_INEQUAL
%token <token>   TOK_OP_GREATER TOK_OP_GREATER_OR_EQUAL TOK_OP_LESSER TOK_OP_LESSER_OR_EQUAL
%token <token>   TOK_OP_AND
%token <token>   TOK_OP_OR TOK_OP_XOR
%token <token>   TOK_OP_ASSIGN

%left TOK_OP_ASSIGN
%left TOK_OP_OR TOK_OP_XOR
%left TOK_OP_AND
%left TOK_OP_GREATER TOK_OP_GREATER_OR_EQUAL TOK_OP_LESSER TOK_OP_LESSER_OR_EQUAL
%left TOK_OP_EQUAL TOK_OP_INEQUAL
%left TOK_OP_ADD TOK_OP_SUBTRACT
%left TOK_OP_MULTIPLY TOK_OP_DIVIDE TOK_OP_REMAINDER
%left TOK_OP_NOT
%left TOK_OPEN_PAREN TOK_CLOSE_PAREN

%type <ast> global_instrs global_instr decl assign expr variable constant

%start global_instrs

%locations

%%

global_instrs : global_instrs global_instr {
                            if ($2.result != NULL)
                                ast_scope_push(ast_parse_scope_get(), $2.result);
                            $$ = $2;
                        }
              | global_instr {
                            if ($1.result != NULL)
                                ast_scope_push(ast_parse_scope_get(), $1.result);
                            $$ = $1;
                        }
              ;

global_instr : decl TOK_EOL {
                            $$ = $1;
                        }
             | assign TOK_EOL {
                            $$ = $1;
                        }
             | expr TOK_EOL {
                            $$ = $1;
                        }
             | TOK_EOL {
                            ParseAST ast;
                            ast.pos    = $1.pos;
                            ast.result = NULL;
                            $$ = ast;
                        }
             ;

decl : TOK_IDENTIFIER TOK_COMA TOK_BOOLEAN {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_decl_boolean($1.result, ast_boolean(0, ast.pos), ast.pos);
                            $$ = ast;
/*
                            printf("boolean decl found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                            free($1.result);
                        }
     | TOK_IDENTIFIER TOK_COMA TOK_BOOLEAN TOK_OP_ASSIGN expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $5.pos.lend;
                            ast.pos.cend   = $5.pos.cend;
                            ast.result     = ast_decl_boolean($1.result, $5.result, ast.pos);
                            $$ = ast;
/*
                            printf("boolean decl found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                            free($1.result);
                        }
     | TOK_IDENTIFIER TOK_COMA TOK_INTEGER {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_decl_int32($1.result, ast_int32(0, ast.pos), ast.pos);
                            $$ = ast;
/*
                            printf("int32 decl found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                            free($1.result);
                        }
     | TOK_IDENTIFIER TOK_COMA TOK_INTEGER TOK_OP_ASSIGN expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $5.pos.lend;
                            ast.pos.cend   = $5.pos.cend;
                            ast.result     = ast_decl_int32($1.result, $5.result, ast.pos);
                            $$ = ast;
/*
                            printf("int32 decl found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                            free($1.result);
                        }
     | TOK_IDENTIFIER TOK_COMA TOK_FLOAT {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_decl_float32($1.result, ast_float32(0, ast.pos), ast.pos);
                            $$ = ast;
/*
                            printf("float32 decl found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                            free($1.result);
                        }
     | TOK_IDENTIFIER TOK_COMA TOK_FLOAT TOK_OP_ASSIGN expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $5.pos.lend;
                            ast.pos.cend   = $5.pos.cend;
                            ast.result     = ast_decl_float32($1.result, $5.result, ast.pos);
                            $$ = ast;
/*
                            printf("float32 decl found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                            free($1.result);
                        }
     | TOK_IDENTIFIER TOK_COMA TOK_TEXT {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_decl_text($1.result, ast_text("", ast.pos), ast.pos);
                            $$ = ast;
/*
                            printf("text decl found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                            free($1.result);
                        }
     | TOK_IDENTIFIER TOK_COMA TOK_TEXT TOK_OP_ASSIGN expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $5.pos.lend;
                            ast.pos.cend   = $5.pos.cend;
                            ast.result     = ast_decl_text($1.result, $5.result, ast.pos);
                            $$ = ast;
/*
                            printf("text decl found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                            free($1.result);
                        }
     ;

assign : variable TOK_OP_ASSIGN expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_op_binary($1.result, $3.result, AST_OP_ASSIGN, ast.pos);
                            $$ = ast;
/*
                            printf("assign op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
       ;

expr : expr TOK_OP_ADD expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_op_binary($1.result, $3.result, AST_OP_ADD, ast.pos);
                            $$ = ast;
/*
                            printf("add op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | expr TOK_OP_SUBTRACT expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_op_binary($1.result, $3.result, AST_OP_SUBTRACT, ast.pos);
                            $$ = ast;
/*
                            printf("subtract op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | expr TOK_OP_MULTIPLY expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_op_binary($1.result, $3.result, AST_OP_MULTIPLY, ast.pos);
                            $$ = ast;
/*
                            printf("multiply op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | expr TOK_OP_DIVIDE expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_op_binary($1.result, $3.result, AST_OP_DIVIDE, ast.pos);
                            $$ = ast;
/*
                            printf("divide op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | expr TOK_OP_REMAINDER expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_op_binary($1.result, $3.result, AST_OP_REMAINDER, ast.pos);
                            $$ = ast;
/*
                            printf("remainder op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | expr TOK_OP_EQUAL expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_op_binary($1.result, $3.result, AST_OP_EQUAL, ast.pos);
                            $$ = ast;
/*
                            printf("equal op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | expr TOK_OP_INEQUAL expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_op_binary($1.result, $3.result, AST_OP_INEQUAL, ast.pos);
                            $$ = ast;
/*
                            printf("inequal op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | expr TOK_OP_GREATER expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_op_binary($1.result, $3.result, AST_OP_GREATER, ast.pos);
                            $$ = ast;
/*
                            printf("greater op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | expr TOK_OP_GREATER_OR_EQUAL expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_op_binary($1.result, $3.result, AST_OP_GREATER_OR_EQUAL, ast.pos);
                            $$ = ast;
/*
                            printf("greater_or_equal op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | expr TOK_OP_LESSER expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_op_binary($1.result, $3.result, AST_OP_LESSER, ast.pos);
                            $$ = ast;
/*
                            printf("lesser op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | expr TOK_OP_LESSER_OR_EQUAL expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_op_binary($1.result, $3.result, AST_OP_LESSER_OR_EQUAL, ast.pos);
                            $$ = ast;
/*
                            printf("lesser_or_equal op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | expr TOK_OP_AND expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_op_binary($1.result, $3.result, AST_OP_AND, ast.pos);
                            $$ = ast;
/*
                            printf("and op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | expr TOK_OP_OR expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_op_binary($1.result, $3.result, AST_OP_OR, ast.pos);
                            $$ = ast;
/*
                            printf("or op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | expr TOK_OP_XOR expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $3.pos.lend;
                            ast.pos.cend   = $3.pos.cend;
                            ast.result     = ast_op_binary($1.result, $3.result, AST_OP_XOR, ast.pos);
                            $$ = ast;
/*
                            printf("xor op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | TOK_OP_NOT expr {
                            ParseAST ast;
                            ast.pos.lstart = $1.pos.lstart;
                            ast.pos.cstart = $1.pos.cstart;
                            ast.pos.lend   = $2.pos.lend;
                            ast.pos.cend   = $2.pos.cend;
                            ast.result     = ast_op_unary($2.result, AST_OP_NOT, ast.pos);
                            $$ = ast;
/*
                            printf("not op found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | TOK_OPEN_PAREN expr TOK_CLOSE_PAREN {
                            ParseAST ast;
                            ast.pos.lstart  = $1.pos.lstart;
                            ast.pos.cstart  = $1.pos.cstart;
                            ast.pos.lend    = $3.pos.lend;
                            ast.pos.cend    = $3.pos.cend;
                            ast.result      = $2.result;
                            ast.result->pos = ast.pos;
                            $$ = ast;
/*
                            printf("parenthesis found : %d:%d -> %d:%d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend);
*/
                        }
     | variable {
                            $$ = $1;
                        }
     | constant {
                            $$ = $1;
                        }
     ;

constant : TOK_VAL_NUMBER {
                            ParseAST ast;
                            ast.pos    = $1.pos;
                            ast.result = ast_int32($1.result, ast.pos);
                            $$ = ast;
/*
                            printf("integer found : %d:%d -> %d:%d >> %d\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend,
                                   $1.result);
*/
                        }
         | TOK_VAL_FPNUMBER {
                            ParseAST ast;
                            ast.pos    = $1.pos;
                            ast.result = ast_float32($1.result, ast.pos);
                            $$ = ast;
/*
                            printf("float found : %d:%d -> %d:%d >> %f\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend,
                                   $1.result);
*/
                        }
         | TOK_VAL_TEXT {
                            ParseAST ast;
                            ast.pos    = $1.pos;
                            ast.result = ast_text($1.result, ast.pos);
                            $$ = ast;
/*
                            printf("text found : %d:%d -> %d:%d >> %s\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend,
                                   $1.result);
*/
                            free($1.result);
                        }
         ; 

variable : TOK_IDENTIFIER {
                            ParseAST ast;
                            ast.pos    = $1.pos;
                            ast.result = ast_variable($1.result, ast.pos);
                            $$ = ast;
/*
                            printf("Variable found : %d:%d -> %d:%d >> %s\n",
                                   ast.pos.lstart,
                                   ast.pos.cstart,
                                   ast.pos.lend,
                                   ast.pos.cend,
                                   $1.result);
*/
                            free($1.result);
                        }
         ;

%%
