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
    Operator_type m_operator_type;
    Gpl_type m_gpl_type;
    void *m_value;
    Node_type m_node_type;

    int eval_int();
    double eval_double();
    string eval_string();
    
    // Constructor for unary and binary operator
    Expression (Operator_type operator_type, Gpl_type gpl_type, Expression *lhs, Expression *rhs);
    // Constructor for constant
    Expression (void *m_value, Gpl_type gpl_type, Expression *m_lhs, Expression *m_rhs);
   
   
  private:
    enum Tree_kinds {EXPRESSION, CONSTANT, VARIABLE};
    Tree_kinds m_kind;
    Expression *evaluation();
};
#endif
