/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1





# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "token.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_REGISTER_RAX = 3,         /* TOKEN_REGISTER_RAX  */
  YYSYMBOL_TOKEN_REGISTER_RBX = 4,         /* TOKEN_REGISTER_RBX  */
  YYSYMBOL_TOKEN_REGISTER_RCX = 5,         /* TOKEN_REGISTER_RCX  */
  YYSYMBOL_TOKEN_REGISTER_RDX = 6,         /* TOKEN_REGISTER_RDX  */
  YYSYMBOL_TOKEN_REGISTER_FIRST_FUNCTION_ARG = 7, /* TOKEN_REGISTER_FIRST_FUNCTION_ARG  */
  YYSYMBOL_TOKEN_REGISTER_SECOND_FUNCTION_ARG = 8, /* TOKEN_REGISTER_SECOND_FUNCTION_ARG  */
  YYSYMBOL_TOKEN_REGISTER_STACK_POINTER = 9, /* TOKEN_REGISTER_STACK_POINTER  */
  YYSYMBOL_TOKEN_REGISTER_FRAME_POINTER = 10, /* TOKEN_REGISTER_FRAME_POINTER  */
  YYSYMBOL_TOKEN_REGISTER_8 = 11,          /* TOKEN_REGISTER_8  */
  YYSYMBOL_TOKEN_REGISTER_9 = 12,          /* TOKEN_REGISTER_9  */
  YYSYMBOL_TOKEN_REGISTER_10 = 13,         /* TOKEN_REGISTER_10  */
  YYSYMBOL_TOKEN_REGISTER_11 = 14,         /* TOKEN_REGISTER_11  */
  YYSYMBOL_TOKEN_REGISTER_12 = 15,         /* TOKEN_REGISTER_12  */
  YYSYMBOL_TOKEN_REGISTER_13 = 16,         /* TOKEN_REGISTER_13  */
  YYSYMBOL_TOKEN_REGISTER_14 = 17,         /* TOKEN_REGISTER_14  */
  YYSYMBOL_TOKEN_REGISTER_15 = 18,         /* TOKEN_REGISTER_15  */
  YYSYMBOL_TOKEN_IMMEDIATE = 19,           /* TOKEN_IMMEDIATE  */
  YYSYMBOL_TOKEN_DIGIT = 20,               /* TOKEN_DIGIT  */
  YYSYMBOL_TOKEN_OP_LEFT_PAREN = 21,       /* TOKEN_OP_LEFT_PAREN  */
  YYSYMBOL_TOKEN_OP_RIGHT_PAREN = 22,      /* TOKEN_OP_RIGHT_PAREN  */
  YYSYMBOL_TOKEN_OP_COMMA = 23,            /* TOKEN_OP_COMMA  */
  YYSYMBOL_TOKEN_OP_COLON = 24,            /* TOKEN_OP_COLON  */
  YYSYMBOL_TOKEN_OP_NEWLINE = 25,          /* TOKEN_OP_NEWLINE  */
  YYSYMBOL_TOKEN_DIRECTIVE_DATA = 26,      /* TOKEN_DIRECTIVE_DATA  */
  YYSYMBOL_TOKEN_DIRECTIVE_QUAD = 27,      /* TOKEN_DIRECTIVE_QUAD  */
  YYSYMBOL_TOKEN_DIRECTIVE_TEXT = 28,      /* TOKEN_DIRECTIVE_TEXT  */
  YYSYMBOL_TOKEN_DIRECTIVE_GLOBAL = 29,    /* TOKEN_DIRECTIVE_GLOBAL  */
  YYSYMBOL_TOKEN_DIRECTIVE_SECTION = 30,   /* TOKEN_DIRECTIVE_SECTION  */
  YYSYMBOL_TOKEN_DIRECTIVE_GNU_STACK = 31, /* TOKEN_DIRECTIVE_GNU_STACK  */
  YYSYMBOL_TOKEN_DIRECTIVE_PROGBITS = 32,  /* TOKEN_DIRECTIVE_PROGBITS  */
  YYSYMBOL_TOKEN_DIRECTIVE_FILE = 33,      /* TOKEN_DIRECTIVE_FILE  */
  YYSYMBOL_TOKEN_DIRECTIVE_STRING = 34,    /* TOKEN_DIRECTIVE_STRING  */
  YYSYMBOL_TOKEN_IDENTIFIER = 35,          /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_LITERAL_STRING = 36,      /* TOKEN_LITERAL_STRING  */
  YYSYMBOL_TOKEN_INSTR_MOVQ = 37,          /* TOKEN_INSTR_MOVQ  */
  YYSYMBOL_TOKEN_INSTR_LEAQ = 38,          /* TOKEN_INSTR_LEAQ  */
  YYSYMBOL_TOKEN_INSTR_ADDQ = 39,          /* TOKEN_INSTR_ADDQ  */
  YYSYMBOL_TOKEN_INSTR_SUBQ = 40,          /* TOKEN_INSTR_SUBQ  */
  YYSYMBOL_TOKEN_INSTR_IMULQ = 41,         /* TOKEN_INSTR_IMULQ  */
  YYSYMBOL_TOKEN_INSTR_IDIVQ = 42,         /* TOKEN_INSTR_IDIVQ  */
  YYSYMBOL_TOKEN_INSTR_NEGQ = 43,          /* TOKEN_INSTR_NEGQ  */
  YYSYMBOL_TOKEN_INSTR_INCQ = 44,          /* TOKEN_INSTR_INCQ  */
  YYSYMBOL_TOKEN_INSTR_DECQ = 45,          /* TOKEN_INSTR_DECQ  */
  YYSYMBOL_TOKEN_INSTR_CQO = 46,           /* TOKEN_INSTR_CQO  */
  YYSYMBOL_TOKEN_INSTR_CMPQ = 47,          /* TOKEN_INSTR_CMPQ  */
  YYSYMBOL_TOKEN_INSTR_JE = 48,            /* TOKEN_INSTR_JE  */
  YYSYMBOL_TOKEN_INSTR_JNE = 49,           /* TOKEN_INSTR_JNE  */
  YYSYMBOL_TOKEN_INSTR_JL = 50,            /* TOKEN_INSTR_JL  */
  YYSYMBOL_TOKEN_INSTR_JG = 51,            /* TOKEN_INSTR_JG  */
  YYSYMBOL_TOKEN_INSTR_JLE = 52,           /* TOKEN_INSTR_JLE  */
  YYSYMBOL_TOKEN_INSTR_JGE = 53,           /* TOKEN_INSTR_JGE  */
  YYSYMBOL_TOKEN_INSTR_JMP = 54,           /* TOKEN_INSTR_JMP  */
  YYSYMBOL_TOKEN_INSTR_CALL = 55,          /* TOKEN_INSTR_CALL  */
  YYSYMBOL_TOKEN_INSTR_PUSHQ = 56,         /* TOKEN_INSTR_PUSHQ  */
  YYSYMBOL_TOKEN_INSTR_POPQ = 57,          /* TOKEN_INSTR_POPQ  */
  YYSYMBOL_TOKEN_INSTR_RET = 58,           /* TOKEN_INSTR_RET  */
  YYSYMBOL_TOKEN_INSTR_NOP = 59,           /* TOKEN_INSTR_NOP  */
  YYSYMBOL_TOKEN_ERROR_UNDEFINED_CHAR = 60, /* TOKEN_ERROR_UNDEFINED_CHAR  */
  YYSYMBOL_TOKEN_EOF = 61,                 /* TOKEN_EOF  */
  YYSYMBOL_YYACCEPT = 62,                  /* $accept  */
  YYSYMBOL_program = 63,                   /* program  */
  YYSYMBOL_identifier = 64,                /* identifier  */
  YYSYMBOL_operand = 65,                   /* operand  */
  YYSYMBOL_memory = 66,                    /* memory  */
  YYSYMBOL_label = 67,                     /* label  */
  YYSYMBOL_immediate = 68,                 /* immediate  */
  YYSYMBOL_register = 69,                  /* register  */
  YYSYMBOL_instruction_2_operand = 70,     /* instruction_2_operand  */
  YYSYMBOL_instruction_1_operand = 71,     /* instruction_1_operand  */
  YYSYMBOL_instruction_0_operand = 72,     /* instruction_0_operand  */
  YYSYMBOL_instruction = 73,               /* instruction  */
  YYSYMBOL_line = 74,                      /* line  */
  YYSYMBOL_directive = 75,                 /* directive  */
  YYSYMBOL_line_list = 76,                 /* line_list  */
  YYSYMBOL_literal_string = 77,            /* literal_string  */
  YYSYMBOL_literal_digit = 78              /* literal_digit  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 93 "parserAssembler.bison"


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scannerAssemblerFunc.h"
#include "astAssembler.h"

extern char *yytext;
extern int yylex();
extern int yyerror( char *str );
extern struct asm_program * program_pointer;


#line 197 "parserAssembler.c"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  50
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   104

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  92

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   316


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   113,   113,   114,   117,   120,   121,   122,   123,   126,
     127,   130,   133,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   154,
     155,   156,   157,   158,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   178,
     179,   180,   183,   184,   185,   188,   189,   190,   191,   194,
     195,   197,   198,   199,   200,   201,   204,   205,   208,   211
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_REGISTER_RAX",
  "TOKEN_REGISTER_RBX", "TOKEN_REGISTER_RCX", "TOKEN_REGISTER_RDX",
  "TOKEN_REGISTER_FIRST_FUNCTION_ARG",
  "TOKEN_REGISTER_SECOND_FUNCTION_ARG", "TOKEN_REGISTER_STACK_POINTER",
  "TOKEN_REGISTER_FRAME_POINTER", "TOKEN_REGISTER_8", "TOKEN_REGISTER_9",
  "TOKEN_REGISTER_10", "TOKEN_REGISTER_11", "TOKEN_REGISTER_12",
  "TOKEN_REGISTER_13", "TOKEN_REGISTER_14", "TOKEN_REGISTER_15",
  "TOKEN_IMMEDIATE", "TOKEN_DIGIT", "TOKEN_OP_LEFT_PAREN",
  "TOKEN_OP_RIGHT_PAREN", "TOKEN_OP_COMMA", "TOKEN_OP_COLON",
  "TOKEN_OP_NEWLINE", "TOKEN_DIRECTIVE_DATA", "TOKEN_DIRECTIVE_QUAD",
  "TOKEN_DIRECTIVE_TEXT", "TOKEN_DIRECTIVE_GLOBAL",
  "TOKEN_DIRECTIVE_SECTION", "TOKEN_DIRECTIVE_GNU_STACK",
  "TOKEN_DIRECTIVE_PROGBITS", "TOKEN_DIRECTIVE_FILE",
  "TOKEN_DIRECTIVE_STRING", "TOKEN_IDENTIFIER", "TOKEN_LITERAL_STRING",
  "TOKEN_INSTR_MOVQ", "TOKEN_INSTR_LEAQ", "TOKEN_INSTR_ADDQ",
  "TOKEN_INSTR_SUBQ", "TOKEN_INSTR_IMULQ", "TOKEN_INSTR_IDIVQ",
  "TOKEN_INSTR_NEGQ", "TOKEN_INSTR_INCQ", "TOKEN_INSTR_DECQ",
  "TOKEN_INSTR_CQO", "TOKEN_INSTR_CMPQ", "TOKEN_INSTR_JE",
  "TOKEN_INSTR_JNE", "TOKEN_INSTR_JL", "TOKEN_INSTR_JG", "TOKEN_INSTR_JLE",
  "TOKEN_INSTR_JGE", "TOKEN_INSTR_JMP", "TOKEN_INSTR_CALL",
  "TOKEN_INSTR_PUSHQ", "TOKEN_INSTR_POPQ", "TOKEN_INSTR_RET",
  "TOKEN_INSTR_NOP", "TOKEN_ERROR_UNDEFINED_CHAR", "TOKEN_EOF", "$accept",
  "program", "identifier", "operand", "memory", "label", "immediate",
  "register", "instruction_2_operand", "instruction_1_operand",
  "instruction_0_operand", "instruction", "line", "directive", "line_list",
  "literal_string", "literal_digit", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-37)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      11,   -37,   -37,   -17,   -37,   -31,   -26,   -30,   -30,   -37,
     -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,
     -37,   -37,   -37,     9,   -16,   -15,     8,     8,   -37,     5,
      11,     6,   -37,   -37,   -37,   -37,    10,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,
      71,   -37,    12,   -37,   -37,   -37,    13,   -37,   -37,   -37,
     -37,   -30,    49,     8,    71,    68,   -37,   -37,    50,     0,
     -37,   -37
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,    58,    61,     0,    63,     0,     0,     0,     0,     4,
      29,    30,    31,    32,    35,    36,    34,    37,    38,    49,
      33,    40,    41,    42,    44,    43,    45,    46,    39,    47,
      48,    50,    51,     0,     0,     0,     0,     0,    54,     0,
      67,     0,     3,    69,    65,    62,     0,    68,    59,    64,
       1,    11,    56,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    12,
       0,     5,     0,     7,     6,     8,     0,    53,    55,    66,
      57,     0,     0,     0,     0,     0,     9,    52,     0,     0,
      10,    60
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -37,   -37,     2,   -36,   -37,   -37,   -37,    20,   -37,   -37,
     -37,   -37,   -37,   -37,    52,    -8,    90
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    33,    71,    72,    73,    35,    74,    75,    36,    37,
      38,    39,    40,    41,    42,    48,    76
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      49,    77,    34,    43,     9,    46,    47,    45,    51,    50,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    43,    70,
      78,    80,    91,    81,    84,    83,     1,     2,     3,     4,
       5,     6,    34,     9,     7,     8,     9,    87,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    86,    90,    85,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      82,    89,    79,    44,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    88
};

static const yytype_int8 yycheck[] =
{
       8,    37,     0,    20,    35,    31,    36,     5,    24,     0,
      25,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      25,    25,    32,    23,    21,    23,    25,    26,    27,    28,
      29,    30,    40,    35,    33,    34,    35,    83,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    22,    22,    81,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      70,    23,    40,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    25,    26,    27,    28,    29,    30,    33,    34,    35,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    63,    64,    67,    70,    71,    72,    73,
      74,    75,    76,    20,    78,    64,    31,    36,    77,    77,
       0,    24,    25,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      21,    64,    65,    66,    68,    69,    78,    65,    25,    76,
      25,    23,    69,    23,    21,    77,    22,    65,    69,    23,
      22,    32
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    63,    63,    64,    65,    65,    65,    65,    66,
      66,    67,    68,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    70,
      70,    70,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    72,
      72,    72,    73,    73,    73,    74,    74,    74,    74,    75,
      75,    75,    75,    75,    75,    75,    76,    76,    77,    78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     1,     1,     1,     1,     1,     3,
       4,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     2,     1,     2,     2,     2,     1,     2,
       6,     1,     2,     1,     2,     2,     2,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: %empty  */
