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




/* First part of user prologue.  */
#line 1 "c.y"

#include <cstdio>
#include <iostream>

#include "ast.hpp"
using namespace std;

ASTNode* program_ast = NULL;

// stuff from flex that bison needs to know about:
extern "C" FILE *yyin;
extern "C" char yytext[];

extern "C" int yylex();
 
int yyparse();
void yyerror(const char *s);
void todo(int);

#line 91 "c.tab.cpp"

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

#include "c.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_I_CONSTANT = 4,                 /* I_CONSTANT  */
  YYSYMBOL_F_CONSTANT = 5,                 /* F_CONSTANT  */
  YYSYMBOL_STRING_LITERAL = 6,             /* STRING_LITERAL  */
  YYSYMBOL_FUNC_NAME = 7,                  /* FUNC_NAME  */
  YYSYMBOL_SIZEOF = 8,                     /* SIZEOF  */
  YYSYMBOL_PTR_OP = 9,                     /* PTR_OP  */
  YYSYMBOL_INC_OP = 10,                    /* INC_OP  */
  YYSYMBOL_DEC_OP = 11,                    /* DEC_OP  */
  YYSYMBOL_LEFT_OP = 12,                   /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 13,                  /* RIGHT_OP  */
  YYSYMBOL_LE_OP = 14,                     /* LE_OP  */
  YYSYMBOL_GE_OP = 15,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 16,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 17,                     /* NE_OP  */
  YYSYMBOL_AND_OP = 18,                    /* AND_OP  */
  YYSYMBOL_OR_OP = 19,                     /* OR_OP  */
  YYSYMBOL_MUL_ASSIGN = 20,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 21,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 22,                /* MOD_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 23,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 24,                /* SUB_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 25,               /* LEFT_ASSIGN  */
  YYSYMBOL_RIGHT_ASSIGN = 26,              /* RIGHT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 27,                /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 28,                /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 29,                 /* OR_ASSIGN  */
  YYSYMBOL_TYPEDEF_NAME = 30,              /* TYPEDEF_NAME  */
  YYSYMBOL_ENUMERATION_CONSTANT = 31,      /* ENUMERATION_CONSTANT  */
  YYSYMBOL_TYPEDEF = 32,                   /* TYPEDEF  */
  YYSYMBOL_EXTERN = 33,                    /* EXTERN  */
  YYSYMBOL_STATIC = 34,                    /* STATIC  */
  YYSYMBOL_AUTO = 35,                      /* AUTO  */
  YYSYMBOL_REGISTER = 36,                  /* REGISTER  */
  YYSYMBOL_INLINE = 37,                    /* INLINE  */
  YYSYMBOL_CONST = 38,                     /* CONST  */
  YYSYMBOL_RESTRICT = 39,                  /* RESTRICT  */
  YYSYMBOL_VOLATILE = 40,                  /* VOLATILE  */
  YYSYMBOL_BOOL = 41,                      /* BOOL  */
  YYSYMBOL_CHAR = 42,                      /* CHAR  */
  YYSYMBOL_SHORT = 43,                     /* SHORT  */
  YYSYMBOL_INT = 44,                       /* INT  */
  YYSYMBOL_LONG = 45,                      /* LONG  */
  YYSYMBOL_SIGNED = 46,                    /* SIGNED  */
  YYSYMBOL_UNSIGNED = 47,                  /* UNSIGNED  */
  YYSYMBOL_FLOAT = 48,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 49,                    /* DOUBLE  */
  YYSYMBOL_VOID = 50,                      /* VOID  */
  YYSYMBOL_COMPLEX = 51,                   /* COMPLEX  */
  YYSYMBOL_IMAGINARY = 52,                 /* IMAGINARY  */
  YYSYMBOL_STRUCT = 53,                    /* STRUCT  */
  YYSYMBOL_UNION = 54,                     /* UNION  */
  YYSYMBOL_ENUM = 55,                      /* ENUM  */
  YYSYMBOL_ELLIPSIS = 56,                  /* ELLIPSIS  */
  YYSYMBOL_CASE = 57,                      /* CASE  */
  YYSYMBOL_DEFAULT = 58,                   /* DEFAULT  */
  YYSYMBOL_IF = 59,                        /* IF  */
  YYSYMBOL_ELSE = 60,                      /* ELSE  */
  YYSYMBOL_SWITCH = 61,                    /* SWITCH  */
  YYSYMBOL_WHILE = 62,                     /* WHILE  */
  YYSYMBOL_DO = 63,                        /* DO  */
  YYSYMBOL_FOR = 64,                       /* FOR  */
  YYSYMBOL_GOTO = 65,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 66,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 67,                     /* BREAK  */
  YYSYMBOL_RETURN = 68,                    /* RETURN  */
  YYSYMBOL_ALIGNAS = 69,                   /* ALIGNAS  */
  YYSYMBOL_ALIGNOF = 70,                   /* ALIGNOF  */
  YYSYMBOL_ATOMIC = 71,                    /* ATOMIC  */
  YYSYMBOL_GENERIC = 72,                   /* GENERIC  */
  YYSYMBOL_NORETURN = 73,                  /* NORETURN  */
  YYSYMBOL_STATIC_ASSERT = 74,             /* STATIC_ASSERT  */
  YYSYMBOL_THREAD_LOCAL = 75,              /* THREAD_LOCAL  */
  YYSYMBOL_76_ = 76,                       /* '('  */
  YYSYMBOL_77_ = 77,                       /* ')'  */
  YYSYMBOL_78_ = 78,                       /* '['  */
  YYSYMBOL_79_ = 79,                       /* ']'  */
  YYSYMBOL_80_ = 80,                       /* '.'  */
  YYSYMBOL_81_ = 81,                       /* '{'  */
  YYSYMBOL_82_ = 82,                       /* '}'  */
  YYSYMBOL_83_ = 83,                       /* ','  */
  YYSYMBOL_84_ = 84,                       /* '&'  */
  YYSYMBOL_85_ = 85,                       /* '*'  */
  YYSYMBOL_86_ = 86,                       /* '+'  */
  YYSYMBOL_87_ = 87,                       /* '-'  */
  YYSYMBOL_88_ = 88,                       /* '~'  */
  YYSYMBOL_89_ = 89,                       /* '!'  */
  YYSYMBOL_90_ = 90,                       /* '/'  */
  YYSYMBOL_91_ = 91,                       /* '%'  */
  YYSYMBOL_92_ = 92,                       /* '<'  */
  YYSYMBOL_93_ = 93,                       /* '>'  */
  YYSYMBOL_94_ = 94,                       /* '^'  */
  YYSYMBOL_95_ = 95,                       /* '|'  */
  YYSYMBOL_96_ = 96,                       /* '?'  */
  YYSYMBOL_97_ = 97,                       /* ':'  */
  YYSYMBOL_98_ = 98,                       /* '='  */
  YYSYMBOL_99_ = 99,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 100,                 /* $accept  */
  YYSYMBOL_primary_expression = 101,       /* primary_expression  */
  YYSYMBOL_constant = 102,                 /* constant  */
  YYSYMBOL_string = 103,                   /* string  */
  YYSYMBOL_postfix_expression = 104,       /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 105, /* argument_expression_list  */
  YYSYMBOL_unary_expression = 106,         /* unary_expression  */
  YYSYMBOL_unary_operator = 107,           /* unary_operator  */
  YYSYMBOL_cast_expression = 108,          /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 109, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 110,      /* additive_expression  */
  YYSYMBOL_shift_expression = 111,         /* shift_expression  */
  YYSYMBOL_relational_expression = 112,    /* relational_expression  */
  YYSYMBOL_equality_expression = 113,      /* equality_expression  */
  YYSYMBOL_and_expression = 114,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 115,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 116,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 117,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 118,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 119,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 120,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 121,      /* assignment_operator  */
  YYSYMBOL_expression = 122,               /* expression  */
  YYSYMBOL_constant_expression = 123,      /* constant_expression  */
  YYSYMBOL_declaration = 124,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 125,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 126,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 127,          /* init_declarator  */
  YYSYMBOL_type_specifier = 128,           /* type_specifier  */
  YYSYMBOL_specifier_qualifier_list = 129, /* specifier_qualifier_list  */
  YYSYMBOL_declarator = 130,               /* declarator  */
  YYSYMBOL_direct_declarator = 131,        /* direct_declarator  */
  YYSYMBOL_pointer = 132,                  /* pointer  */
  YYSYMBOL_parameter_type_list = 133,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 134,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 135,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 136,          /* identifier_list  */
  YYSYMBOL_type_name = 137,                /* type_name  */
  YYSYMBOL_abstract_declarator = 138,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 139, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 140,              /* initializer  */
  YYSYMBOL_initializer_list = 141,         /* initializer_list  */
  YYSYMBOL_designation = 142,              /* designation  */
  YYSYMBOL_designator_list = 143,          /* designator_list  */
  YYSYMBOL_designator = 144,               /* designator  */
  YYSYMBOL_statement = 145,                /* statement  */
  YYSYMBOL_labeled_statement = 146,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 147,       /* compound_statement  */
  YYSYMBOL_block_item_list = 148,          /* block_item_list  */
  YYSYMBOL_block_item = 149,               /* block_item  */
  YYSYMBOL_expression_statement = 150,     /* expression_statement  */
  YYSYMBOL_selection_statement = 151,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 152,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 153,           /* jump_statement  */
  YYSYMBOL_translation_unit = 154,         /* translation_unit  */
  YYSYMBOL_external_declaration = 155,     /* external_declaration  */
  YYSYMBOL_function_definition = 156,      /* function_definition  */
  YYSYMBOL_declaration_list = 157          /* declaration_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  30
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1347

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  100
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  194
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  335

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   330


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
       2,     2,     2,    89,     2,     2,     2,    91,    84,     2,
      76,    77,    85,    86,    83,    87,    80,    90,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    97,    99,
      92,    98,    93,    96,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    78,     2,    79,    94,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    81,    95,    82,    88,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   156,   156,   157,   158,   159,   163,   164,   168,   169,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     186,   187,   191,   192,   193,   194,   195,   196,   197,   201,
     202,   203,   204,   205,   206,   210,   211,   215,   216,   217,
     218,   222,   223,   224,   228,   229,   230,   234,   235,   236,
     237,   238,   242,   243,   244,   248,   249,   253,   254,   258,
     259,   263,   264,   268,   269,   273,   274,   278,   279,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     297,   298,   302,   306,   307,   311,   312,   316,   317,   321,
     322,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   342,   343,   347,   348,   352,   353,
     354,   355,   356,   357,   358,   359,   363,   364,   368,   369,
     373,   374,   378,   379,   380,   384,   385,   389,   390,   394,
     395,   396,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   415,   416,   417,   421,   422,   423,
     424,   428,   432,   433,   437,   438,   442,   443,   444,   445,
     446,   447,   451,   452,   453,   457,   458,   462,   463,   467,
     468,   472,   473,   477,   478,   479,   483,   484,   485,   486,
     487,   488,   492,   493,   494,   495,   496,   500,   505,   513,
     514,   518,   519,   523,   524
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
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "I_CONSTANT", "F_CONSTANT", "STRING_LITERAL", "FUNC_NAME", "SIZEOF",
  "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP",
  "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN",
  "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "TYPEDEF_NAME",
  "ENUMERATION_CONSTANT", "TYPEDEF", "EXTERN", "STATIC", "AUTO",
  "REGISTER", "INLINE", "CONST", "RESTRICT", "VOLATILE", "BOOL", "CHAR",
  "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE", "VOID",
  "COMPLEX", "IMAGINARY", "STRUCT", "UNION", "ENUM", "ELLIPSIS", "CASE",
  "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE", "DO", "FOR", "GOTO",
  "CONTINUE", "BREAK", "RETURN", "ALIGNAS", "ALIGNOF", "ATOMIC", "GENERIC",
  "NORETURN", "STATIC_ASSERT", "THREAD_LOCAL", "'('", "')'", "'['", "']'",
  "'.'", "'{'", "'}'", "','", "'&'", "'*'", "'+'", "'-'", "'~'", "'!'",
  "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'", "':'", "'='", "';'",
  "$accept", "primary_expression", "constant", "string",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "unary_operator", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "declaration_specifiers",
  "init_declarator_list", "init_declarator", "type_specifier",
  "specifier_qualifier_list", "declarator", "direct_declarator", "pointer",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "type_name", "abstract_declarator",
  "direct_abstract_declarator", "initializer", "initializer_list",
  "designation", "designator_list", "designator", "statement",
  "labeled_statement", "compound_statement", "block_item_list",
  "block_item", "expression_statement", "selection_statement",
  "iteration_statement", "jump_statement", "translation_unit",
  "external_declaration", "function_definition", "declaration_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-227)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1295,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,
    -227,  -227,  -227,  -227,  -227,    12,  1295,  1203,  -227,  -227,
    -227,    13,   -71,  -227,   -49,  -227,  1127,    47,    24,  -227,
    -227,  -227,   -55,  -227,    13,  -227,   277,   736,  -227,    12,
    -227,  1226,  1104,   773,    47,  -227,  -227,   -66,   -24,  -227,
    -227,  -227,  -227,   967,  1017,  1017,  1054,   -12,   -27,    31,
      36,   501,    64,    58,    86,    88,    32,   129,   599,  -227,
    -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,
     141,   169,  1054,  -227,   117,   114,   203,    41,   234,   153,
     119,   130,   225,    -9,  -227,  -227,   -42,  -227,  -227,  -227,
    -227,   364,  -227,  -227,  -227,  -227,  -227,  -227,   686,  -227,
    -227,  -227,  -227,  -227,  -227,    28,   180,   177,  -227,    -1,
    -227,   193,   196,   501,   599,  -227,   599,  -227,  -227,  -227,
    -227,   179,   501,  1054,  1054,  1054,   216,   451,   187,  -227,
    -227,  -227,    16,  1295,    53,  1295,    78,   213,   288,  -227,
    -227,   793,  1054,   291,  -227,  -227,  -227,  -227,  -227,  -227,
    -227,  -227,  -227,  -227,  -227,  1054,  -227,  1054,  1054,  1054,
    1054,  1054,  1054,  1054,  1054,  1054,  1054,  1054,  1054,  1054,
    1054,  1054,  1054,  1054,  1054,  1054,  1054,  -227,  -227,  -227,
    1054,   292,  -227,   171,   736,   -20,  -227,  1033,    59,  -227,
       1,  -227,    63,  -227,  1272,  -227,   293,  -227,  -227,  -227,
     220,   221,   501,  -227,    76,   126,   127,   223,   538,   538,
    -227,  -227,   224,  -227,  -227,  1150,    84,  -227,   823,  -227,
    -227,   135,  -227,   -11,  -227,  -227,  -227,  -227,  -227,   117,
     117,   114,   114,   203,   203,   203,   203,    41,    41,   234,
     153,   119,   130,   225,    27,  -227,   226,  -227,  -227,   628,
    -227,  -227,  -227,  -227,   227,   229,  1054,  -227,   230,   231,
      63,  1249,   880,  -227,  -227,  -227,   219,   219,  -227,   501,
     501,   501,  1054,   910,   930,  -227,   686,  -227,  -227,  1054,
    -227,  1054,  -227,  -227,  -227,   736,  -227,  -227,   232,  -227,
    -227,  -227,   235,  -227,   236,   237,   242,  -227,  -227,   137,
     501,   147,   501,   151,   173,  -227,  -227,  -227,  -227,  -227,
    -227,  -227,   501,   204,  -227,   501,  -227,   501,  -227,   649,
    -227,  -227,  -227,  -227,  -227
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   103,   100,    92,    93,    94,    96,    98,    99,    95,
      97,    91,   101,   102,   190,     0,    86,     0,   187,   189,
     108,     0,   117,    83,     0,    87,    90,   107,     0,    85,
       1,   188,     0,   116,     0,    84,     0,     0,   193,     0,
     192,     0,     0,     0,   106,   109,    88,    90,     2,     6,
       7,     8,     9,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   165,
      29,    30,    31,    32,    33,    34,   171,    10,     3,     4,
      22,    35,     0,    37,    41,    44,    47,    52,    55,    57,
      59,    61,    63,    65,    67,    80,     0,   169,   170,   156,
     157,     0,   167,   158,   159,   160,   161,     2,     0,   146,
      89,   194,   191,   125,   114,   124,     0,   119,   120,     0,
     110,    30,     0,     0,     0,    26,     0,    23,    24,    35,
      82,     0,     0,     0,     0,     0,     0,     0,     0,   183,
     184,   185,     0,     0,     0,   105,   128,     0,     0,    16,
      17,     0,     0,     0,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    69,     0,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   172,   166,   168,
       0,     0,   148,     0,     0,     0,   152,     0,     0,   122,
     130,   123,   131,   113,     0,   115,     0,   111,   112,   162,
       0,     0,     0,   164,     0,     0,     0,     0,     0,     0,
     182,   186,     0,     5,   104,     0,   130,   127,     0,    15,
      12,     0,    20,     0,    14,    68,    38,    39,    40,    42,
      43,    45,    46,    50,    51,    48,    49,    53,    54,    56,
      58,    60,    62,    64,     0,    81,     0,   155,   144,     0,
     147,   151,   153,   140,     0,     0,     0,   133,    30,     0,
     129,     0,     0,   118,   121,   126,    27,     0,   163,     0,
       0,     0,     0,     0,     0,    28,     0,    36,    13,     0,
      11,     0,   154,   145,   150,     0,   141,   132,     0,   134,
     136,   142,     0,   137,    30,     0,   174,   175,   176,     0,
       0,     0,     0,     0,     0,    21,    66,   149,   135,   143,
     138,   139,     0,     0,   180,     0,   178,     0,    18,     0,
     173,   177,   181,   179,    19
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -227,  -227,  -227,  -227,  -227,  -227,    -2,  -227,   -73,    95,
      96,    71,    92,   128,   132,   148,   131,   133,  -227,   -53,
     -37,  -227,   -43,   142,   -15,     2,  -227,   297,   118,   188,
     -10,   -16,   -14,   -35,  -227,   144,  -227,   -96,   -98,  -180,
     -36,    51,  -226,  -227,   154,   -48,  -227,    33,  -227,   245,
     -92,  -227,  -227,  -227,  -227,   333,  -227,  -227
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    77,    78,    79,    80,   231,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,   165,    96,   131,    14,    39,    24,    25,    16,   146,
      32,    27,    28,   264,   117,   118,   119,   147,   265,   202,
     192,   193,   194,   195,   196,    98,    99,   100,   101,   102,
     103,   104,   105,   106,    17,    18,    19,    41
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     109,   110,    15,   130,    20,    26,   122,   116,    33,   166,
     184,    38,    44,   136,    22,    20,    20,   201,    29,    15,
     270,    97,    45,   142,    47,   144,   111,    20,   210,    47,
     211,    20,    37,   295,    34,   107,    49,    50,    51,    52,
      53,   186,    54,    55,   115,   219,   270,   222,   227,   133,
      35,   125,   127,   128,   129,   174,   175,   187,   190,    40,
     191,   138,   107,    49,    50,    51,    52,    53,   290,    54,
      55,   109,   186,   123,   112,   209,   205,   197,   261,   198,
     129,   144,   206,   144,   213,   132,    97,   185,    21,    21,
     214,   215,   216,   266,   236,   237,   238,    22,    22,   186,
      21,   200,    67,   295,   197,   199,   198,   134,    68,   233,
     186,    23,   135,    22,   232,   221,    70,    71,    72,    73,
      74,    75,   218,    42,   291,    43,   283,   284,   235,    67,
     223,   141,   226,   176,   177,    68,   186,   130,   267,   271,
     137,   272,   254,    70,   268,    72,    73,    74,    75,   255,
     148,   149,   150,   279,   225,   287,   198,   109,   260,   186,
     225,   269,   198,    22,   278,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   200,    44,   139,   145,   140,   129,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   115,
     170,   171,   167,   280,   281,   143,   115,   168,   169,   186,
     186,   226,   288,   181,   323,   172,   173,   151,   289,   152,
     186,   153,   109,   294,   325,   182,   129,   115,   327,   298,
     186,   306,   307,   308,   186,   305,   302,   180,   316,   309,
     311,   313,   145,   183,   145,   243,   244,   245,   246,   109,
     178,   179,   315,   258,   259,   328,   329,   203,   109,   317,
     204,   145,   324,   145,   326,   239,   240,   164,   241,   242,
     247,   248,   207,   115,   330,   208,   212,   332,   217,   333,
      48,    49,    50,    51,    52,    53,   220,    54,    55,   129,
     228,   229,   109,   294,   234,   257,   275,   276,   277,   282,
     286,   285,   322,   331,   296,   292,   297,     1,   249,   299,
     300,   318,   319,   250,   252,   320,   321,   253,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
     251,    46,   256,   224,    56,    57,    58,   314,    59,    60,
      61,    62,    63,    64,    65,    66,   189,    67,   274,   262,
      31,     0,     0,    68,     0,     0,     0,     0,    36,    69,
       0,    70,    71,    72,    73,    74,    75,    48,    49,    50,
      51,    52,    53,     0,    54,    55,    76,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,     0,
       0,    56,    57,    58,     0,    59,    60,    61,    62,    63,
      64,    65,    66,     0,    67,     0,     0,     0,     0,     0,
      68,     0,     0,     0,     0,    36,   188,     0,    70,    71,
      72,    73,    74,    75,   107,    49,    50,    51,    52,    53,
       0,    54,    55,    76,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    48,    49,    50,    51,    52,    53,
       0,    54,    55,     0,     0,     0,     0,     0,     0,     0,
       0,    67,     0,     0,     0,     0,     0,    68,     0,     0,
       0,     0,     0,     0,     0,    70,    71,    72,    73,    74,
      75,   107,    49,    50,    51,    52,    53,     0,    54,    55,
      76,     0,     0,     0,     0,     0,     0,     0,    56,    57,
      58,     0,    59,    60,    61,    62,    63,    64,    65,    66,
       0,    67,     0,     0,     0,     0,     0,    68,     0,     0,
       0,     0,    36,     0,     0,    70,    71,    72,    73,    74,
      75,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      76,     0,   107,    49,    50,    51,    52,    53,    67,    54,
      55,     0,     0,     0,    68,     0,     0,     0,     0,     0,
       0,     0,    70,    71,    72,    73,    74,    75,     0,     1,
       0,   107,    49,    50,    51,    52,    53,    76,    54,    55,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,   107,    49,    50,    51,    52,    53,     0,    54,
      55,     0,     0,     0,     0,     0,     0,     0,     0,    67,
       0,     0,     0,     0,     0,    68,     0,     0,     0,     0,
       0,     0,     0,    70,    71,    72,    73,    74,    75,   107,
      49,    50,    51,    52,    53,     0,    54,    55,    67,     0,
       0,     0,     0,     0,    68,     0,   190,     0,   191,   108,
     293,     0,    70,    71,    72,    73,    74,    75,     0,    67,
       0,     0,     0,     0,     0,    68,     0,   190,     0,   191,
     108,   334,     0,    70,    71,    72,    73,    74,    75,   107,
      49,    50,    51,    52,    53,     0,    54,    55,     0,     0,
       0,     0,     0,     0,     0,     0,    67,     0,     0,     0,
       0,     0,    68,     0,   190,     0,   191,   108,     0,     0,
      70,    71,    72,    73,    74,    75,   107,    49,    50,    51,
      52,    53,     0,    54,    55,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   107,    49,    50,    51,
      52,    53,     0,    54,    55,     0,    67,     0,     0,     0,
       0,     0,    68,     0,     0,     0,     0,   108,     0,     0,
      70,    71,    72,    73,    74,    75,   107,    49,    50,    51,
      52,    53,     0,    54,    55,     0,     0,     0,     0,     0,
       0,     0,     0,    67,     0,     0,     0,     0,     0,    68,
       0,     0,   120,     0,     0,     0,     0,    70,   121,    72,
      73,    74,    75,    67,     0,     0,     0,     0,     0,    68,
     230,     0,     0,     0,     0,     0,     0,    70,    71,    72,
      73,    74,    75,   107,    49,    50,    51,    52,    53,     0,
      54,    55,     0,    67,     0,     0,     0,     0,     0,    68,
       0,     0,     0,     0,   286,     0,     0,    70,    71,    72,
      73,    74,    75,   107,    49,    50,    51,    52,    53,     0,
      54,    55,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   107,    49,    50,    51,    52,    53,     0,
      54,    55,     0,     0,     0,     0,     0,     0,     0,     0,
      67,     0,     0,     0,     0,     0,    68,     0,     0,   303,
       0,     0,     0,     0,    70,   304,    72,    73,    74,    75,
     107,    49,    50,    51,    52,    53,     0,    54,    55,     0,
      67,     0,     0,     0,     0,     0,    68,   310,     0,     0,
       0,     0,     0,     0,    70,    71,    72,    73,    74,    75,
      67,     0,     0,     0,     0,     0,    68,   312,     0,     0,
       0,     0,     0,     0,    70,    71,    72,    73,    74,    75,
     107,    49,    50,    51,    52,    53,     0,    54,    55,     0,
       0,     0,     0,     0,     0,     0,    20,    67,     0,     0,
       0,     0,     0,   124,     0,     0,     0,     0,     0,     0,
       0,    70,    71,    72,    73,    74,    75,   107,    49,    50,
      51,    52,    53,     1,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     0,    67,     0,     0,
       0,     0,     0,   126,     0,     0,     0,     0,     0,     0,
       0,    70,    71,    72,    73,    74,    75,   113,     0,   197,
     263,   198,     0,     0,     0,     0,     0,     0,    22,     0,
       0,     0,     0,     0,    67,     0,     0,     0,     0,     0,
      68,     0,     0,     0,     1,     0,     0,     0,    70,    71,
      72,    73,    74,    75,     0,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       1,   114,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    30,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,   225,   263,   198,     0,
       0,     0,     0,     1,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     1,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     1,     0,     0,     0,     0,    36,     0,     0,
       0,     0,     0,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     1,   301,     0,   273,     0,
       0,     0,     0,     0,     0,     0,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13
};

static const yytype_int16 yycheck[] =
{
      37,    37,     0,    56,     3,    15,    43,    42,    22,    82,
      19,    26,    28,    61,    85,     3,     3,   115,    16,    17,
     200,    36,    77,    66,    34,    68,    41,     3,   124,    39,
     126,     3,    98,   259,    83,     3,     4,     5,     6,     7,
       8,    83,    10,    11,    42,   137,   226,   143,   146,    76,
      99,    53,    54,    55,    56,    14,    15,    99,    78,    26,
      80,     3,     3,     4,     5,     6,     7,     8,    79,    10,
      11,   108,    83,    97,    41,   123,    77,    76,    98,    78,
      82,   124,    83,   126,   132,    97,   101,    96,    76,    76,
     133,   134,   135,    34,   167,   168,   169,    85,    85,    83,
      76,   115,    70,   329,    76,   115,    78,    76,    76,   152,
      83,    99,    76,    85,   151,    99,    84,    85,    86,    87,
      88,    89,   137,    76,    97,    78,   218,   219,   165,    70,
      77,    99,   146,    92,    93,    76,    83,   190,    79,    76,
      76,    78,   185,    84,    85,    86,    87,    88,    89,   186,
       9,    10,    11,    77,    76,   228,    78,   194,   194,    83,
      76,   198,    78,    85,   212,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   197,   200,    99,    68,    99,   190,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,   197,
      86,    87,    85,    77,    77,    76,   204,    90,    91,    83,
      83,   225,    77,    94,    77,    12,    13,    76,    83,    78,
      83,    80,   259,   259,    77,    95,   228,   225,    77,   266,
      83,   279,   280,   281,    83,   272,   271,    84,   291,   282,
     283,   284,   124,    18,   126,   174,   175,   176,   177,   286,
      16,    17,   289,    82,    83,    82,    83,    77,   295,   295,
      83,   143,   310,   145,   312,   170,   171,    98,   172,   173,
     178,   179,    79,   271,   322,    79,    97,   325,    62,   327,
       3,     4,     5,     6,     7,     8,    99,    10,    11,   291,
      77,     3,   329,   329,     3,     3,     3,    77,    77,    76,
      81,    77,    60,    99,    77,    79,    77,    30,   180,    79,
      79,    79,    77,   181,   183,    79,    79,   184,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
     182,    34,   190,   145,    57,    58,    59,   286,    61,    62,
      63,    64,    65,    66,    67,    68,   101,    70,   204,   195,
      17,    -1,    -1,    76,    -1,    -1,    -1,    -1,    81,    82,
      -1,    84,    85,    86,    87,    88,    89,     3,     4,     5,
       6,     7,     8,    -1,    10,    11,    99,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,    -1,    -1,
      -1,    57,    58,    59,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    81,    82,    -1,    84,    85,
      86,    87,    88,    89,     3,     4,     5,     6,     7,     8,
      -1,    10,    11,    99,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,     3,     4,     5,     6,     7,     8,
      -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,
      89,     3,     4,     5,     6,     7,     8,    -1,    10,    11,
      99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,
      59,    -1,    61,    62,    63,    64,    65,    66,    67,    68,
      -1,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    84,    85,    86,    87,    88,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      99,    -1,     3,     4,     5,     6,     7,     8,    70,    10,
      11,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    88,    89,    -1,    30,
      -1,     3,     4,     5,     6,     7,     8,    99,    10,    11,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,     3,     4,     5,     6,     7,     8,    -1,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    86,    87,    88,    89,     3,
       4,     5,     6,     7,     8,    -1,    10,    11,    70,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    78,    -1,    80,    81,
      82,    -1,    84,    85,    86,    87,    88,    89,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    76,    -1,    78,    -1,    80,
      81,    82,    -1,    84,    85,    86,    87,    88,    89,     3,
       4,     5,     6,     7,     8,    -1,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    78,    -1,    80,    81,    -1,    -1,
      84,    85,    86,    87,    88,    89,     3,     4,     5,     6,
       7,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,    -1,    10,    11,    -1,    70,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      84,    85,    86,    87,    88,    89,     3,     4,     5,     6,
       7,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    84,    85,    86,
      87,    88,    89,    70,    -1,    -1,    -1,    -1,    -1,    76,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,
      87,    88,    89,     3,     4,     5,     6,     7,     8,    -1,
      10,    11,    -1,    70,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    -1,    81,    -1,    -1,    84,    85,    86,
      87,    88,    89,     3,     4,     5,     6,     7,     8,    -1,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,    -1,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    79,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
       3,     4,     5,     6,     7,     8,    -1,    10,    11,    -1,
      70,    -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
      70,    -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
       3,     4,     5,     6,     7,     8,    -1,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    70,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    86,    87,    88,    89,     3,     4,     5,
       6,     7,     8,    30,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    70,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    86,    87,    88,    89,     3,    -1,    76,
      77,    78,    -1,    -1,    -1,    -1,    -1,    -1,    85,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    30,    -1,    -1,    -1,    84,    85,
      86,    87,    88,    89,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      30,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,     0,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    76,    77,    78,    -1,
      -1,    -1,    -1,    30,    -1,    85,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    30,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    -1,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    30,    77,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,   124,   125,   128,   154,   155,   156,
       3,    76,    85,    99,   126,   127,   130,   131,   132,   125,
       0,   155,   130,   132,    83,    99,    81,    98,   124,   125,
     147,   157,    76,    78,   131,    77,   127,   130,     3,     4,
       5,     6,     7,     8,    10,    11,    57,    58,    59,    61,
      62,    63,    64,    65,    66,    67,    68,    70,    76,    82,
      84,    85,    86,    87,    88,    89,    99,   101,   102,   103,
     104,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   122,   124,   145,   146,
     147,   148,   149,   150,   151,   152,   153,     3,    81,   120,
     140,   124,   147,     3,    77,   125,   133,   134,   135,   136,
      79,    85,   120,    97,    76,   106,    76,   106,   106,   106,
     119,   123,    97,    76,    76,    76,   145,    76,     3,    99,
      99,    99,   122,    76,   122,   128,   129,   137,     9,    10,
      11,    76,    78,    80,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    98,   121,   108,    85,    90,    91,
      86,    87,    12,    13,    14,    15,    92,    93,    16,    17,
      84,    94,    95,    18,    19,    96,    83,    99,    82,   149,
      78,    80,   140,   141,   142,   143,   144,    76,    78,   130,
     132,   138,   139,    77,    83,    77,    83,    79,    79,   145,
     137,   137,    97,   145,   122,   122,   122,    62,   124,   150,
      99,    99,   137,    77,   129,    76,   132,   138,    77,     3,
      77,   105,   120,   122,     3,   120,   108,   108,   108,   109,
     109,   110,   110,   111,   111,   111,   111,   112,   112,   113,
     114,   115,   116,   117,   122,   120,   123,     3,    82,    83,
     140,    98,   144,    77,   133,   138,    34,    79,    85,   120,
     139,    76,    78,    56,   135,     3,    77,    77,   145,    77,
      77,    77,    76,   150,   150,    77,    81,   108,    77,    83,
      79,    97,    79,    82,   140,   142,    77,    77,   120,    79,
      79,    77,   133,    79,    85,   120,   145,   145,   145,   122,
      77,   122,    77,   122,   141,   120,   119,   140,    79,    77,
      79,    79,    60,    77,   145,    77,   145,    77,    82,    83,
     145,    99,   145,   145,    82
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   100,   101,   101,   101,   101,   102,   102,   103,   103,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     105,   105,   106,   106,   106,   106,   106,   106,   106,   107,
     107,   107,   107,   107,   107,   108,   108,   109,   109,   109,
     109,   110,   110,   110,   111,   111,   111,   112,   112,   112,
     112,   112,   113,   113,   113,   114,   114,   115,   115,   116,
     116,   117,   117,   118,   118,   119,   119,   120,   120,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     122,   122,   123,   124,   124,   125,   125,   126,   126,   127,
     127,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   129,   129,   130,   130,   131,   131,
     131,   131,   131,   131,   131,   131,   132,   132,   133,   133,
     134,   134,   135,   135,   135,   136,   136,   137,   137,   138,
     138,   138,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   140,   140,   140,   141,   141,   141,
     141,   142,   143,   143,   144,   144,   145,   145,   145,   145,
     145,   145,   146,   146,   146,   147,   147,   148,   148,   149,
     149,   150,   150,   151,   151,   151,   152,   152,   152,   152,
     152,   152,   153,   153,   153,   153,   153,   154,   154,   155,
     155,   156,   156,   157,   157
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     4,     3,     4,     3,     3,     2,     2,     6,     7,
       1,     3,     1,     2,     2,     2,     2,     4,     4,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     5,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     2,     3,     2,     1,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     2,     1,     1,     3,
       3,     4,     4,     4,     3,     4,     2,     1,     3,     1,
       1,     3,     2,     2,     1,     1,     3,     2,     1,     2,
       1,     1,     3,     2,     3,     4,     3,     3,     4,     4,
       2,     3,     3,     4,     3,     4,     1,     2,     1,     4,
       3,     2,     1,     2,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     4,     3,     2,     3,     1,     2,     1,
       1,     1,     2,     7,     5,     5,     5,     7,     6,     7,
       6,     7,     3,     2,     2,     2,     3,     1,     2,     1,
       1,     4,     3,     1,     2
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
  case 2: /* primary_expression: IDENTIFIER  */
