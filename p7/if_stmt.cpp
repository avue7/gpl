#include "if_stmt.h"

If_stmt::If_stmt(Expression* expr, Statement_block* then)
{
  m_expr = expr;
  m_then = then;
  m_else = NULL;
}

If_stmt::If_stmt(Expression* expr, Statement_block* then, Statement_block* b_else)
{
  m_expr = expr;
  m_then = then;
  m_else = b_else;
}

void If_stmt::execute()
{
  // NOT SURE WHAT TO DO HERE YET.
}
