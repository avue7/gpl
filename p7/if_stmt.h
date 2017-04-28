#ifndef IF_STMT_H
#define IF_STMT_H

#include "expression.h"
#include "statement_block.h"

// Use class <NAME> : public <INHERENT_CLASS_NAME> {} 
// for inherentency to happen. 
class If_stmt : public Statement
{
  public:
    // HUMPH...contains an Expression and STATEMENT_BLOCKS for
    // then and else (the else block is optional).

    // Public member variables
    Expression* m_expr;
    Statement_block* m_then;
    Statement_block* m_else;

    // Remember: this is a pure virtual function
    void execute();

    // Member functions
    If_stmt(Expression* expr, Statement_block* then);
    If_stmt(Expression* expr, Statement_block* then, Statement_block* b_else);
};

#endif     