#line 156 "c.y"
                                                                                         { (yyval.p_expr) = new ASTPrimaryExpr(new ASTId(yytext)); }
#line 1695 "c.tab.cpp"
    break;

  case 3: /* primary_expression: constant  */
#line 157 "c.y"
                                                                                         { (yyval.p_expr) = new ASTPrimaryExpr((yyvsp[0].constant)); }
#line 1701 "c.tab.cpp"
    break;

  case 4: /* primary_expression: string  */
#line 158 "c.y"
                                                                                         { (yyval.p_expr) = new ASTPrimaryExpr((yyvsp[0].str_const)); }
#line 1707 "c.tab.cpp"
    break;

  case 5: /* primary_expression: '(' expression ')'  */
#line 159 "c.y"
                                                                                         { (yyval.p_expr) = new ASTPrimaryExpr((yyvsp[-1].expr)); }
#line 1713 "c.tab.cpp"
    break;

  case 6: /* constant: I_CONSTANT  */
#line 163 "c.y"
                                                                                                 { (yyval.constant) = new ASTConst(i_const, yytext); }
#line 1719 "c.tab.cpp"
    break;

  case 7: /* constant: F_CONSTANT  */
#line 164 "c.y"
                                                                                         { (yyval.constant) = new ASTConst(f_const, yytext); }