#line 113 "parserAssembler.bison"
                           { (yyval.program) = 0; }
#line 1235 "parserAssembler.c"
    break;

  case 3: /* program: line_list  */
#line 114 "parserAssembler.bison"
                           { program_pointer = (yyval.program) = program_create((yyvsp[0].line)); }
#line 1241 "parserAssembler.c"
    break;

  case 4: /* identifier: TOKEN_IDENTIFIER  */
#line 117 "parserAssembler.bison"
                              { (yyval.name) = strdup(yytext); }
#line 1247 "parserAssembler.c"
    break;

  case 5: /* operand: identifier  */
#line 120 "parserAssembler.bison"
                      { (yyval.operand) = operand_create_label((yyvsp[0].name)); }
#line 1253 "parserAssembler.c"
    break;

  case 6: /* operand: immediate  */
#line 121 "parserAssembler.bison"
                      { (yyval.operand) = operand_create_immediate((yyvsp[0].imm)); }
#line 1259 "parserAssembler.c"
    break;

  case 7: /* operand: memory  */
#line 122 "parserAssembler.bison"
                      { (yyval.operand) = (yyvsp[0].operand); }
#line 1265 "parserAssembler.c"
    break;

  case 8: /* operand: register  */
#line 123 "parserAssembler.bison"
                      { (yyval.operand) = operand_create_register((yyvsp[0].reg_num)); }
