%{
#include <stdio.h>
#include <string.h>

#include <internal/portugol/ast.h>
#include "parser.h"

int yycolumn = 1;

#define STORE_POS(pos, yylloc) ((pos).lstart = yylloc.first_line, \
                                (pos).lend   = yylloc.last_line, \
                                (pos).cstart = yylloc.first_column, \
                                (pos).cend   = yylloc.last_column)

#define YY_USER_ACTION \
    yylloc.first_line   = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column  = yycolumn + yyleng - 1; \
    yycolumn           += yyleng;

void
ast_parse_remove_ml_comment(void);

%}

%option yylineno

%%
(?i:"booleano") {
        /* boolean token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_BOOLEAN;
    }
(?i:"inteiro") {
        /* int32 token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_INTEGER;
    }
(?i:"racional") {
        /* float32 token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_FLOAT;
    }
(?i:"texto") {
        /* text token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_TEXT;
    }
(?i:"e") {
        /* and op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_AND;
    }
(?i:"ou") {
        /* or op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_OR;
    }
(?i:"xou") {
        /* xor op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_XOR;
    }
(?i:"nao")|(?i:"não")|(?i:"nÃo") {
        /* not op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_NOT;
    }
(?i:"fim") {
        /* xor op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_END;
    }
(?i:"de") {
        /* xor op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_FROM;
    }
(?i:"se") {
        /* xor op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_IF;
    }
(?i:"entao")|(?i:"então")|(?i:"entÃo") {
        /* xor op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_THEN;
    }
(?i:"senao")|(?i:"senão")|(?i:"senÃo") {
        /* xor op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_ELSE;
    }

"+" {
        /* addition op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_ADD;
    }
"-" {
        /* subtraction op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_SUBTRACT;
    }
"*" {
        /* multiplication op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_MULTIPLY;
    }
"/" {
        /* division op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_DIVIDE;
    }
"%" {
        /* remainder op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_REMAINDER;
    }
"=" {
        /* equal op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_EQUAL;
    }
"<>" {
        /* inequal op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_INEQUAL;
    }
">" {
        /* greater op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_GREATER;
    }
">=" {
        /* greater_or_euqal op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_GREATER_OR_EQUAL;
    }
"<" {
        /* lesser op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_LESSER;
    }
"<=" {
        /* lesser_or_euqal op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_LESSER_OR_EQUAL;
    }
"<-" {
        /* assign op token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OP_ASSIGN;
    }

"(" {
        /* open parenthesis token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_OPEN_PAREN;
    }
")" {
        /* close parenthesis token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_CLOSE_PAREN;
    }
":" {
        /* coma token */
        STORE_POS(yylval.token.pos, yylloc);
        return yylval.token.result = TOK_COMA;
    }

"/*" {
        /* ignore multiline comment */
        ast_parse_remove_ml_comment();
    }
\/\/[^\n]* {
        /* ignore line comment */
        ;
    }

[a-zA-Z_][a-zA-Z0-9_]* {
        /* id value */
        STORE_POS(yylval.text.pos, yylloc);
        yylval.text.result = malloc(strlen(yytext) + 1);
        strcpy(yylval.text.result, yytext);
        return TOK_IDENTIFIER;
    }
[0-9]*\.[0-9]* {
        /* float value */
        STORE_POS(yylval.float32.pos, yylloc);
        sscanf(yytext, "%f", &yylval.float32.result);
        return TOK_VAL_FPNUMBER;
    }
[0-9]* {
        /* integer value */
        STORE_POS(yylval.int32.pos, yylloc);
        sscanf(yytext, "%d", &yylval.int32.result);
        return TOK_VAL_NUMBER;
    }
\"([^\\\"]|\\.)*\" {
        /* text value */
        STORE_POS(yylval.text.pos, yylloc);
        yylval.text.result = malloc(strlen(yytext) - 1);
        strcpy(yylval.text.result, &yytext[1]);
        yylval.text.result[strlen(yylval.text.result) - 1] = 0;
        return TOK_VAL_TEXT;
    }

\n {
        /* end-of-line character */
        STORE_POS(yylval.token.pos, yylloc);
        yylval.token.pos.lstart--;
        yylval.token.pos.lend--;
        yycolumn = 1;
        return yylval.token.result = TOK_EOL;
    }
[ \t] {
        /* ignore spaces */
        ;
    }

. {
        /* unknown token */
        printf("Unknown token!\n");
        yyterminate();
    }

%%

int yywrap(void) { return 1; }

void
ast_parse_remove_ml_comment(void)
{
    // http://www.lysator.liu.se/c/ANSI-C-grammar-l.html
    char c, c1;

loop:
    while ((c = input()) != '*' && c != 0)
        /* void */;

    if ((c1 = input()) != '/' && c != 0)
    {
        unput(c1);
        goto loop;
    }
}
