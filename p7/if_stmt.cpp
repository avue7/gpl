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
  if(m_expr->eval_int()) //If true
  {
    m_then->execute();
  }
  else if (m_else) // If m_else exists and not null
  {
    m_else->execute();
  }
/*  else
  {
    cerr << "ERROR: trouble in execute() of if_stmt.cpp" << endl;
  } */
}
