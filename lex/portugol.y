%{
#include <stdio.h>
#include <stdint.h>

#include <internal/portugol/ast.h>

extern int yylex();
extern int yyget_lineno();
void yyerror(const char *s) { printf("ERROR: %s at line %d\n", s, yyget_lineno()); ast_error = 1; }

#define INIT_AST(ls, cs, le, ce)       \
                ParseAST ast;          \
                ast.pos.lstart = (ls); \
                ast.pos.cstart = (cs); \
                ast.pos.lend   = (le); \
                ast.pos.cend   = (ce);

%}

%union { ParseAST     ast;
         ParseBool    bool;
         ParseInt32   int32;
         ParseFloat32 float32;
         ParseText    text;
         ParseToken   token;
         ParseFParam  fparam;
         ParseFParams fparams;
         ParseFArgs   farguments;
         AST_Node*    global;
}

%token <bool>    TOK_VAL_BOOLEAN
%token <int32>   TOK_VAL_NUMBER
%token <float32> TOK_VAL_FPNUMBER
%token <text>    TOK_VAL_TEXT TOK_IDENTIFIER
%token <token>   TOK_COLON TOK_BOOLEAN TOK_INTEGER TOK_FLOAT TOK_TEXT
%token <token>   TOK_EOL
%token <token>   TOK_FUNCTION TOK_RETURN TOK_PROGRAM TOK_COMMA

%token <token>   TOK_END TOK_OF
%token <token>   TOK_IF TOK_THEN TOK_ELSE
%token <token>   TOK_FOR TOK_TO TOK_STEP
%token <token>   TOK_SWITCH TOK_CASE TOK_DEFAULT
%token <token>   TOK_WHILE

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

%type <token> vartype
%type <fparam> fparam
%type <fparams> fparams
%type <ast> fargument
%type <farguments> farguments
%type <ast> globals global function program locals local decl assign if while for return expr fcall variable constant

%start globals

%locations

%%

globals : globals global {
                if ($2.result != NULL)
                    ast_scope_push(ast_parse_scope_get(), $2.result);
                $$ = $2;
            }
        | global {
                if ($1.result != NULL)
                    ast_scope_push(ast_parse_scope_get(), $1.result);
                $$ = $1;
            }
        ;

global : decl TOK_EOL {
                $$ = $1;
            }
       | program TOK_EOL {
                $$ = $1;
            }
       | function TOK_EOL {
                $$ = $1;
            }
       | TOK_EOL {
                ParseAST ast;
                ast.pos    = $1.pos;
                ast.result = NULL;
                $$ = ast;
            }
       ;

program : TOK_PROGRAM TOK_EOL locals TOK_END TOK_OF TOK_PROGRAM {
                INIT_AST($1.pos.lstart, $1.pos.cstart, $6.pos.lend, $6.pos.cend);
                ast.result = ast_program(ast_parse_scope_pop(), ast.pos);
                $$ = ast;
             }
         ;

