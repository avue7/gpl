#include "exit_stmt.h"

Exit_stmt::Exit_stmt(Expression* expr)
{
  m_expr = expr;
}

void Exit_stmt::execute()
{
  assert(false);
  // Need to implement
}
