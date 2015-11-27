%{
#include <stdio.h>
#include <stdint.h>

#include <internal/portugol/lex/lex.h>

extern int yylex();
extern int yyget_lineno();
void yyerror(const char *msg) {
    printf("ERROR: %s at line %d\n", msg, yyget_lineno());
    ast_error = 1;
}

%}

%union {
    AST_Node*                 ast;
    AST_ParamList*            fparams;
    LexParam                  fparam;
    AST_ArgList*              fargs;
    LexToken                  token;
    LexVarType                vtype;
}

%token <token> TOK_EOL

%token <token> TOK_VAL_TRUE
%token <token> TOK_VAL_FALSE
%token <token> TOK_VAL_NUMBER
%token <token> TOK_VAL_FPNUMBER
%token <token> TOK_VAL_TEXT

%token <token> TOK_OP_NOT
%token <token> TOK_OP_ADD
%token <token> TOK_OP_SUBTRACT 
%token <token> TOK_OP_MULTIPLY
%token <token> TOK_OP_DIVIDE
%token <token> TOK_OP_REMAINDER

%token <token> TOK_OP_EQUAL
%token <token> TOK_OP_INEQUAL
%token <token> TOK_OP_GREATER
%token <token> TOK_OP_GREATER_OR_EQUAL
%token <token> TOK_OP_LESSER
%token <token> TOK_OP_LESSER_OR_EQUAL

%token <token> TOK_OP_AND
%token <token> TOK_OP_OR
%token <token> TOK_OP_XOR

%token <token> TOK_OP_ASSIGN

%token <token> TOK_IDENTIFIER
%token <token> TOK_COMMA
%token <token> TOK_COLON

%token <token> TOK_BOOLEAN
%token <token> TOK_INT32
%token <token> TOK_FLOAT32
%token <token> TOK_TEXT

%token <token> TOK_END
%token <token> TOK_OF

%token <token> TOK_IF
%token <token> TOK_THEN
%token <token> TOK_ELSE

%token <token> TOK_FOR
%token <token> TOK_TO
%token <token> TOK_STEP

%token <token> TOK_WHILE

%token <token> TOK_RETURN
%token <token> TOK_FUNCTION
%token <token> TOK_PROGRAM
%token <token> TOK_IMPORT

%token <token> TOK_OPEN_PAREN
%token <token> TOK_CLOSE_PAREN

%left TOK_OP_ASSIGN
%left TOK_OP_OR TOK_OP_XOR
%left TOK_OP_AND
%left TOK_OP_GREATER TOK_OP_GREATER_OR_EQUAL TOK_OP_LESSER TOK_OP_LESSER_OR_EQUAL
%left TOK_OP_EQUAL TOK_OP_INEQUAL
%left TOK_OP_ADD TOK_OP_SUBTRACT
%left TOK_OP_MULTIPLY TOK_OP_DIVIDE TOK_OP_REMAINDER
%left TOK_OP_NOT
%left TOK_OPEN_PAREN TOK_CLOSE_PAREN

%type <vtype> vartype
%type <fparams> fparams
%type <fparam> fparam
%type <fargs> fargs
%type <ast> globals global import program function locals local if while for decl assign return expr cast fcall farg constant variable

%start globals

%locations

%%

globals : globals global { if ($2 != NULL)
                           {
                               if (!ast_lex)
                                   ast_lex = ast_file(ast_filepath);
                               ast_push_instr(ast_lex, $2);
                           } }
        | global         { if ($1 != NULL)
                           {
                               if (!ast_lex)
                                   ast_lex = ast_file(ast_filepath);
                               ast_push_instr(ast_lex, $1);
                           } }
        ;

global : import   { $$ = $1; }
       | decl     { $$ = $1; }
       | program  { $$ = $1; }
       | function { $$ = $1; }
       | TOK_EOL  { $$ = NULL; }
       ;

locals : locals local { if ($2 != NULL)
                            ast_push_instr($1, $2);
                        $$ = $1; }
      | local         { AST_Node* scope = ast_scope();
                        if ($1 != NULL)
                            ast_push_instr(scope, $1);
                        $$ = scope; }
      ;