function : TOK_IDENTIFIER TOK_COLON TOK_FUNCTION TOK_OPEN_PAREN fparams TOK_CLOSE_PAREN TOK_RETURN vartype TOK_EOL locals TOK_END TOK_OF TOK_FUNCTION {
                INIT_AST($1.pos.lstart, $1.pos.cstart, $12.pos.lend, $12.pos.cend);

                AST_Node* scope = ast_parse_scope_pop();
                switch ($8.result)
                {
                    case TOK_BOOLEAN:
                        ast.result = ast_function($1.result, $5.result, $5.count, VBOOLEAN, scope, ast.pos);        break;
                    case TOK_INTEGER:
                        ast.result = ast_function($1.result, $5.result, $5.count, VINT32, scope, ast.pos);          break;
                    case TOK_FLOAT:
                        ast.result = ast_function($1.result, $5.result, $5.count, VFLOAT32, scope, ast.pos);        break;
                    case TOK_TEXT:
                        ast.result = ast_function($1.result, $5.result, $5.count, VTEXT, scope, ast.pos);           break;
                    case TOK_FUNCTION:
                        ast.result = ast_function($1.result, $5.result, $5.count, VFUNCTION, scope, ast.pos);       break;
                    default:
                        break;
                }
                $$ = ast;

                free($1.result);
             }
         | TOK_IDENTIFIER TOK_COLON TOK_FUNCTION TOK_OPEN_PAREN TOK_CLOSE_PAREN TOK_RETURN vartype TOK_EOL locals TOK_END TOK_OF TOK_FUNCTION {
                INIT_AST($1.pos.lstart, $1.pos.cstart, $11.pos.lend, $11.pos.cend);

                AST_Node* scope = ast_parse_scope_pop();
                switch ($7.result)
                {
                    case TOK_BOOLEAN:
                        ast.result = ast_function($1.result, NULL, 0, VBOOLEAN, scope, ast.pos);                    break;
                    case TOK_INTEGER:
                        ast.result = ast_function($1.result, NULL, 0, VINT32, scope, ast.pos);                      break;
                    case TOK_FLOAT:
                        ast.result = ast_function($1.result, NULL, 0, VFLOAT32, scope, ast.pos);                    break;
                    case TOK_TEXT:
                        ast.result = ast_function($1.result, NULL, 0, VTEXT, scope, ast.pos);                       break;
                    case TOK_FUNCTION:
                        ast.result = ast_function($1.result, NULL, 0, VFUNCTION, scope, ast.pos);                   break;
                    default:                                                                                        break;
                }
                $$ = ast;

                free($1.result);
             }
         ;

fparams : fparams TOK_COMMA fparam {
                ParseFParams params;
                params.pos.lstart = $1.pos.lstart;
                params.pos.cstart = $1.pos.cstart;
                params.pos.lend   = $3.pos.lend;
                params.pos.cend   = $3.pos.cend;
                params.result     = ast_function_param_push($3.result, $1.result, $1.count);
                params.count      = $1.count + 1;
                $$ = params;
            }
        | fparam {
                ParseFParams params;
                params.pos.lstart = $1.pos.lstart;
                params.pos.cstart = $1.pos.cstart;
                params.pos.lend   = $1.pos.lend;
                params.pos.cend   = $1.pos.cend;
                params.result     = ast_function_param_push($1.result, NULL, 0);
                params.count      = 1;
                $$ = params;
            }
        ;

fparam : vartype TOK_IDENTIFIER {
                ParseFParam param;
                param.pos.lstart = $1.pos.lstart;
                param.pos.cstart = $1.pos.cstart;
                param.pos.lend   = $2.pos.lend;
                param.pos.cend   = $2.pos.cend;
                switch ($1.result)
                {
                    case TOK_BOOLEAN:
                        param.result = ast_function_param(VBOOLEAN, $2.result);                                     break;
                    case TOK_INTEGER:
                        param.result = ast_function_param(VINT32, $2.result);                                       break;
                    case TOK_FLOAT:
                        param.result = ast_function_param(VFLOAT32, $2.result);                                     break;
                    case TOK_TEXT:
                        param.result = ast_function_param(VTEXT, $2.result);                                        break;
                    case TOK_FUNCTION:
                        param.result = ast_function_param(VFUNCTION, $2.result);                                    break;
                    default:                                                                                        break;
                }
                $$ = param;

                free($2.result);
            }
       ;

locals : locals local {
                if ($2.result != NULL)
                    ast_scope_push(ast_parse_scope_get(), $2.result);
                $$ = $2;
            }
       | local {
                ast_parse_scope_push(ast_scope($1.pos));

                if ($1.result != NULL)
                    ast_scope_push(ast_parse_scope_get(), $1.result);
                $$ = $1;
            }
       ;

