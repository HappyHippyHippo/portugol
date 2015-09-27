/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_VAL_NUMBER = 258,
     TOK_VAL_FPNUMBER = 259,
     TOK_VAL_TEXT = 260,
     TOK_IDENTIFIER = 261,
     TOK_BOOLEAN = 262,
     TOK_INTEGER = 263,
     TOK_FLOAT = 264,
     TOK_TEXT = 265,
     TOK_EOL = 266,
     TOK_COMA = 267,
     TOK_OPEN_PAREN = 268,
     TOK_CLOSE_PAREN = 269,
     TOK_OP_NOT = 270,
     TOK_OP_MULTIPLY = 271,
     TOK_OP_DIVIDE = 272,
     TOK_OP_REMAINDER = 273,
     TOK_OP_ADD = 274,
     TOK_OP_SUBTRACT = 275,
     TOK_OP_EQUAL = 276,
     TOK_OP_INEQUAL = 277,
     TOK_OP_GREATER = 278,
     TOK_OP_GREATER_OR_EQUAL = 279,
     TOK_OP_LESSER = 280,
     TOK_OP_LESSER_OR_EQUAL = 281,
     TOK_OP_AND = 282,
     TOK_OP_OR = 283,
     TOK_OP_XOR = 284,
     TOK_OP_ASSIGN = 285
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 13 "lex/portugol.y"
 ParseAST     ast;
         ParseInt32   int32;
         ParseFloat32 float32;
         ParseText    text;
         ParseToken   token;
         ASTNode*     global;



/* Line 1685 of yacc.c  */
#line 91 "lex/parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;