local : if TOK_EOL     { $$ = $1; }
      | while TOK_EOL  { $$ = $1; }
      | for TOK_EOL    { $$ = $1; }
      | assign TOK_EOL { $$ = $1; }
      | return TOK_EOL { $$ = $1; }
      | decl TOK_EOL   { $$ = $1; }
      | expr TOK_EOL   { $$ = $1; }
      | TOK_EOL        { $$ = NULL; }
      ;

import : TOK_IMPORT TOK_VAL_TEXT { AST_Pos pos;
                                   pos.line.start   = $1.pos.line.start;
                                   pos.column.start = $1.pos.column.start;
                                   pos.line.stop    = $2.pos.line.stop;
                                   pos.column.stop  = $2.pos.column.stop;
                                   $$ = ast_import(pos, $2.text);
                                   free($2.text); }
       ;

program : TOK_PROGRAM TOK_EOL
              locals
          TOK_END TOK_OF TOK_PROGRAM TOK_EOL { AST_Pos pos;
                                               pos.line.start   = $1.pos.line.start;
                                               pos.column.start = $1.pos.column.start;
                                               pos.line.stop    = $6.pos.line.stop;
                                               pos.column.stop  = $6.pos.column.stop;
                                               $$ = ast_function(pos, "programa", ast_param_list(), VINT32, $3); }
         ;

function : TOK_IDENTIFIER TOK_COLON TOK_FUNCTION TOK_OPEN_PAREN fparams TOK_CLOSE_PAREN TOK_RETURN vartype TOK_EOL
                locals
           TOK_END TOK_OF TOK_FUNCTION { AST_Pos pos;
                                         pos.line.start   = $1.pos.line.start;
                                         pos.column.start = $1.pos.column.start;
                                         pos.line.stop    = $13.pos.line.stop;
                                         pos.column.stop  = $13.pos.column.stop;
                                         $$ = ast_function(pos, $1.text, $5, $8.type, $10);
                                         free($1.text); }
         | TOK_IDENTIFIER TOK_COLON TOK_FUNCTION TOK_OPEN_PAREN TOK_CLOSE_PAREN TOK_RETURN vartype TOK_EOL
               locals
           TOK_END TOK_OF TOK_FUNCTION { AST_Pos pos;
                                         pos.line.start   = $1.pos.line.start;
                                         pos.column.start = $1.pos.column.start;
                                         pos.line.stop    = $12.pos.line.stop;
                                         pos.column.stop  = $12.pos.column.stop;
                                         $$ = ast_function(pos, $1.text, ast_param_list(), $7.type, $9);
                                         free($1.text); }
         ;

fparams : fparams TOK_COMMA fparam { ast_param_list_add($1, $3.pos, $3.type, $3.name);
                                     free($3.name);
                                     $$ = $1; }
        | fparam                   { AST_ParamList* list = ast_param_list();
                                     ast_param_list_add(list, $1.pos, $1.type, $1.name);
                                     free($1.name);
                                     $$ = list; }
        ;

fparam : vartype TOK_IDENTIFIER { AST_Pos pos;
                                  pos.line.start   = $1.pos.line.start;
                                  pos.column.start = $1.pos.column.start;
                                  pos.line.stop    = $2.pos.line.stop;
                                  pos.column.stop  = $2.pos.column.stop;

                                  $$.pos = pos;
                                  $$.type = $1.type;
                                  $$.name = $2.text; }
       ;

if : TOK_IF expr TOK_THEN TOK_EOL
         locals
     TOK_END TOK_OF TOK_IF { AST_Pos pos;
                             pos.line.start   = $1.pos.line.start;
                             pos.column.start = $1.pos.column.start;
                             pos.line.stop    = $8.pos.line.stop;
                             pos.column.stop  = $8.pos.column.stop;
                             $$ = ast_if(pos, $2, $5, NULL); }
   | TOK_IF expr TOK_THEN TOK_EOL
         locals
     TOK_ELSE TOK_EOL
         locals
     TOK_END TOK_OF TOK_IF { AST_Pos pos;
                             pos.line.start   = $1.pos.line.start;
                             pos.column.start = $1.pos.column.start;
                             pos.line.stop    = $11.pos.line.stop;
                             pos.column.stop  = $11.pos.column.stop;
                             $$ = ast_if(pos, $2, $5, $8); }
   ;

