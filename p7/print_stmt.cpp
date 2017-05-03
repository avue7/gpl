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
  cerr << "PRINT_STMT.CPP(16) VALUE IS : " << s_value << endl;
  cerr << " ___m_TYPE is : " << m_expr->m_type << endl;
  cerr << "    m_node is : " << m_expr->m_node << endl;
  cout << "print[" << m_line_number << "]: " << s_value << endl;
}
