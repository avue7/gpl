#include "expression.h"

// unary and binary operator
Expression::Expression(Operator_type operator_type, Gpl_type gpl_type, Expression *lhs, Expression *rhs)
{
  m_gpl_type = gpl_type;
  m_lhs = lhs;
  m_rhs = rhs;
  // Binary Operators
  if (operator_type == PLUS)
    m_oper = operator_type;
    m_node = BINARY_OPERATOR;
  else if (operator_type == MINUS)
    m_oper = operator_type;
    m_node = BINARY_OPERATOR;
  else if (operator_type == MULTIPLY)
    m_oper = operator_type;
    m_node = BINARY_OPERATOR;
  else if (operator_type == DIVIDE)
    m_oper = operator_type;
    m_node = BINARY_OPERATOR;
  else if (operator_type == MOD)
    m_oper = operator_type;
    m_node = BINARY_OPERATOR;
  // Unary Operators
  else if (operator_type == UNARY_MINUS)
    m_oper = operator_type;
    m_node = UNARY_OPERATOR;
  else if (operator_type == SIN)
    m_oper = operator_type;
    m_node = UNARY_OPERATOR;
  else if (operator_type == COS)
    m_oper = operator_type;
    m_node = UNARY_OPERATOR;
  else if (operator_type == TAN)
    m_oper = operator_type;
    m_node = UNARY_OPERATOR;
  else if (operator_type == ASIN)
    m_oper = operator_type;
    m_node = UNARY_OPERATOR;
  else if (operator_type == ACOS)
    m_oper = operator_type;
    m_node = UNARY_OPERATOR;
  else if (operator_type == ATAN)
    m_oper = operator_type;
    m_node = UNARY_OPERATOR;
  else if (operator_type == RANDOM)
    m_oper = operator_type;
    m_node = UNARY_OPERATOR;
  else if (operator_type == SQRT)
    m_oper = operator_type;
    m_node = UNARY_OPERATOR;
  else
    cerr << "Error: cannot get operator type in constructor." << endl;
}

// Constructor for constants
Expression::Expression(void *value, Gpl_type gpl_type, Expression *lhs, Expression *rhs)
{
  m_value = value;
  m_gpl_type = gpl_type;
  m_lhs = lhs;
  m_rhs = rhs;
  m_node = CONSTANT // Set this node_type to CONSTANT
}