while : TOK_WHILE expr TOK_THEN TOK_EOL
            locals
        TOK_END TOK_OF TOK_WHILE { AST_Pos pos;
                                   pos.line.start   = $1.pos.line.start;
                                   pos.column.start = $1.pos.column.start;
                                   pos.line.stop    = $8.pos.line.stop;
                                   pos.column.stop  = $8.pos.column.stop;
                                   $$ = ast_while(pos, $2, $5); }
      ;

for : TOK_FOR TOK_IDENTIFIER TOK_OF expr TOK_TO expr TOK_THEN TOK_EOL
          locals
      TOK_END TOK_OF TOK_FOR { AST_Pos pos;
                               pos.line.start   = $1.pos.line.start;
                               pos.column.start = $1.pos.column.start;
                               pos.line.stop    = $12.pos.line.stop;
                               pos.column.stop  = $12.pos.column.stop;
                               $$ = ast_for(pos, $2.text, $4, $6, NULL, $9);
                               free($2.text); }
    | TOK_FOR TOK_IDENTIFIER TOK_OF expr TOK_TO expr TOK_STEP expr TOK_THEN TOK_EOL
          locals
      TOK_END TOK_OF TOK_FOR { AST_Pos pos;
                               pos.line.start   = $1.pos.line.start;
                               pos.column.start = $1.pos.column.start;
                               pos.line.stop    = $14.pos.line.stop;
                               pos.column.stop  = $14.pos.column.stop;
                               $$ = ast_for(pos, $2.text, $4, $6, $8, $11);
                               free($2.text); }
    ;

decl : TOK_IDENTIFIER TOK_COLON vartype                    { AST_Pos pos;
                                                             pos.line.start   = $1.pos.line.start;
                                                             pos.column.start = $1.pos.column.start;
                                                             pos.line.stop    = $3.pos.line.stop;
                                                             pos.column.stop  = $3.pos.column.stop;

                                                             AST_Pos aux = {{0, 0}, {0, 0}};

                                                             switch ($3.type)
                                                             {
                                                                 case VBOOLEAN: $$ = ast_decl_boolean(pos, $1.text, ast_boolean(aux, 0));    break;
                                                                 case VINT32:   $$ = ast_decl_int32(pos, $1.text, ast_int32(aux, 0));        break;
                                                                 case VFLOAT32: $$ = ast_decl_float32(pos, $1.text, ast_float32(aux, 0.0f)); break;
                                                                 case VTEXT:    $$ = ast_decl_text(pos, $1.text, ast_text(aux, ""));         break;
                                                                 default:                                                                    break;
                                                             }

                                                             free($1.text); }
     | TOK_IDENTIFIER TOK_COLON vartype TOK_OP_ASSIGN expr { AST_Pos pos;
                                                             pos.line.start   = $1.pos.line.start;
                                                             pos.column.start = $1.pos.column.start;
                                                             pos.line.stop    = ast_get_position($5).line.stop;
                                                             pos.column.stop  = ast_get_position($5).column.stop;

                                                             switch ($3.type)
                                                             {
                                                                 case VBOOLEAN: $$ = ast_decl_boolean(pos, $1.text, $5); break;
                                                                 case VINT32:   $$ = ast_decl_int32(pos, $1.text, $5);   break;
                                                                 case VFLOAT32: $$ = ast_decl_float32(pos, $1.text, $5); break;
                                                                 case VTEXT:    $$ = ast_decl_text(pos, $1.text, $5);    break;
                                                                 default:                                                break;
                                                             }
                                                             free($1.text); }
     ;

