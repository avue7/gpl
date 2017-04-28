#ifndef ASSIGNMENT_STMT_H
#define ASSIGNMENT_STMT_H

#include "statement.h"
#include "expression.h"
#include "variable.h"
#include "assert.h"
#include "gpl_type.h"

class Assignment_stmt : public Statement
{
  public:
    //Member functions
    Assignment_stmt(Variable* lhs, Expression* rhs, Operator_type op_type);   

    void execute();    

    //Member vairables
    Variable* m_lhs;
    Expression* m_rhs;
    Operator_type m_oper;
};

#endif
