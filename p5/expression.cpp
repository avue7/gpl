#include "expression.h"
#include "variable.h"

// unary and binary operator
Expression::Expression(Operator_type operator_type, Gpl_type gpl_type, Expression *lhs, Expression *rhs)
{
  m_type = gpl_type;
  m_lhs = lhs;
  m_rhs = rhs;
  m_oper = operator_type;
  
  // Use a switch statement to keep from typing too many if else
  switch (operator_type)
  {
    case PLUS:
    case MINUS:
    case MULTIPLY:
    case DIVIDE:
    case MOD:
      m_node = BINARY_OPERATOR;
      break;
    case OR:
    case AND:
    case EQUAL:
    case NOT_EQUAL:
    case GREATER_EQUAL:
    case GREATER_THAN:
    case LESS_THAN:
    case LESS_EQUAL:
      m_node = LOGICAL_OPERATOR; // Logical ops are binary
      break;
    case UNARY_MINUS:
    case SIN:
    case COS:
    case TAN:
    case ASIN:
    case ACOS:
    case ATAN:
    case RANDOM:
    case SQRT:
      m_node = UNARY_OPERATOR;
      break;
    //set the default of the case incase cant get the op_type
    default: cerr << "Error: cannot assign operator type" << endl;
    break;
  }
}

// Constructor for constants
Expression::Expression(int value, Gpl_type gpl_type, Expression *lhs, Expression *rhs)
{
  m_value = (void*) new int(value);
  m_type = gpl_type;
  m_lhs = lhs;
  m_rhs = rhs;
  m_node = CONSTANT; // Set this node_type to CONSTANT
}

Expression::Expression(double value, Gpl_type gpl_type, Expression *lhs, Expression *rhs)
{
  m_value = (void*) new double(value);
  m_type = gpl_type;
  m_lhs = lhs;
  m_rhs = rhs;
  m_node = CONSTANT; // Set this node_type to CONSTANT
}

Expression::Expression(string value, Gpl_type gpl_type, Expression *lhs, Expression *rhs)
{
  m_value = (void*) new string(value);
  m_type = gpl_type;
  m_lhs = lhs;
  m_rhs = rhs;
  m_node = CONSTANT; // Set this node_type to CONSTANT
}