assign : variable TOK_OP_ASSIGN expr { AST_Pos pos;
                                       pos.line.start   = ast_get_position($1).line.start;
                                       pos.column.start = ast_get_position($1).column.start;
                                       pos.line.stop    = ast_get_position($3).line.stop;
                                       pos.column.stop  = ast_get_position($3).column.stop;
                                       $$ = ast_op_assign(pos, $1, $3); }
       ;

return : TOK_RETURN expr { AST_Pos pos;
                           pos.line.start   = $1.pos.line.start;
                           pos.column.start = $1.pos.column.start;
                           pos.line.stop    = ast_get_position($2).line.stop;
                           pos.column.stop  = ast_get_position($2).column.stop;
                           $$ = ast_return(pos, $2); }
       ;

expr : TOK_OPEN_PAREN expr TOK_CLOSE_PAREN { $$ = $2; }
     | expr TOK_OP_ADD expr                { AST_Pos pos;
                                             pos.line.start   = ast_get_position($1).line.start;
                                             pos.column.start = ast_get_position($1).column.start;
                                             pos.line.stop    = ast_get_position($3).line.stop;
                                             pos.column.stop  = ast_get_position($3).column.stop;
                                             $$ = ast_op_add(pos, $1, $3); }
     | expr TOK_OP_SUBTRACT expr           { AST_Pos pos;
                                             pos.line.start   = ast_get_position($1).line.start;
                                             pos.column.start = ast_get_position($1).column.start;
                                             pos.line.stop    = ast_get_position($3).line.stop;
                                             pos.column.stop  = ast_get_position($3).column.stop;
                                             $$ = ast_op_subtract(pos, $1, $3); }
     | expr TOK_OP_MULTIPLY expr           { AST_Pos pos;
                                             pos.line.start   = ast_get_position($1).line.start;
                                             pos.column.start = ast_get_position($1).column.start;
                                             pos.line.stop    = ast_get_position($3).line.stop;
                                             pos.column.stop  = ast_get_position($3).column.stop;
                                             $$ = ast_op_multiply(pos, $1, $3); }
     | expr TOK_OP_DIVIDE expr             { AST_Pos pos;
                                             pos.line.start   = ast_get_position($1).line.start;
                                             pos.column.start = ast_get_position($1).column.start;
                                             pos.line.stop    = ast_get_position($3).line.stop;
                                             pos.column.stop  = ast_get_position($3).column.stop;
                                             $$ = ast_op_divide(pos, $1, $3); }
     | expr TOK_OP_REMAINDER expr          { AST_Pos pos;
                                             pos.line.start   = ast_get_position($1).line.start;
                                             pos.column.start = ast_get_position($1).column.start;
                                             pos.line.stop    = ast_get_position($3).line.stop;
                                             pos.column.stop  = ast_get_position($3).column.stop;
                                             $$ = ast_op_remainder(pos, $1, $3); }
     | expr TOK_OP_EQUAL expr              { AST_Pos pos;
                                             pos.line.start   = ast_get_position($1).line.start;
                                             pos.column.start = ast_get_position($1).column.start;
                                             pos.line.stop    = ast_get_position($3).line.stop;
                                             pos.column.stop  = ast_get_position($3).column.stop;
                                             $$ = ast_op_equal(pos, $1, $3); }
     | expr TOK_OP_INEQUAL expr            { AST_Pos pos;
                                             pos.line.start   = ast_get_position($1).line.start;
                                             pos.column.start = ast_get_position($1).column.start;
                                             pos.line.stop    = ast_get_position($3).line.stop;
                                             pos.column.stop  = ast_get_position($3).column.stop;
                                             $$ = ast_op_inequal(pos, $1, $3); }
     | expr TOK_OP_GREATER expr            { AST_Pos pos;
                                             pos.line.start   = ast_get_position($1).line.start;
                                             pos.column.start = ast_get_position($1).column.start;
                                             pos.line.stop    = ast_get_position($3).line.stop;
                                             pos.column.stop  = ast_get_position($3).column.stop;
                                             $$ = ast_op_greater(pos, $1, $3); }
     | expr TOK_OP_GREATER_OR_EQUAL expr   { AST_Pos pos;
                                             pos.line.start   = ast_get_position($1).line.start;
                                             pos.column.start = ast_get_position($1).column.start;
                                             pos.line.stop    = ast_get_position($3).line.stop;
                                             pos.column.stop  = ast_get_position($3).column.stop;
                                             $$ = ast_op_greater_or_equal(pos, $1, $3); }
     | expr TOK_OP_LESSER expr             { AST_Pos pos;
                                             pos.line.start   = ast_get_position($1).line.start;
                                             pos.column.start = ast_get_position($1).column.start;
                                             pos.line.stop    = ast_get_position($3).line.stop;
                                             pos.column.stop  = ast_get_position($3).column.stop;
                                             $$ = ast_op_lesser(pos, $1, $3); }
     | expr TOK_OP_LESSER_OR_EQUAL expr    { AST_Pos pos;
                                             pos.line.start   = ast_get_position($1).line.start;
                                             pos.column.start = ast_get_position($1).column.start;
                                             pos.line.stop    = ast_get_position($3).line.stop;
                                             pos.column.stop  = ast_get_position($3).column.stop;
                                             $$ = ast_op_lesser_or_equal(pos, $1, $3); }
     | expr TOK_OP_AND expr                { AST_Pos pos;
                                             pos.line.start   = ast_get_position($1).line.start;
                                             pos.column.start = ast_get_position($1).column.start;
                                             pos.line.stop    = ast_get_position($3).line.stop;
                                             pos.column.stop  = ast_get_position($3).column.stop;
                                             $$ = ast_op_and(pos, $1, $3); }
     | expr TOK_OP_OR expr                 { AST_Pos pos;
                                             pos.line.start   = ast_get_position($1).line.start;
                                             pos.column.start = ast_get_position($1).column.start;
                                             pos.line.stop    = ast_get_position($3).line.stop;
                                             pos.column.stop  = ast_get_position($3).column.stop;
                                             $$ = ast_op_or(pos, $1, $3); }
     | expr TOK_OP_XOR expr                { AST_Pos pos;
                                             pos.line.start   = ast_get_position($1).line.start;
                                             pos.column.start = ast_get_position($1).column.start;
                                             pos.line.stop    = ast_get_position($3).line.stop;
                                             pos.column.stop  = ast_get_position($3).column.stop;
                                             $$ = ast_op_xor(pos, $1, $3); }
     | TOK_OP_NOT expr                     { AST_Pos pos;
                                             pos.line.start   = $1.pos.line.start;
                                             pos.column.start = $1.pos.column.start;
                                             pos.line.stop    = ast_get_position($2).line.stop;
                                             pos.column.stop  = ast_get_position($2).column.stop;
                                             $$ = ast_op_negate(pos, $2); }
     | TOK_OP_SUBTRACT expr                { AST_Pos pos;
                                             pos.line.start   = $1.pos.line.start;
                                             pos.line.stop    = ast_get_position($2).line.stop;
                                             pos.column.start = $1.pos.column.start;
                                             pos.column.stop  = ast_get_position($2).column.stop;
                                             $$ = ast_op_negative(pos, $2); }
     | fcall                               { $$ = $1; }
     | cast                                { $$ = $1; }
     | constant                            { $$ = $1; }
     | variable                            { $$ = $1; }
     ;