#line 1271 "parserAssembler.c"
    break;

  case 9: /* memory: TOKEN_OP_LEFT_PAREN register TOKEN_OP_RIGHT_PAREN  */
#line 126 "parserAssembler.bison"
                                                                             { (yyval.operand) = operand_create_memory(0, (yyvsp[-1].reg_num)); }
#line 1277 "parserAssembler.c"
    break;

  case 10: /* memory: literal_digit TOKEN_OP_LEFT_PAREN register TOKEN_OP_RIGHT_PAREN  */
#line 127 "parserAssembler.bison"
                                                                             { (yyval.operand) = operand_create_memory((yyvsp[-3].imm), (yyvsp[-1].reg_num)); }
#line 1283 "parserAssembler.c"
    break;

  case 11: /* label: identifier TOKEN_OP_COLON  */
#line 130 "parserAssembler.bison"
                                      { (yyval.line) = line_create(ASM_LINE_LABEL, (yyvsp[-1].name), 0, 0); }
#line 1289 "parserAssembler.c"
    break;

  case 12: /* immediate: TOKEN_IMMEDIATE  */
#line 133 "parserAssembler.bison"
                            { (yyval.imm) = atoi(yytext+1); }
#line 1295 "parserAssembler.c"
    break;

  case 13: /* register: TOKEN_REGISTER_RAX  */
