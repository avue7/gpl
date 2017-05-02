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
  for(m_initializer->execute(); m_expr->eval_int(); m_incrementor->execute())
  {
   cerr << "body executed" << endl;  
   cerr << "m_body in m_expr os : " << m_expr->m_type << endl;
   cerr << "end condition value is :" << m_expr->eval_int() << endl;
   // m_body->execute();
  }
}