local : decl TOK_EOL {
                $$ = $1;
            }
      | assign TOK_EOL {
                $$ = $1;
            }
      | if TOK_EOL {
                $$ = $1;
            }
      | while TOK_EOL {
                $$ = $1;
            }
      | for TOK_EOL {
                $$ = $1;
            }
      | return TOK_EOL {
                $$ = $1;
            }
      | fcall TOK_EOL {
                $$ = $1;
            }
      | TOK_EOL {
                ParseAST ast;
                ast.pos    = $1.pos;
                ast.result = NULL;
                $$ = ast;
            }
      ;

if : TOK_IF expr TOK_THEN TOK_EOL locals TOK_END TOK_OF TOK_IF {
                INIT_AST($1.pos.lstart, $1.pos.cstart, $8.pos.lend, $8.pos.cend);

                AST_Node* chk_true = ast_parse_scope_pop();
                ast.result = ast_if($2.result, chk_true, NULL, ast.pos);
                $$ = ast;
            }
   | TOK_IF expr TOK_THEN TOK_EOL locals TOK_ELSE TOK_EOL locals TOK_END TOK_OF TOK_IF {
                INIT_AST($1.pos.lstart, $1.pos.cstart, $11.pos.lend, $11.pos.cend);

                AST_Node* chk_false = ast_parse_scope_pop();
                AST_Node* chk_true = ast_parse_scope_pop();
                ast.result = ast_if($2.result, chk_true, chk_false, ast.pos);
                $$ = ast;
            }
   ;

while : TOK_WHILE expr TOK_THEN TOK_EOL locals TOK_END TOK_OF TOK_WHILE {
                INIT_AST($1.pos.lstart, $1.pos.cstart, $8.pos.lend, $8.pos.cend);

                AST_Node* scope = ast_parse_scope_pop();
                ast.result = ast_while($2.result, scope, ast.pos);
                $$ = ast;
            }
      ;

for : TOK_FOR TOK_IDENTIFIER TOK_OF expr TOK_TO expr TOK_THEN TOK_EOL locals TOK_END TOK_OF TOK_FOR {
                INIT_AST($1.pos.lstart, $1.pos.cstart, $12.pos.lend, $12.pos.cend);

                AST_Node* scope = ast_parse_scope_pop();
                ast.result = ast_for($2.result, $4.result, $6.result, ast_int32(1, ast.pos), scope, ast.pos);
                $$ = ast;

                free($2.result);
            }
    | TOK_FOR TOK_IDENTIFIER TOK_OF expr TOK_TO expr TOK_STEP expr TOK_THEN TOK_EOL locals TOK_END TOK_OF TOK_FOR {
                INIT_AST($1.pos.lstart, $1.pos.cstart, $14.pos.lend, $14.pos.cend);

                AST_Node* scope = ast_parse_scope_pop();
                ast.result = ast_for($2.result, $4.result, $6.result, $8.result, scope, ast.pos);
                $$ = ast;

                free($2.result);
            }
    ;