#line 136 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_RAX; }
#line 1301 "parserAssembler.c"
    break;

  case 14: /* register: TOKEN_REGISTER_RBX  */
#line 137 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_RBX; }
#line 1307 "parserAssembler.c"
    break;

  case 15: /* register: TOKEN_REGISTER_RCX  */
#line 138 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_RCX; }
#line 1313 "parserAssembler.c"
    break;

  case 16: /* register: TOKEN_REGISTER_RDX  */
#line 139 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_RDX; }
#line 1319 "parserAssembler.c"
    break;

  case 17: /* register: TOKEN_REGISTER_FIRST_FUNCTION_ARG  */
#line 140 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_FIRST_FUNCTION_ARG; }
#line 1325 "parserAssembler.c"
    break;

  case 18: /* register: TOKEN_REGISTER_SECOND_FUNCTION_ARG  */
#line 141 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_SECOND_FUNCTION_ARG; }
#line 1331 "parserAssembler.c"
    break;

  case 19: /* register: TOKEN_REGISTER_STACK_POINTER  */
#line 142 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_STACK_POINTER; }
#line 1337 "parserAssembler.c"
    break;

  case 20: /* register: TOKEN_REGISTER_FRAME_POINTER  */
#line 143 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_FRAME_POINTER; }
#line 1343 "parserAssembler.c"
    break;

  case 21: /* register: TOKEN_REGISTER_8  */
