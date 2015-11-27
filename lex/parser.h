/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_LEX_PARSER_H_INCLUDED
# define YY_YY_LEX_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_EOL = 258,
    TOK_VAL_TRUE = 259,
    TOK_VAL_FALSE = 260,
    TOK_VAL_NUMBER = 261,
    TOK_VAL_FPNUMBER = 262,
    TOK_VAL_TEXT = 263,
    TOK_OP_NOT = 264,
    TOK_OP_ADD = 265,
    TOK_OP_SUBTRACT = 266,
    TOK_OP_MULTIPLY = 267,
    TOK_OP_DIVIDE = 268,
    TOK_OP_REMAINDER = 269,
    TOK_OP_EQUAL = 270,
    TOK_OP_INEQUAL = 271,
    TOK_OP_GREATER = 272,
    TOK_OP_GREATER_OR_EQUAL = 273,
    TOK_OP_LESSER = 274,
    TOK_OP_LESSER_OR_EQUAL = 275,
    TOK_OP_AND = 276,
    TOK_OP_OR = 277,
    TOK_OP_XOR = 278,
    TOK_OP_ASSIGN = 279,
    TOK_IDENTIFIER = 280,
    TOK_COMMA = 281,
    TOK_COLON = 282,
    TOK_BOOLEAN = 283,
    TOK_INT32 = 284,
    TOK_FLOAT32 = 285,
    TOK_TEXT = 286,
    TOK_END = 287,
    TOK_OF = 288,
    TOK_IF = 289,
    TOK_THEN = 290,
    TOK_ELSE = 291,
    TOK_FOR = 292,
    TOK_TO = 293,
    TOK_STEP = 294,
    TOK_WHILE = 295,
    TOK_RETURN = 296,
    TOK_FUNCTION = 297,
    TOK_PROGRAM = 298,
    TOK_IMPORT = 299,
    TOK_OPEN_PAREN = 300,
    TOK_CLOSE_PAREN = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 16 "lex/portugol.y" /* yacc.c:1909  */

    AST_Node*                 ast;
    AST_ParamList*            fparams;
    LexParam                  fparam;
    AST_ArgList*              fargs;
    LexToken                  token;
    LexVarType                vtype;

#line 110 "lex/parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_LEX_PARSER_H_INCLUDED  */
