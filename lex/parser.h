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
    TOK_VAL_BOOLEAN = 258,
    TOK_VAL_NUMBER = 259,
    TOK_VAL_FPNUMBER = 260,
    TOK_VAL_TEXT = 261,
    TOK_IDENTIFIER = 262,
    TOK_COLON = 263,
    TOK_BOOLEAN = 264,
    TOK_INTEGER = 265,
    TOK_FLOAT = 266,
    TOK_TEXT = 267,
    TOK_EOL = 268,
    TOK_FUNCTION = 269,
    TOK_RETURN = 270,
    TOK_PROGRAM = 271,
    TOK_COMMA = 272,
    TOK_END = 273,
    TOK_OF = 274,
    TOK_IF = 275,
    TOK_THEN = 276,
    TOK_ELSE = 277,
    TOK_FOR = 278,
    TOK_TO = 279,
    TOK_STEP = 280,
    TOK_SWITCH = 281,
    TOK_CASE = 282,
    TOK_DEFAULT = 283,
    TOK_WHILE = 284,
    TOK_OPEN_PAREN = 285,
    TOK_CLOSE_PAREN = 286,
    TOK_OP_NOT = 287,
    TOK_OP_MULTIPLY = 288,
    TOK_OP_DIVIDE = 289,
    TOK_OP_REMAINDER = 290,
    TOK_OP_ADD = 291,
    TOK_OP_SUBTRACT = 292,
    TOK_OP_EQUAL = 293,
    TOK_OP_INEQUAL = 294,
    TOK_OP_GREATER = 295,
    TOK_OP_GREATER_OR_EQUAL = 296,
    TOK_OP_LESSER = 297,
    TOK_OP_LESSER_OR_EQUAL = 298,
    TOK_OP_AND = 299,
    TOK_OP_OR = 300,
    TOK_OP_XOR = 301,
    TOK_OP_ASSIGN = 302
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 20 "lex/portugol.y" /* yacc.c:1909  */
 ParseAST     ast;
         ParseBool    bool;
         ParseInt32   int32;
         ParseFloat32 float32;
         ParseText    text;
         ParseToken   token;
         ParseFParam  fparam;
         ParseFParams fparams;
         ParseFArgs   farguments;
         AST_Node*    global;

#line 114 "lex/parser.h" /* yacc.c:1909  */
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
