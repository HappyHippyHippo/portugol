%{
#include <stdio.h>
#include <stdint.h>

#include <internal/portugol/ast.h>

extern int yylex();
extern int yyget_lineno();
void yyerror(const char *s) { printf("ERROR: %s at line %d\n", s, yyget_lineno()); }

#define INIT_AST(ls, cs, le, ce)       \
                ParseAST ast;          \
                ast.pos.lstart = (ls); \
                ast.pos.cstart = (cs); \
                ast.pos.lend   = (le); \
                ast.pos.cend   = (ce);

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
%token <token>   TOK_COMA TOK_BOOLEAN TOK_INTEGER TOK_FLOAT TOK_TEXT
%token <token>   TOK_EOL

%token <token>   TOK_IF TOK_THEN TOK_ELSE
%token <token>   TOK_FOR TOK_FROM TOK_TO TOK_STEP
%token <token>   TOK_SWITCH TOK_CASE TOK_DEFAULT
%token <token>   TOK_WHILE TOK_DO
%token <token>   TOK_END

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
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_decl_boolean($1.result, ast_boolean(0, ast.pos), ast.pos);
                            $$ = ast;

                            free($1.result);
                        }
     | TOK_IDENTIFIER TOK_COMA TOK_BOOLEAN TOK_OP_ASSIGN expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $5.pos.lend, $5.pos.cend);
                            ast.result = ast_decl_boolean($1.result, $5.result, ast.pos);
                            $$ = ast;

                            free($1.result);
                        }
     | TOK_IDENTIFIER TOK_COMA TOK_INTEGER {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_decl_int32($1.result, ast_int32(0, ast.pos), ast.pos);
                            $$ = ast;

                            free($1.result);
                        }
     | TOK_IDENTIFIER TOK_COMA TOK_INTEGER TOK_OP_ASSIGN expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $5.pos.lend, $5.pos.cend);
                            ast.result = ast_decl_int32($1.result, $5.result, ast.pos);
                            $$ = ast;

                            free($1.result);
                        }
     | TOK_IDENTIFIER TOK_COMA TOK_FLOAT {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_decl_float32($1.result, ast_float32(0, ast.pos), ast.pos);
                            $$ = ast;

                            free($1.result);
                        }
     | TOK_IDENTIFIER TOK_COMA TOK_FLOAT TOK_OP_ASSIGN expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $5.pos.lend, $5.pos.cend);
                            ast.result = ast_decl_float32($1.result, $5.result, ast.pos);
                            $$ = ast;

                            free($1.result);
                        }
     | TOK_IDENTIFIER TOK_COMA TOK_TEXT {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_decl_text($1.result, ast_text("", ast.pos), ast.pos);
                            $$ = ast;

                            free($1.result);
                        }
     | TOK_IDENTIFIER TOK_COMA TOK_TEXT TOK_OP_ASSIGN expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $5.pos.lend, $5.pos.cend);
                            ast.result = ast_decl_text($1.result, $5.result, ast.pos);
                            $$ = ast;

                            free($1.result);
                        }
     ;

assign : variable TOK_OP_ASSIGN expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_op_binary($1.result, $3.result, AST_OP_ASSIGN, ast.pos);
                            $$ = ast;
                        }
       ;

expr : expr TOK_OP_ADD expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_op_binary($1.result, $3.result, AST_OP_ADD, ast.pos);
                            $$ = ast;
                        }
     | expr TOK_OP_SUBTRACT expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_op_binary($1.result, $3.result, AST_OP_SUBTRACT, ast.pos);
                            $$ = ast;
                        }
     | expr TOK_OP_MULTIPLY expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_op_binary($1.result, $3.result, AST_OP_MULTIPLY, ast.pos);
                            $$ = ast;
                        }
     | expr TOK_OP_DIVIDE expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_op_binary($1.result, $3.result, AST_OP_DIVIDE, ast.pos);
                            $$ = ast;
                        }
     | expr TOK_OP_REMAINDER expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_op_binary($1.result, $3.result, AST_OP_REMAINDER, ast.pos);
                            $$ = ast;
                        }
     | expr TOK_OP_EQUAL expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_op_binary($1.result, $3.result, AST_OP_EQUAL, ast.pos);
                            $$ = ast;
                        }
     | expr TOK_OP_INEQUAL expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_op_binary($1.result, $3.result, AST_OP_INEQUAL, ast.pos);
                            $$ = ast;
                        }
     | expr TOK_OP_GREATER expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_op_binary($1.result, $3.result, AST_OP_GREATER, ast.pos);
                            $$ = ast;
                        }
     | expr TOK_OP_GREATER_OR_EQUAL expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_op_binary($1.result, $3.result, AST_OP_GREATER_OR_EQUAL, ast.pos);
                            $$ = ast;
                        }
     | expr TOK_OP_LESSER expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_op_binary($1.result, $3.result, AST_OP_LESSER, ast.pos);
                            $$ = ast;
                        }
     | expr TOK_OP_LESSER_OR_EQUAL expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_op_binary($1.result, $3.result, AST_OP_LESSER_OR_EQUAL, ast.pos);
                            $$ = ast;
                        }
     | expr TOK_OP_AND expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_op_binary($1.result, $3.result, AST_OP_AND, ast.pos);
                            $$ = ast;
                        }
     | expr TOK_OP_OR expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_op_binary($1.result, $3.result, AST_OP_OR, ast.pos);
                            $$ = ast;
                        }
     | expr TOK_OP_XOR expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = ast_op_binary($1.result, $3.result, AST_OP_XOR, ast.pos);
                            $$ = ast;
                        }
     | TOK_OP_NOT expr {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $2.pos.lend, $2.pos.cend);
                            ast.result = ast_op_unary($2.result, AST_OP_NOT, ast.pos);
                            $$ = ast;
                        }
     | TOK_OPEN_PAREN expr TOK_CLOSE_PAREN {
                            INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                            ast.result = $2.result;
                            ast.result->pos = ast.pos;
                            $$ = ast;
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
                        }
         | TOK_VAL_FPNUMBER {
                            ParseAST ast;
                            ast.pos    = $1.pos;
                            ast.result = ast_float32($1.result, ast.pos);
                            $$ = ast;
                        }
         | TOK_VAL_TEXT {
                            ParseAST ast;
                            ast.pos    = $1.pos;
                            ast.result = ast_text($1.result, ast.pos);
                            $$ = ast;

                            free($1.result);
                        }
         ; 

variable : TOK_IDENTIFIER {
                            ParseAST ast;
                            ast.pos    = $1.pos;
                            ast.result = ast_variable($1.result, ast.pos);
                            $$ = ast;

                            free($1.result);
                        }
         ;

%%