#line 1725 "c.tab.cpp"
    break;

  case 8: /* string: STRING_LITERAL  */
#line 168 "c.y"
                                                                                         { (yyval.str_const) = new ASTStrLiteralConst(); }
#line 1731 "c.tab.cpp"
    break;

  case 9: /* string: FUNC_NAME  */
#line 169 "c.y"
                                                                                         { (yyval.str_const) = new ASTFuncNameConst(); }
#line 1737 "c.tab.cpp"
    break;

  case 10: /* postfix_expression: primary_expression  */
#line 173 "c.y"
                                                                                         { (yyval.postfix_expr) = new ASTPostExpr((yyvsp[0].p_expr)); }
#line 1743 "c.tab.cpp"
    break;

  case 11: /* postfix_expression: postfix_expression '[' expression ']'  */
#line 174 "c.y"
                                                                                         { (yyval.postfix_expr) = new ASTPostExpr((yyvsp[-3].postfix_expr), (yyvsp[-1].expr)); }
#line 1749 "c.tab.cpp"
    break;

  case 12: /* postfix_expression: postfix_expression '(' ')'  */
#line 175 "c.y"
                                                                                         { (yyval.postfix_expr) = new ASTPostExpr((yyvsp[-2].postfix_expr)); }
#line 1755 "c.tab.cpp"
    break;

  case 13: /* postfix_expression: postfix_expression '(' argument_expression_list ')'  */