#line 144 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_R8; }
#line 1349 "parserAssembler.c"
    break;

  case 22: /* register: TOKEN_REGISTER_9  */
#line 145 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_R9; }
#line 1355 "parserAssembler.c"
    break;

  case 23: /* register: TOKEN_REGISTER_10  */
#line 146 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_R10; }
#line 1361 "parserAssembler.c"
    break;

  case 24: /* register: TOKEN_REGISTER_11  */
#line 147 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_R11; }
#line 1367 "parserAssembler.c"
    break;

  case 25: /* register: TOKEN_REGISTER_12  */
#line 148 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_R12; }
#line 1373 "parserAssembler.c"
    break;

  case 26: /* register: TOKEN_REGISTER_13  */
#line 149 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_R13; }
#line 1379 "parserAssembler.c"
    break;

  case 27: /* register: TOKEN_REGISTER_14  */
#line 150 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_R14; }
#line 1385 "parserAssembler.c"
    break;

  case 28: /* register: TOKEN_REGISTER_15  */
#line 151 "parserAssembler.bison"
                                               { (yyval.reg_num) = OP_R15; }
#line 1391 "parserAssembler.c"
    break;

  case 29: /* instruction_2_operand: TOKEN_INSTR_MOVQ  */
#line 154 "parserAssembler.bison"
                                          { (yyval.command) = OP_INSTR_MOVQ; }
#line 1397 "parserAssembler.c"
    break;

  case 30: /* instruction_2_operand: TOKEN_INSTR_LEAQ  */
#line 155 "parserAssembler.bison"
                                          { (yyval.command) = OP_INSTR_LEAQ; }
#line 1403 "parserAssembler.c"
    break;

  case 31: /* instruction_2_operand: TOKEN_INSTR_ADDQ  */
#line 156 "parserAssembler.bison"
                                          { (yyval.command) = OP_INSTR_ADDQ; }
#line 1409 "parserAssembler.c"
    break;

  case 32: /* instruction_2_operand: TOKEN_INSTR_SUBQ  */
#line 157 "parserAssembler.bison"
                                          { (yyval.command) = OP_INSTR_SUBQ; }
#line 1415 "parserAssembler.c"
    break;

  case 33: /* instruction_2_operand: TOKEN_INSTR_CMPQ  */
