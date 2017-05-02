#include "expression.h"
#include "variable.h"
#include "constant.h"


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
    case NOT:
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
    case FLOOR:
    case ABS:
      m_node = UNARY_OPERATOR;
      break;
    //set the default of the case incase cant get the op_type
    default: cerr << "Error: cannot assign operator type in EXPR constructor"
                  << endl;
    break;
  }
}

// Constructor for constants
Expression::Expression(int value, Gpl_type gpl_type, Expression *lhs, Expression *rhs)
{
  m_type = gpl_type;
  m_lhs = lhs;
  m_rhs = rhs;
  m_node = CONSTANT; // Set this node_type to CONSTANT
  m_constant = new Constant(value);
}

Expression::Expression(double value, Gpl_type gpl_type, Expression *lhs, Expression *rhs)
{
  m_type = gpl_type;
  m_lhs = lhs;
  m_rhs = rhs;
  m_node = CONSTANT; // Set this node_type to CONSTANT
  m_constant = new Constant(value);
}

Expression::Expression(string *value, Gpl_type gpl_type, Expression *lhs, Expression *rhs)
{
  m_type = gpl_type;
  m_lhs = lhs;
  m_rhs = rhs;
  m_node = CONSTANT; // Set this node_type to CONSTANT
  m_constant = new Constant(value);
}

