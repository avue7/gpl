#ifndef ASSIGNMENT_STMT_H
#define ASSIGNMENT_STMT_H

#include "statement.h"
#include "expression.h"
#include "variable.h"
#include "assert.h"

enum Assignment_type { ASS_ASSIGN,
                       ASS_PLUS, 
                       ASS_MINUS,
                       ASS_PLUS_PLUS,
                       ASS_MINUS_MINUS, 
};

class Assignment_stmt : public Statement
{
  public:
    //Member functions
    Assignment_stmt(Variable* lhs, Expression* rhs, Assignment_type type);   

    void execute();    

    //Member vairables
    Variable* m_var_lhs;
    Expression* m_expr_rhs;
    Assignment_type m_oper;
};

#endif