decl : TOK_IDENTIFIER TOK_COLON vartype {
                INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                switch ($3.result)
                {
                    case TOK_BOOLEAN:
                        ast.result = ast_decl_boolean($1.result, ast_boolean(0, ast.pos), ast.pos);
                        break;
                    case TOK_INTEGER:
                        ast.result = ast_decl_int32($1.result, ast_int32(0, ast.pos), ast.pos);
                        break;
                    case TOK_FLOAT:
                        ast.result = ast_decl_float32($1.result, ast_float32(0, ast.pos), ast.pos);
                        break;
                    case TOK_TEXT:
                        ast.result = ast_decl_text($1.result, ast_text("", ast.pos), ast.pos);
                        break;
                    default:
                        break;
                }
                $$ = ast;

                free($1.result);
            }
     | TOK_IDENTIFIER TOK_COLON vartype TOK_OP_ASSIGN expr {
                INIT_AST($1.pos.lstart, $1.pos.cstart, $5.pos.lend, $5.pos.cend);
                switch ($3.result)
                {
                    case TOK_BOOLEAN:
                        ast.result = ast_decl_boolean($1.result, $5.result, ast.pos);
                        break;
                    case TOK_INTEGER:
                        ast.result = ast_decl_int32($1.result, $5.result, ast.pos);
                        break;
                    case TOK_FLOAT:
                        ast.result = ast_decl_float32($1.result, $5.result, ast.pos);
                        break;
                    case TOK_TEXT:
                        ast.result = ast_decl_text($1.result, $5.result, ast.pos);
                        break;
                    default:
                        break;
                }
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

return : TOK_RETURN expr {
                INIT_AST($1.pos.lstart, $1.pos.cstart, $2.pos.lend, $2.pos.cend);
                ast.result = ast_return($2.result, ast.pos);
                $$ = ast;
            }
       ;

expr : TOK_OP_ADD expr {
                INIT_AST($1.pos.lstart, $1.pos.cstart, $2.pos.lend, $2.pos.cend);
                ast.result = ast_op_unary($2.result, AST_OP_POSITIVE, ast.pos);
                $$ = ast;
            }
     | TOK_OP_SUBTRACT expr {
                INIT_AST($1.pos.lstart, $1.pos.cstart, $2.pos.lend, $2.pos.cend);
                ast.result = ast_op_unary($2.result, AST_OP_NEGATIVE, ast.pos);
                $$ = ast;
            }
     | expr TOK_OP_ADD expr {
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
     | fcall {
                $$ = $1;
            }
     | constant {
                $$ = $1;
            }
     ;

fcall : TOK_IDENTIFIER TOK_OPEN_PAREN farguments TOK_CLOSE_PAREN {
                INIT_AST($1.pos.lstart, $1.pos.cstart, $4.pos.lend, $4.pos.cend);
                ast.result = ast_function_call($1.result, $3.result, $3.count, ast.pos);
                $$ = ast;

                free($1.result);
            }
      | TOK_IDENTIFIER TOK_OPEN_PAREN TOK_CLOSE_PAREN {
                INIT_AST($1.pos.lstart, $1.pos.cstart, $3.pos.lend, $3.pos.cend);
                ast.result = ast_function_call($1.result, NULL, 0, ast.pos);
                $$ = ast;

                free($1.result);
            }
      ;

farguments : farguments TOK_COMMA fargument {
                ParseFArgs args;
                args.pos.lstart = $1.pos.lstart;
                args.pos.cstart = $1.pos.cstart;
                args.pos.lend   = $3.pos.lend;
                args.pos.cend   = $3.pos.cend;
                args.result     = ast_function_call_arg_push($3.result, $1.result, $1.count);
                args.count      = $1.count + 1;
                $$ = args;
            }
           | fargument {
                ParseFArgs args;
                args.pos.lstart = $1.pos.lstart;
                args.pos.cstart = $1.pos.cstart;
                args.pos.lend   = $1.pos.lend;
                args.pos.cend   = $1.pos.cend;
                args.result     = ast_function_call_arg_push($1.result, NULL, 0);
                args.count      = 1;
                $$ = args;
            }
           ;

fargument : expr {
                ParseAST ast;
                ast.pos    = $1.pos;
                ast.result = $1.result;
                $$ = ast;
            }
          ;

constant : TOK_VAL_BOOLEAN {
                ParseAST ast;
                ast.pos    = $1.pos;
                ast.result = ast_boolean($1.result, ast.pos);
                $$ = ast;
            }
         | TOK_VAL_NUMBER {
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

vartype : TOK_BOOLEAN {
                $$ = $1;
            }
        | TOK_INTEGER {
                $$ = $1;
            }
        | TOK_FLOAT {
                $$ = $1;
            }
        | TOK_TEXT {
                $$ = $1;
            }
        ;

%%