// Constructor for variable
Expression::Expression(Variable *variable)
{
  m_var = variable;
  m_type = variable->m_type;
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
  if (m_node == CONSTANT)
  {
    return m_constant->get_int_value();
  }
  else if (m_node == VARIABLE)
  {
    return m_var->get_int_value();
  }
  else if (m_node == BINARY_OPERATOR)
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
      default: 
        cerr << "Error: cannot find m_oper in binary of eval_int()!" << endl;
        return 1;
    }
  }
  else if (m_node == LOGICAL_OPERATOR) 
  {
    switch(m_oper)
    {
      case OR: 
        if (m_lhs->m_type == INT && m_rhs->m_type == DOUBLE)
        {
          return (double) m_lhs->eval_int() || m_rhs->eval_double();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == INT)
        {
          return  m_lhs->eval_double() || (double) m_rhs->eval_int();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == DOUBLE)
        {
          return m_lhs->eval_double() || m_rhs->eval_double();
        }
        else
        {
          return m_lhs->eval_int() || m_rhs->eval_int();
        }
      case AND:
        if (m_lhs->m_type == INT && m_rhs->m_type == DOUBLE)
        {
          return (double)m_lhs->eval_int() &&  m_rhs->eval_double();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == INT)
        {
          return  m_lhs->eval_double() && (double)m_rhs->eval_int();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == DOUBLE)
        {
          return m_lhs->eval_double() && m_rhs->eval_double();
        }
        else
        {
          return m_lhs->eval_int() && m_rhs->eval_int();
        }
      case EQUAL:
        if (m_lhs->m_type == INT && m_rhs->m_type == DOUBLE)
        {
          return (double) m_lhs->eval_int() ==  m_rhs->eval_double();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == INT)
        {
          return m_lhs->eval_double() == (double) m_rhs->eval_int();
        }
        else if (m_lhs->m_type == STRING && m_rhs->m_type == INT)
        {
          string s_value = m_lhs->eval_string();
          int int_value = m_rhs->eval_int();
          stringstream ss;
          string right_value;
          ss << int_value;
          ss >> right_value;
          return s_value == right_value;
        }
        else if (m_lhs->m_type == INT && m_rhs->m_type == STRING)
        {
	  int int_value = m_lhs->eval_int();
          stringstream ss;
          string left;
          ss << int_value;
          ss >> left;
          string right = m_rhs->eval_string();
          return left == right;
        }
        else if (m_lhs->m_type == INT && m_rhs->m_type == INT)
        {
          return m_lhs->eval_int() == m_rhs->eval_int();
        }
        else if (m_lhs->m_type == INT && m_rhs->m_type == INT_ARRAY)
        {
          return m_lhs->eval_int() == m_rhs->eval_int();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == DOUBLE)
        {
 	  return m_lhs->eval_double() == m_rhs->eval_double();
 	}
        else if (m_lhs->m_type == STRING || m_rhs->m_type == STRING)
        {
          return m_lhs->eval_string() == m_rhs->eval_string();
	}
        else
        {
          cerr << "ERROR: Trouble in equal of logical of eval_int()!" << endl;
          return 1;
        }
      case NOT_EQUAL:
        if (m_lhs->m_type == INT && m_rhs->m_type == DOUBLE)
        {
          return (double) m_lhs->eval_int() !=  m_rhs->eval_double();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == INT)
        {
          return m_lhs->eval_double() != (double) m_rhs->eval_int();
        }
        else if (m_lhs->m_type == STRING && m_rhs->m_type == INT)
        {
          string s_value = m_lhs->eval_string();
          int int_value = m_rhs->eval_int();
          stringstream ss;
          string right_value;
          ss << int_value;
          ss >> right_value;
          return s_value != right_value;
        }
        else if (m_lhs->m_type == INT && m_rhs->m_type == STRING)
        {
	  int int_value = m_lhs->eval_int();
          stringstream ss;
          string left;
          ss << int_value;
          ss >> left;
          string right = m_rhs->eval_string();
          return left != right;
        }
        else if (m_lhs->m_type == INT && m_rhs->m_type == INT)
        {
          return m_lhs->eval_int() != m_rhs->eval_int();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == DOUBLE)
        {
 	  return m_lhs->eval_double() != m_rhs->eval_double();
 	}
        else if (m_lhs->m_type == STRING || m_rhs->m_type == STRING)
        {
          return m_lhs->eval_string() != m_rhs->eval_string();
	}
        else
        {
          cerr << "ERROR: Trouble in != of logical of eval_int()!" << endl;
          return 1;
        }
        return m_lhs->eval_int() != m_rhs->eval_int();
      case LESS_THAN:
        if (m_lhs->m_type == INT && m_rhs->m_type == DOUBLE)
        {
          return (double) m_lhs->eval_int() <  m_rhs->eval_double();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == INT)
        {
          return m_lhs->eval_double() < (double) m_rhs->eval_int();
        }
        else if (m_lhs->m_type == STRING && m_rhs->m_type == INT)
        {
          string s_value = m_lhs->eval_string();
          int int_value = m_rhs->eval_int();
          stringstream ss;
          string right_value;
          ss << int_value;
          ss >> right_value;
          return s_value < right_value;
        }
        else if (m_lhs->m_type == INT && m_rhs->m_type == STRING)
        {
	  int int_value = m_lhs->eval_int();
          stringstream ss;
          string left;
          ss << int_value;
          ss >> left;
          string right = m_rhs->eval_string();
          return left < right;
        }
        else if (m_lhs->m_type == INT && m_rhs->m_type == INT)
        {
          return m_lhs->eval_int() < m_rhs->eval_int();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == DOUBLE)
        {
 	  return m_lhs->eval_double() < m_rhs->eval_double();
 	}
        else if (m_lhs->m_type == STRING || m_rhs->m_type == STRING)
        {
          return m_lhs->eval_string() < m_rhs->eval_string();
	}
        else
        {
          cerr << "ERROR: Trouble in < of logical of eval_int()!" << endl;
          return 1;
        }
      case LESS_EQUAL:
        if (m_lhs->m_type == INT && m_rhs->m_type == DOUBLE)
        {
          return (double) m_lhs->eval_int() <=  m_rhs->eval_double();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == INT)
        {
          return m_lhs->eval_double() <= (double) m_rhs->eval_int();
        }
        else if (m_lhs->m_type == STRING && m_rhs->m_type == INT)
        {
          string s_value = m_lhs->eval_string();
          int int_value = m_rhs->eval_int();
          stringstream ss;
          string right_value;
          ss << int_value;
          ss >> right_value;
          return s_value <= right_value;
        }
        else if (m_lhs->m_type == INT && m_rhs->m_type == STRING)
        {
	  int int_value = m_lhs->eval_int();
          stringstream ss;
          string left;
          ss << int_value;
          ss >> left;
          string right = m_rhs->eval_string();
          return left <= right;
        }
        else if (m_lhs->m_type == INT && m_rhs->m_type == INT)
        {
          return m_lhs->eval_int() <= m_rhs->eval_int();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == DOUBLE)
        {
 	  return m_lhs->eval_double() <= m_rhs->eval_double();
 	}
        else if (m_lhs->m_type == STRING || m_rhs->m_type == STRING)
        {
          return m_lhs->eval_string() <= m_rhs->eval_string();
	}
        else
        {
          cerr << "ERROR: Trouble in <= of logical of eval_int()!" << endl;
          return 1;
        }
      case GREATER_THAN:
        if (m_lhs->m_type == INT && m_rhs->m_type == DOUBLE)
        {
          return (double) m_lhs->eval_int() >  m_rhs->eval_double();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == INT)
        {
          return m_lhs->eval_double() > (double) m_rhs->eval_int();
        }
        else if (m_lhs->m_type == STRING && m_rhs->m_type == INT)
        {
          string s_value = m_lhs->eval_string();
          int int_value = m_rhs->eval_int();
          stringstream ss;
          string right_value;
          ss << int_value;
          ss >> right_value;
          return s_value > right_value;
        }
        else if (m_lhs->m_type == INT && m_rhs->m_type == STRING)
        {
	  int int_value = m_lhs->eval_int();
          stringstream ss;
          string left;
          ss << int_value;
          ss >> left;
          string right = m_rhs->eval_string();
          return left > right;
        }
        else if (m_lhs->m_type == INT && m_rhs->m_type == INT)
        {
          return m_lhs->eval_int() > m_rhs->eval_int();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == DOUBLE)
        {
 	  return m_lhs->eval_double() > m_rhs->eval_double();
 	}
        else if (m_lhs->m_type == STRING || m_rhs->m_type == STRING)
        {
          return m_lhs->eval_string() > m_rhs->eval_string();
	}
        else
        {
          cerr << "ERROR: Trouble in > of logical of eval_int()!" << endl;
          return 1;
        }
      case GREATER_EQUAL:
        if (m_lhs->m_type == INT && m_rhs->m_type == DOUBLE)
        {
          return (double) m_lhs->eval_int() >=  m_rhs->eval_double();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == INT)
        {
          return m_lhs->eval_double() >= (double) m_rhs->eval_int();
        }
        else if (m_lhs->m_type == STRING && m_rhs->m_type == INT)
        {
          string s_value = m_lhs->eval_string();
          int int_value = m_rhs->eval_int();
          stringstream ss;
          string right_value;
          ss << int_value;
          ss >> right_value;
          return s_value >= right_value;
        }
        else if (m_lhs->m_type == INT && m_rhs->m_type == STRING)
        {
	  int int_value = m_lhs->eval_int();
          stringstream ss;
          string left;
          ss << int_value;
          ss >> left;
          string right = m_rhs->eval_string();
          return left >= right;
        }
        else if (m_lhs->m_type == INT && m_rhs->m_type == INT)
        {
          return m_lhs->eval_int() >= m_rhs->eval_int();
        }
        else if (m_lhs->m_type == DOUBLE && m_rhs->m_type == DOUBLE)
        {
 	  return m_lhs->eval_double() >= m_rhs->eval_double();
 	}
        else if (m_lhs->m_type == STRING || m_rhs->m_type == STRING)
        {
          return m_lhs->eval_string() >= m_rhs->eval_string();
	}
        else
        {
          cerr << "ERROR: Trouble in >= of logical of eval_int()!" << endl;
          return 1;
        }
      case NOT:
        if (m_lhs->m_type == DOUBLE)
        {
          return !m_lhs->eval_double();
        }
        else
        {
          return !m_lhs->eval_int();
        }
      default:
        cerr << "Error: cannot find m_oper in logical_ops of eval_double()!" << endl;
        return 1;
    }
  }
  else if (m_node == UNARY_OPERATOR)
  {
    if (m_oper == UNARY_MINUS)
    { 
      return (-m_lhs->eval_int());
    }
    else if (m_oper == ABS)
    {
      return abs(m_lhs->eval_int());
    }
    else if (m_oper == FLOOR)
    {
      if (m_lhs->m_type == DOUBLE)
      {
        return floor(m_lhs->eval_double());
      }
      else 
      {
        return floor(m_lhs->eval_int());
      }
    }
    else if (m_oper == RANDOM)
    {
      if (m_lhs->m_type == DOUBLE)
      { 
        // If lhs is take the floor and cast it to an int
        return rand() % (int) floor(m_lhs->eval_double());
      }
      else
      {
        return rand() % m_lhs->eval_int();
      } 
    }
    else if (m_oper ==  UNARY_MINUS)
    {
      return -m_lhs->eval_int();
    }
    else
    {
      cerr << "Error: Cannot find m_oper in eval_int();" << endl;
      return 1;
    }
  }
  else
  {
    cerr << "ERROR: TROUBLE IN EVAL_INT()" << endl;
    return 1;
  }
}

