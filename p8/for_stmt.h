#ifndef FOR_STMT_H
#define FOR_STMT_H

#include "statement.h"
#include "statement_block.h"
#include "expression.h"

class For_stmt : public Statement
{
  public:
    For_stmt(Statement_block* initializer, Statement_block* incrementor, Statement_block* body, Expression* expr);

    void execute();

    Expression* m_expr;
    Statement_block* m_initializer, *m_incrementor, *m_body;
};

#endif