cast : TOK_BOOLEAN TOK_OPEN_PAREN fargs TOK_CLOSE_PAREN { AST_Pos pos;
                                                          pos.line.start   = $1.pos.line.start;
                                                          pos.line.stop    = $1.pos.line.stop;
                                                          pos.column.start = $4.pos.column.start;
                                                          pos.column.stop  = $4.pos.column.stop;
                                                          $$ = ast_function_call(pos, "booleano", $3); }
     | TOK_INT32 TOK_OPEN_PAREN fargs TOK_CLOSE_PAREN   { AST_Pos pos;
                                                          pos.line.start   = $1.pos.line.start;
                                                          pos.line.stop    = $1.pos.line.stop;
                                                          pos.column.start = $4.pos.column.start;
                                                          pos.column.stop  = $4.pos.column.stop;
                                                          $$ = ast_function_call(pos, "inteiro", $3); }
     | TOK_FLOAT32 TOK_OPEN_PAREN fargs TOK_CLOSE_PAREN { AST_Pos pos;
                                                          pos.line.start   = $1.pos.line.start;
                                                          pos.line.stop    = $1.pos.line.stop;
                                                          pos.column.start = $4.pos.column.start;
                                                          pos.column.stop  = $4.pos.column.stop;
                                                          $$ = ast_function_call(pos, "real", $3); }
     | TOK_TEXT TOK_OPEN_PAREN fargs TOK_CLOSE_PAREN    { AST_Pos pos;
                                                          pos.line.start   = $1.pos.line.start;
                                                          pos.line.stop    = $1.pos.line.stop;
                                                          pos.column.start = $4.pos.column.start;
                                                          pos.column.stop  = $4.pos.column.stop;
                                                          $$ = ast_function_call(pos, "texto", $3); }
     ;

