//
// Created by satyam on 31/3/24.
//

#include "enums.h"


op_type get_op_type(operators op){
  switch (op) {
    case noop:
      return nop;
    case u_op_plus_plus:
      return unary;
    case u_op_minus_minus:
      return unary;
    case u_op_and:
      return unary;
    case u_op_star:
      return unary;
    case u_op_plus:
      return unary;
    case u_op_minus:
      return unary;
    case u_op_tilde:
      return unary;
    case u_op_not:
      return unary;

    case b_mul:
      return binary;
    case b_div:
      return binary;
    case b_remainder:
      return binary;
    case b_add:
      return binary;
    case b_minus:
      return binary;
    case b_left_shift:
      return binary;
    case b_right_shift:
      return binary;
    case b_less:
      return binary;
    case b_greater:
      return binary;
    case b_less_eq:
      return binary;
    case b_greater_eq:
      return binary;
    case b_eq:
      return binary;
    case b_neq:
      return binary;
    case b_bitand:
      return binary;
    case b_bitxor:
      return binary;
    case b_bitor:
      return binary;
    case b_and:
      return binary;
    case b_or:
      return binary;

    case t_cond:
      return ternary;

    case assign:
      return assignment;
    case mul_assign:
      return assignment;
    case div_assign:
      return assignment;
    case mod_assign:
      return assignment;
    case add_assign:
      return assignment;
    case sub_assign:
      return assignment;
    case left_assign:
      return assignment;
    case right_assign:
      return assignment;
    case and_assign:
      return assignment;
    case xor_assign:
      return assignment;
    case or_assign:
      return assignment;
    default:
      return nop;
  }
}

string op_to_str(operators op){
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

string const_type_to_str(const_type ct){
  switch (ct){
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