#line 176 "c.y"
                                                                                         { (yyval.postfix_expr) = new ASTPostExpr((yyvsp[-3].postfix_expr), (yyvsp[-1].arg_expr_l)); }
#line 1761 "c.tab.cpp"
    break;

  case 14: /* postfix_expression: postfix_expression '.' IDENTIFIER  */
#line 177 "c.y"
                                                                                         { (yyval.postfix_expr) = new ASTPostExpr((yyvsp[-2].postfix_expr), new ASTPtrOp(dot_op), new ASTId(yytext)); }
#line 1767 "c.tab.cpp"
    break;

  case 15: /* postfix_expression: postfix_expression PTR_OP IDENTIFIER  */
#line 178 "c.y"
                                                                                         { (yyval.postfix_expr) = new ASTPostExpr((yyvsp[-2].postfix_expr), new ASTPtrOp(ptr_op), new ASTId(yytext)); }
#line 1773 "c.tab.cpp"
    break;

  case 16: /* postfix_expression: postfix_expression INC_OP  */
#line 179 "c.y"
                                                                                         { (yyval.postfix_expr) = new ASTPostExpr((yyvsp[-1].postfix_expr), new ASTIncOp(plus_plus)); }
#line 1779 "c.tab.cpp"
    break;

  case 17: /* postfix_expression: postfix_expression DEC_OP  */
