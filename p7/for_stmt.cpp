#include "for_stmt.h"

For_stmt::For_stmt(Statement_block* initializer, Statement_block* incrementor, Statement_block* body, Expression* expr)
{
  m_initializer = initializer;
  m_incrementor = incrementor;
  m_body = body;
  m_expr = expr;
}

void For_stmt::execute()
{
  assert(false);
  // Need to implement
}
