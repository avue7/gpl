#ifndef  EXPRESSION_H
#define   EXPRESSION_H

#include "gpl_type.h"
#include "error.h" // Dont know if i need this yet but just in case for now
#include <limits.h> // To use macros M_PI
#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <cmath>
#include <math.h>
#include <assert.h>
using namespace std;

class Variable; // Forwarding class to avoid inf. loop
class Constant;

class Expression
{
  public:
    // Member variables declared here
    Expression *m_lhs;
    Expression *m_rhs;
    Operator_type m_oper;
    Gpl_type m_type;
    Variable *m_var;
    Constant *m_constant;
 
    // Member functions: 
    int eval_int();         // To return evaluated ints
    double eval_double();   // to return evaluated doubles
    string eval_string();   // To return evaluated strings     
    
    // Constructor for unary and binary operator
    Expression (Operator_type operator_type, Gpl_type gpl_type, Expression *lhs, Expression *rhs);
    // Constructor for constant
    Expression (int value, Gpl_type gpl_type, Expression *lhs, Expression *rhs);
    Expression (double value, Gpl_type gpl_type, Expression *lhs, Expression *rhs);
    Expression (string *value, Gpl_type gpl_type, Expression *lhs, Expression *rhs);
    // Constructor for variable
    Expression (Variable *variable); 
   
    enum Node {BINARY_OPERATOR = 2, LOGICAL_OPERATOR=4, UNARY_OPERATOR=6, CONSTANT=8, VARIABLE=10}; // since im making a node maybe i dont need this
    Node m_node;
};
#endif