#line 180 "c.y"
                                                                                         { (yyval.postfix_expr) = new ASTPostExpr((yyvsp[-1].postfix_expr), new ASTIncOp(minus_minus)); }
#line 1785 "c.tab.cpp"
    break;

  case 18: /* postfix_expression: '(' type_name ')' '{' initializer_list '}'  */
#line 181 "c.y"
                                                                                         { todo(84); }
#line 1791 "c.tab.cpp"
    break;

  case 19: /* postfix_expression: '(' type_name ')' '{' initializer_list ',' '}'  */
#line 182 "c.y"
                                                                                         { todo(85); }
#line 1797 "c.tab.cpp"
    break;

  case 20: /* argument_expression_list: assignment_expression  */
#line 186 "c.y"
                                                                                         { (yyval.arg_expr_l) = new ASTArgExpList((yyvsp[0].ass_expr)); }
#line 1803 "c.tab.cpp"
    break;

  case 21: /* argument_expression_list: argument_expression_list ',' assignment_expression  */
#line 187 "c.y"
                                                                                         { (yyval.arg_expr_l) = new ASTArgExpList((yyvsp[-2].arg_expr_l), (yyvsp[0].ass_expr)); }
#line 1809 "c.tab.cpp"
    break;

  case 22: /* unary_expression: postfix_expression  */
#line 191 "c.y"
                                                                                         { (yyval.unary_expr) = new ASTUnaryExpr((yyvsp[0].postfix_expr)); }
#line 1815 "c.tab.cpp"
    break;

  case 23: /* unary_expression: INC_OP unary_expression  */
#line 192 "c.y"
                                                                                         { (yyval.unary_expr) = new ASTUnaryExpr(new ASTIncOp(plus_plus), (yyvsp[0].unary_expr)); }
#line 1821 "c.tab.cpp"
    break;

  case 24: /* unary_expression: DEC_OP unary_expression  */
#line 193 "c.y"
                                                                                         { (yyval.unary_expr) = new ASTUnaryExpr(new ASTIncOp(minus_minus), (yyvsp[0].unary_expr)); }
#line 1827 "c.tab.cpp"
    break;

  case 25: /* unary_expression: unary_operator cast_expression  */
#line 194 "c.y"
                                                                                         { (yyval.unary_expr) = new ASTUnaryExpr((yyvsp[-1].unary_op), (yyvsp[0].unary_expr)); }
#line 1833 "c.tab.cpp"
    break;

  case 26: /* unary_expression: SIZEOF unary_expression  */
#line 195 "c.y"
                                                                                         { todo(98); }
#line 1839 "c.tab.cpp"
    break;

  case 27: /* unary_expression: SIZEOF '(' type_name ')'  */
#line 196 "c.y"
                                                                                         { todo(99); }
#line 1845 "c.tab.cpp"
    break;

  case 28: /* unary_expression: ALIGNOF '(' type_name ')'  */
#line 197 "c.y"
                                                                                         { todo(100); }
#line 1851 "c.tab.cpp"
    break;

  case 29: /* unary_operator: '&'  */
#line 201 "c.y"
                                                                                         { (yyval.unary_op) = new ASTUnaryOp(u_op_and); }
#line 1857 "c.tab.cpp"
    break;

  case 30: /* unary_operator: '*'  */
#line 202 "c.y"
                                                                                         { (yyval.unary_op) = new ASTUnaryOp(u_op_star); }
#line 1863 "c.tab.cpp"
    break;

  case 31: /* unary_operator: '+'  */
#line 203 "c.y"
                                                                                         { (yyval.unary_op) = new ASTUnaryOp(u_op_plus); }
#line 1869 "c.tab.cpp"
    break;

  case 32: /* unary_operator: '-'  */
#line 204 "c.y"
                                                                                         { (yyval.unary_op) = new ASTUnaryOp(u_op_minus); }
#line 1875 "c.tab.cpp"
    break;

  case 33: /* unary_operator: '~'  */
#line 205 "c.y"
                                                                                         { (yyval.unary_op) = new ASTUnaryOp(u_op_tilde); }
#line 1881 "c.tab.cpp"
    break;

  case 34: /* unary_operator: '!'  */
#line 206 "c.y"
                                                                                         { (yyval.unary_op) = new ASTUnaryOp(u_op_not); }
#line 1887 "c.tab.cpp"
    break;

  case 35: /* cast_expression: unary_expression  */
#line 210 "c.y"
                                                                                         { (yyval.unary_expr) = (yyvsp[0].unary_expr); }
#line 1893 "c.tab.cpp"
    break;

  case 36: /* cast_expression: '(' type_name ')' cast_expression  */
#line 211 "c.y"
                                                                                         { todo(160); }
#line 1899 "c.tab.cpp"
    break;

  case 37: /* multiplicative_expression: cast_expression  */
#line 215 "c.y"
                                                                                         { (yyval.mul_expr) = new ASTMulExpr((yyvsp[0].unary_expr)); }
#line 1905 "c.tab.cpp"
    break;

  case 38: /* multiplicative_expression: multiplicative_expression '*' cast_expression  */
#line 216 "c.y"
                                                                                         { (yyval.mul_expr) = new ASTMulExpr((yyvsp[-2].mul_expr), new ASTArithOp(mul_op), (yyvsp[0].unary_expr)); }
#line 1911 "c.tab.cpp"
    break;

  case 39: /* multiplicative_expression: multiplicative_expression '/' cast_expression  */
#line 217 "c.y"
                                                                                         { (yyval.mul_expr) = new ASTMulExpr((yyvsp[-2].mul_expr), new ASTArithOp(div_op), (yyvsp[0].unary_expr)); }
#line 1917 "c.tab.cpp"
    break;

  case 40: /* multiplicative_expression: multiplicative_expression '%' cast_expression  */
#line 218 "c.y"
                                                                                         { (yyval.mul_expr) = new ASTMulExpr((yyvsp[-2].mul_expr), new ASTArithOp(remainder_op), (yyvsp[0].unary_expr)); }
#line 1923 "c.tab.cpp"
    break;

  case 41: /* additive_expression: multiplicative_expression  */
#line 222 "c.y"
                                                                                         { (yyval.add_expr) = new ASTAddExpr((yyvsp[0].mul_expr)); }
#line 1929 "c.tab.cpp"
    break;

  case 42: /* additive_expression: additive_expression '+' multiplicative_expression  */
#line 223 "c.y"
                                                                                         { (yyval.add_expr) = new ASTAddExpr((yyvsp[-2].add_expr), new ASTArithOp(add_op), (yyvsp[0].mul_expr)); }
#line 1935 "c.tab.cpp"
    break;

  case 43: /* additive_expression: additive_expression '-' multiplicative_expression  */
#line 224 "c.y"
                                                                                         { (yyval.add_expr) = new ASTAddExpr((yyvsp[-2].add_expr), new ASTArithOp(minus_op), (yyvsp[0].mul_expr)); }
#line 1941 "c.tab.cpp"
    break;

  case 44: /* shift_expression: additive_expression  */
#line 228 "c.y"
                                                                                         { (yyval.shift_expr) = new ASTShiftExpr((yyvsp[0].add_expr)); }
#line 1947 "c.tab.cpp"
    break;

  case 45: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 229 "c.y"
                                                                                         { (yyval.shift_expr) = new ASTShiftExpr((yyvsp[-2].shift_expr), new ASTShiftOp(left_shift_op), (yyvsp[0].add_expr)); }
#line 1953 "c.tab.cpp"
    break;

  case 46: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 230 "c.y"
                                                                                         { (yyval.shift_expr) = new ASTShiftExpr((yyvsp[-2].shift_expr), new ASTShiftOp(right_shift_op), (yyvsp[0].add_expr)); }
#line 1959 "c.tab.cpp"
    break;

  case 47: /* relational_expression: shift_expression  */
#line 234 "c.y"
                                                                                         { (yyval.rel_expr) = new ASTRelExpr((yyvsp[0].shift_expr)); }
#line 1965 "c.tab.cpp"
    break;

  case 48: /* relational_expression: relational_expression '<' shift_expression  */
#line 235 "c.y"
                                                                                         { (yyval.rel_expr) = new ASTRelExpr((yyvsp[-2].rel_expr), new ASTRelOp(less_op), (yyvsp[0].shift_expr)); }
#line 1971 "c.tab.cpp"
    break;

  case 49: /* relational_expression: relational_expression '>' shift_expression  */
#line 236 "c.y"
                                                                                         { (yyval.rel_expr) = new ASTRelExpr((yyvsp[-2].rel_expr), new ASTRelOp(greater_op), (yyvsp[0].shift_expr)); }
#line 1977 "c.tab.cpp"
    break;

  case 50: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 237 "c.y"
                                                                                         { (yyval.rel_expr) = new ASTRelExpr((yyvsp[-2].rel_expr), new ASTRelOp(less_eq), (yyvsp[0].shift_expr)); }
#line 1983 "c.tab.cpp"
    break;

  case 51: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 238 "c.y"
                                                                                         { (yyval.rel_expr) = new ASTRelExpr((yyvsp[-2].rel_expr), new ASTRelOp(greater_eq), (yyvsp[0].shift_expr)); }
#line 1989 "c.tab.cpp"
    break;

  case 52: /* equality_expression: relational_expression  */
#line 242 "c.y"
                                                                                         { (yyval.eq_expr) = new ASTEqExpr((yyvsp[0].rel_expr)); }
#line 1995 "c.tab.cpp"
    break;

  case 53: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 243 "c.y"
                                                                                         { (yyval.eq_expr) = new ASTEqExpr((yyvsp[-2].eq_expr), new ASTEqOp(eq_op), (yyvsp[0].rel_expr)); }
#line 2001 "c.tab.cpp"
    break;

  case 54: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 244 "c.y"
                                                                                         { (yyval.eq_expr) = new ASTEqExpr((yyvsp[-2].eq_expr), new ASTEqOp(neq_op), (yyvsp[0].rel_expr)); }
#line 2007 "c.tab.cpp"
    break;

  case 55: /* and_expression: equality_expression  */
