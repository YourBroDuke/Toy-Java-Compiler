/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_TOYPARSER_TAB_H_INCLUDED
# define YY_YY_TOYPARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    DECIMAL_LITERAL = 259,
    HEX_LITERAL = 260,
    OCT_LITERAL = 261,
    BINARY_LITERAL = 262,
    FLOAT_LITERAL = 263,
    HEXFLOAT_LITERAL = 264,
    CHAR_LITERAL = 265,
    STRING_LITERAL = 266,
    ABSTRACT = 267,
    ASSERT = 268,
    AUTO = 269,
    BOOLEAN = 270,
    BREAK = 271,
    BYTE = 272,
    CASE = 273,
    CATCH = 274,
    CHAR = 275,
    CLASS = 276,
    CONST = 277,
    CONTINUE = 278,
    DEFAULT = 279,
    DO = 280,
    DOUBLE = 281,
    ELSE = 282,
    ENUM = 283,
    EXTENDS = 284,
    FINAL = 285,
    FINALLY = 286,
    FLOAT = 287,
    FOR = 288,
    IF = 289,
    GOTO = 290,
    IMPLEMENTS = 291,
    IMPORT = 292,
    INSTANCEOF = 293,
    INT = 294,
    INTERFACE = 295,
    LONG = 296,
    NATIVE = 297,
    NEW = 298,
    PACKAGE = 299,
    PRIVATE = 300,
    PROTECTED = 301,
    PUBLIC = 302,
    RETURN = 303,
    SHORT = 304,
    STATIC = 305,
    STRICTFP = 306,
    SUPER = 307,
    SWITCH = 308,
    SYNCHRONIZED = 309,
    THIS = 310,
    THROW = 311,
    THROWS = 312,
    TRANSIENT = 313,
    TRY = 314,
    VOID = 315,
    VOLATILE = 316,
    WHILE = 317,
    _AT = 318,
    _ELLIPSIS = 319,
    ASSIGN = 320,
    TILDE = 321,
    QUESTION = 322,
    DCOLON = 323,
    COLON = 324,
    LPAREN = 325,
    RPAREN = 326,
    LBRACE = 327,
    RBRACE = 328,
    LBRACK = 329,
    RBRACK = 330,
    DOT = 331,
    COMMA = 332,
    SEMIC = 333,
    BANG = 334,
    LT = 335,
    GT = 336,
    BITAND = 337,
    BITOR = 338,
    CARET = 339,
    ADD = 340,
    SUB = 341,
    MUL = 342,
    DIV = 343,
    MOD = 344,
    EQUAL = 345,
    NEQUAL = 346,
    LTOE = 347,
    GTOE = 348,
    AND = 349,
    OR = 350,
    LSHIFT = 351,
    RSHIFT = 352,
    INCRE = 353,
    DEFAULT_VAL = 354,
    ARROW = 355,
    DECRE = 356,
    ADD_ASSIGN = 357,
    SUB_ASSIGN = 358,
    MUL_ASSIGN = 359,
    DIV_ASSIGN = 360,
    AND_ASSIGN = 361,
    OR_ASSIGN = 362,
    XOR_ASSIGN = 363,
    MOD_ASSIGN = 364,
    LSHIFT_ASSIGN = 365,
    RSHIFT_ASSIGN = 366,
    URSHIFT = 367,
    URSHIFT_ASSIGN = 368,
    NULL_LITERAL = 369,
    TRUE_LITERAL = 370,
    FALSE_LITERAL = 371
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 28 "ToyParser.y" /* yacc.c:1909  */

	std::string *string;
	int token;

#line 176 "ToyParser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TOYPARSER_TAB_H_INCLUDED  */