double Expression::eval_double()
{  
  // Check for ints. Cast to double if there are any
  if (m_type == INT)
  {
    int value;
    double d_value;
    value = eval_int();
    d_value = (double) value;
    return d_value;
  }
  if (m_node == CONSTANT)
  {
    if (m_constant->get_type() == INT)
    {
      int value;
      value = m_constant->get_int_value();
      return (double)value;
    }
    else
    {
      return m_constant->get_double_value();
    }
  }
  else if (m_node == VARIABLE)
  {
    if (m_var->m_type == INT)
    {
      assert(m_var->m_type == INT);
      int value;
      value = m_var->get_int_value();
      return (double)value;
    }
    else
    {
      return m_var->get_double_value();
    }
  }
  else if (m_node == BINARY_OPERATOR)
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
        cerr << "Error: cannot find m_oper in eval_double()!" << endl;
        return 1;
    }
  }
  else if (m_node == UNARY_OPERATOR)
  { 
    /* The parenthesis that encapsulates the order of ops is very
       important. YOU MUST NOT CHANGE THE ORDER OF THE PARENS!!!
       OR YOU WILL GET THE WRONG RETURN VALUES!!!! */
    if (m_oper == SIN)
    {
      return sin (m_lhs->eval_double() * M_PI / 180.0);
    }
    else if (m_oper == COS)
    {
      return cos (m_lhs->eval_double() * M_PI / 180.0);
    }
    else if (m_oper == TAN)
    {
      return tan (m_lhs->eval_double() * M_PI / 180.0);
    }
    // For arcsin, arccos, arctan...parens only around recursive call
    else if (m_oper == ASIN)
    {
      return asin (m_lhs->eval_double()) * 180.0 / M_PI;
    }
    else if (m_oper == ACOS)
    {
      return acos (m_lhs->eval_double()) * 180.0 / M_PI;
    }
    else if (m_oper == ATAN)
    {
      return atan (m_lhs->eval_double()) * 180.0 / M_PI;
    }
    else if (m_oper == SQRT)
    {
      return sqrt (m_lhs->eval_double());
    }
    else if (m_oper == ABS)
    {
      return abs(m_lhs->eval_double());
    }
    else if (m_oper == UNARY_MINUS)
    {
      return (-m_lhs->eval_double());
    }
  }
  else
  { 
    cerr << "ERROR: TROUBLE IN EVAL_DOUBLE()" << endl;
    return 1;
  }
}