// Constructor for variable
Expression::Expression(Variable *variable)
{
  m_type = variable->m_type;
  m_var = variable;
  m_node = VARIABLE;
}
/***************************************
 *** EXPRESSION EVALUATION FUNCTIONS ***
***************************************/
/*
 * Recursively evaluates each node in the tree. Performs a depth-first
 * traversal of the tree. When a node's evaluation function is called, 
 * if the node has children, it calls evaluate on the left child, then 
 * the right child, then applies its operator. If the node holds a 
 * constant, it returns the value (which it gets from the my_variable->
 * get_int_value() and returns the value.
 * -----EXTRACT FROM: TYSON's WEBSITE, per p5 instruction-----
*/
int Expression::eval_int()
{

  // Make sure type is INT or DOUBLE
//  assert(m_type == INT || m_type == DOUBLE);
  if (m_node == CONSTANT)
  {
    return *(int*) m_value;
  }
  if (m_node == VARIABLE)
  {
    return m_var->get_int_value();
  }
  if (m_node == BINARY_OPERATOR)
  {   
    switch(m_oper)
    {
      case MULTIPLY: 
        return m_lhs->eval_int() * m_rhs->eval_int();
      case PLUS:
        return m_lhs->eval_int() + m_rhs->eval_int();
      case MINUS:
        return m_lhs->eval_int() - m_rhs->eval_int();
      case DIVIDE:
        return m_lhs->eval_int() / m_rhs->eval_int();
      case MOD:
        return m_lhs->eval_int() % m_rhs->eval_int();
      default: cerr << "Error: eval_int() failed!" << endl;
    }
  }
 // if (m_node == VARIABLE)
 // {
 //   cout << "Printing from var" << endl;
 // }
  /* BINARY_LOGICAL_OPERATORS EVALUATION */  
/*  if (m_oper == LESS_THAN)
  {
    assert(m_lhs && m_rhs); // Make sure both lhs and rhs exists
    // Check left and right side 
    if (m_lhs->m_type == STRING || m_rhs->m_type == STRING)
    {
      return m_lhs->eval_string() < m_rhs->eval_string();
    }
    else if (m_lhs->m_type == DOUBLE || m_rhs->m_type == DOUBLE) 
    {
      return m_lhs->eval_double() < m_rhs->eval_double();
    }
    else
    {
      return m_lhs->eval_int() < m_rhs->eval_int();
    }
  }
  else if (m_oper == LESS_EQUAL)
  {
    assert(m_lhs && m_rhs) // Make sure both lhs and rhs exists
    // Check left and right side 
    if (m_lhs->get_type() == STRING || m_rhs->get_type() == STRING)
    {
      return m_lhs->eval_string() <= m_rhs->eval_string();
    }
    else if (m_lhs->get_type() == DOUBLE || m_rhs->get_type() == DOUBLE) 
    {
      return m_lhs->eval_double() <= m_rhs->eval_double();
    }
    else
    {
      return m_lhs->eval_int() <= m_rhs->eval_int();
    }
  }
  else if (m_oper == GREATER_THAN)
  {
    assert(m_lhs && m_rhs) // Make sure both lhs and rhs exists
    // Check left and right side 
    if (m_lhs->get_type() == STRING || m_rhs->get_type() == STRING)
    {
      return m_lhs->eval_string() > m_rhs->eval_string();
    }
    else if (m_lhs->get_type() == DOUBLE || m_rhs->get_type() == DOUBLE) 
    {
      return m_lhs->eval_double() > m_rhs->eval_double();
    }
    else
    {
      return m_lhs->eval_int() > m_rhs->eval_int();
    }
  }
  else if (m_oper == GREATER_EQUAL)
  {
    assert(m_lhs && m_rhs) // Make sure both lhs and rhs exists
    // Check left and right side 
    if (m_lhs->get_type() == STRING || m_rhs->get_type() == STRING)
    {
      return m_lhs->eval_string() >= m_rhs->eval_string();
    }
    else if (m_lhs->get_type() == DOUBLE || m_rhs->get_type() == DOUBLE) 
    {
      return m_lhs->eval_double() >= m_rhs->eval_double();
    }
    else
    {
      return m_lhs->eval_int() >= m_rhs->eval_int();
    }
  }
  else if (m_oper == NOT_EQUAL)
  {
    assert(m_lhs && m_rhs) // Make sure both lhs and rhs exists
    // Check left and right side 
    if (m_lhs->get_type() == STRING || m_rhs->get_type() == STRING)
    {
      return m_lhs->eval_string() !=  m_rhs->eval_string();
    }
    else if (m_lhs->get_type() != DOUBLE || m_rhs->get_type() == DOUBLE) 
    {
      return m_lhs->eval_double() != m_rhs->eval_double();
    }
    else
    {
      return m_lhs->eval_int() != m_rhs->eval_int();
    }
  }
  else if (m_oper == EQUAL)
  {
    assert(m_lhs && m_rhs) // Make sure both lhs and rhs exists
    // Check left and right side 
    if (m_lhs->get_type() == STRING || m_rhs->get_type() == STRING)
    {
      return m_lhs->eval_string() == m_rhs->eval_string();
    }
    else if (m_lhs->get_type() == DOUBLE || m_rhs->get_type() == DOUBLE) 
    {
      return m_lhs->eval_double() == m_rhs->eval_double();
    }
    else
    {
      return m_lhs->eval_int() == m_rhs->eval_int();
    }
  }
  else if (m_oper == AND)
  {
    assert(m_lhs && m_rhs) // Make sure both lhs and rhs exists
    // Check left and right side 
    if (m_lhs->get_type() == STRING || m_rhs->get_type() == STRING)
    {
      return m_lhs->eval_string() && m_rhs->eval_string();
    }
    else if (m_lhs->get_type() == DOUBLE || m_rhs->get_type() == DOUBLE) 
    {
      return m_lhs->eval_double() && m_rhs->eval_double();
    }
    else
    {
      return m_lhs->eval_int() && m_rhs->eval_int();
    }
  }
  else if (m_oper == OR)
  {
    assert(m_lhs && m_rhs) // Make sure both lhs and rhs exists
    // Check left and right side 
    if (m_lhs->get_type() == STRING || m_rhs->get_type() == STRING)
    {
      return m_lhs->eval_string() || m_rhs->eval_string();
    }
    else if (m_lhs->get_type() == DOUBLE || m_rhs->get_type() == DOUBLE) 
    {
      return m_lhs->eval_double() || m_rhs->eval_double();
    }
    else
    {
      return m_lhs->eval_int() || m_rhs->eval_int();
    }
  }*/
  /* BINARY_OPERATORS EVALUATION */
/*  else if (m_oper == PLUS)
  {
    if (m_lhs->m_type == DOUBLE || m_rhs->m_type == DOUBLE)
    {
      return m_lhs->eval_double() + m_rhs->eval_double();
    }
    else
    {
      return m_lhs->eval_int() + m_rhs->eval_int();
    }
  }
  else
  {
    cout << "fucking shit what da hell" << endl;
  }
*/
}


double Expression::eval_double()
{  
  if (m_node == CONSTANT)
  {
    return *(double*) m_value;
  }
  if (m_node == VARIABLE)
  {
    return m_var->get_double_value();
  }
  if (m_node == BINARY_OPERATOR)
  {  
    switch(m_oper)
    {
      case MULTIPLY: 
        return m_lhs->eval_double() * m_rhs->eval_double();
      case PLUS:
        return m_lhs->eval_double() + m_rhs->eval_double();
      case MINUS:
        return m_lhs->eval_double() - m_rhs->eval_double();
      case DIVIDE:
        return m_lhs->eval_double() / m_rhs->eval_double();
      default:
        cerr << "Error: eval_double in m_oper failed!" << endl;
    }
  }
/*  if (m_type == INT)
  {
    int r = eval_int();
    double s = (double) r;
    return s;}
*/
}

string Expression::eval_string()
{
  stringstream ss;
  string value;
  if (m_node == CONSTANT)
  {
    return *(string*) m_value;
  }
  if (m_node == VARIABLE)
  {
    if (m_var->m_type == INT)
    {
      ss << m_var->get_int_value();
      ss >> value;
      return value;      
    }
    if (m_var->m_type == DOUBLE)
    { 
      ss << m_var->get_double_value();
      ss >> value;
      return value;
    }
    return m_var->get_string_value();
  }
  if (m_node == BINARY_OPERATOR)
  {
    if (m_oper == PLUS)
    {  
      return m_lhs->eval_string() + m_rhs->eval_string();   
    }
  }
}

