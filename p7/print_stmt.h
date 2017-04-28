#ifndef PRINT_STMT_H
#define PRINT_STMT_H

#include "statement.h"
#include "expression.h"
#include "assert.h" // Need for initial before function implementation

class Print_stmt : public Statement
{
  public:
    // Member functions
    Print_stmt(Expression* expr);

    // Virtual function from Statement
    void execute();

    // Member variables
    Expression* m_expr;
    
    
    
};

#endif
