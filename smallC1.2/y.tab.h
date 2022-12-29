
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
     CALLSYM = 258,
     CONSTSYM = 259,
     IFSYM = 260,
     PROCSYM = 261,
     READSYM = 262,
     INTSYM = 263,
     WHILESYM = 264,
     WRITESYM = 265,
     FORSYM = 266,
     DOSYM = 267,
     WHENSYM = 268,
     REPEATSYM = 269,
     UNTILSYM = 270,
     LSS = 271,
     LEQ = 272,
     GTR = 273,
     GEQ = 274,
     PLUS = 275,
     MINUS = 276,
     TIMES = 277,
     SLASH = 278,
     LPAREN = 279,
     RPAREN = 280,
     EQL = 281,
     COMMA = 282,
     PERIOD = 283,
     NEQ = 284,
     SEMICOLON = 285,
     NOT = 286,
     EQUALS = 287,
     ELSESYM = 288,
     LBRACE = 289,
     RBRACE = 290,
     MOD = 291,
     XOR = 292,
     ODDSYM = 293,
     MOREPLUS = 294,
     MOREMINUS = 295,
     AND = 296,
     OR = 297,
     CONTINUESYM = 298,
     EXITSYM = 299,
     BREAKSYM = 300,
     LOWER_THAN_ELSE = 301,
     LOWER_THAN_MORE = 302,
     LOWER_THAN_SEMICOLON = 303,
     IDENT = 304,
     NUMBER = 305
   };
#endif
/* Tokens.  */
#define CALLSYM 258
#define CONSTSYM 259
#define IFSYM 260
#define PROCSYM 261
#define READSYM 262
#define INTSYM 263
#define WHILESYM 264
#define WRITESYM 265
#define FORSYM 266
#define DOSYM 267
#define WHENSYM 268
#define REPEATSYM 269
#define UNTILSYM 270
#define LSS 271
#define LEQ 272
#define GTR 273
#define GEQ 274
#define PLUS 275
#define MINUS 276
#define TIMES 277
#define SLASH 278
#define LPAREN 279
#define RPAREN 280
#define EQL 281
#define COMMA 282
#define PERIOD 283
#define NEQ 284
#define SEMICOLON 285
#define NOT 286
#define EQUALS 287
#define ELSESYM 288
#define LBRACE 289
#define RBRACE 290
#define MOD 291
#define XOR 292
#define ODDSYM 293
#define MOREPLUS 294
#define MOREMINUS 295
#define AND 296
#define OR 297
#define CONTINUESYM 298
#define EXITSYM 299
#define BREAKSYM 300
#define LOWER_THAN_ELSE 301
#define LOWER_THAN_MORE 302
#define LOWER_THAN_SEMICOLON 303
#define IDENT 304
#define NUMBER 305




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 93 "smallC.y"

char *ident;
int number;



/* Line 1676 of yacc.c  */
#line 159 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


