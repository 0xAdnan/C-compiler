//
// Created by satyam on 29/3/24.
//

#ifndef CCOMPILER_ENUMS_H
#define CCOMPILER_ENUMS_H

#include "string"

using namespace std;

enum ctype_ {
    t_void,
    t_char,
    t_short,
    t_int,
    t_long,
    t_long_long,
    t_float,
    t_double,
    t_signed,
    t_unsigned,
    t_bool,
    t_complex,
    t_imaginary
};

enum op_type{
    nop,
    unary,
    binary,
    ternary,
    assignment,
};

enum operators {
    noop,

// unary operator_
    u_op_plus_plus,
    u_op_minus_minus,
    u_op_and,
    u_op_star,
    u_op_plus,
    u_op_minus,
    u_op_tilde,
    u_op_not,

// binary_op
    b_mul,
    b_div,
    b_remainder,
    b_add,
    b_minus,

    b_left_shift,
    b_right_shift,

    b_less,
    b_greater,
    b_less_eq,
    b_greater_eq,
    b_eq,
    b_neq,

    b_bitand,
    b_bitxor,
    b_bitor,

    b_and,
    b_or,

    t_cond,

// assignment_op
    assign,
    mul_assign,
    div_assign,
    mod_assign,
    add_assign,
    sub_assign,
    left_assign,
    right_assign,
    and_assign,
    xor_assign,
    or_assign,
};

enum const_type {
    i_const,
    f_const,
    s_const,
};


op_type get_op_type(operators op);

string op_to_str(operators op);

string const_type_to_str(const_type ct);

#endif //CCOMPILER_ENUMS_H
