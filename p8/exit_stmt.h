#ifndef EXIT_STMT_H
#define EXIT_STMT_H

#include "statement.h"
#include "expression.h"
#include "assert.h"
#include "event_manager.h"
class Exit_stmt : public Statement
{
  public:
    // Member functions
    Exit_stmt(Expression* expr, int line_number);
    ~Exit_stmt();
    
    void execute();
   
    // Member vairables
    Expression* m_expr;
    int m_line_number;
};

#endif
