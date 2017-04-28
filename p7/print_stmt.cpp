#include "print_stmt.h"

Print_stmt::Print_stmt(int line_number, Expression* expr)
{
  m_expr = expr;
  m_line_number = line_number;
}

void Print_stmt::execute()
{
  assert(false);
  // ......need to implement
}
