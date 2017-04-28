#include "assignment_stmt.h"

Assignment_stmt::Assignment_stmt(Variable* lhs, Expression* rhs, Operator_type op_type)
{
  m_lhs = lhs;
  m_rhs = rhs;
  m_oper = op_type;
}

void Assignment_stmt::execute()
{
  assert (false);
  // Need to implement
}