#line 248 "c.y"
                                                                                         { (yyval.and_expr) = new ASTAndExpr((yyvsp[0].eq_expr)); }
#line 2013 "c.tab.cpp"
    break;

  case 56: /* and_expression: and_expression '&' equality_expression  */
#line 249 "c.y"
                                                                                         { (yyval.and_expr) = new ASTAndExpr((yyvsp[-2].and_expr), (yyvsp[0].eq_expr)); }
#line 2019 "c.tab.cpp"
    break;

  case 57: /* exclusive_or_expression: and_expression  */
#line 253 "c.y"
                                                                                         { (yyval.exor_expr) = new ASTExclusiveOrExpr((yyvsp[0].and_expr)); }
#line 2025 "c.tab.cpp"
    break;

  case 58: /* exclusive_or_expression: exclusive_or_expression '^' and_expression  */
#line 254 "c.y"
                                                                                         { (yyval.exor_expr) = new ASTExclusiveOrExpr((yyvsp[-2].exor_expr), (yyvsp[0].and_expr)); }
#line 2031 "c.tab.cpp"
    break;

  case 59: /* inclusive_or_expression: exclusive_or_expression  */
#line 258 "c.y"
                                                                                         { (yyval.inor_expr) = new ASTInclusiveOrExpr((yyvsp[0].exor_expr)); }
#line 2037 "c.tab.cpp"
    break;

  case 60: /* inclusive_or_expression: inclusive_or_expression '|' exclusive_or_expression  */
#line 259 "c.y"
                                                                                         { (yyval.inor_expr) = new ASTInclusiveOrExpr((yyvsp[-2].inor_expr), (yyvsp[0].exor_expr)); }
#line 2043 "c.tab.cpp"
    break;

  case 61: /* logical_and_expression: inclusive_or_expression  */
#line 263 "c.y"
                                                                                         { (yyval.l_and_expr) = new ASTLogicalAndExpr((yyvsp[0].inor_expr)); }
#line 2049 "c.tab.cpp"
    break;

  case 62: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 264 "c.y"
                                                                                         { (yyval.l_and_expr) = new ASTLogicalAndExpr((yyvsp[-2].l_and_expr), (yyvsp[0].inor_expr)); }
#line 2055 "c.tab.cpp"
    break;

  case 63: /* logical_or_expression: logical_and_expression  */
#line 268 "c.y"
                                                                                         { (yyval.l_or_expr) = new ASTLogicalOrExpr((yyvsp[0].l_and_expr)); }
#line 2061 "c.tab.cpp"
    break;

  case 64: /* logical_or_expression: logical_or_expression OR_OP logical_and_expression  */
#line 269 "c.y"
                                                                                         { (yyval.l_or_expr) = new ASTLogicalOrExpr((yyvsp[-2].l_or_expr), (yyvsp[0].l_and_expr)); }
#line 2067 "c.tab.cpp"
    break;

  case 65: /* conditional_expression: logical_or_expression  */
#line 273 "c.y"
                                                                                         { (yyval.cond_expr) = new ASTCondExpr((yyvsp[0].l_or_expr)); }
#line 2073 "c.tab.cpp"
    break;

  case 66: /* conditional_expression: logical_or_expression '?' expression ':' conditional_expression  */
#line 274 "c.y"
                                                                                         { (yyval.cond_expr) = new ASTCondExpr((yyvsp[-4].l_or_expr), (yyvsp[-2].expr), (yyvsp[0].cond_expr)); }
#line 2079 "c.tab.cpp"
    break;

  case 67: /* assignment_expression: conditional_expression  */
#line 278 "c.y"
                                                                                         { (yyval.ass_expr) = new ASTAssignmentExpr((yyvsp[0].cond_expr)); }
#line 2085 "c.tab.cpp"
    break;

  case 68: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 279 "c.y"
                                                                                         { (yyval.ass_expr) = new ASTAssignmentExpr((yyvsp[-2].unary_expr), (yyvsp[-1].ass_op), (yyvsp[0].ass_expr));}
#line 2091 "c.tab.cpp"
    break;

  case 69: /* assignment_operator: '='  */
#line 283 "c.y"
                                                                                         { (yyval.ass_op) = new ASTAssignmentOp(assign); }
#line 2097 "c.tab.cpp"
    break;

  case 70: /* assignment_operator: MUL_ASSIGN  */
#line 284 "c.y"
                                                                                         { (yyval.ass_op) = new ASTAssignmentOp(mul_assign); }
#line 2103 "c.tab.cpp"
    break;

  case 71: /* assignment_operator: DIV_ASSIGN  */
#line 285 "c.y"
                                                                                         { (yyval.ass_op) = new ASTAssignmentOp(div_assign); }
#line 2109 "c.tab.cpp"
    break;

  case 72: /* assignment_operator: MOD_ASSIGN  */
#line 286 "c.y"
                                                                                         { (yyval.ass_op) = new ASTAssignmentOp(mod_assign); }
#line 2115 "c.tab.cpp"
    break;

  case 73: /* assignment_operator: ADD_ASSIGN  */
#line 287 "c.y"
                                                                                         { (yyval.ass_op) = new ASTAssignmentOp(add_assign); }
#line 2121 "c.tab.cpp"
    break;

  case 74: /* assignment_operator: SUB_ASSIGN  */
#line 288 "c.y"
                                                                                         { (yyval.ass_op) = new ASTAssignmentOp(sub_assign); }
#line 2127 "c.tab.cpp"
    break;

  case 75: /* assignment_operator: LEFT_ASSIGN  */
#line 289 "c.y"
                                                                                         { (yyval.ass_op) = new ASTAssignmentOp(left_assign); }
#line 2133 "c.tab.cpp"
    break;

  case 76: /* assignment_operator: RIGHT_ASSIGN  */
#line 290 "c.y"
                                                                                         { (yyval.ass_op) = new ASTAssignmentOp(right_assign); }
#line 2139 "c.tab.cpp"
    break;

  case 77: /* assignment_operator: AND_ASSIGN  */
#line 291 "c.y"
                                                                                         { (yyval.ass_op) = new ASTAssignmentOp(and_assign); }
#line 2145 "c.tab.cpp"
    break;

  case 78: /* assignment_operator: XOR_ASSIGN  */
#line 292 "c.y"
                                                                                         { (yyval.ass_op) = new ASTAssignmentOp(xor_assign); }
#line 2151 "c.tab.cpp"
    break;

  case 79: /* assignment_operator: OR_ASSIGN  */
#line 293 "c.y"
                                                                                         { (yyval.ass_op) = new ASTAssignmentOp(or_assign); }
#line 2157 "c.tab.cpp"
    break;

  case 80: /* expression: assignment_expression  */
#line 297 "c.y"
                                                                                         { (yyval.expr) = new ASTExpr((yyvsp[0].ass_expr)); }
#line 2163 "c.tab.cpp"
    break;

  case 81: /* expression: expression ',' assignment_expression  */
#line 298 "c.y"
                                                                                         { (yyval.expr) = new ASTExpr((yyvsp[-2].expr), (yyvsp[0].ass_expr)); }
#line 2169 "c.tab.cpp"
    break;

  case 83: /* declaration: declaration_specifiers ';'  */
#line 306 "c.y"
                                                                                         { (yyval.decl) = new ASTDecl((yyvsp[-1].decl_spec)); }
#line 2175 "c.tab.cpp"
    break;

  case 84: /* declaration: declaration_specifiers init_declarator_list ';'  */
#line 307 "c.y"
                                                                                         { (yyval.decl) = new ASTDecl((yyvsp[-2].decl_spec), (yyvsp[-1].init_decl_list)); }
#line 2181 "c.tab.cpp"
    break;

  case 85: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 311 "c.y"
                                                                                         { (yyval.decl_spec) = new ASTDeclSpec((yyvsp[-1].type), (yyvsp[0].decl_spec)); }
#line 2187 "c.tab.cpp"
    break;

  case 86: /* declaration_specifiers: type_specifier  */
#line 312 "c.y"
                                                                                         { (yyval.decl_spec) = new ASTDeclSpec((yyvsp[0].type)); }
#line 2193 "c.tab.cpp"
    break;

  case 87: /* init_declarator_list: init_declarator  */
#line 316 "c.y"
                                                                                         { (yyval.init_decl_list) = new ASTInitDeclList((yyvsp[0].init_decl)); }
#line 2199 "c.tab.cpp"
    break;

  case 88: /* init_declarator_list: init_declarator_list ',' init_declarator  */
#line 317 "c.y"
                                                                                         { (yyval.init_decl_list) = new ASTInitDeclList((yyvsp[-2].init_decl_list), (yyvsp[0].init_decl)); }
#line 2205 "c.tab.cpp"
    break;

  case 89: /* init_declarator: declarator '=' initializer  */
#line 321 "c.y"
                                                                                         { (yyval.init_decl) = new ASTInitDecl((yyvsp[-2].d_declarator), (yyvsp[0].init)); }
#line 2211 "c.tab.cpp"
    break;

  case 90: /* init_declarator: declarator  */
#line 322 "c.y"
                                                                                         { (yyval.init_decl) = new ASTInitDecl((yyvsp[0].d_declarator)); }
#line 2217 "c.tab.cpp"
    break;

  case 91: /* type_specifier: VOID  */
#line 326 "c.y"
                                                                                         { (yyval.type) = new ASTType(t_void); }
#line 2223 "c.tab.cpp"
    break;

  case 92: /* type_specifier: CHAR  */
#line 327 "c.y"
                                                                                         { (yyval.type) = new ASTType(t_char); }
#line 2229 "c.tab.cpp"
    break;

  case 93: /* type_specifier: SHORT  */
#line 328 "c.y"
                                                                                         { (yyval.type) = new ASTType(t_short); }
#line 2235 "c.tab.cpp"
    break;

  case 94: /* type_specifier: INT  */
#line 329 "c.y"
                                                                                         { (yyval.type) = new ASTType(t_int); }
