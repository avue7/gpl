#ifndef  EXPRESSION_H
#define   EXPRESSION_H

#include "gpl_type.h"
#include "error.h" // Dont know if i need this yet but just in case for now
#include <string>
#include <iostream>
#include <cmath>
#include <assert.h>
using namespace std;

class Expression
{
  public:
    // Member variables declared here
    Expression *m_lhs;
    Expression *m_rhs;
    Operator_type m_oper;
    Gpl_type m_gpl_type;
    void *m_value;
    Node_type m_node; // To store the type of Nodes

    int eval_int();         // To return evaluated ints
    double eval_double();   // to return evaluated doubles
    string eval_string();   // To return evaluated strings
    

    // Member functions: 

    // Constructor for unary and binary operator
    Expression (Operator_type operator_type, Gpl_type gpl_type, Expression *lhs, Expression *rhs);
    // Constructor for constant
    Expression (void *value, Gpl_type gpl_type, Expression *lhs, Expression *rhs);
   
   
  private:
    enum Tree_kinds {EXPRESSION, CONSTANT, VARIABLE}; // since im making a node maybe i dont need this
    Tree_kinds m_kind;
    Expression *evaluation(); // member function to build tree; recursively evaluates each node
};
#endif