#line 158 "parserAssembler.bison"
                                          { (yyval.command) = OP_INSTR_CMPQ; }
#line 1421 "parserAssembler.c"
    break;

  case 34: /* instruction_1_operand: TOKEN_INSTR_NEGQ  */
#line 161 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_NEGQ; }
#line 1427 "parserAssembler.c"
    break;

  case 35: /* instruction_1_operand: TOKEN_INSTR_IMULQ  */
#line 162 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_IMULQ; }
#line 1433 "parserAssembler.c"
    break;

  case 36: /* instruction_1_operand: TOKEN_INSTR_IDIVQ  */
#line 163 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_IDIVQ; }
#line 1439 "parserAssembler.c"
    break;

  case 37: /* instruction_1_operand: TOKEN_INSTR_INCQ  */
#line 164 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_INCQ; }
#line 1445 "parserAssembler.c"
    break;

  case 38: /* instruction_1_operand: TOKEN_INSTR_DECQ  */
#line 165 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_DECQ; }
#line 1451 "parserAssembler.c"
    break;

  case 39: /* instruction_1_operand: TOKEN_INSTR_CALL  */
#line 166 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_CALL; }
#line 1457 "parserAssembler.c"
    break;

  case 40: /* instruction_1_operand: TOKEN_INSTR_JE  */
#line 167 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_JE; }
#line 1463 "parserAssembler.c"
    break;

  case 41: /* instruction_1_operand: TOKEN_INSTR_JNE  */
#line 168 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_JNE; }
#line 1469 "parserAssembler.c"
    break;

  case 42: /* instruction_1_operand: TOKEN_INSTR_JL  */
#line 169 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_JL; }
#line 1475 "parserAssembler.c"
    break;

  case 43: /* instruction_1_operand: TOKEN_INSTR_JLE  */
#line 170 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_JLE; }
#line 1481 "parserAssembler.c"
    break;

  case 44: /* instruction_1_operand: TOKEN_INSTR_JG  */
#line 171 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_JG; }
#line 1487 "parserAssembler.c"
    break;

  case 45: /* instruction_1_operand: TOKEN_INSTR_JGE  */
#line 172 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_JGE; }
#line 1493 "parserAssembler.c"
    break;

  case 46: /* instruction_1_operand: TOKEN_INSTR_JMP  */
#line 173 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_JMP; }
#line 1499 "parserAssembler.c"
    break;

  case 47: /* instruction_1_operand: TOKEN_INSTR_PUSHQ  */
#line 174 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_PUSHQ; }
#line 1505 "parserAssembler.c"
    break;

  case 48: /* instruction_1_operand: TOKEN_INSTR_POPQ  */
#line 175 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_POPQ; }
#line 1511 "parserAssembler.c"
    break;

  case 49: /* instruction_0_operand: TOKEN_INSTR_CQO  */
#line 178 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_CQO; }
#line 1517 "parserAssembler.c"
    break;

  case 50: /* instruction_0_operand: TOKEN_INSTR_RET  */
#line 179 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_RET; }
#line 1523 "parserAssembler.c"
    break;

  case 51: /* instruction_0_operand: TOKEN_INSTR_NOP  */
#line 180 "parserAssembler.bison"
                                           { (yyval.command) = OP_INSTR_NOP; }
#line 1529 "parserAssembler.c"
    break;

  case 52: /* instruction: instruction_2_operand operand TOKEN_OP_COMMA operand  */
#line 183 "parserAssembler.bison"
                                                                   { (yyval.instr) = instr_create((yyvsp[-3].command), (yyvsp[-2].operand), (yyvsp[0].operand)); }
#line 1535 "parserAssembler.c"
    break;

  case 53: /* instruction: instruction_1_operand operand  */
#line 184 "parserAssembler.bison"
                                                                   { (yyval.instr) = instr_create((yyvsp[-1].command), (yyvsp[0].operand), 0); }
#line 1541 "parserAssembler.c"
    break;

  case 54: /* instruction: instruction_0_operand  */
#line 185 "parserAssembler.bison"
                                                                   { (yyval.instr) = instr_create((yyvsp[0].command), 0, 0); }
#line 1547 "parserAssembler.c"
    break;

  case 55: /* line: instruction TOKEN_OP_NEWLINE  */