#line 2241 "c.tab.cpp"
    break;

  case 95: /* type_specifier: FLOAT  */
#line 330 "c.y"
                                                                                         { (yyval.type) = new ASTType(t_float); }
#line 2247 "c.tab.cpp"
    break;

  case 96: /* type_specifier: LONG  */
#line 331 "c.y"
                                                                                   { (yyval.type) = new ASTType(t_long); }
#line 2253 "c.tab.cpp"
    break;

  case 97: /* type_specifier: DOUBLE  */
#line 332 "c.y"
                                                                                         { (yyval.type) = new ASTType(t_double); }
#line 2259 "c.tab.cpp"
    break;

  case 98: /* type_specifier: SIGNED  */
#line 333 "c.y"
                                                                                         { (yyval.type) = new ASTType(t_signed); }
#line 2265 "c.tab.cpp"
    break;

  case 99: /* type_specifier: UNSIGNED  */
#line 334 "c.y"
                                                                                         { (yyval.type) = new ASTType(t_unsigned); }
#line 2271 "c.tab.cpp"
    break;

  case 100: /* type_specifier: BOOL  */
#line 335 "c.y"
                                                                                         { (yyval.type) = new ASTType(t_bool); }
#line 2277 "c.tab.cpp"
    break;

  case 101: /* type_specifier: COMPLEX  */
#line 336 "c.y"
                                                                                         { (yyval.type) = new ASTType(t_complex); }
#line 2283 "c.tab.cpp"
    break;

  case 102: /* type_specifier: IMAGINARY  */
#line 337 "c.y"
                                                                                                 { (yyval.type) = new ASTType(t_imaginary); }
#line 2289 "c.tab.cpp"
    break;

  case 103: /* type_specifier: TYPEDEF_NAME  */
#line 338 "c.y"
                                                                                               { todo(262); }
#line 2295 "c.tab.cpp"
    break;

  case 106: /* declarator: pointer direct_declarator  */
#line 347 "c.y"
                                                                                          { todo(345);}
#line 2301 "c.tab.cpp"
    break;

  case 107: /* declarator: direct_declarator  */
#line 348 "c.y"
                                                                                          { (yyval.d_declarator) = (yyvsp[0].d_declarator);}
#line 2307 "c.tab.cpp"
    break;

  case 108: /* direct_declarator: IDENTIFIER  */
#line 352 "c.y"
                                                                                          { (yyval.d_declarator) = new ASTIdDeclarator(new ASTId(yytext)); }
#line 2313 "c.tab.cpp"
    break;

  case 109: /* direct_declarator: '(' declarator ')'  */
#line 353 "c.y"
                                                                                          { (yyval.d_declarator) = (yyvsp[-1].d_declarator); }
#line 2319 "c.tab.cpp"
    break;

  case 110: /* direct_declarator: direct_declarator '[' ']'  */
#line 354 "c.y"
                                                                                          { todo(352); }
#line 2325 "c.tab.cpp"
    break;

  case 111: /* direct_declarator: direct_declarator '[' '*' ']'  */
#line 355 "c.y"
                                                                                          { todo(353); }
#line 2331 "c.tab.cpp"
    break;

  case 112: /* direct_declarator: direct_declarator '[' assignment_expression ']'  */
#line 356 "c.y"
                                                                                          { todo(360); }
#line 2337 "c.tab.cpp"
    break;

  case 113: /* direct_declarator: direct_declarator '(' parameter_type_list ')'  */
#line 357 "c.y"
                                                                                          { (yyval.d_declarator) = new ASTFnDeclarator((yyvsp[-3].d_declarator), (yyvsp[-1].param_list));}
#line 2343 "c.tab.cpp"
    break;

  case 114: /* direct_declarator: direct_declarator '(' ')'  */
#line 358 "c.y"
                                                                                          { (yyval.d_declarator) = new ASTFnDeclarator((yyvsp[-2].d_declarator));}
#line 2349 "c.tab.cpp"
    break;

  case 115: /* direct_declarator: direct_declarator '(' identifier_list ')'  */
#line 359 "c.y"
                                                                                          { (yyval.d_declarator) = new ASTFnCallDeclarator((yyvsp[-3].d_declarator), (yyvsp[-1].id_list));}
#line 2355 "c.tab.cpp"
    break;

  case 116: /* pointer: '*' pointer  */
#line 363 "c.y"
                                                                                          { (yyval.ptr) = new ASTPtr((yyvsp[0].ptr)); }
#line 2361 "c.tab.cpp"
    break;

  case 117: /* pointer: '*'  */
#line 364 "c.y"
                                                                                          { (yyval.ptr) = new ASTPtr(); }
#line 2367 "c.tab.cpp"
    break;

  case 118: /* parameter_type_list: parameter_list ',' ELLIPSIS  */
#line 368 "c.y"
                                                                                           { todo(285); }
#line 2373 "c.tab.cpp"
    break;

  case 119: /* parameter_type_list: parameter_list  */
#line 369 "c.y"
                                                                                           { (yyval.param_list) = (yyvsp[0].param_list); }
#line 2379 "c.tab.cpp"
    break;

  case 120: /* parameter_list: parameter_declaration  */
#line 373 "c.y"
                                                                                           { (yyval.param_list) = new ASTParamList((yyvsp[0].param_decl)); }
#line 2385 "c.tab.cpp"
    break;

  case 121: /* parameter_list: parameter_list ',' parameter_declaration  */
#line 374 "c.y"
                                                                                           { (yyval.param_list) = new ASTParamList((yyvsp[-2].param_list), (yyvsp[0].param_decl)); }
#line 2391 "c.tab.cpp"
    break;

  case 122: /* parameter_declaration: declaration_specifiers declarator  */
#line 378 "c.y"
                                                                                           { (yyval.param_decl) = new ASTParamDecl((yyvsp[-1].decl_spec), (yyvsp[0].d_declarator)); }
#line 2397 "c.tab.cpp"
    break;

  case 123: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 379 "c.y"
                                                                                           { todo(296); }
#line 2403 "c.tab.cpp"
    break;

  case 124: /* parameter_declaration: declaration_specifiers  */
#line 380 "c.y"
                                                                                           { (yyval.param_decl) = new ASTParamDecl((yyvsp[0].decl_spec)); }
#line 2409 "c.tab.cpp"
    break;

  case 125: /* identifier_list: IDENTIFIER  */
#line 384 "c.y"
                                                                                           { (yyval.id_list) = new ASTIdList(new ASTId(yytext)); }
#line 2415 "c.tab.cpp"
    break;

  case 126: /* identifier_list: identifier_list ',' IDENTIFIER  */
#line 385 "c.y"
                                                                                           { (yyval.id_list) = new ASTIdList((yyvsp[-2].id_list), new ASTId(yytext)); }
#line 2421 "c.tab.cpp"
    break;

  case 144: /* initializer: '{' initializer_list '}'  */
#line 415 "c.y"
                                                                                            { (yyval.init) = new ASTInitializer((yyvsp[-1].init_list)); }
#line 2427 "c.tab.cpp"
    break;

  case 145: /* initializer: '{' initializer_list ',' '}'  */
#line 416 "c.y"
                                                                                            { (yyval.init) = new ASTInitializer((yyvsp[-2].init_list)); }
#line 2433 "c.tab.cpp"
    break;

  case 146: /* initializer: assignment_expression  */
#line 417 "c.y"
                                                                                            { (yyval.init) = new ASTInitializer((yyvsp[0].ass_expr)); }
#line 2439 "c.tab.cpp"
    break;

  case 147: /* initializer_list: designation initializer  */
#line 421 "c.y"
                                                                                            { (yyval.init_list) = new ASTInitializerList((yyvsp[-1].design_list), (yyvsp[0].init)); }
#line 2445 "c.tab.cpp"
    break;

  case 148: /* initializer_list: initializer  */
#line 422 "c.y"
                                                                                            { (yyval.init_list) = new ASTInitializerList((yyvsp[0].init)); }
#line 2451 "c.tab.cpp"
    break;

  case 149: /* initializer_list: initializer_list ',' designation initializer  */
#line 423 "c.y"
                                                                                            { (yyval.init_list) = new ASTInitializerList((yyvsp[-3].init_list), (yyvsp[-1].design_list), (yyvsp[0].init)); }
#line 2457 "c.tab.cpp"
    break;

  case 150: /* initializer_list: initializer_list ',' initializer  */
#line 424 "c.y"
                                                                                            { (yyval.init_list) = new ASTInitializerList((yyvsp[-2].init_list), (yyvsp[0].init)); }
#line 2463 "c.tab.cpp"
    break;

  case 151: /* designation: designator_list '='  */
#line 428 "c.y"
                                                                                            { (yyval.design_list) = (yyvsp[-1].design_list); }
#line 2469 "c.tab.cpp"
    break;

  case 152: /* designator_list: designator  */
#line 432 "c.y"
                                                                                            { (yyval.design_list) = new ASTDesignatorList((yyvsp[0].design)); }
#line 2475 "c.tab.cpp"
    break;

  case 153: /* designator_list: designator_list designator  */
#line 433 "c.y"
                                                                                            { (yyval.design_list) = new ASTDesignatorList((yyvsp[-1].design_list), (yyvsp[0].design)); }
#line 2481 "c.tab.cpp"
    break;

  case 154: /* designator: '[' constant_expression ']'  */
#line 437 "c.y"
                                                                                            { (yyval.design) = new ASTDesignator((yyvsp[-1].cond_expr)); }
#line 2487 "c.tab.cpp"
    break;

  case 155: /* designator: '.' IDENTIFIER  */
#line 438 "c.y"
                                                                                            { (yyval.design) = new ASTDesignator(new ASTId(yytext)); }
#line 2493 "c.tab.cpp"
    break;

  case 156: /* statement: labeled_statement  */
#line 442 "c.y"
                                                                                            { (yyval.stmt) = (yyvsp[0].lab_stmt); }
#line 2499 "c.tab.cpp"
    break;

  case 157: /* statement: compound_statement  */
