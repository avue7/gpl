#ifndef EXIT_STMT_H
#define EXIT_STMT_H

#include "statement.h"
#include "expression.h"
#include "assert.h"

class Exit_stmt : public Statement
{
  public:
    // Member functions
    Exit_stmt(Expression* expr);
    
    void execute();
   
    // Member vairables
    Expression* m_expr;
};

#endif
