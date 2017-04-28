#include "assignment_stmt.h"

Assignment_stmt::Assignment_stmt(Variable* lhs, Expression* rhs, Assignment_type type)
{
  m_var_lhs = lhs;
  m_expr_rhs = rhs;
  m_oper = type;
}

void Assignment_stmt::execute()
{
  if (m_oper == ASS_ASSIGN)
  {
    if (m_expr_rhs->m_type == INT)
    {
      int value;
      value = m_expr_rhs->eval_int();
      m_var_lhs->set_new_value(value);
      cerr << "from ass.cpp new value is : " << m_var_lhs->get_int_value() << endl;
    }
  }
}