fcall : TOK_IDENTIFIER TOK_OPEN_PAREN fargs TOK_CLOSE_PAREN { AST_Pos pos;
                                                              pos.line.start   = $1.pos.line.start;
                                                              pos.line.stop    = $1.pos.line.stop;
                                                              pos.column.start = $4.pos.column.start;
                                                              pos.column.stop  = $4.pos.column.stop;
                                                              $$ = ast_function_call(pos, $1.text, $3);
                                                              free($1.text); }
      | TOK_IDENTIFIER TOK_OPEN_PAREN TOK_CLOSE_PAREN       { AST_Pos pos;
                                                              pos.line.start   = $1.pos.line.start;
                                                              pos.line.stop    = $1.pos.line.stop;
                                                              pos.column.start = $3.pos.column.start;
                                                              pos.column.stop  = $3.pos.column.stop;
                                                              $$ = ast_function_call(pos, $1.text, ast_arg_list());
                                                              free($1.text); }
      ;

fargs : fargs TOK_COMMA farg { ast_arg_list_add($1, $3);
                               $$ = $1; }
      | farg                 { AST_ArgList* list = ast_arg_list();
                               ast_arg_list_add(list, $1);
                               $$ = list; }
      ;

farg : expr { $$ = $1; }
          ;

constant : TOK_VAL_TRUE     { $$ = ast_boolean($1.pos, 1); }
         | TOK_VAL_FALSE    { $$ = ast_boolean($1.pos, 0); }
         | TOK_VAL_NUMBER   { int value;
#ifdef _MSC_VER
                              sscanf_s($1.text, "%d", &value);
#else
                              sscanf($1.text, "%d", &value);
#endif /* _MSC_VER */
                              $$ = ast_int32($1.pos, value);
                              free($1.text); }
         | TOK_VAL_FPNUMBER { float value;
#ifdef _MSC_VER
                              sscanf_s($1.text, "%f", &value);
#else
                              sscanf($1.text, "%f", &value);
#endif /* _MSC_VER */
                              $$ = ast_float32($1.pos, value);
                              free($1.text); }
         | TOK_VAL_TEXT     { $$ = ast_text($1.pos, $1.text);
                              free($1.text); }
         ; 

variable : TOK_IDENTIFIER { $$ = ast_variable($1.pos, $1.text);
                            free($1.text); }
         ; 

vartype : TOK_BOOLEAN { $$.pos = $1.pos;
                        $$.type = VBOOLEAN; }
        | TOK_INT32   { $$.pos = $1.pos;
                        $$.type = VINT32; }
        | TOK_FLOAT32 { $$.pos = $1.pos;
                        $$.type = VFLOAT32; }
        | TOK_TEXT    { $$.pos = $1.pos;
                        $$.type = VTEXT; }
        ;

%%
