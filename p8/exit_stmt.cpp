#include "exit_stmt.h"

Exit_stmt::Exit_stmt(Expression* expr, int line_number)
{
  m_expr = expr;
  m_line_number = line_number;
}

Exit_stmt::~Exit_stmt() {}

void Exit_stmt::execute()
{
  int int_val;
  int_val = m_expr->eval_int();
  cout << "gpl[" << m_line_number << "]: exit(" << int_val << ")" << endl;
  exit(int_val);
}
