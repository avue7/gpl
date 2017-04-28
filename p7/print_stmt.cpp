#include "print_stmt.h"

Print_stmt::Print_stmt(int line_number, Expression* expr)
{
  m_expr = expr;
  m_line_number = line_number;
}

void Print_stmt::execute()
{
  //assert(false);
  /* So the expression here is evaluated to a string and the string 
     should be printed */
  string s_value;
  s_value = m_expr->eval_string();
  cout << "print[" << m_line_number << "]: " << s_value << endl;
}