#line 443 "c.y"
                                                                                            { (yyval.stmt) = (yyvsp[0].blk_ilist); }
#line 2505 "c.tab.cpp"
    break;

  case 158: /* statement: expression_statement  */
#line 444 "c.y"
                                                                                            { (yyval.stmt) = (yyvsp[0].expr); }
#line 2511 "c.tab.cpp"
    break;

  case 159: /* statement: selection_statement  */
#line 445 "c.y"
                                                                                            { (yyval.stmt) = (yyvsp[0].sel_stmt); }
#line 2517 "c.tab.cpp"
    break;

  case 160: /* statement: iteration_statement  */
#line 446 "c.y"
                                                                                            { (yyval.stmt) = (yyvsp[0].iter_stmt); }
#line 2523 "c.tab.cpp"
    break;

  case 161: /* statement: jump_statement  */
#line 447 "c.y"
                                                                                            { (yyval.stmt) = (yyvsp[0].jmp_stmt); }
#line 2529 "c.tab.cpp"
    break;

  case 162: /* labeled_statement: IDENTIFIER ':' statement  */
#line 451 "c.y"
                                                                                            { (yyval.lab_stmt) = new ASTGotoLabeledStmt(new ASTId(yytext), (yyvsp[0].stmt)); }
#line 2535 "c.tab.cpp"
    break;

  case 163: /* labeled_statement: CASE constant_expression ':' statement  */
#line 452 "c.y"
                                                                                            { (yyval.lab_stmt) = new ASTCaseLabeledStmt((yyvsp[-2].cond_expr), (yyvsp[0].stmt)); }
#line 2541 "c.tab.cpp"
    break;

  case 164: /* labeled_statement: DEFAULT ':' statement  */
#line 453 "c.y"
                                                                                            { (yyval.lab_stmt) = new ASTDefLabeledStmt((yyvsp[0].stmt)); }
#line 2547 "c.tab.cpp"
    break;

  case 165: /* compound_statement: '{' '}'  */
#line 457 "c.y"
                                                                                            { (yyval.blk_ilist) = new ASTBlockItemList(); }
#line 2553 "c.tab.cpp"
    break;

  case 166: /* compound_statement: '{' block_item_list '}'  */
#line 458 "c.y"
                                                                                            { (yyval.blk_ilist) = (yyvsp[-1].blk_ilist); }
#line 2559 "c.tab.cpp"
    break;

  case 167: /* block_item_list: block_item  */
#line 462 "c.y"
                                                                                            { (yyval.blk_ilist) = new ASTBlockItemList((yyvsp[0].blk_i)); }
#line 2565 "c.tab.cpp"
    break;

  case 168: /* block_item_list: block_item_list block_item  */
#line 463 "c.y"
                                                                                            { (yyval.blk_ilist) = new ASTBlockItemList((yyvsp[-1].blk_ilist), (yyvsp[0].blk_i)); }
#line 2571 "c.tab.cpp"
    break;

  case 169: /* block_item: declaration  */
#line 467 "c.y"
                                                                                            { (yyval.blk_i) = new ASTBlockItem((yyvsp[0].decl)); }
#line 2577 "c.tab.cpp"
    break;

  case 170: /* block_item: statement  */
#line 468 "c.y"
                                                                                            { (yyval.blk_i) = new ASTBlockItem((yyvsp[0].stmt)); }
#line 2583 "c.tab.cpp"
    break;

  case 171: /* expression_statement: ';'  */
#line 472 "c.y"
                                                                                            { (yyval.expr) = NULL; }
#line 2589 "c.tab.cpp"
    break;

  case 172: /* expression_statement: expression ';'  */
#line 473 "c.y"
                                                                                            { (yyval.expr) = (yyvsp[-1].expr); }
#line 2595 "c.tab.cpp"
    break;

  case 173: /* selection_statement: IF '(' expression ')' statement ELSE statement  */
#line 477 "c.y"
                                                                                            { (yyval.sel_stmt) = new ASTIfElseSelectStmt((yyvsp[-4].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt)); }
#line 2601 "c.tab.cpp"
    break;

  case 174: /* selection_statement: IF '(' expression ')' statement  */
#line 478 "c.y"
                                                                                            { (yyval.sel_stmt) = new ASTIfSelectStmt((yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2607 "c.tab.cpp"
    break;

  case 175: /* selection_statement: SWITCH '(' expression ')' statement  */
#line 479 "c.y"
                                                                                            { (yyval.sel_stmt) = new ASTSwitchStmt((yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2613 "c.tab.cpp"
    break;

  case 176: /* iteration_statement: WHILE '(' expression ')' statement  */
#line 483 "c.y"
                                                                                            { (yyval.iter_stmt) = new ASTWhileStmt((yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2619 "c.tab.cpp"
    break;

  case 177: /* iteration_statement: DO statement WHILE '(' expression ')' ';'  */
#line 484 "c.y"
                                                                                            { (yyval.iter_stmt) = new ASTDoWhileStmt((yyvsp[-5].stmt), (yyvsp[-2].expr)); }
#line 2625 "c.tab.cpp"
    break;

  case 178: /* iteration_statement: FOR '(' expression_statement expression_statement ')' statement  */
#line 485 "c.y"
                                                                                            { (yyval.iter_stmt) = new ASTForStmt((yyvsp[-3].expr), (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2631 "c.tab.cpp"
    break;

  case 179: /* iteration_statement: FOR '(' expression_statement expression_statement expression ')' statement  */
#line 486 "c.y"
                                                                                            { (yyval.iter_stmt) = new ASTForStmt((yyvsp[-4].expr), (yyvsp[-3].expr), (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2637 "c.tab.cpp"
    break;

  case 180: /* iteration_statement: FOR '(' declaration expression_statement ')' statement  */
#line 487 "c.y"
                                                                                            { (yyval.iter_stmt) = new ASTForStmt((yyvsp[-3].decl), (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2643 "c.tab.cpp"
    break;

  case 181: /* iteration_statement: FOR '(' declaration expression_statement expression ')' statement  */
#line 488 "c.y"
                                                                                            { (yyval.iter_stmt) = new ASTForStmt((yyvsp[-4].decl), (yyvsp[-3].expr), (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2649 "c.tab.cpp"
    break;

  case 182: /* jump_statement: GOTO IDENTIFIER ';'  */
#line 492 "c.y"
                                                                                      { (yyval.jmp_stmt) = new ASTGotoJmpStmt(new ASTId(yytext)); }
#line 2655 "c.tab.cpp"
    break;

  case 183: /* jump_statement: CONTINUE ';'  */
#line 493 "c.y"
                                                                                            { (yyval.jmp_stmt) = new ASTContJmpStmt(); }
#line 2661 "c.tab.cpp"
    break;

  case 184: /* jump_statement: BREAK ';'  */
#line 494 "c.y"
                                                                                      { (yyval.jmp_stmt) = new ASTBreakJmpStmt(); }
#line 2667 "c.tab.cpp"
    break;

  case 185: /* jump_statement: RETURN ';'  */
#line 495 "c.y"
                                                                                            { (yyval.jmp_stmt) = new ASTRetJmpStmt(); }
#line 2673 "c.tab.cpp"
    break;

  case 186: /* jump_statement: RETURN expression ';'  */
#line 496 "c.y"
                                                                                            { (yyval.jmp_stmt) = new ASTRetJmpStmt((yyvsp[-1].expr)); }
#line 2679 "c.tab.cpp"
    break;

  case 187: /* translation_unit: external_declaration  */
#line 501 "c.y"
        {
		(yyval.prog) = new ASTProgram((yyvsp[0].ext_decl));
		program_ast = (yyval.prog);
	}
#line 2688 "c.tab.cpp"
    break;

  case 188: /* translation_unit: translation_unit external_declaration  */
#line 506 "c.y"
        {
		(yyval.prog) = new ASTProgram((yyvsp[-1].prog), (yyvsp[0].ext_decl));
		program_ast = (yyval.prog);
	}
#line 2697 "c.tab.cpp"
    break;

  case 189: /* external_declaration: function_definition  */
#line 513 "c.y"
                                                                                            { (yyval.ext_decl) = new ASTExternDecl((yyvsp[0].fn_def)); }
#line 2703 "c.tab.cpp"
    break;

  case 190: /* external_declaration: declaration  */
#line 514 "c.y"
                                                                                            { (yyval.ext_decl) = new ASTExternDecl((yyvsp[0].decl)); }
#line 2709 "c.tab.cpp"
    break;

  case 191: /* function_definition: declaration_specifiers declarator declaration_list compound_statement  */
#line 518 "c.y"
                                                                                            { (yyval.fn_def) = new ASTFnDef((yyvsp[-3].decl_spec), (yyvsp[-2].d_declarator), (yyvsp[-1].decl_list), (yyvsp[0].blk_ilist)); }
#line 2715 "c.tab.cpp"
    break;

  case 192: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 519 "c.y"
                                                                                            { (yyval.fn_def) = new ASTFnDef((yyvsp[-2].decl_spec), (yyvsp[-1].d_declarator), (yyvsp[0].blk_ilist)); }
#line 2721 "c.tab.cpp"
    break;

  case 193: /* declaration_list: declaration  */
#line 523 "c.y"
                                                                                            { (yyval.decl_list) = new ASTDeclList(); }
#line 2727 "c.tab.cpp"
    break;

  case 194: /* declaration_list: declaration_list declaration  */
#line 524 "c.y"
                                                                                            { (yyval.decl_list) = new ASTDeclList((yyvsp[-1].decl_list), (yyvsp[0].decl)); }
#line 2733 "c.tab.cpp"
    break;


#line 2737 "c.tab.cpp"

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

#line 527 "c.y"

#include <stdio.h>

void yyerror(const char *s)
{
	fflush(stdout);
	fprintf(stderr, "*** %s\n", s);
}

void todo(int rule_no){
  char *msg;
  int formatterStrResult = asprintf(&msg, "Rule no. %d Not Supported Yet\n", rule_no);
  yyerror(msg);
  free(msg);
}
