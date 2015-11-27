%{
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <internal/portugol/lex/lex.h>
#include "parser.h"

int yycolumn = 1;

#define STORE_POS(pos, yylloc)                 \
    ((pos).line.start   = yylloc.first_line,   \
     (pos).column.start = yylloc.first_column, \
     (pos).line.stop    = yylloc.last_line,    \
     (pos).column.stop  = yylloc.last_column)

#define YY_USER_ACTION                                 \
    yylloc.first_line   = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn;                    \
    yylloc.last_column  = yycolumn + yyleng;           \
    yycolumn           += yyleng;

void
ast_parse_remove_ml_comment(void);

%}

%option yylineno

%%

(?i:"verdadeiro") {
        /* true boolean value token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_VAL_TRUE;
    }

(?i:"falso") {
        /* false boolean value token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_VAL_FALSE;
    }

(?i:"booleano") {
        /* boolean reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_BOOLEAN;
    }

(?i:"inteiro") {
        /* int32 reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_INT32;
    }

(?i:"real") {
        /* float32 reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_FLOAT32;
    }

(?i:"texto") {
        /* text reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_TEXT;
    }

(?i:"e") {
        /* and op reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_AND;
    }

(?i:"ou") {
        /* or op reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_OR;
    }

(?i:"xou") {
        /* xor op reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_XOR;
    }

(?i:"nao")|(?i:"não")|(?i:"nÃo") {
        /* not op reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_NOT;
    }

(?i:"fim") {
        /* end reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_END;
    }

(?i:"de") {
        /* of reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OF;
    }

(?i:"se") {
        /* if control structure reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_IF;
    }

(?i:"entao")|(?i:"então")|(?i:"entÃo") {
        /* then reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_THEN;
    }

(?i:"senao")|(?i:"senão")|(?i:"senÃo") {
        /* else reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_ELSE;
    }

(?i:"enquanto") {
        /* while control structure reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_WHILE;
    }

(?i:"para") {
        /* for control structure reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_FOR;
    }

(?i:"ate")|(?i:"até")|(?i:"atÉ") {
        /* to control structure reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_TO;
    }

(?i:"passo") {
        /* step control structure reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_STEP;
    }

(?i:"funcao")|(?i:"funcão")|(?i:"funcÃo")|(?i:"funçao")|(?i:"função")|(?i:"funçÃo")|(?i:"funÇao")|(?i:"funÇão")|(?i:"funÇÃo") {
        /* function reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_FUNCTION;
    }

(?i:"retorna") {
        /* return reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_RETURN;
    }

(?i:"programa") {
        /* program reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_PROGRAM;
    }

(?i:"importar") {
        /* program reserved word */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_IMPORT;
    }

"+" {
        /* addition op token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_ADD;
    }

"-" {
        /* subtraction op token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_SUBTRACT;
    }

"*" {
        /* multiplication op token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_MULTIPLY;
    }

"/" {
        /* division op token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_DIVIDE;
    }

"%" {
        /* remainder op token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_REMAINDER;
    }

"=" {
        /* equal op token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_EQUAL;
    }

"<>" {
        /* inequal op token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_INEQUAL;
    }

">" {
        /* greater op token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_GREATER;
    }

">=" {
        /* greater_or_euqal op token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_GREATER_OR_EQUAL;
    }

"<" {
        /* lesser op token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_LESSER;
    }

"<=" {
        /* lesser_or_euqal op token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_LESSER_OR_EQUAL;
    }

"<-" {
        /* assign op token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OP_ASSIGN;
    }

"(" {
        /* open parenthesis token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_OPEN_PAREN;
    }

")" {
        /* close parenthesis token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_CLOSE_PAREN;
    }

":" {
        /* colon token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_COLON;
    }

"," {
        /* comma token */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.text = yytext;
        return yylval.token.token = TOK_COMMA;
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
        STORE_POS(yylval.token.pos, yylloc);

        size_t length = strlen(yytext);
        yylval.token.text = malloc(length + 1);
#ifdef _MSC_VER
        strcpy_s(yylval.token.text, length + 1, yytext);
#else
        strcpy(yylval.token.text, yytext);
#endif /* _MSC_VER */
        return yylval.token.token = TOK_IDENTIFIER;
    }

[0-9]*\.[0-9]* {
        /* float value */
        STORE_POS(yylval.token.pos, yylloc);

        size_t length = strlen(yytext);
        yylval.token.text = malloc(length + 1);
#ifdef _MSC_VER
        strcpy_s(yylval.token.text, length + 1, yytext);
#else
        strcpy(yylval.token.text, yytext);
#endif /* _MSC_VER */
        return yylval.token.token = TOK_VAL_FPNUMBER;
    }

[0-9]* {
        /* integer value */
        STORE_POS(yylval.token.pos, yylloc);

        size_t length = strlen(yytext);
        yylval.token.text = malloc(length + 1);
#ifdef _MSC_VER
        strcpy_s(yylval.token.text, length + 1, yytext);
#else
        strcpy(yylval.token.text, yytext);
#endif /* _MSC_VER */
        return yylval.token.token = TOK_VAL_NUMBER;
    }

\"([^\\\"]|\\.)*\" {
        /* text value */
        STORE_POS(yylval.token.pos, yylloc);

        size_t length = strlen(yytext);
        yylval.token.text = malloc(length + 1);
#ifdef _MSC_VER
        strncpy_s(yylval.token.text, length + 1, &yytext[1], length - 2);
        yylval.token.text[length - 2] = 0;
#else
        strncpy(yylval.token.text, &yytext[1], length - 2);
        yylval.token.text[length - 2] = 0;
#endif /* _MSC_VER */
        return yylval.token.token = TOK_VAL_TEXT;
    }

\n {
        /* end-of-line character */
        STORE_POS(yylval.token.pos, yylloc);

        yylval.token.pos.line.start--;
        yylval.token.pos.line.stop--;
        yycolumn = 0;
        return yylval.token.token = TOK_EOL;
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