// Recursion function for transversing the tree and finding its string value
string Expression::eval_string()
{
  stringstream ss;
  string value;
  // Casting and base case for for recursion in eval_string
  // If double call eval_double() let it handle the doubles 
  // return then cast to string
  if (m_type == DOUBLE)
  {
    double value;
    string s_value;
    value = eval_double();
    ss << value;
    ss >> s_value;
    return s_value;
  }
  // Check for ints as well.
  if (m_type == INT)
  {
    int value;
    string s_value;
    value = eval_int();
    ss << value;
    ss >> s_value;
    return s_value;
  }     
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
  else if (m_node == VARIABLE)
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
      cerr << "exp.cpp 684 this ran" << endl;
      return m_var->get_string_value();
    }
  }
  else if (m_node == BINARY_OPERATOR)
  {
    if (m_oper == PLUS)
    { 
      cerr << " expres:692 " << m_lhs->eval_string();
      cerr << " m_rih " << m_rhs->eval_string();
      return m_lhs->eval_string() + m_rhs->eval_string();   
    }
    else
    {
      cerr << "ERROR: cannot find m_oper in eval_string()!" << endl;
    }
  }
  else
  {
    return "ERROR: TROUBLE IN EVAL_STRING()!";
  }
}

Animation_block* Expression::eval_animation_block()
{
  if (m_node == VARIABLE)
  {
   assert(m_var->m_type == ANIMATION_BLOCK);
   return m_var->get_animation_block();
  }
}