#line 188 "parserAssembler.bison"
                                              { (yyval.line) = line_create(ASM_LINE_INSTRUCTION, 0, 0, (yyvsp[-1].instr)); }
#line 1553 "parserAssembler.c"
    break;

  case 56: /* line: label TOKEN_OP_NEWLINE  */
#line 189 "parserAssembler.bison"
                                              { (yyval.line) = (yyvsp[-1].line); }
#line 1559 "parserAssembler.c"
    break;

  case 57: /* line: directive TOKEN_OP_NEWLINE  */
#line 190 "parserAssembler.bison"
                                              { (yyval.line) = line_create(ASM_LINE_DIRECTIVE, 0, (yyvsp[-1].directive), 0); }
#line 1565 "parserAssembler.c"
    break;

  case 58: /* line: TOKEN_OP_NEWLINE  */
#line 191 "parserAssembler.bison"
                                              { (yyval.line) = 0; }
#line 1571 "parserAssembler.c"
    break;

  case 59: /* directive: TOKEN_DIRECTIVE_FILE literal_string  */
#line 194 "parserAssembler.bison"
                                                                              { (yyval.directive) = directive_create(DIR_FILE, (yyvsp[0].name), 0, 0); }
#line 1577 "parserAssembler.c"
    break;

  case 60: /* directive: TOKEN_DIRECTIVE_SECTION TOKEN_DIRECTIVE_GNU_STACK TOKEN_OP_COMMA literal_string TOKEN_OP_COMMA TOKEN_DIRECTIVE_PROGBITS  */
#line 196 "parserAssembler.bison"
                                                                              { (yyval.directive) = directive_create(DIR_SECTION, (yyvsp[-2].name), 0, 0); }
#line 1583 "parserAssembler.c"
    break;

  case 61: /* directive: TOKEN_DIRECTIVE_DATA  */
#line 197 "parserAssembler.bison"
                                                                              { (yyval.directive) = directive_create(DIR_DATA, 0, 0, 0); }
#line 1589 "parserAssembler.c"
    break;

  case 62: /* directive: TOKEN_DIRECTIVE_GLOBAL identifier  */
#line 198 "parserAssembler.bison"
                                                                              { (yyval.directive) = directive_create(DIR_GLOBAL, (yyvsp[0].name), 0, 0); }
#line 1595 "parserAssembler.c"
    break;

  case 63: /* directive: TOKEN_DIRECTIVE_TEXT  */
#line 199 "parserAssembler.bison"
                                                                              { (yyval.directive) = directive_create(DIR_TEXT, 0, 0, 0); }
#line 1601 "parserAssembler.c"
    break;

  case 64: /* directive: TOKEN_DIRECTIVE_STRING literal_string  */
#line 200 "parserAssembler.bison"
                                                                              { (yyval.directive) = directive_create(DIR_STRING, 0, (yyvsp[0].name), 0); }
#line 1607 "parserAssembler.c"
    break;

  case 65: /* directive: TOKEN_DIRECTIVE_QUAD literal_digit  */
#line 201 "parserAssembler.bison"
                                                                              { (yyval.directive) = directive_create(DIR_QUAD, 0, 0, (yyvsp[0].imm)); }
#line 1613 "parserAssembler.c"
    break;

  case 66: /* line_list: line line_list  */
#line 204 "parserAssembler.bison"
                               { (yyval.line) = (yyvsp[-1].line); (yyvsp[-1].line)->next = (yyvsp[0].line); }
#line 1619 "parserAssembler.c"
    break;

  case 67: /* line_list: line  */
#line 205 "parserAssembler.bison"
                               { (yyval.line) = (yyvsp[0].line); }
#line 1625 "parserAssembler.c"
    break;

  case 68: /* literal_string: TOKEN_LITERAL_STRING  */
#line 208 "parserAssembler.bison"
                                       { (yyval.name) = strdup(beautifyString(yytext)); }
#line 1631 "parserAssembler.c"
    break;

  case 69: /* literal_digit: TOKEN_DIGIT  */
#line 211 "parserAssembler.bison"
                            { (yyval.imm) = atoi(yytext); }
#line 1637 "parserAssembler.c"
    break;


#line 1641 "parserAssembler.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 214 "parserAssembler.bison"


int yyerror( char *str ) {
   printf("Parse Error: %s\n",str);
   return 0;
}
