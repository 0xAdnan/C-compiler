//
// Created by satyam on 31/3/24.
//

#include "enums.h"


op_type get_op_type(operators op) {
  switch (op) {
    case noop:
      return nop;
    case u_op_plus_plus:
    case u_op_minus_minus:
    case u_op_and:
    case u_op_star:
    case u_op_plus:
    case u_op_minus:
    case u_op_tilde:
    case u_op_not:
      return unary;

    case b_mul:
    case b_div:
    case b_remainder:
    case b_add:
    case b_minus:
    case b_left_shift:
    case b_right_shift:
    case b_less:
    case b_greater:
    case b_less_eq:
    case b_greater_eq:
    case b_eq:
    case b_neq:
    case b_bitand:
    case b_bitxor:
    case b_bitor:
    case b_and:
    case b_or:
      return binary;

    case t_cond:
      return ternary;

    case assign:
    case mul_assign:
    case div_assign:
    case mod_assign:
    case add_assign:
    case sub_assign:
    case left_assign:
    case right_assign:
    case and_assign:
    case xor_assign:
    case or_assign:
      return assignment;

    default:
      return nop;
  }
}

string op_to_str(operators op) {
  switch (op) {
    case noop:
      return "noop";
    case u_op_plus_plus:
      return "++";
    case u_op_minus_minus:
      return "--";
    case u_op_and:
      return "&ref";
    case u_op_star:
      return "*ref";
    case u_op_plus:
      return "+";
    case u_op_minus:
      return "-";
    case u_op_tilde:
      return "~";
    case u_op_not:
      return "!";

    case b_mul:
      return "*";
    case b_div:
      return "/";
    case b_remainder:
      return "%";
    case b_add:
      return "+";
    case b_minus:
      return "-";
    case b_left_shift:
      return "<<";
    case b_right_shift:
      return ">>";
    case b_less:
      return "<";
    case b_greater:
      return ">";
    case b_less_eq:
      return "<=";
    case b_greater_eq:
      return ">=";
    case b_eq:
      return "==";
    case b_neq:
      return "!=";
    case b_bitand:
      return "&";
    case b_bitxor:
      return "^";
    case b_bitor:
      return "|";
    case b_and:
      return "&&";
    case b_or:
      return "||";

    case t_cond:
      return "?";

    case assign:
      return "=";
    case mul_assign:
      return "*=";
    case div_assign:
      return "/=";
    case mod_assign:
      return "%=";
    case add_assign:
      return "+=";
    case sub_assign:
      return "-=";
    case left_assign:
      return "<<=";
    case right_assign:
      return ">>=";
    case and_assign:
      return "&=";
    case xor_assign:
      return "^=";
    case or_assign:
      return "|=";
    default:
      return "BadOperator";
  }
}

string const_type_to_str(const_type ct) {
  switch (ct) {
    case i_const:
      return "int";
    case f_const:
      return "float";
    case s_const:
      return "string";
    default:
      return "BadType";
  }
}
