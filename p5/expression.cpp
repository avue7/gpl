#include "expression.h"
#include "variable.h"
#include "constant.h"
// unary and binary operator
Expression::Expression(Operator_type operator_type, Gpl_type gpl_type, Expression *lhs, Expression *rhs)
{
  m_return_type = gpl_type;
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
  m_return_type = gpl_type;
  m_lhs = lhs;
  m_rhs = rhs;
  m_node = CONSTANT; // Set this node_type to CONSTANT
  m_constant = new Constant(value);
}

Expression::Expression(double value, Gpl_type gpl_type, Expression *lhs, Expression *rhs)
{
  m_return_type = gpl_type;
  m_lhs = lhs;
  m_rhs = rhs;
  m_node = CONSTANT; // Set this node_type to CONSTANT
  m_constant = new Constant(value);
}

Expression::Expression(string *value, Gpl_type gpl_type, Expression *lhs, Expression *rhs)
{
  m_return_type = gpl_type;
  m_lhs = lhs;
  m_rhs = rhs;
  m_node = CONSTANT; // Set this node_type to CONSTANT
  m_constant = new Constant(value);
}

// Constructor for variable
Expression::Expression(Variable *variable)
{
  m_var = variable;;
  m_return_type = variable->m_type;
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
    return m_constant->get_int_value();
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
  stringstream ss;
  double value;
  if (m_node == CONSTANT)
  {
    if (m_constant->get_type() == INT)
    {
      int value;
      value = m_constant->get_int_value();
      return (double)value;
    }
    return m_constant->get_double_value();
  }
  if (m_node == VARIABLE)
  {
    if (m_var->m_type == INT)
    {
      int value;
      value = m_var->get_int_value();
      return (double)value;
    }
    else
    {
      return m_var->get_double_value();
    }
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
}

// Recursion function for transversing the tree and finding its string value
string Expression::eval_string()
{
  stringstream ss;
  string value;
  // This is one of our base case for recursion to stop.
  if (m_node == CONSTANT)
  {       
    if (m_constant->get_type() == INT)
    {
      ss << m_constant->get_int_value();
      ss >> value;
      return value;      
    }
    else if (m_constant->get_type() == DOUBLE)
    { 
      ss << m_constant->get_double_value();
      ss >> value;
      return value;
    }
    else
    {
    return m_constant->get_string_value();
    }
  }
  // The other base case for recursion to stop.
  /* NOTE: CASTING HAPPENS HERE */ 
  if (m_node == VARIABLE)
  {
    if (m_var->m_type == INT)
    {
      ss << m_var->get_int_value();
      ss >> value;
      return value;      
    }
    else if (m_var->m_type == DOUBLE)
    { 
      ss << m_var->get_double_value();
      ss >> value;
      return value;
    }
    else
    {
      return m_var->get_string_value();
    }
  }
  if (m_node == BINARY_OPERATOR)
  {
    if (m_oper == PLUS)
    { 
      if (m_return_type == DOUBLE)
      {
        double value;
        string s_value;
        value = eval_double();
        ss << value;
        ss >> s_value;
        return s_value;
      }
      else
     {      
        return m_lhs->eval_string() + m_rhs->eval_string();  
      } 
    }
  }
}
/*
      // If either side is a double FOR BOTH VARIABLE AND CONSTANT LEAF
      // with a simple type (RETURN TYPE) of string.
      if (m_lhs->m_var->m_type == DOUBLE || m_rhs->m_var->m_type == DOUBLE)
      {
         double left;
         double right;
         double result;
         string to_string;
         
         left = m_lhs->eval_double();
         right = m_rhs->eval_double();
         result = left + right;
         ss << result;
         ss >> to_string;     
         return to_string;
      }
      // If leaves of both types are an int on either side, just use 
      // eval_double for simplicity.
      if (m_lhs->m_var->m_type == INT || m_rhs->m_var->m_type == INT)
      {
         double left;
         double right;
         double result;
         string to_string;
         
         left = m_lhs->eval_double();
         right = m_rhs->eval_double();
         result = left + right;
         ss << result;
         ss >> to_string;     
         return to_string;
      }
      // Recursively call the left side of the tree
      // then recursively call the right side and add the 
      // two values together  */
