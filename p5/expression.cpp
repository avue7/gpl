#include "expression.h"

Expression::Expression(Operator_type operator_type, Gpl_type gpl_type, Expression *lhs, Expression *rhs)
{
  m_operator_type = operator_type;
  m_gpl_type = gpl_type;
  m_lhs = lhs;
  m_rhs = rhs;
}
